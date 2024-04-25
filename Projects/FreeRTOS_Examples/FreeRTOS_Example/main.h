#pragma once
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "usbd_core.h"
#include "usbd_user_hid.h"

#include "matrix.h"
#include "config.h"

#include "semphr.h"
#include "timer.h"
#include "task_usb.h"
#include "task_app.h"
#include "keycode.h"

#include "drv_key_led.h"

#include "keyprocess.h"

#include "eeconfig.h"
extern volatile SemaphoreHandle_t xMutexUsb;

extern volatile QueueHandle_t xQueueAppEventMsg;
// USB 任务句柄声明
extern TaskHandle_t USBTask_Handler;
extern TaskHandle_t APPTask_Handler;
