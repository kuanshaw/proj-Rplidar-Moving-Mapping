#ifndef __EXTI_H
#define __EXTI_H
#include <sys.h>

#define K_UP GPIO_Pin_0					//PA0
#define K_RIGHT GPIO_Pin_4			//PE4
#define K_DOWN GPIO_Pin_3
#define K_LEFT GPIO_Pin_2

void Exti_Init(void);


#endif

