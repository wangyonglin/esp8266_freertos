#ifndef WANGYONGLIN_UART_H
#define WANGYONGLIN_UART_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
    struct objUart
    {
        int baud_rate;
        uart_port_t uart_num;
    };
    typedef struct objUart objUart_t;
    esp_err_t objUartSend(uint8_t *data, uint32_t length);
    esp_err_t objUartInit(int baud_rate);
#ifdef __cplusplus
}
#endif
#endif