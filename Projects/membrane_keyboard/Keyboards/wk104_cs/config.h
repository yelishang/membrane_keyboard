#pragma once

#define FW_VERSION 1.0
#define MANUFACTURER "Your Company" // 键盘制造商
#define PRODUCT "Keyboard DEMO"     // 键盘名称
#define VENDOR_ID 0x8888            // USB VID
#define PRODUCT_ID 0x5A42           // USB PID
#define DEVICE_VER 0x0100           // 版本号

#define MATRIX_ROW_PINS \
    {A3, A6, A7, B0, B1, B2, B4, B5}
#define MATRIX_COL_PINS \
    {A11, A14, A15, B15, B14, B13, B12, B9, B8, C5, C4, C3, C2, C1, C0, D4, A1, A2}

#define MATRIX_ROWS                8
#define MATRIX_COLS                18

#define DEBOUNCE 1
    
#define DIODE_DIRECTION COL2ROW

#define NUM_KEYMAP_LAYERS_RAW 2

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

enum im_keys {
  IM_TOFN = 0x7E00,
  IM_TEST
};

