#ifndef WANGYONGLIN_RF433_H
#define WANGYONGLIN_RF433_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif

BaseType_t objRf433PackParse(objRF433Pack_t *obj, uint8_t *dat, uint32_t dat_len);
BaseType_t objRF433PackAdd(objConfig_t *config, objRF433Pack_t obj);
BaseType_t objRF433PackCheck(objConfig_t *config,objRF433Pack_t obj);
#ifdef __cplusplus
}
#endif
#endif