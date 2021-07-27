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
    esp_err_t objWifiStart(objConfig_t *config,objWifiCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif