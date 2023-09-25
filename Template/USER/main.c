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
#include "bkrcspeak.h"
#include <stdio.h>

extern u8 usart1_buff[USART_BUFFER_SIZE];
extern u32 buff_len;

int main(void)
{
	u16 temp = 0, humi = 0;
	float light;
	char buf[50];
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	USART1_Init(115200);
	USART6_Init(115200);
	//USART6_Init(57600);
	DHT11_Init();
	BEEP_Init();
	TIM14_PWMInit(84-1, 1000);
	TIM4_PWMInit(84-1, 1000);
	//TIM_SetCompare1(TIM14, 500);
	//IIC_Init();
	//BH1750_Init(ONETIME_H_Mode);
	//DRV8837_Mode(DRV8837_Mode2);
	USART_SendString(USART1, "Test Video\r\n");
	
	while(1)
	{
#if 0 //测试DHT11
		if(DHT11_ReadData(&temp, &humi) != 0)
			USART1_SendString("fail\r\n");
		sprintf(buf, "temp:%2.1f\r\n", temp/10.0);
		USART_SendString(USART1, buf);
		sprintf(buf, "humi:%d\r\n", humi/10);
		USART_SendString(USART1, buf);
		Delay_ms(500);	
#endif
				
		
#if 0	//测试BH1750
		sprintf(buf, "light:%2.1f lx\r\n", BH1750_GetLight());
		USART_SendString(USART1, buf);
		Delay_ms(500);	
#endif
		Voice_Control();
	} 
}

