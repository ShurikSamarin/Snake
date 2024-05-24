#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define MAX_X 15
#define MAX_Y 15
typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
	int direction; // d - right, w - up, a - left, s - down
	}  snake_t;

struct snake_t initSnake(int x, int y, size_t tsize){
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
		}
	snake.direction = 0; // по умолчанию движение вправо
	return snake;
}

	
// @**
void printSnake(struct snake_t snake){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}}
		
		matrix[snake.x][snake.y] = '@';
		for (int i = 0; i < snake.tsize; ++i){
			matrix[snake.tail[i].x][snake.tail[i].y] = '*';
			}
		
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%c", matrix[i][j]);
				}
				printf("\n");
				}
	}
	

snake_t moveLeft(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x = snake.x - 1;	
	if (snake.x < 0){
		snake.x = MAX_X - 1;
		}
	return snake;
	}

	snake_t moveUp(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.y = snake.y - 1;	
	if (snake.y < 0){
		snake.y = MAX_Y - 1;
		}
	return snake;
	}

	snake_t moveRight(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x = snake.x + 1;	
	if (snake.x >= MAX_X){
		snake.x = 0;
		}
	return snake;
	}

	snake_t moveDown(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.y = snake.y + 1;	
	if (snake.y >= MAX_Y){
		snake.y = 0;
		}
	return snake;
	}

	void changeDirection(snake_t * snake, int newDirection){
		if (newDirection != (snake->direction + 2) % 4 && newDirection != (snake->direction + 4) % 4){
			snake->direction = newDirection;
		}
	}

	int main(){
		struct snake_t snake = initSnake( 10, 5, 2);
		printSnake(snake);
		while(1)//for( int i = 0; i < 8; ++i)
		{
			int ch = getch();
			switch (ch){
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
			switch (snake.direction){
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
			sleep(1);
			system("cls");
			printSnake(snake);
		}
		return 0;
	}
