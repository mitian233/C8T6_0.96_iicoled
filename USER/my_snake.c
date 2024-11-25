#include "my_snake.h"

//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3		
unsigned char draw_background[16][16];

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//PA2 作为模拟通道输入引脚 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_71Cycles5  );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(1);
	}
	return temp_val/times;
} 	 


//8*8led IO口初始化
/*
D：PA3
C：PA4
B：PA5
A：PA6
G：PA7
DI：PA8
CLK：PA9
LAT：PA10
*/
void LedarrayIO_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//PA
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);	

}
/*扫描第几行*/
void scan_line(int linenum)
{
		int binary[4] = {0}, i = 3,num = linenum;
		int j;
	//	uint16_t IO[] = {ArrayLed_D,ArrayLed_C,ArrayLed_B,ArrayLed_A};
		
    while (num > 0) {
        binary[i] = num % 2;
        num = num / 2;
        i--;
    }
		ArrayLed_D=binary[0];
		ArrayLed_C=binary[1];
		ArrayLed_B=binary[2];
		ArrayLed_A=binary[3];
		
		//for(j = 0; j < 4 ; j++)SetIO(IO[j],binary[j]);
		
}
/*
设置io高低
*/
void SetIO(uint16_t ArrayLed_IO,int num)
{
	if(num)GPIO_SetBits(GPIOA,ArrayLed_IO);
	else GPIO_ResetBits(GPIOA,ArrayLed_IO);
}
//清空点阵
void draw_Clear(void)
{
	int i,j;
	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			draw_background[i][j]=0;
}
//显示灯阵
void Display(void)					
{
	int i,j;
	for( i = 0 ; i < 16 ; i++ )
	{		
		//ArrayLed_G=1;//更新数据时候关闭显示。等更新完数据，打开138显示行。防止重影。

		ArrayLed_CLK=0;
		delay_us(5);	
		ArrayLed_LAT=0;
		delay_us(5);
		
		for(j=15;j>=0;j--)
		{
			if(draw_background[i][j]==0)ArrayLed_DI=1;
			else if(draw_background[i][j]==1)ArrayLed_DI=0;
			//ArrayLed_DI=1;
//			ArrayLed_CLK=0;
//				delay_us(10);
			ArrayLed_CLK=1;				//上升沿发送数据
				delay_us(5);
			ArrayLed_CLK=0;
				delay_us(5);
		}


		ArrayLed_LAT=1;			//锁存数据
		delay_us(5);

		ArrayLed_LAT=0;
		delay_us(5);

		scan_line(i);						//选择第i行
		delay_us(5);
		ArrayLed_G=0;
		delay_us(800);				
	}	
}

