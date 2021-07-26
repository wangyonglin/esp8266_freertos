#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "QUEUE";

void objQueueWaitHandler(void *pvParameter)
{
    objQueue_t *queue = (objQueue_t *)pvParameter;
    objMessage_t message;
    for (;;)
    {
        objMessageInit(&message);

        if (xQueueReceive(queue->xQueue, &message, queue->ticks_to_wait) == pdPASS)
        {
            if (message.level == 0x0002)
            {

                objMessageTrun(&message);
                if (message.trun == On)
                {

                    queue->callback(obj_trun_level, (uint8_t *)"on", 2);
                    obj_output_setting(IO00, 0);
                }
                else if (message.trun == Off)
                {
                    queue->callback(obj_trun_level, (uint8_t *)"off", 3);
                }
            }
            else if (message.level == 0x0001)
            {

                objMessageRF433(&message);
                if (message.rf433)
                {
                    queue->callback(obj_rf433_level, message.rf433, strlen((char *)message.rf433));
                }
            }
        }
        objMessageClean(&message);
    }
    vTaskDelete(NULL);
}
esp_err_t obj_queue_init(objQueue_t *queue, obj_queue_cb_t cb)
{
    queue->xQueue = xQueueCreate(3, sizeof(objMessage_t));
    queue->ticks_to_wait = portMAX_DELAY;
    queue->callback = cb;
    esp_err_t err = ESP_OK;
    xTaskCreate(objQueueWaitHandler, "objQueueWaitHandler", 1024 * 5, queue, 10, NULL);
    return err;
}
