#include "tim.h"

/*初始化通用定时器13输出PWM方波，驱动舵机*/
void TIM13_PWMInit(uint32_t prescaler, uint32_t reload)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef timebase;
	TIM_OCInitTypeDef octime;

	//使能定时器13时钟
	RCC_APB1PeriphClockCmd(TIM13_CLK, ENABLE);

	//使能定时器13的通道1和通道2的GPIO时钟
	RCC_AHB1PeriphClockCmd(TIM13_CH1_CLK, ENABLE);

	//复用
	GPIO_PinAFConfig(TIM13_CH1_PORT, GPIO_PinSource8, GPIO_AF_TIM13);

	//配置ch1的gpio
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = TIM13_CH1_PIN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(TIM13_CH1_PORT, &gpio);

	/*初始化定时器基础时序*/
	timebase.TIM_ClockDivision = TIM_CKD_DIV1;
	timebase.TIM_Prescaler = prescaler;
	timebase.TIM_Period = reload;
	timebase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM13, &timebase);

	/*初始化定时器通道1*/
	octime.TIM_OCMode = TIM_OCMode_PWM1;
	octime.TIM_OutputState = TIM_OutputState_Enable;
	octime.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM13, &octime);
	
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM13, ENABLE);
	
	TIM_Cmd(TIM13, ENABLE); //使能TIM13

}

/*初始化通用定时器14来输出PWM方波，驱动风扇转动*/
void TIM14_PWMInit(uint32_t prescaler, uint32_t reload)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef timebase;
	TIM_OCInitTypeDef octime;
	
	/*打开定时器通道1的GPIO时钟*/
	RCC_AHB1PeriphClockCmd(TIM14_CH1_CLK, ENABLE);
	
	/*打开定时器14的时钟*/
	RCC_APB1PeriphClockCmd(TIM14_CLK, ENABLE);
	
	/*将PF9做为TIM14的通道1*/
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);
	
	/*初始化定时器通道1的GPIO*/
	gpio.GPIO_Pin = TIM14_CH1_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(TIM14_CH1_PORT, &gpio);
	
	/*初始化定时器基础时序*/
	timebase.TIM_ClockDivision = TIM_CKD_DIV1;
	timebase.TIM_Prescaler = prescaler;
	timebase.TIM_Period = reload;
	timebase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM14, &timebase);
	
	/*初始化定时器通道1*/
	octime.TIM_OCMode = TIM_OCMode_PWM1;
	octime.TIM_OutputState = TIM_OutputState_Enable;
	octime.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM14, &octime);
	
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM14, ENABLE);

	
	TIM_Cmd(TIM14, ENABLE); //使能TIM14
	
}