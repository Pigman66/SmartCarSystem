#include "stm32f4xx.h"
#include "led.h" 

/*******************************************************************
功  能：LED IO初始化  
参  数: 无
返回值: 无
********************************************************************/
void LED_Hardware_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	//使能GPIOE时钟

	//GPIOE2，E3，E4，E5初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 
								| GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);					//初始化GPIO

}

