//#include "drv_key_led.h"
//#include "hal_pal_lld.h"
//#include "gpio.h"
//#include "bsp_pin_defs.h"
//#include "matrix.h"

//#include "config.h"

//#define PCT_DIV  PCT_CFGR_PSC_DIV64

//#define PCT_ARR  255

//#ifdef LED_MATRIX 
//static const pin_t klm_sink_lines[SINK_ROWS] = SINK_ROW_PINS;
//uint8_t led_play_phase[SINK_ROWS][MATRIX_COLS] = {0};
//#endif 

//extern const pin_t row_pins[MATRIX_ROWS];
//extern const pin_t col_pins[MATRIX_COLS];

//static uint32_t pct_ccr_addr[MATRIX_COLS] = {0};
//  
//const uint32_t pin2pct_tarns_array[] = {(uint32_t)(&PCT0->CCR0L), 
//                                        (uint32_t)(&PCT0->CCR1L),
//                                        (uint32_t)(&PCT0->CCR2L),
//                                        (uint32_t)(&PCT0->CCR3L),
//                                        (uint32_t)(&PCT0->CCR4L),
//                                        (uint32_t)(&PCT0->CCR5L),
//                                                              
//                                        (uint32_t)(&PCT1->CCR0L),
//                                        (uint32_t)(&PCT1->CCR1L),
//                                        (uint32_t)(&PCT1->CCR2L),
//                                        (uint32_t)(&PCT1->CCR3L),
//                                        (uint32_t)(&PCT1->CCR4L),
//                                        (uint32_t)(&PCT1->CCR5L),
//                                                              
//                                        (uint32_t)(&PCT2->CCR0L),
//                                        (uint32_t)(&PCT2->CCR1L),
//                                        (uint32_t)(&PCT2->CCR2L),
//                                        (uint32_t)(&PCT2->CCR3L),
//                                        (uint32_t)(&PCT2->CCR4L),
//                                        (uint32_t)(&PCT2->CCR5L),
//                                                              
//                                        (uint32_t)(&PCT3->CCR0L),
//                                        (uint32_t)(&PCT3->CCR1L),
//                                        (uint32_t)(&PCT3->CCR2L),
//                                        (uint32_t)(&PCT3->CCR3L),
//                                                              
//                                        (uint32_t)(&PCT4->CCR0L),
//                                        (uint32_t)(&PCT4->CCR1L),
//                                        (uint32_t)(&PCT4->CCR2L)
//};

//const int8_t pina2pca_array[] = {21, 20, 19, 18, 6, 7, 8, 9, -1, -1, 0, 1, 2, 3, 4, 5};
//const int8_t pinb2pca_array[] = {10, 11, 12, 13, 14, 15, 16, 17, 24, 23, 22};

//int8_t pin2pctnum_tarns(pin_t pin) {
//  int8_t rev = 0;
//  switch((uint32_t)PAL_PORT(pin)) {
//    case ((uint32_t)PAL_PORT(A0)): {
//      rev = pina2pca_array[PAL_PAD(pin)];
//    } break;
//    case ((uint32_t)PAL_PORT(B0)): {
//      if (PAL_PAD(pin) > sizeof(pinb2pca_array)) {
//        rev = -1;
//      } else {
//      rev = pinb2pca_array[PAL_PAD(pin)];
//      }
//    } break;
//    default:
//        rev = -1;
//      break;
//  }
//  return rev;
//}

//uint32_t pin2pct_tarns(int8_t num) {
//  if((num < 0) || (num > sizeof(pin2pct_tarns_array))) {
//    return 0;
//  }
//  return pin2pct_tarns_array[num];
//}


//void KeyLed_Init(void)
//{
//  // TODO: peripheral clock need enable
//  RCC->APBENR |= RCC_APBENR_GPIOEN |RCC_APBENR_PCT0EN |RCC_APBENR_PCT1EN |RCC_APBENR_PCT2EN |RCC_APBENR_PCT3EN |RCC_APBENR_PCT4EN;
//  
//#ifdef LED_MATRIX 
//  for(int i = 0; i < SINK_ROWS; i++)
//  {
//    setPinOutputPushPull(klm_sink_lines[i]);
//    writePinHigh(klm_sink_lines[i]);
//  }
//#endif
//  
//  for(int i = 0; i < MATRIX_COLS; i++)
//  {

//    GPIO_Init(PAL_PORT(col_pins[i]), (1 << PAL_PAD(col_pins[i])), GPIO_OTYPE_PP |GPIO_PUPD_UP |GPIO_SPEED_HIGH);


//#ifdef LED_MATRIX 
//    
//    PCT_PORT(pct_ccr_addr[i])->CFGR = PCT_DIV;
//    PCT_PORT(pct_ccr_addr[i])->CFGR2 = PCT_CFGR2_OPM;
//    
//    PCT_PORT(pct_ccr_addr[i])->ARRL = (PCT_ARR);
//    PCT_PORT(pct_ccr_addr[i])->ARRH = (PCT_ARR) >> 8;
//    PCT_PORT(pct_ccr_addr[i])->CCMR0 = 0x00;
//    PCT_PORT(pct_ccr_addr[i])->CCMR1 = 0x00;
//    PCT_PORT(pct_ccr_addr[i])->CCMR2 = 0x00;
//    PCT_PORT(pct_ccr_addr[i])->CCMR3 = 0x00;
//    PCT_PORT(pct_ccr_addr[i])->CCMR4 = 0x00;
//    PCT_PORT(pct_ccr_addr[i])->CCMR5 = 0x00;
//#endif
//  }
//#ifndef LED_MATRIX 
//  
//  PCT0->CFGR = PCT_DIV;
//  PCT0->CFGR2 = PCT_CFGR2_OPM;
//  PCT0->ARRL = (PCT_ARR);
//  PCT0->ARRH = (PCT_ARR) >> 8;
//  PCT0->CCMR0 = 0x00;
//  PCT0->CCMR1 = 0x00;
//  PCT0->CCMR2 = 0x00;
//  PCT0->CCMR3 = 0x00;
//  PCT0->CCMR4 = 0x00;
//  PCT0->CCMR5 = 0x00;
//  
//#endif
//  
//  PCT0->CFGR |= PCT_CFGR_OVFIE;

//  NVIC_SetPriority(PCT0_IRQn, 1);
//  NVIC_EnableIRQ(PCT0_IRQn);
//}

//static volatile uint32_t sink_scan_index = 0;
//static volatile uint32_t sink_line_active = 0;

//static volatile uint32_t r_scan_index = 0;


//void KeyLed_Start(void)
//{
//  PCT0->CSR |= PCT_CSR_CEN;
//}


//extern matrix_row_t curr_matrix[MATRIX_ROWS];
//extern void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
//// 在复用模式下，GPIO可以读取IO的输入状态，所以在此中断函数中没有切换C lines的配置。
//// 也是为了防止在中断函数中修改GPIO配置，因为中断函数中修改GPIO配置会打断程序其他地方的GPIO配置修改会引发问题。
//void PCT0_IRQHandler(void)
//{
//  if (PCT0->CSR & PCT_CSR_OVF)
//  {
//    PCT0->CSR &= ~PCT_CSR_OVF;

//    if (sink_line_active == 0)
//    {

//      matrix_read_cols_on_row(curr_matrix, r_scan_index);

//      setPinInputHigh(row_pins[r_scan_index]);
//      
//      r_scan_index = (r_scan_index + 1) % MATRIX_ROWS;

//      // Inactive R line
//      
//      PCT0->ARRL = (PCT_ARR);
//      PCT0->ARRH = (PCT_ARR) >> 8;
//      
//#ifdef LED_MATRIX 
//      for(uint8_t i = 0; i < MATRIX_COLS; i++) {
//        *(uint32_t *)(pct_ccr_addr[i]) = led_play_phase[sink_scan_index][i];
//      }

//      
//      PCT0->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR3 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR4 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR5 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;

//      PCT1->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT1->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT1->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT1->CCMR3 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT1->CCMR4 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT1->CCMR5 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;

//      PCT2->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT2->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT2->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT2->CCMR3 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT2->CCMR4 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT2->CCMR5 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;

//      PCT3->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT3->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT3->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT3->CCMR3 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;

//      PCT4->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT4->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT4->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      
//      // Active Sink line
//      writePinLow(klm_sink_lines[sink_scan_index]);
//      
//      PCT1->CSR |= PCT_CSR_CEN;
//      PCT2->CSR |= PCT_CSR_CEN;
//      PCT3->CSR |= PCT_CSR_CEN;
//      PCT4->CSR |= PCT_CSR_CEN;
//#else 
//      PCT0->CCMR0 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR1 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR2 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR3 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR4 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//      PCT0->CCMR5 = PCT_CCMR_ECOM | PCT_CCMR_PWM | PCT_CCMR_POL;
//#endif
//      setPinOutput(row_pins[r_scan_index]);
//      writePinLow(row_pins[r_scan_index]);
//      sink_line_active = 1;
//    }
//    else
//    {
//      sink_line_active = 0;
//#ifdef LED_MATRIX 
//      // Inactive Sink line
//      writePinHigh(klm_sink_lines[sink_scan_index]);
//      sink_scan_index = (sink_scan_index + 1) % MATRIX_ROWS;
//      
//      PCT0->CCMR0 = 0x00;
//      PCT0->CCMR1 = 0x00;
//      PCT0->CCMR2 = 0x00;
//      PCT0->CCMR3 = 0x00;
//      PCT0->CCMR4 = 0x00;
//      PCT0->CCMR5 = 0x00;

//      PCT2->CCMR0 = 0x00;
//      PCT2->CCMR1 = 0x00;
//      PCT2->CCMR2 = 0x00;
//      PCT2->CCMR3 = 0x00;
//      PCT2->CCMR4 = 0x00;
//      PCT2->CCMR5 = 0x00;
//      
//      PCT1->CCMR0 = 0x00;
//      PCT1->CCMR1 = 0x00;
//      PCT1->CCMR2 = 0x00;
//      PCT1->CCMR3 = 0x00;
//      PCT1->CCMR4 = 0x00;
//      PCT1->CCMR5 = 0x00;
//      
//      PCT3->CCMR0 = 0x00;
//      PCT3->CCMR1 = 0x00;
//      PCT3->CCMR2 = 0x00;
//      PCT3->CCMR3 = 0x00;
//      
//      PCT4->CCMR0 = 0x00;
//      PCT4->CCMR1 = 0x00;
//      PCT4->CCMR2 = 0x00;
//      
//#endif

//      PCT0->ARRL = (10-1);
//      PCT0->ARRH = (10-1) >> 8;
//    }
//    PCT0->CSR |= PCT_CSR_CEN;
//  }
//}

