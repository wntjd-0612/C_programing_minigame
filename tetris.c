#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>


#define FIELD_WIDTH 11
#define FIELD_HEIGHT 23

//필드 좌상단 좌료 (14,2), next Block 좌상단 좌표(48,2)
//레벨인쇄할곳 좌표(47,9), 점수인쇄좌표(47,13)
#define DATUM_POINT_X 14
#define DATUM_POINT_Y 2
#define LEVEL_BOARD_POS_X 47
#define LEVEL_BOARD_POS_Y 15
#define SCORE_BOARD_POS_X 47
#define SCORE_BOARD_POS_Y 10
#define NEXT_POS_X 45
#define NEXT_POS_Y 3


//테트리스 블럭 1칸
typedef struct _BLOCK
{
    int x;
    int y;
    struct _BLOCK* next;
}BLOCK, * pBLOCK;



//콘솔에서 커서위치 설정
void gotoxy(int x, int y)
{
    COORD POS;
    POS.X = x;
    POS.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}

//시작화면출력
void StartingScreen()
{

    while (1)
    {
        gotoxy(30, 20);
        printf("Press any key to Start");
        Sleep(500);
        gotoxy(30, 20);
        printf("                            ");
        Sleep(500);
        if (kbhit() != 0)
        {
            getch();
            break;
        }
    }
}

//게임화면 테두리 및 화면 구성요소 출력 
void GameScreen()
{
    gotoxy(0, 0);
    puts("┌────────────────────────────────────────────────────────────────────────────────┐");
    puts("│           ┌───────────┐        ┌  NEXT BLOCK  ────┐             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       └───────────┘             │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │                                              │");
    puts("│           │                       │       ┌  CONTROLS  ─────┐             │");
    puts("│           │                       │       │ 블럭이동:←→↓      │             │");
    puts("│           │                       │       │ 회전 : ↑            │             │");
    puts("│           │                       │       │ 드랍 : SPACEBAR      │             │");
    puts("│           │                       │       │                      │             │");
    puts("│           │                       │       │ 종료 : Q             │             │");
    puts("│           └───────────────────────┘       └──────────────────────┘             │");
    puts("└────────────────────────────────────────────────────────────────────────────────┘");

}

//콘솔에서 커서 안보이게 하기(showFlag true 보임, false 안보임)
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;
    cursorInfo.dwSize = 10;
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}


//필드 지우기
void ClearField(int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (field[y][x] == 1)
            {
                gotoxy(DATUM_POINT_X + x * 2, DATUM_POINT_Y + y);
                printf("  ");
            }
        }
    }
}


//필드출력 자료값이 1인 부분에는 □ 를 출력
void PrintField(int field[][FIELD_WIDTH])
{

    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (field[y][x] == 1)
            {
                gotoxy(DATUM_POINT_X + x * 2, DATUM_POINT_Y + y);
                printf("□");
            }
        }
    }
}

//게임종료화면 출력
void GameOver(int score, int level)
{
    gotoxy(0, 10);
    puts("┌──────────────────────────────────────────────────────────────────────────────┐");
    puts("│                                  게임 오버                                   │");
    puts("│                                                                              │");
    gotoxy(20, 12);
    printf("최종 점수 : %d    최종레벨 : %d ", score, level);

    gotoxy(0, 13);
    puts("│ 3초후 종료합니다.                                                            │");
    puts("└──────────────────────────────────────────────────────────────────────────────┘");
    Sleep(3000);//게임종료 메시지 출력후 5초간 정지
}

//블럭을 랜덤으로 생성함
void CreatBlock(pBLOCK blockHead)
{
    int blocks[7][4][4] =
    {
        {{1,1,0,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0} },

        {{1,1,1,0},
        {0,0,1,0},
        {0,0,0,0},
        {0,0,0,0} },

        {{1,1,1,0},
        {1,0,0,0},
        {0,0,0,0},
        {0,0,0,0} },

        {{1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,0,0,0}},

        {{0,1,0,0},
        {1,1,0,0},
        {1,0,0,0},
        {0,0,0,0} },

        {{0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}},

        {{1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}}
    };

    int pick = (int)rand() % 7;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blocks[pick][y][x] == 1)
            {
                pBLOCK newBlock = malloc(sizeof(BLOCK));
                newBlock->next = blockHead->next;
                blockHead->next = newBlock;
                newBlock->x = x + 4;
                newBlock->y = y;
            }
        }
    }

}

//블럭의 오른쪽 왼쪽 끝의 좌표값 리턴(direction 왼쪽 확인은 1, 오른쪽확인은 0)
int CheckSide(pBLOCK blockHead, int direction)
{
    pBLOCK curr = blockHead->next;
    int side = curr->x;
    if (direction == 1)
    {
        while (curr != NULL)
        {
            if (curr->x < side)
                side = curr->x;
            curr = curr->next;
        }
    }
    else if (direction == 0)
    {
        while (curr != NULL)
        {
            if (curr->x > side)
                side = curr->x;
            curr = curr->next;
        }
    }
    else
    {
        side = -1;
    }
    return side;
}

//블럭 출력
void PrintBlock(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    while (curr != NULL)
    {
        gotoxy(DATUM_POINT_X + ((curr->x) * 2), DATUM_POINT_Y + curr->y);
        printf("■");
        curr = curr->next;
    }
}

//블럭의 위치 지우기
void ClearBlock(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    while (curr != NULL)
    {
        gotoxy(DATUM_POINT_X + ((curr->x) * 2), DATUM_POINT_Y + curr->y);
        printf("  ");
        curr = curr->next;
    }
}


//입력된 필드의 줄을 지우는 함수
void DeleteLine(int  field[FIELD_HEIGHT][FIELD_WIDTH], int lineNumber)
{
    for (int y = lineNumber; y > 0; y--)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            field[y][x] = field[y - 1][x];
        }
    }
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        field[0][x] = 0;
    }
}

//한줄이 가득찼는지 확인하는 함수
int CheckFieldLine(int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    int scoringCounter = 0;
    int lineTotal = 0;
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            lineTotal = lineTotal + field[y][x];
        }
        if (lineTotal == FIELD_WIDTH) {
            DeleteLine(field, y);
            scoringCounter++;
        }
        lineTotal = 0;
    }
    return scoringCounter;
}

//블럭오른쪽으로 이동
void MoveRight(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    while (curr != NULL)
    {
        curr->x++;
        curr = curr->next;
    }
}

//블럭왼쪽으로 이동
void MoveLeft(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    while (curr != NULL)
    {
        curr->x--;
        curr = curr->next;
    }
}

//블럭아래로 한칸씩 이동
void MoveDown(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    while (curr != NULL)
    {
        curr->y++;
        curr = curr->next;
    }
}

//블럭을 떨어뜨림.
void Drop(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    pBLOCK curr = blockHead->next;
    int distance = GetDistance(blockHead, field);
    while (curr != NULL)
    {
        curr->y = curr->y + distance;
        curr = curr->next;
    }
}

//블럭과 필드에 쌓인 블럭과의 최단거리 구하기 리턴값은 최단거리
int GetDistance(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    pBLOCK curr = blockHead->next;
    int distance = FIELD_HEIGHT;    //최초값을 필드의 높이로 정함
    int block_pos_y = curr->y;
    int topOfStacked = 0;
    int dist_counter = 0;

    while (curr != NULL)
    {
        for (int y = curr->y; y < FIELD_HEIGHT; y++)
        {

            if (field[y][curr->x] == 1)
            {
                break;
            }
            dist_counter += 1;
        }

        if (distance > dist_counter)
        {
            distance = dist_counter;
        }
        dist_counter = 0;
        curr = curr->next;
    }
    return distance - 1;

}

//블럭이 부딪히거나 쌓이게 되면 필드에 기록하고 메모리를 해제함
void PutBlocksInField(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    ClearField(field);
    pBLOCK curr = blockHead->next;
    pBLOCK temp;
    while (curr != NULL)
    {
        temp = curr->next;
        field[curr->y][curr->x] = 1;
        free(curr);
        curr = temp;
    }
    blockHead->next = NULL;
    CreatBlock(blockHead);
    PrintField(field);
}

//필드를 리셋해주는 함수
void FieldReset(int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        for (int j = 0; j < FIELD_WIDTH; j++)
            field[i][j] = 0;
    }
}

//블럭을 만든 메모리 해제
void FreeBlockMemory(pBLOCK blockHead)
{
    pBLOCK curr = blockHead;
    pBLOCK temp;
    while (curr != NULL)
    {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
}

//게임 시작시 
void init(int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    ShowConsoleCursor(false);   //커서숨기기
    FieldReset(field);          //필드자료를 모두 0으로 만듬
    system("cls");
    StartingScreen();           //시작화면 출력
    system("cls");
    GameScreen();               //게임화면 출력
    srand(time(NULL));                //랜덤시드를 time으로
}

void _2x2_Rotate(int target[][2], int source[][2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            target[i][j] = source[i][j];
        }
    }
}

//블럭 회전
void RotateBlock(pBLOCK blockHead)
{
    pBLOCK curr = blockHead->next;
    int currPos_x = FIELD_WIDTH;
    int currPos_y = FIELD_HEIGHT;
    int blocks_rotate[4][4] = { 0, };
    int temp = 0;

    //현재의 위치값을 저장
    while (curr != NULL)
    {
        if (curr->x < currPos_x)
            currPos_x = curr->x;
        if (curr->y < currPos_y)
            currPos_y = curr->y;
        curr = curr->next;
    }

    //회전을 시키기위해서 필드에 넣음
    curr = blockHead->next;
    while (curr != NULL)
    {
        blocks_rotate[curr->y - currPos_y][curr->x - currPos_x] = 1;
        curr = curr->next;
    }

    //회전 1단계 4개의 작은 블럭으로 만들어 작은블럭을 회전
    int rotate_step1[2][2][2][2] = { 0, };
    for (int bigY = 0; bigY < 2; bigY++)
    {
        for (int bigX = 0; bigX < 2; bigX++)
        {
            for (int y = 0; y < 2; y++)
            {
                for (int x = 0; x < 2; x++)
                {
                    rotate_step1[bigY][bigX][y][x] = blocks_rotate[bigY * 2 + y][bigX * 2 + x];
                }
            }
            temp = rotate_step1[bigY][bigX][0][0];
            rotate_step1[bigY][bigX][0][0] = rotate_step1[bigY][bigX][1][0];
            rotate_step1[bigY][bigX][1][0] = rotate_step1[bigY][bigX][1][1];
            rotate_step1[bigY][bigX][1][1] = rotate_step1[bigY][bigX][0][1];
            rotate_step1[bigY][bigX][0][1] = temp;
        }
    }

    //회전 2단계
    int temp2[2][2];

    _2x2_Rotate(temp2, rotate_step1[0][0]);
    _2x2_Rotate(rotate_step1[0][0], rotate_step1[1][0]);
    _2x2_Rotate(rotate_step1[1][0], rotate_step1[1][1]);
    _2x2_Rotate(rotate_step1[1][1], rotate_step1[0][1]);
    _2x2_Rotate(rotate_step1[0][1], temp2);


    for (int bigY = 0; bigY < 2; bigY++)
    {
        for (int bigX = 0; bigX < 2; bigX++)
        {
            for (int y = 0; y < 2; y++)
            {
                for (int x = 0; x < 2; x++)
                {
                    blocks_rotate[bigY * 2 + y][bigX * 2 + x] = rotate_step1[bigY][bigX][y][x];
                }
            }
        }
    }


    int margin_x = 2;
    int margin_y = 2;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blocks_rotate[y][x] == 1)
            {
                if (x < margin_x)
                    margin_x = x;
                if (y < margin_y)
                    margin_y = y;
            }
        }
    }

    curr = blockHead->next;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (blocks_rotate[y][x] == 1)
            {
                curr->x = x + currPos_x - margin_x;
                curr->y = y + currPos_y - margin_y;
                curr = curr->next;
            }
        }
    }

    //회전하다가 블럭이 경계를 넘는지 확인하여 넘어가면 위치 조정
    curr = blockHead->next;
    int rightSide = CheckSide(blockHead, 0);
    int leftSide = CheckSide(blockHead, 1);
    if (rightSide >= FIELD_WIDTH)
    {
        while (curr != NULL)
        {
            curr->x -= (rightSide - FIELD_WIDTH) + 1;
            curr = curr->next;
        }
    }
    else if (leftSide < 0)
    {
        while (curr != NULL)
        {
            curr->x += 0 - leftSide;
            curr = curr->next;
        }
    }
}

//다음블럭 인쇄
void PrintNextBlock(pBLOCK nextBlockHead)
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            gotoxy(NEXT_POS_X + x, NEXT_POS_Y + y);
            printf(" ");
        }
    }
    pBLOCK curr = nextBlockHead->next;

    while (curr != NULL) {
        gotoxy(NEXT_POS_X + (curr->x) * 2, NEXT_POS_Y + curr->y);
        printf("■");
        curr = curr->next;
    }
}

//Next 블럭을 현재 블럭으로 옮김
void ExchgBlock(pBLOCK blockHead, pBLOCK nextBlockHead)
{
    blockHead->next = nextBlockHead->next;
    nextBlockHead->next = NULL;
}
//게임점수 및 레벨 계산 및 출력
void CalculateScoreLevel(int* pScore, int* pLevel, double* speed, int numberOfLines)
{
    switch (numberOfLines)
    {
    case 1:
        *pScore = *pScore + 100;
        break;

    case 2:
        *pScore = *pScore + 100 + 110;
        break;

    case 3:
        *pScore = *pScore + 100 + 110 + 150;
        break;

    case 4:
        *pScore = *pScore + 100 + 110 + 150 + 200;
        break;

    default:
        break;
    }

    gotoxy(SCORE_BOARD_POS_X, SCORE_BOARD_POS_Y);
    printf("%d", *pScore);

    *pLevel = 1;
    if (*pScore > 6000) {
        *pLevel = 7;
        *speed = 37;
    }
    else if (*pScore > 5000)
    {
        *pLevel = 6;
        *speed = 75;
    }
    else if (*pScore > 4000)
    {
        *pLevel = 5;
        *speed = 145;
    }
    else if (*pScore > 3000)
    {
        *pLevel = 4;
        *speed = 290;
    }
    else if (*pScore > 2000)
    {
        *pLevel = 3;
        *speed = 440;
    }
    else if (*pScore > 1000)
    {
        *pLevel = 2;
        *speed = 660;
    }
    gotoxy(LEVEL_BOARD_POS_X, LEVEL_BOARD_POS_Y);
    for (int i = 0; i < *pLevel; i++)
        printf("☆");
    gotoxy(2, 24);
}

//맨 윗줄 확인, 게임종료시 0이아닌 정수 리턴
int CheckTopLineOfField(int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    int total1 = 0;
    int total2 = 0;
    for (int x = 0; x < FIELD_WIDTH; x++)
        total1 = total1 + field[0][x];
    for (int x = 0; x < FIELD_WIDTH; x++)
        total2 = total2 + field[1][x];

    return total1 + total2;
}

//블럭왼쪽에 블럭이 쌓인지 확인 있으면 1리턴
int CheckLeftBlock(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    pBLOCK curr = blockHead->next;
    int indicator = 0;
    while (curr != NULL)
    {
        if (field[curr->y][curr->x - 1] == 1)
        {
            indicator = 1;
        }
        curr = curr->next;
    }
    return indicator;
}

//블럭오른쪽에 블럭이 쌓인지 확인 있으면 1리턴
int CheckRightBlock(pBLOCK blockHead, int field[FIELD_HEIGHT][FIELD_WIDTH])
{
    pBLOCK curr = blockHead->next;
    int indicator = 0;
    while (curr != NULL)
    {
        if (field[curr->y][curr->x + 1] == 1)
        {
            indicator = 1;
        }
        curr = curr->next;
    }
    return indicator;
}


int tetris()
{
    pBLOCK blockHead = malloc(sizeof(BLOCK));
    blockHead->next = NULL;

    pBLOCK nextBlockHead = malloc(sizeof(BLOCK));
    nextBlockHead->next = NULL;

    clock_t starting_time;   //시간비교변수1
    starting_time = clock();   //게임시작시간기록
    clock_t current_time;    //시간비교변수2
    double t_diff = 0;      //시간비교변수 1과 2의 차이를 저장할 변수
    int key;                //키입력 밭을 변수
    int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0, };  //게임필드
    int leftSide = 0;       //왼쪽 한계점 확인할 변수
    int rightSide = 0;      //오른쪽 한계점 확인할 변수
    int level = 1;       //게임레벨 1~7
    double speed = 1000;     //게임속도
    int score = 0;          //게임점수저장할 변수
    int numberOfLines = 0;

    init(field);            //게임 초기화함수
    CreatBlock(blockHead);  //최초블럭 생성

    do {
        //최상단에 블럭이 차면 게임종료
        if (CheckTopLineOfField(field) != 0)
            break;

        //블럭이 사라지면 새로 생성 다음 블럭을 받고
        if (blockHead->next == NULL)
        {
            ExchgBlock(blockHead, nextBlockHead);
        }

        //다음블럭이 빈자리이면 생성
        if (nextBlockHead->next == NULL)
        {
            CreatBlock(nextBlockHead);
            PrintNextBlock(nextBlockHead);
        }

        //이전의 블럭자리를 지움
        ClearBlock(blockHead);

        //시간간격을 이용해 블럭이 이동하도록 함. level변수가 시간간격 초깃값은 1
        current_time = clock();
        t_diff = difftime(current_time, starting_time);
        if (t_diff >= speed)
        {
            MoveDown(blockHead);
            starting_time = current_time;
        }

        //키보드가 눌리면 실행될 부분들 회전,이동,드랍
        if (kbhit() != 0)
        {
            key = getch();
            if (key == 'q' || key == 'Q') {
                break;
            }
            else if (key == 32)
            {
                //아래로 떨어뜨림
                Drop(blockHead, field);
            }


            if (key == 224)
            {
                key = _getch();
                if (key == 72)
                {
                    //회전
                    if (CheckLeftBlock(blockHead, field) != 1 || CheckRightBlock(blockHead, field) != 1)
                        RotateBlock(blockHead);
                }
                else if (key == 80)
                {
                    //아래로
                    MoveDown(blockHead);
                }
                else if (key == 75 && CheckSide(blockHead, 1) >= 1 && CheckLeftBlock(blockHead, field) != 1)
                {
                    //왼쪽으로
                    MoveLeft(blockHead);
                }
                else if (key == 77 && CheckSide(blockHead, 0) <= FIELD_WIDTH - 2 && CheckRightBlock(blockHead, field) != 1)
                {
                    //오른쪽으로
                    MoveRight(blockHead);
                }
            }


        }


        //블럭이 쌓이는 조건이 되면 연결리스트의 자료로 필드에 기록
        if (GetDistance(blockHead, field) <= 0) {
            PutBlocksInField(blockHead, field);
            ExchgBlock(blockHead, nextBlockHead);
        }

        //이전화면의 필드를 지우고
        ClearField(field);

        //필드에 가득찬 줄이 있는지 확인해서 제거하고
        numberOfLines = CheckFieldLine(field);

        //점수및 레벨 확인 출력
        CalculateScoreLevel(&score, &level, &speed, numberOfLines);

        //필드를 인쇄
        PrintField(field);

        //블럭을 화면에 출력
        PrintBlock(blockHead);

        //딜레이타임(가장빠른 게임속도와 맞추어 놓음)
        Sleep(37);
    } while (1);
    GameOver(score, level);
    FreeBlockMemory(blockHead);
    FreeBlockMemory(nextBlockHead);
    system("cls");
    int ana;
    printf("해당 게임을 계속 플레이 할 것인가요?...네(1),아니요(0) :");
    scanf("%d", &ana);
    if (ana == 1) {
        tetris();
    }
    else if (ana == 0) {
        return 0;
    }
}

