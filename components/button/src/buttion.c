#include <wangyonglin/wangyonglin.h>
#include <wangyonglin/esp.h>

typedef enum
{
    KEY_SHORT_PRESS = 1,
    KEY_LONG_PRESS,
} alink_key_t;

//宏定义一个GPIO
#define KEY_GPIO 5

static xQueueHandle gpio_evt_queue = NULL;

void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void KeyInit(uint32_t key_gpio_pin)
{

    //配置GPIO，下降沿和上升沿触发中断
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_ANYEDGE;
    io_conf.pin_bit_mask = 1 << key_gpio_pin;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    gpio_set_intr_type(key_gpio_pin, GPIO_INTR_ANYEDGE);
    gpio_evt_queue = xQueueCreate(2, sizeof(uint32_t));

    gpio_install_isr_service(0);
    gpio_isr_handler_add(key_gpio_pin, gpio_isr_handler, (void *)key_gpio_pin);
}

esp_err_t alink_key_scan(TickType_t ticks_to_wait)
{

    uint32_t io_num;
    BaseType_t press_key = pdFALSE;
    BaseType_t lift_key = pdFALSE;
    int64_t backup_time = 0;

    while (1)
    {

        //接收从消息队列发来的消息
        xQueueReceive(gpio_evt_queue, &io_num, ticks_to_wait);

        //记录下用户按下按键的时间点
        if (gpio_get_level(io_num) == 0)
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
                return KEY_LONG_PRESS;
            }
            else
            {
                return KEY_SHORT_PRESS;
            }
        }
    }
}

void key_trigger(void *arg)
{
    objEvent_t *evt = (objEvent_t *)arg;
    esp_err_t ret = 0;
    KeyInit(KEY_GPIO);

    while (1)
    {
        ret = alink_key_scan(portMAX_DELAY);
        if (ret == -1)
            vTaskDelete(NULL);

        switch (ret)
        {
        case KEY_SHORT_PRESS:
            printf("短按触发回调 ... \r\n");
            objEventToggler(evt);
            break;

        case KEY_LONG_PRESS:
            printf("长按触发回调 ... \r\n");
            objFlashBootSet(0);
            break;

        default:
            break;
        }
    }

    vTaskDelete(NULL);
}

esp_err_t objButtonInit(objEvent_t *evt)
{
    esp_err_t err = ESP_OK;
    xTaskCreate(key_trigger, "key_trigger", 1024 * 3, evt, 10, NULL);
    return err;
}
