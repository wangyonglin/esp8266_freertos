/**
 * @file gpio.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月22日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_GPIO_H
#define WANGYONGLIN_GPIO_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define KEY_SHORT_PRESS 1
#define KEY_LONG_PRESS 2
#define IO00 0
#define IO01 1
#define IO02 2
#define IO03 3
#define IO05 5
#define IO14 14
#define IO16 16
    typedef void (*objGpio_cb_t)(uint32_t press, uint32_t io);
    esp_err_t objGpioInputInit(uint32_t io, objGpio_cb_t cb);
    esp_err_t objGpioOutputInit(uint32_t pin_bit_mask);
    esp_err_t objGpioOutputChange(uint32_t io);
    esp_err_t objGpioOutputSet(uint32_t io, uint32_t level);
#ifdef __cplusplus
}
#endif
#endif