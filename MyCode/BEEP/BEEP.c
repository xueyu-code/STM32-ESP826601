#include "BEEP.h"
#include "delay.h"

#define beep_pin  GPIO_Pin_0
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = beep_pin;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.0

 GPIO_SetBits(GPIOB,beep_pin);	

}
 
void BEEP_ON(){ 

	//��������һ��
	GPIO_ResetBits(GPIOB,beep_pin);		//�͵�ƽ
	delay_ms(1000);
	GPIO_SetBits(GPIOB,beep_pin);			//�ߵ�ƽ
}
