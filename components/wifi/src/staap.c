#include <wangyonglin/wangyonglin.h>
#include <wangyonglin/esp.h>
static const char *TAG = "APSTA";

typedef struct objWifiHandle
{
    EventGroupHandle_t wifi_event_group;
    EventBits_t wifi_connected_bit : BIT1;
    EventBits_t wifi_scan_bit : BIT2;
} objWifiHandle_t;

objWifiHandle_t wifi_handle_t;

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
    objWifiHandle_t *wifi_handle_t = (objWifiHandle_t *)ctx;
    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
        ESP_LOGI(TAG, "路由已启动");
        if (objFlashBootGet() == 1)
        {
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "路由IP已分配");
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_handle_t->wifi_event_group, wifi_handle_t->wifi_connected_bit);
       
        break;
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "启动热点");
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "停止热点");
        break;
    case SYSTEM_EVENT_WIFI_READY:
        ESP_LOGI(TAG, "SYSTEM_EVENT_WIFI_READY");
        break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        ESP_LOGI(TAG, "接收热点");
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "连接AP成功");

        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "连接AP关闭");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "路由断网");
        if (objFlashBootGet() == 1)
        {
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        //xEventGroupClearBits(config.wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        ESP_LOGI(TAG, "扫描完毕");
        xEventGroupSetBits(wifi_handle_t->wifi_event_group, BIT2);
        break;
    default:
        ESP_LOGI(TAG, "default[%d]", event->event_id);
        break;
    }
    return ESP_OK;
}
esp_err_t obj_wifi_apsta_start()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    wifi_handle_t.wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, &wifi_handle_t));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(obj_wifi_adapter_init());
    wifi_config_t cfg;
    ESP_ERROR_CHECK(obj_wifi_get_parameters(ESP_IF_WIFI_STA, &cfg));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg));
    ESP_ERROR_CHECK(obj_wifi_get_parameters(ESP_IF_WIFI_AP, &cfg));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &cfg));

    return ESP_OK;
}
esp_err_t obj_wifi_sta_start()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    tcpip_adapter_init();
    wifi_handle_t.wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, &wifi_handle_t));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    wifi_config_t cfg;
    ESP_ERROR_CHECK(obj_wifi_get_parameters(ESP_IF_WIFI_STA, &cfg));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &cfg));
    return ESP_OK;
}