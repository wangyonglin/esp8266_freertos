#ifndef WANGYONGLIN_BUTTON_H
#define WANGYONGLIN_BUTTON_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

struct wang_button
{
   void(*event_cb_t)(int8_t id,void *ctx);
};
typedef struct wang_button wang_button_t;

void wang_button_set(void (*event_cb_t)(int8_t id, void *ctx));
#ifdef __cplusplus
}
#endif
#endif