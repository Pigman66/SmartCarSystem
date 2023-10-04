#ifndef  __BKRCSPEAK_H
#define  __BKRCSPEAK_H
#include "stm32f4xx.h"
#include "usart6.h"
#include "led.h"

#define  CTRL_CLK	RCC_AHB1Periph_GPIOG
#define  CTRL_PORT	GPIOG
#define  CTRL_PIN	GPIO_Pin_4

#define  CTRL_On()		GPIO_ResetBits(CTRL_PORT, CTRL_PIN)
#define  CTRL_Off()		GPIO_SetBits(CTRL_PORT, CTRL_PIN)

void Voice_Init(void);
u8 Video_Get(void);
void Voice_Control(void);

#endif