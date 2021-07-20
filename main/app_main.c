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
objEvent_t trigger;
objEvent_t button;
void app_main()
{
    objSystemInit();
    objEventInit(&trigger, objIOButton);
    objEventClick(&trigger, objIOLow);
    objButtonInit(&button);
    objQueueInit(&queue,&trigger);
    objUartInit(9600);
    initialise_wifi();
    objMqttStart(&queue);

    // objOtaStart("https://www.wangyonglin.com/hello-world.bin");
}
