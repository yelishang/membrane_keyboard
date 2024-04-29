#include <string.h>
#include <stdbool.h>
#include "keycode.h"
#include "matrix.h"
#include "quantum.h"
#include "config.h"


// clang-format off
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
  [0] = LAYOUT( /* Base */
      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_MUTE, KC_VOLD, KC_VOLU, 
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,   KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,   KC_P7,  KC_P8,   KC_P9,  
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                                          KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,                     KC_UP,              KC_P1,  KC_P2,   KC_P3,   
      KC_LCTL,  MO(1),    KC_LGUI,  KC_LALT,            KC_SPC,                                 KC_RALT,  MO(1),    KC_APP,   KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT,           KC_P0,   KC_PDOT, KC_PENT
  ),

  [1] = LAYOUT(
      IM_TOFN, KC_SLEP, _______, _______, _______, _______, _______, _______, _______, KC_WSCH, KC_MPRV, KC_MPLY, KC_MNXT,          _______, _______, _______, 
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, IM_TEST, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______,          _______, _______, _______,
      _______, _______, _______, _______,          _______,                            _______, _______, _______, _______,          _______, _______, _______,          _______, _______, _______
  ),
};
extern uint8_t hid_keyboard_out_report_buf[1];
bool test_flag = false;
void indicator_light(uint8_t temp);
uint32_t test_time = 0;
bool temp = false;

void housekeeping_task(void) {

  if (test_flag) {
    if (timer_elapsed32(test_time) > 500) {
      test_time = timer_read32();
      temp = !temp ;
      if (temp) {
        register_code16(KC_A);
        indicator_light(0xFF);
      } else {
        unregister_code16(KC_A);
        indicator_light(0x0);
      }
    }
  } else {
    indicator_light(hid_keyboard_out_report_buf[0]);
  }
}

bool process_record_kb(uint16_t keycode, keyevent_t event) {
    switch (keycode) {
        case IM_TEST: {
          if(event.pressed) {
            test_flag = !test_flag;
          }
        } break;
        default:
            break;
    }
    return true;
}
