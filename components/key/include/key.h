#ifndef __KEY_H
#define __KEY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
#define KEY_GPIO_LL_PRESS_EVT 0x09 //超长按事件
#define KEY_GPIO_L_PRESS_EVT 0x06  //长按事件
#define KEY_GPIO_S_PRESS_EVT 0x03  //短按事件

    
    esp_err_t objClickInit(Configify_t *config,uint32_t io, ClickCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif