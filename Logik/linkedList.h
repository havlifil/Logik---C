/*
 * File: linkedList.h
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Header file containing function declaration for linkedList.c.
 * Contact: havlifil@gmail.com
 */


#include <stdint.h>

#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct node {
    char *p_name;
    char *p_surname;
    uint16_t ID;
    uint16_t bestScore;
    struct node *p_next; // address of the next node
} NODE;

typedef struct {
    uint16_t numNodes; // number of nodes in the list
    NODE *p_first; // address of the first node
    NODE *p_last; // address of the last node
} LIST;

extern LIST *createList();
extern void freeList(LIST *p_list);
extern NODE *addToList(LIST *p_list, char *p_name, char *p_surname, uint16_t bestScore);
extern void printList(LIST *p_list);
extern LIST *generateRandomList(int numNodes);
extern void saveList(LIST *p_list);
extern void *loadList();
extern bool validateString(char *p_string);
extern char *getNameSurname();
extern void setNewUser(LIST *p_list, uint16_t bestScore);
extern void toLower(char *p_string);
extern void swapNodes(LIST *p_list, NODE *p_nodeBefore, NODE *p_node1, NODE *p_node2);
extern void bubbleSortListByID(LIST *p_list);
extern void bubbleSortListByScore(LIST *p_list);
extern void bubbleSortListByName(LIST *p_list);
extern void bubbleSortListBySurname(LIST *p_list);
extern void logScoreboard(LIST *p_list);

#endif // LINKEDLIST_H_INCLUDED
