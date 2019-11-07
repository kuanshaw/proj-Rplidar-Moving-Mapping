#ifndef __KEY_H
#define __KEY_H
#include <sys.h>

#define K_UP GPIO_Pin_0					//PA0
#define K_RIGHT GPIO_Pin_4			//PE4
#define K_DOWN GPIO_Pin_3
#define K_LEFT GPIO_Pin_2

#define k_up GPIO_ReadInputDataBit(GPIOA, K_UP)
#define k_right GPIO_ReadInputDataBit(GPIOE, K_RIGHT)
#define k_down GPIO_ReadInputDataBit(GPIOE, K_DOWN)
#define k_left GPIO_ReadInputDataBit(GPIOE, K_LEFT)

#define GET_UP 1 
#define GET_RIGHT 2
#define GET_DOWN 3
#define GET_LEFT 4


void Key_Init(void);
u8 Key_Scan(void);

#endif

