#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "usart2.h"
#include "timer.h"
#include "gizwits_product.h"
#include "math.h"
#include "adc.h"
#include "stm32f10x_adc.h"
#include "BEEP.h"
#include "dht11.h"

//����
int flag=0;
int MQ2_flag,Heat_flag,hum_flag,tmp_flag;
int MQ2_threshold,MQ5_threshold,MQ9_threshold,fire_threshold,tmp_threshold,hum_threshold;
int beep_flag=0;
int tmp_data,hum_data;
uint16_t Heat,MQ2,MQ5,MQ9;/*Heat�����洫������MQ2:�����⣬MQ5:ú��Һ������⣬MQ9:��ȼ������*/
int main(void)
{	

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	adc_Init();
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear()  	; 
	TIM3_Int_Init(71,999);				//һ���붨ʱ
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	usart3_init((u32)9600);//WIFI��ʼ��
	gizwitsInit();//��������ʼ��
//	
//	gizwitsSetMode(WIFI_RESET_MODE);
	delay_ms(500);
//	gizwitsSetMode(WIFI_AIRLINK_MODE);
	
	gizwitsSetMode(WIFI_SOFTAP_MODE);
	BEEP_Init();
	BEEP_ON();

	
	while(DHT11_Init())//�ȴ�DHT11��ʼ�����
	{;}

	OLED_ShowString(0,0,"Fire:",16);
	OLED_ShowString(0,2,"Smoke:",16);
	OLED_ShowString(0,4,"Temp:",16);
	OLED_ShowString(0,6,"Hum:",16);
	
	while(1)
	{


		
		Heat = AD_GetValue(ADC_Channel_2);/*��ȡ��������ֵ*/
		MQ2 = AD_GetValue(ADC_Channel_1);
		DHT11_Read_Data(&tmp_data,&hum_data);
		
		
		//������ر�������ֵ���
		if(MQ2>MQ2_threshold&&beep_flag==1)//�����ⱨ��
		{
			MQ2_flag=1;
			BEEP_ON();
		}
		else
		{
			MQ2_flag=0;
		}
		///////////////////////
		if(Heat<fire_threshold&&beep_flag==1)//�����ⱨ��
		{
			Heat_flag=1;
			BEEP_ON();
		}
		else
		{
			Heat_flag=0;
		}
		
		if(tmp_data>tmp_threshold&&beep_flag==1)//�¶ȼ�ⱨ��
		{
			tmp_flag=1;
			BEEP_ON();
		}
		else
		{
			tmp_flag=0;
		}
		
		
				
		if(hum_data>hum_threshold&&beep_flag==1)//ʪ�ȼ�ⱨ��
		{
			hum_flag=1;
			BEEP_ON();
		}
		else
		{
			hum_flag=0;
		}
		
		
		userHandle();
    gizwitsHandle((dataPoint_t *)&currentDataPoint);
//		/////////////////////
	
		OLED_ShowNum(70,0,Heat,3,16);
		OLED_ShowNum(70,2,MQ2,3,16);
		OLED_ShowNum(70,4,tmp_data,3,16);
		OLED_ShowNum(70,6,hum_data,3,16);

}
}









