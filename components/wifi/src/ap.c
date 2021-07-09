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

static wifi_config_t wifi_config = {
    .ap = {
        .ssid = "wang",
        .ssid_len = strlen("wang"),
        .max_connection = 3,
        .authmode = WIFI_AUTH_OPEN,
    }};
esp_err_t wang_ap_start(struct wang_handle *handle)
{
    esp_err_t err = ESP_OK;
  
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    if (esp_wifi_get_state() == WIFI_STATE_START)
    {
        ESP_ERROR_CHECK(esp_wifi_stop());
    }

    ESP_ERROR_CHECK(esp_wifi_start());
    return err;
}