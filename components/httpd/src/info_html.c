#include <espify.h>
#include <configify.h>
#include <wifiify.h>
#include <flashify.h>
static const char *TAG = "/info.html";
esp_err_t info_html(httpd_req_t *req)
{
    Configify_t *config = (Configify_t *)req->user_ctx;
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

    httpd_query_key_value(content, "ssid", (char *)config->wifi_config_sta.sta.ssid, sizeof(config->wifi_config_sta.sta.ssid));
    httpd_query_key_value(content, "passwd", (char *)config->wifi_config_sta.sta.password, sizeof(config->wifi_config_sta.sta.ssid));
    ESP_LOGE(TAG, "SSID[%s][%d]", (char *)config->wifi_config_sta.sta.ssid, strlen((char *)config->wifi_config_sta.sta.ssid));
    ESP_LOGE(TAG, "passwd[%s][%d]", (char *)config->wifi_config_sta.sta.password, strlen((char *)config->wifi_config_sta.sta.password));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &config->wifi_config_sta));
    //vTaskDelay(1000 / portTICK_PERIOD_MS);

    cJSON *root = cJSON_CreateObject();
    ESP_ERROR_CHECK(objWifiSTASet(config));
    FlashifyBootSet(pdTRUE);
    cJSON_AddNumberToObject(root, "code", 200);
    cJSON_AddStringToObject(root, "message", "配置成功,自动重启");
    char *out = cJSON_Print(root);
    httpd_resp_send(req, out, strlen(out));
    cJSON_Delete(root);
    free(out);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    esp_restart();

    return ESP_OK;
}

void objHttpdRegisterUriInfoHtml(Configify_t *config)
{
    httpd_uri_t uri_t = {
        .uri = TAG,
        .method = HTTP_POST,
        .handler = info_html,
        .user_ctx = config,
    };
    if (httpd_register_uri_handler(config->httpd, &uri_t) == ESP_OK)
    {
        ESP_LOGI(TAG, "successfully registering the uri%s", TAG);
    }
}

void objHttpdUnRegisterUriInfoHtml(Configify_t *config)
{
    if (httpd_unregister_uri_handler(config->httpd, TAG, HTTP_POST) == ESP_OK)
    {
        ESP_LOGI(TAG, "successfully deregistering the uri%s", TAG);
    }
}