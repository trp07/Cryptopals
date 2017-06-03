/*
CyptoPals - Set 1 - Challenge 5
https://cryptopals.com/sets/1/challenges/5

 Encrypt it, under the key "ICE", using repeating-key XOR.

In repeating-key XOR, you'll sequentially apply each byte of the key; the
first byte of plaintext will be XOR'd against I, the next C, the next E,
then I again for the 4th byte, and so on.

Compile: gcc set1.c  5_repeating_xor.c -o 5_repeating_xor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1.h"


int main(void)
{
    char *input = "Burning 'em, if you ain't quick and nimble\n"
                  "I go crazy when I hear a cymbal";

    char *result = encryptXor(input, "ICE");
    printf("%s\n", result);

    free(result);
    result = NULL;
    return 0;
}
