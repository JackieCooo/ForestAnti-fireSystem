#include "uart_app.h"

const static char* TAG = "Uart";

data_t data;  // 串口接收数据
QueueHandle_t is_data_received = NULL;  // 二值信号量，用于通知TCP客户端开始发送数据

static QueueHandle_t uart_queue;

static bool check_data_valid() {
    
}

static void uart_event_task(void *args) {
    uart_event_t event;
    while (true) {
        //Waiting for UART event.
        if (xQueueReceive(uart_queue, (void *)&event, (TickType_t)portMAX_DELAY)) {
            bzero(data.data, BUF_SIZE);
            ESP_LOGI(TAG, "uart[%d] event:", UART_PORT);
            switch(event.type) {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
                case UART_DATA:
                    ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                    data.size = event.size;
                    uart_read_bytes(UART_PORT, data.data, event.size, portMAX_DELAY);
                    // 检查数据包格式合法性
                    if (check_data_valid()) {
                        xSemaphoreGive(is_data_received);  // 通知TCP客户端开始发送
                    }
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_PORT);
                    xQueueReset(uart_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    // If buffer full happened, you should consider encreasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_PORT);
                    xQueueReset(uart_queue);
                    break;
                //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    ESP_LOGI(TAG, "uart pattern detected");
                    break;
                //Others
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }

    vTaskDelete(NULL);
}

void uart_init_task(void *args) {
    while (true) {
        uart_config_t uart_config = {
            .baud_rate = 115200,  // 波特率115200
            .data_bits = UART_DATA_8_BITS,  // 8位数据位
            .parity = UART_PARITY_DISABLE,  // 无校检
            .stop_bits = UART_STOP_BITS_1,  // 1位停止位
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,  // 无硬件流控
            .source_clk = UART_SCLK_APB,  // APB时钟
        };

        ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 20, &uart_queue, 0));
        ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_PORT, UART_TX_PIN, UART_RX_PIN, -1, -1));
        uart_pattern_queue_reset(UART_PORT, 20);

        is_data_received = xSemaphoreCreateBinary();

        xTaskCreate(uart_event_task, "uart_event_task", 4096, NULL, 5, NULL);

        break;
    }
    
    vTaskDelete(NULL);
}
