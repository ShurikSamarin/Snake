#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <windows.h> 

#define MAX_X 25
#define MAX_Y 25
#define FOOD_SYM 'O'
#define RED 4
#define BLUE 1
#define GREEN 2

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct snake_t {
    int x;
    int y;
    struct tail_t *tail;
    size_t tsize;
    int direction; 
    int level;
} snake_t;


void setColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void moveSnake(snake_t *snake) {
    
    for (int i = snake->tsize - 1; i > 0; i--) {
        snake->tail[i] = snake->tail[i - 1];
    }
    
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;
    switch (snake->direction) {
        case 0: // Вправо
            snake->x++;
            break;
        case 1: // Вверх
            snake->y--;
            break;
        case 2: // Влево
            snake->x--;
            break;
        case 3: // Вниз
            snake->y++;
            break;
    }
    
    if (snake->x < 0 || snake->x >= MAX_X || snake->y < 0 || snake->y >= MAX_Y) {
        printf("Game over! You hit the wall.\n");
        exit(0);
    }
}


void checkFood(snake_t *snake, int *foodX, int *foodY) {
    if (snake->x == *foodX && snake->y == *foodY) {
        
        snake->tsize++;
        snake->level++;
        
        *foodX = rand() % MAX_X;
        *foodY = rand() % MAX_Y;
    }
}

snake_t initSnake(int startX, int startY, int startSize) {
    snake_t snake;
    snake.x = startX;
    snake.y = startY;
    snake.tsize = startSize;
    snake.tail = (tail_t*)malloc(snake.tsize * sizeof(tail_t));
    snake.direction = 0; 
    snake.level = 1;
    for (int i = 0; i < snake.tsize; i++) {
        snake.tail[i].x = startX - i;
        snake.tail[i].y = startY;
    }
    return snake;
}


void changeDirection(snake_t *snake, int dir) {
    
    if (abs(snake->direction - dir) != 2) {
        snake->direction = dir;
    }
}


void printSnake(snake_t snake, int foodX, int foodY, int snakeColor) {
    
    system("cls"); 

    
    char field[MAX_X][MAX_Y];
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            field[x][y] = ' ';
        }
    }

    
    for (int i = 0; i < snake.tsize; i++) {
        if (snake.tail[i].x >= 0 && snake.tail[i].x < MAX_X &&
            snake.tail[i].y >= 0 && snake.tail[i].y < MAX_Y) {
            field[snake.tail[i].x][snake.tail[i].y] = '*';
        }
    }

    
    if (foodX >= 0 && foodX < MAX_X && foodY >= 0 && foodY < MAX_Y) {
        field[foodX][foodY] = FOOD_SYM;
    }

    
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (field[x][y] == '*') {
                setColor(snakeColor);
                printf("%c", field[x][y]);
                
            } else {
                printf("%c", field[x][y]);
            }
        }
        printf("\n");
    }
    
    setColor(7);
}

int main() {
    srand(time(NULL));
    int foodX, foodY;
    struct snake_t snake1 = initSnake(10, 5, 2);
    struct snake_t snake2 = initSnake(15, 5, 2); 
    foodX = rand() % MAX_X;
    foodY = rand() % MAX_Y;
    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            
            switch (ch) {
                case 'w':
                    changeDirection(&snake1, 1);
                    break;
                case 'a':
                    changeDirection(&snake1, 2);
                    break;
                case 's':
                    changeDirection(&snake1, 3);
                    break;
                case 'd':
                    changeDirection(&snake1, 0);
                    break;
                
                case '8':
                    changeDirection(&snake2, 1);
                    break;
                case '4':
                    changeDirection(&snake2, 2);
                    break;
                case '5':
                    changeDirection(&snake2, 3);
                    break;
                case '6':
                    changeDirection(&snake2, 0);
                    break;
            }
        }
        
        moveSnake(&snake1);
        moveSnake(&snake2);
        
        checkFood(&snake1, &foodX, &foodY);
        checkFood(&snake2, &foodX, &foodY);
        
        
        printSnake(snake1, foodX, foodY, RED);
        
        printSnake(snake2, foodX, foodY, BLUE);
        
        setColor(GREEN);
        printf("%c", FOOD_SYM);
        
        printf("Level: %d\n", snake1.level);
        printf("Level: %d\n", snake2.level);
        sleep(1);
        
    }
    return 0;
}
