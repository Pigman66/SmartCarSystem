#ifndef __TIM_H
#define __TIM_H
#include "stm32f4xx.h"

#define  TIM13_CLK			RCC_APB1Periph_TIM13
#define  TIM13_CH1_CLK		RCC_AHB1Periph_GPIOF
#define  TIM13_CH1_PORT		GPIOF
#define  TIM13_CH1_PIN		GPIO_Pin_8

#define  TIM14_CLK			RCC_APB1Periph_TIM14
#define  TIM14_CH1_CLK		RCC_AHB1Periph_GPIOF
#define  TIM14_CH1_PORT		GPIOF
#define  TIM14_CH1_PIN		GPIO_Pin_9

void TIM13_PWMInit(uint32_t prescaler, uint32_t reload);
void TIM14_PWMInit(uint32_t prescaler, uint32_t reload);

#endif