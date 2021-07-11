/**
 * @file event.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月11日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */

#ifndef WANGYONGLIN_EVENT_H
#define WANGYONGLIN_EVENT_H
#include <wangyonglin/esp.h>
#include <wangyonglin/io.h>
#ifdef __cplusplus
extern "C"
{
#endif

    struct objEvent
    {
        objGPIO_t io;
    };
    typedef struct objEvent objEvent_t;

    esp_err_t objEventInit(struct objEvent *obj, objGPIO_t bit);
    esp_err_t objEventToggler(struct objEvent *obj);
    esp_err_t objEventClick(struct objEvent *obj, objIO_t level);
#ifdef __cplusplus
}
#endif
#endif