#include <espify.h>
#include <configify.h>

extern const uint8_t web_file_index_css_start[] asm("_binary_index_css_start");
extern const uint8_t web_file_index_css_end[] asm("_binary_index_css_end");
static const char *TAG = "/index.css";
/* An HTTP GET handler */
esp_err_t index_css(httpd_req_t *req)
{
    httpd_resp_set_type(req,"text/css; charset=utf-8");
    char *str = web_file_index_css_start;
    unsigned int str_len = web_file_index_css_end - web_file_index_css_start;
    httpd_resp_send(req, str, str_len);
    return ESP_OK;
}

void objHttpdRegisterUriIndexCss(Configify_t *config)
{
    httpd_uri_t uri_t = {
        .uri = TAG,
        .method = HTTP_GET,
        .handler = index_css,
        .user_ctx = NULL,
    };
    if (httpd_register_uri_handler(config->httpd, &uri_t) == ESP_OK)
    {
        ESP_LOGI(TAG, "successfully registering the uri%s", TAG);
    }
}
void objHttpdUnRegisterUriIndexCss(Configify_t *config)
{
    if(httpd_unregister_uri_handler(config->httpd,TAG, HTTP_GET)==ESP_OK){
         ESP_LOGI(TAG, "successfully deregistering the uri%s", TAG);
    }
}