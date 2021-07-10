#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include <wangyonglin/wifi.h>
static const char *TAG = "wifi softAP";
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
    char *out = wang_ap_default();
    ESP_LOGE(TAG, out);
    memcpy( cfg.ap.ssid,out,strlen(out));
    cfg.ap.ssid_len=strlen(out);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &cfg));
    if (esp_wifi_get_state() == WIFI_STATE_START)
    {
        ESP_ERROR_CHECK(esp_wifi_stop());
    }
    ESP_ERROR_CHECK(esp_wifi_start());
    return err;
}

char *wang_ap_default(void)
{
    char *out = (char *)malloc(sizeof(char) * 32);
    bzero(out, sizeof(char) * 32);
    uint32_t id;
    get_chip_id(&id);
    sprintf(out, "ESP%04X", id);
    return out;
}