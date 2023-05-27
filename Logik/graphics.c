/*
 * File: graphics.c
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Source file containing graphics for the game Logik.
 * Contact: havlifil@gmail.com
 */

#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "conio2.h"
#include "logik.h"
#include "linkedList.h"
#include "constants.h"

// get command line width
int getCommandLineWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// get command line height
int getCommandLineHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return rows;
}

// set all colors to default and places cursor to 1,1
void setDefaultGraphics(){
    textbackground(0);
    textcolor(15);
    gotoxy(1,1);
}

// draw rectangle from x, y with current width and height
void drawRect(int x, int y, int width, int height, uint8_t color){
    textbackground(color);
    for(int i = 0; i<height; i++){
        gotoxy(x,y+i);
        for(int x = 0; x<width; x++){
            printf("  ");
        }
    }
}

/*---------*/
/* SCREENS */
/*---------*/

// SCREEN GAME

// draw combination
void drawCombination(int x, int y, char *p_combination, int combinationSize){
    uint8_t color;
    for(int i = 0; i<combinationSize; i++){
        switch(*(p_combination+i)){
        case PIN_RED:
            color = COLOR_RED;
            break;
        case PIN_BLUE:
            color = COLOR_BLUE;
            break;
        case PIN_YELLOW:
            color = COLOR_YELLOW;
            break;
        case PIN_GREEN:
            color = COLOR_GREEN;
            break;
        case PIN_MAGENTA:
            color = COLOR_MAGENTA;
            break;
        case PIN_GRAY:
            color = COLOR_GRAY;
            break;
        case PIN_BLACK:
            color = COLOR_BLACK;
            break;
        case PIN_WHITE:
            color = COLOR_WHITE;
            break;
        case PIN_NEUTRAL:
            color = COLOR_NEUTRAL;
            break;
        }
        drawRect(x+(i*8)+(i*2), y, 4, 4, color);
    }
}

// draw smaller combination with including informative pins
void drawCombinationSmall(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize){
    uint8_t color;
    for(int i = 0; i<combinationSize; i++){
        switch(*(p_combination+i)){
        case PIN_RED:
            color = COLOR_RED;
            break;
        case PIN_BLUE:
            color = COLOR_BLUE;
            break;
        case PIN_YELLOW:
            color = COLOR_YELLOW;
            break;
        case PIN_GREEN:
            color = COLOR_GREEN;
            break;
        case PIN_MAGENTA:
            color = COLOR_MAGENTA;
            break;
        case PIN_GRAY:
            color = COLOR_GRAY;
            break;
        case PIN_BLACK:
            color = COLOR_BLACK;
            break;
        case PIN_WHITE:
            color = COLOR_WHITE;
            break;
        case PIN_NEUTRAL:
            color = COLOR_NEUTRAL;
            break;
        }
        drawRect(x+(i*4)+i, y, 2, 2, color);
    }
    if(informativePins.guessedColorsInPositions !=0){
        for(int i = 0; i<informativePins.guessedColorsInPositions; i++){
            drawRect(x+(i*2)+i, y+3, 1, 1, COLOR_INFO_COLOR_IN_POSITION);
        }
    }
    if(informativePins.guessedColors !=0){
        for(int i = 0; i<informativePins.guessedColors; i++){
            drawRect(x+(informativePins.guessedColorsInPositions*3)+(i*2)+i, y+3, 1, 1, COLOR_INFO_COLOR);
        }
    }
}

// SCREEN SCOREBOARD

// print sorted scoreboard
void printScoreboard(LIST *p_list, int sortType){
    setDefaultGraphics();
    switch(sortType){
    case 0:
        bubbleSortListByID(p_list);
        break;
    case 1:
        bubbleSortListByName(p_list);
        break;
    case 2:
        bubbleSortListBySurname(p_list);
        break;
    case 3:
        bubbleSortListByScore(p_list);
        break;
    }
    NODE *p_actual = p_list->p_first;
    drawRect(1, 1, 29, 3, COLOR_WHITE);
    textbackground(COLOR_BLACK);
    if(sortType == 0){
        textbackground(COLOR_LIGHTGREEN);
    } else
        textbackground(COLOR_BLACK);
    gotoxy(2, 2);
    printf("ID   ");
    if(sortType == 1){
        textbackground(COLOR_LIGHTGREEN);
    } else
        textbackground(COLOR_BLACK);
    gotoxy(8, 2);
    printf("NAME               ");
    if(sortType == 2){
        textbackground(COLOR_LIGHTGREEN);
    } else
        textbackground(COLOR_BLACK);
    gotoxy(28, 2);
    printf("SURNAME            ");
    if(sortType == 3){
        textbackground(COLOR_LIGHTGREEN);
    } else
        textbackground(COLOR_BLACK);
    gotoxy(48, 2);
    printf("BESTSCORE");
    setDefaultGraphics();
    int row = 1;
    while(p_actual != NULL){
        gotoxy(2, (row*2)+2);
        printf("%d", p_actual->ID);
        gotoxy(8, (row*2)+2);
        printf("%s", p_actual->p_name);
        gotoxy(28, (row*2)+2);
        printf("%s", p_actual->p_surname);
        gotoxy(48, (row*2)+2);
        printf("%d", p_actual->bestScore);
        p_actual = p_actual->p_next;
        row++;
    }
}

// print YOU WON
void youWon(){
    int size[2];
    bool youWonInProgress = true;
    size[0] = getCommandLineWidth();
    size[1] = getCommandLineHeight();
    clrscr();
    gotoxy(size[0]/2-8, size[1]/2-6);
    printf("X   X XXXXX X   X");
    gotoxy(size[0]/2-8, size[1]/2-5);
    printf(" X X  X   X X   X");
    gotoxy(size[0]/2-8, size[1]/2-4);
    printf("  X   X   X X   X");
    gotoxy(size[0]/2-8, size[1]/2-3);
    printf("  X   X   X X   X");
    gotoxy(size[0]/2-8, size[1]/2-2);
    printf("  X   XXXXX XXXXX");
    gotoxy(size[0]/2-8, size[1]/2);
    printf("X   X XXXXX XX  X");
    gotoxy(size[0]/2-8, size[1]/2+1);
    printf("X   X X   X X X X");
    gotoxy(size[0]/2-8, size[1]/2+2);
    printf("X X X X   X X X X");
    gotoxy(size[0]/2-8, size[1]/2+3);
    printf(" X X  X   X X X X");
    gotoxy(size[0]/2-8, size[1]/2+4);
    printf(" X X  XXXXX X  XX");
    gotoxy(size[0]/2-12, size[1]/2+6);
    printf("Press [SPACE] to continue.");
    while(youWonInProgress){
        if(kbhit()){
            int pressedKey = getch(); // get pressed key
            switch(pressedKey){
            case 32:
                youWonInProgress = false;
                break;
            }
        }
    }
}

// print tournament result
void printTournamentResult(int result){
    int size[2];
    bool printTournamentResultInProgress = true;
    size[0] = getCommandLineWidth();
    size[1] = getCommandLineHeight();
    clrscr();
    switch(result){
    case 0:
        gotoxy(size[0]/2-11, size[1]/2-6);
        printf("XXXX  XXXXX XXXXX X   X");
        gotoxy(size[0]/2-11, size[1]/2-5);
        printf("X   X X   X X   X X   X");
        gotoxy(size[0]/2-11, size[1]/2-4);
        printf("X   X XXXXX XXXXX X X X");
        gotoxy(size[0]/2-11, size[1]/2-3);
        printf("X   X X X   X   X  X X ");
        gotoxy(size[0]/2-11, size[1]/2-2);
        printf("XXXX  X  XX X   X  X X ");
        gotoxy(size[0]/2-12, size[1]/2);
        printf("Press [SPACE] to continue.");
        break;
    case 1:
        gotoxy(size[0]/2-19, size[1]/2-6);
        printf("XXXXX X     XXXXX X   X XXXXX XXXXX   X");
        gotoxy(size[0]/2-19, size[1]/2-5);
        printf("X   X X     X   X  X X  X     X   X  XX");
        gotoxy(size[0]/2-19, size[1]/2-4);
        printf("XXXXX X     XXXXX   X   XXXXX XXXXX X X");
        gotoxy(size[0]/2-19, size[1]/2-3);
        printf("X     X     X   X   X   X     X X     X");
        gotoxy(size[0]/2-19, size[1]/2-2);
        printf("X     XXXXX X   X   X   XXXXX X  XX   X");
        gotoxy(size[0]/2-8, size[1]/2);
        printf("X   X XXXXX XX  X");
        gotoxy(size[0]/2-8, size[1]/2+1);
        printf("X   X X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+2);
        printf("X X X X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+3);
        printf(" X X  X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+4);
        printf(" X X  XXXXX X  XX");
        gotoxy(size[0]/2-12, size[1]/2+6);
        printf("Press [SPACE] to continue.");
        break;
    case 2:
        gotoxy(size[0]/2-20, size[1]/2-6);
        printf("XXXXX X     XXXXX X   X XXXXX XXXXX  XXX ");
        gotoxy(size[0]/2-20, size[1]/2-5);
        printf("X   X X     X   X  X X  X     X   X X   X");
        gotoxy(size[0]/2-20, size[1]/2-4);
        printf("XXXXX X     XXXXX   X   XXXXX XXXXX X   X");
        gotoxy(size[0]/2-20, size[1]/2-3);
        printf("X     X     X   X   X   X     X X      X");
        gotoxy(size[0]/2-20, size[1]/2-2);
        printf("X     XXXXX X   X   X   XXXXX X  XX XXXXX");
        gotoxy(size[0]/2-8, size[1]/2);
        printf("X   X XXXXX XX  X");
        gotoxy(size[0]/2-8, size[1]/2+1);
        printf("X   X X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+2);
        printf("X X X X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+3);
        printf(" X X  X   X X X X");
        gotoxy(size[0]/2-8, size[1]/2+4);
        printf(" X X  XXXXX X  XX");
        gotoxy(size[0]/2-12, size[1]/2+6);
        printf("Press [SPACE] to continue.");
        break;
    }
    while(printTournamentResultInProgress){
        if(kbhit()){
            int pressedKey = getch(); // get pressed key
            switch(pressedKey){
            case 32:
                printTournamentResultInProgress = false;
                break;
            }
        }
    }
}

// wrap text
void printWrappedText(const char* text, int lineWidth) {
    int textLength = strlen(text);
    int start = 0;

    while (start < textLength) {
        int end = start + lineWidth;

        if (end >= textLength) {
            end = textLength;
        }
        else {
            // Find the last space within the line width
            while (end > start && text[end] != ' ') {
                end--;
            }

            // If no space found, move to the next word
            if (end == start) {
                end = start + lineWidth;
            }
        }

        // Print the line
        for (int i = start; i < end; i++) {
            printf("%c", text[i]);
        }
        printf("\n");

        start = end + 1;
    }
}
