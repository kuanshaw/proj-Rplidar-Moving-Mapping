#include "pwm_motor.h"


void Pwm_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);					//��GPIOE��ʱ��	PE5
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM9, ENABLE);						//����ʱ��ʱ��9

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);				//ӳ�临������		//BEEP

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;						//PE5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseStructure.TIM_Period = 499;										//��װ��ֵ	��ʱ��ʱ��Ϊ84mhz
	TIM_TimeBaseStructure.TIM_Prescaler = 83;									//��Ƶϵ��	84/84=1��1/500=2khz��PWMƵ��2khz
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM����ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//������Ըߣ�����
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);														//��ʼ������TIM9_CH1

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);										//ʹ��Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM9, ENABLE);																	//ARPʹ��
	TIM_Cmd(TIM9, ENABLE);																							//ʹ�ܶ�ʱ��9

}	

