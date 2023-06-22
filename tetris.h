    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #include <time.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <Windows.h>
    #pragma once
    #define FIELD_WIDTH 11
    #define FIELD_HEIGHT 23
    #define DATUM_POINT_X 14
    #define DATUM_POINT_Y 2
    #define LEVEL_BOARD_POS_X 47
    #define LEVEL_BOARD_POS_Y 15
    #define SCORE_BOARD_POS_X 47
    #define SCORE_BOARD_POS_Y 10
    #define NEXT_POS_X 45
    #define NEXT_POS_Y 3
    typedef struct _BLOCK
    {
        int x;
        int y;
        struct _BLOCK* next;
    } BLOCK, * pBLOCK;
    void gotoxy(int x, int y);
    void StartingScreen();
    void GameScreen();
    void ShowConsoleCursor(bool showFlag);
    void ClearField(int field[FIELD_HEIGHT][FIELD_WIDTH]);
    void PrintField(int field[][FIELD_WIDTH]);
    void GameOver(int score, int level);
    void CreatBlock(pBLOCK blockHead);
    int CheckSide(pBLOCK blockHead, int direction);
    void PrintBlock(pBLOCK blockHead);
    void ClearBlock(pBLOCK blockHead);
    void DeleteLine(int field[FIELD_HEIGHT][FIELD_WIDTH], int lineNumber);
    int CheckFieldLine(int field[FIELD_HEIGHT][FIELD_WIDTH]);
    void MoveRight(pBLOCK blockHead);
    void MoveLeft(pBLOCK blockHead);
    void MoveDown(pBLOCK blockHead);
    void Drop(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH]);
    int GetDistance(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH]);
    void PutBlocksInField(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH]);
    void GameLoop();
