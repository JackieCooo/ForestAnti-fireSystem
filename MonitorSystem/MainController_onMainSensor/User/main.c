/**
  ******************************************************************************
  * @file    main.c 
  * @author  Jackie
  * @version V1.0
  * @date    2022-09-22
  * @brief   GD32 FreeRTOS ģ��
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

	/* ������ʼ������ */
	xReturn = xTaskCreate(AppInitTask, "AppInitTask", 1024, NULL, 5, NULL);
	/* ����������� */           
	if(pdPASS == xReturn)
		vTaskStartScheduler();   /* �������񣬿������� */
	else
		return -1;  

	while(1);   /* ��������ִ�е����� */
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
	taskENTER_CRITICAL();  // �����ٽ��
	/*
	 * STM32�ж����ȼ�����Ϊ4����4bit��������ʾ��ռ���ȼ�����ΧΪ��0~15
	 * ���ȼ�����ֻ��Ҫ����һ�μ��ɣ��Ժ������������������Ҫ�õ��жϣ�
	 * ��ͳһ��������ȼ����飬ǧ��Ҫ�ٷ��飬�мɡ�
	 */
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	
	/* ��ʼ������ */
	USART_Init();
	/* ��ʼ��EC-01Fģ�� */
	EC01F_Init();

	xTaskCreate(LEDTask, "LEDTask", 512, NULL, 5, NULL);
	
	taskEXIT_CRITICAL();  // �˳��ٽ��
	
	vTaskDelete(NULL);  // ɾ��������
}
