/*
CyptoPals - Set 1 - Challenge 4
https://cryptopals.com/sets/1/challenges/4

One of the 60-character strings in the file "4_input.txt" has been encrypted
by single-character XOR.  Find it.

Compile: gcc set1.c 4_detect_single_xor.c -o 4_detect_single_xor

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1.h"


int main(void)
{
    /* open the input file 4_input.txt */
    FILE *fin;
    fin = fopen("4_input.txt", "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        exit(EXIT_FAILURE);
    }

    /* vars for 'getline'   */
    ssize_t read;
    char *line = NULL;
    size_t n;

    /* vars to find the encrypted text */
    char *current = NULL;
    char *winner = (char *) malloc(sizeof(char) * 60 + 1);
    int best_score = 0;
    int score = 0;

    while ((read = getline(&line, &n, fin)) != -1) {
        if (line[read - 1] == '\n')
            line[read - 1] =  '\0';

        current = singleXOR_iterate(line);

        score = scorePlaintext(current);
        if (score > best_score) {
            best_score = score;
            strcpy(winner, current);
        }

        free(current);
    }

    printf("%s\n", winner);

    fclose(fin);
    free(winner);
    free(line);
    return 0;
}
