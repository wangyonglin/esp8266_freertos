
#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "GPIO";

static xQueueHandle gpio_evt_queue = NULL;
static void gpio_isr_handler(void *arg)
{
    objIO_t io = (objIO_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &io, NULL);
}

static void gpio_task_example(void *arg)
{
    objIO_t io;
    objGpio_cb_t callback = (objGpio_cb_t)arg;
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

                //如果大于1s则回调长按，否则就短按回调
                if (backup_time > 6000000)
                {
                    ESP_LOGI(TAG, "长按触发");
                    callback(KEY_LONG_PRESS, io);
                }
                else
                {
                    ESP_LOGI(TAG, "短按触发");
                    callback(KEY_SHORT_PRESS, io);
                }
            }
        }
    }
}

esp_err_t objGpioInputInit(objIO_t io, objGpio_cb_t cb)
{

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = (1ULL << io);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    gpio_set_intr_type(io, GPIO_INTR_ANYEDGE);
    gpio_evt_queue = xQueueCreate(10, sizeof(objIO_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, cb, 10, NULL);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(io, gpio_isr_handler, (void *)io);
    return ESP_OK;
}
esp_err_t objGpioOutputInit(uint32_t pin_bit_mask)
{
    gpio_config_t io_conf;                 //创建一个GPIO结构体
    io_conf.intr_type = GPIO_INTR_DISABLE; //失能中断服务
    io_conf.mode = GPIO_MODE_OUTPUT;       //设置成输出模式
    io_conf.pin_bit_mask = pin_bit_mask;   //指定要配置的GPIO
    io_conf.pull_down_en = 0;              //不使能下拉
    io_conf.pull_up_en = 0;                //不使能上拉
    gpio_config(&io_conf);                 //配置GPIO
    return ESP_OK;
}
esp_err_t objGpioOutputSet(objIO_t io, uint32_t level)
{
    return gpio_set_level(io, level);
}
esp_err_t objGpioOutputChange(uint32_t io)
{
    esp_err_t err;
    uint32_t ret;
    ret = gpio_get_level(io);
    if (ret == 1)
    {
        err = gpio_set_level(io, 0);
    }
    else
    {
        err = gpio_set_level(io, 1);
    }
    return err;
}