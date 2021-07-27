/**
 * @file app_main.c
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月10日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#include <wangyonglin/wangyonglin.h>
#include <wangyonglin/esp.h>
static const char *TAG = "main";
objConfig_t config;
void objMqttCallback(objConfig_t *config,int level, uint8_t *data, int len)
{
    switch (level)
    {
    case obj_trun_level:
        if (strcmp((char *)data, "on") == 0)
        {
            obj_output_setting(IO00, 0);
        }
        else if (strcmp((char *)data, "off") == 0)
        {
            obj_output_setting(IO00, 1);
        }
        break;
    case obj_rf433_level:
        if (data)
        {
            ESP_LOGI(TAG, (char *)data);
        }
        break;
    default:
        break;
    }
}
void key_click_handler(objConfig_t *config, uint8_t event)
{
    switch (event)
    {
    case KEY_GPIO_S_PRESS_EVT:
        ESP_LOGI(TAG, "短按事件");
        obj_output_switch(IO00);
        break;
    case KEY_GPIO_L_PRESS_EVT:
        ESP_LOGI(TAG, "长按事件");
        break;
    case KEY_GPIO_LL_PRESS_EVT:
        ESP_LOGI(TAG, "超长按事件");
        objBootSet(config, pdFALSE);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        esp_restart();
        break;
    default:
        break;
    }
}

void objWifiCallback(objConfig_t *config, objRouteId_t id)
{
    switch (id)
    {
    case ROUTE_STA_GOT_IP:
        esp_mqtt_client_start(config->client);
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
    objSystemInit();
    objConfigInit(&config);
    obj_output_init(IO00);
    objQueueInit(&config,objMqttCallback);

    objClickInit(&config, IO02, key_click_handler);

    objWifiStart(&config, objWifiCallback);
    if (config.bits == pdTRUE)
    {
        objMqttInit(&config);
    }
}
