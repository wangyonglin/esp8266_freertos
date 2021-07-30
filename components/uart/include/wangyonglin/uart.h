#ifndef WANGYONGLIN_UART_H
#define WANGYONGLIN_UART_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t objUartSend(objConfig_t *config, uint8_t *data, uint32_t length);
    esp_err_t objUartStart(objConfig_t *config);
#ifdef __cplusplus
}
#endif
#endif