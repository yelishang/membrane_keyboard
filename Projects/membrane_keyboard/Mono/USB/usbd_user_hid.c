#include "main.h"
#include "usbd_core.h"
#include "usbd_user_hid.h"

uint8_t hid_customer_in_report_buf[USBD_HID_CONSUMER_IN_REPORT_SIZE] = {0};
uint8_t hid_system_in_report_buf[USBD_HID_SYSTEM_IN_REPORT_SIZE] = {0};
uint8_t hid_nkro_in_report_buf[USBD_HID_NKRO_IN_REPORT_SIZE] = {0};


volatile uint32_t reset_flag;
uint8_t hid_report_buf[64]    = {0};
uint8_t hid_in_report_buf[64] = {0};
uint8_t wl_led_old_control    = 0;
int hid_ep1_report_xfer_flag  = 1;
int hid_ep2_report_xfer_flag  = 1;
int hid_ep3_report_xfer_flag  = 1;


uint8_t hid_mouse_in_report_buf[USBD_HID_MOUSE_IN_REPORT_SIZE] = {0};
volatile int hid_ep2_in_xfer_flag = 0;

uint8_t hid_keyboard_in_report_buf[USBD_HID_KEYBOARD_IN_REPORT_SIZE] = {0};
volatile int hid_ep1_in_xfer_flag = 0;

bool USBD_User_HID_GetReport(void)
{
  if ((UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_MIXED_IF_NUM) &&
      (UsbdCoreInfo.SetupPacket.wValueH == HID_REPORT_INPUT) &&
      (UsbdCoreInfo.SetupPacket.wLength == USBD_HID_MOUSE_IN_REPORT_SIZE)) {
    UsbdCoreInfo.DataPtr = hid_mouse_in_report_buf;
    return true;
  }
  if ((UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_KEYBOARD_IF_NUM) &&
      (UsbdCoreInfo.SetupPacket.wValueH == HID_REPORT_INPUT) &&
      (UsbdCoreInfo.SetupPacket.wLength == USBD_HID_KEYBOARD_IN_REPORT_SIZE)) {
    UsbdCoreInfo.DataPtr = hid_keyboard_in_report_buf;
    return true;
  }

  return false;
}

uint8_t hid_keyboard_out_report_buf[1] = {0};
void indicator_light(uint8_t temp);
bool USBD_User_HID_SetReport(bool data_received)
{
  if ((UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_KEYBOARD_IF_NUM) &&
      (UsbdCoreInfo.SetupPacket.wValueH == HID_REPORT_OUTPUT) &&
      (UsbdCoreInfo.SetupPacket.wLength == 1))
  {
    if (data_received == false)
    {
      UsbdCoreInfo.DataPtr = &hid_keyboard_out_report_buf[0];
      return true;
    }
    else
    {
      indicator_light(hid_keyboard_out_report_buf[0]);
     return true;
    }
  }

  return false;
}


static uint8_t hid_duration = 0;

bool USBD_User_HID_GetIdle(void)
{
  UsbdCoreInfo.DataPtr = &hid_duration;
  return true;
}

bool USBD_User_HID_SetIdle(void)
{
  hid_duration = UsbdCoreInfo.SetupPacket.wValueH;
  return true;
}


// 0 - Boot Protocol
// 1 - Report Protocol
static uint8_t hid_data_protocol = 1;

bool USBD_User_HID_GetProtocol(void)
{
  UsbdCoreInfo.DataPtr = &hid_data_protocol;
  return true;
}

bool USBD_User_HID_SetProtocol(void)
{
  hid_data_protocol = UsbdCoreInfo.SetupPacket.wValueL;
  return true;
}
