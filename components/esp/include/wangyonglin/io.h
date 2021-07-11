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

#ifdef __cplusplus
}
#endif
#endif