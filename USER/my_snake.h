#ifndef MY_SNAKE_H
#define MY_SNAKE_H

#include "sys.h"
#include "delay.h"
#include "string.h"		
#include "TIME.h"
#include "stdlib.h"
//GPIO_SetBits(GPIOB,GPIO_Pin_9)
/*
D��PA3
C��PA4
B��PA5
A��PA6
G��PA7
DI��PA8
CLK��PA9
LAT��PA10
*/
#define ArrayLed_D PAout(3)//GPIO_Pin_3 
#define ArrayLed_C PAout(4)//GPIO_Pin_4
#define ArrayLed_B PAout(5)//GPIO_Pin_5
#define ArrayLed_A PAout(6)//GPIO_Pin_6
#define ArrayLed_G PAout(7)//GPIO_Pin_7
#define ArrayLed_DI PAout(8)//GPIO_Pin_8
#define ArrayLed_CLK PAout(9)//GPIO_Pin_9
#define ArrayLed_LAT PAout(10)//GPIO_Pin_10


void draw_Clear(void);

void Adc_Init(void);
u16 Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times);

void LedarrayIO_init(void);
void SetIO(uint16_t ArrayLed_IO,int num);
void scan_line(int linenum);
void Display(void);


#endif