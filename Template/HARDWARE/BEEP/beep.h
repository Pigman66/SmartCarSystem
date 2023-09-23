#ifndef  __BEEP_H
#define  __BEEP_H
#include "stm32f4xx.h"

#define  BEEP_CLK		RCC_AHB1Periph_GPIOA
#define  BEEP_PORT		GPIOA
#define  BEEP_PIN		GPIO_Pin_15

#define  BEEP_On()		GPIO_SetBits(BEEP_PORT, BEEP_PIN)
#define  BEEP_Off()		GPIO_ResetBits(BEEP_PORT, BEEP_PIN)

void BEEP_Init(void);

#endif