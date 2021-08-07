#ifndef __RF433IFY_H
#define __RF433IFY_H
#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif

    BaseType_t objRf433PackParse(objRF433Pack_t *obj, uint8_t *dat, uint32_t dat_len);
    BaseType_t objRF433PackAdd(Configify_t *config, objRF433Pack_t obj);
    BaseType_t objRF433PackCheck(Configify_t *config, objRF433Pack_t obj);
    
#ifdef __cplusplus
}
#endif
#endif