#pragma once
#include "main.h"

void report_send(void);
uint8_t usbd_report_send(uint8_t ep, uint8_t *report);
void process_key(keycode_t keycode, bool pressed);
void process_system(keycode_t keycode, bool pressed);
void process_mod(keycode_t keycode, bool pressed);
void process_customer(keycode_t keycode, bool pressed);
void lift_all_keys(void);
