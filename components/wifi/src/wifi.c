#include <espify.h>
#include <configify.h>
static const char *TAG = "wifi";

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
    Configify_t *config = (Configify_t *)ctx;
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        ESP_LOGI(TAG, "route start");
        config->id = ROUTE_STA_START;
        if (config->bits == pdTRUE)
        {
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        config->id = ROUTE_STA_GOT_IP;
        ESP_LOGI(TAG, "route got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        //xEventGroupSetBits(config->wifi_event_group, config->wifi_connected_bit);
        config->pfnWifiCallback(config, ROUTE_STA_GOT_IP);
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        ESP_LOGI(TAG, "route connected");
        config->id = ROUTE_STA_CONNECTED;
        break;
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "ap start");
        config->id = ROUTE_AP_START;
        config->pfnWifiCallback(config, ROUTE_AP_START);
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "ap stop");
        config->id = ROUTE_AP_STOP;
        config->pfnWifiCallback(config, ROUTE_AP_STOP);
        break;
    case SYSTEM_EVENT_WIFI_READY:
        ESP_LOGI(TAG, "wifi ready");
        config->id = ROUTE_WIFI_READY;
        break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        ESP_LOGI(TAG, "ap recv");
        config->id = ROUTE_AP_PROBEREQRECVED;
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "soft route connected");
        config->id = ROUTE_AP_STACONNECTED;
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "soft route disconnected");
        config->id = ROUTE_AP_STADISCONNECTED;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "route disconnected");
        config->id = ROUTE_STA_DISCONNECTED;
        config->pfnWifiCallback(config, ROUTE_STA_DISCONNECTED);
        if (config->bits == pdTRUE)
        {
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        //xEventGroupClearBits(config.wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        ESP_LOGI(TAG, "route scan done");
        // xEventGroupSetBits(config->wifi_event_group, BIT2);
        config->id = ROUTE_SCAN_DONE;
        break;
    default:
        ESP_LOGI(TAG, "default[%d]", event->event_id);
        break;
    }
    return ESP_OK;
}

esp_err_t objWifiStart(Configify_t *config, WifiCallback_t cb)
{
    config->pfnWifiCallback = cb;
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    config->wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, config));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    if (config->bits == pdTRUE)
    {
        ESP_LOGI(TAG, "sta mode");
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_start());
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &config->wifi_config_sta));
    }
    else
    {
        ESP_LOGI(TAG, "apsta mode");
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
        ESP_ERROR_CHECK(esp_wifi_start());
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &config->wifi_config_sta));
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &config->wifi_config_ap));
    }

    return ESP_OK;
}