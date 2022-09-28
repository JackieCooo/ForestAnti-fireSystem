#include "ec_01f/ec_01f.h"

struct STRUCT_USARTx_Fram strUSART_Fram_Record = {0};
xQueueHandle receiveDone = NULL;  // 二值信号量，用于提示串口接收完成

static uint8_t EC01F_GetSocketID(void);

void EC01F_Init(void)
{
	/* 初始化GPIO */
	rcu_periph_clock_enable(EC01F_USART_GPIO_RCU);
	gpio_init(EC01F_USART_GPIO_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, EC01F_USART_TX_PIN);
	gpio_init(EC01F_USART_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, EC01F_USART_RX_PIN);
	
	/* 初始化DMA */
	rcu_periph_clock_enable(EC01F_USART_DMA_RCU);
	
	/* 初始化USART */
	rcu_periph_clock_enable(EC01F_USART_RCU);
	usart_baudrate_set(EC01F_USARTx, EC01F_USART_BAUDRATE);  // 波特率115200
	usart_parity_config(EC01F_USARTx, USART_PM_NONE);  // 无校检
	usart_word_length_set(EC01F_USARTx, USART_WL_8BIT);  // 8位数据
	usart_stop_bit_set(EC01F_USARTx, USART_STB_1BIT);  // 1位停止位
	usart_transmit_config(EC01F_USARTx, USART_TRANSMIT_ENABLE);  // 使能串口发送
	usart_receive_config(EC01F_USARTx, USART_RECEIVE_ENABLE);  // 使能串口接收
	usart_hardware_flow_rts_config(EC01F_USARTx, USART_RTS_DISABLE);  // 关闭硬件流控
    usart_hardware_flow_cts_config(EC01F_USARTx, USART_CTS_DISABLE);
	usart_interrupt_enable(EC01F_USARTx, USART_INT_RBNE);  // 使能串口接收中断
	usart_interrupt_enable(EC01F_USARTx, USART_INT_IDLE);  // 使能串口空闲中断
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	nvic_irq_enable(USART1_IRQn, 1, 0);  // 抢占优先级为1
	
	usart_enable(EC01F_USARTx);  // 使能串口
	usart_dma_transmit_config(EC01F_USARTx, USART_DENT_ENABLE);  // 使能串口DMA发送
	
	receiveDone = xQueueCreate(1, 0);
}

void EC01F_UsartSend(char* str)
{
	dma_parameter_struct dma_struct = {0};
	
	dma_struct.direction = DMA_MEMORY_TO_PERIPHERAL;  // 内存到外设
	dma_struct.memory_addr = (uint32_t)str;  // 内存基地址
	dma_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;  // 使能内存地址自增
	dma_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;  // 8位内存数据宽度
	dma_struct.number = strlen(str);  // 数据数量
	dma_struct.periph_addr = (uint32_t)0x40004404;  // 外设基地址
	dma_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;  // 关闭外设基地址自增
	dma_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;  // 8位外设数据宽度
	dma_struct.priority = DMA_PRIORITY_HIGH;  // 高优先级
	
	dma_init(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, &dma_struct);  // 使能DMA
	dma_circulation_disable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // 关闭DMA循环模式
	dma_flag_clear(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, DMA_FLAG_FTF);  // 清除传输完成标志位
	dma_channel_enable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // 使能DMA传输
	
	while(dma_flag_get(EC01F_USART_DMAx, EC01F_USART_DMA_CHL, DMA_FLAG_FTF) == RESET);  // 等待传输完成
	dma_channel_disable(EC01F_USART_DMAx, EC01F_USART_DMA_CHL);  // 关闭DMA传输
}

bool EC01F_Cmd(char* cmd, char* reply1, char* reply2, uint32_t waittime)
{
	EC01F_UsartSend(cmd);  // 发送命令
	xQueueReceive(receiveDone, NULL, (TickType_t)waittime);  // 等待命令响应
	strUSART_Fram_Record.len = 0;
	
	// 判断响应是否正常
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
