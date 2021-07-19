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

        if (xQueueReceive(queue->xQueue, &message,queue->ticks_to_wait)== pdPASS)
        {
            ESP_LOGI(TAG, "xQueueReceive %d", message.trun);
            if (message.trun == objTrunOn)
            {
                objEventClick(queue->trigger, objIOHigh);
            }
            else if (message.trun == objTrunOff)
            {
                objEventClick(queue->trigger, objIOLow);
            }
        }
    }
    vTaskDelete(NULL);
}
esp_err_t objQueueInit(objQueue_t *queue, objEvent_t *trigger)
{
    queue->xQueue = xQueueCreate(5, sizeof(objMessage_t));
    queue->ticks_to_wait = portMAX_DELAY;
    queue->trigger = trigger;
    esp_err_t err = ESP_OK;
    xTaskCreate(objQueueWaitHandler, "objQueueWaitHandler", 1024 * 3, queue, 10, NULL);
    return err;
}
