#include "tim.h"

/*初始化通用定时器4输出PWM方波，驱动电机*/
void TIM4_PWMInit(uint32_t prescaler, uint32_t reload)
{
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef timebase;
	TIM_OCInitTypeDef octime;

	//使能定时器4时钟
	RCC_APB1PeriphClockCmd(TIM4_CLK, ENABLE);

	//使能定时器4的通道1和通道2的GPIO时钟
	RCC_AHB1PeriphClockCmd(TIM4_CH1_CLK | TIM4_CH2_CLK, ENABLE);

	//复用
	GPIO_PinAFConfig(TIM4_CH1_PORT, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(TIM4_CH2_PORT, GPIO_PinSource13, GPIO_AF_TIM4);

	//配置ch1的gpio
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = TIM4_CH1_PIN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(TIM4_CH1_PORT, &gpio);

	//配置ch2的gpio
	gpio.GPIO_Pin = TIM4_CH2_PIN;
	GPIO_Init(TIM4_CH2_PORT, &gpio);

	/*初始化定时器基础时序*/
	timebase.TIM_ClockDivision = TIM_CKD_DIV1;
	timebase.TIM_Prescaler = prescaler;
	timebase.TIM_Period = reload;
	timebase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &timebase);

	/*初始化定时器通道1*/
	octime.TIM_OCMode = TIM_OCMode_PWM1;
	octime.TIM_OutputState = TIM_OutputState_Enable;
	octime.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &octime);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/*初始化定时器通道2*/
	TIM_OC2Init(TIM4, &octime);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	TIM_SetCompare1(TIM4, 0);
	TIM_SetCompare2(TIM4, 0);
	
	TIM_Cmd(TIM4, ENABLE); //使能TIM4

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
	
	TIM_SetCompare1(TIM14, 0);
	
	TIM_Cmd(TIM14, ENABLE); //使能TIM14
	
}