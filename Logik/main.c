#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "logik.h"
#include "linkedList.h"

int main()
{
    /*INFORMATIVE_PINS actualInformativePins;
    char combination[COMBINATION_SIZE];
    char actualCombination[COMBINATION_SIZE] = {PIN_BLUE, PIN_BLACK, PIN_BLACK, PIN_WHITE, PIN_GREEN};
    printf("Right combination:\n");
    getCombination(&combination[0], COMBINATION_SIZE);
    printCombination(&combination[0], COMBINATION_SIZE);
    printf("Guessed combination:\n");
    printCombination(&actualCombination[0], COMBINATION_SIZE);
    actualInformativePins = checkCombination(&combination[0], &actualCombination[0], COMBINATION_SIZE);
    printf("guessed positions+colors: %d\nguessed colors: %d\n", actualInformativePins.guessedColorsInPositions, actualInformativePins.guessedColors);*/

    LIST *p_userList = createList();
    p_userList->numNodes = 0;

    char buffer[1024];
    char *p_newNickname;
    for(int i = 0; i<15; i++){
        printf("New nickname:");
        scanf(" %1023[^\n]s", buffer);
        p_newNickname = (char *) malloc(strlen(buffer)+1);
        strcpy(p_newNickname, buffer);
        addToList(p_userList, p_newNickname);
    }
    NODE *p_actualNode = p_userList->p_first;
    while(p_actualNode != NULL){
        printf("%s\n", p_actualNode->p_nickname);
        p_actualNode = p_actualNode->p_next;
    }
    freeList(p_userList);
    return 0;
}
