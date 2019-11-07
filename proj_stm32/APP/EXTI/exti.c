#include "exti.h"
#include "key.h"
#include "delay.h"
#include "beep.h"
#include "usart3.h"

#include "rplidar.h"

void Exti_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE);				//

	//
	GPIO_InitStructure.GPIO_Pin = K_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;				//输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = K_RIGHT | K_DOWN | K_LEFT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//GPIO与中段线的映射关系
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
	//外部中断配置
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//UP
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//RIGHT
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//DOWN	//STOP
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//LEFT
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}


//外部中断函数
void EXTI0_IRQHandler(void)				//UP
{
	delay_ms(10);
	if(k_up)
	{
		//Beep_Bi();
		TIM_SetCompare1(TIM9, 500);
		Send_Cmd(RPLIDAR_CMD_SCAN);
		SCAN_FALG = 1;
	}
	while(k_up);
	/*
	while(!USART3_RX_STA)		//
	{
		Send_Cmd(RPLIDAR_CMD_SCAN);
	}
	*/
	EXTI_ClearITPendingBit(EXTI_Line0);		//清除中断标志
}

void EXTI2_IRQHandler(void)				//LEFT
{
	delay_ms(10);
	if(!k_left)
	{
		//Beep_Bi();
		Send_Cmd(RPLIDAR_CMD_GET_DEVICE_HEALTH);
	}
	while(!k_left);
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)				//DOWN
{
	delay_ms(10);
	if(!k_down)
	{
		//Beep_Bi();
		Send_Cmd(RPLIDAR_CMD_STOP);
		TIM_SetCompare1(TIM9, 0);
		
		STOP_FALG = 1;			//中断标志置1
		SCAN_FALG = 0;
	}
	while(!k_down);
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)				//RIGHT
{
	delay_ms(10);
	if(!k_right)
	{
		//Beep_Bi();
		Send_Cmd(RPLIDAR_CMD_RESET);
	}
	while(!k_right);
	EXTI_ClearITPendingBit(EXTI_Line4);
}








