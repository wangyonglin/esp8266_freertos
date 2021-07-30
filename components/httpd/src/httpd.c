#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>

const char *TAG = "httpd";

void start_webserver(objConfig_t *config)
{

    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    cfg.max_resp_headers=1024;
    cfg.send_wait_timeout = 8;
    cfg.recv_wait_timeout = 8;
    ESP_LOGI(TAG, "Starting server on port: '%d'", cfg.server_port);
    if (httpd_start(&config->httpd, &cfg) == ESP_OK)
    {
        objHttpdRegisterUriPromiseMinJs(config);
        objHttpdRegisterUriIndexCss(config);
        objHttpdRegisterUriIndexHtml(config);
        objHttpdRegisterUriInfoHtml(config);
        objHttpdRegisterUriWifiHtml(config);
        return;
    }
    ESP_LOGI(TAG, "Error starting server!");
    return;
}
void stop_webserver(objConfig_t *config)
{
    // Stop the httpd server
    objHttpdUnRegisterUriPromiseMinJs(config);
    objHttpdUnRegisterUriIndexCss(config);
    objHttpdUnRegisterUriIndexHtml(config);
    objHttpdUnRegisterUriInfoHtml(config);
    objHttpdUnRegisterUriWifiHtml(config);
    httpd_stop(config->httpd);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    objConfig_t *config = (objConfig_t *)arg;
    if (config->httpd)
    {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(config);
        config->httpd = NULL;
    }
}

static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data)
{
    objConfig_t *config = (objConfig_t *)arg;
    if (config->httpd == NULL)
    {
        ESP_LOGI(TAG, "Starting webserver");
        start_webserver(config);
    }
}

esp_err_t objHttpdStart(objConfig_t *config)
{
    ESP_LOGI(TAG, "httpd start");
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, config));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, config));

    start_webserver(config);
    return ESP_OK;
}
esp_err_t objHttpdStop(objConfig_t *config)
{

    ESP_LOGI(TAG, "https stop");
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler));
    stop_webserver(config);
    return ESP_OK;
}