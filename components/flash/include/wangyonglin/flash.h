/**
 *@file esp8266_freertos/components/flash/include/wangyonglin/flash.h
 *@author: 王永林 (admin@wangyonglin.com)
 *@brief
 *@version 1
 *@date: 2021-07-08
 *@copyright Copyright (c) 2021
 */
#ifndef WANGYONGLIN_FLASH_H
#define WANGYONGLIN_FLASH_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wifi.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objFlashWifiSet(wifi_config_t *cfg);
    esp_err_t objFlashWifiGet(wifi_config_t *cfg);

    int16_t objFlashBootGet(void);
    esp_err_t objFlashBootSet(int16_t val);
#ifdef __cplusplus
}
#endif
#endif