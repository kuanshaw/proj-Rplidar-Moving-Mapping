#include "beep.h"
#include "delay.h"

void Beep_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	delay_init(168);
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);  									//����
}

void Beep_Bi()
{
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
	delay_ms(20);
	GPIO_ResetBits(GPIOF,GPIO_Pin_8); 
}

