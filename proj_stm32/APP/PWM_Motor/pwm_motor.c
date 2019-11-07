#include "pwm_motor.h"


void Pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);					//开GPIOE的时钟	PE5
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM9, ENABLE);						//开定时器时钟9

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);				//映射复用引脚		//BEEP

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;						//PE5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//下拉！！
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseStructure.TIM_Period = 499;										//重装载值	定时器时钟为84mhz
	TIM_TimeBaseStructure.TIM_Prescaler = 83;									//分频系数	84/84=1；1/500=2khz，PWM频率2khz
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM调制模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//输出极性高！！！
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);														//初始化外设TIM9_CH1

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);										//使能预装载寄存器
	TIM_ARRPreloadConfig(TIM9, ENABLE);																	//ARP使能
	TIM_Cmd(TIM9, ENABLE);																							//使能定时器9

}	

