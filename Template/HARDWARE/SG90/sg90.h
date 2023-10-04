#ifndef  __SG90_H
#define  __SG90_H
#include "stm32f4xx.h"
#include "tim.h"

#define  SG90_Stop()		TIM_SetCompare1(TIM13, 500)		//0
#define  SG90_Quarter()		TIM_SetCompare1(TIM13, 1000)	//45
#define  SG90_Half()		TIM_SetCompare1(TIM13, 1500)	//90
#define  SG90_Full()		TIM_SetCompare1(TIM13, 2500)	//180

#endif