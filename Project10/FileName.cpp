#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20
#define NUM_DROPS 3  // 물방울의 수

int dropX[NUM_DROPS] = { 9, 24, 52 };  // 물방울의 X 좌표 (적절히 분산)
int dropY[NUM_DROPS] = { 3, 1, 6 };    // 물방울의 Y 좌표 (초기 위치)
int waveRadius[NUM_DROPS] = { 0, 0, 0 };  // 파장 반경
int waveActive[NUM_DROPS] = { 0, 0, 0 };  // 파장이 퍼지고 있는지 여부

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void ClearScreen() {
    system("cls");
}

void DrawTitleScreen() {
    printf("\n\n\n");
    printf("                         ESCAPE FROM DARKROOM                         \n");
    printf("\n\n\n\n\n");
    printf("\n\n\n\n\n");
    printf("\n\n\n");
    printf("          s. 게임 시작          h. 도움말          q. 종료          \n");
}

void ClearPrints(int x, int y, int radius) {
    // 이전에 그린 파장을 지우는 함수 (빈 공간으로 덮어쓰기)
    for (int i = 1; i <= radius; i++) {
        gotoxy(x - i, y);         printf(" ");  // 좌측
        gotoxy(x + i, y);         printf(" ");  // 우측
        gotoxy(x, y - i);         printf(" ");  // 상단
        gotoxy(x, y + i);         printf(" ");  // 하단
        gotoxy(x - i, y - i);     printf(" ");  // 좌상
        gotoxy(x + i, y - i);     printf(" ");  // 우상
        gotoxy(x - i, y + i);     printf(" ");  // 좌하
        gotoxy(x + i, y + i);     printf(" ");  // 우하
    }
}

void DrawPrints(int x, int y, int radius) {
    // 파장을 그립니다.
    char rain = '*';  // 파장을 '*'로 표시

    for (int i = 1; i <= radius; i++) {
        gotoxy(x - i, y);         printf("%c", rain);  // 좌측
        gotoxy(x + i, y);         printf("%c", rain);  // 우측
        gotoxy(x, y - i);         printf("%c", rain);  // 상단
        gotoxy(x, y + i);         printf("%c", rain);  // 하단
        gotoxy(x - i, y - i);     printf("%c", rain);  // 좌상
        gotoxy(x + i, y - i);     printf("%c", rain);  // 우상
        gotoxy(x - i, y + i);     printf("%c", rain);  // 좌하
        gotoxy(x + i, y + i);     printf("%c", rain);  // 우하
    }
}

void DrawDrop(int x, int y) {
    gotoxy(x, y);
    printf("o");  // 떨어지는 물방울
}

void GameLoop() {
    clock_t start_time = clock();

    while (1) {
        ClearScreen();
        DrawTitleScreen();

        for (int i = 0; i < NUM_DROPS; i++) {
            // 물방울이 떨어지는 애니메이션
            if (!waveActive[i]) {  // 파장이 퍼지고 있지 않을 때만 물방울이 떨어짐
                DrawDrop(dropX[i], dropY[i]);
                if (dropY[i] < SCREEN_HEIGHT) {
                    dropY[i]++;
                }
                else {
                    waveActive[i] = 1;  // 바닥에 닿으면 파장이 퍼지기 시작
                    dropY[i] = 0;  // 물방울을 다시 위에서 시작
                }
            }

            // 파장이 퍼지는 애니메이션
            if (waveActive[i]) {
                // 이전 반경의 파장을 지워줌
                if (waveRadius[i] > 0) {
                    ClearPrints(dropX[i], SCREEN_HEIGHT, waveRadius[i] - 1);
                }

                // 현재 반경의 파장을 그려줌
                DrawPrints(dropX[i], SCREEN_HEIGHT, waveRadius[i]);
                waveRadius[i]++;

                if (waveRadius[i] > 3) {
                    // 파장이 끝나면 초기화
                    waveActive[i] = 0;
                    waveRadius[i] = 0;
                }
            }
        }

        Sleep(200);  // 애니메이션 속도 조정

        // 키 입력 확인
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q') {
                printf("\n\n\n\n\n\n\n\n");
                printf("게임이 종료되었습니다.\n");
                break;  // 'q' 키를 누르면 게임 종료
            }

            if (key == 'h') { // 도움말
                printf("\n\n\n\n\n\n\n\n");
                printf("\n게임 도움말:\n");
                printf("- 'q' 키를 눌러 게임을 종료할 수 있습니다.\n");
                Sleep(1500);
            }

            else {
                printf("\n\n\n\n\n\n\n\n");
                printf("\n잘못된 입력입니다. 다시 선택하세요.\n");
                Sleep(500);
            }
        }
    }
}

int main() {
    GameLoop();
    return 0;
}