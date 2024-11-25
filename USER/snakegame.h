#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "my_snake.h"
#define SNAKE_MAXLEN	50
#define SNAKE_MAP_XMAX	16
#define SNAKE_MAP_YMAX	16


typedef enum {
	DIR_UP = 0,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT	
}DIR;

typedef struct {
	uint8_t body_X[SNAKE_MAXLEN];
	uint8_t body_Y[SNAKE_MAXLEN];
	uint8_t head,tail,length;
	DIR tmp_dir;
	DIR dir;
}SNAKE;

/*
KEY1:PA11
KEY2:PA12
*/
#define KEY1 PAin(11)//right
#define KEY2 PAin(12)//down
#define KEY3 PAin(1)//left
#define KEY4 PAin(2)//up
void Snake_KEY_Init(void);
void	Snake_Dir			(void);
void 	Snake_Init			(SNAKE *obj);
void 	Snake_ClearTail		(SNAKE *obj);
void 	Snake_PaintHead		(SNAKE *obj);
void 	Snake_Move			(SNAKE *obj);
void 	Snake_CreateFood	(SNAKE *obj);
uint8_t Snake_CheckDeath	(SNAKE *obj);
uint8_t Snake_CheckFood		(SNAKE *obj);
uint8_t Snake_Level			(SNAKE *obj);

void	Snake_StartPage	(void);
void	Snake_GamePage	(void);
void	Snake_OverPage	(void);
void Snake_Start(void);
void Show_Start(void);
void Show_Over(void);

#endif 