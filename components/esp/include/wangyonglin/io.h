#ifndef WANGYONGLIN_STDLIB_H
#define WANGYONGLIN_STDLIB_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        objIOBoot = 4,
        objIOButton = 14
    } objGPIO_t;
    typedef uint32_t objIO_t;

#define objIOHigh ((objIO_t)1)
#define objIOLow ((objIO_t)0)
#define IO00 0
#define IO01 1
#define IO02 2
#define IO03 3
#define IO05 5
#define IO14 14
#define IO16 16
#ifdef __cplusplus
}
#endif
#endif