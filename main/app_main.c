/**
 * @file app_main.c
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

static const char *TAG = "main";
objQueue_t queue;
void input_handler(uint32_t press,uint32_t io)
{
    if (press == KEY_LONG_PRESS)
    {
        objFlashBootSet(0);
    }
    else if (press == KEY_SHORT_PRESS)
    {
        objGpioOutputChange(IO14);
    }
}
void app_main()
{
    objSystemInit();
    objQueueInit(&queue);
    objUartInit(9600);
    objGpioOutputInit((1ULL<<IO14));
    objGpioInputInit(IO05, input_handler);
    initialise_wifi();
    objMqttStart(&queue);

    // objOtaStart("https://www.wangyonglin.com/hello-world.bin");
}
