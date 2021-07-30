#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "timer";
// 定义一个单次运行的定时器结构体
void test_timer_once_cb(void *arg)
{
    objConfig_t *config = (objConfig_t *)arg;
    config->timer_control_clieck.bit = pdFALSE;
    objTimerStop(config);
}

esp_err_t objTimerCreate(objConfig_t *config)
{
    esp_timer_create_args_t test_once_arg =
        {
            .callback = &test_timer_once_cb, // 设置回调函数
            .arg = config,                   // 不携带参数
            .name = "TestOnceTimer"          // 定时器名字
        };
    return esp_timer_create(&test_once_arg, &config->timer_control_clieck.handler);
}
esp_err_t objTimerStart(objConfig_t *config)
{
    config->timer_control_clieck.bit=pdTRUE;
    return esp_timer_start_once(config->timer_control_clieck.handler, config->timer_control_clieck.timeout_us);
}
esp_err_t objTimerStop(objConfig_t *config)
{
    return esp_timer_stop(config->timer_control_clieck.handler);
}
esp_err_t objTimerDelete(objConfig_t *config)
{
    return esp_timer_delete(config->timer_control_clieck.handler);
}
