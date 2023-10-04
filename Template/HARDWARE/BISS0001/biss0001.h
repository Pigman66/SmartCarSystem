#ifndef  __BISS0001_H
#define  __BISS0001_H
#include "stm32f4xx.h"

#define  BISS0001_OUT_CLK	RCC_AHB1Periph_GPIOG
#define  BISS0001_OUT_PORT	GPIOG
#define  BISS0001_OUT_PIN	GPIO_Pin_11

#define  BISS0001_In()		GPIO_ReadInputDataBit(BISS0001_OUT_PORT, BISS0001_OUT_PIN)

void BISS0001_Init(void);

#endif