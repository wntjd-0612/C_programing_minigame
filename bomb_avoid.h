#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 15

void bomb_gotoxy(int x, int y);
void bomb_drawMap(int playerX, int playerY, int bombX[], int bombY[], int numBombs);
int bomb();


