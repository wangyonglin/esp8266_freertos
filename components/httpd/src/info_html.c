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
static const char *TAG = "info.html";

esp_err_t info_html(httpd_req_t *req)
{
    char content[100] = {0};
    size_t recv_size = MIN(req->content_len, sizeof(content));
    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0)
    {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    wifi_config_t cfg;
    bzero(&cfg, sizeof(wifi_config_t));
    httpd_query_key_value(content, "ssid", (char *)cfg.sta.ssid, sizeof(cfg.sta.ssid));
    httpd_query_key_value(content, "passwd", (char *)cfg.sta.password, sizeof(cfg.sta.ssid));
    ESP_LOGE(TAG, "SSID[%s][%d]", (char *)cfg.sta.ssid, strlen((char *)cfg.sta.ssid));
    ESP_LOGE(TAG, "passwd[%s][%d]", (char *)cfg.sta.password, strlen((char *)cfg.sta.password));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg));
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    if ( objFlashBootSet(1) == 0)
    { 
        cJSON *root = cJSON_CreateObject();
        ESP_ERROR_CHECK(obj_flash_wifi_set(&cfg));
        cJSON_AddNumberToObject(root, "code", 200);
        cJSON_AddStringToObject(root, "message", "配置成功,3秒自动重启");
        char *out = cJSON_Print(root);
        httpd_resp_send(req, out, strlen(out));
        cJSON_Delete(root);
        free(out);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        esp_restart();
    }
   /*
    else if (objFlashBootGet() == 1)
    {
        cJSON *root = cJSON_CreateObject();
        cJSON_AddNumberToObject(root, "code", 500);
        cJSON_AddStringToObject(root, "message", "配置失败");
        char *out = cJSON_Print(root);
        httpd_resp_send(req, out, strlen(out));
        cJSON_Delete(root);
        free(out);
    }
    */
    return ESP_OK;
}
void obj_httpd_info_html(obj_httpd_t *httpd, const char *uri, void *ctx)
{
    httpd_uri_t uri_t = {
        .uri = uri,
        .method = HTTP_POST,
        .handler = info_html,
        .user_ctx = ctx,
    };
    httpd_register_uri_handler(httpd->handle, &uri_t);
}