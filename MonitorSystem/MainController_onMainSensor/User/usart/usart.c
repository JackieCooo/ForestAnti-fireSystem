#include "usart/usart.h"

/**
  * @brief 串口初始化
  * @param None
  * @retval None
  */
void USART_Init(void)
{
	rcu_periph_clock_enable(USART0_RCU_CLK);  // 初始化串口0时钟
	rcu_periph_clock_enable(USART0_RCU_PIN_CLK);  // 初始化串口0 GPIO时钟
	
	gpio_init(USART0_PIN_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, USART0_TX_PIN);  // 初始化发送管脚
	gpio_init(USART0_PIN_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, USART0_RX_PIN);  // 初始化接收管脚
	
	usart_baudrate_set(USART0, USART0_BAUDRATE);  // 波特率115200
	usart_parity_config(USART0, USART_PM_NONE);  // 无校检
	usart_word_length_set(USART0, USART_WL_8BIT);  // 8位数据
	usart_stop_bit_set(USART0, USART_STB_1BIT);  // 1位停止位
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);  // 使能串口发送
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);  // 使能串口接收
	usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);  // 关闭硬件流控
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
	usart_enable(USART0);  // 使能USART0
}

/**
  * @brief 发送一个字节
  * @param pUSARTx 串口号
  * @param ch 发送的字符
  * @retval None
  */
void UART_SendByte(uint32_t pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	usart_data_transmit(pUSARTx, ch);
		
	/* 等待发送数据寄存器为空 */
	while (usart_flag_get(pUSARTx, USART_FLAG_TBE) == RESET);	
}

/**
  * @brief 发送一个字符串
  * @param pUSARTx 串口号
  * @param str 发送的字符串
  * @retval None
  */
void Usart_SendString(uint32_t pUSARTx, char *str)
{
	uint16_t k = 0;
	do
	{
		UART_SendByte(pUSARTx, *(str + k));
		k++;
	} while(*(str + k) != '\0');

	/* 等待发送完成 */
	while (usart_flag_get(pUSARTx, USART_FLAG_TBE) == RESET);
}

/**
  * @brief 重定向c库函数printf到串口，重定向后可使用printf函数
  * @param ch 发送的字符
  * @param f 文件对象
  * @retval 返回发送的字符
  */
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		usart_data_transmit(USART0, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET);
	
		return (ch);
}

/**
  * @brief 重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
  * @param f 文件对象
  * @retval 返回接收的字符
  */
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (usart_flag_get(USART0, USART_FLAG_RBNE) == RESET);

		return (int)usart_data_receive(USART0);
}
