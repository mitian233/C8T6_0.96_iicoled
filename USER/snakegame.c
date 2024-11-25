#include "snakegame.h"
extern unsigned char draw_background[16][16];
SNAKE snake1,snake2;
unsigned short SNAKE_SPEED_LEVEL[11] = {0,300,250,200,170,150,130,110,100,90,80}; 
uint8_t level=1;
uint8_t foodx,foody;
unsigned short i ;
/*
KEY1:PA11
KEY2:PA12
*/
void Snake_KEY_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时
	
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_1|GPIO_Pin_2;//PA11
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA11
	
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PA12
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA12
	
}
void Snake_Init(SNAKE *obj)
{
	obj->head = 0;
	obj->tail = 0;
	obj->length = 1;
	obj->body_X[obj->head] = 7;
	obj->body_Y[obj->head] = 7;
	obj->dir = DIR_RIGHT;
	obj->tmp_dir = DIR_RIGHT;
}

void Snake_Dir()
{
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==0)draw_background[0][0]=1;
//		else draw_background[0][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==0)draw_background[1][0]=1;
//		else draw_background[1][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)draw_background[2][0]=1;
//		else draw_background[2][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)==0)draw_background[3][0]=1;
//		else draw_background[3][1]=1;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)
		snake1.tmp_dir = DIR_UP;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1)
		snake1.tmp_dir = DIR_DOWN;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)==1)
		snake1.tmp_dir = DIR_LEFT;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==1)
		snake1.tmp_dir = DIR_RIGHT;
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)
		snake2.tmp_dir = DIR_UP;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1)
		snake2.tmp_dir = DIR_DOWN;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)==1)
		snake2.tmp_dir = DIR_LEFT;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==1)
		snake2.tmp_dir = DIR_RIGHT;
}

void Snake_ClearTail(SNAKE *obj)
{
	uint8_t tmp = obj->tail;
	//MYGUI_DrawRectangle(obj->body_X[tmp]*3-1,obj->body_Y[tmp]*3-1,obj->body_X[tmp]*3+1,obj->body_Y[tmp]*3+1,1,0);
	draw_background[obj->body_X[tmp]][obj->body_Y[tmp]]=0;
}

void Snake_PaintHead(SNAKE *obj)
{
	uint8_t tmp = obj->head;
	//MYGUI_DrawRectangle(obj->body_X[tmp]*3-1,obj->body_Y[tmp]*3-1,obj->body_X[tmp]*3+1,obj->body_Y[tmp]*3+1,1,1);
	draw_background[obj->body_X[tmp]][obj->body_Y[tmp]]=1;
	
}

void Snake_Move(SNAKE *obj)
{
	uint8_t temp;
	temp = (obj->head+1) % SNAKE_MAXLEN;
	obj->body_X[temp] = obj->body_X[obj->head];
	obj->body_Y[temp] = obj->body_Y[obj->head];
	
	if((obj->tmp_dir+4-obj->dir)%4 != 2)
		obj->dir = obj->tmp_dir;
	switch(obj->dir)
	{
		case DIR_UP:
			obj->body_Y[temp]--;
			break;
		case DIR_LEFT:
			obj->body_X[temp]--;
			break;
		case DIR_DOWN:
			obj->body_Y[temp]++;
			break;
		case DIR_RIGHT:
			obj->body_X[temp]++;
			break;
		default:break;
	}
	obj->head = temp;
	Snake_PaintHead(obj);
	
	if(Snake_CheckFood(obj)==1)
	{
		obj->length++;
		Snake_CreateFood(obj);
	}
	else
	{
		Snake_ClearTail(obj);
		obj->tail++;
		obj->tail %= SNAKE_MAXLEN;
	}
	
//	Display();
//	delay_ms(100);
}

void Snake_CreateFood(SNAKE *obj)
{
	do
	{
		foodx = rand()%(SNAKE_MAP_XMAX-1)+1;
		foody = rand()%(SNAKE_MAP_YMAX-1)+1;
	}while(Snake_CheckFood(obj)==1);
	
	draw_background[foodx][foody]=1;
	Display();
}

uint8_t Snake_CheckDeath(SNAKE *obj)
{
	if(	obj->body_X[obj->head] > SNAKE_MAP_XMAX	||\
		obj->body_X[obj->head] == 0				||\
		obj->body_Y[obj->head] > SNAKE_MAP_YMAX	||\
		obj->body_Y[obj->head] == 0 )
	{
		return 1;
	}
	for(i = obj->tail; i != obj->head; )
    {
    	if(	obj->body_X[obj->head] == obj->body_X[i] && \
			obj->body_Y[obj->head] == obj->body_Y[i])
			return 1;
		i++;
		i %= SNAKE_MAXLEN;
		
    }
	return 0;
}

uint8_t Snake_CheckFood(SNAKE *obj)
{
	if(	(obj->body_X[obj->head] == foodx) && \
		(obj->body_Y[obj->head] == foody ))
		return 1;
	
	for( i = obj->tail; i != obj->head;)
    {
    	if(	obj->body_X[i] == foodx && \
			obj->body_Y[i] == foody)
			return 1;
		i++;
		i %= SNAKE_MAXLEN;
    }
	return 0;
}

uint8_t Snake_Level(SNAKE *obj)
{
	uint8_t level;
	if(obj->length < 10)
		level = 1;
	else if(obj->length < 20)
		level = 2;
	else if(obj->length < 30)
		level = 3;
	else if(obj->length < 40)
		level = 4;
	else if(obj->length < 50)
		level = 5;
	else if(obj->length < 60)
		level = 6;
	else if(obj->length < 70)
		level = 7;
	else if(obj->length < 80)
		level = 8;
	else if(obj->length < 90)
		level = 9;
	else
		level = 10;
	return level;
}

void Snake_StartPage(void)
{
	draw_Clear();
	Show_Start();
	Display();
	//OLED_ShowString(0,28/8,"PRESS KEY UP TO START",12);
	//OLED_Refresh_Gram();
	while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11));
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11));
	Snake_Init(&snake1);
}

void Snake_GamePage(void)
{
	int delaynum = 0;
	//OLED_Clear();
	draw_Clear();
	Snake_PaintHead(&snake1);
	Snake_CreateFood(&snake1);
	while(Snake_CheckDeath(&snake1) == 0)
	{
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==0)
//			delay_ms(40);
//		else
		 for(delaynum = 0;delaynum <20;delaynum++)
		{
			delay_ms(10);//SNAKE_SPEED_LEVEL[level]
			Snake_Dir();
			//draw_background[0][0]=1;
			Display();
		}

		Snake_Move(&snake1);
		//Display();
		//level = Snake_Level(&snake1);

	}

}
//void Snake_OverPage(void)
//{
//	MYGUI_DrawRectangle(8,12,84,50,1,0);
//	OLED_Refresh_Gram();
//	OLED_ShowString(10,14/8,"GAME OVER",12);
//	OLED_ShowNum(35,30/8,snake1.length,4,12);
//	
//}

void Snake_Start(void)
{
	//get_max();
	while(1){
		Snake_StartPage();
		Snake_GamePage();
		//Snake_OverPage();
		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11))
		{
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)) return ;
		}
		//MYGUI_DrawRectangle(0,0,127,63,1,0);
	}
}

void Show_Start(void)
{
	for(i=0;i<8;i++){
		draw_background[8][i+2]=1;
	}
	draw_background[8][10]=1;
	draw_background[9][9]=1;
	draw_background[10][8]=1;
	draw_background[11][7]=1;
	draw_background[7][9]=1;
	draw_background[6][8]=1;
	draw_background[5][7]=1;
}
