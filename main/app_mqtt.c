/**
 * @file app_mqtt.c
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

static const char *TAG = "MQTT";

#define WANGYONGLIN_MQTT_BROKER_URL "mqtt://broker.wangyonglin.com"
#define WANGYONGLIN_MQTT_USERNAME "wangyonglin"
#define WANGYONGLIN_MQTT_PASSWORD "W@ng0811"
#define WANGYONGLIN_MQTT_TOPIC "jscs"
objMessage_t message;
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    objQueue_t *queue = (objQueue_t *)event->user_context;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(client, WANGYONGLIN_MQTT_TOPIC, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        msg_id = esp_mqtt_client_publish(client, WANGYONGLIN_MQTT_TOPIC, "data", 0, 0, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        if (objMessage(event->data, &message) == ESP_OK)
        {
            if (xQueueSend(queue->xQueue, &message, NULL) == pdPASS)
            {
                ESP_LOGI(TAG, "xQueueSend OK");
            }
            else
            {
                ESP_LOGI(TAG, "xQueueSend FAILT");
            }
        }
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

void objMqttStart(objQueue_t *queue)
{

    esp_mqtt_client_config_t mqtt_cfg = {
        .client_id = objChipId(),
        .uri = WANGYONGLIN_MQTT_BROKER_URL,
        .username = WANGYONGLIN_MQTT_USERNAME,
        .password = WANGYONGLIN_MQTT_PASSWORD,
        .user_context = queue};
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, queue);
    esp_mqtt_client_start(client);
    //esp_mqtt_client_stop(client);
}