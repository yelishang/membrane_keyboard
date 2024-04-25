#include "rgb_matrix.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

#ifdef LED_MATRIX 
static uint8_t led_render_phase[MATRIX_ROWS][MATRIX_COLS] = {0};
extern uint8_t led_play_phase[SINK_ROWS][MATRIX_COLS];
const led_point_t k_led_matrix_center = {112, 32};
static effect_params_t led_effect_params = {0, LED_FLAG_ALL, false};
static uint32_t led_timer_buffer;

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
static last_hit_t last_hit_buffer;
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
last_hit_t g_last_hit_tracker;
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

#include "effect_runner_reactive_splash.h"



#define LED_MATRIX_EFFECT(name)
#define LED_MATRIX_CUSTOM_EFFECT_IMPLS
#include "lamp_effect.h"
#undef LED_MATRIX_CUSTOM_EFFECT_IMPLS
#undef LED_MATRIX_EFFECT

static uint8_t led_task_state = 0;

uint8_t effect = 5;

led_eeconfig_t led_matrix_eeconfig;
uint32_t       g_led_timer;




void rgb_task_render(uint8_t effect) {

    bool rendering         = false;
    switch (effect) {
        case LED_MATRIX_NONE:
            break;
#define LED_MATRIX_EFFECT(name, ...)          \
    case LED_MATRIX_##name:                   \
        rendering = name(&led_effect_params); \
        break;
#include "lamp_effect.h"
#undef LED_MATRIX_EFFECT
        case UINT8_MAX: {
        }
            return;
    }
    if (!rendering) {
      led_task_state = FLUSHING;
    } else {
      led_task_state = STARTING;
    }
    
}

extern const led_config_m g_led_matrix;
void led_matrix_set_color(uint16_t index, uint8_t num) {
  
  led_render_phase[g_led_matrix.location[index].y][g_led_matrix.location[index].x] = num;
}

static void rgb_task_start(void) {
  
  g_led_timer = led_timer_buffer;
  led_task_state = RENDERING;
  g_last_hit_tracker = last_hit_buffer;
}

void rgb_task_flush(uint8_t effect){
  memcpy(led_play_phase, led_render_phase, sizeof(led_render_phase));
  led_task_state = SYNCING;
}

static void rgb_task_sync(void) {
  
  led_task_state = STARTING;
}


static void led_task_timers(void) {
    uint32_t deltaTime = timer_elapsed32(led_timer_buffer);
    led_timer_buffer = timer_read32();
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    uint8_t count = last_hit_buffer.count;
    for (uint8_t i = 0; i < count; ++i) {
        if (UINT16_MAX - deltaTime < last_hit_buffer.tick[i]) {
            last_hit_buffer.count--;
            continue;
        }
        last_hit_buffer.tick[i] += deltaTime;
    }

#endif // LED_MATRIX_KEYREACTIVE_ENABLED
}

void rgb_matrix_task(void) {
  
  led_matrix_eeconfig.val = 250;
  led_matrix_eeconfig.speed = 100;
  led_task_timers();
  
    switch (led_task_state) {
      case STARTING:
          rgb_task_start();
          break;
      case RENDERING:
          rgb_task_render(effect);
          break;
      case FLUSHING:
          rgb_task_flush(effect);
          break;
      case SYNCING:
          rgb_task_sync();
          break;
  }
}


__attribute__((weak)) uint8_t led_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
    return 0;
}

uint8_t led_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i) {
    uint8_t led_count = led_matrix_map_row_column_to_led_kb(row, column, led_i);
    uint8_t led_index = g_led_config.matrix_co[row][column];
    if (led_index != NO_LED) {
        led_i[led_count] = led_index;
        led_count++;
    }
    return led_count;
}

void process_led_matrix(uint8_t row, uint8_t col, bool pressed) {
#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    uint8_t led[LED_HITS_TO_REMEMBER];
    uint8_t led_count = 0;

    if (pressed)
    {
        led_count = led_matrix_map_row_column_to_led(row, col, led);
    }

    if (last_hit_buffer.count + led_count > LED_HITS_TO_REMEMBER) {
        memcpy(&last_hit_buffer.x[0], &last_hit_buffer.x[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.y[0], &last_hit_buffer.y[led_count], LED_HITS_TO_REMEMBER - led_count);
        memcpy(&last_hit_buffer.tick[0], &last_hit_buffer.tick[led_count], (LED_HITS_TO_REMEMBER - led_count) * 2); // 16 bit
        memcpy(&last_hit_buffer.index[0], &last_hit_buffer.index[led_count], LED_HITS_TO_REMEMBER - led_count);
        last_hit_buffer.count = LED_HITS_TO_REMEMBER - led_count;
    }

    for (uint8_t i = 0; i < led_count; i++) {
        uint8_t index                = last_hit_buffer.count;
        last_hit_buffer.x[index]     = g_led_config.point[led[i]].x;
        last_hit_buffer.y[index]     = g_led_config.point[led[i]].y;
        last_hit_buffer.index[index] = led[i];
        last_hit_buffer.tick[index]  = 0;
        last_hit_buffer.count++;
    }
#endif // LED_MATRIX_KEYREACTIVE_ENABLED

#if defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
    if (led_matrix_eeconfig.mode == LED_MATRIX_TYPING_HEATMAP) {
        process_led_matrix_typing_heatmap(row, col);
    }
#endif // defined(LED_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_LED_MATRIX_TYPING_HEATMAP)
}


void led_matrix_init(void) {

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED
    g_last_hit_tracker.count = 0;
    for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
        g_last_hit_tracker.tick[i] = UINT16_MAX;
    }

    last_hit_buffer.count = 0;
    for (uint8_t i = 0; i < LED_HITS_TO_REMEMBER; ++i) {
        last_hit_buffer.tick[i] = UINT16_MAX;
    }
#endif // LED_MATRIX_KEYREACTIVE_ENABLED
}

void led_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
    if (!led_matrix_eeconfig.enable) {
        return;
    }
    if (mode < 1) {
        led_matrix_eeconfig.mode = 1;
    } else if (mode >= LED_MATRIX_EFFECT_MAX) {
        led_matrix_eeconfig.mode = LED_MATRIX_EFFECT_MAX - 1;
    } else {
        led_matrix_eeconfig.mode = mode;
    }
    led_task_state = STARTING;
//    eeconfig_flag_led_matrix(write_to_eeprom);
}
#endif 

