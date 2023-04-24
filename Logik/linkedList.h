#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct node {
    char *p_nickname; // nickname saved in the node
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    int numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

extern LIST *createList();
extern void freeList(LIST *p_list);
extern NODE *addToList(LIST *p_list, char *p_nickname);

#endif // LINKEDLIST_H_INCLUDED
