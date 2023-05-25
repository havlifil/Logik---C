#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "conio2.h"
#include "constants.h"
#include "logik.h"
#include "linkedList.h"
#include "graphics.h"

void setNewUser(LIST *p_list, uint16_t bestScore){
    printf("Name: ");
    char *p_name = getNameSurname();
    printf("Surname: ");
    char *p_surname = getNameSurname();
    addToList(p_list, p_name, p_surname, bestScore);
}

uint16_t screenGame();
int screenHome();
void screenScoreboard(LIST *p_list);
void screenTournament();

int main()
{
    LIST *p_userList = createList();
    loadList(p_userList);
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    int actualScreen = -1;
    bool programRunning = true;
    uint16_t bestScore;
    while(programRunning){
        switch(actualScreen){
        case SCREEN_HOME:
            actualScreen = screenHome();
            break;
        case SCREEN_GAME:
            bestScore = screenGame();
            clrscr();
            setNewUser(p_userList, bestScore);
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_SCOREBOARD:
            clrscr();
            gotoxy(0,0);
            screenScoreboard(p_userList);
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_TOURNAMENT:
            screenTournament();
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_QUIT:
            programRunning = false;
            break;
        }
    }
    saveList(p_userList);
    freeList(p_userList);
    return 0;
}

int screenHome(){
    int width = getCommandLineWidth();
    int height = getCommandLineHeight();
    int menuIndex = 0;
    bool menuInProgress = true;
    bool change = true;
    char pressedKey;
    clrscr();
    while(menuInProgress){
        if(change==true){
            gotoxy(width/2-10,height/2-9);
            printf("MENU");
            drawRect(width/2-10,height/2-8,10,5,COLOR_WHITE);
            if(menuIndex == 0){
                drawRect(width/2-9,height/2-7,9,3,10);
            } else {
                drawRect(width/2-9,height/2-7,9,3,COLOR_BLACK);
            }
            gotoxy(width/2-6,height/2-6);
            textbackground(0);
            printf("PLAY");
            drawRect(width/2-10,height/2-4,10,5,COLOR_WHITE);
            if(menuIndex == 1){
                drawRect(width/2-9,height/2-3,9,3,10);
            } else {
                drawRect(width/2-9,height/2-3,9,3,COLOR_BLACK);
            }
            gotoxy(width/2-6,height/2-2);
            textbackground(0);
            printf("PLAYERS");
            drawRect(width/2-10,height/2,10,5,COLOR_WHITE);
            if(menuIndex == 2){
                drawRect(width/2-9,height/2+1,9,3,10);
            } else {
                drawRect(width/2-9,height/2+1,9,3,COLOR_BLACK);
            }
            gotoxy(width/2-6,height/2+2);
            textbackground(0);
            printf("TOURNAMENT");
            drawRect(width/2-10,height/2+4,10,5,COLOR_WHITE);
            if(menuIndex == 3){
                drawRect(width/2-9,height/2+5,9,3,10);
            } else {
                drawRect(width/2-9,height/2+5,9,3,COLOR_BLACK);
            }
            gotoxy(width/2-6,height/2+6);
            textbackground(0);
            printf("SAVE & QUIT");
            setDefaultGraphics();
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
                if(menuIndex>3){
                    menuIndex = 3;
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

uint16_t screenGame(){
    clrscr();
    // generating random right combination
    char rightCombination[COMBINATION_SIZE];
    generateCombination(rightCombination, COMBINATION_SIZE);
    // generating blank combination for users guesses
    char actualCombination[COMBINATION_SIZE];
    generateBlankCombination(actualCombination, COMBINATION_SIZE);
    INFORMATIVE_PINS informativePins; // structure with information about success of users guess
    informativePins.guessedColors = 0;
    informativePins.guessedColorsInPositions = 0;
    bool gameInProgress = true;
    bool change = true; // true if any graphics changes
    char pressedKey; // stores pressed key
    int pinIndex = 0; // index of pin which is user editing
    int numAttemps = 0;
    char **p_attempHistory = NULL;
    drawRect(69,1,25,100,3);
    while(gameInProgress){
        if(change == true){
            drawRect(1,1,25,8,3);
            drawRect((pinIndex*10)+1,1,5,6,10);
            drawCombination(2,2,actualCombination,COMBINATION_SIZE);
            for(int i = numAttemps-1; i>-1; i--){
                INFORMATIVE_PINS informativePins = checkCombination(rightCombination, p_attempHistory[i], COMBINATION_SIZE);
                drawCombinationSmall(70, ((numAttemps-1)*5+2)-(i*5), p_attempHistory[i], informativePins, COMBINATION_SIZE);
            }
            gotoxy(52,1);
            textbackground(0);
            printf("ATTEMPS: %d", numAttemps);
            gotoxy(1,20);
            printCombination(rightCombination, COMBINATION_SIZE);
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
                    if(informativePins.guessedColorsInPositions == 5){
                        gameInProgress = false;
                    }
                    numAttemps++;
                    if(p_attempHistory == NULL){
                        p_attempHistory = (char **)malloc(sizeof(char *));
                    } else {
                        p_attempHistory = (char **)realloc(p_attempHistory, numAttemps*sizeof(char *));
                    }
                    if(p_attempHistory == NULL){
                        printf("ERROR out of memory\n");
                        exit(-1);
                    }
                    p_attempHistory[numAttemps-1] = (char *) malloc(COMBINATION_SIZE*sizeof(char *));
                    if(p_attempHistory[numAttemps-1] == NULL){
                        printf("ERROR out of memory\n");
                        exit(-1);
                    }
                    for(int i = 0; i<COMBINATION_SIZE; i++){
                        *(p_attempHistory[numAttemps-1]+i) = actualCombination[i];
                    }
                    change = true;
                }
                break;
            }
        }
    }
    for(int i = 0; i<numAttemps; i++){
        free(p_attempHistory[i]);
    }
    free(p_attempHistory);
    return numAttemps;
}

void screenScoreboard(LIST *p_list){
    printScoreboard(p_list);
    bool scoreboardInProgress = true;
    while(scoreboardInProgress){
        if(kbhit()){
            char pressedKey = getch();
            if(pressedKey == 27){
                scoreboardInProgress = false;
            }
        }
    }
}

void screenTournament(){
    uint16_t score1 = screenGame();
    uint16_t score2 = screenGame();
    clrscr();
    if(score1==score2){
        printf("Draw");
    } else if (score1<score2) {
        printf("P1 won");
    } else {
        printf("P2 won");
    }
    bool tournamentInProgress = true;
    while(tournamentInProgress){
        if(kbhit()){
            char pressedKey = getch();
            if(pressedKey == 27){
                tournamentInProgress = false;
            }
        }
    }
}

