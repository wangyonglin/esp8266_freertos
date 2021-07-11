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
#include <wangyonglin/esp.h>
#include <wangyonglin/io.h>
#include <wangyonglin/httpd.h>
#include <wangyonglin/wifi.h>
#include <wangyonglin/button.h>
#include <wangyonglin/event.h>
#include <wangyonglin/mqtt.h>

static const char *TAG = "main";

objEvent_t evt;
void app_main(){
    objSystemInit();
    objEventInit(&evt, objIOButton);
    objEventClick(&evt, objIOLow);
    objButtonInit(&evt);
    initialise_wifi();
    mqtt_app_start();
}

