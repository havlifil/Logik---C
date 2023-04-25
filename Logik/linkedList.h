#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct node {
    char *p_name;
    char *p_surname;
    int ID;
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    int numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

extern LIST *createList();
extern void freeList(LIST *p_list);
extern NODE *addToList(LIST *p_list, char *p_name, char *p_surname);
extern void printList(LIST *p_list);
extern LIST *generateRandomList(int numNodes);
extern char *getString();

#endif // LINKEDLIST_H_INCLUDED
