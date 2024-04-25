#include <string.h>
#include <stdbool.h>
#include "keycode.h"
#include "matrix.h"

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
        KC_LCTL,  MO(1),    KC_LGUI,  KC_LALT,            KC_SPC,                                 KC_RALT,  MO(1),    KC_APP,   KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT,           KC_P0,   KC_PDOT, KC_PENT),

    [1] = LAYOUT(
        IM_TOFN, KC_SLEP, _______, _______, _______, _______, _______, _______, _______, KC_WSCH, KC_MPRV, KC_MPLY, KC_MNXT,          _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______, _______, _______,
        _______, _______, _______, _______,          _______,                            _______, _______, _______, _______,          _______, _______, _______,          _______, _______, _______
    ),
};

const led_config_t g_led_config = {
    LAYOUT(
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
     17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
     38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
     58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
     78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
     94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104
    ), {
    {   0 ,  0 },  // 0
    {  20 ,  0 },  // 1
    {  30 ,  0 },  // 2
    {  39 ,  0 },  // 3
    {  49 ,  0 },  // 4
    {  64 ,  0 },  // 5
    {  74 ,  0 },  // 6
    {  84 ,  0 },  // 7
    {  94 ,  0 },  // 8
    { 108 ,  0 },  // 9
    { 118 ,  0 },  // 10
    { 128 ,  0 },  // 11
    { 138 ,  0 },  // 12
    { 150 ,  0 },  // 13
    { 160 ,  0 },  // 14
    { 170 ,  0 },  // 15
    { 204 ,  0 },  // 16

    {   0 , 15 },  // 17
    {  10 , 15 },  // 18
    {  20 , 15 },  // 19
    {  30 , 15 },  // 20
    {  39 , 15 },  // 21
    {  49 , 15 },  // 22
    {  59 , 15 },  // 23
    {  69 , 15 },  // 24
    {  79 , 15 },  // 25
    {  89 , 15 },  // 26
    {  98 , 15 },  // 27
    { 108 , 15 },  // 28
    { 118 , 15 },  // 29
    { 133 , 15 },  // 30
    { 150 , 15 },  // 31
    { 160 , 15 },  // 32
    { 170 , 15 },  // 33
    { 185 , 15 },  // 34
    { 194 , 15 },  // 35
    { 204 , 15 },  // 36
    { 214 , 15 },  // 37

    {   2 , 27 },  // 38
    {  15 , 27 },  // 39
    {  25 , 27 },  // 40
    {  34 , 27 },  // 41
    {  44 , 27 },  // 42
    {  54 , 27 },  // 43
    {  64 , 27 },  // 44
    {  74 , 27 },  // 45
    {  84 , 27 },  // 46
    {  94 , 27 },  // 47
    { 103 , 27 },  // 48
    { 113 , 27 },  // 49
    { 123 , 27 },  // 50
    { 135 , 27 },  // 51
    { 150 , 27 },  // 52
    { 160 , 27 },  // 53
    { 170 , 27 },  // 54
    { 185 , 27 },  // 55
    { 194 , 27 },  // 56
    { 204 , 27 },  // 57

    {   0 , 40 },  // 58
    {   4 , 40 },  // 59
    {  17 , 40 },  // 60
    {  27 , 40 },  // 61
    {  37 , 40 },  // 62
    {  47 , 40 },  // 63
    {  57 , 40 },  // 64
    {  66 , 40 },  // 65
    {  76 , 40 },  // 66
    {  86 , 40 },  // 67
    {  96 , 40 },  // 68
    { 106 , 40 },  // 69
    { 116 , 40 },  // 70
    { 132 , 40 },  // 71
    { 150 , 40 },  // 72
    { 160 , 40 },  // 73
    { 170 , 40 },  // 74
    { 185 , 40 },  // 75
    { 194 , 40 },  // 76
    { 204 , 40 },  // 77

    {   6 , 52 },  // 78
    {  22 , 52 },  // 79
    {  32 , 52 },  // 80
    {  42 , 52 },  // 81
    {  52 , 52 },  // 82
    {  62 , 52 },  // 83
    {  71 , 52 },  // 84
    {  81 , 52 },  // 85
    {  91 , 52 },  // 86
    { 101 , 52 },  // 87
    { 111 , 52 },  // 88
    { 129 , 52 },  // 89
    { 160 , 52 },  // 90
    { 185 , 52 },  // 91
    { 194 , 52 },  // 92
    { 204 , 52 },  // 93
    { 214 , 52 },  // 94

    {   1 , 64 },  // 95
    {  14 , 64 },  // 96
    {  26 , 64 },  // 97
    {  63 , 64 },  // 98
    { 100 , 64 },  // 99
    { 112 , 64 },  // 100
    { 124 , 64 },  // 101
    { 137 , 64 },  // 102
    { 150 , 64 },  // 103
}, {

    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 4, 1, 1, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4
}};