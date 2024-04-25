#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "matrix.h"
#include "timer.h"
#include "bsp_pin_defs.h"
#include "hal_pal_lld.h"

#include "main.h"

#define ROWS_PER_HAND (MATRIX_ROWS)

#define ATOMIC_BLOCK_FORCEON

#ifdef DIRECT_PINS_RIGHT
#    define SPLIT_MUTABLE
#else
#    define SPLIT_MUTABLE const
#endif
#ifdef MATRIX_ROW_PINS_RIGHT
#    define SPLIT_MUTABLE_ROW
#else
#    define SPLIT_MUTABLE_ROW const
#endif
#ifdef MATRIX_COL_PINS_RIGHT
#    define SPLIT_MUTABLE_COL
#else
#    define SPLIT_MUTABLE_COL const
#endif

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

#ifndef MATRIX_ROWS
#    define MATRIX_ROWS 1
#endif

#ifdef DIRECT_PINS
static SPLIT_MUTABLE pin_t direct_pins[ROWS_PER_HAND][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
#    ifdef MATRIX_ROW_PINS
static SPLIT_MUTABLE_ROW pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
#    endif // MATRIX_ROW_PINS
#    ifdef MATRIX_COL_PINS
static SPLIT_MUTABLE_COL pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;
#    endif // MATRIX_COL_PINS
#endif

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
matrix_row_t matrix[MATRIX_ROWS];     // debounced values

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}


static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}


 extern void debounce_init(uint8_t num_rows);

__attribute__((weak)) void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (uint8_t i = 0; i < 100 ; i++);
}


#ifdef DIRECT_PINS

__attribute__((weak)) void matrix_init_pins(void) {
    for (int row = 0; row < ROWS_PER_HAND; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                setPinInputHigh(pin);
            }
        }
    }
}

__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        pin_t pin = direct_pins[current_row][col_index];
        current_row_value |= readMatrixPin(pin) ? 0 : row_shifter;
    }

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

#elif defined(DIODE_DIRECTION)
#    if defined(MATRIX_ROW_PINS) && defined(MATRIX_COL_PINS)
#        if (DIODE_DIRECTION == COL2ROW)

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinInputHigh(pin);

    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        unselect_row(x);
    }
}

__attribute__((weak)) void matrix_init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(col_pins[x]);
        }
    }
}

void led_init_pins(void) {
  setPinOutput_writeLow(A10);
  setPinOutput_writeHigh(B10);
  setPinOutput_writeLow(A5);
}

void led_set_close(void) {
  setPinOutput_writeLow(A10);
  setPinOutput_writeHigh(B10);
  setPinOutput_writeLow(A5);
}

__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

#        elif (DIODE_DIRECTION == ROW2COL)

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
#            ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#            else
        setPinInputHigh_atomic(pin);
#            endif
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col(x);
    }
}

__attribute__((weak)) void matrix_init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(row_pins[x]);
        }
    }
}

__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

#        else
#            error DIODE_DIRECTION must be one of COL2ROW or ROW2COL!
#        endif
#    endif // defined(MATRIX_ROW_PINS) && defined(MATRIX_COL_PINS)
#else
#    error DIODE_DIRECTION is not defined!
#endif



void matrix_init(void)
{
  RCC->APBENR |= RCC_APBENR_GPIOEN;

  matrix_init_pins();
  led_init_pins();
  // initialize matrix state: all keys off
  memset(matrix, 0, sizeof(matrix));
  memset(raw_matrix, 0, sizeof(raw_matrix));

  debounce_init(ROWS_PER_HAND);
  
}

extern bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

matrix_row_t curr_matrix[MATRIX_ROWS] = {0};
matrix_row_t curr_matrix2[MATRIX_ROWS] = {0};
uint8_t matrix_scan(void) {


#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        matrix_read_cols_on_row(curr_matrix, current_row);
    }
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        matrix_read_cols_on_row(curr_matrix2, current_row);
    }
    
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }
#endif
    bool changed = memcmp(curr_matrix, curr_matrix2, sizeof(curr_matrix));
    if (!changed)  {
      changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
      if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

      changed = debounce(raw_matrix, matrix, ROWS_PER_HAND, changed);
    }

    return (uint8_t)changed;
}



/**
 * @brief Generates a tick event at a maximum rate of 1KHz that drives the
 * internal QMK state machine.
 */
static inline void generate_tick_event(void) {
    static uint16_t last_tick = 0;
    const uint16_t  now       = timer_read();
    if (TIMER_DIFF_16(now, last_tick) != 0) {
//        action_exec(TICK_EVENT);
        last_tick = now;
    }
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}


uint16_t keycode_at_keymap_location_raw(uint8_t layer_num, uint8_t row, uint8_t column) {
    if (layer_num < NUM_KEYMAP_LAYERS_RAW && row < MATRIX_ROWS && column < MATRIX_COLS) {
        return keymaps[layer_num][row][column];
    }
    return KC_TRNS;
}

static matrix_row_t get_real_keys(uint8_t row, matrix_row_t rowdata) {
    matrix_row_t out = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // read each key in the row data and check if the keymap defines it as a real key
        if (keycode_at_keymap_location_raw(0, row, col) && (rowdata & (((matrix_row_t)1) << col))) {
            // this creates new row data, if a key is defined in the keymap, it will be set here
            out |= ((matrix_row_t)1) << col;
        }
    }
    return out;
}

static inline bool popcount_more_than_one(matrix_row_t rowdata) {
    rowdata &= rowdata - 1; // if there are less than two bits (keys) set, rowdata will become zero
    return rowdata;
}

static inline bool has_ghost_in_row(uint8_t row, matrix_row_t rowdata) {
    /* No ghost exists when less than 2 keys are down on the row.
    If there are "active" blanks in the matrix, the key can't be pressed by the user,
    there is no doubt as to which keys are really being pressed.
    The ghosts will be ignored, they are KC_NO.   */
    rowdata = get_real_keys(row, rowdata);
    if ((popcount_more_than_one(rowdata)) == 0) {
        return false;
    }
    /* Ghost occurs when the row shares a column line with other row,
    and two columns are read on each row. Blanks in the matrix don't matter,
    so they are filtered out.
    If there are two or more real keys pressed and they match columns with
    at least two of another row's real keys, the row will be ignored. Keep in mind,
    we are checking one row at a time, not all of them at once.
    */
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (i != row && popcount_more_than_one(get_real_keys(i, matrix_get_row(i)) & rowdata)) {
            return true;
        }
    }
    return false;
}



static uint8_t evtbuf[8] = {0};

#include "FreeRTOS.h"
#include "queue.h"
extern volatile QueueHandle_t xQueueAppEventMsg;
/**
 * @brief This task scans the keyboards matrix and processes any key presses
 * that occur.
 *
 * @return true Matrix did change
 * @return false Matrix didn't change
 */
bool matrix_task(void) {

    static matrix_row_t matrix_previous[MATRIX_ROWS];
    function_counter_t function_counter;
    matrix_scan();
    bool matrix_changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS && !matrix_changed; row++) {
        matrix_changed |= matrix_previous[row] ^ matrix[row];
    }

    // Short-circuit the complete matrix processing if it is not necessary
    if (!matrix_changed) {
        generate_tick_event();
        return matrix_changed;
    }

    const bool process_keypress = true;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        const matrix_row_t current_row = matrix[row];
        const matrix_row_t row_changes = current_row ^ matrix_previous[row];

        if (!row_changes ||has_ghost_in_row(row, current_row)) {
            continue;
        }

        matrix_row_t col_mask = 1;
        for (uint8_t col = 0; col < MATRIX_COLS; col++, col_mask <<= 1) {
            if (row_changes & col_mask) {
              function_counter.function_counter_s.key_pressed = (current_row & col_mask) > 0 ?1 :0 ;
                if (process_keypress) {
                      evtbuf[0] = col;
                      evtbuf[1] = row;
                      evtbuf[2] = function_counter.raw;
                      xQueueSend(xQueueAppEventMsg, evtbuf, 0);
                      xTaskNotify(APPTask_Handler, 0x01, eSetBits);
                }
            }
        }

        matrix_previous[row] = current_row;
    }

    return matrix_changed;
}

typedef union
{
  uint8_t raw;
  struct {
      uint8_t num : 1;
      uint8_t caps : 1;
      uint8_t scroll : 1;
      uint8_t rev : 5;
  } indicator_light_led;
} indicator_light_t;

void indicator_light(uint8_t temp) {
  indicator_light_t indicator_light;
  indicator_light.raw = temp;
  writePin(A10, indicator_light.indicator_light_led.num);
  writePin(B10, !indicator_light.indicator_light_led.caps);
  writePin(A5, indicator_light.indicator_light_led.scroll);
}

