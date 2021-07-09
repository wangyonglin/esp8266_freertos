#ifndef WANGYONGLIN_HTTPD_H
#define WANGYONGLIN_HTTPD_H
#include <wangyonglin/wifi.h>
#include <esp_http_server.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct
    {
        httpd_handle_t handle;
        void *ctx;
    } wang_httpd_t;
    void wang_httpd_start(struct wang_handle *handle,void *ctx);
    void wang_httpd_index_html(wang_httpd_t *httpd, const char *uri);
    void wang_httpd_wifi_json(wang_httpd_t *httpd, const char *uri,void *ctx);
    void wang_httpd_config_json(wang_httpd_t *httpd, const char *uri, void *ctx);
#ifdef __cplusplus
}
#endif
#endif