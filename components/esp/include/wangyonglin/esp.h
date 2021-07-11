#ifndef WANGYONGLIN_SYSTEM_ESP_H
#define WANGYONGLIN_SYSTEM_ESP_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/param.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "mqtt_client.h"
#include <esp_http_server.h>
#include <wangyonglin/io.h>

#ifdef __cplusplus
extern "C"
{
#endif

    char *objChipId(void);
    void objSystemInit(void);
#ifdef __cplusplus
}
#endif
#endif