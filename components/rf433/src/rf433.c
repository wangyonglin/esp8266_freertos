#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
static const char *TAG = "rf433";
BaseType_t objRf433Parse(objRF433Pack_t *obj, uint8_t *dat, uint32_t dat_len)
{
    bzero(obj, sizeof(objRF433Pack_t));
    for (int i = 0; i <= (dat_len - 6); i++)
    {
        if ((dat[i] == 0xFD) && (dat[i + 5] == 0xDF))
        {
            obj->h = dat[i + 0];
            obj->a = dat[i + 1];
            obj->b = dat[i + 2];
            obj->k = dat[i + 3];
            obj->o = dat[i + 4];
            obj->f = dat[i + 5];
            return pdTRUE;
        }
    }
    return pdFALSE;
}
BaseType_t objRF433Add(objConfig_t *config, objRF433Pack_t obj)
{
    for (int i = 0; i < config->rf433_size; i++)
    {
        if ((config->rf433[i].a == obj.a) && (config->rf433[i].b == obj.b) && (config->rf433[i].k == obj.k))
        {
            return pdFALSE;
        }
        else if ((config->rf433[i].a != obj.a) && (config->rf433[i].b != obj.b) && (config->rf433[i].k != obj.k))
        {
            if ((config->rf433[i].a == 0x00) && (config->rf433[i].b == 0x00) && (config->rf433[i].k == 0x00))
            {
                config->rf433[i] = obj;
                objFlashRF433PacksSaveing(config);
                ESP_LOGI(TAG, "save 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", obj.h, obj.a, obj.b, obj.k, obj.o, obj.f);
                return pdTRUE;
            }
            return pdFALSE;
        }
    }
    return pdFALSE;
}

BaseType_t objRF433PackCheck(objConfig_t *config, objRF433Pack_t obj)
{

    objFlashRF433PacksGetting(config);
    for (int i = 0; i < config->rf433_size; i++)
    {
        if ((config->rf433[i].a == obj.a) && (config->rf433[i].b == obj.b) && (config->rf433[i].k == obj.k))
        {
            config->timer_control_clieck.bit = pdFALSE;
            ESP_LOGI(TAG, "cmd 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", obj.h, obj.a, obj.b, obj.k, obj.o, obj.f);
            return pdTRUE;
        }
    }
    return pdFALSE;
}