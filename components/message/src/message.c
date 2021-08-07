#include <espify.h>
#include <configify.h>
#include <messageify.h>
#include <stringify.h>
static const char *TAG = "MESSAGE";
esp_err_t objMessageTrun(objMessage_t *message)
{
    esp_err_t err = ESP_OK;
    cJSON *root;
    root = cJSON_Parse((char *)message->pvBuffer);
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
        message->trun = On;
        return ESP_OK;
    }
    else if (strcmp(trun->valuestring, "off") == 0)
    {
        message->trun = Off;
        return ESP_OK;
    }
    cJSON_Delete(trun);
    cJSON_Delete(result);
    cJSON_Delete(success);
    cJSON_Delete(root);
    return err;
}

esp_err_t objMessageRF433(objMessage_t *message)
{
    esp_err_t err = ESP_OK;
    cJSON *root;
    root = cJSON_Parse((char *)message->pvBuffer);
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
    cJSON *rf433 = cJSON_GetObjectItem(result, "rf433");
    if (!rf433)
    {
        ESP_LOGI(TAG, "cjson parse failt rf433");
        cJSON_Delete(result);
        cJSON_Delete(success);
        cJSON_Delete(root);
        return ESP_ERR_INVALID_ARG;
    }
    else
    {
        int len = strlen(rf433->valuestring);
        if (len < sizeof(message->rf433))
        {
            ESP_LOGI(TAG, "rf433 %s", rf433->valuestring);
            strbytes(rf433->valuestring, message->rf433);
        }
    }

    cJSON_Delete(rf433);
    cJSON_Delete(result);
    cJSON_Delete(success);
    cJSON_Delete(root);
    return err;
}

esp_err_t objMessageInit(objMessage_t *message)
{
    esp_err_t err = ESP_OK;
    message->level = -1;
    message->trun = None;
    bzero(message->rf433, sizeof(message->rf433));
    bzero(message->pvBuffer, sizeof(message->pvBuffer));
    return err;
}
esp_err_t objMessageClean(objMessage_t *message)
{
    return ESP_OK;
}