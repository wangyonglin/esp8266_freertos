#ifndef WANGYONGLIN_BUTTON_H
#define WANGYONGLIN_BUTTON_H
#include <wangyonglin/esp.h>
#include <wangyonglin/event.h>
#ifdef __cplusplus
extern "C"
{
#endif
    struct objButton
    {
        uint32_t bit;
    };
    typedef struct objButton objButton_t;
    esp_err_t objButtonInit(objEvent_t *evt);
#ifdef __cplusplus
}
#endif
#endif