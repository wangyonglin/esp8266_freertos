#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <esp_http_server.h>
#include <wangyonglin/httpd.h>
#include <wangyonglin/flash.h>
#include <cJSON.h>
static const char *TAG = "wifi.html";

cJSON *root = NULL;
esp_err_t wifi_html(httpd_req_t *req)
{
    wifi_scan_config_t cfg;
    obj_wifi_scan_parameters(&cfg);
    esp_wifi_scan_start(&cfg, 0);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    esp_err_t err;
    httpd_resp_set_type(req, "application/json; charset=utf-8");
    root = cJSON_CreateObject();
    cJSON *wifi = NULL;
    cJSON *items = NULL;
    uint16_t apCount = 0;
    err = esp_wifi_scan_get_ap_num(&apCount);
    if (apCount != 0)
    {
        wifi_ap_record_t *list = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * apCount);
        if ((err = esp_wifi_scan_get_ap_records(&apCount, list)) == ESP_OK)
        {
            cJSON_AddStringToObject(root, "message", "ok");
            cJSON_AddNumberToObject(root, "code", 200);
            cJSON_AddItemToObject(root, "wifi", wifi = cJSON_CreateArray());
            for (int i = 0; i < apCount; i++)
            {
                if (strcmp((char*)list[i].ssid,"")!=0)
                {
                    cJSON_AddItemToArray(wifi, (items = cJSON_CreateObject()));
                    cJSON_AddStringToObject(items, "ssid", (char *)list[i].ssid);
                    cJSON_AddNumberToObject(items, "rssi", list[i].rssi);
                    cJSON_AddNumberToObject(items, "authmode", list[i].authmode);
                }
            }
            char *out = cJSON_Print(root);
            httpd_resp_send(req, out, strlen(out));
            printf(out);
            //free(out);
        }
        free(list);
    }
    else
    {
        ESP_LOGI(TAG, "Nothing AP found");
        cJSON_AddStringToObject(root, "message", "fail");
        cJSON_AddNumberToObject(root, "code", 500);
        cJSON_AddItemToObject(root, "wifi", cJSON_CreateNull());
        char *out = cJSON_Print(root);
        httpd_resp_send(req, out, strlen(out));
        printf(out);
        //free(out);
    }
    ESP_LOGI(TAG, "结束扫描");
    esp_wifi_scan_stop();
    cJSON_Delete(root);
    root = NULL;
    return err;
}

void obj_httpd_wifi_html(obj_httpd_t *httpd, const char *uri, void *ctx)
{
    httpd_uri_t uri_t = {
        .uri = uri,
        .method = HTTP_GET,
        .handler = wifi_html,
        .user_ctx = ctx,
    };
    httpd_register_uri_handler(httpd->handle, &uri_t);
}