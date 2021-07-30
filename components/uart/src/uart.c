#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "uart_events";



#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)

static QueueHandle_t uart0_queue;

static void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    uint8_t *dtmp = (uint8_t *)malloc(RD_BUF_SIZE);
    objConfig_t *config = (objConfig_t *)pvParameters;
    objRF433Pack_t obj;
    for (;;)
    {
        if (xQueueReceive(uart0_queue, (void *)&event, (portTickType)portMAX_DELAY))
        {
            bzero(dtmp, RD_BUF_SIZE);
            switch (event.type)
            {
            case UART_DATA:
                if (config->timer_control_clieck.bit == pdTRUE)
                {
                    if (uart_read_bytes(config->uart_num, dtmp, event.size, portMAX_DELAY) > 0)
                    {
                        if (config->timer_control_message.bit == pdFALSE)
                        {
                            if (objRf433Parse(&obj, dtmp, event.size) == pdTRUE)
                            {
                                if (objRF433Add(config, obj) == pdTRUE)
                                {
                                    config->timer_control_message.bit = pdTRUE;
                                    esp_timer_start_once(config->timer_control_message.handler, config->timer_control_message.timeout_us);
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (uart_read_bytes(config->uart_num, dtmp, event.size, portMAX_DELAY) > 0)
                    {
                        if (config->timer_control_message.bit == pdFALSE)
                        {
                            if (objRf433Parse(&obj, dtmp, event.size) == pdTRUE)
                            {
                                if (objRF433PackCheck(config, obj) == pdTRUE)
                                {
                                    obj_output_switch(IO00);
                                    config->timer_control_message.bit = pdTRUE;
                                    esp_timer_start_once(config->timer_control_message.handler, config->timer_control_message.timeout_us);
                                }
                            }
                        }
                    }
                }
                break;

            // Event of HW FIFO overflow detected
            case UART_FIFO_OVF:
                ESP_LOGI(TAG, "hw fifo overflow");

                uart_flush_input(config->uart_num);
                xQueueReset(uart0_queue);
                break;

            // Event of UART ring buffer full
            case UART_BUFFER_FULL:
                ESP_LOGI(TAG, "ring buffer full");
                uart_flush_input(config->uart_num);
                xQueueReset(uart0_queue);
                break;

            case UART_PARITY_ERR:
                ESP_LOGI(TAG, "uart parity error");
                break;

            // Event of UART frame error
            case UART_FRAME_ERR:
                ESP_LOGI(TAG, "uart frame error");
                break;

            // Others
            default:
                ESP_LOGI(TAG, "uart event type: %d", event.type);
                break;
            }
        }
    }

    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}
void UartOnceTimerCallback(void *arg)
{
    objConfig_t *config = (objConfig_t *)arg;
    config->timer_control_message.bit = pdFALSE;
    esp_timer_stop(config->timer_control_message.handler);
}

esp_err_t objUartStart(objConfig_t *config)
{
    esp_timer_create_args_t test_once_arg =
        {
            .callback = &UartOnceTimerCallback, // 设置回调函数
            .arg = config,                      // 不携带参数
            .name = "UartOnceTimer"             // 定时器名字
        };
    esp_timer_create(&test_once_arg, &config->timer_control_message.handler);
    ESP_ERROR_CHECK(uart_param_config(config->uart_num, &config->uart_config));
    ESP_ERROR_CHECK(uart_driver_install(config->uart_num, BUF_SIZE * 1, BUF_SIZE * 1, 100, &uart0_queue, 0));
    xTaskCreate(uart_event_task, "uart_event_task", 2048, config, 10, NULL);
    return ESP_OK;
}