/**
  ******************************************************************************
  * @file    main.c 
  * @author  Jackie
  * @version V1.0
  * @date    2022-09-22
  * @brief   GD32 FreeRTOS 模板
  ******************************************************************************
  */

#include "gd32f10x.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "usart/usart.h"
#include "ec_01f/ec_01f.h"

static void LEDTask(void* args);
static void AppInitTask(void* args);

int main(void)
{
	BaseType_t xReturn = pdPASS;

	/* 创建初始化任务 */
	xReturn = xTaskCreate(AppInitTask, "AppInitTask", 1024, NULL, 5, NULL);
	/* 启动任务调度 */           
	if(pdPASS == xReturn)
		vTaskStartScheduler();   /* 启动任务，开启调度 */
	else
		return -1;  

	while(1);   /* 正常不会执行到这里 */
}

static void LEDTask(void* args)
{
	uint8_t sck = 0;
	
	EC01F_DetectDevice();
	
	EC01F_EnableTCPService(&sck);
	printf("Socket ID: %d", sck);
	
    for(;;)
    {
    }
}

static void AppInitTask(void* args)
{
	taskENTER_CRITICAL();  // 进入临界段
	/*
	 * STM32中断优先级分组为4，即4bit都用来表示抢占优先级，范围为：0~15
	 * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	 * 都统一用这个优先级分组，千万不要再分组，切忌。
	 */
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	
	/* 初始化串口 */
	USART_Init();
	/* 初始化EC-01F模块 */
	EC01F_Init();

	xTaskCreate(LEDTask, "LEDTask", 512, NULL, 5, NULL);
	
	taskEXIT_CRITICAL();  // 退出临界段
	
	vTaskDelete(NULL);  // 删除该任务
}
