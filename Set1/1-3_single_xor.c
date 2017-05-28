/*
CyptoPals - Set 1 - Challenge 3
https://cryptopals.com/sets/1/challenges/3

input has been XOR'd against a single character. Find the key, decrypt the
message.

Compile: gcc set1.c linked_list.c 1-3_single_xor.c -o 1-3_single_xor

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1.h"
#include "linked_list.h"

void printHighestScore(LinkedList *list)
{
    /* function that will print the candidate's plaintext with the highest
       score.     */

    double score = 0;
    Candidate *tmp, *can;

    list->current = list->head;
    while (list->current != NULL) {
        tmp = (Candidate *) list->current->data;

        if (tmp->score > score) {
            can = tmp;
            score = can->score;
            //printf("score: %f\n", score);
        }

        list->current = list->current->next;
    }

    printf("%s\n", can->plaintext);
}


/******************************************************************************/
int main(void)
{
    char *input = "1b37373331363f78151b7f2b783431333d78397828"
                  "372d363c78373e783a393b3736";

    int INPUT_LEN = strlen(input);
    int *INPUT_ARR = (int *) malloc(sizeof(int) * (INPUT_LEN / 2));
    int index = 0;

    /* create an array of numerical representation of the input string */
    for (int i = 0; i < INPUT_LEN; i += 2) {
        /* see set1.c for getHexInt  */
        INPUT_ARR[index++] = getHexInt(input[i]) * 16 + getHexInt(input[i + 1]);
    }

    LinkedList *list = ListInit();

    char byte;     /* xor string against this */
    int num;

    for (int i = 0; i < 128; i++) { /* iterate through ASCII char 0-127  */
        byte = (char) i;
        Candidate *can = createCandidateStruct(input);  // set1.c
        index = 0;

        for (int j = 0; j < INPUT_LEN / 2; j++) { /* iterate through INPUT_ARR */
            num = INPUT_ARR[j];
            num ^= byte;
            can->plaintext[index++] = (char) num;
        }

        /* add Candidate to LinkedList (see linked_list.c) */
        insert_node(list, (void *) can);

        /* analyze plaintext and 'score' it (see set1.c)*/
        analyzeCandidate(can);
    }

    printHighestScore(list);

    freeLinkedList(list);
    free(INPUT_ARR);
    INPUT_ARR = NULL;
    return 0;
}
