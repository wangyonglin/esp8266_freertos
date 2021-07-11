#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "string.h"
#include <esp_log.h>
#include <cJSON.h>
#include <wangyonglin/message.h>
objMessage_t * objMessageInit()
{
    objMessage_t *obj=(objMessage_t*)malloc(sizeof(objMessage_t));
    obj->root = cJSON_CreateArray();
    return obj;
}
esp_err_t objMessageSkeleton(objMessage_t *obj, const char *id, double level)
{
    esp_err_t err = ESP_OK;
    if (obj != NULL)
    {
        return ESP_FAIL;
    }
    cJSON *res = NULL;
    cJSON_AddItemToArray(obj->root, (res = cJSON_CreateObject()));
    cJSON_AddStringToObject(res, "id", id);
    if (level != 1)
    {
        cJSON_AddStringToObject(res, "trun", "off");
    }
    else
    {
        cJSON_AddStringToObject(res, "trun", "on");
    }

    return err;
}

char *objMessagePrint(objMessage_t *obj)
{
    return cJSON_Print(obj->root);
}