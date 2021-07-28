#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "esp";

void objSystemInit(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}
char *obj_chip_id(void)
{
    char *out = (char *)malloc(sizeof(char) * 32);
    bzero(out, sizeof(char) * 32);
    uint32_t id;
    get_chip_id(&id);
    sprintf(out, "ESP%04X", id);
    return out;
}

esp_err_t objConfigInit(objConfig_t *config)
{
    config->wifi_event_group = xEventGroupCreate();
    objWifiInit(config);
    objWifiAPInit(config);
    objWifiSTAInit(config);
    objBootGet(config);

    return ESP_OK;
}
esp_err_t objWifiAPInit(objConfig_t *config)
{
    bzero(&config->wifi_config_ap, sizeof(wifi_config_t));
    config->wifi_config_ap.ap.authmode = WIFI_AUTH_OPEN;
    config->wifi_config_ap.ap.max_connection = 5;
    char *out = obj_chip_id();
    ESP_LOGE(TAG, out);
    memcpy(config->wifi_config_ap.ap.ssid, out, strlen(out));
    config->wifi_config_ap.ap.ssid_len = strlen(out);
    return ESP_OK;
}
esp_err_t objWifiSTAInit(objConfig_t *config)
{
    return objFlashWifiGet(&config->wifi_config_sta);
}
esp_err_t objWifiSTAGet(objConfig_t *config)
{
    return objFlashWifiGet(&config->wifi_config_sta);
}
esp_err_t objWifiSTASet(objConfig_t *config)
{
    return objFlashWifiSet(&config->wifi_config_sta);
}
esp_err_t objWifiInit(objConfig_t *config)
{
    return ESP_OK;
}
esp_err_t objWifiScanInit(objConfig_t *config)
{
    config->wifi_scan_config.ssid = NULL;
    config->wifi_scan_config.bssid = NULL;
    config->wifi_scan_config.channel = 0;
    config->wifi_scan_config.show_hidden = 0;
    return ESP_OK;
}

esp_err_t objBootGet(objConfig_t *config)
{
    if (objFlashBootGet() == 0)
    {
        config->bits = pdFALSE;
    }
    else
    {
        config->bits = pdTRUE;
    }
    return ESP_OK;
}
esp_err_t objBootSet(objConfig_t *config, BaseType_t base)
{
    if (base == pdTRUE)
    {
        if (objFlashBootSet(1) == ESP_OK)
        {
            config->bits = pdTRUE;
        }
    }
    else
    {
        if (objFlashBootSet(0) == ESP_OK)
        {
            config->bits = pdFALSE;
        }
    }

    return ESP_OK;
}