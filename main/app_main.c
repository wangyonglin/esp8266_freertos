/**
 * @file app_main.c
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月10日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
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
#include <app.h>
static const char *TAG = "main";
void sta_ok(int id, void *ctx)
{
    ESP_LOGI(TAG, "sta_ok");
     mqtt_app_start();
}
void sta_fail(int id, void *ctx)
{
    ESP_LOGI(TAG, "sta_fail");
}
void app_main()
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wang_button_bit();
    wang_sta_ok(sta_ok, NULL);
    wang_sta_fail(sta_fail, NULL);
    initialise_wifi();
}
