#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "wifi";
esp_err_t obj_wifi_get_parameters(wifi_interface_t interface, wifi_config_t *cfg)
{
    esp_err_t err = ESP_OK;
    bzero(cfg, sizeof(wifi_config_t));
    if (interface == ESP_IF_WIFI_AP)
    {
        cfg->ap.authmode = WIFI_AUTH_OPEN;
        cfg->ap.max_connection = 5;
        char *out = objChipId();
        ESP_LOGE(TAG, out);
        memcpy(cfg->ap.ssid, out, strlen(out));
        cfg->ap.ssid_len = strlen(out);
        return err;
    }
    else if (interface == ESP_IF_WIFI_STA)
    {
        if ((err = obj_flash_wifi_get(cfg)) == ESP_OK)
        {
            if ((err = esp_wifi_set_config(ESP_IF_WIFI_STA, cfg)) == ESP_OK)
            {
                return ESP_OK;
            }
            return err;
        }
        return ESP_ERR_INVALID_ARG;
    }
    return err;
}

esp_err_t obj_wifi_scan_parameters(wifi_scan_config_t *config)
{
    config->ssid = NULL;
    config->bssid = NULL;
    config->channel = 0;
    config->show_hidden = 0;
    return ESP_OK;
}