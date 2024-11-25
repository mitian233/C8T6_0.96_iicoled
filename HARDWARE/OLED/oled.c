//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ÖÐ¾°Ô°µç×Ó
//µêÆÌµØÖ·£ºhttp://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  ÎÄ ¼þ Ãû   : main.c
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : Evk123
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üÐÞ¸Ä   : 
//  ¹¦ÄÜÃèÊö   : 0.69´çOLED ½Ó¿ÚÑÝÊ¾Àý³Ì(STM32F103ZEÏµÁÐIIC)
//              ËµÃ÷: 
//              ----------------------------------------------------------------
//              GND   µçÔ´µØ
//              VCC   ½Ó5V»ò3.3vµçÔ´
//              SCL   ½ÓPD6£¨SCL£©
//              SDA   ½ÓPD7£¨SDA£©            
//              ----------------------------------------------------------------
//Copyright(C) ÖÐ¾°Ô°µç×Ó2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////£

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
//OLEDµÄÏÔ´æ
//´æ·Å¸ñÊ½ÈçÏÂ.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
/**********************************************
//IIC Start
**********************************************/
/**********************************************
//IIC Start
**********************************************/

void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//ÉèÖÃPB12ÎªÉÏÀ­ÊäÈëÄ£Ê½
	//GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½OLED Ó¦´ðÐÅºÅ
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//ÉèÖÃPB12ÎªÍ¨ÓÃÍÆÃâÊä³öÄ£Ê½
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

   Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//×ø±êÉèÖÃ

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//¿ªÆôOLEDÏÔÊ¾    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//¹Ø±ÕOLEDÏÔÊ¾     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDCÃüÁî
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//ÇåÆÁº¯Êý,ÇåÍêÆÁ,Õû¸öÆÁÄ»ÊÇºÚÉ«µÄ!ºÍÃ»µãÁÁÒ»Ñù!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //¸üÐÂÏÔÊ¾
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //¸üÐÂÏÔÊ¾
}
//ÔÚÖ¸¶¨Î»ÖÃÏÔÊ¾Ò»¸ö×Ö·û,°üÀ¨²¿·Ö×Ö·û
//x:0~127
//y:0~63
//mode:0,·´°×ÏÔÊ¾;1,Õý³£ÏÔÊ¾				 
//size:Ñ¡Ôñ×ÖÌå 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//µÃµ½Æ«ÒÆºóµÄÖµ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^nº¯Êý
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//ÏÔÊ¾2¸öÊý×Ö
//x,y :Æðµã×ø±ê	 
//len :Êý×ÖµÄÎ»Êý
//size:×ÖÌå´óÐ¡
//mode:Ä£Ê½	0,Ìî³äÄ£Ê½;1,µþ¼ÓÄ£Ê½
//num:ÊýÖµ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//ÏÔÊ¾Ò»¸ö×Ö·ûºÅ´®
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

///***********¹¦ÄÜÃèÊö£ºÏÔÊ¾ÏÔÊ¾BMPÍ¼Æ¬128¡Á64ÆðÊ¼µã×ø±ê(x,y),xµÄ·¶Î§0¡«127£¬yÎªÒ³µÄ·¶Î§0¡«7*****************/
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
//{ 	
// unsigned int j=0;
// unsigned char x,y;
//  
//  if(y1%8==0) y=y1/8;      
//  else y=y1/8+1;
//	for(y=y0;y<y1;y++)
//	{
//		OLED_Set_Pos(x0,y);
//    for(x=x0;x<x1;x++)
//	    {      
//	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
//	    }
//	}
//} 

//³õÊ¼»¯SSD1306					    
void OLED_Init(void)
{ 	
 
 	 

 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //Ê¹ÄÜB¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //³õÊ¼»¯GPIOB8,9
 	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);	


delay_ms(800);
OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  
uint8_t OLED_GRAM[128][8];
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·    
		for(n=0;n<128;n++)
		{
				OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
		}
	}   
}
void OLED_showGram(uint8_t num[128][8])
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //ÉèÖÃÒ³µØÖ·£¨0~7£©
		OLED_WR_Byte (0x00,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐµÍµØÖ·
		OLED_WR_Byte (0x10,OLED_CMD);      //ÉèÖÃÏÔÊ¾Î»ÖÃ¡ªÁÐ¸ßµØÖ·    
		for(n=0;n<128;n++)OLED_WR_Byte(num[n][i],OLED_DATA);
	}   
}
//»­µã 
//x:0~127
//y:0~63
//t:1 Ìî³ä 0,Çå¿Õ	
void OLED_DrawPoint( uint8_t x,uint8_t y,uint8_t mode )
{
	/* Ö÷ÒªÊÇÇó³öy×ø±ê£¬¸ù¾Ýy×ø±êÀ´Î»ÔËËãOLED_GRAMÖÐÏàÓ¦µÄÎ» */
	uint8_t i,j,temp;
	/*ÅÐ¶Ï×ø±êÊÇ·ñ³¬³ö·¶Î§*/
	if(x>127||y>63)return;
	i=7-y/8;//Ëã³öµÚ¼¸Ò³
	j=y%8;
	temp=0x01<<(7-j);//ÓÉÎ»ÔËËã¾«È·ÕÒ³ö×ø±êÏñËØµã
	if(mode==0)
		OLED_GRAM[x][i]&=~temp;
	else
		OLED_GRAM[x][i]|=temp;
	
}
void MYGUI_DrawRectangle(int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint8_t fill,uint8_t color)
{
	int16_t i,j;
	if(x1>x2)
	{
		i=x1;x1=x2;x2=i;
	}
	if(y1>y2)
	{
		i=y1;y1=y2;y2=i;
	}
	if(fill)
	{
		for(i=x1; i<=x2; i++)
        	for(j=y1; j<=y2; j++)
            	OLED_DrawPoint(i,j,color);
	}
	else
	{
		for(i=x1; i<=x2; i++)
		{
			OLED_DrawPoint(i,y1,color);
			OLED_DrawPoint(i,y2,color);
		}
		for(i=y1; i<=y2; i++)
		{
			OLED_DrawPoint(x1,i,color);
			OLED_DrawPoint(x2,i,color);
		}
	}
}
/***********¹¦ÄÜÃèÊö£ºÏÔÊ¾ÏÔÊ¾BMPÍ¼Æ¬128¡Á64ÆðÊ¼µã×ø±ê(x,y),xµÄ·¶Î§0¡«127£¬yÎªÒ³µÄ·¶Î§0¡«7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
	    {
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);
	    }
	}
}

// ¿ìËÙ»æÖÆÍ¼Ïñ
void OLED_DrawBMPFast(const unsigned char BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;

	for (y = 0; y < 8; y++)
	{
		OLED_Set_Pos(0, y);
		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();
		for (x = 0; x < 128; x++)
		{
			Write_IIC_Byte(BMP[j++]);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}
}

void oled_drawbmp_block_clear(int bx, int by, int clear_size)
{
	unsigned int i;
	OLED_Set_Pos(bx, by);
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);
	IIC_Wait_Ack();

	for (i = 0; i < clear_size; i++)
	{
		if (bx + i>128) break;
		Write_IIC_Byte(0x0);
		IIC_Wait_Ack();
	}
	IIC_Stop();
}

void OLED_DrawGround()
{
	static unsigned int pos = 0;
	unsigned char speed = 5;
	unsigned int ground_length = sizeof(GROUND);
	unsigned char x;

	OLED_Set_Pos(0, 7);
	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);
	IIC_Wait_Ack();
	for (x = 0; x < 128; x++)
	{
		Write_IIC_Byte(GROUND[(x+pos)%ground_length]);
		IIC_Wait_Ack();
	}
	IIC_Stop();

	pos = pos + speed;
	//if(pos>ground_length) pos=0;
}


// »æÖÆÔÆ¶ä
void OLED_DrawCloud()
{
	static int pos = 128;
	static char height=0;
	char speed = 3;
	unsigned int i=0;
	int x;
	int start_x = 0;
	int length = sizeof(CLOUD);
	unsigned char byte;

	//if (pos + length <= -speed) pos = 128;

	if (pos + length <= -speed)
	{
		pos = 128;
		height = rand()%3;
	}
	if(pos < 0)
	{
		start_x = -pos;
		OLED_Set_Pos(0, 1+height);
	}
	else
	{
		OLED_Set_Pos(pos, 1+height);
	}

	IIC_Start();
	Write_IIC_Byte(0x78);
	IIC_Wait_Ack();
	Write_IIC_Byte(0x40);
	IIC_Wait_Ack();
	for (x = start_x; x < length + speed; x++)
	{
		if (pos + x > 127) break;
		if (x < length) byte = CLOUD[x];
		else byte = 0x0;

		Write_IIC_Byte(byte);
		IIC_Wait_Ack();
	}
	IIC_Stop();

	pos = pos - speed;
}

// »æÖÆÐ¡¿ÖÁú
void OLED_DrawDino()
{
	static unsigned char dino_dir = 0;
	unsigned int j=0;
	unsigned char x, y;
	unsigned char byte;

	dino_dir++;
	dino_dir = dino_dir%2;
	for(y=0; y<2; y++)
	{
		OLED_Set_Pos(16, 6+y);
		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();
		for (x = 0; x < 16; x++)
		{
			j = y*16 + x;
			byte = DINO[dino_dir][j];

			Write_IIC_Byte(byte);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}
}

// »æÖÆÏÉÈËÕÆÕÏ°­Îï
void OLED_DrawCactus()
{
	char speed = 5;
	static int pos = 128;
	int start_x = 0;
	int length = sizeof(CACTUS_2)/2;

	unsigned int j=0;
	unsigned char x, y;
	unsigned char byte;

	if (pos + length <= 0)
	{
		oled_drawbmp_block_clear(0, 6, speed);
		pos = 128;
	}

	for(y=0; y<2; y++)
	{
		if(pos < 0)
		{
			start_x = -pos;
			OLED_Set_Pos(0, 6+y);
		}
		else
		{
			OLED_Set_Pos(pos, 6+y);
		}

		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();

		for (x = start_x; x < length; x++)
		{
			if (pos + x > 127) break;
			j = y*length + x;
			byte = CACTUS_2[j];
			Write_IIC_Byte(byte);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}
	oled_drawbmp_block_clear(pos + length, 6, speed); // Çå³ý²ÐÓ°
	pos = pos - speed;
}


// »æÖÆËæ»ú³öÏÖµÄÏÉÈËÕÆÕÏ°­Îï
int OLED_DrawCactusRandom(unsigned char ver, unsigned char reset)
{
	char speed = 5;
	static int pos = 128;
	int start_x = 0;
	int length = 0;

	unsigned int i=0, j=0;
	unsigned char x, y;
	unsigned char byte;
	if (reset == 1)
	{
		pos = 128;
		oled_drawbmp_block_clear(0, 6, speed);
		return 128;
	}
	if (ver == 0) length = 8; //sizeof(CACTUS_1) / 2;
	else if (ver == 1) length = 16; //sizeof(CACTUS_2) / 2;
	else if (ver == 2 || ver == 3) length = 24;

	for(y=0; y<2; y++)
	{
		if(pos < 0)
		{
			start_x = -pos;
			OLED_Set_Pos(0, 6+y);
		}
		else
		{
			OLED_Set_Pos(pos, 6+y);
		}

		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();

		for (x = start_x; x < length; x++)
		{
			if (pos + x > 127) break;

			j = y*length + x;
			if (ver == 0) byte = CACTUS_1[j];
			else if (ver == 1) byte = CACTUS_2[j];
			else if(ver == 2) byte = CACTUS_3[j];
			else byte = CACTUS_4[j];

			Write_IIC_Byte(byte);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}

	oled_drawbmp_block_clear(pos + length, 6, speed);

	pos = pos - speed;
	return pos + speed;
}




// »æÖÆÌøÔ¾Ð¡¿ÖÁú
int OLED_DrawDinoJump(char reset)
{
	char speed_arr[] = {1, 1, 3, 3, 4, 4, 5, 6, 7};
	static char speed_idx = sizeof(speed_arr)-1;
	static int height = 0;
	static char dir = 0;
	//char speed = 4;

	unsigned int j=0;
	unsigned char x, y;
	char offset = 0;
	unsigned char byte;
	if(reset == 1)
	{
		height = 0;
		dir = 0;
		speed_idx = sizeof(speed_arr)-1;
		return 0;
	}
	if (dir==0)
	{
		height += speed_arr[speed_idx];
		speed_idx --;
		if (speed_idx<0) speed_idx = 0;
	}
	if (dir==1)
	{
		height -= speed_arr[speed_idx];
		speed_idx ++;
		if (speed_idx>sizeof(speed_arr)-1) speed_idx = sizeof(speed_arr)-1;
	}
	if(height >= 31)
	{
		dir = 1;
		height = 31;
	}
	if(height <= 0)
	{
		dir = 0;
		height = 0;
	}
	if(height <= 7) offset = 0;
	else if(height <= 15) offset = 1;
	else if(height <= 23) offset = 2;
	else if(height <= 31) offset = 3;
	else offset = 4;

	for(y=0; y<3; y++) // 4
	{
		OLED_Set_Pos(16, 5- offset + y);

		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();
		for (x = 0; x < 16; x++) // 32
		{
			j = y*16 + x; // 32
			byte = DINO_JUMP[height%8][j];

			Write_IIC_Byte(byte);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}
	if (dir == 0) oled_drawbmp_block_clear(16, 8- offset, 16);
	if (dir == 1) oled_drawbmp_block_clear(16, 4- offset, 16);
	return height;
}

// »æÖÆÖØÆô
void OLED_DrawRestart()
{
	unsigned int j=0;
	unsigned char x, y;
	unsigned char byte;
	//OLED_SetPos(0, 0);
	for (y = 2; y < 5; y++)
	{
		OLED_Set_Pos(52, y);
		IIC_Start();
		Write_IIC_Byte(0x78);
		IIC_Wait_Ack();
		Write_IIC_Byte(0x40);
		IIC_Wait_Ack();
		for (x = 0; x < 24; x++)
		{
			byte = RESTART[j++];
			Write_IIC_Byte(byte);
			IIC_Wait_Ack();
		}
		IIC_Stop();
	}
	OLED_ShowString(10, 3, "GAME", 16);
	OLED_ShowString(86, 3, "OVER", 16);
}
// »æÖÆ·âÃæ
void OLED_DrawCover()
{
	OLED_DrawBMPFast(COVER);
}



























