#include <configify.h>
#include <espify.h>
#include <timerify.h>
#include <key.h>
#include <httpd.h>
#include <messageify.h>
#include <outify.h>
#include <queueify.h>
#include <flashify.h>
#include <wifiify.h>
#include <mqttify.h>

static const char *TAG = "main";
Configify_t config;
void objMqttCallback(Configify_t *config, int level, Stringify_t *data, int len)
{
    switch (level)
    {
    case EVENT_TRUN_LEVEL:
        if (strcmp((char *)data, "on") == 0)
        {
            ESP_LOGI(TAG, "trun on");
            OutifySetting(IO00, 1);
        }
        else if (strcmp((char *)data, "off") == 0)
        {
            ESP_LOGI(TAG, "trun off");
            OutifySetting(IO00, 0);
        }
        break;
    case EVENT_RF433_LEVEL:
        if (data)
        {
            ESP_LOGI(TAG, (char *)data);
        }
        break;
    default:
        break;
    }
}
void key_click_handler(Configify_t *config, Integerify_t event)
{
    switch (event)
    {
    case KEY_GPIO_S_PRESS_EVT:
        ESP_LOGI(TAG, "trigger clieck");
        OutifyTrigger(IO00);
        break;
    case KEY_GPIO_L_PRESS_EVT:
        ESP_LOGI(TAG, "long clieck");
        objTimerStart(config);
        break;
    case KEY_GPIO_LL_PRESS_EVT:
        ESP_LOGI(TAG, "overlong clieck");
        FlashifyBootSet(pdFALSE);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        esp_restart();
        break;
    default:
        break;
    }
}

void objWifiCallback(Configify_t *config, objRouteId_t id)
{
    switch (id)
    {
    case ROUTE_STA_GOT_IP:
        if (esp_mqtt_client_start(config->client) != ESP_OK)
        {
            vTaskDelay(3000 / portTICK_PERIOD_MS);
            esp_restart();
        }
        break;
    case ROUTE_STA_DISCONNECTED:
        esp_mqtt_client_stop(config->client);
        break;
    case ROUTE_AP_START:
        objHttpdStart(config);
        break;
    case ROUTE_AP_STOP:
        objHttpdStop(config);
        break;
    default:
        break;
    }
}
void app_main()
{
    ConfigifyInit(&config);
    objTimerCreate(&config);
    OutifyInit(IO00);

    objQueueInit(&config, objMqttCallback);
    objClickInit(&config, IO02, key_click_handler);

    objWifiStart(&config, objWifiCallback);
    if (config.bits == pdTRUE)
    {
        MqttifyInit(&config);
    }
}
