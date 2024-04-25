#pragma once


#include "main.h"
#include "led_arithmetic.h"

#ifdef LED_MATRIX 

typedef enum rgb_task_states { STARTING, RENDERING, FLUSHING, SYNCING } rgb_task_states;

enum rgb_matrix_effects {
  LED_MATRIX_NONE = 0,
  #define LED_MATRIX_EFFECT(name, ...) LED_MATRIX_##name,
  #include "lamp_effect.h"
  #undef LED_MATRIX_EFFECT
  LED_MATRIX_EFFECT_MAX
};

# define LED_MATRIX_USE_LIMITS(min, max) \
          uint8_t min = 0;                    \
          uint8_t max = LED_MATRIX_LED_COUNT;

#define HAS_FLAGS(bits, flags) ((bits & flags) == flags)
#define abs(x) ((x)>0?(x):-(x))

#define LED_FLAG_ALL 0xFF
#define LED_FLAG_NONE 0x00
#define LED_FLAG_MODIFIER 0x01
#define LED_FLAG_KEYLIGHT 0x04
#define LED_FLAG_INDICATOR 0x08

#define HAS_ANY_FLAGS(bits, flags) ((bits & flags) != 0x00)

#define NO_LED 255

typedef struct PACKED {
    uint8_t     enable : 2;
    uint8_t     mode : 6;
    uint16_t    reserved;
    uint8_t     val;
    uint8_t     speed; // EECONFIG needs to be increased to support this
    uint8_t     flags;
}led_eeconfig_t;

typedef struct  {
    uint8_t     iter;
    uint8_t     flags;
    bool        init;
} effect_params_t;


// Last led hit
#ifndef LED_HITS_TO_REMEMBER
#    define LED_HITS_TO_REMEMBER 8
#endif // LED_HITS_TO_REMEMBER

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
typedef struct {
    uint8_t  count;
    uint8_t  x[LED_HITS_TO_REMEMBER];
    uint8_t  y[LED_HITS_TO_REMEMBER];
    uint8_t  index[LED_HITS_TO_REMEMBER];
    uint16_t tick[LED_HITS_TO_REMEMBER];
} last_hit_t;
#endif // LED_MATRIX_KEYREACTIVE_ENABLED


extern uint32_t     g_led_timer;
extern led_eeconfig_t led_matrix_eeconfig;
void rgb_task_render(uint8_t effect);
void led_matrix_set_color(uint16_t index, uint8_t num);
void rgb_matrix_task(void);

void process_led_matrix(uint8_t row, uint8_t col, bool pressed);

static inline bool led_matrix_check_finished_leds(uint8_t led_idx) {
    return led_idx < LED_MATRIX_LED_COUNT;

}

#define LED_MATRIX_TEST_LED_FLAGS() \
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue

#endif
