#ifndef __LIBIFY_H
#define __LIBIFY_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef int Integerify_t;
typedef unsigned char Stringify_t;
typedef signed int Errorify_t;
typedef int Boolify_t;

#define On ((Boolify_t)1)
#define Off ((Boolify_t)0)
#define None ((Boolify_t)-1)
#define ERRIFY_ERR_OK 0
#define ERRIFY_ERR_FAIL -1
#define ERRIFY_ERR_INVALID_OBJECT 0x101
#define ERRIFY_ERR_INVALID_ARG 0x102
#define IO00 0
#define IO01 1
#define IO02 2
#define IO03 3
#define IO05 5
#define IO14 14
#define IO16 16
#define EVENT_RF433_LEVEL 0x0002
#define EVENT_TRUN_LEVEL 0x0001
#ifdef __cplusplus
extern "C"
{
#endif
    Stringify_t *StringifyMalloc(int len);
    Errorify_t StringifyZero(Stringify_t *obj, size_t len);
    Errorify_t StringifyCopy(Stringify_t *obj, char *str, size_t len);
    Errorify_t StringifyFree(Stringify_t *obj);
    Errorify_t StringifyFormat(Stringify_t *obj, const char *format, ...);
#ifdef __cplusplus
}
#endif
#endif