/*
CyptoPals - Set 1

Functions created while completing challenges for Set 1

See also:
    linked_list.h / linked_list.c
*/

#ifndef SET1_H
#define SET1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*******************************************************************************
* DATA STRUCTURES
*******************************************************************************/

/* struct to store information about plaintext to score it */
typedef struct _candidate {
    char    *ciphertext;
    char    *plaintext;
    unsigned long     plain_length;
    double  score;
} Candidate;

/* nodes for a linked list */
typedef struct _node {
    void    *data;
    struct _node   *next;
} Node;

/* singly linked list */
typedef struct _list {
    Node    *head;
    Node    *tail;
    Node    *current;
    unsigned int size;
} LinkedList;


/*******************************************************************************
* FUNCTIONS
*   listed in order as they appear in set1.c
*******************************************************************************/

/* General Utilities */
void errExit(char *message);

/* Linked-List functions */
LinkedList *ListInit(void);
void insert_node(LinkedList *list, void *item);
void freeLinkedList(LinkedList *list);

/* Cryptography functions */
int getHexInt(char c);
char getHexChar(int num);
char *string_to_hexString(char *input);
char *hexString_to_base64String(char *input);
char *base64String_to_hexString(char *input);
int base64char_to_int(char c);
char *fixed_xor(char *buf1, char *buf2);
Candidate *createCandidateStruct(char *input);
void analyzeCandidate(Candidate *can);
int scorePlaintext(char *plaintext);
char *findHighestScore(LinkedList *list);
char *singleXOR_iterate(char *input);
char *encryptXor(char *plaintext, char *key);
int hammingDist(char *str1, char *str2);





#endif
