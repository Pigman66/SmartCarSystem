#ifndef __C1016_H_
#define __C1016_H_

#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "beep.h"
#include "usart6.h"
#include "tim.h"
#include <stdio.h>

#define RXBUFFERSIZE 26
extern uint8_t aRxBuffer[100];
extern uint8_t c1016_rx_flag ;          //串口接收完成标志
extern uint8_t c1016_identify_key;      //录入标志
extern uint8_t c1016_identify_state;    //指纹识别标志位
extern uint8_t c1016_identify_id_select;//指定识别ID
extern uint8_t c1016_Weakup_flag;       //指纹检测标志
extern uint16_t setidnnumber;           //录入ID

#define TOUCHOUT_CLK		RCC_AHB1Periph_GPIOG
#define TOUCHOUT_PORT		GPIOG
#define TOUCHOUT_PIN		GPIO_Pin_0
#define TOUCHOUT_EXTILINE	EXTI_Line0

#define C1016_COLOR_MODE_RESPIRE 1 		   //呼吸
#define C1016_COLOR_MODE_QUAICT_RESPIRE 2  //快闪
#define C1016_COLOR_MODE_NORMALLY_OPEN  3  //常开
#define C1016_COLOR_MODE_NORMAL_CLOSE 4    //常闭
#define C1016_COLOR_MODE_GRADUALLY_OPEN 5  //渐开
#define C1016_COLOR_MODE_GRADUALLY_CLOSE 6 //渐关
#define C1016_COLOR_MODE_SLOW_RESPIRE 7    //慢闪

#define C1016_COLOR_GREEN 1
#define C1016_COLOR_RED 2
#define C1016_COLOR_BLUE 4

void C1016_Data_Verification(uint8_t *da,uint8_t len);
void C1016_Enroll(uint16_t id_number);
void C1016_Identify(void);
void C1016_Send_Data(uint8_t *da, uint8_t len);
void C1016_Init(void);
void C1016_cmd_Delete(void);
#endif

