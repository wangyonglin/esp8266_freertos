#ifndef __ESPIFY_H
#define __ESPIFY_H
#include <libify.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/param.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>
#include <esp_system.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_event.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <esp_wifi.h>
#include <lwip/err.h>
#include <lwip/sys.h>
#include <lwip/sockets.h>
#include <lwip/dns.h>
#include <lwip/netdb.h>
#include <esp_ota_ops.h>
#include <esp_http_client.h>
#include <esp_https_ota.h>
#include <esp_http_server.h>
#include <driver/uart.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include <freertos/portmacro.h>
#include <cJSON.h>

#ifdef __cplusplus
extern "C"
{
#endif


    typedef enum
    {
        ROUTE_WIFI_READY = 0,
        ROUTE_SCAN_DONE,
        ROUTE_STA_START,
        ROUTE_STA_STOP,
        ROUTE_STA_CONNECTED,
        ROUTE_STA_DISCONNECTED,
        ROUTE_STA_GOT_IP,
        ROUTE_AP_START,
        ROUTE_AP_STOP,
        ROUTE_AP_STACONNECTED,
        ROUTE_AP_STADISCONNECTED,
        ROUTE_AP_STAIPASSIGNED,
        ROUTE_AP_PROBEREQRECVED,
    } objRouteId_t;

    typedef struct objRF433Pack objRF433Pack_t;
    typedef struct Timerify Timerify_t;
    typedef struct Uartify Uartify_t;

    typedef struct Configify Configify_t;
    struct Timerify
    {
        esp_timer_handle_t handler;
        int timeout_us;
        BaseType_t bit;
    };
    struct Uartify
    {
        uart_port_t port;
        uart_config_t config;
    };
    struct objRF433Pack
    {
        Integerify_t i;
        Stringify_t h;
        Stringify_t a;
        Stringify_t b;
        Stringify_t k;
        Stringify_t o;
        Stringify_t f;
    };
#ifdef __cplusplus
}
#endif
#endif