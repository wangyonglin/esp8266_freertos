/**
 * @file message.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月11日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_MESSAGE_H
#define WANGYONGLIN_MESSAGE_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef int objTrun_t;
#define On ((objTrun_t)1)
#define Off ((objTrun_t)0)
#define None ((objTrun_t)-1)
    typedef unsigned char objData_t;
    typedef struct objMessage
    {
        int level;
        objTrun_t trun;
        objData_t rf433[16];
        objData_t pvBuffer[1024];
    } objMessage_t;
    esp_err_t objMessageInit(objMessage_t *message);
    esp_err_t objMessageClean(objMessage_t *message);
    esp_err_t objMessageTrun(objMessage_t *message);
    esp_err_t objMessageRF433(objMessage_t *message);
#ifdef __cplusplus
}
#endif
#endif