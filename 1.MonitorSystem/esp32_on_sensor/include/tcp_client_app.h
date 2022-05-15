#ifndef _TCP_CLIENT_APP_H
#define _TCP_CLIENT_APP_H

#include <string.h>
#include <sys/param.h>
#include <lwip/netdb.h>
#include <arpa/inet.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_err.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#define HOST_IP_ADDR "192.168.3.51"
#define SENSOR_DATA_PORT 20001

void tcp_client_init_task(void *args);

#endif