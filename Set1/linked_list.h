/*
Utility functions to use a linked list
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H


/*******************************************************************************
* DATA STRUCTURES
*******************************************************************************/

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
*******************************************************************************/

LinkedList *ListInit(void);
void insert_node(LinkedList *list, void *item);
void freeLinkedList(LinkedList *list);









#endif
