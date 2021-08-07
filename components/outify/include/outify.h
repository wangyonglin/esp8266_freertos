#ifndef __OUTPUT_H
#define __OUTPUT_H
#include <espify.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t OutifyInit(uint32_t gpio);
    esp_err_t OutifySetting(uint32_t io, uint32_t level);
    esp_err_t OutifyTrigger(uint32_t io);
#ifdef __cplusplus
}
#endif
#endif