#include "hash2.h"
#include "sm4.h"
#include "test.h"
#include <stdio.h>

/**
 * @brief u变换
 *
 * @param X 128比特输入
 * @param Y 128比特输出
 */
void u1(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x7f;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}

/**
 * @brief u' 变换
 *
 * @param X 128比特输入
 * @param Y 128比特输出
 */
void u2(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] | 0x80;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}

/**
 * @brief 轮函数
 *
 * @param Dj 128比特分组
 * @param Hj_1 H(j-1) 2x128比特
 * @param Hj 输出 2x128比特
 */
void phi(const uint8_t *Dj, const uint8_t *Hj_1, uint8_t *Hj)
{
    uint8_t X[16];
    uint8_t Y[16];
    uint8_t Bj1[16], Bj2[16];
    u1(Hj_1, X);
    u2(Hj_1 + 16, Y);

    SM4_Enc(Bj1, Dj, X);
    for (int i = 0; i < 16; ++i)
    {
        Bj1[i] ^= Dj[i];
    }

    SM4_Enc(Bj2, Dj, Y);
    for (int i = 0; i < 16; ++i)
    {
        Bj2[i] ^= Dj[i];
    }

    for (int i = 0; i < 8; ++i)
    {
        Hj[i] = Bj1[i];
    }
    for (int i = 8; i < 16; ++i)
    {
        Hj[i] = Bj2[i];
    }
    for (int i = 0; i < 8; ++i)
    {
        Hj[16 + i] = Bj2[i];
    }
    for (int i = 8; i < 16; ++i)
    {
        Hj[16 + i] = Bj1[i];
    }
}

/**
 * @brief 输出变换
 *
 * @param Hq 最终轮输出
 * @param LH 散列码H长度
 * @param H 散列码H
 */
void T(const uint8_t *Hq, int LH, uint8_t *H)
{
    const uint8_t *HqL = Hq;
    const uint8_t *HqR = Hq + 16;
    if (LH % 2 == 0)
    {
        for (int i = 0; i < LH / 2; i++)
        {
            H[i] = HqL[i];
        }
        for (int i = 0; i < LH / 2; i++)
        {
            H[LH / 2 + i] = HqR[i];
        }
    }
    else
    {
        for (int i = 0; i < (LH + 1) / 2; i++)
        {
            H[i] = HqL[i];
        }
        for (int i = 0; i < (LH - 1) / 2; i++)
        {
            H[(LH + 1) / 2 + i] = HqR[i];
        }
    }
}

/**
 * @brief 散列函数
 *
 * @param D 数据（填充后）
 * @param D_len 数据长度
 * @param IV 初始化值
 * @param H 散列码
 */
void h(const uint8_t *D, int D_len, const uint8_t *IV, uint8_t *H)
{
    int q = D_len / 16;
    uint8_t Hj[32];
    phi(D, IV, Hj);
    printf("j=1,Hj:\n");
    memory_dump(Hj, 32);
    for (int i = 1; i < q; i++)
    {
        phi(D + i * 16, Hj, Hj);
        printf("j=%d,Hj:\n", i + 1);
        memory_dump(Hj, 32);
    }
    T(Hj, 32, H);
}