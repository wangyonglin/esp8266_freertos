#ifndef __UARTIFY_H
#define __UARTIFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t objUartSend(Configify_t *config, uint8_t *data, uint32_t length);
    esp_err_t objUartStart(Configify_t *config);

#ifdef __cplusplus
}
#endif
#endif