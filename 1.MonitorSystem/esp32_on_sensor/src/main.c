#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "nvs_flash.h"

#include "wifi_app.h"
#include "tcp_client_app.h"

const static char *TAG = "App";

static void app_init_task(void *args) {
    while (true) {
        //Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
        wifi_init_sta();

        xTaskCreate(tcp_client_init_task, "tcp_client_task", 4096, NULL, 5, NULL);

        break;
    }

    vTaskDelete(NULL);
    
}

void app_main() {
    xTaskCreate(app_init_task, "app_init_task", 4096, NULL, 5, NULL);
}