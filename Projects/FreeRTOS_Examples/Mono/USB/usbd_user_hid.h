/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_USER_HID_H
#define __USBD_USER_HID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "usb_hid_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USBD_HID_IF_NUM                     0
#define USBD_HID_KEYBOARD_INTERFACE_NUM     1
   
#define USBD_HID_FEATURE_REPORT_SIZE        64

#define USBD_HID_KEYBOARD_IF_NUM            0
#define USBD_HID_MIXED_IF_NUM               1
#define USBD_HID_VENDOR_DEFINED_IF_NUM      2

#define USBD_HID_KEYBOARD_IN_REPORT_SIZE    8
#define USBD_HID_NKRO_IN_REPORT_SIZE        16
#define USBD_HID_MOUSE_IN_REPORT_SIZE       8
#define USBD_HID_CONSUMER_IN_REPORT_SIZE    3

enum usbd_hid_report_ids
{
  USBD_REPORT_ID_MOUSE = 1,
  USBD_REPORT_ID_CONSUMER,
  USBD_REPORT_ID_SYSTEM,
  USBD_REPORT_ID_NKRO
};


extern uint8_t hid_keyboard_in_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE];
extern uint8_t hid_nkro_in_report_buf[USBD_HID_NKRO_IN_REPORT_SIZE];
extern uint8_t hid_customer_in_report_buf[USBD_HID_CONSUMER_IN_REPORT_SIZE];


extern uint8_t hid_mouse_in_report_buf[USBD_HID_MOUSE_IN_REPORT_SIZE];
extern volatile int hid_ep2_in_xfer_flag;

extern uint8_t hid_keyboard_in_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE];
extern volatile int hid_ep1_in_xfer_flag;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

bool USBD_User_HID_GetReport(void);
bool USBD_User_HID_SetReport(bool data_received);
bool USBD_User_HID_GetIdle(void);
bool USBD_User_HID_SetIdle(void);
bool USBD_User_HID_GetProtocol(void);
bool USBD_User_HID_SetProtocol(void);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_USER_HID_H */
