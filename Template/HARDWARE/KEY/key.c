#include "key.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(KEY0_CLK | KEY1_CLK | KEY2_CLK | KEY3_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	
	gpio.GPIO_Pin = KEY0_PIN;
	GPIO_Init(KEY0_PORT, &gpio);
	
	gpio.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PORT, &gpio);
	
	gpio.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PORT, &gpio);
	
	gpio.GPIO_Pin = KEY3_PIN;
	GPIO_Init(KEY3_PORT, &gpio);
	
}

/*按键扫描，mode为1支持连按，为0不支持*/
KEYPress KEY_Scan(u8 mode)
{
	static u8 keyup = 1; //按键松开标志
	if(mode) 
		keyup = 1;
	if(keyup && ((Key0() == 0) || (Key1() == 0) || (Key2() == 0) || (Key3() == 0)))
	{
		Delay_ms(10);
		keyup = 0;
		if(Key0() == 0) return KEY0_Press;
		else if(Key1() == 0) return KEY1_Press;
		else if(Key2() == 0) return KEY2_Press;
		else if(Key3() == 0) return KEY3_Press;
	}
	else if((Key0() == 1) && (Key1() == 1) && (Key2() == 1) && (Key3() == 1))
		keyup = 1;
	
	return NONE_Press;
}

