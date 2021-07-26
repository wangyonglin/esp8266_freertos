#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>

esp_err_t obj_output_init(uint32_t gpio)
{
    gpio_config_t io_conf;                 //创建一个GPIO结构体
    io_conf.intr_type = GPIO_INTR_DISABLE; //失能中断服务
    io_conf.mode = GPIO_MODE_OUTPUT;       //设置成输出模式
    io_conf.pin_bit_mask = (1ULL << gpio);   //指定要配置的GPIO
    io_conf.pull_down_en = 0;              //不使能下拉
    io_conf.pull_up_en = 0;                //不使能上拉
    gpio_config(&io_conf);                 //配置GPIO
    return ESP_OK;
}
esp_err_t obj_output_setting(uint32_t io, uint32_t level)
{
    return gpio_set_level(io, level);
}
esp_err_t obj_output_switch(uint32_t io)
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