#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include "bomb_avoid.h"
#include "tetris.h"

int num_bb();
int rsp();
int main() {
    int n;
    while (1) {
        printf("하실 게임을 입력하십시오.\n 1, 숫자야구\n 2, 테트리스\n 3, 가위 바위 보\n 4, 폭탄 피하기\n 5, 게임 끝내기\n");
        scanf_s("%d", &n);
        switch (n)
        {
        case(1): num_bb(); Sleep(1000); system("cls");break;
        case(2):  tetris(); Sleep(1000); system("cls");  break;
        case(3): rsp(); Sleep(1000); system("cls"); break;
        case(4): bomb(); Sleep(1000); system("cls"); break;
        case(5): return 0;
        }
    }

}
int num_bb() {
    int answer[3];
    int guess[3];
    int strike = 0;
    int ball = 0;


    answer[0] = rand() % 9 + 1;
    do {
        answer[1] = rand() % 10;
    } while (answer[0] == answer[1]);
    do {
        answer[2] = rand() % 10;
    } while (answer[0] == answer[2] || answer[1] == answer[2]);

    printf("게임을 시작합니다!\n");


    while (strike != 3) {

        printf("3자리 숫자를 입력하세요 (중복 없이): ");
        scanf_s("%1d%1d%1d", &guess[0], &guess[1], &guess[2]);
        strike = 0;
        ball = 0;


        for (int i = 0; i < 3; i++) {
            if (guess[i] == answer[i]) {
                strike++;
            }
            else {
                for (int j = 0; j < 3; j++) {
                    if (guess[i] == answer[j]) {
                        ball++;
                        break;
                    }
                }
            }
        }


        printf("결과: %d 스트라이크, %d 볼\n\n", strike, ball);
    }

    printf("축하합니다! 정답을 맞추셨습니다.\n");
    int ana;
    printf("해당 게임을 계속 플레이 할 것인가요?...네(1),아니요(0) :");
    scanf_s("%d", &ana);
    if (ana == 1) {
        system("cls");
        num_bb();
    }
    else if (ana == 0) {
        return 0;
    }
}

int rsp() {
    int userChoice, computerChoice;

    printf("가위(1), 바위(2), 보(3) 중 하나를 선택하세요: ");
    scanf_s("%d", &userChoice);
    computerChoice = rand() % 3 + 1;
    printf("사용자: ");
    switch (userChoice) {
    case 1:
        printf("가위\n");
        break;
    case 2:
        printf("바위\n");
        break;
    case 3:
        printf("보\n");
        break;
    default:
        printf("잘못된 선택\n");
        rsp();
    }

    printf("컴퓨터: ");
    switch (computerChoice) {
    case 1:
        printf("가위\n");
        break;
    case 2:
        printf("바위\n");
        break;
    case 3:
        printf("보\n");
        break;
    }


    if (userChoice == computerChoice) {
        printf("비겼습니다!\n");
    }
    else if (
        (userChoice == 1 && computerChoice == 3) ||
        (userChoice == 2 && computerChoice == 1) ||
        (userChoice == 3 && computerChoice == 2)
        ) {
        printf("사용자가 이겼습니다!\n");
    }
    else {
        printf("컴퓨터가 이겼습니다!\n");
    }
    int ana;
    printf("해당 게임을 계속 플레이 할 것인가요?...네(1),아니요(0) :");
    scanf_s("%d", &ana);
    if (ana == 1) {
        rsp();
    }
    else if(ana==0){
        return 1;
    }
}
