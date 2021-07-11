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
#include <cJSON.h>
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct objMessage{
    cJSON * root;
}objMessage_t;

objMessage_t *objMessageInit();
esp_err_t objMessageSkeleton(objMessage_t *obj, const char *id, double level);
char *objMessagePrint(objMessage_t *obj);

#ifdef __cplusplus
}
#endif
#endif