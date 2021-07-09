/*
 * @Author: your name
 * @Date: 2021-07-08 06:41:24
 * @LastEditTime: 2021-07-08 08:10:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /github/esp8266_freertos/components/flash/src/flash.c
 */
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi_types.h"
#include "wangyonglin/flash.h"
#include "wangyonglin/wifi.h"
#include <cJSON.h>
static const char *TAG = "FLASH-AP";
