/**
 * @file timer.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月29日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_TIMER_H
#define WANGYONGLIN_TIMER_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objTimerCreate(objConfig_t *config);
    esp_err_t objTimerDelete(objConfig_t *config);
    esp_err_t objTimerStart(objConfig_t *config);
    esp_err_t objTimerStop(objConfig_t *config);
#ifdef __cplusplus
}
#endif
#endif