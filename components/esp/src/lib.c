#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <libify.h>

Stringify_t *StringifyMalloc(int len)
{
    Stringify_t *obj = (Stringify_t *)malloc(sizeof(Stringify_t *) * len);
    bzero(obj, sizeof(Stringify_t *) * len);
    return obj;
}
Errorify_t StringifyCopy(Stringify_t *obj, char *str, size_t len)
{
    memcpy(obj, str, len);
    return ERRIFY_ERR_OK;
}
Errorify_t StringifyFree(Stringify_t *obj)
{
    if (obj != NULL)
    {
        free(obj);
    }
    return ERRIFY_ERR_OK;
}
Errorify_t StringifyFormat(Stringify_t *obj, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    sprintf((char *)obj, format, args);
    va_end(args);
    return ERRIFY_ERR_OK;
}
