#pragma once

#include "main.h"

void register_code16(uint16_t code);
void unregister_code16(uint16_t code);
void tap_code16(uint16_t code);
void action_key_pressed(keycode_t keycode, keyevent_t event);
