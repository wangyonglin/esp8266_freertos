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

const char *TAG = "WANGYONGLIN:HTTPD->";
obj_httpd_t httpd;

void start_webserver(obj_httpd_t *httpd)
{

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&httpd->handle, &config) == ESP_OK)
    {
        ESP_LOGI(TAG, "Registering URI handlers");
        obj_httpd_index_html(httpd, "/");
        obj_httpd_wifi_html(httpd, "/wifi", NULL);
        obj_httpd_info_html(httpd, "/info", NULL);
        return;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return;
}
void stop_webserver(httpd_handle_t handle)
{
    // Stop the httpd server
    httpd_stop(handle);
}

static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    obj_httpd_t *httpd = (obj_httpd_t *)arg;
    if (httpd->handle)
    {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(httpd->handle);
        httpd->handle = NULL;
    }
}

static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data)
{
    obj_httpd_t *httpd = (obj_httpd_t *)arg;
    if (httpd->handle == NULL)
    {
        ESP_LOGI(TAG, "Starting webserver");
        start_webserver(httpd);
    }
}

void obj_httpd_start()
{
    ESP_LOGI(TAG, "obj_httpd_start");
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &httpd));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &httpd));
    start_webserver(&httpd);
}
void obj_httpd_stop()
{
    ESP_LOGI(TAG, "obj_httpd_stop");
    stop_webserver(&httpd);
}