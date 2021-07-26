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
#define obj_rf433_level 0x0002
#define obj_trun_level 0x0001
    typedef void (*obj_queue_cb_t)(int level, uint8_t *data, int len);
    struct objHandle
    {
        xQueueHandle xQueue;
        TickType_t ticks_to_wait;
        obj_queue_cb_t callback;
    };

    typedef struct objHandle objQueue_t;
    esp_err_t obj_queue_init(objQueue_t *queue, obj_queue_cb_t cb);
#ifdef __cplusplus
}
#endif
#endif