#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

#define MAX_X 25
#define MAX_Y 25
#define FOOD_SYM '$'

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct snake_t {
    int x;
    int y;
    struct tail_t *tail;
    size_t tsize;
    int direction; // 0 - right, 1 - up, 2 - left, 3 - down
    int level;
} snake_t;

struct snake_t initSnake(int x, int y, size_t tsize) {
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; ++i) {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    snake.direction = 0;
    snake.level = 1;
    return snake;
}

void printSnake(struct snake_t snake, int foodX, int foodY) {
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            matrix[i][j] = ' ';
        }
    }
    if (snake.x >= 0 && snake.x < MAX_X && snake.y >= 0 && snake.y < MAX_Y) {
        matrix[snake.x][snake.y] = '@';
    }
    for (int i = 0; i < snake.tsize; ++i) {
        if (snake.tail[i].x >= 0 && snake.tail[i].x < MAX_X && snake.tail[i].y >= 0 && snake.tail[i].y < MAX_Y) {
            matrix[snake.tail[i].x][snake.tail[i].y] = '*';
        }
    }
    if (foodX >= 0 && foodX < MAX_X && foodY >= 0 && foodY < MAX_Y) {
        matrix[foodX][foodY] = FOOD_SYM;
    }
    for (int j = 0; j < MAX_Y; ++j) {
        for (int i = 0; i < MAX_X; ++i) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

snake_t moveLeft(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x - 1;
    if (snake.x < 0) {
        printf("Game over! You hit the left.\n");
        exit(0);
    }
    return snake;
}

snake_t moveUp(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y - 1;
    if (snake.y < 0) {
        printf("Game over! You hit the top.\n");
        exit(0);
    }
    return snake;
}

snake_t moveRight(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.x = snake.x + 1;
    if (snake.x >= MAX_X) {
        printf("Game over! You hit the right.\n");
        exit(0);
    }
    return snake;
}

snake_t moveDown(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;
    snake.y = snake.y + 1;
    if (snake.y >= MAX_Y) {
        printf("Game over! You hit the bottom.\n");
        exit(0);
    }
    return snake;
}

void changeDirection(snake_t *snake, int newDirection) {
    if (newDirection != (snake->direction + 2) % 4 && newDirection != (snake->direction + 4) % 4) {
        snake->direction = newDirection;
    }
}

int main() {
    srand(time(NULL));
    int foodX, foodY;
    struct snake_t snake = initSnake(10, 5, 2);
    foodX = rand() % MAX_X;
    foodY = rand() % MAX_Y;
    while (1) {
        int ch = getch();
        switch (ch) {
            case 'w':
                changeDirection(&snake, 1);
                break;
            case 'a':
                changeDirection(&snake, 2);
                break;
            case 's':
                changeDirection(&snake, 3);
                break;
            case 'd':
                changeDirection(&snake, 0);
                break;
        }
        switch (snake.direction) {
            case 0:
                snake = moveRight(snake);
                break;
            case 1:
                snake = moveUp(snake);
                break;
            case 2:
                snake = moveLeft(snake);
                break;
            case 3:
                snake = moveDown(snake);
                break;
        }
        if (snake.x == foodX && snake.y == foodY) {
            snake.tsize++;
            snake.level++;
            foodX = rand() % MAX_X;
            foodY = rand() % MAX_Y;
        }
        system("cls");
        printSnake(snake, foodX, foodY);
        printf("Level: %d\n", snake.level);
        sleep(1);
    }
    return 0;
}
