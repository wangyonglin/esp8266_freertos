#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <wangyonglin/event.h>
#include "driver/gpio.h"

esp_err_t objEventInit(struct objEvent *obj, objGPIO_t io)
{
    esp_err_t err = ESP_OK;
    if (obj == NULL)
        return ESP_FAIL;
    obj->io = io;
    gpio_config_t io_conf;                     //创建一个GPIO结构体
    io_conf.intr_type = GPIO_INTR_DISABLE;     //失能中断服务
    io_conf.mode = GPIO_MODE_OUTPUT;           //设置成输出模式
    io_conf.pin_bit_mask = (1ULL << obj->io); //指定要配置的GPIO
    io_conf.pull_down_en = 0;                  //不使能下拉
    io_conf.pull_up_en = 0;                    //不使能上拉
    gpio_config(&io_conf);                     //配置GPIO
    ESP_ERROR_CHECK(err);
    return err;
}

esp_err_t objEventToggler(struct objEvent *obj)
{
    esp_err_t err = ESP_OK;
    int ret = 0;
    if (obj != NULL)
    {
        ret = gpio_get_level(obj->io);
        if (ret == 0)
        {
            err = gpio_set_level(obj->io, 1);
        }
        else
        {
            err = gpio_set_level(obj->io, 0);
        }
    }

    return err;
}

esp_err_t objEventClick(struct objEvent *obj, objIO_t level)
{
    esp_err_t err = ESP_OK;
    if (obj != NULL)
    {
        err = gpio_set_level(obj->io, level);
    }

    return err;
}