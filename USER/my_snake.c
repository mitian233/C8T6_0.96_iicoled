#include "my_snake.h"

//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3		
unsigned char draw_background[16][16];

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//PA2 ��Ϊģ��ͨ���������� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_71Cycles5  );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
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


//8*8led IO�ڳ�ʼ��
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
void LedarrayIO_init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//PA
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);	

}
/*ɨ��ڼ���*/
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
����io�ߵ�
*/
void SetIO(uint16_t ArrayLed_IO,int num)
{
	if(num)GPIO_SetBits(GPIOA,ArrayLed_IO);
	else GPIO_ResetBits(GPIOA,ArrayLed_IO);
}
//��յ���
void draw_Clear(void)
{
	int i,j;
	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			draw_background[i][j]=0;
}
//��ʾ����
void Display(void)					
{
	int i,j;
	for( i = 0 ; i < 16 ; i++ )
	{		
		//ArrayLed_G=1;//��������ʱ��ر���ʾ���ȸ��������ݣ���138��ʾ�С���ֹ��Ӱ��

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
			ArrayLed_CLK=1;				//�����ط�������
				delay_us(5);
			ArrayLed_CLK=0;
				delay_us(5);
		}


		ArrayLed_LAT=1;			//��������
		delay_us(5);

		ArrayLed_LAT=0;
		delay_us(5);

		scan_line(i);						//ѡ���i��
		delay_us(5);
		ArrayLed_G=0;
		delay_us(800);				
	}	
}

