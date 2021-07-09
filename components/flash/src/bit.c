
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi_types.h"
#include "wangyonglin/flash.h"
#include "wangyonglin/wifi.h"
#include <cJSON.h>
static const char *TAG = "FLASH-BIT";

int16_t wang_flash_bit_get(void)
{
    nvs_handle handle;
    int16_t out;
    esp_err_t err;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return -1;
    }
    if ((err = nvs_get_i16(handle, "BIT", &out)) == ESP_ERR_NVS_NOT_FOUND)
    {
        if ((err = nvs_set_i16(handle, "BIT", 0)) != ESP_OK)
        {
            ESP_ERROR_CHECK(err);
            nvs_close(handle);
            return -1;
        }
        if ((err = nvs_commit(handle)) != ESP_OK)
        {
            ESP_ERROR_CHECK(err);
            nvs_close(handle);
            return -1;
        }
    }

    nvs_close(handle);
    return out;
}

esp_err_t wang_flash_bit_set(int16_t val)
{
    nvs_handle handle;
    esp_err_t err = ESP_OK;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return err;
    }

    if ((err = nvs_set_i16(handle, "BIT", val)) != ESP_OK)
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