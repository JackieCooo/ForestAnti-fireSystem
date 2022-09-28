#include "tcp_client_app.h"

static const char *TAG = "TCP Client";

/* TCP服务器地址绑定 */
static struct sockaddr_in sensor_data_server;

/* TCP套接字 */
static int sensor_data_socket;

static void upload_sensor_data() {
    int err = 0;

    sensor_data_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sensor_data_socket < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        close(sensor_data_socket);
        return;
    }
    ESP_LOGI(TAG, "Socket created, connecting to %s:%d", HOST_IP_ADDR, SENSOR_DATA_PORT);

    err = connect(sensor_data_socket, (struct sockaddr *)&sensor_data_server, sizeof(struct sockaddr_in6));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
        close(sensor_data_socket);
        return;
    }
    ESP_LOGI(TAG, "Successfully connected");

    err = send(sensor_data_socket, data.data, data.size, 0);
    if (err < 0) {
        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
        close(sensor_data_socket);
        return;
    }
    ESP_LOGI(TAG, "Successfully sent");

    close(sensor_data_socket);

}

static void tcp_client_task(void *args) {
    while (true) {
        // 查看是否接收到数据
        if (is_data_received != NULL && xSemaphoreTake(is_data_received, (TickType_t)20)) {
            upload_sensor_data();
        }
        
    }

    vTaskDelete(NULL);
    
}

void tcp_client_init_task(void *args) {
    while (true) {
        sensor_data_server.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        sensor_data_server.sin_family = AF_INET;
        sensor_data_server.sin_port = htons(SENSOR_DATA_PORT);

        xTaskCreate(tcp_client_task, "tcp_client_task", 4096, NULL, 5, NULL);

        break;
    }

    vTaskDelete(NULL);
}
