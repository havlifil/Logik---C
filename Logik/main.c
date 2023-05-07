#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "conio2.h"
#include "constants.h"
#include "logik.h"
#include "linkedList.h"
#include "graphics.h"

void setNewUser(LIST *p_list){
    printf("Name: ");
    char *p_name = getString();
    printf("Surname: ");
    char *p_surname = getString();
    addToList(p_list, p_name, p_surname);
}

void screenGame();
int screenHome();

int main()
{
    LIST *p_list = createList();
    p_list = generateRandomList(10);
    printList(p_list);
    freeList(p_list);
    /*ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    int actualScreen = -1;
    bool programRunning = true;
    while(programRunning){
        switch(actualScreen){
        case SCREEN_HOME:
            actualScreen = screenHome();
            break;
        case SCREEN_GAME:
            screenGame();
            break;
        case SCREEN_SCOREBOARD:
            break;
        }
    }*/
    return 0;
}

int screenHome(){
    int menuIndex = 0;
    bool menuInProgress = true;
    bool change = true;
    char pressedKey;
    clrscr();
    while(menuInProgress){
        if(change==true){
            gotoxy(10,10);
            printf("MENU");
            drawRect(10,11,10,5,COLOR_WHITE);
            if(menuIndex == 0){
                drawRect(11,12,9,3,10);
            } else {
                drawRect(11,12,9,3,COLOR_BLACK);
            }
            gotoxy(12,13);
            textbackground(0);
            printf("PLAY");
            drawRect(10,15,10,5,COLOR_WHITE);
            if(menuIndex == 1){
                drawRect(11,16,9,3,10);
            } else {
                drawRect(11,16,9,3,COLOR_BLACK);
            }
            gotoxy(12,17);
            textbackground(0);
            printf("PLAYERS");
            change = false;
        }
        if(kbhit()){
            pressedKey = getch();
            switch(pressedKey){
            case 'w':
                menuIndex--;
                if(menuIndex<0){
                    menuIndex = 0;
                }
                change = true;
                break;
            case 's':
                menuIndex++;
                if(menuIndex>1){
                    menuIndex = 1;
                }
                change = true;
                break;
            case '\r':
                return menuIndex;
                break;
            }
        }
    }
}

void screenGame(){
    clrscr();
    // generating random right combination
    char rightCombination[COMBINATION_SIZE];
    generateCombination(rightCombination, COMBINATION_SIZE);
    // generating blank combination for users guesses
    char actualCombination[COMBINATION_SIZE];
    generateBlankCombination(actualCombination, COMBINATION_SIZE);
    INFORMATIVE_PINS informativePins; // structure with information about success of users guess
    bool gameInProgress = true;
    bool change = true; // true if any graphics changes
    char pressedKey; // stores pressed key
    int pinIndex = 0; // index of pin which is user editing
    int numAttemps = 0;
    drawRect(69,1,25,100,3);
    while(gameInProgress){
        if(change == true){
            drawRect(1,1,25,8,3);
            drawRect((pinIndex*10)+1,1,5,6,10);
            drawCombination(2,2,actualCombination,informativePins,COMBINATION_SIZE);
            gotoxy(52,1);
            textbackground(0);
            printf("ATTEMPS: %d", numAttemps);
            change = false;
        }
        if(kbhit()){
            pressedKey = getch();
            switch(pressedKey){
            case 'w':
                actualCombination[pinIndex]++;
                if(actualCombination[pinIndex]>7){
                    actualCombination[pinIndex] = 0;
                }
                change = true;
                break;
            case 's':
                actualCombination[pinIndex]--;
                if(actualCombination[pinIndex]<0){
                    actualCombination[pinIndex] = 7;
                }
                change = true;
                break;
            case 'a':
                if(pinIndex>0){
                    pinIndex--;
                }
                change = true;
                break;
            case 'd':
                if(pinIndex<COMBINATION_SIZE-1){
                    pinIndex++;
                }
                change = true;
                break;
            case '\r':
                if(combinationIsValid(actualCombination, COMBINATION_SIZE)){
                    informativePins = checkCombination(rightCombination, actualCombination, COMBINATION_SIZE);
                    numAttemps++;
                    drawCombinationSmall(70, 2+((numAttemps-1)*5), actualCombination, informativePins, COMBINATION_SIZE);
                    change = true;
                }
                break;
            }
        }
    }
}
