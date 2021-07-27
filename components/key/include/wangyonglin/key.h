/**
 * @file key.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月26日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_KEY_H
#define WANGYONGLIN_KEY_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
#define KEY_GPIO_LL_PRESS_EVT 0x09 //超长按事件
#define KEY_GPIO_L_PRESS_EVT 0x06  //长按事件
#define KEY_GPIO_S_PRESS_EVT 0x03  //短按事件

    
    esp_err_t objClickInit(objConfig_t *config,uint32_t io, objClickCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif