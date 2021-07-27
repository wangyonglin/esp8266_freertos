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
   


    esp_err_t objQueueInit(objConfig_t *config, objMqttCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif