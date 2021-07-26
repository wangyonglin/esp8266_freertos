#ifndef WANGYONGLIN_WIFI_H
#define WANGYONGLIN_WIFI_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_err.h"
#include "esp_wifi.h"

#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t obj_wifi_scan_parameters(wifi_scan_config_t *config);
    esp_err_t obj_wifi_get_parameters(wifi_interface_t interface, wifi_config_t *conf);
    esp_err_t obj_wifi_apsta_start();
    esp_err_t obj_wifi_sta_start();
#ifdef __cplusplus
}
#endif
#endif