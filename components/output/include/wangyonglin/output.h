#ifndef WANGYONGLIN_OUTPUT_H
#define WANGYONGLIN_OUTPUT_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t obj_output_init(uint32_t gpio);
    esp_err_t obj_output_setting(uint32_t io, uint32_t level);
    esp_err_t obj_output_switch(uint32_t io);
#ifdef __cplusplus
}
#endif
#endif