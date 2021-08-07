#ifndef __MESSAGEIFY_H
#define __MESSAGEIFY_H
#include <espify.h>
#include <configify.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct objMessage
    {
        Integerify_t level;
        Boolify_t trun;
        Stringify_t rf433[16];
        Stringify_t pvBuffer[1024];
    } objMessage_t;
    esp_err_t objMessageInit(objMessage_t *message);
    esp_err_t objMessageClean(objMessage_t *message);
    esp_err_t objMessageTrun(objMessage_t *message);
    esp_err_t objMessageRF433(objMessage_t *message);
#ifdef __cplusplus
}
#endif
#endif