
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "wangyonglin/wifi.h"
#include "cJSON.h"
#include <wangyonglin/wifi.h>
#include <wangyonglin/flash.h>

static const char *TAG = "wifi sta";
const int SCAN_DONE_BIT = BIT0; //定义事件，占用事件变量的第0位，最多可以定义32个事件。

static void scan_task(void *pvParameters)
{
    struct wang_handle *handle = (struct wang_handle *)pvParameters;
    cJSON *root = NULL;
    cJSON *items = NULL;
    esp_err_t err;
    ESP_LOGI(TAG, "准备扫描");
    while (1)
    {
        root = cJSON_CreateArray();
        xEventGroupWaitBits(handle->wifi_event_group, SCAN_DONE_BIT, 0, 1, portMAX_DELAY);
        ESP_LOGI(TAG, "开始扫描");
        xEventGroupClearBits(handle->wifi_event_group, SCAN_DONE_BIT);
        uint16_t apCount = 0;
        esp_wifi_scan_get_ap_num(&apCount);
        ESP_LOGI(TAG, "Number of access points found: %d\n", apCount);

        if (apCount != 0)
        {
            wifi_ap_record_t *list = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * apCount);
            if ((err = esp_wifi_scan_get_ap_records(&apCount, list)) == ESP_OK)
            {
                for (int i = 0; i < apCount; i++)
                {
                    cJSON_AddItemToArray(root, (items = cJSON_CreateObject()));
                    cJSON_AddStringToObject(items, "ssid", (char *)list[i].ssid);
                    cJSON_AddNumberToObject(items, "rssi", list[i].rssi);
                    cJSON_AddNumberToObject(items, "authmode", list[i].authmode);
                }
            }
            char *out = cJSON_Print(root);
            ESP_LOGI(TAG,out);
            
             handle->startup(WANG_AP_START,handle,out,strlen(out));
            free(out);
            free(list);
        }
        else
        {
            ESP_LOGI(TAG, "Nothing AP found");
        }
        cJSON_Delete(root);
        root = NULL;
        ESP_LOGI(TAG, "结束扫描");
    }
}

esp_err_t wang_sta_scan(struct wang_handle *handle)
{
    esp_err_t err = ESP_OK;
    xTaskCreate(&scan_task, "scan_task", 2048, handle, 10, NULL); //创建扫描任务
    return err;
}

void wang_station_json(uint16_t count, wifi_ap_record_t *list)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *obj;
    for (int i = 0; i < count; i++)
    {
        ESP_LOGI(TAG, "%s %d", (char *)list[i].ssid, list[i].rssi);
        cJSON_AddItemToArray(root, obj = cJSON_CreateObject());
        cJSON_AddStringToObject(obj, "ssid", (char *)list[i].ssid);
        cJSON_AddNumberToObject(obj, "rssi", list[i].rssi);
        cJSON_AddNumberToObject(obj, "authmode", list[i].authmode);
    }
    char *out = cJSON_Print(root);
    ESP_LOGI(TAG, out);
}