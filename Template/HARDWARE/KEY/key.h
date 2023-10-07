#ifndef  __KEY_H
#define  __KEY_H
#include "stm32f4xx.h"
#include "delay.h"

#define KEY0_CLK	RCC_AHB1Periph_GPIOG
#define KEY0_PORT	GPIOG
#define KEY0_PIN	GPIO_Pin_13

#define KEY1_CLK	RCC_AHB1Periph_GPIOF
#define KEY1_PORT	GPIOF
#define KEY1_PIN	GPIO_Pin_13

#define KEY2_CLK	RCC_AHB1Periph_GPIOF
#define KEY2_PORT	GPIOF
#define KEY2_PIN	GPIO_Pin_14

#define KEY3_CLK	RCC_AHB1Periph_GPIOF
#define KEY3_PORT	GPIOF
#define KEY3_PIN	GPIO_Pin_15

#define Key0()		GPIO_ReadInputDataBit(KEY0_PORT, KEY0_PIN)
#define Key1()		GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)
#define Key2()		GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN)
#define Key3()		GPIO_ReadInputDataBit(KEY3_PORT, KEY3_PIN)

/*键值枚举*/
typedef enum
{
	NONE_Press = 0,
	KEY0_Press,
	KEY1_Press,
	KEY2_Press,
	KEY3_Press
}KEYPress;

void KEY_Init(void);
KEYPress KEY_Scan(u8 mode);

#endif