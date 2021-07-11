
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
#include <wangyonglin/wifi.h>
#include <wangyonglin/httpd.h>
#include "cJSON.h"
#include <wangyonglin/flash.h>
static const char *TAG = "WIFI";

const int WIFI_CONNECTED_BIT = BIT1;
struct wang_handle handle;
void wang_wifi_init(struct wang_handle *handle);
char *buffer = NULL;
void startup_callback(wang_startup_id_t id, struct wang_handle *handle, void *ctx, size_t len)
{
    switch (id)
    {
    case WANG_STA_CONNECT:
        ESP_LOGI(TAG, "WANG_STA_CONNECT");
        ESP_ERROR_CHECK(esp_wifi_connect());
        break;
    case WANG_STA_SCAN_START:
        ESP_LOGI(TAG, "WANG_STA_SCAN_START");
        ESP_ERROR_CHECK(esp_wifi_scan_start(handle->config, 1));
        break;
    case WANG_STA_SCAN_STOP:
        ESP_LOGI(TAG, "WANG_STA_SCAN_STOP");
        break;
    case WANG_STA_START:
        ESP_LOGI(TAG, "WANG_STA_START");
        ESP_ERROR_CHECK(esp_wifi_start());
        break;
    case WANG_AP_HTTPD_START:
        ESP_LOGI(TAG, "WANG_AP_HTTPD_START");
        wang_httpd_start(handle, buffer);
        break;
    case WANG_AP_START:
        ESP_LOGI(TAG, "WANG_AP_HTTPD_START");
        buffer = (char *)malloc(sizeof(char) * len);
        memcpy(buffer, ctx, len);
        wang_ap_start(handle);
        break;
    case WANG_STA_GOT_IP:
        ESP_LOGI(TAG, "WANG_STA_GOT_IP");
        break;
    default:
        break;
    }
}

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    struct wang_handle *handle = (struct wang_handle *)ctx;
    system_event_info_t *info = &event->event_info;
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        ESP_LOGI(TAG, "路由已启动");
        if (objFlashBootGet() == 1)
        {
            handle->startup(WANG_STA_CONNECT, handle, NULL, 0);
        }
        else
        {
            handle->startup(WANG_STA_SCAN_START, handle, NULL, 0);
        }
        //esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "路由IP已分配");
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(handle->wifi_event_group, WIFI_CONNECTED_BIT);
        handle->startup(WANG_STA_GOT_IP, handle, NULL, 0);
        break;
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "启动热点");
        handle->startup(WANG_AP_HTTPD_START, handle, NULL, 0);
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "停止热点");
        break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        ESP_LOGI(TAG, "接收热点");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "路由");
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:

        ESP_LOGI(TAG, "station:" MACSTR "leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "路由断网");
        esp_wifi_connect();
        //xEventGroupClearBits(config.wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        ESP_LOGI(TAG, "扫描完毕");
        xEventGroupSetBits(handle->wifi_event_group, BIT0);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void initialise_wifi(void)
{
    wifi_config_t cfg;
    wang_wifi_init(&handle);
    handle.startup = startup_callback;
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    if (objFlashWifiGet(&cfg) == ESP_OK)
    {
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg));
    }
    ESP_ERROR_CHECK(esp_wifi_start());
    wang_sta_scan(&handle);
}
static wifi_scan_config_t config = {
    .ssid = NULL,
    .bssid = NULL,
    .channel = 0,
    .show_hidden = 0,
};
void wang_wifi_init(struct wang_handle *handle)
{

    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    handle->config = &config;
    handle->wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, handle));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
}
