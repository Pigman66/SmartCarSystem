#ifndef __LED_H_
#define __LED_H_

#include "sys.h"

#define LED0(X) GPIO_WriteBit(GPIOE,GPIO_Pin_2,(BitAction)X)	// LED0
#define LED1(X) GPIO_WriteBit(GPIOE,GPIO_Pin_3,(BitAction)X)	// LED1	 
#define LED2(X) GPIO_WriteBit(GPIOE,GPIO_Pin_4,(BitAction)X)	// LED2
#define LED3(X) GPIO_WriteBit(GPIOE,GPIO_Pin_5,(BitAction)X)	// LED3	

void LED_Hardware_Init(void);

#endif
