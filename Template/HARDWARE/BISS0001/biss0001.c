#include "biss0001.h"

void BISS0001_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(BISS0001_OUT_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Pin = BISS0001_OUT_PIN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(BISS0001_OUT_PORT, &gpio);
}