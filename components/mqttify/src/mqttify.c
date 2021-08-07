#include <espify.h>
#include <configify.h>
#include <messageify.h>
#include <queueify.h>
static const char *TAG = "mqttify";

#define WANGYONGLIN_MQTT_BROKER_URL "mqtt://broker.wangyonglin.com"
#define WANGYONGLIN_MQTT_USERNAME "wangyonglin"
#define WANGYONGLIN_MQTT_PASSWORD "W@ng0811"
#define TOPIC_RF433_SET "/wangyonglin/rf433/set"
#define TOPIC_RF433_GET "/wangyonglin/rf433/get"
#define TOPIC_TRUN_SET "/wangyonglin/trun/set"
#define TOPIC_TRUN_GET "/wangyonglin/trun/get"
objMessage_t message;
static void mqtt_event_task(void *pvParameters);
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    Configify_t *config = (Configify_t *)handler_args;
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    int msg_id;

    switch (event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(event->client, TOPIC_RF433_GET, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        msg_id = esp_mqtt_client_subscribe(event->client, TOPIC_TRUN_GET, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        xTaskCreate(mqtt_event_task, "mqtt_event_task", 2048, config, 10, NULL);
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
        if (strncmp(TOPIC_RF433_GET, event->topic, event->topic_len) == 0)
        {
            message.level = 0x0001;
            memcpy(message.pvBuffer, event->data, event->data_len);
            if (xQueueSendToBack(config->xQueueMqtt, &message, NULL) != pdPASS)
            {
                ESP_LOGI(TAG, "send rf433 queue fail");
            }
        }
        else if (strncmp(TOPIC_TRUN_GET, event->topic, event->topic_len) == 0)
        {
            message.level = 0x0002;
            memcpy(message.pvBuffer, event->data, event->data_len);
            if (xQueueSendToBack(config->xQueueMqtt, &message, NULL) != pdPASS)
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

static void mqtt_event_task(void *pvParameters)
{
    Configify_t *config = (Configify_t *)pvParameters;
    cJSON *root = NULL;
    cJSON *restult = NULL;
    cJSON *items = NULL;
    for (;;)
    {

        vTaskDelay(5000 / portTICK_PERIOD_MS);
        root = cJSON_CreateObject();
        cJSON_AddTrueToObject(root, "success");
        cJSON_AddStringToObject(root, "message", "ok");
        cJSON_AddItemToObject(root, "result", restult = cJSON_CreateObject());
        cJSON_AddStringToObject(restult,"id",(char*)config->only_id);
        if (gpio_get_level(IO00) == 0)
        {
            cJSON_AddStringToObject(restult, "trun", "off");
        }
        else
        {
            cJSON_AddStringToObject(restult, "trun", "on");
        }
        char *out = cJSON_Print(root);
        if (esp_mqtt_client_publish(config->client, TOPIC_TRUN_SET, out, strlen(out), 0, 0) == ESP_OK)
        {
            ESP_LOGI(TAG, out);
        }
        free(out);
        cJSON_Delete(root);
        root = NULL;
    }

    vTaskDelete(NULL);
}

void MqttifyInit(Configify_t *config)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .client_id = (char*)config->only_id,
        .uri = WANGYONGLIN_MQTT_BROKER_URL,
        .username = WANGYONGLIN_MQTT_USERNAME,
        .password = WANGYONGLIN_MQTT_PASSWORD};
    config->client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(config->client, ESP_EVENT_ANY_ID, mqtt_event_handler, config);
}