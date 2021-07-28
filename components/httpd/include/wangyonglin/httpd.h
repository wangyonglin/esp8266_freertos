#ifndef WANGYONGLIN_HTTPD_H
#define WANGYONGLIN_HTTPD_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wifi.h>

#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objHttpdStart(objConfig_t *config);
    esp_err_t objHttpdStop(objConfig_t *config);
    void objHttpdRegisterUriIndexCss(objConfig_t *config);
    void objHttpdUnRegisterUriIndexCss(objConfig_t *config);
    void objHttpdRegisterUriIndexHtml(objConfig_t *config);
    void objHttpdUnRegisterUriIndexHtml(objConfig_t *config);
    void objHttpdRegisterUriInfoHtml(objConfig_t *config);
    void objHttpdUnRegisterUriInfoHtml(objConfig_t *config);
    void objHttpdRegisterUriWifiHtml(objConfig_t *config);
    void objHttpdUnRegisterUriWifiHtml(objConfig_t *config);
    void objHttpdRegisterUriPromiseMinJs(objConfig_t *config);
    void objHttpdUnRegisterUriPromiseMinJs(objConfig_t *config);

#ifdef __cplusplus
}
#endif
#endif