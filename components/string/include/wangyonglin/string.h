/**
 * @file message.h
 * @author 王永林 (admin@wangyonglin.com)
 * @brief 
 * @version 1.0.0
 * @date 2021年07月11日
 * 
 * @copyright Copyright (c) 1988-2021 wangyonglin.com. All rights reserved.
 * 
 */
#ifndef WANGYONGLIN_STRING_STRING_H
#define WANGYONGLIN_STRING_STRING_H

#include <wangyonglin/esp.h>
#include <wangyonglin/wangyonglin.h>
#ifdef __cplusplus
extern "C"
{
#endif
typedef unsigned char objByte_t;
void strbytes(const char *hexString, unsigned char *bytes);
#ifdef __cplusplus
}
#endif
#endif