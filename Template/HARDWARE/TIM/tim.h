#ifndef __TIM_H
#define __TIM_H
#include "stm32f4xx.h"

extern volatile uint32_t global_times;
extern volatile uint32_t delay_ms_const;

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
void TIM3_Init(uint16_t arr,uint16_t psc);
u32 gt_get_sub(u32 c);
u32 gt_get(void);

#endif