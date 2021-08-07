#include <espify.h>
#include <configify.h>
#include <messageify.h>
#include <stringify.h>
#include <queueify.h>
void objQueueWaitHandler(void *pvParameter)
{
    Configify_t *config = (Configify_t *)pvParameter;
    objMessage_t message;
    for (;;)
    {
        objMessageInit(&message);

        if (xQueueReceive(config->xQueueMqtt, &message, config->ticks_to_wait) == pdPASS)
        {
            if (message.level == 0x0002)
            {

                objMessageTrun(&message);
                if (message.trun == On)
                {

                    config->pfnMqttCallback(config, EVENT_TRUN_LEVEL, (uint8_t *)"on", 2);
                }
                else if (message.trun == Off)
                {
                    config->pfnMqttCallback(config, EVENT_TRUN_LEVEL, (uint8_t *)"off", 3);
                }
            }
            else if (message.level == 0x0001)
            {

                objMessageRF433(&message);
                if (message.rf433)
                {
                    config->pfnMqttCallback(config, EVENT_RF433_LEVEL, message.rf433, strlen((char *)message.rf433));
                }
            }
        }
        objMessageClean(&message);
    }
    vTaskDelete(NULL);
}
esp_err_t objQueueInit(Configify_t *config, MqttCallback_t cb)
{
    config->pfnMqttCallback = cb;
    config->xQueueMqtt = xQueueCreate(3, sizeof(objMessage_t));
    config->ticks_to_wait = portMAX_DELAY;
    esp_err_t err = ESP_OK;
    xTaskCreate(objQueueWaitHandler, "objQueueWaitHandler", 1024 * 5, config, 10, NULL);
    return err;
}
