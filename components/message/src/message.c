#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "MESSAGE";
esp_err_t objMessage(char *data, objMessage_t *message)
{
    objMessageInit(message);
    esp_err_t err = ESP_OK;
    cJSON *root;
    root = cJSON_Parse(data);
    if (!root)
    {
        ESP_LOGI(TAG, "cjson parse failt root");
        return ESP_ERR_INVALID_ARG;
    }

    cJSON *success = cJSON_GetObjectItem(root, "success");
    if (!success)
    {
        ESP_LOGI(TAG, "cjson parse failt success");
        cJSON_Delete(root);
        return ESP_ERR_INVALID_ARG;
    }
    cJSON *result = cJSON_GetObjectItem(root, "result");
    if (!result)
    {
        ESP_LOGI(TAG, "cjson parse failt result");
        cJSON_Delete(success);
        cJSON_Delete(root);
        return ESP_ERR_INVALID_ARG;
    }
    cJSON *trun = cJSON_GetObjectItem(result, "trun");
    if (!trun)
    {
        ESP_LOGI(TAG, "cjson parse failt trun");
        cJSON_Delete(result);
        cJSON_Delete(success);
        cJSON_Delete(root);
        return ESP_ERR_INVALID_ARG;
    }
    if (strcmp(trun->valuestring, "on") == 0)
    {
        message->trun = objTrunOn;
        return err;
    }
    else if (strcmp(trun->valuestring, "off") == 0)
    {
        message->trun = objTrunOff;
        return err;
    }
    cJSON_Delete(trun);
    cJSON_Delete(result);
    cJSON_Delete(success);
    cJSON_Delete(root);
    return err;
}
esp_err_t objMessageInit(objMessage_t *message)
{
    esp_err_t err = ESP_OK;
    message->level = -1;
    message->trun = objTrunNone;
    return err;
}
