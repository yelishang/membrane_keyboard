#pragma once
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "matrix.h"
#include "config.h"

#include "timer.h"
#include "keycode.h"
#include "keyprocess.h"

extern volatile SemaphoreHandle_t xMutexUsb;

extern volatile QueueHandle_t xQueueAppEventMsg;
// USB 任务句柄声明
extern TaskHandle_t USBTask_Handler;
extern TaskHandle_t APPTask_Handler;
