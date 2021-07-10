#ifndef WANGYONGLIN_WIFI_H
#define WANGYONGLIN_WIFI_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_err.h"
#include "esp_wifi.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        WANG_STA_START,
        WANG_STA_STOP,
        WANG_AP_START,
        WANG_AP_STOP,
        WANG_STA_CONNECT,
        WANG_STA_SCAN_START,
        WANG_STA_SCAN_STOP,
        WANG_AP_HTTPD_START,
        WANG_AP_HTTPD_STOP,
        WANG_SYSTEM_START,
        WANG_STA_GOT_IP
    } wang_startup_id_t;

    struct wang_sta
    {
        void (*ok)(int id, void *ctx);
        void (*fail)(int id, void *ctx);
    };
    typedef struct wang_sta wang_sta_t;

    struct wang_handle
    {
        EventGroupHandle_t wifi_event_group;
        wifi_scan_config_t *config;
        void *ctx;
        size_t len;
        void (*startup)(wang_startup_id_t id, struct wang_handle *handle, void *ctx, size_t len);
        wang_sta_t sta;
    };
    typedef struct wang_handle wang_handle_t;

    void wang_sta_ok(void (*ok)(int id, void *ctx), void *ctx);
    void wang_sta_fail(void (*fail)(int id, void *ctx), void *ctx);
    void initialise_wifi();
    esp_err_t wang_ap_start(struct wang_handle *handle);
    esp_err_t wang_sta_scan(struct wang_handle *handle);
    char *wang_ap_default(void);
#ifdef __cplusplus
}
#endif
#endif