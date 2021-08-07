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
#ifndef __STRINGIFY_H
#define __STRINGIFY_H

#include <espify.h>
#include <configify.h>
#ifdef __cplusplus
extern "C"
{
#endif
void strbytes(const char *hexString, unsigned char *bytes);
#ifdef __cplusplus
}
#endif
#endif