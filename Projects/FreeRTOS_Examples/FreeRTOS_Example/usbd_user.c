#include "mono.h"
#include "usbd_user.h"
#include "usbd_hid.h"
#include "usbd_user_hid.h"


/**
 * @brief  Initializes the USB Device.
 * @return None
 */
void USBD_User_Init(void)
{
  /* Enable USB peripheral clock */
  RCC->APBENR |= RCC_APBENR_USBEN;

  /* Reset USB peripheral */
  RCC->APBRSTR |= RCC_APBRSTR_USBRST;
  RCC->APBRSTR &= ~RCC_APBRSTR_USBRST;

  /* Configure and enable USBCLK */
  RCC->USBCLKSRC = RCC_USBCLKSRC_HSI48;
  RCC->PLL2USBPRE2 = RCC_PLL2USBPRE2_SRCEN;

  USB->INTRUSBE = 0x00;
  USB->INTRINE = 0x00;
  USB->INTROUTE = 0x00;

  NVIC_SetPriority(USB_IRQn, 0);
  NVIC_EnableIRQ(USB_IRQn);
}

/**
 * @brief  Deinitializes the USB Device.
 * @return None
 */
void USBD_User_DeInit(void)
{
  /* Disable USB interrupt channel */
  NVIC_DisableIRQ(USB_IRQn);

  /* Disable USBCLK */
  RCC->PLL2USBPRE2 = 0x00;
  RCC->USBCLKSRC = RCC_USBCLKSRC_NONE;

  /* Disable USB peripheral clock */
  RCC->APBENR &= ~RCC_APBENR_USBEN;
}

/**
 * @brief  Connects the device to the USB host.
 * @return None
 */
void USBD_User_Connect(void)
{
  RCC->APBENR |= RCC_APBENR_GPIOEN;
  GPIO_Init(GPIOD, GPIO_Pin_1 |GPIO_Pin_2, GPIO_MODE_AF | GPIO_AF1);

  USB->POWER = USB_POWER_SUSEN;
  USB->INTRUSBE = USB_INTRUSBE_RSTIE | USB_INTRUSBE_RSUIE | USB_INTRUSBE_SUSIE;
}

/**
 * @brief  Disconnects the device from the USB host.
 * @return None
 */
void USBD_User_Disconnect(void)
{
}

/**
 * @brief  USB Reset Event Service Routine.
 * @return None
 */
void USBD_User_Reset(void)
{
  USB->POWER = USB_POWER_SUSEN;
  USB->INTRINE = USB_INTRINE_EP0E;
  USB->INTROUTE = 0x00;

  hid_ep2_in_xfer_flag = 0;
  hid_ep1_in_xfer_flag = 0;
}

/**
 * @brief  USB Resume Event Service Routine.
 * @return None
 */
void USBD_User_Resume(void)
{
//  GPIO_ResetBits(GPIOB, GPIO_Pin_13);   // Turn on LED2
}

/**
 * @brief  USB Suspend Event Service Routine.
 * @return None
 */
void USBD_User_Suspend(void)
{
//  GPIO_SetBits(GPIOB, GPIO_Pin_13);     // Turn off LED2
}

/**
 * @brief  USB SOF Event Service Routine.
 * @return None
 */
void USBD_User_SOF(void)
{
}


/**
 * @brief  Configures device.
 * @param  cfgidx: the configuration index.
 * @return true - Success, false - Error
 */
bool USBD_User_SetConfig(uint8_t cfgidx)
{
  if (cfgidx == 1)
  {
    // Configure IN Endpoint 1 (Interrupt)
    USB->INDEX = 0x01;
    USB->INCSR2 = 0x00;
    USB->INMAXP = (64 >> 3);
    USB->INCSR1 = USB_INCSR1_CLRDATATOG;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INTRINE |= (0x01 << 1);

    // Configure IN Endpoint 2 (Interrupt)
    USB->INDEX = 0x02;
    USB->INCSR2 = 0x00;
    USB->INMAXP = (64 >> 3);
    USB->INCSR1 = USB_INCSR1_CLRDATATOG;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INTRINE |= (0x01 << 2);

    // Configure IN Endpoint 3 (Interrupt)
    USB->INDEX = 0x03;
    USB->INCSR2 = 0x00;
    USB->INMAXP = (64 >> 3);
    USB->INCSR1 = USB_INCSR1_CLRDATATOG;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INCSR1 = USB_INCSR1_FLUSHFIFO;
    USB->INTRINE |= (0x01 << 3);

    // Configure OUT Endpoint 3 (Interrupt)
    USB->INDEX = 0x03;
    USB->OUTCSR2 = 0x00;
    USB->OUTMAXP = (64 >> 3);
    USB->OUTCSR1 = USB_OUTCSR1_CLRDATATOG;
    USB->OUTCSR1 = USB_OUTCSR1_FLUSHFIFO;
    USB->OUTCSR1 = USB_OUTCSR1_FLUSHFIFO;
    USB->INTROUTE |= (0x01 << 3);

    return true;
  }

  return false;
}

/**
 * @brief  Clear current configuration.
 * @param  cfgidx: the configuration index.
 * @note   If cfgidx is 0, this function should clear all configuration.
 * @return None
 */
void USBD_User_ClearConfig(uint8_t cfgidx)
{
  USB->INTRINE &= ~(0x01 << 1);
  USB->INTRINE &= ~(0x01 << 2);
  USB->INTRINE &= ~(0x01 << 3);
  USB->INTROUTE &= ~(0x01 << 3);
}


/**
 * @brief  Handle the setup device requests (Except the recipient is device).
 * @return The next control stage.
 */
UsbdControlStage USBD_User_EndPoint0_Setup(void)
{
  UsbdControlStage next_stage = USBD_CONTROL_STAGE_STALL;

  if ((UsbdCoreInfo.SetupPacket.bmRequestType & USB_REQUEST_RECIPIENT_Msk) == USB_REQUEST_RECIPIENT_INTERFACE)
  {
    if ((UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_KEYBOARD_IF_NUM) || 
        (UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_MIXED_IF_NUM) || 
        (UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_VENDOR_DEFINED_IF_NUM)) {
      next_stage = USBD_EndPoint0_Setup_HID_Req();
    }
  }

  return next_stage;
}

/**
 * @brief  Handle the out device requests.
 * @return The next control stage.
 */
UsbdControlStage USBD_User_EndPoint0_Out(void)
{
  UsbdControlStage next_stage = USBD_CONTROL_STAGE_STALL;

  if ((UsbdCoreInfo.SetupPacket.bmRequestType & (USB_REQUEST_TYPE_Msk | USB_REQUEST_RECIPIENT_Msk)) == 
      (USB_REQUEST_TYPE_CLASS | USB_REQUEST_RECIPIENT_INTERFACE))
  {
    if ((UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_KEYBOARD_IF_NUM) || 
        (UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_MIXED_IF_NUM) || 
        (UsbdCoreInfo.SetupPacket.wIndexL == USBD_HID_VENDOR_DEFINED_IF_NUM)) {
      next_stage = USBD_EndPoint0_Out_HID_Req();
    }
  }

  return next_stage;
}



/**
 * @brief  IN Endpoint 1 Service Routine.
 * @return None
 */
void USBD_User_EP1_IN(void)
{
  hid_ep1_in_xfer_flag = 0;
}

/**
 * @brief  IN Endpoint 2 Service Routine.
 * @return None
 */
void USBD_User_EP2_IN(void)
{
  hid_ep2_in_xfer_flag = 0;
}

/**
 * @brief  IN Endpoint 3 Service Routine.
 * @return None
 */
void USBD_User_EP3_IN(void)
{
}

/**
 * @brief  IN Endpoint 4 Service Routine.
 * @return None
 */
void USBD_User_EP4_IN(void)
{
}

/**
 * @brief  OUT Endpoint 1 Service Routine.
 * @return None
 */
void USBD_User_EP1_OUT(void)
{
}

/**
 * @brief  OUT Endpoint 2 Service Routine.
 * @return None
 */
void USBD_User_EP2_OUT(void)
{
}

/**
 * @brief  OUT Endpoint 3 Service Routine.
 * @return None
 */
void USBD_User_EP3_OUT(void)
{
}

/**
 * @brief  OUT Endpoint 4 Service Routine.
 * @return None
 */
void USBD_User_EP4_OUT(void)
{
}
