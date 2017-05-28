/*
CyptoPals - Set 1 - Challenge 2
https://cryptopals.com/sets/1/challenges/2

Fixed XOR:
Write a function that takes two equal-length buffers and produces their
XOR combination.

Compile: gcc set1.c 1-2_fixed_xor.c -o 1-2_fixed_xor

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set1.h"


int main(int argc, char **argv)
{
    char *buf1, *buf2, *answer;

    /* get command-line args or use defaults listed below */
    if (argc == 1) {
        buf1 = "1c0111001f010100061a024b53535009181c";
        buf2 = "686974207468652062756c6c277320657965";
    } else {
        buf1 = argv[1];
        buf2 = argv[2];
    }

    /* see set1.c   */
    answer = fixed_xor(buf1, buf2);

    printf("%s\n", answer);

    /* must free since it was dynamically allocated */
    free(answer);
    answer = NULL;
    return 0;
}
