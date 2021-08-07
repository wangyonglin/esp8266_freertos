#include <espify.h>
#include <libify.h>
#include <configify.h>
#include <uartify.h>
#include <timerify.h>
#include <queueify.h>
#include <flashify.h>
static const char *TAG = "config";
esp_err_t objPacksInit(Configify_t *config);
esp_err_t objSystemInit(void);
esp_err_t objUartInit(Configify_t *config, uart_port_t uart_port, int uart_baud_rate);
esp_err_t objSystemInit(void)
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
    return ret;
}

esp_err_t ConfigifyInit(Configify_t *config)
{
    objSystemInit();
    config->wifi_event_group = xEventGroupCreate();
    ConfigifyIdInit(config);
    objTimerInit(config);
    objWifiInit(config);
    objWifiAPInit(config);
    objWifiSTAInit(config);
    objBootGet(config);
    objPacksInit(config);
    ConfigifyUartInit(config, UART_NUM_0, 9600);
    return ESP_OK;
}
esp_err_t objWifiAPInit(Configify_t *config)
{
    bzero(&config->wifi_config_ap, sizeof(wifi_config_t));
    config->wifi_config_ap.ap.authmode = WIFI_AUTH_OPEN;
    config->wifi_config_ap.ap.max_connection = 5;
    size_t len = strlen((char *)config->only_id);
    memcpy(config->wifi_config_ap.ap.ssid, config->only_id, len);
    config->wifi_config_ap.ap.ssid_len = len;
    return ESP_OK;
}
esp_err_t objWifiSTAInit(Configify_t *config)
{
    return objFlashWifiGet(&config->wifi_config_sta);
}
esp_err_t objWifiSTAGet(Configify_t *config)
{
    return objFlashWifiGet(&config->wifi_config_sta);
}
esp_err_t objWifiSTASet(Configify_t *config)
{
    return objFlashWifiSet(&config->wifi_config_sta);
}
esp_err_t objWifiInit(Configify_t *config)
{
    return ESP_OK;
}
esp_err_t objWifiScanInit(Configify_t *config)
{
    config->wifi_scan_config.ssid = NULL;
    config->wifi_scan_config.bssid = NULL;
    config->wifi_scan_config.channel = 0;
    config->wifi_scan_config.show_hidden = 0;
    return ESP_OK;
}

esp_err_t objBootGet(Configify_t *config)
{
    if (FlashifyBootGet() == 0)
    {
        config->bits = pdFALSE;
    }
    else
    {
        config->bits = pdTRUE;
    }
    return ESP_OK;
}
esp_err_t objBootSet(Configify_t *config, BaseType_t base)
{
    if (base == pdTRUE)
    {
        if (FlashifyBootSet(1) == ESP_OK)
        {
            config->bits = pdTRUE;
        }
    }
    else
    {
        if (FlashifyBootSet(0) == ESP_OK)
        {
            config->bits = pdFALSE;
        }
    }

    return ESP_OK;
}
esp_err_t objPacksInit(Configify_t *config)
{
    config->rf433_size = (sizeof(config->rf433) / sizeof(config->rf433[0]));
    objFlashRF433PacksGetting(config);
    for (int i = 0; i < config->rf433_size; i++)
    {
        ESP_LOGI(TAG, "RF433[%d] 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", i, config->rf433[i].h, config->rf433[i].a, config->rf433[i].b, config->rf433[i].k, config->rf433[i].o, config->rf433[i].f);
    }
    return ESP_OK;
}
esp_err_t ConfigifyUartInit(Configify_t *config, uart_port_t uart_port, int uart_baud_rate)
{
    config->uart.port = uart_port;
    config->uart.config.baud_rate = uart_baud_rate;
    config->uart.config.data_bits = UART_DATA_8_BITS;
    config->uart.config.parity = UART_PARITY_DISABLE;
    config->uart.config.stop_bits = UART_STOP_BITS_1;
    config->uart.config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    objUartStart(config);
    return ESP_OK;
}

esp_err_t objTimerInit(Configify_t *config)
{
    config->timer_control_message.bit = pdFALSE;
    config->timer_control_message.timeout_us = 1 * 1000 * 1000;
    config->timer_control_clieck.bit = pdFALSE;
    config->timer_control_clieck.timeout_us = 3 * 1000 * 1000;
    return esp_timer_init();
}
esp_err_t ConfigifyIdInit(Configify_t *config)
{
    config->only_id=StringifyMalloc(16);
    uint32_t id;
    get_chip_id(&id);
    StringifyFormat(config->only_id, "ESP%04X", id);
    ESP_LOGI(TAG,(char*)config->only_id);
    return ESP_OK;
}