#include <stdint.h>

#include "conio2.h"
#include "constants.h"

void drawRect(int x, int y, int width, int height, uint8_t color){
    textbackground(color);
    for(int i = 0; i<height; i++){
        gotoxy(x,y+i);
        for(int x = 0; x<width; x++){
            printf("  ");
        }
    }
}
