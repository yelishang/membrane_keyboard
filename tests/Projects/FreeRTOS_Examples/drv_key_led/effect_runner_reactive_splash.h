#pragma once

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

typedef uint8_t (*reactive_splash_f)(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);

bool effect_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        uint8_t val = 0;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], led_matrix_eeconfig.speed);
            val           = effect_func(val, dx, dy, dist, tick);
        }
        led_matrix_set_color(i, scale8(val, led_matrix_eeconfig.val));
    }
    return led_matrix_check_finished_leds(led_max);;
}

#endif // LED_MATRIX_KEYREACTIVE_ENABLED

typedef uint8_t (*i_f)(uint8_t val, uint8_t i, uint8_t time);

bool effect_runner_i(effect_params_t* params, i_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 4);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_color(i, effect_func(led_matrix_eeconfig.val, i, time));
    }
    return led_matrix_check_finished_leds(led_max);
}

typedef uint8_t (*dx_dy_f)(uint8_t val, int16_t dx, int16_t dy, uint8_t time);

bool effect_runner_dx_dy(effect_params_t* params, dx_dy_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 2);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        int16_t dx = g_led_config.point[i].x - k_led_matrix_center.x;
        int16_t dy = g_led_config.point[i].y - k_led_matrix_center.y;
        led_matrix_set_color(i, effect_func(led_matrix_eeconfig.val, dx, dy, time));
    }
    return led_matrix_check_finished_leds(led_max);
}

typedef uint8_t (*dx_dy_dist_f)(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint8_t time);

bool effect_runner_dx_dy_dist(effect_params_t* params, dx_dy_dist_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 2);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        int16_t dx   = g_led_config.point[i].x - k_led_matrix_center.x;
        int16_t dy   = g_led_config.point[i].y - k_led_matrix_center.y;
        uint8_t dist = sqrt16(dx * dx + dy * dy);
        led_matrix_set_color(i, effect_func(led_matrix_eeconfig.val, dx, dy, dist, time));
    }
    return led_matrix_check_finished_leds(led_max);
}


typedef uint8_t (*sin_cos_i_f)(uint8_t val, int8_t sin, int8_t cos, uint8_t i, uint8_t time);

bool effect_runner_sin_cos_i(effect_params_t* params, sin_cos_i_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t time      = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 4);
    int8_t   cos_value = cos8(time) - 128;
    int8_t   sin_value = sin8(time) - 128;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_color(i, effect_func(led_matrix_eeconfig.val, cos_value, sin_value, i, time));
    }
    return led_matrix_check_finished_leds(led_max);
}

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

typedef uint8_t (*reactive_f)(uint8_t val, uint16_t offset);

bool effect_runner_reactive(effect_params_t* params, reactive_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / led_matrix_eeconfig.speed;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, led_matrix_eeconfig.speed);
        led_matrix_set_color(i, effect_func(led_matrix_eeconfig.val, offset));
    }
    return led_matrix_check_finished_leds(led_max);
}

#endif // LED_MATRIX_KEYREACTIVE_ENABLED

