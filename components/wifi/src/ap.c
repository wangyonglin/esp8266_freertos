#include <wangyonglin/esp.h>
#include <wangyonglin/wifi.h>
#include <wangyonglin/adapter.h>
static const char *TAG = "wifi sta";
char *wang_ap_default(void);
static wifi_config_t cfg = {
    .ap.ssid = "wangyonglin",
    .ap.ssid_len = strlen("wangyonglin"),
    .ap.authmode = WIFI_AUTH_OPEN,
    .ap.max_connection = 3,
};
esp_err_t wang_ap_start(struct wang_handle *handle)
{
    esp_err_t err = ESP_OK;
    char *out = objChipId();
    ESP_LOGE(TAG, out);
    memcpy(cfg.ap.ssid, out, strlen(out));
    cfg.ap.ssid_len = strlen(out);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &cfg));
    if (esp_wifi_get_state() == WIFI_STATE_START)
    {
        ESP_ERROR_CHECK(esp_wifi_stop());
    }
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(objAdapterInit());
    return err;
}



