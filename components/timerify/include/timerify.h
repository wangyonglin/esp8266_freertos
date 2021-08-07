#ifndef __TIMERIFY_H
#define __TIMERIFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
  
    esp_err_t objTimerCreate(Configify_t *config);
    esp_err_t objTimerDelete(Configify_t *config);
    esp_err_t objTimerStart(Configify_t *config);
    esp_err_t objTimerStop(Configify_t *config);
#ifdef __cplusplus
}
#endif
#endif