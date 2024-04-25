#pragma once

//#define SINK_ROW_PINS \
//    {C4, C5, C2, C3, C1, C0}

#define MATRIX_ROW_PINS \
    {A1, A2, A4, A6, A7, B0, B3, B5}
#define MATRIX_COL_PINS \
    {A11, A14, A15, B15, B14, B13, B12, B9, B8, C5, C4, C3, C2, C1, C0, D4, A3, A0}
    
#define SINK_ROWS                  6
#define MATRIX_ROWS                8
#define MATRIX_COLS                18

#define LED_MATRIX_LED_COUNT 120

#define DEBOUNCE 1
    
#define DIODE_DIRECTION COL2ROW

#define LAYOUT( \
 k4b, k1a, k19, k69, k49, k0h, k45, k62, k12, k13, k03, k43, k23,        k4h, k5h, k6h,                       \
 k1b, k0b, k0a, k09, k07, k17, k16, k06, k05, k02, k04, k14, k15, k63,   k1d, k1c, k1e,    k30, k3d, k3e, k2e,\
 k6b, k7b, k7a, k79, k77, k67, k66, k76, k75, k72, k74, k64, k65, k53,   k10, k0c, k0e,    k70, k7d, k7e,     \
 k6a, k5b, k5a, k59, k57, k47, k46, k56, k55, k52, k54, k44, k33,                          k60, k6d, k6e, k7c,\
 k68, k3b, k3a, k39, k37, k27, k26, k36, k35, k32, k24,      k58,             k4c,         k50, k5d, k5e,     \
 k1h, k6g, k61, k4f,      k40,                k2f, k5g, k22, k3h,        k2c, k20, k2d,    k4d,      k4e, k5c \
) \
{ \
 { ___, ___, k02, k03, k04, k05, k06, k07, ___, k09, k0a, k0b, k0c, ___, k0e, ___, ___, k0h }, \
 { k10, ___, k12, k13, k14, k15, k16, k17, ___, k19, k1a, k1b, k1c, k1d, k1e, ___, ___, k1h }, \
 { k20, ___, k22, k23, k24, ___, k26, k27, ___, ___, ___, ___, k2c, k2d, k2e, k2f, ___, ___ }, \
 { k30, ___, k32, k33, ___, k35, k36, k37, ___, k39, k3a, k3b, ___, k3d, k3e, ___, ___, k3h }, \
 { k40, ___, ___, k43, k44, k45, k46, k47, ___, k49, ___, k4b, k4c, k4d, k4e, k4f, ___, k4h }, \
 { k50, ___, k52, k53, k54, k55, k56, k57, k58, k59, k5a, k5b, k5c, k5d, k5e, ___, k5g, k5h }, \
 { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6a, k6b, ___, k6d, k6e, ___, k6g, k6h }, \
 { k70, ___, k72, ___, k74, k75, k76, k77, ___, k79, k7a, k7b, k7c, k7d, k7e, ___, ___, ___ }  \
}

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

typedef struct  {
    uint8_t x;
    uint8_t y;
} led_point_t;

typedef struct  {
    uint8_t     matrix_co[MATRIX_ROWS][MATRIX_COLS];
    led_point_t point[LED_MATRIX_LED_COUNT];
    uint8_t     flags[LED_MATRIX_LED_COUNT];
} led_config_t;

typedef struct  {
    led_point_t location[LED_MATRIX_LED_COUNT];
} led_config_m;

extern const led_config_t g_led_config;


enum im_keys {
  IM_TOFN = 0x7E00
};


#define LED_MATRIX_KEYREACTIVE_ENABLED

#define ENABLE_LED_MATRIX_ALPHAS_MODS
#define ENABLE_LED_MATRIX_BREATHING
#define ENABLE_LED_MATRIX_BAND
#define ENABLE_LED_MATRIX_BAND_PINWHEEL
#define ENABLE_LED_MATRIX_BAND_SPIRAL
#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
#define ENABLE_LED_MATRIX_CYCLE_OUT_IN
#define ENABLE_LED_MATRIX_DUAL_BEACON
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_LED_MATRIX_SOLID_SPLASH
#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH
#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_WAVE_UP_DOWN





