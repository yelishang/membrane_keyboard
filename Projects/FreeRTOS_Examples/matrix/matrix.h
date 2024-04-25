#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "debonce.h"
#include "config.h"
//#include "main.h"

bool matrix_task(void);

/* diode directions */
#define COL2ROW 0
#define ROW2COL 1

#if (MATRIX_COLS <= 8)
typedef uint8_t matrix_row_t;
#elif (MATRIX_COLS <= 16)
typedef uint16_t matrix_row_t;
#elif (MATRIX_COLS <= 32)
typedef uint32_t matrix_row_t;
#else
#    error "MATRIX_COLS: invalid value"
#endif

#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)

#ifdef __cplusplus
extern "C" {
#endif
typedef union
{
  uint8_t raw;
  struct {
      uint8_t ghost_key : 1;
      uint8_t key_pressed : 1;
      uint8_t rev : 6;
  } function_counter_s;
} function_counter_t;

typedef union
{
  uint8_t base;
  uint16_t all;
} keycode_t;
  
/* key matrix position */
typedef struct
{
  uint8_t col;
  uint8_t row;
} keypos_t;

/* key event */
typedef struct
{
  keypos_t key;
  bool pressed;
  bool long_press;
} keyevent_t;

typedef struct
{
  keycode_t keycode;
  uint8_t layer;
} action_t;

/* number of matrix rows */
uint8_t matrix_rows(void);
/* number of matrix columns */
uint8_t matrix_cols(void);
/* should be called at early stage of startup before matrix_init.(optional) */
void matrix_setup(void);
/* intialize matrix for scaning. */
void matrix_init(void);
/* scan all key states on matrix */
uint8_t matrix_scan(void);
/* whether matrix scanning operations should be executed */
bool matrix_can_read(void);
/* whether a switch is on */
bool matrix_is_on(uint8_t row, uint8_t col);
/* matrix state on row */
matrix_row_t matrix_get_row(uint8_t row);
/* print matrix for debug */
void matrix_print(void);
/* delay between changing matrix pin state and reading values */
void matrix_output_select_delay(void);
void matrix_output_unselect_delay(uint8_t line, bool key_pressed);
/* only for backwards compatibility. delay between changing matrix pin state and reading values */
void matrix_io_delay(void);

/* power control */
void matrix_power_up(void);
void matrix_power_down(void);

void matrix_init_kb(void);
void matrix_scan_kb(void);

void matrix_init_user(void);
void matrix_scan_user(void);

#ifdef SPLIT_KEYBOARD
bool matrix_post_scan(void);
void matrix_slave_scan_kb(void);
void matrix_slave_scan_user(void);
#endif

void gpio_cs(void);
void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter);

#ifdef __cplusplus
}
#endif
