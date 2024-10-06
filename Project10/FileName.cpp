#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 20
#define NUM_DROPS 3  // ������� ��

int dropX[NUM_DROPS] = { 9, 24, 52 };  // ������� X ��ǥ (������ �л�)
int dropY[NUM_DROPS] = { 3, 1, 6 };    // ������� Y ��ǥ (�ʱ� ��ġ)
int waveRadius[NUM_DROPS] = { 0, 0, 0 };  // ���� �ݰ�
int waveActive[NUM_DROPS] = { 0, 0, 0 };  // ������ ������ �ִ��� ����

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
    printf("          s. ���� ����          h. ����          q. ����          \n");
}

void ClearPrints(int x, int y, int radius) {
    // ������ �׸� ������ ����� �Լ� (�� �������� �����)
    for (int i = 1; i <= radius; i++) {
        gotoxy(x - i, y);         printf(" ");  // ����
        gotoxy(x + i, y);         printf(" ");  // ����
        gotoxy(x, y - i);         printf(" ");  // ���
        gotoxy(x, y + i);         printf(" ");  // �ϴ�
        gotoxy(x - i, y - i);     printf(" ");  // �»�
        gotoxy(x + i, y - i);     printf(" ");  // ���
        gotoxy(x - i, y + i);     printf(" ");  // ����
        gotoxy(x + i, y + i);     printf(" ");  // ����
    }
}

void DrawPrints(int x, int y, int radius) {
    // ������ �׸��ϴ�.
    char rain = '*';  // ������ '*'�� ǥ��

    for (int i = 1; i <= radius; i++) {
        gotoxy(x - i, y);         printf("%c", rain);  // ����
        gotoxy(x + i, y);         printf("%c", rain);  // ����
        gotoxy(x, y - i);         printf("%c", rain);  // ���
        gotoxy(x, y + i);         printf("%c", rain);  // �ϴ�
        gotoxy(x - i, y - i);     printf("%c", rain);  // �»�
        gotoxy(x + i, y - i);     printf("%c", rain);  // ���
        gotoxy(x - i, y + i);     printf("%c", rain);  // ����
        gotoxy(x + i, y + i);     printf("%c", rain);  // ����
    }
}

void DrawDrop(int x, int y) {
    gotoxy(x, y);
    printf("o");  // �������� �����
}

void GameLoop() {
    clock_t start_time = clock();

    while (1) {
        ClearScreen();
        DrawTitleScreen();

        for (int i = 0; i < NUM_DROPS; i++) {
            // ������� �������� �ִϸ��̼�
            if (!waveActive[i]) {  // ������ ������ ���� ���� ���� ������� ������
                DrawDrop(dropX[i], dropY[i]);
                if (dropY[i] < SCREEN_HEIGHT) {
                    dropY[i]++;
                }
                else {
                    waveActive[i] = 1;  // �ٴڿ� ������ ������ ������ ����
                    dropY[i] = 0;  // ������� �ٽ� ������ ����
                }
            }

            // ������ ������ �ִϸ��̼�
            if (waveActive[i]) {
                // ���� �ݰ��� ������ ������
                if (waveRadius[i] > 0) {
                    ClearPrints(dropX[i], SCREEN_HEIGHT, waveRadius[i] - 1);
                }

                // ���� �ݰ��� ������ �׷���
                DrawPrints(dropX[i], SCREEN_HEIGHT, waveRadius[i]);
                waveRadius[i]++;

                if (waveRadius[i] > 3) {
                    // ������ ������ �ʱ�ȭ
                    waveActive[i] = 0;
                    waveRadius[i] = 0;
                }
            }
        }

        Sleep(200);  // �ִϸ��̼� �ӵ� ����

        // Ű �Է� Ȯ��
        if (_kbhit()) {
            char key = _getch();
            if (key == 'q') {
                printf("\n\n\n\n\n\n\n\n");
                printf("������ ����Ǿ����ϴ�.\n");
                break;  // 'q' Ű�� ������ ���� ����
            }

            if (key == 'h') { // ����
                printf("\n\n\n\n\n\n\n\n");
                printf("\n���� ����:\n");
                printf("- 'q' Ű�� ���� ������ ������ �� �ֽ��ϴ�.\n");
                Sleep(1500);
            }

            else {
                printf("\n\n\n\n\n\n\n\n");
                printf("\n�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n");
                Sleep(500);
            }
        }
    }
}

int main() {
    GameLoop();
    return 0;
}