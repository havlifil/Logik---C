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

// functions declaration
uint16_t screenGame();
int screenHome();
void screenScoreboard(LIST *p_list);
void screenTournament();

int main()
{
    LIST *p_userList = generateRandomList(10);//createList();
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
            if(bestScore != 0){
                clrscr();
                setNewUser(p_userList, bestScore);
            }
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

// show main menu
int screenHome(){
    // SETUP
    int menuIndex = 0; // index of menu item
    bool menuInProgress = true; // if true, the menu screen is still running
    bool change = true; // if true, print screen
    int oldSize[2]; // console size before last change
    int actualSize[2]; // actual console size
    // set old console size to actual values
    oldSize[0] = getCommandLineWidth();
    oldSize[1] = getCommandLineHeight();
    clrscr();
    // LOOP
    while(menuInProgress){
        // set actual size to actual values
        actualSize[0] = getCommandLineWidth();
        actualSize[1] = getCommandLineHeight();
        // if console size has changed, print screen
        if(actualSize[0] != oldSize[0]||actualSize[1] != oldSize[1]){
            oldSize[0] = actualSize[0];
            oldSize[1] = actualSize[1];
            clrscr();
            change = true;
        }
        // print screen
        if(change==true){
            // print MENU item
            gotoxy(actualSize[0]/2-10,actualSize[1]/2-9);
            printf("MENU");
            drawRect(actualSize[0]/2-10,actualSize[1]/2-8,10,5,COLOR_WHITE);
            if(menuIndex == 0){
                drawRect(actualSize[0]/2-9,actualSize[1]/2-7,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2-7,9,3,COLOR_BLACK);
            }
            // print PLAY item
            gotoxy(actualSize[0]/2-6,actualSize[1]/2-6);
            textbackground(COLOR_BLACK);
            printf("PLAY");
            drawRect(actualSize[0]/2-10,actualSize[1]/2-4,10,5,COLOR_WHITE);
            if(menuIndex == 1){
                drawRect(actualSize[0]/2-9,actualSize[1]/2-3,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2-3,9,3,COLOR_BLACK);
            }
            // print SCOREBOARD item
            gotoxy(actualSize[0]/2-6,actualSize[1]/2-2);
            textbackground(COLOR_BLACK);
            printf("SCOREBOARD");
            drawRect(actualSize[0]/2-10,actualSize[1]/2,10,5,COLOR_WHITE);
            if(menuIndex == 2){
                drawRect(actualSize[0]/2-9,actualSize[1]/2+1,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2+1,9,3,COLOR_BLACK);
            }
            // print TOURNAMENT item
            gotoxy(actualSize[0]/2-6,actualSize[1]/2+2);
            textbackground(COLOR_BLACK);
            printf("TOURNAMENT");
            drawRect(actualSize[0]/2-10,actualSize[1]/2+4,10,5,COLOR_WHITE);
            if(menuIndex == 3){
                drawRect(actualSize[0]/2-9,actualSize[1]/2+5,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2+5,9,3,COLOR_BLACK);
            }
            // print SAVE & QUIT item
            gotoxy(actualSize[0]/2-6,actualSize[1]/2+6);
            textbackground(COLOR_BLACK);
            printf("SAVE & QUIT");
            setDefaultGraphics();
            change = false;
        }
        // user control
        if(kbhit()){
            int pressedKey = getch(); // get pressed key
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

// start game
uint16_t screenGame(){
    // SETUP
    // generating random right combination
    char rightCombination[COMBINATION_SIZE];
    generateCombination(rightCombination, COMBINATION_SIZE);
    // generating blank combination for users guesses
    char actualCombination[COMBINATION_SIZE];
    generateBlankCombination(actualCombination, COMBINATION_SIZE);
    // structure with information about success of users guess
    INFORMATIVE_PINS informativePins;
    informativePins.guessedColors = 0;
    informativePins.guessedColorsInPositions = 0;
    bool gameInProgress = true; // if true, the game screen is still running
    bool change = true; // if true, print screen
    int pinIndex = 0; // index of selected pin
    int numAttempts = 0; // number of attempts
    char **p_attemptHistory = NULL; // history of all attempts
    int oldSize[2]; // console size before last change
    int actualSize[2]; // actual console size
    // set old console size to actual values
    oldSize[0] = getCommandLineWidth();
    oldSize[1] = getCommandLineHeight();
    clrscr();
    // LOOP
    while(gameInProgress){
        // set actual size to actual values
        actualSize[0] = getCommandLineWidth();
        actualSize[1] = getCommandLineHeight();
        // if console size has changed, print screen
        if(actualSize[0] != oldSize[0]||actualSize[1] != oldSize[1]){
            oldSize[0] = actualSize[0];
            oldSize[1] = actualSize[1];
            clrscr();
            change = true;
        }
        // print screen
        if(change == true){
            // draw combination
            drawRect(actualSize[0]/2-52,1,26,8,COLOR_CYAN);// draw background rect
            drawRect((actualSize[0]/2-52)+(pinIndex*10)+1,2,5,6,COLOR_LIGHTGREEN);// draw bounding rect
            drawCombination(actualSize[0]/2-50,3,actualCombination,COMBINATION_SIZE);// draw combination
            // drew attempt history
            for(int i = numAttempts-1; i>-1; i--){
                INFORMATIVE_PINS informativePins = checkCombination(rightCombination, p_attemptHistory[i], COMBINATION_SIZE);
                drawRect(actualSize[0]/2+1,((numAttempts-1)*5+1)-(i*5),14,6,COLOR_CYAN);
                drawCombinationSmall(actualSize[0]/2+3, ((numAttempts-1)*5+2)-(i*5), p_attemptHistory[i], informativePins, COMBINATION_SIZE);
            }
            gotoxy(actualSize[0]/2-52,9);
            textbackground(COLOR_BLACK);
            printf("Attempt: %d", numAttempts);
            gotoxy(1,1);
            printCombination(rightCombination, COMBINATION_SIZE);
            setDefaultGraphics();
            change = false;
        }
        // user control
        if(kbhit()){
            char pressedKey = getch();
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
                    // if combination right, end game
                    if(informativePins.guessedColorsInPositions == 5){
                        gameInProgress = false;
                    }
                    numAttempts++;
                    // add item to attempt history
                    if(p_attemptHistory == NULL){
                        p_attemptHistory = (char **)malloc(sizeof(char *));
                    } else {
                        p_attemptHistory = (char **)realloc(p_attemptHistory, numAttempts*sizeof(char *));
                    }
                    if(p_attemptHistory == NULL){
                        printf("ERROR out of memory\n");
                        exit(-1);
                    }
                    p_attemptHistory[numAttempts-1] = (char *) malloc(COMBINATION_SIZE*sizeof(char *));
                    if(p_attemptHistory[numAttempts-1] == NULL){
                        printf("ERROR out of memory\n");
                        exit(-1);
                    }
                    for(int i = 0; i<COMBINATION_SIZE; i++){
                        *(p_attemptHistory[numAttempts-1]+i) = actualCombination[i];
                    }
                    change = true;
                }
                break;
            case 27:
                return 0;
                break;
            }
        }
    }
    // free allocated memory
    for(int i = 0; i<numAttempts; i++){
        free(p_attemptHistory[i]);
    }
    free(p_attemptHistory);
    return numAttempts;
}

// show scoreboard
void screenScoreboard(LIST *p_list){
    bool scoreboardInProgress = true;
    bool change = true;
    int oldSize[2]; // console size before last change
    int actualSize[2]; // actual console size
    // set old console size to actual values
    oldSize[0] = getCommandLineWidth();
    oldSize[1] = getCommandLineHeight();
    clrscr();
    while(scoreboardInProgress){
        // set actual size to actual values
        actualSize[0] = getCommandLineWidth();
        actualSize[1] = getCommandLineHeight();
        // if console size has changed, print screen
        if(actualSize[0] != oldSize[0]||actualSize[1] != oldSize[1]){
            oldSize[0] = actualSize[0];
            oldSize[1] = actualSize[1];
            clrscr();
            change = true;
        }
        if(change == true){
            printScoreboard(p_list);
            change = false;
        }
        if(kbhit()){
            char pressedKey = getch();
            if(pressedKey == 27){
                scoreboardInProgress = false;
            }
        }
    }
}

// start tournament
void screenTournament(){
    uint16_t score1 = screenGame();
    if(score1 == 0){
        return;
    }
    uint16_t score2 = screenGame();
    if(score2 == 0){
        return;
    }
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

