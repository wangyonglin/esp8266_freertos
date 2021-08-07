#ifndef __QUEUEIFY_H
#define __QUEUEIFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t objQueueInit(Configify_t *config, MqttCallback_t cb);
#ifdef __cplusplus
}
#endif
#endif