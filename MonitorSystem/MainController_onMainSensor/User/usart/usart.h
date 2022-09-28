#ifndef _USART_H_
#define _USART_H_

#include "gd32f10x.h"
#include <stdio.h>

/* 串口0管脚定义 */
#define USART0_PIN_PORT GPIOA
#define USART0_RX_PIN GPIO_PIN_10
#define USART0_TX_PIN GPIO_PIN_9
#define USART0_RCU_CLK RCU_USART0
#define USART0_RCU_PIN_CLK RCU_GPIOA
#define USART0_BAUDRATE 115200

void USART_Init(void);

#endif
