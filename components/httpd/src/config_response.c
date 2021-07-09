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
static const char *TAG = "HTTPD:RESPONSE->";

esp_err_t config_json(httpd_req_t *req)
{

    char content[100];

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
    cJSON *root = cJSON_CreateObject();
    wifi_config_t cfg;
    bzero(&cfg, sizeof(wifi_config_t));
    httpd_query_key_value(content, "ssid", (char *)cfg.sta.ssid, sizeof(cfg.ap.ssid));
    httpd_query_key_value(content, "passwd", (char *)cfg.sta.password, sizeof(cfg.ap.password));
    if (wang_flash_wifi_set(&cfg) == ESP_OK)
    {
        if (wang_flash_bit_set(1) == ESP_OK)
        {
            cJSON_AddNumberToObject(root, "code", 200);
            cJSON_AddStringToObject(root, "message", "配置成功,请重启!");
        }
        else
        {
            cJSON_AddNumberToObject(root, "code", 500);
            cJSON_AddStringToObject(root, "message", "配置失败");
        }
    }
    else
    {
        cJSON_AddNumberToObject(root, "code", 500);
        cJSON_AddStringToObject(root, "message", "配置失败");
    }

    char *out = cJSON_Print(root);
    httpd_resp_send(req, out, strlen(out));
    cJSON_Delete(root);
    free(out);
    return ESP_OK;
}
void wang_httpd_config_json(wang_httpd_t *httpd, const char *uri, void *ctx)
{
    httpd_uri_t uri_t = {
        .uri = uri,
        .method = HTTP_POST,
        .handler = config_json,
        .user_ctx = ctx,
    };
    httpd_register_uri_handler(httpd->handle, &uri_t);
}