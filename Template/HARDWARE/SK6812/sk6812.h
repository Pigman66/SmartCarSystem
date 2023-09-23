#ifndef  __SK6812_H
#define  __SK6812_H
#include "stm32f4xx.h"

#define  SK6812_CLK		RCC_AHB1Periph_GPIOG
#define  SK6812_PORT	GPIOG
#define  SK6812_PIN		GPIO_Pin_4

void SK6812_Init(void);

#endif