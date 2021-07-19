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
#define objTrunNone ((objTrun_t)-1)
#define objTrunOn ((objTrun_t)1)
#define objTrunOff ((objTrun_t)0)
    typedef struct objMessage
    {
        char *topic;
        int level;
        objTrun_t trun;
    } objMessage_t;
    esp_err_t objMessageInit(objMessage_t *message);
    esp_err_t objMessage(char *data, objMessage_t *message);
#ifdef __cplusplus
}
#endif
#endif