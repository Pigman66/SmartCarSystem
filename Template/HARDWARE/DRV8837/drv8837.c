#include "drv8837.h"

void DRV8837_Mode(DRV8837_Mode_t mode)
{
	switch(mode)
	{
		case DRV8837_Mode1:
			TIM_SetCompare1(TIM4, 0);
			TIM_SetCompare2(TIM4, 0);
			break;
		case DRV8837_Mode2:
			TIM_SetCompare1(TIM4, 500);
			TIM_SetCompare2(TIM4, 0);
			break;
		case DRV8837_Mode3:
			TIM_SetCompare1(TIM4, 0);
			TIM_SetCompare2(TIM4, 500);
			break;
		case DRV8837_Mode4:
			TIM_SetCompare1(TIM4, 0);
			TIM_SetCompare2(TIM4, 0);
			break;
	}
}