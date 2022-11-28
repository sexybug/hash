#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t *a="abcd";
    uint8_t *b1=a,*b2=a+1;

    printf("%c\n",*b1);
    printf("%c\n",*b2);
    return 0;
}