#include "task_usb.h"
#include "usbd_core.h"
#include "usbd_user_hid.h"
#include "main.h"

extern volatile uint32_t reset_flag;
static volatile uint32_t ulUsbInterruptFlags = 0;

void USB_IRQHandler(void) {
  uint8_t IntrUSB;
  uint8_t IntrIn;
  uint8_t IntrOut;

  IntrUSB = USB->INTRUSB;
  IntrIn  = USB->INTRIN;
  IntrOut = USB->INTROUT;

  Handle_USBD_INT(IntrUSB, IntrIn, IntrOut);
}
