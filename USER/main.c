#include "my_snake.h"
#include "snakegame.h"
#include "string.h"
/*

A1 为左4096右0
A2 为上0下4096
A10 key1 
A9 key2
A8 sw
B8  
B9 scl
*/
//#define Right 0
//#define Left 2
//#define Up 3
//#define Down 1
//unsigned char table[31]={0x00,0x10,0x20};
//unsigned char count = 3;
//unsigned char Direction;
//unsigned char T;
//int tt;
//unsigned char Flag_Shift,Flag_Over,flag3,Flag_Dot,Flag_Draw;
//unsigned char u;

extern unsigned char draw_background[16][16];
//unsigned char Display_Buffer[2];
//void ReInit(void);
//void Scan_Key(void);
//void Shift(void);
//void Random_Dot(void);
//void Display(void);
//void Send( unsigned char dat);

int main(void)
  {	
		delay_init();
//		GPIO_InitTypeDef GPIO_InitStructure;
		LedarrayIO_init();
		//Adc_Init();
		Snake_KEY_Init();
//	
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTC时钟
//	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;//PA
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
//	GPIO_Init(GPIOB, &GPIO_I		nitStructure);//初始化GPIOA
//	
//	GPIO_SetBits(GPIOB,GPIO_Pin_9);
//	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	while(1)
	{	
//		draw_Clear();
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==0)draw_background[0][0]=1;
//		else draw_background[0][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==0)draw_background[1][0]=1;
//		else draw_background[1][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)draw_background[2][0]=1;
//		else draw_background[2][1]=1;
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)==0)draw_background[3][0]=1;
//		else draw_background[3][1]=1;
//		Display();	
//			Flag_Shift=1;
//			if (Flag_Dot == 1)			//开启按键按下
//				Random_Dot();			//随即显示一个点
//			if (Flag_Shift == 1)		
//				Shift();				//贪食蛇移动

//			Scan_Key();
	
//		Display();
			Snake_Start();
		//delay_ms(1000);
//		scan_line(2);	
//		while(1);
	}
}
	
////**********************************************************
////按键扫描
////**********************************************************
//void Scan_Key()
//{
//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1)
//	{
//		if (Flag_Dot==2)
//		{
//			Flag_Dot=1;			//启动游戏
//		}
//		if(Direction != Left)
//			Direction = Right;
//			
//	}

//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)==1)
//	{
//		if(Direction != Up)
//		Direction = Down;	
//	}

//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==1)
//	{
//		if(Direction != Right)
//		Direction = Left;
//	
//	}

//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)==1)
//	{
//		if(Direction != Down)
//		Direction = Up;	
//	}
//}
////**********************************************************
////
////**********************************************************
//void Shift()
//{
//	int k;
//	if ( Flag_Draw == 1 )
//	{
//		for(k=0;k<count-1;k++)				//绘制蛇身
//		{
//			table[k]=table[k+1];
//		}
//	}
//	switch (Direction)
//	{
//		case 0:							//向右
//			if (table[count-1]/16<15)				//蛇头没有超过右边框
//				table[count-1]=table[count-1]+16;	//右移
//			else
//				Flag_Over=1;							//蛇头超过边框，游戏结束
//			break;
//		case 1:							//向下
//			if (table[count-1]%16<15)
//				table[count-1]=table[count-1]+1;
//			else
//				Flag_Over=1;
//			break;
//		case 2:							//向左
//			if (table[count-1]/16>0)
//				table[count-1]=table[count-1]-16;
//			else
//				Flag_Over=1;
//			break;
//		case 3:							//向上
//			if (table[count-1]%16>0)
//				table[count-1]=table[count-1]-1;
//			else
//				Flag_Over=1;
//			break;
//		default:
//			break;
//	}
//	Flag_Shift=0;
//	if (Flag_Over == 0)
//	{
//		for (k=0;k<count-1;k++)							//判断是否蛇头碰撞到蛇身
//		{
//			if (table[count-1]==table[k])
//			{
//				Flag_Over=1;
//				break;
//			}
//		}
//	}
//	if (Flag_Over == 1)
//	{ 
//		ReInit();					//重现开始游戏
//	}
//	else if (table[count-1]==table[count])		//蛇头 碰到 食物
//	{
//		if (count<30)							
//		{
//			count++;							//蛇身长度+1
//			Flag_Draw=0;
//		}
//		Flag_Dot=1;
//		table[count]=0xff;						//新的食物的坐标在没随机前，不显示
//	}
//	else
//	{
//		Flag_Draw=1;
//	}		
//}

//void Random_Dot()
//{
//	int k;
//	Flag_Dot=0;
//	do
//	{
//		flag3=1;
//		u=rand()%256;				//取出0-255中的任意一个值
//		u=u/16*10+u%16;				//取出随即点的行号放高4位，列号放低4位
//		for (k=0;k<count;k++)		//查询射身与随即点是否重合
//		{
//			if (u==table[k])		//假如有重合，重新随即
//			{
//				flag3=0;
//				break;
//			}
//		}
//	}
//	while(!flag3);					//假如flag3 == 1跳出循环，如果为0则重新随即点
//	table[count]=u;					//取出随即点的值放在table[count]中
//}
//void ReInit(void)
//{	

//	T=0;
//	Direction=0;
//	count=3;
//	table[0]=0x00;
//	table[1]=0x10;
//	table[2]=0x20;
//	delay_ms(500);
//	Flag_Over=0;
//	Flag_Dot=2;
//	Flag_Draw=1;
//	table[count]=0;
//}

//void Display(void)					
//{
//	unsigned char i,j;
//	unsigned int temp = 0x7fff;
//	unsigned char x,y;
//	for( j = 0 ; j <= count ; j++ )
//	{
//		ArrayLed_G=1;		//更新数据时候关闭显示。等更新完数据，打开138显示行。防止重影。

//		y=table[j]/16;				//高4位放列值，  行值：0 = 选通  1 = 不选
//		x=table[j]%16;				//低4位放行值，  列值：1 = 选通  0 = 不选


//		temp = 0x7fff;		
//		for(i = 0 ; i < y ; i++)
//		{
//			temp = (temp>>1)|0x8000;
//		} 

//		Display_Buffer[1] = temp&0x00ff;
//		Display_Buffer[0] = (temp>>8)&0x00ff;
//				
//		Send(Display_Buffer[1]);
//		Send(Display_Buffer[0]);

//		ArrayLed_LAT=1;			//锁存数据
//		delay_us(5);

//		ArrayLed_LAT=0;
//		delay_us(5);

//		scan_line(i);						//选择第i行
//		delay_us(5);
//		ArrayLed_G=0;
//		delay_us(1000);				
//	}	
//}

////显示灯阵
//void Send( unsigned char dat)
//{
//	unsigned char i;
//	char j = 0;
//		ArrayLed_CLK=0;
//		delay_us(5);	
//		ArrayLed_LAT=0;
//		delay_us(5);

//	for( i = 0 ; i < 8 ; i++ )
//	{
//			if(dat&0x01==0)ArrayLed_DI=1;
//			else if(dat&0x01==1)ArrayLed_DI=0;


//			ArrayLed_CLK=1;				//上升沿发送数据
//				delay_us(5);
//			ArrayLed_CLK=0;
//				delay_us(5);

//		
//		dat >>= 1;
//			
//	}			
//}
