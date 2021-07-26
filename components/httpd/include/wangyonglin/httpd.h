#ifndef WANGYONGLIN_HTTPD_H
#define WANGYONGLIN_HTTPD_H
#include <wangyonglin/esp.h>
#include <wangyonglin/wifi.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        httpd_handle_t handle;
        void *ctx;
    } obj_httpd_t;
    void obj_httpd_start();

    void obj_httpd_stop();
    void obj_httpd_index_html(obj_httpd_t *httpd, const char *uri);
    void obj_httpd_wifi_html(obj_httpd_t *httpd, const char *uri, void *ctx);
    void obj_httpd_info_html(obj_httpd_t *httpd, const char *uri, void *ctx);
#ifdef __cplusplus
}
#endif
#endif