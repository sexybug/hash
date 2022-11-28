#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sm4.h"

void memory_dump(void *ptr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (i % 8 == 0 && i != 0)
            printf(" ");
        if (i % 16 == 0 && i != 0)
            printf("\n");
        printf("%02x ", *((uint8_t *)ptr + i));
    }
    printf("\n");
}

int main()
{
    uint8_t iv[] = {0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52};
    uint8_t key[] = "1234567812345678";
    int key_len = 16;
    uint8_t in[] = "1234567812345678";
    uint8_t out[16];
    SM4_Enc(out,in,key);
    memory_dump(out,16);
    return 0;
}