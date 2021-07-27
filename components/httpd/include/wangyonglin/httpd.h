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
    void obj_httpd_index_html(objConfig_t *config, const char *uri);
    void obj_httpd_wifi_html(objConfig_t *config, const char *uri, void *ctx);
    void obj_httpd_info_html(objConfig_t *config, const char *uri, void *ctx);
#ifdef __cplusplus
}
#endif
#endif