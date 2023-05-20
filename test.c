#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// ������Ϸ�����С
#define WIDTH 20
#define HEIGHT 20

// �����ߵ���󳤶�
#define MAX_LENGTH WIDTH*HEIGHT

// �����ߵķ���
enum Direction { UP, DOWN, LEFT, RIGHT };

// �����ߵĽṹ��
struct Snake {
    int x, y;
};

int main() {
    struct Snake snake[MAX_LENGTH];
    int length = 1;
    int fruitX, fruitY;
    int score = 0;
    enum Direction dir = RIGHT;

    // ��ʼ���ߵ�λ��
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;

    // ������ɹ�ʵλ��
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    while (1) {
        // �����Ļ
        system("cls");

        // ������Ϸ����
        for (int i = 0; i < WIDTH + 2; i++)
            printf("#");
        printf("\n");

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0)
                    printf("#");
                if (i == snake[0].y && j == snake[0].x)
                    printf("O");  // ��ͷ
                else if (i == fruitY && j == fruitX)
                    printf("F");  // ��ʵ
                else {
                    int isTail = 0;
                    for (int k = 1; k < length; k++) {
                        if (i == snake[k].y && j == snake[k].x) {
                            printf("o");  // ����
                            isTail = 1;
                            break;
                        }
                    }
                    if (!isTail)
                        printf(" ");
                }
                if (j == WIDTH - 1)
                    printf("#");
            }
            printf("\n");
        }

        for (int i = 0; i < WIDTH + 2; i++)
            printf("#");
        printf("\n");

        // �������ƶ�
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                return 0;
            }
        }

        // �����ߵ�λ��
        int prevX = snake[0].x;
        int prevY = snake[0].y;
        int prev2X, prev2Y;
        snake[0].x += (dir == RIGHT) ? 1 : (dir == LEFT) ? -1 : 0;
        snake[0].y += (dir == DOWN) ? 1 : (dir == UP) ? -1 : 0;

        // ������Ƿ�Ե���ʵ
        if (snake[0].x == fruitX && snake[0].y == fruitY) {
            // �����µĹ�ʵλ��
            score++;
            length++;

            // �����µĹ�ʵλ��
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        }

        // �����������λ��
        for (int i = 1; i < length; i++) {
            prev2X = snake[i].x;
            prev2Y = snake[i].y;
            snake[i].x = prevX;
            snake[i].y = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        // ������Ƿ�ײǽ��ײ���Լ�������
        if (snake[0].x >= WIDTH || snake[0].x < 0 || snake[0].y >= HEIGHT || snake[0].y < 0) {
            printf("\n��Ϸ�������÷֣�%d\n", score);
            break;
        }

        for (int i = 1; i < length; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                printf("\n��Ϸ�������÷֣�%d\n", score);
                break;
            }
        }

        // ������Ϸ�ٶ�
        Sleep(100);
    }

    return 0;
}
