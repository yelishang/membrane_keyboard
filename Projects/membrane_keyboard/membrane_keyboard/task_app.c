#include "task_app.h"
#include "main.h"

#include "usbd_core.h"
#include "usbd_user_hid.h"

extern const uint16_t keymaps[1][MATRIX_ROWS][MATRIX_COLS];

#define pgm_read_word(address_short) *((uint16_t *)(address_short))
#define KEY_LAYOUT_MAX               (sizeof(keymaps) / sizeof(keymaps[0]))
  
static uint8_t evtbuf[8] = {0};
uint8_t layer_state = 0;
static keyevent_t func = {.pressed = false};


uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
  if ((key.row < MATRIX_ROWS) && (key.col < MATRIX_COLS) && (layer < NUM_KEYMAP_LAYERS_RAW))
  {
    return pgm_read_word(&keymaps[layer][key.row][key.col]);
  }
  return KC_NO;
}

action_t keymap_key_to_action(keyevent_t event)
{
  action_t action;
  static keypos_t key;
  static bool fn_flag = false;
  static bool fn_layer = false;
  if (fn_flag) {
    layer_state = fn_layer;
  }
  action.layer = layer_state;
  action.keycode.all = keymap_key_to_keycode(layer_state, event.key);
  if (event.pressed && action.keycode.all == IM_TOFN) {
    fn_flag = !fn_flag;
    fn_layer = !fn_layer;
  } else if (!fn_flag && IS_FN(action.keycode.all))
  {
    action.layer = action.keycode.base;
    key.row = event.key.row;
    key.col = event.key.col;
  }
  else if (!fn_flag && !event.pressed && layer_state &&
           (key.row == event.key.row) &&
           (key.col == event.key.col))
  {
    action.layer = 0;
  }

  return action;
}

void action_key_pressed(keycode_t keycode, keyevent_t event) {
  if (IS_KEY(keycode.all))
  {
    process_key(keycode, event.pressed);
  }
  if (IS_MOD(keycode.all))
  {
    process_mod(keycode, event.pressed);
  }
  if (IS_SYSTEM(keycode.all))
  {
    process_system(keycode, event.pressed);
  }
  if (IS_CUSTOMER(keycode.all))
  {
    process_customer(keycode, event.pressed);
  }
  

}

void bsp_usbd_resume(void);

void APPTask(void *pvParameters) {
  BaseType_t xResult;
  keyevent_t event;
  uint32_t ulNotifiedValue;
  function_counter_t function_counter;
  while (1)
  {
    xResult = xTaskNotifyWait(0x00, 0xFFFFFFFF, &ulNotifiedValue, portMAX_DELAY);
    if (xResult == pdTRUE) {
      if (ulNotifiedValue & 0x01) {
        while (xQueueReceive(xQueueAppEventMsg, evtbuf, 0) == pdPASS) {

          action_t action;
          event.key.col = evtbuf[0];
          event.key.row = evtbuf[1];
          function_counter.raw = evtbuf[2];
          event.pressed = function_counter.function_counter_s.key_pressed;

          action = keymap_key_to_action(event);

              if (action.layer != layer_state)
              {
                func.key.row = event.key.row;
                func.key.col = event.key.col;
                func.pressed = event.pressed;
                layer_state = action.layer;
                process_clear_report();
              }
              else if (!((func.pressed == true) &&
                 (func.key.row == event.key.row) &&
                 (func.key.col == event.key.col))) {
              action_key_pressed(action.keycode, event);
            }

          if (UsbdCoreInfo.DeviceState == USBD_STATE_SUSPENDED)
          {
            xSemaphoreTake(xMutexUsb, portMAX_DELAY);
            if (UsbdCoreInfo.RemoteWakeup != 0)
            {
              bsp_usbd_resume();
              /* Remote Wakeup */
              USB->POWER |= USB_POWER_RESUME;
              vTaskDelay(10);   // delay 10ms
              USB->POWER &= ~USB_POWER_RESUME;
              USBD_Core_Resume();
            }
            xSemaphoreGive(xMutexUsb);
          }
          
          report_send();
          
        }
      }
    }
  }
}

