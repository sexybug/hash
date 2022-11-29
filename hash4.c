#include "hash4.h"
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
    Y[0] = X[0] & 0x0f;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u2(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x10;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u3(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x20;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u4(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x30;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u5(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x40;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u6(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x50;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u7(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x60;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u8(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x70;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}
void u9(const uint8_t *X, uint8_t *Y)
{
    Y[0] = X[0] & 0x0f | 0x80;
    for (int i = 1; i < 16; ++i)
    {
        Y[i] = X[i];
    }
}

/**
 * @brief f1
 *
 * @param X 128比特输入
 * @param Y 128比特输入
 * @param H 128比特输出
 */
void f1(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u1(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f2(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u2(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f3(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u3(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f4(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u4(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f5(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u5(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f6(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u6(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f7(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u7(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f8(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u8(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}
void f9(const uint8_t *X, const uint8_t *Y, uint8_t *H)
{
    uint8_t K[16];
    u9(X, K);
    SM4_Enc(H, X, K);
    XOR(H, Y, 16, H);
}

/**
 * @brief 线性映射
 *
 * @param X 2x128比特输入
 * @param Y 2x128比特输出
 */
void beta(const uint8_t *X, uint8_t *Y)
{
    const uint8_t *x0 = X, *x1 = X + 8, *x2 = X + 16, *x3 = X + 24;
    uint8_t *y0 = Y, *y1 = Y + 8, *y2 = Y + 16, *y3 = Y + 24;
    for (int i = 0; i < 8; i++)
    {
        y0[i] = x0[i] ^ x3[i];
        y1[i] = x0[i] ^ x1[i] ^ x3[i];
        y2[i] = x1[i] ^ x2[i];
        y3[i] = x2[i] ^ x3[i];
    }
}

void gamma2_step2(const uint8_t *l1, const uint8_t *l2, const uint8_t *l3, const uint8_t *l4,
                  const uint8_t *l5, const uint8_t *l6, const uint8_t *l7, const uint8_t *l8,
                  const uint8_t *l9, const uint8_t *l10, const uint8_t *l11, const uint8_t *l12,
                  uint8_t *M0, uint8_t *M1, uint8_t *M2, uint8_t *M3, uint8_t *M4, uint8_t *M5,
                  uint8_t *R0, uint8_t *R1, uint8_t *R2)
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
    memset(R2, 0, 32);
}

void gamma2_step3(const uint8_t *M0, const uint8_t *M1, const uint8_t *M2,
                  const uint8_t *M3, const uint8_t *M4, const uint8_t *M5,
                  uint8_t *R0, uint8_t *R1, uint8_t *R2)
{
    uint8_t B[32], U[32];

    XOR(R2, M0, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);

    XOR(R2, M1, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);

    XOR(R2, M2, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);

    XOR(R2, M3, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);

    XOR(R2, M4, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);

    XOR(R2, M5, 32, B);
    beta(B, U);
    XOR(R1, U, 32, R2);
    XOR(R0, U, 32, R1);
    memcpy(R0, B, 32);
}

void gamma2_step4(const uint8_t *l1, const uint8_t *l2, const uint8_t *l3, const uint8_t *l4,
                  const uint8_t *l5, const uint8_t *l6, const uint8_t *l7, const uint8_t *l8,
                  const uint8_t *l9, const uint8_t *l10, const uint8_t *l11, const uint8_t *l12,
                  const uint8_t *R0, const uint8_t *R1, const uint8_t *R2,
                  uint8_t *X1, uint8_t *X2, uint8_t *X3, uint8_t *X4, uint8_t *X5, uint8_t *X6, uint8_t *X7, uint8_t *X8, uint8_t *X9,
                  uint8_t *Y1, uint8_t *Y2, uint8_t *Y3, uint8_t *Y4, uint8_t *Y5, uint8_t *Y6, uint8_t *Y7, uint8_t *Y8, uint8_t *Y9)
{
    memcpy(X1, l1, 16);
    memcpy(X2, l2, 16);
    memcpy(X3, l3, 16);
    memcpy(X4, l4, 16);
    memcpy(X5, l5, 16);
    memcpy(X6, l6, 16);
    memcpy(X7, l7, 16);
    memcpy(X8, l8, 16);
    memcpy(X9, l9, 16);

    memcpy(Y1, R0, 16);
    memcpy(Y2, R0 + 16, 16);
    memcpy(Y3, R1, 16);
    memcpy(Y4, R1 + 16, 16);
    memcpy(Y5, R2, 16);
    memcpy(Y6, R2 + 16, 16);
    memcpy(Y7, l10, 16);
    memcpy(Y8, l11, 16);
    memcpy(Y9, l12, 16);
}

void gamma2(const uint8_t *H1, const uint8_t *H2, const uint8_t *H3, const uint8_t *H4,
            const uint8_t *H5, const uint8_t *H6, const uint8_t *H7, const uint8_t *H8, const uint8_t *H9,
            const uint8_t *Dj1, const uint8_t *Dj2, const uint8_t *Dj3,
            uint8_t *Xj1, uint8_t *Xj2, uint8_t *Xj3, uint8_t *Xj4, uint8_t *Xj5, uint8_t *Xj6, uint8_t *Xj7, uint8_t *Xj8, uint8_t *Xj9,
            uint8_t *Yj1, uint8_t *Yj2, uint8_t *Yj3, uint8_t *Yj4, uint8_t *Yj5, uint8_t *Yj6, uint8_t *Yj7, uint8_t *Yj8, uint8_t *Yj9)
{
    uint8_t M0[32], M1[32], M2[32], M3[32], M4[32], M5[32], R0[32], R1[32], R2[32];

    gamma2_step2(H1, H2, H3, H4, H5, H6, H7, H8, H9, Dj1, Dj2, Dj3, M0, M1, M2, M3, M4, M5, R0, R1, R2);
    gamma2_step3(M0, M1, M2, M3, M4, M5, R0, R1, R2);
    gamma2_step4(H1, H2, H3, H4, H5, H6, H7, H8, H9, Dj1, Dj2, Dj3,
                 R0, R1, R2,
                 Xj1, Xj2, Xj3, Xj4, Xj5, Xj6, Xj7, Xj8, Xj9, Yj1, Yj2, Yj3, Yj4, Yj5, Yj6, Yj7, Yj8, Yj9);
}

void phi(const uint8_t *Hj_11, const uint8_t *Hj_12, const uint8_t *Hj_13, const uint8_t *Hj_14,
         const uint8_t *Hj_15, const uint8_t *Hj_16, const uint8_t *Hj_17, const uint8_t *Hj_18, const uint8_t *Hj_19,
         const uint8_t *Dj1, const uint8_t *Dj2, const uint8_t *Dj3,
         uint8_t *Hj1, uint8_t *Hj2, uint8_t *Hj3, uint8_t *Hj4,
         uint8_t *Hj5, uint8_t *Hj6, uint8_t *Hj7, uint8_t *Hj8, uint8_t *Hj9)
{
    uint8_t Xj1[16], Xj2[16], Xj3[16], Xj4[16], Xj5[16], Xj6[16], Xj7[16], Xj8[16], Xj9[16];
    uint8_t Yj1[16], Yj2[16], Yj3[16], Yj4[16], Yj5[16], Yj6[16], Yj7[16], Yj8[16], Yj9[16];

    gamma2(Hj_11, Hj_12, Hj_13, Hj_14, Hj_15, Hj_16, Hj_17, Hj_18, Hj_19,
           Dj1, Dj2, Dj3,
           Xj1, Xj2, Xj3, Xj4, Xj5, Xj6, Xj7, Xj8, Xj9,
           Yj1, Yj2, Yj3, Yj4, Yj5, Yj6, Yj7, Yj8, Yj9);

    f1(Xj1, Yj1, Hj1);
    f2(Xj2, Yj2, Hj2);
    f3(Xj3, Yj3, Hj3);
    f4(Xj4, Yj4, Hj4);
    f5(Xj5, Yj5, Hj5);
    f6(Xj6, Yj6, Hj6);
    f7(Xj7, Yj7, Hj7);
    f8(Xj8, Yj8, Hj8);
    f8(Xj9, Yj9, Hj9);
}

/**
 * @brief 输出变换
 *
 * @param H 散列码H
 */
void T(const uint8_t *Hq1, const uint8_t *Hq2, const uint8_t *Hq3, const uint8_t *Hq4,
       const uint8_t *Hq5, const uint8_t *Hq6, const uint8_t *Hq7, const uint8_t *Hq8, const uint8_t *Hq9,
       uint8_t *H)
{
    uint8_t D1[16], D2[16], D3[16];
    uint8_t Hj1[16], Hj2[16], Hj3[16], Hj4[16], Hj5[16], Hj6[16], Hj7[16], Hj8[16], Hj9[16];

    //第1轮
    for (int i = 0; i < 16; ++i)
    {
        D1[i] = Hq1[i];
        D2[i] = Hq2[i];
        D3[i] = Hq3[i];
    }
    phi(Hq1, Hq2, Hq3, Hq4, Hq5, Hq6, Hq7, Hq8, Hq9, D1, D2, D3,
        Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);
    //第2轮
    for (int i = 0; i < 16; ++i)
    {
        D1[i] = Hq4[i];
        D2[i] = Hq5[i];
        D3[i] = Hq6[i];
    }
    phi(Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9, D1, D2, D3,
        Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);
    //第3轮
    for (int i = 0; i < 16; ++i)
    {
        D1[i] = Hq7[i];
        D2[i] = Hq8[i];
        D3[i] = Hq9[i];
    }
    phi(Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9, D1, D2, D3,
        Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);
    //第4轮
    for (int i = 0; i < 16; ++i)
    {
        D1[i] = Hq1[i];
        D2[i] = Hq2[i];
        D3[i] = Hq3[i];
    }
    phi(Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9, D1, D2, D3,
        Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);

    for (int i = 0; i < 16; ++i)
    {
        H[i] = Hj1[i];
        H[16 + i] = Hj2[i];
        H[32 + i] = Hj3[i];
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
    int q = D_len / 48;
    uint8_t Hj1[16], Hj2[16], Hj3[16], Hj4[16], Hj5[16], Hj6[16], Hj7[16], Hj8[16], Hj9[16];
    phi(IV, IV + 16, IV + 16 * 2, IV + 16 * 3, IV + 16 * 4, IV + 16 * 5, IV + 16 * 6, IV + 16 * 7, IV + 16 * 8,
        D, D + 16, D + 16 * 2,
        Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);
    printf("j=1,Hj:\n");
    memory_dump(Hj1, 16);
    memory_dump(Hj2, 16);
    memory_dump(Hj3, 16);
    memory_dump(Hj4, 16);
    memory_dump(Hj5, 16);
    memory_dump(Hj6, 16);
    memory_dump(Hj7, 16);
    memory_dump(Hj8, 16);
    memory_dump(Hj9, 16);
    for (int i = 1; i < q; i++)
    {
        phi(Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9, D + 48 * i, D + 48 * i + 16, D + 48 * i + 16 * 2,
            Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9);
        printf("j=%d,Hj:\n", i + 1);
        memory_dump(Hj1, 16);
        memory_dump(Hj2, 16);
        memory_dump(Hj3, 16);
        memory_dump(Hj4, 16);
        memory_dump(Hj5, 16);
        memory_dump(Hj6, 16);
        memory_dump(Hj7, 16);
        memory_dump(Hj8, 16);
        memory_dump(Hj9, 16);
    }
    T(Hj1, Hj2, Hj3, Hj4, Hj5, Hj6, Hj7, Hj8, Hj9, H);
}