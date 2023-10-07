#include "tim.h"

volatile uint32_t global_times = 0;
volatile uint32_t delay_ms_const = 0;

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

void TIM3_Init(uint16_t arr,uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);				//使能TIM3时钟

	TIM_TimeBaseInitStructure.TIM_Period = arr;						//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;					//定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	//向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);				//初始化TIM3

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);						//允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE);	//使能定时器3

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;					//定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;		//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;				//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
	{
		global_times++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

u32 gt_get(void)
{
	return global_times;
}

u32 gt_get_sub(u32 c)
{
	if(c > global_times)
		c -= global_times;
	else
		c = 0;
	return c;
}
