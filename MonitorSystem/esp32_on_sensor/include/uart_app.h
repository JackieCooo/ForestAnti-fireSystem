#ifndef _UART_APP_H
#define _UART_APP_H

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "driver/uart.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#define UART_PORT UART_NUM_1
#define UART_RX_PIN 18
#define UART_TX_PIN 19
#define BUF_SIZE (256)

typedef struct Data {
    uint8_t data[BUF_SIZE];
    uint8_t size;
} data_t;

extern data_t data;
extern QueueHandle_t is_data_received;

void uart_init_task(void *args);

#endif
