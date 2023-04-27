#include "BEEP.h"
#include "delay.h"

#define beep_pin  GPIO_Pin_0
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = beep_pin;				 //
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.0

 GPIO_SetBits(GPIOB,beep_pin);	

}
 
void BEEP_ON(){ 

	//蜂鸣器响一声
	GPIO_ResetBits(GPIOB,beep_pin);		//低电平
	delay_ms(1000);
	GPIO_SetBits(GPIOB,beep_pin);			//高电平
}
