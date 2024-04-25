#include <string.h>
#include "keyprocess.h"
#include "matrix.h"
#include "keycode.h"
#include "main.h"

#include "usbd_core.h"
#include "usbd_user_hid.h"

#define USBD_HID_KEYBOARD_IN_REPORT_SIZE 8
#define USBD_HID_NKRO_IN_REPORT_SIZE     16
#define USBD_HID_CONSUMER_IN_REPORT_SIZE 3

#ifndef USBD_HID_RETRY_SIZE
# define USBD_HID_RETRY_SIZE  100000
#endif

uint8_t usbd_keyboard_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE] = {0};
uint8_t usbd_consumer_report_buf[USBD_HID_CONSUMER_IN_REPORT_SIZE] = {0};
uint8_t usbd_system_report_buf[USBD_HID_CONSUMER_IN_REPORT_SIZE] = {0};
uint8_t usbd_nkro_report_buf[USBD_HID_NKRO_IN_REPORT_SIZE] = {0};
 
static uint16_t       last_system_usage   = 0;

void process_key(keycode_t keycode, bool pressed)
{
  if (pressed) {
    int i;
    for (i = 2; i < 8; i++) {
      if (usbd_keyboard_report_buf[i] == keycode.base)
        break;
      if (usbd_keyboard_report_buf[i] == 0x00)
      {
        usbd_keyboard_report_buf[i] = keycode.base;
        break;
      }
    }
    
    if (i == 8) {
      usbd_nkro_report_buf[0] = USBD_REPORT_ID_NKRO;
      usbd_nkro_report_buf[2 + (keycode.base / 8)] |= (0x01 << (keycode.base % 8));
    }
  } else {
      for (int i = 2; i < 8; i++) {
        if (usbd_keyboard_report_buf[i] == keycode.base)
        {
          usbd_keyboard_report_buf[i] = 0x00;
          break;
        }
      }

      usbd_nkro_report_buf[0] = USBD_REPORT_ID_NKRO;
      usbd_nkro_report_buf[2 + (keycode.base / 8)] &= ~(0x01 << (keycode.base % 8));
  }
}

void process_customer(keycode_t keycode, bool pressed) {
  if (pressed) {
    usbd_consumer_report_buf[0] = USBD_REPORT_ID_CONSUMER;
    usbd_consumer_report_buf[1] = KEYCODE2CONSUMER(keycode.base);
    usbd_consumer_report_buf[2] = KEYCODE2CONSUMER(keycode.base) >> 8;
  } else {
    usbd_consumer_report_buf[0] = USBD_REPORT_ID_CONSUMER;
    usbd_consumer_report_buf[1] = 0x00;
    usbd_consumer_report_buf[2] = 0x00;
  }
}

void process_system(keycode_t keycode, bool pressed) {
  uint16_t usage = KEYCODE2SYSTEM(keycode.base);
  if (usage == last_system_usage) return;
  last_system_usage = usage;
  if (pressed) {
    usbd_system_report_buf[0] = USBD_REPORT_ID_SYSTEM;
    usbd_system_report_buf[1] = usage;
    usbd_system_report_buf[2] = usage >> 8;
  } else {
    usbd_system_report_buf[0] = USBD_REPORT_ID_SYSTEM;
    usbd_system_report_buf[1] = usage;
    usbd_system_report_buf[2] = usage >> 8;
  }
}

void process_mod(keycode_t keycode, bool pressed) {
  if (pressed) {
    if ((keycode.base >= 0xE0) && (keycode.base <= 0xE7)) {
      usbd_keyboard_report_buf[0] |= (0x01 << (keycode.base - 0xE0));
    }
  } else {
    if ((keycode.base >= 0xE0) && (keycode.base <= 0xE7)) {
      usbd_keyboard_report_buf[0] &= ~(0x01 << (keycode.base - 0xE0));
    }
  }
}

void process_clear_report(void) {
  usbd_nkro_report_buf[0] = USBD_REPORT_ID_NKRO;
  usbd_consumer_report_buf[0] = USBD_REPORT_ID_CONSUMER;
  memset(usbd_keyboard_report_buf, 0, sizeof(usbd_keyboard_report_buf));
  memset(usbd_nkro_report_buf + 1, 0, sizeof(usbd_nkro_report_buf) - 1);
  memset(usbd_consumer_report_buf + 1, 0, sizeof(usbd_consumer_report_buf) - 1);
}


uint8_t usbd_report_send(uint8_t ep, uint8_t *report)
{
  uint8_t error = 3;
  if (UsbdCoreInfo.DeviceState == USBD_STATE_CONFIGURED)
  {
    switch (ep)
    {
      case 0x81:
      {
        if (hid_ep1_in_xfer_flag == 0)
        {
          memcpy(hid_keyboard_in_report_buf, report, USBD_HID_KEYBOARD_IN_REPORT_SIZE);
          USBD_HW_Transmit(ep, hid_keyboard_in_report_buf, USBD_HID_KEYBOARD_IN_REPORT_SIZE);
          hid_ep1_in_xfer_flag = 1;
          error = 0;
        } else {
          error = 1;
        }
      }
      break;
      case 0x82:
      {
        if (hid_ep2_in_xfer_flag == 0)
        {
          switch (report[0])
          {
            case USBD_REPORT_ID_SYSTEM:
            {
              memcpy(hid_system_in_report_buf, report, USBD_HID_CONSUMER_IN_REPORT_SIZE);
              USBD_HW_Transmit(ep, hid_system_in_report_buf, USBD_HID_CONSUMER_IN_REPORT_SIZE);
              hid_ep2_in_xfer_flag = 1;
              error = 0;
            }
            break;
            case USBD_REPORT_ID_CONSUMER:
            {
              memcpy(hid_customer_in_report_buf, report, USBD_HID_CONSUMER_IN_REPORT_SIZE);
              USBD_HW_Transmit(ep, hid_customer_in_report_buf, USBD_HID_CONSUMER_IN_REPORT_SIZE);
              hid_ep2_in_xfer_flag = 1;
              error = 0;
            }
            break;
            case USBD_REPORT_ID_NKRO:
            {
              memcpy(hid_nkro_in_report_buf, report, USBD_HID_NKRO_IN_REPORT_SIZE);
              USBD_HW_Transmit(ep, hid_nkro_in_report_buf, USBD_HID_NKRO_IN_REPORT_SIZE);
              hid_ep2_in_xfer_flag = 1;
              error = 0;
            }
            break;
            default:
              error = 1;
              break;
          }
        } else {
          error = 1;
        }
      }
      break;
    }
  } else {
    error = 2;
  }
  return error;
}

void report_send(void) {
 uint8_t *report_buf = NULL;
 uint8_t ep = 0;
 if (memcmp(usbd_keyboard_report_buf, hid_keyboard_in_report_buf, sizeof(hid_keyboard_in_report_buf)) != 0)
 {
   report_buf = usbd_keyboard_report_buf;
   ep = 0x81;
 }
 else if (memcmp(usbd_consumer_report_buf, hid_customer_in_report_buf, sizeof(hid_customer_in_report_buf)) != 0)
 {
   report_buf = usbd_consumer_report_buf;
   ep = 0x82;
 }
 else if (memcmp(usbd_system_report_buf, hid_system_in_report_buf, sizeof(usbd_system_report_buf)) != 0)
 {
   report_buf = usbd_system_report_buf;
   ep = 0x82;
 }
 else if (memcmp(usbd_nkro_report_buf, hid_nkro_in_report_buf, sizeof(hid_nkro_in_report_buf)) != 0)
 {
   report_buf = usbd_nkro_report_buf;
   ep = 0x82;
 }

  if (report_buf != NULL)
  {
    xSemaphoreTake(xMutexUsb, portMAX_DELAY);
    while(usbd_report_send(ep, report_buf));
    xSemaphoreGive(xMutexUsb);
  }
}

