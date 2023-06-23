#include <stdio.h>
#include <conio.h>
#include <windows.h> // Windows에서 시간 지연을 위해 사용

#define MAP_WIDTH 20  // 게임 맵 가로 길이
#define MAP_HEIGHT 15 // 게임 맵 세로 길이

void bomb_gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void bomb_drawMap(int playerX, int playerY, int bombX[], int bombY[], int numBombs) {
    system("cls"); // 화면을 지우고 새로 그리기

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == playerX && y == playerY) {
                printf("\033[1;32m@\033[0m"); // 캐릭터 (@)
            }
            else {
                int isBomb = 0;
                for (int i = 0; i < numBombs; i++) {
                    if (x == bombX[i] && y == bombY[i]) {
                        isBomb = 1;
                        break;
                    }
                }
                if (isBomb) {
                    printf("\033[1;31m#\033[0m"); // 폭탄 (#)
                }
                else {
                    printf("."); // 빈 공간
                }
            }
        }
        printf("\n");
    }
}

int bomb() {
    int key;
    int playerX = MAP_WIDTH / 2; // 캐릭터의 초기 X 좌표
    int playerY = MAP_HEIGHT - 1; // 캐릭터의 초기 Y 좌표

    const int maxBombs = 10; // 최대 폭탄 개수
    int bombX[10]; // 폭탄들의 X 좌표 배열
    int bombY[10]; // 폭탄들의 Y 좌표 배열
    int numBombs = 0; // 현재 폭탄 개수

    int score = 0; // 점수
    int speed = 100; // 폭탄 속도 (밀리초)

    while (1) {
        bomb_drawMap(playerX, playerY, bombX, bombY, numBombs);
        bomb_gotoxy(0, MAP_HEIGHT);

        if (_kbhit()) { // 키보드 입력 체크
            key = _getch();

            if (key == 224) {
                key = _getch();

                switch (key) {
                case 75: // 왼쪽 화살표 키
                    if (playerX > 0) {
                        playerX--; // 왼쪽으로 이동
                    }
                    break;
                case 77: // 오른쪽 화살표 키
                    if (playerX < MAP_WIDTH - 1) {
                        playerX++; // 오른쪽으로 이동
                    }
                    break;
                }
            }
        }

        // 폭탄 위치 업데이트
        for (int i = 0; i < numBombs; i++) {
            if (bombY[i] >= MAP_HEIGHT) { // 폭탄이 바닥에 닿았을 때
                if (bombX[i] == playerX && bombY[i] == playerY) {
                    printf("\n\033[1;31mGame Over! Score: %d\n\033[0m", score);
                    return 0; // 게임 종료
                }
                else {
                    // 폭탄 삭제
                    for (int j = i; j < numBombs - 1; j++) {
                        bombX[j] = bombX[j + 1];
                        bombY[j] = bombY[j + 1];
                    }
                    numBombs--;
                }
            }
            else {
                bombY[i]++; // 폭탄이 아직 바닥에 닿지 않았으면 내려옴
            }
        }

        // 점수에 따라 폭탄 추가
        if (score % 10 == 0 && numBombs < maxBombs) {
            bombX[numBombs] = rand() % MAP_WIDTH;
            bombY[numBombs] = 0;
            numBombs++;
        }

        // 폭탄과 캐릭터 충돌 체크
        for (int i = 0; i < numBombs; i++) {
            if (bombX[i] == playerX && bombY[i] == playerY) {
                printf("\n\033[1;31mGame Over! Score: %d\n\033[0m", score);
                int ana;
                printf("해당 게임을 계속 플레이 할 것인가요?...네(1),아니요(0) :");
                scanf_s("%d", &ana);
                if (ana == 1) {
                    bomb();
                }
                else if (ana == 0) {
                    return 1;
                } // 게임 종료
            }
        }

        score++; // 점수 증가
        Sleep(speed); // 일정 시간 지연 (Windows에서 사용)
    }
    
}
