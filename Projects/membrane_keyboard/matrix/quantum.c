#include "quantum.h"
#include "keyprocess.h"

void tap_code16(uint16_t code) {
    register_code16(code);
    vTaskDelay(10);
    unregister_code16(code);
}

__attribute__((weak)) void register_code16(uint16_t code) {
    keycode_t keycode;
    keycode.all = code;
    keyevent_t event;
    event.pressed = true;
    action_key_pressed(keycode, event);
    report_send();
}

__attribute__((weak)) void unregister_code16(uint16_t code) {
    keycode_t keycode;
    keycode.all = code;
    keyevent_t event;
    event.pressed = false;
    action_key_pressed(keycode, event);
    report_send();
}
