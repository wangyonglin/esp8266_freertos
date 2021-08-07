#ifndef __WIFIIFY_H
#define __WIFIIFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objWifiStart(Configify_t *config,WifiCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif