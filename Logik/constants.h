/*
 * File: constants.h
 * Author: Filip Havl�k
 * Last Modified: 27. 5. 2023
 * Description: Header file containing constants for the game Logik.
 * Contact: havlifil@gmail.com
 */

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// program setup
#define COMBINATION_SIZE 5
#define NAMESURNAME_LENGTH 20

// pins
#define PIN_RED 0b0
#define PIN_GREEN 0b1
#define PIN_BLUE 0b10
#define PIN_YELLOW 0b11
#define PIN_WHITE 0b100
#define PIN_BLACK 0b101
#define PIN_GRAY 0b110
#define PIN_MAGENTA 0b111
#define PIN_NEUTRAL 0b1000

// colors
#define COLOR_RED 4
#define COLOR_GREEN 2
#define COLOR_BLUE 1
#define COLOR_YELLOW 14
#define COLOR_WHITE 15
#define COLOR_BLACK 0
#define COLOR_GRAY 8
#define COLOR_MAGENTA 5
#define COLOR_NEUTRAL 7

#define COLOR_LIGHTGREEN 10
#define COLOR_CYAN 3

#define COLOR_INFO_COLOR 15
#define COLOR_INFO_COLOR_IN_POSITION 0

// screens
#define SCREEN_HOME -1
#define SCREEN_GAME 0
#define SCREEN_SCOREBOARD 1
#define SCREEN_TOURNAMENT 2
#define SCREEN_RULES 3
#define SCREEN_QUIT 4

#endif // CONSTANTS_H_INCLUDED
