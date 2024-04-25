#pragma once

#define EECONFIG_DEBOUNCE_HELPER_CHECKED(name, offset, config)          \
    static uint8_t dirty_##name = false;                                \
                                                                        \
    bool eeconfig_check_valid_##name(void);                             \
    void eeconfig_post_flush_##name(void);                              \
                                                                        \
    static inline void eeconfig_init_##name(void) {                     \
        dirty_##name = true;                                            \
        if (eeconfig_check_valid_##name()) {                            \
            eeprom_read_block(&config, offset, sizeof(config));         \
            dirty_##name = false;                                       \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flush_##name(bool force) {              \
        if (force || dirty_##name) {                                    \
            eeprom_update_block(&config, offset, sizeof(config));       \
            eeconfig_post_flush_##name();                               \
            dirty_##name = false;                                       \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flush_##name##_task(uint16_t timeout) { \
        static uint16_t flush_timer = 0;                                \
        if (timer_elapsed(flush_timer) > timeout) {                     \
            eeconfig_flush_##name(false);                               \
            flush_timer = timer_read();                                 \
        }                                                               \
    }                                                                   \
    static inline void eeconfig_flag_##name(bool v) {                   \
        dirty_##name |= v;                                              \
    }                                                                   \
    static inline void eeconfig_write_##name(typeof(config) *conf) {    \
        if (memcmp(&config, conf, sizeof(config)) != 0) {               \
            memcpy(&config, conf, sizeof(config));                      \
            eeconfig_flag_##name(true);                                 \
        }                                                               \
    }

#define EECONFIG_DEBOUNCE_HELPER(name, offset, config)     \
    EECONFIG_DEBOUNCE_HELPER_CHECKED(name, offset, config) \
                                                           \
    bool eeconfig_check_valid_##name(void) {               \
        return true;                                       \
    }                                                      \
    void eeconfig_post_flush_##name(void) {}
