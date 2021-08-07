#include <espify.h>
#include <configify.h>
extern const uint8_t web_file_index_html_start[] asm("_binary_index_html_start");
extern const uint8_t web_file_index_html_end[] asm("_binary_index_html_end");
static const char *TAG = "/index.html";
/* An HTTP GET handler */
esp_err_t index_html(httpd_req_t *req)
{
    char *str = web_file_index_html_start;
    unsigned int str_len = web_file_index_html_end - web_file_index_html_start;
    httpd_resp_send(req, str, str_len);
    return ESP_OK;
}

void objHttpdRegisterUriIndexHtml(Configify_t *config)
{
    httpd_uri_t uri_t = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = index_html,
        .user_ctx = NULL,
    };
    if (httpd_register_uri_handler(config->httpd, &uri_t) == ESP_OK)
    {
        ESP_LOGI(TAG, "successfully registering the uri%s", TAG);
    }
}
void objHttpdUnRegisterUriIndexHtml(Configify_t *config)
{
    if(httpd_unregister_uri_handler(config->httpd, "/", HTTP_GET)==ESP_OK){
         ESP_LOGI(TAG, "successfully deregistering the uri%s", "/");
    }
}