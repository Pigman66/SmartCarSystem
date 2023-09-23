#include "beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(BEEP_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = BEEP_PIN;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(BEEP_PORT, &gpio);
	
	GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
}