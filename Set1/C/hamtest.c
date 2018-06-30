#include <stdio.h>
#include "set1.h"

int main(void)
{
    char *str1 = "this is a test";
    char *str2 = "wokka wokka!!!";

    int ham = hammingDist(str1, str2);
    printf("hamming = %d\n", ham);

    return 0;
}
