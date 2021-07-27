#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <esp_http_server.h>
#include <wangyonglin/httpd.h>
extern const uint8_t web_file_index_html_start[] asm("_binary_index_html_start");
extern const uint8_t web_file_index_html_end[] asm("_binary_index_html_end");
/* An HTTP GET handler */
esp_err_t index_html(httpd_req_t *req)
{
    char * str =web_file_index_html_start;
    unsigned int str_len =web_file_index_html_end-web_file_index_html_start; 
    httpd_resp_send(req, str,str_len);
    return ESP_OK;
}

void obj_httpd_index_html(objConfig_t *config, const char *uri)
{
    httpd_uri_t uri_t = {
        .uri = uri,
        .method = HTTP_GET,
        .handler = index_html,
        .user_ctx = NULL,
    };
    httpd_register_uri_handler(config->httpd, &uri_t);
}