#include "my_snake.h"
#include "snakegame.h"
#include "string.h"
/*

A1 Ϊ��4096��0
A2 Ϊ��0��4096
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
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTCʱ��
//	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;//PA
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
//	GPIO_Init(GPIOB, &GPIO_I		nitStructure);//��ʼ��GPIOA
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
//			if (Flag_Dot == 1)			//������������
//				Random_Dot();			//�漴��ʾһ����
//			if (Flag_Shift == 1)		
//				Shift();				//̰ʳ���ƶ�

//			Scan_Key();
	
//		Display();
			Snake_Start();
		//delay_ms(1000);
//		scan_line(2);	
//		while(1);
	}
}
	
////**********************************************************
////����ɨ��
////**********************************************************
//void Scan_Key()
//{
//	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)==1)
//	{
//		if (Flag_Dot==2)
//		{
//			Flag_Dot=1;			//������Ϸ
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
//		for(k=0;k<count-1;k++)				//��������
//		{
//			table[k]=table[k+1];
//		}
//	}
//	switch (Direction)
//	{
//		case 0:							//����
//			if (table[count-1]/16<15)				//��ͷû�г����ұ߿�
//				table[count-1]=table[count-1]+16;	//����
//			else
//				Flag_Over=1;							//��ͷ�����߿���Ϸ����
//			break;
//		case 1:							//����
//			if (table[count-1]%16<15)
//				table[count-1]=table[count-1]+1;
//			else
//				Flag_Over=1;
//			break;
//		case 2:							//����
//			if (table[count-1]/16>0)
//				table[count-1]=table[count-1]-16;
//			else
//				Flag_Over=1;
//			break;
//		case 3:							//����
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
//		for (k=0;k<count-1;k++)							//�ж��Ƿ���ͷ��ײ������
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
//		ReInit();					//���ֿ�ʼ��Ϸ
//	}
//	else if (table[count-1]==table[count])		//��ͷ ���� ʳ��
//	{
//		if (count<30)							
//		{
//			count++;							//������+1
//			Flag_Draw=0;
//		}
//		Flag_Dot=1;
//		table[count]=0xff;						//�µ�ʳ���������û���ǰ������ʾ
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
//		u=rand()%256;				//ȡ��0-255�е�����һ��ֵ
//		u=u/16*10+u%16;				//ȡ���漴����кŷŸ�4λ���кŷŵ�4λ
//		for (k=0;k<count;k++)		//��ѯ�������漴���Ƿ��غ�
//		{
//			if (u==table[k])		//�������غϣ������漴
//			{
//				flag3=0;
//				break;
//			}
//		}
//	}
//	while(!flag3);					//����flag3 == 1����ѭ�������Ϊ0�������漴��
//	table[count]=u;					//ȡ���漴���ֵ����table[count]��
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
//		ArrayLed_G=1;		//��������ʱ��ر���ʾ���ȸ��������ݣ���138��ʾ�С���ֹ��Ӱ��

//		y=table[j]/16;				//��4λ����ֵ��  ��ֵ��0 = ѡͨ  1 = ��ѡ
//		x=table[j]%16;				//��4λ����ֵ��  ��ֵ��1 = ѡͨ  0 = ��ѡ


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

//		ArrayLed_LAT=1;			//��������
//		delay_us(5);

//		ArrayLed_LAT=0;
//		delay_us(5);

//		scan_line(i);						//ѡ���i��
//		delay_us(5);
//		ArrayLed_G=0;
//		delay_us(1000);				
//	}	
//}

////��ʾ����
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


//			ArrayLed_CLK=1;				//�����ط�������
//				delay_us(5);
//			ArrayLed_CLK=0;
//				delay_us(5);

//		
//		dat >>= 1;
//			
//	}			
//}
