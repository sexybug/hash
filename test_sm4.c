#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sm4.h"
#include "test.h"

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