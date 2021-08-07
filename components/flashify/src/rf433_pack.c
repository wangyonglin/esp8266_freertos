
#include <espify.h>
#include <configify.h>

static const char *TAG = "rf433_pack";
static const char *NAMESPACE = "RF433_PACK";

esp_err_t objFlashRF433PacksGetting(Configify_t *config)
{
    nvs_handle handle;
    size_t len = sizeof(objRF433Pack_t)*config->rf433_size;
    esp_err_t err = ESP_OK;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return err;
    }
    if ((err = nvs_get_blob(handle, NAMESPACE, config->rf433, &len)) == ESP_ERR_NVS_NOT_FOUND)
    {
        bzero(config->rf433,sizeof(config->rf433));
        if ((err = nvs_set_blob(handle, NAMESPACE, config->rf433, sizeof(objRF433Pack_t)*config->rf433_size)) != ESP_OK)
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

esp_err_t objFlashRF433PacksSaveing(Configify_t *config)
{
    nvs_handle handle;
    esp_err_t err = ESP_OK;
    if ((err = nvs_open(TAG, NVS_READWRITE, &handle)) != ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        return err;
    }

    if ((err = nvs_set_blob(handle, NAMESPACE, config->rf433, sizeof(objRF433Pack_t)*config->rf433_size)) != ESP_OK)
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
