#include "sk6812.h"

void SK6812_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(SK6812_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = SK6812_PIN;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(SK6812_PORT, &gpio);

}

void SK6812_WriteLow(void) //写0
{
	DQ(1);
	//Delay_us(3);//延时0.3us，这里不需要延时
	DQ(0);
	Delay_us(3);
}

void SK6812_WriteHigh(void) //写1
{
	DQ(1);
	Delay_us(1);//延时1us
	DQ(0);
	Delay_us(3);
}

void SK6812_WriteReset(void) //写复位信号
{
	DQ(0);
	Delay_us(100);
}

/*向sk6812写一个字节*/
void SK6812_WriteByte(u8 data)
{
	u8 i;
	
	//高位先行
	for(i = 0; i < 8; i++)
	{
		if((data << i) & 0x80)
			SK6812_WriteHigh();
		else
			SK6812_WriteLow();
	}
}

void SK6812_WriteRGB(RGB_TypeDef *rgb)
{
	SK6812_WriteReset(); //复位
	SK6812_WriteByte(rgb->green);
	SK6812_WriteByte(rgb->red);
	SK6812_WriteByte(rgb->blue);
	SK6812_WriteReset(); //复位
}

/*呼吸灯*/
void SK6812_Breath(void)
{
	u8 i;
	RGB_TypeDef rgb;
	rgb.green = 0;
	rgb.red = 0;
	rgb.blue = 0;
	for(i = 0; i < 255; i++)
	{
		SK6812_WriteReset(); //复位
		SK6812_WriteByte(rgb.green);
		SK6812_WriteByte(rgb.red);
		SK6812_WriteByte(rgb.blue);
		Delay_ms(7);
		rgb.green++;
	}
	for(i = 0; i < 255; i++)
	{
		SK6812_WriteReset(); //复位
		SK6812_WriteByte(rgb.green);
		SK6812_WriteByte(rgb.red);
		SK6812_WriteByte(rgb.blue);
		Delay_ms(5);
		rgb.green--;
	}
}