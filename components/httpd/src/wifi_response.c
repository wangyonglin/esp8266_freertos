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

esp_err_t wifi_json(httpd_req_t *req)
{
    cJSON *root = cJSON_CreateObject();
    httpd_resp_set_type(req, "application/json; charset=utf-8");
    if (req->user_ctx != NULL)
    {
        cJSON_AddStringToObject(root, "message", "ok");
        cJSON_AddNumberToObject(root, "code", 200);
        cJSON *wifi = cJSON_Parse(req->user_ctx);
        cJSON_AddItemToObject(root, "wifi", wifi);
    }else{
        cJSON_AddStringToObject(root, "message", "fail");
        cJSON_AddNumberToObject(root, "code", 500);
        cJSON_AddItemToObject(root, "wifi", cJSON_CreateNull());
    }
    char *out = cJSON_Print(root);
    httpd_resp_send(req, out, strlen(out));
    free(out);
    cJSON_Delete(root);
    return ESP_OK;
}

void wang_httpd_wifi_json(wang_httpd_t *httpd, const char *uri, void *ctx)
{
    httpd_uri_t uri_t = {
        .uri = uri,
        .method = HTTP_GET,
        .handler = wifi_json,
        .user_ctx = ctx,
    };
    httpd_register_uri_handler(httpd->handle, &uri_t);
}