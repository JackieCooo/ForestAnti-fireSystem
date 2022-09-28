#include "usart/usart.h"

/**
  * @brief ���ڳ�ʼ��
  * @param None
  * @retval None
  */
void USART_Init(void)
{
	rcu_periph_clock_enable(USART0_RCU_CLK);  // ��ʼ������0ʱ��
	rcu_periph_clock_enable(USART0_RCU_PIN_CLK);  // ��ʼ������0 GPIOʱ��
	
	gpio_init(USART0_PIN_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, USART0_TX_PIN);  // ��ʼ�����͹ܽ�
	gpio_init(USART0_PIN_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, USART0_RX_PIN);  // ��ʼ�����չܽ�
	
	usart_baudrate_set(USART0, USART0_BAUDRATE);  // ������115200
	usart_parity_config(USART0, USART_PM_NONE);  // ��У��
	usart_word_length_set(USART0, USART_WL_8BIT);  // 8λ����
	usart_stop_bit_set(USART0, USART_STB_1BIT);  // 1λֹͣλ
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);  // ʹ�ܴ��ڷ���
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);  // ʹ�ܴ��ڽ���
	usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);  // �ر�Ӳ������
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
	usart_enable(USART0);  // ʹ��USART0
}

/**
  * @brief ����һ���ֽ�
  * @param pUSARTx ���ں�
  * @param ch ���͵��ַ�
  * @retval None
  */
void UART_SendByte(uint32_t pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	usart_data_transmit(pUSARTx, ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (usart_flag_get(pUSARTx, USART_FLAG_TBE) == RESET);	
}

/**
  * @brief ����һ���ַ���
  * @param pUSARTx ���ں�
  * @param str ���͵��ַ���
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

	/* �ȴ�������� */
	while (usart_flag_get(pUSARTx, USART_FLAG_TBE) == RESET);
}

/**
  * @brief �ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
  * @param ch ���͵��ַ�
  * @param f �ļ�����
  * @retval ���ط��͵��ַ�
  */
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		usart_data_transmit(USART0, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET);
	
		return (ch);
}

/**
  * @brief �ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
  * @param f �ļ�����
  * @retval ���ؽ��յ��ַ�
  */
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (usart_flag_get(USART0, USART_FLAG_RBNE) == RESET);

		return (int)usart_data_receive(USART0);
}
