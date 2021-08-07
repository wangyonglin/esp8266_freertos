#ifndef __MQTTIFY_H
#define __MQTTIFY_H

#include <espify.h>
#include <configify.h>

#ifdef __cplusplus
extern "C"
{
#endif

void MqttifyInit(Configify_t *config);
#ifdef __cplusplus
}
#endif
#endif