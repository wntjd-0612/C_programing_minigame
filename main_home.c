#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"
int num_bb();
int rsp();
int main() {
    int n;
    printf("하실 게임을 입력하십시오.\n 1, 숫자야구\n 2, 테트리스\n 3, 가위 바위 보\n 4, 똥 피하기\n5, 승부차기 게임\n 6, 두더지 게임\n 7, 홈으로 가기\n8, 게임 끝내기\n");
    scanf_s("%d", &n);
    switch (n)
    {
    case(1): num_bb(); break;
    case(2):  tetris();  break;
    case(3): rsp();  break;
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

    return 0;
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
        return 1;
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

    return 0;
}
