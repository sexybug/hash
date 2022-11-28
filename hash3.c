#include "hash3.h"
#include <string.h>
#include "sm4.h"
#include "test.h"
#include <stdio.h>

/**
 * @brief 异或， C = A XOR B
 *
 * @param A
 * @param B
 * @param n 输入长度
 * @param C 输出
 */
void XOR(const uint8_t *A, const uint8_t *B, int n, uint8_t *C)
{
    for (int i = 0; i < n; ++i)
    {
        C[i] = A[i] ^ B[i];
    }
}

/**
 * @brief u1变换
 *
 * @param X 128比特输入
 * @param Y 128比特输出
 */
void u1(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f;
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
    Y[0] = X[0] & 0x1f | 0x20;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u3(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0x40;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u4(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0x60;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u5(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0x80;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u6(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0xa0;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u7(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0xc0;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u8(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x1f | 0xe0;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}

/**
 * @brief 线性映射
 *
 * @param X 2x128比特输入
 * @param Y 2x128比特输出
 */
void beta(const uint8_t *X, uint8_t *Y)
{
    uint8_t *x0 = X, *x1 = X + 8, *x2 = X + 16, *x3 = X + 24;
    uint8_t *y0 = Y, *y1 = Y + 8, *y2 = Y + 16, *y3 = Y + 24;
    for (int i = 0; i < 8; i++)
    {
        y0[i] = x0[i] ^ x3[i];
        y1[i] = x0[i] ^ x1[i] ^ x3[i];
        y2[i] = x1[i] ^ x2[i];
        y3[i] = x2[i] ^ x3[i];
    }
}

void gamma1_step2(const uint8_t *l1, const uint8_t *l2, const uint8_t *l3, const uint8_t *l4,
                  const uint8_t *l5, const uint8_t *l6, const uint8_t *l7, const uint8_t *l8,
                  const uint8_t *l9, const uint8_t *l10, const uint8_t *l11, const uint8_t *l12,
                  uint8_t *M0, uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5,
                  uint8_t *R0, uint8_t *R1)
{
    for (int i = 0; i < 16; ++i)
    {
        M0[i] = l1[i];
        M0[16 + i] = l2[i];

        M1[i] = l3[i];
        M1[16 + i] = l4[i];

        M2[i] = l5[i];
        M2[16 + i] = l6[i];

        M3[i] = l7[i];
        M3[16 + i] = l8[i];

        M4[i] = l9[i];
        M4[16 + i] = l10[i];

        M5[i] = l11[i];
        M5[16 + i] = l12[i];
    }
    memset(R0, 0, 32);
    memset(R1, 0, 32);
}

void gamma1_step3(const uint8_t *M0, const uint8_t *M1, const uint8_t *M2,
                  const uint8_t *M3, const uint8_t *M4, const uint8_t *M5,
                  uint8_t *R0, uint8_t *R1)
{
    uint8_t B[32], beta_B[32];

    XOR(R1, M0, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }

    XOR(R1, M1, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }

    XOR(R1, M2, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }

    XOR(R1, M3, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }

    XOR(R1, M4, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }

    XOR(R1, M5, 32, B);
    beta(B, beta_B);
    XOR(R0, beta_B, 32, R1);
    for (int i = 0; i < 32; i++)
    {
        R0[i] = B[i];
    }
}

void gamma1_step4(const uint8_t *l1, const uint8_t *l2, const uint8_t *l3, const uint8_t *l4,
                  const uint8_t *l5, const uint8_t *l6, const uint8_t *l7, const uint8_t *l8,
                  const uint8_t *l9, const uint8_t *l10, const uint8_t *l11, const uint8_t *l12,
                  const uint8_t *R0, const uint8_t *R1,
                  uint8_t *X1, uint8_t *X2, uint8_t *X3, uint8_t *X4, uint8_t *X5, uint8_t *X6, uint8_t *X7, uint8_t X8,
                  uint8_t *Y1, uint8_t *Y2, uint8_t *Y3, uint8_t *Y4, uint8_t *Y5, uint8_t *Y6, uint8_t *Y7, uint8_t *Y8)
{
    memcpy(X1, l1, 16);
    memcpy(X2, l2, 16);
    memcpy(X3, l3, 16);
    memcpy(X4, l4, 16);
    memcpy(X5, l5, 16);
    memcpy(X6, l6, 16);
    memcpy(X7, l7, 16);
    memcpy(X8, l8, 16);

    memcpy(Y1, R0, 16);
    memcpy(Y2, R0 + 16, 16);
    memcpy(Y3, R1, 16);
    memcpy(Y4, R1 + 16, 16);
    memcpy(Y5, l9, 16);
    memcpy(Y6, l10, 16);
    memcpy(Y7, l11, 16);
    memcpy(Y8, l12, 16);
}

void gamma1(const uint8_t *H1, const uint8_t *H2, const uint8_t *H3, const uint8_t *H4,
            const uint8_t *H5, const uint8_t *H6, const uint8_t *H7, const uint8_t *H8,
            const uint8_t *Dj1, const uint8_t *Dj2, const uint8_t *Dj3, const uint8_t *Dj4,
            uint8_t *Xj1, uint8_t *Xj2, uint8_t *Xj3, uint8_t *Xj4, uint8_t *Xj5, uint8_t *Xj6, uint8_t *Xj7, uint8_t Xj8,
            uint8_t *Yj1, uint8_t *Yj2, uint8_t *Yj3, uint8_t *Yj4, uint8_t *Yj5, uint8_t *Yj6, uint8_t *Yj7, uint8_t *Yj8)
{
    uint8_t M0[32], M1[32], M2[32], M3[32], M4[32], M5[32], R0[32], R1[32];

    gamma1_step2(H1, H2, H3, H4, H5, H6, H7, H8, Dj1, Dj2, Dj3, Dj4, M0, M1, M2, M3, M4, M5, R0, R1);
    gamma1_step3(M0, M1, M2, M3, M4, M5, R0, R1);
    gamma1_step4(H1, H2, H3, H4, H5, H6, H7, H8, Dj1, Dj2, Dj3, Dj4,
                 R0, R1,
                 Xj1, Xj2, Xj3, Xj4, Xj5, Xj6, Xj7, Xj8, Yj1, Yj2, Yj3, Yj4, Yj5, Yj6, Yj7, Yj8);
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