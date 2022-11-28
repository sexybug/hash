#ifndef _HASH1_H
#define _HASH1_H

#include <stdint.h>

/**
 * @brief 散列函数
 *
 * @param D 数据（填充后）
 * @param D_len 数据长度
 * @param IV 初始化值
 * @param H 散列码
 */
void h(uint8_t *D, int D_len, uint8_t *IV, uint8_t *H);

#endif // _HASH1_H