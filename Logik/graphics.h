/*
 * File: graphics.h
 * Author: Filip Havlík
 * Last Modified: 27. 5. 2023
 * Description: Header file containing function declaration for graphics.c.
 * Contact: havlifil@gmail.com
 */

#include <stdint.h>

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

extern int getCommandLineWidth();
extern int getCommandLineHeight();
extern void setDefaultGraphics();
extern void drawRect(int x, int y, int width, int height, uint8_t color);
extern void drawCombination(int x, int y, char *p_combination, int combinationSize);
extern void drawCombinationSmall(int x, int y, char *p_combination, INFORMATIVE_PINS informativePins, int combinationSize);
extern void printScoreboard(LIST *p_list, int sortType);
extern void youWon();
extern void printTournamentResult(int result);
extern void printWrappedText(const char* text, int lineWidth);

#endif // GRAPHICS_H_INCLUDED
