/*
CyptoPals - Set 1 - Challenge 1
https://cryptopals.com/sets/1/challenges/1

Convert hex to base64

Good reference on Base64:
https://en.wikipedia.org/wiki/Base64

Compile: gcc set1.c 1-1_hex_to_base64.c -o 1-1_hex_to_base64
*/

#include <stdio.h>
#include <stdlib.h>
#include "set1.h"


int main(void)
{
    /* TEST CODE */

    char *input = "49276d206b696c6c696e6720796f757220627261696e206c696b"
              "65206120706f69736f6e6f7573206d757368726f6f6d";

    /* see set1.c   */
    char *output = hexString_to_base64String(input);

    printf("%s\n", output);

    /* free 'output' since it was dynamically allocated in
    'hexString_to_base64String()'   */
    free(output);
    output = NULL;
    return 0;
}
