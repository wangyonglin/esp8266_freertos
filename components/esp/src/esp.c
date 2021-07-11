#include <wangyonglin/esp.h>

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
char *objChipId(void)
{
    char *out = (char *)malloc(sizeof(char) * 32);
    bzero(out, sizeof(char) * 32);
    uint32_t id;
    get_chip_id(&id);
    sprintf(out, "ESP%04X", id);
    return out;
}