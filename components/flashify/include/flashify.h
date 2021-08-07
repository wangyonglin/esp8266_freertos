#ifndef __FLASHIFY_H
#define __FLASHIFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objFlashWifiSet(wifi_config_t *config);
    esp_err_t objFlashWifiGet(wifi_config_t *config);
    int16_t FlashifyBootGet(void);
    esp_err_t FlashifyBootSet(int16_t val);
    esp_err_t objFlashRF433PacksSaveing(Configify_t *config);
    esp_err_t objFlashRF433PacksGetting(Configify_t *config);
#ifdef __cplusplus
}
#endif
#endif