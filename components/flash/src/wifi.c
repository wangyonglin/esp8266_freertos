
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi_types.h"
#include "wangyonglin/flash.h"
#include "wangyonglin/wifi.h"
#include <cJSON.h>
static const char *TAG = "FLASH-WIFI";
static const char *NAMESPACE = "WIFIINFO";

esp_err_t wang_flash_wifi_get(wifi_config_t *cfg)
{
    nvs_handle handle;
    size_t len = sizeof(wifi_config_t);
    esp_err_t err = ESP_OK;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return err;
    }
    if ((err = nvs_get_blob(handle, NAMESPACE, cfg, &len)) == ESP_ERR_NVS_NOT_FOUND)
    {
        if ((err = nvs_set_blob(handle, NAMESPACE, cfg, sizeof(wifi_config_t))) != ESP_OK)
        {
            ESP_ERROR_CHECK(err);
            nvs_close(handle);
            return err;
        }
        if ((err = nvs_commit(handle)) != ESP_OK)
        {
            ESP_ERROR_CHECK(err);
            nvs_close(handle);
            return err;
        }
    }

    nvs_close(handle);
    return err;
}

esp_err_t wang_flash_wifi_set(wifi_config_t *cfg)
{
    nvs_handle handle;
    esp_err_t err = ESP_OK;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return err;
    }

    if ((err = nvs_set_blob(handle, NAMESPACE, cfg, sizeof(wifi_config_t))) != ESP_OK)
    {

        ESP_ERROR_CHECK(err);
        nvs_close(handle);
        return err;
    }
    if ((err = nvs_commit(handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        nvs_close(handle);
        return err;
    }
    nvs_close(handle);
    ESP_ERROR_CHECK(err);
    return err;
}
