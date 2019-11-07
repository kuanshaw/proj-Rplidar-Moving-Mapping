#include "sys.h"
#include "stdlib.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "beep.h"
#include "usart3.h"
#include "usart.h"
#include "pwm_motor.h"
#include "exti.h"

#include "rplidar.h"

void Init()	
{	
	//ģ���ʼ���б�
	delay_init(168);
	Key_Init();
	Led_Init();
	Beep_Init();
	LCD_Init();
	usart3_init(115200);		//����3
	uart_init(115200);			//����1
	Pwm_Init();
	LCD_Init();
	Exti_Init();

	STOP_FALG = 0;
	SCAN_FALG = 0;			//�ڽ��սڵ�����ʱ��SCAN_FALG�ض�Ϊ1
	
	//�����ʼ��
	delay_ms(100);
	LCD_Clear(GREEN);
	POINT_COLOR=BLACK;
	TIM_SetCompare1(TIM9, 0);		//���PWM//����
	
}

rplidar_response_measurement_node_t nodes[360];				//ȫ��

int main(void)
{
	//�����б�
	u8 temp=0;
	u16 len=0;
	u16 count=0;

	//��ʼ���жϷ���
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);		//�ж����ȼ�����
	
	Init();
	delay_ms(1000);	//�ȴ�һ��
	
	while(1)
	{			
		STOP_FALG = 0;
	
		temp++;
		if(temp==100)
			temp=0;
		LCD_ShowNum(30,40, temp, 24, 24);
		
		delay_ms(50);
		
		if(USART3_RX_STA)
		{
			len = USART3_RX_STA&0x3fff;
			count = len/5;
		//	Beep_Bi();
			
			if(SCAN_FALG==1)		//�����ɨ�����ݣ�����д���
			{
				Rplidar_BuildGroups(nodes, count);		//��������
				Rplidar_Manage_Data(nodes, count);		//���˽��
			}
			Rplidar_SendData(nodes, len, count);
			
			//memcpy(group, USART3_RX_BUF, len);		//���ṹ��ֵ��//��ʱ̫������
			
			USART3_RX_STA = 0;		//������
		}
	}
}









