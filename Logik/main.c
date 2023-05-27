/*
 * File: main.c
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Main code file for the game Logik. Contains necessary libraries to run the game.
 * Contact: havlifil@gmail.com
 */

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

// functions declaration
uint16_t screenGame(char *p_label);
int screenHome();
void screenScoreboard(LIST *p_list);
void screenTournament();
void screenSetScore(LIST *p_list, uint16_t score);
void screenRules();

/*------*/
/* MAIN */
/*------*/

int main()
{
    LIST *p_userList = createList();
    loadList(p_userList);
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    int actualScreen = -1;
    bool programRunning = true;
    uint16_t bestScore;
    int actualSize[2]; // actual console size
    while(programRunning){
        // set actual values
        actualSize[0] = getCommandLineWidth();
        actualSize[1] = getCommandLineHeight();
        switch(actualScreen){
        case SCREEN_HOME:
            actualScreen = screenHome();
            break;
        case SCREEN_GAME:
            bestScore = screenGame("");
            if(bestScore != 0){
                clrscr();
                youWon();
                screenSetScore(p_userList, bestScore);
                saveList(p_userList);
                logScoreboard(p_userList);
            }
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_SCOREBOARD:
            clrscr();
            screenScoreboard(p_userList);
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_TOURNAMENT:
            screenTournament();
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_RULES:
            screenRules();
            actualScreen = SCREEN_HOME;
            break;
        case SCREEN_QUIT:
            clrscr();
            programRunning = false;
            break;
        }
    }
    saveList(p_userList);
    freeList(p_userList);
    return 0;
}

/*---------*/
/* SCREENS */
/*---------*/

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
            // print MENU label
            gotoxy(actualSize[0]/2-10,actualSize[1]/2-11);
            printf("MENU");
            // print PLAY item
            drawRect(actualSize[0]/2-10,actualSize[1]/2-10,10,5,COLOR_WHITE);
            if(menuIndex == 0){
                drawRect(actualSize[0]/2-9,actualSize[1]/2-9,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2-9,9,3,COLOR_BLACK);
            }
            gotoxy(actualSize[0]/2-6,actualSize[1]/2-8);
            textbackground(COLOR_BLACK);
            printf("PLAY");
            // print SCOREBOARD item
            drawRect(actualSize[0]/2-10,actualSize[1]/2-6,10,5,COLOR_WHITE);
            if(menuIndex == 1){
                drawRect(actualSize[0]/2-9,actualSize[1]/2-5,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2-5,9,3,COLOR_BLACK);
            }
            gotoxy(actualSize[0]/2-6,actualSize[1]/2-4);
            textbackground(COLOR_BLACK);
            printf("SCOREBOARD");
            // print TOURNAMENT item
            drawRect(actualSize[0]/2-10,actualSize[1]/2-2,10,5,COLOR_WHITE);
            if(menuIndex == 2){
                drawRect(actualSize[0]/2-9,actualSize[1]/2-1,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2-1,9,3,COLOR_BLACK);
            }
            gotoxy(actualSize[0]/2-6,actualSize[1]/2);
            textbackground(COLOR_BLACK);
            printf("TOURNAMENT");
            // print RULES item
            drawRect(actualSize[0]/2-10,actualSize[1]/2+2,10,5,COLOR_WHITE);
            if(menuIndex == 3){
                drawRect(actualSize[0]/2-9,actualSize[1]/2+3,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2+3,9,3,COLOR_BLACK);
            }
            gotoxy(actualSize[0]/2-6,actualSize[1]/2+4);
            textbackground(COLOR_BLACK);
            printf("RULES");
            // print SAVE & QUIT item
            drawRect(actualSize[0]/2-10,actualSize[1]/2+6,10,5,COLOR_WHITE);
            if(menuIndex == 4){
                drawRect(actualSize[0]/2-9,actualSize[1]/2+7,9,3,COLOR_LIGHTGREEN);
            } else {
                drawRect(actualSize[0]/2-9,actualSize[1]/2+7,9,3,COLOR_BLACK);
            }
            gotoxy(actualSize[0]/2-6,actualSize[1]/2+8);
            textbackground(COLOR_BLACK);
            printf("SAVE & QUIT");
            // print controls
            gotoxy(actualSize[0]/2-10,actualSize[1]/2+11);
            printf("control: [W]%c [S]%c", 24, 25);
            gotoxy(actualSize[0]/2-1,actualSize[1]/2+12);
            printf("[ENTER]confirm", 26);
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
                if(menuIndex>4){
                    menuIndex = 4;
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
uint16_t screenGame(char *p_label){
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
            printf("attempt: %d", numAttempts);
            if(strcasecmp(p_label, "")!=0){
                gotoxy(actualSize[0]/2-52,10);
                printf("%s", p_label);
            }
            // print controls
            gotoxy(actualSize[0]/2-52,15);
            printf("control: [W]%c [A]%c [S]%c [D]%c", 24,26,25,27);
            gotoxy(actualSize[0]/2-43,16);
            printf("[ENTER]confirm");
            gotoxy(actualSize[0]/2-43,17);
            printf("[ESC]exit");
            // print right combination (debug)
            /*gotoxy(1,1);
            printCombination(rightCombination, COMBINATION_SIZE);
            setDefaultGraphics();*/
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
                } else {
                    MessageBox(NULL, "You have to set all the pins first.", "Combination is not valid", MB_OK);
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
    int sortIndex = 0; //define type of sorting
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
            clrscr();
            printScoreboard(p_list, sortIndex);
            // print controls
            gotoxy(60,1);
            printf("control: [A]%c [D]%c", 27, 26);
            gotoxy(69,2);
            printf("[ESC]exit");
            setDefaultGraphics();
            change = false;
        }
        if(kbhit()){
            int pressedKey = getch(); // get pressed key
            switch(pressedKey){
            case 'a':
                sortIndex--;
                if(sortIndex<0){
                    sortIndex = 0;
                }
                change = true;
                break;
            case 'd':
                sortIndex++;
                if(sortIndex>3){
                    sortIndex = 3;
                }
                change = true;
                break;
            case 27:
                scoreboardInProgress = false;
                break;
            }
        }
    }
}

// start tournament
void screenTournament(){
    uint16_t score1 = screenGame("PLAYER 1");
    if(score1 == 0){
        return;
    }
    uint16_t score2 = screenGame("PLAYER 2");
    if(score2 == 0){
        return;
    }
    clrscr();
    if(score1==score2){
        printTournamentResult(0);
    } else if (score1<score2) {
        printTournamentResult(1);
    } else {
        printTournamentResult(2);
    }
    bool tournamentInProgress = true;
}

// save users score
void screenSetScore(LIST *p_list, uint16_t score){
    setDefaultGraphics();
    bool stringIsValid = false; // validity of string
    char buffer[NAMESURNAME_LENGTH+1];
    char *p_name, *p_surname;
    int size[2]; // size of console
    // get name and surname properly
    while(stringIsValid == false){
        // get current console size
        size[0] = getCommandLineWidth();
        size[1] = getCommandLineHeight();
        // print form
        clrscr();
        drawRect(size[0]/2-14,size[1]/2-1, 14, 3, COLOR_WHITE);
        gotoxy(size[0]/2-13,size[1]/2);
        textcolor(COLOR_WHITE);
        textbackground(COLOR_BLACK);
        printf("NAME:");
        gotoxy(size[0]/2-7,size[1]/2);
        printf("                    ");
        gotoxy(size[0]/2-7,size[1]/2);
        int ee = scanf(" %1023[^\n]s", buffer);
        if(ee = 0){
            printf("ERROR scanf\n");
            exit(-2);
        }
        stringIsValid = validateString(buffer);
        if(stringIsValid == false){
           MessageBox(NULL, "The name can only contain characters of the alphabet and can be up to 20 characters long.", "String is not valid", MB_OK);
        }
    }
    p_name = (char *) malloc((strlen(buffer)+1)*sizeof(char));
    if(p_name == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    strcpy(p_name, buffer);
    stringIsValid = false;
    while(stringIsValid == false){
        // get current console size
        size[0] = getCommandLineWidth();
        size[1] = getCommandLineHeight();
        // print form
        clrscr();
        drawRect(size[0]/2-16,size[1]/2-1, 16, 3, COLOR_WHITE);
        gotoxy(size[0]/2-15,size[1]/2);
        textcolor(COLOR_WHITE);
        textbackground(COLOR_BLACK);
        printf("SURNAME:");
        gotoxy(size[0]/2-6,size[1]/2);
        printf("                     ");
        gotoxy(size[0]/2-6,size[1]/2);
        int ee = scanf(" %1023[^\n]s", buffer);
        if(ee = 0){
            printf("ERROR scanf\n");
            exit(-2);
        }
        stringIsValid = validateString(buffer);
        if(stringIsValid == false){
           MessageBox(NULL, "The surname can only contain characters of the alphabet and can be up to 20 characters long.", "String is not valid", MB_OK);
        }
    }
    p_surname = (char *) malloc((strlen(buffer)+1)*sizeof(char));
    if(p_surname == NULL){
        printf("ERROR out of memory\n");
        exit(-1);
    }
    strcpy(p_surname, buffer);
    // write score to list
    bool userExists = false; // true if user already exists
    NODE *p_actual = p_list->p_first;
    NODE *p_user = NULL;
    if(p_actual == NULL){
        userExists = false;
    } else {
        while(p_actual != NULL){
            if(strcmp(p_actual->p_name, p_name) == 0){
                if(strcmp(p_actual->p_surname, p_surname) == 0){
                    userExists = true;
                    p_user = p_actual;
                    p_actual = NULL;
                }
            }
            if(userExists == false){
                p_actual = p_actual->p_next;
            }
        }
    }
    if(userExists == true){
        if(p_user->bestScore > score){
            p_user->bestScore = score;
        }
    } else {
        addToList(p_list, p_name, p_surname, score);
    }
}

// show rules
void screenRules(){
    bool rulesInProgress = true;
    const char *p_text = "The aim of the game is to guess the correct color combination in as few attempts as possible. You start by assembling the pins into an arbitrary color combination, where multiple pins of the same color can be included. The game then evaluates the correctness of this combination, displaying the result in the form of small pins. A black pin means that you have one of the right colors in the right place. A white pin means you have the correct color but it is misplaced. Use this information to make your next combination. The process repeats until you have guessed the correct combination.";
    setDefaultGraphics();
    clrscr();
    printWrappedText(p_text, 80);
    printf("\n[ESC]exit");
    while(rulesInProgress){
        if(kbhit()){
            int pressedKey = getch(); // get pressed key
            switch(pressedKey){
            case 27:
                rulesInProgress = false;
                break;
            }
        }
    }
}
