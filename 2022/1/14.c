#include<stdio.h>
int main(void)
{
    unsigned char a = 4 | 7;
    a <<= 3;
    unsigned char b = 5 & 7;
    b >>= 3;
    unsigned char c = 6 ^ 7;
    c = ~c;
    unsigned short d = (a ^ c) << 3;
    signed char e = -63;
    e <<= 2;
    printf("%hu",d);
    printf("a:%d , b:%d , c:%d , d:%d\n", a, b, c, (char)d);
    printf("e:%#x\n", e);
}