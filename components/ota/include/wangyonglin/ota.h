/**
 * @file ota.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月11日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_OTA_H
#define WANGYONGLIN_OTA_H
#include <wangyonglin/esp.h>
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief 开启OTA远程下载更新固件
 * 
 * @return esp_err_t 
 */
esp_err_t objOtaStart(char *url);
#ifdef __cplusplus
}
#endif
#endif