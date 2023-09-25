#ifndef  __SK6812_H
#define  __SK6812_H
#include "stm32f4xx.h"
#include "delay.h"

#define  SK6812_CLK		RCC_AHB1Periph_GPIOG
#define  SK6812_PORT	GPIOG
#define  SK6812_PIN		GPIO_Pin_4

#define  DQ(X)	GPIO_WriteBit(SK6812_PORT, SK6812_PIN, (BitAction)(X))

//rgb数据结构体
typedef struct
{
	u8 green;
	u8 red;
	u8 blue;
}RGB_TypeDef;

void SK6812_Init(void);
void SK6812_WriteLow(void);
void SK6812_WriteHigh(void);
void SK6812_WriteReset(void);
void SK6812_WriteByte(u8 data);
void SK6812_WriteRGB(RGB_TypeDef *rgb);
void SK6812_Breath(void);

#endif