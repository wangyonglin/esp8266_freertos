#ifndef WANGYONGLIN_SYSTEM_ESP_H
#define WANGYONGLIN_SYSTEM_ESP_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/param.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
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
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include <esp_http_server.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include <string.h>
#include <cJSON.h>
#include <wangyonglin/io.h>

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
    /*
    typedef unsigned char objPackData_t;
    typedef int objPackDataLenth_t;
    typedef unsigned int objPackSize_t;
    typedef unsigned char objPackAddr_t;
    typedef unsigned char objPackKey_t;
    typedef unsigned int objPackId_t;
    typedef struct
    {
        objPackAddr_t a;
        objPackAddr_t b;
        objPackKey_t k;
        objPackId_t i;
    } objPack_t;*/
    typedef unsigned char objRF433Header_t;
    typedef unsigned char objRF433Footer_t;
    typedef unsigned char objRF433Data_t;
    typedef int objRF433DataLength_t;
    typedef unsigned int objRF433Size_t;
    typedef unsigned char objRF433Addr_t;
    typedef unsigned char objRF433Key_t;
    typedef unsigned int objRF433Id_t;
    typedef unsigned char objRF433Oscillation_t;
    typedef struct
    {
        objRF433Id_t i;
        objRF433Header_t h;
        objRF433Addr_t a;
        objRF433Addr_t b;
        objRF433Key_t k;
        objRF433Oscillation_t o;
        objRF433Footer_t f;
    } objRF433Pack_t;

    typedef struct objConfig objConfig_t;
    typedef void (*objClickCallback_t)(objConfig_t *config, uint8_t event);
    typedef void (*objWifiCallback_t)(objConfig_t *config, objRouteId_t id);
    typedef void (*objMqttCallback_t)(objConfig_t *config, int level, uint8_t *data, int len);
    typedef struct
    {
        esp_timer_handle_t handler;
        int timeout_us;
        BaseType_t bit;
    } objTimer_t;
    struct objConfig
    {
        EventGroupHandle_t wifi_event_group;
        EventBits_t wifi_connected_bit : BIT1;
        EventBits_t wifi_scan_bit : BIT2;
        xQueueHandle xQueueMqtt;
        TickType_t ticks_to_wait;
        esp_mqtt_client_handle_t client;
        httpd_handle_t httpd;
        void *user_ctx;
        wifi_config_t wifi_config_sta;
        wifi_config_t wifi_config_ap;
        wifi_init_config_t wifi_init_config;
        wifi_scan_config_t wifi_scan_config;
        BaseType_t bits;
        objRouteId_t id;
        objClickCallback_t pfnClickCallback;
        objWifiCallback_t pfnWifiCallback;
        objMqttCallback_t pfnMqttCallback;
        objRF433Pack_t rf433[8];
        int rf433_size;
        uart_port_t uart_num;
        uart_config_t uart_config;
        objTimer_t timer_control_clieck;
        objTimer_t timer_control_message;
    };

    esp_err_t objConfigInit(objConfig_t *config);
    esp_err_t objWifiAPInit(objConfig_t *config);
    esp_err_t objWifiSTAInit(objConfig_t *config);
    esp_err_t objWifiInit(objConfig_t *config);
    esp_err_t objWifiSTAGet(objConfig_t *config);
    esp_err_t objWifiSTASet(objConfig_t *config);
    esp_err_t objWifiScanInit(objConfig_t *config);
    esp_err_t objBootGet(objConfig_t *config);
    esp_err_t objBootSet(objConfig_t *config, BaseType_t base);
    esp_err_t objUartInit(objConfig_t *config, uart_port_t uart_port, int uart_baud_rate);
    char *obj_chip_id(void);
    esp_err_t objTimerInit(objConfig_t *config);
#ifdef __cplusplus
}
#endif
#endif