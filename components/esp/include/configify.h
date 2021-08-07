#ifndef __CONFIGIFY_H
#define __CONFIGIFY_H
#include <espify.h>
#include <rf433ify.h>
#include <uartify.h>
#include <timerify.h>
#include <mqtt_client.h>
typedef void (*ClickCallback_t)(Configify_t *config, Integerify_t event);
typedef void (*WifiCallback_t)(Configify_t *config, objRouteId_t id);
typedef void (*MqttCallback_t)(Configify_t *config, int level, Stringify_t *data, int len);
struct Configify
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
    ClickCallback_t pfnClickCallback;
    WifiCallback_t pfnWifiCallback;
    MqttCallback_t pfnMqttCallback;
    objRF433Pack_t rf433[8];
    int rf433_size;
    Uartify_t uart;
    Timerify_t timer_control_clieck;
    Timerify_t timer_control_message;
    Stringify_t *only_id;
};

#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t ConfigifyIdInit(Configify_t *config);
    esp_err_t ConfigifyInit(Configify_t *config);
    esp_err_t objWifiAPInit(Configify_t *config);
    esp_err_t objWifiSTAInit(Configify_t *config);
    esp_err_t objWifiInit(Configify_t *config);
    esp_err_t objWifiSTAGet(Configify_t *config);
    esp_err_t objWifiSTASet(Configify_t *config);
    esp_err_t objWifiScanInit(Configify_t *config);
    esp_err_t objBootGet(Configify_t *config);
    esp_err_t objBootSet(Configify_t *config, BaseType_t base);
    esp_err_t ConfigifyUartInit(Configify_t *config, uart_port_t uart_port, int uart_baud_rate);
    esp_err_t objTimerInit(Configify_t *config);
#ifdef __cplusplus
}
#endif
#endif