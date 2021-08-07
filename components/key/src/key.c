
#include <espify.h>
#include <configify.h>
#include <key.h>
static xQueueHandle gpio_evt_queue = NULL;
static void gpio_isr_handler(void *arg)
{
    uint32_t io = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &io, NULL);
}

static void gpio_task_example(void *arg)
{
    uint32_t io;
    Configify_t *config = (Configify_t *)arg;
    BaseType_t press_key = pdFALSE;
    BaseType_t lift_key = pdFALSE;
    int64_t backup_time = 0;
    for (;;)
    {
        if (xQueueReceive(gpio_evt_queue, &io, portMAX_DELAY))
        {
            //记录下用户按下按键的时间点
            if (gpio_get_level(io) == 0)
            {
                press_key = pdTRUE;
                backup_time = esp_timer_get_time();

                //如果当前GPIO口的电平已经记录为按下，则开始减去上次按下按键的时间点
            }
            else if (press_key)
            {
                //记录抬升时间点
                lift_key = pdTRUE;
                backup_time = esp_timer_get_time() - backup_time;
            }

            //近当按下标志位和按键弹起标志位都为1时候，才执行回调
            if (press_key & lift_key)
            {
                press_key = pdFALSE;
                lift_key = pdFALSE;

                if (backup_time > 12000000)
                { /* 30m long long press */
                    config->pfnClickCallback(config, KEY_GPIO_LL_PRESS_EVT);
                }
                else
                {
                    if (backup_time > 3000000)
                    { /*30m long press */
                        config->pfnClickCallback(config, KEY_GPIO_L_PRESS_EVT);
                    }
                    else
                    {
                        config->pfnClickCallback(config, KEY_GPIO_S_PRESS_EVT);
                    }
                }
            }
        }
    }
}

esp_err_t objClickInit(Configify_t *config, uint32_t io, ClickCallback_t cb)
{
    config->pfnClickCallback = cb;
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = (1ULL << io);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1; //使能上拉
    gpio_config(&io_conf);
    gpio_set_intr_type(io, GPIO_INTR_ANYEDGE);
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, config, 10, NULL);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(io, gpio_isr_handler, (void *)io);
    return ESP_OK;
}
