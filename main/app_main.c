/*
 * @Author: your name
 * @Date: 2021-07-08 06:18:59
 * @LastEditTime: 2021-07-08 12:18:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /github/esp8266_freertos/main/app_main.c
 */
/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <wangyonglin/httpd.h>
#include <wangyonglin/wifi.h>
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "string.h"
#include <wangyonglin/button.h>
#include <esp_log.h>
static const char *TAG = "main";
void button_handler(int8_t id, void *ctx)
{
    if (id == 2)
    {
        ESP_LOGI(TAG, "长长长");
    }
}
void app_main()
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    wang_button_set(button_handler);
    initialise_wifi();
}
