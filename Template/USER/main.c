#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "dht11.h"
#include "tim.h"
#include "i2c.h"
#include "bh1750fvi.h"
#include "drv8837.h"
#include "usart6.h"
#include "sk6812.h"
#include "bkrcspeak.h"
#include "biss0001.h"
#include "sg90.h"
#include <stdio.h>

extern u8 usart1_buff[USART_BUFFER_SIZE];
extern u32 buff_len;

int main(void)
{
	u16 temp = 0, humi = 0;
	float light;
	RGB_TypeDef rgb;
	char buf[50];
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	USART1_Init(115200);			/*初始化串口1*/
	DHT11_Init();					/*初始化温湿度传感器*/
	BEEP_Init();					/*初始化蜂鸣器*/
	TIM14_PWMInit(84-1, 1000);		/*初始化定时器，驱动风扇*/
	TIM13_PWMInit(84-1, 3000);		/*初始化定时器，驱动舵机*/
	IIC_Init();						/*初始化IIC2*/
	BH1750_Init();					/*初始化光照传感器*/
	//DRV8837_Mode(DRV8837_Mode1);	/*初始化电机*/
	Voice_Init();					/*初始化语音助手*/
	SK6812_Init();					/*初始化可变LED灯*/
	BISS0001_Init();				/*初始化红外热释电传感器*/
	
	while(1)
	{
		
		DHT11_ReadData(&temp, &humi);
		sprintf(buf, "temp:%2.1f\r\n", temp/10.0);
		USART_SendString(USART1, buf);
		sprintf(buf, "humi:%d\r\n", humi/10);
		USART_SendString(USART1, buf);
		
		if(temp/10.0 >= 30.0)
			TIM_SetCompare1(TIM14, 500);
		else
			TIM_SetCompare1(TIM14, 0);
		
		light = BH1750_GetLight();
		sprintf(buf, "light:%2.1f lx\r\n", light);
		USART_SendString(USART1, buf);
		if(light > 100)
			SG90_Half();
		else
			SG90_Full();
		
		if(BISS0001_In() == 1)
		{
			USART_SendString(USART1, "no person\r\n");
			CTRL_Off();
		}
		else
		{
			USART_SendString(USART1, "person\r\n");
			CTRL_On();
		}

		
		//BH1750_Test();
		//Delay_ms(500);	
		//Voice_Control();

#if 0		
		//测试可变LED灯
		rgb.green = 0xFF;
		rgb.red = 0x00;
		rgb.blue = 0x00;
		SK6812_WriteRGB(&rgb);
		Delay_ms(500);
		rgb.green = 0x00;
		rgb.red = 0xFF;
		rgb.blue = 0x00;
		SK6812_WriteRGB(&rgb);
		Delay_ms(500);
		rgb.green = 0x00;
		rgb.red = 0x00;
		rgb.blue = 0xFF;
		SK6812_WriteRGB(&rgb);
		Delay_ms(500);
#endif
		//SK6812_Breath();

#if 0
		SG90_Half();
		Delay_ms(1000);
		SG90_Stop();
		Delay_ms(1000);
		SG90_Full();
		Delay_ms(1000);
#endif
		
		Delay_ms(50);

	} 
}

