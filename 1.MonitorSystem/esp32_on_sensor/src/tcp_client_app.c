#include "tcp_client_app.h"

static const char *TAG = "TCP Client";
static const uint8_t payload[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x11};

/* TCP服务器信息绑定 */
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

    err = send(sensor_data_socket, payload, sizeof(payload), 0);
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
        upload_sensor_data();

        vTaskDelay(2000 / portTICK_RATE_MS);
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
