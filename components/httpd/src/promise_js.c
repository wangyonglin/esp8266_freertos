#include <espify.h>
#include <configify.h>

extern const uint8_t web_file_promise_min_js_start[] asm("_binary_promise_min_js_start");
extern const uint8_t web_file_promise_min_js_end[] asm("_binary_promise_min_js_end");
static const char *TAG = "/promise.min.js";
/* An HTTP GET handler */
esp_err_t promise_min_js(httpd_req_t *req)
{
    httpd_resp_set_type(req,"application/javascript;charset=UTF-8");
    char *str = web_file_promise_min_js_start;
    unsigned int str_len = web_file_promise_min_js_end - web_file_promise_min_js_start;
    httpd_resp_send(req, str, str_len);
    return ESP_OK;
}

void objHttpdRegisterUriPromiseMinJs(Configify_t *config)
{
    httpd_uri_t uri_t = {
        .uri = TAG,
        .method = HTTP_GET,
        .handler = promise_min_js,
        .user_ctx = NULL,
    };
    if (httpd_register_uri_handler(config->httpd, &uri_t) == ESP_OK)
    {
        ESP_LOGI(TAG, "successfully registering the uri%s", TAG);
    }
}
void objHttpdUnRegisterUriPromiseMinJs(Configify_t *config)
{
    if(httpd_unregister_uri_handler(config->httpd,TAG, HTTP_GET)==ESP_OK){
         ESP_LOGI(TAG, "successfully deregistering the uri%s", TAG);
    }
}