/**
 * @file app.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月10日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_MAIN_MQTT_H
#define WANGYONGLIN_MAIN_MQTT_H
#include <wangyonglin/queue.h>
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
void objMqttInit(objConfig_t *config);
#ifdef __cplusplus
}
#endif
#endif