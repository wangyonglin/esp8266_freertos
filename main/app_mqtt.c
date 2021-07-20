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
#define TOPIC_RF433 "rf433"
#define TOPIC_TRUN "trun"
objMessage_t message;
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    objQueue_t *queue = (objQueue_t *)handler_args;
    int msg_id;
    switch (event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(event->client, TOPIC_RF433, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        msg_id = esp_mqtt_client_subscribe(event->client, TOPIC_TRUN, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        objMessageInit(&message);
        if (strncmp(TOPIC_RF433, event->topic, event->topic_len) == 0)
        {
            message.level = 0x0001;
            memcpy(message.pvBuffer, event->data, event->data_len);
            if (xQueueSendToBack(queue->xQueue, &message, NULL) != pdPASS)
            {
                ESP_LOGI(TAG, "send rf433 queue fail");
            }
        }
        else if (strncmp(TOPIC_TRUN, event->topic, event->topic_len) == 0)
        {
            message.level = 0x0002;
            memcpy(message.pvBuffer, event->data, event->data_len);
            if (xQueueSendToBack(queue->xQueue, &message, NULL) != pdPASS)
            {
                ESP_LOGI(TAG, "send trun queue fail");
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
}

void objMqttStart(objQueue_t *queue)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .client_id = objChipId(),
        .uri = WANGYONGLIN_MQTT_BROKER_URL,
        .username = WANGYONGLIN_MQTT_USERNAME,
        .password = WANGYONGLIN_MQTT_PASSWORD};
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);

    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, queue);
    esp_mqtt_client_start(client);
    //esp_mqtt_client_stop(client);
}