/**
 * @file queue.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月18日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_QUEUE_H
#define WANGYONGLIN_QUEUE_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct objHandle
    {
        xQueueHandle xQueue;
        TickType_t ticks_to_wait;
    };

    typedef struct objHandle objQueue_t;
    esp_err_t objQueueInit(objQueue_t *queue);
#ifdef __cplusplus
}
#endif
#endif