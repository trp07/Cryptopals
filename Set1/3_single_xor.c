/*
CyptoPals - Set 1 - Challenge 3
https://cryptopals.com/sets/1/challenges/3

input has been XOR'd against a single character. Find the key, decrypt the
message.

Compile: gcc set1.c linked_list.c 3_single_xor.c -o 3_single_xor

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1.h"
#include "linked_list.h"


/******************************************************************************/
int main(void)
{
    char *input = "1b37373331363f78151b7f2b783431333d78397828"
                  "372d363c78373e783a393b3736";

    char *result = singleXOR_iterate(input);
    printf("%s\n", result);

    /* 'result' is dynamically allocated in 'singleXOR_interate'  */
    free(result);
    return 0;
}
