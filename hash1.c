#include "hash1.h"
#include "sm4.h"

/**
 * @brief u变换
 *
 * @param X 128比特输入
 * @param Y 128比特输出
 */
void u(uint8_t *X, uint8_t *Y)
{
    for (int i = 0; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}

/**
 * @brief 轮函数
 *
 * @param Dj
 * @param Hj_1 H(j-1)
 * @param Hj 输出
 */
void phi(uint8_t *Dj, uint8_t *Hj_1, uint8_t *Hj)
{
    uint8_t Kj[16];
    u(Hj_1, Kj);
    SM4_Enc(Hj, Dj, Kj);
    for (int i = 0; i < 16; ++i)
    {
        Hj[i] ^= Dj[i];
    }
}

/**
 * @brief 输出变换
 *
 * @param Hq 最终轮输出
 * @param LH 散列码H长度
 * @param H 散列码H
 */
void T(uint8_t *Hq, int LH, uint8_t *H)
{
    for (int i = 0; i < LH; i++)
    {
        H[i] = Hq[i];
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
void h(uint8_t *D, int D_len, uint8_t *IV, uint8_t *H)
{
    int q = D_len / 16;
    uint8_t Hj[16];
    phi(D, IV, Hj);
    for (int i = 1; i < q; i++)
    {
        phi(D + i * 16, Hj, Hj);
    }
    T(Hj,16,H);
}