#ifndef __TIM_H
#define __TIM_H
#include "stm32f4xx.h"

#define  TIM4_CLK			RCC_APB1Periph_TIM4
#define  TIM4_CH1_CLK		RCC_AHB1Periph_GPIOD
#define  TIM4_CH1_PORT		GPIOD
#define  TIM4_CH1_PIN		GPIO_Pin_12
#define  TIM4_CH2_CLK		RCC_AHB1Periph_GPIOD
#define  TIM4_CH2_PORT		GPIOD
#define  TIM4_CH2_PIN		GPIO_Pin_13

#define  TIM14_CLK			RCC_APB1Periph_TIM14
#define  TIM14_CH1_CLK		RCC_AHB1Periph_GPIOF
#define  TIM14_CH1_PORT		GPIOF
#define  TIM14_CH1_PIN		GPIO_Pin_9

void TIM4_PWMInit(uint32_t prescaler, uint32_t reload);
void TIM14_PWMInit(uint32_t prescaler, uint32_t reload);

#endif