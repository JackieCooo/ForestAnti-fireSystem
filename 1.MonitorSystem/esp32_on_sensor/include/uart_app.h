#ifndef _UART_APP_H
#define _UART_APP_H

#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_PORT UART_NUM_1
#define UART_RX_PIN 16
#define UART_TX_PIN 17

#endif