#include "key.h"
#include "delay.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = K_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;				//输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = K_RIGHT | K_DOWN | K_LEFT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

u8 Key_Scan()
{
	//UP
	if(k_up == 1)
	{
		delay_ms(10);
		if(k_up == 1)
		{
			while(k_up);
			return GET_UP;
		}
	}
	//RIGHT
	if(k_right == 0)
	{
		delay_ms(10);
		if(k_right == 0)
		{
			while(!k_right);
			return GET_RIGHT;
		}
	}
	//DOWN
	if(k_down == 0)
	{
		delay_ms(10);
		if(k_down == 0)
		{
			while(!k_down);
			return GET_DOWN;
		}
	}
	//LEFT
	if(k_left == 0)
	{
		delay_ms(10);
		if(k_left == 0)
		{
			while(!k_left);
			return GET_LEFT;
		}
	}
	return 0;
}



