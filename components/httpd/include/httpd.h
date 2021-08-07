#ifndef WANGYONGLIN_HTTPD_H
#define WANGYONGLIN_HTTPD_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
    esp_err_t objHttpdStart(Configify_t *config);
    esp_err_t objHttpdStop(Configify_t *config);
    void objHttpdRegisterUriIndexCss(Configify_t *config);
    void objHttpdUnRegisterUriIndexCss(Configify_t *config);
    void objHttpdRegisterUriIndexHtml(Configify_t *config);
    void objHttpdUnRegisterUriIndexHtml(Configify_t *config);
    void objHttpdRegisterUriInfoHtml(Configify_t *config);
    void objHttpdUnRegisterUriInfoHtml(Configify_t *config);
    void objHttpdRegisterUriWifiHtml(Configify_t *config);
    void objHttpdUnRegisterUriWifiHtml(Configify_t *config);
    void objHttpdRegisterUriPromiseMinJs(Configify_t *config);
    void objHttpdUnRegisterUriPromiseMinJs(Configify_t *config);

#ifdef __cplusplus
}
#endif
#endif