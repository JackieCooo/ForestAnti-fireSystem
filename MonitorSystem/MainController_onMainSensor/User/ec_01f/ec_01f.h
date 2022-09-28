#ifndef _EC_01F_H
#define _EC_01F_H

#include "gd32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define EC01F_USARTx USART1
#define EC01F_USART_BAUDRATE 9600
#define EC01F_USART_RCU RCU_USART1
#define EC01F_USART_GPIO_RCU RCU_GPIOA
#define EC01F_USART_GPIO_PORT GPIOA
#define EC01F_USART_TX_PIN GPIO_PIN_2
#define EC01F_USART_RX_PIN GPIO_PIN_3
#define EC01F_USART_DMAx DMA0
#define EC01F_USART_DMA_RCU RCU_DMA0
#define EC01F_USART_DMA_CHL DMA_CH6

#define RX_BUF_MAX_LEN 1024  // 最大接收缓存字节数

struct STRUCT_USARTx_Fram  // 串口数据帧的处理结构体
{
	char Data_RX_BUF[RX_BUF_MAX_LEN];
	uint16_t len;
};
extern struct STRUCT_USARTx_Fram strUSART_Fram_Record;

extern xQueueHandle receiveDone;

void EC01F_Init(void);
void EC01F_UsartSend(char* str);
bool EC01F_Cmd(char* cmd, char* reply1, char* reply2, uint32_t waittime);
void EC01F_DetectDevice(void);
void EC01F_EnableTCPService(uint8_t* id);

#endif
