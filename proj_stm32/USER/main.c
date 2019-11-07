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
	//模块初始化列表
	delay_init(168);
	Key_Init();
	Led_Init();
	Beep_Init();
	LCD_Init();
	usart3_init(115200);		//串口3
	uart_init(115200);			//串口1
	Pwm_Init();
	LCD_Init();
	Exti_Init();

	STOP_FALG = 0;
	SCAN_FALG = 0;			//在接收节点数据时，SCAN_FALG必定为1
	
	//程序初始化
	delay_ms(100);
	LCD_Clear(GREEN);
	POINT_COLOR=BLACK;
	TIM_SetCompare1(TIM9, 0);		//电机PWM//不动
	
}

rplidar_response_measurement_node_t nodes[360];				//全局

int main(void)
{
	//参数列表
	u8 temp=0;
	u16 len=0;
	u16 count=0;

	//初始化中断分组
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);		//中断优先级分组
	
	Init();
	delay_ms(1000);	//等待一秒
	
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
			
			if(SCAN_FALG==1)		//如果是扫描数据，则进行处理
			{
				Rplidar_BuildGroups(nodes, count);		//建立分组
				Rplidar_Manage_Data(nodes, count);		//过滤结点
			}
			Rplidar_SendData(nodes, len, count);
			
			//memcpy(group, USART3_RX_BUF, len);		//赋结构体值！//耗时太长！？
			
			USART3_RX_STA = 0;		//不接收
		}
	}
}









