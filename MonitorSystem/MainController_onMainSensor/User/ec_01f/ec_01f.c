#include "ec_01f/ec_01f.h"

struct STRUCT_USARTx_Fram strUSART_Fram_Record = {0};
xQueueHandle receiveDone = NULL;  // ��ֵ�ź�����������ʾ���ڽ������

static uint8_t EC01F_GetSocketID(void);

void EC01F_Init(void)
{
	/* ��ʼ��GPIO */
	rcu_periph_clock_enable(EC01F_USART_GPIO_RCU);
	gpio_init(EC01F_USART_GPIO_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, EC01F_USART_TX_PIN);
	gpio_init(EC01F_USART_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, EC01F_USART_RX_PIN);
	
	/* ��ʼ��DMA */
	rcu_periph_clock_enable(EC01F_USART_DMA_RCU);
	
	/* ��ʼ��USART */
	rcu_periph_clock_enable(EC01F_USART_RCU);
	usart_baudrate_set(EC01F_USARTx, EC01F_USART_BAUDRATE);  // ������115200
	usart_parity_config(EC01F_USARTx, USART_PM_NONE);  // ��У��
	usart_word_length_set(EC01F_USARTx, USART_WL_8BIT);  // 8λ����
	usart_stop_bit_set(EC01F_USARTx, USART_STB_1BIT);  // 1λֹͣλ
	usart_transmit_config(EC01F_USARTx, USART_TRANSMIT_ENABLE);  // ʹ�ܴ��ڷ���
	usart_receive_config(EC01F_USARTx, USART_RECEIVE_ENABLE);  // ʹ�ܴ��ڽ���
	usart_hardware_flow_rts_config(EC01F_USARTx, USART_RTS_DISABLE);  // �ر�Ӳ������
    usart_hardware_flow_cts_config(EC01F_USARTx, USART_CTS_DISABLE);
	usart_interrupt_enable(EC01F_USARTx, USART_INT_RBNE);  // ʹ�ܴ��ڽ����ж�
	usart_interrupt_enable(EC01F_USARTx, USART_INT_IDLE);  // ʹ�ܴ��ڿ����ж�
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	nvic_irq_enable(USART1_IRQn, 1, 0);  // ��ռ���ȼ�Ϊ1
	
	usart_enable(EC01F_USARTx);  // ʹ�ܴ���
	usart_dma_transmit_config(EC01F_USARTx, USART_DENT_ENABLE);  // ʹ�ܴ���DMA����
	
	receiveDone = xQueueCreate(1, 0);
}

void EC01F_UsartSend(char* str)
{
	dma_parameter_struct dma_struct = {0};
	
	dma_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  // �ڴ浽����
	dma_struct.memory_addr = (uint32_t)str;  // �ڴ����ַ
	dma_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;  // ʹ���ڴ��ַ����
	dma_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;  // 8λ�ڴ����ݿ��
	dma_struct.number = strlen(str);  // ��������
	dma_struct.periph_addr = (uint32_t)0x40004404;  // �������ַ
	dma_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  // �ر��������ַ����
	dma_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;  // 8λ�������ݿ��
	dma_struct.priority = DMA_PRIORITY_HIGH;  // �����ȼ�
	
	dma_init(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, &dma_struct);  // ʹ��DMA
	dma_circulation_disable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // �ر�DMAѭ��ģʽ
	dma_flag_clear(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, DMA_FLAG_FTF);  // ���������ɱ�־λ
	dma_channel_enable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // ʹ��DMA����
	
	while(dma_flag_get(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, DMA_FLAG_FTF) == RESET);  // �ȴ��������
	dma_channel_disable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // �ر�DMA����
}

bool EC01F_Cmd(char* cmd, char* reply1, char* reply2, uint32_t waittime)
{
	EC01F_UsartSend(cmd);  // ��������
	xQueueReceive(receiveDone, NULL, (TickType_t)waittime);  // �ȴ�������Ӧ
	strUSART_Fram_Record.len = 0;
	
	// �ж���Ӧ�Ƿ�����
	if (reply1 != NULL && reply2 != NULL)
	{
		return (bool)strstr(strUSART_Fram_Record.Data_RX_BUF, reply1) || (bool)strstr(strUSART_Fram_Record.Data_RX_BUF, reply2);
	}
	else if(reply1 != NULL)
	{
		return (bool)strstr(strUSART_Fram_Record.Data_RX_BUF, reply1);
	}
	else if(reply2 != NULL)
	{
		return (bool)strstr(strUSART_Fram_Record.Data_RX_BUF, reply2);
	}

	return true;
}

void EC01F_DetectDevice(void)
{
	bool detected = false;
	for(; !detected;)
	{
		printf("Detecting device...\n");
		detected = EC01F_Cmd("AT\r\n", "OK", NULL, (TickType_t)5000);
	}
	printf("Device Detected\n");
}

void EC01F_EnableTCPService(uint8_t* id)
{
	EC01F_Cmd("AT+ECICCID\r\n", "OK", NULL, (TickType_t)5000);
	printf("SIM card detected\n");
	
	EC01F_Cmd("AT+CGATT=1\r\n", "OK", NULL, (TickType_t)10000);
	printf("PS domin attached\n");
	
	EC01F_Cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n", "OK", NULL, (TickType_t)5000);
	printf("APNID registered\n");
	
	EC01F_Cmd("AT+CGACT=1\r\n", "OK", NULL, (TickType_t)5000);
	printf("Network activated\n");
	
	EC01F_Cmd("AT+SKTCREATE=1,1,6\r\n", "OK", NULL, (TickType_t)5000);
	*id = EC01F_GetSocketID();
	printf("Socket created\n");
}

static uint8_t EC01F_GetSocketID(void)
{
	for(uint8_t i = 0; strUSART_Fram_Record.Data_RX_BUF[i] != '\0'; ++i)
	{
		if(isdigit(strUSART_Fram_Record.Data_RX_BUF[i])) return strUSART_Fram_Record.Data_RX_BUF[i] - '0';
	}
	return 10;
}
