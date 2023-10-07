#ifndef __USART6_H_
#define __USART6_H_
#include "stm32f4xx.h"


#define USART6_RX_SIZE 26

#define  USART6_CLK			RCC_APB2Periph_USART6
#define  USART6_TX_CLK		RCC_AHB1Periph_GPIOC
#define  USART6_TX_PORT		GPIOC
#define  USART6_TX_PIN		GPIO_Pin_6
#define  USART6_RX_CLK		RCC_AHB1Periph_GPIOC
#define  USART6_RX_PORT		GPIOC
#define  USART6_RX_PIN		GPIO_Pin_7

extern uint8_t usart6_buffer[];
extern uint16_t usart6_length;
extern uint8_t voice_falg;

void USART6_Hardware_Init(uint32_t baudrate);
void USART6_Send_Byte(uint8_t src);
void USART6_Send_Length_String(uint8_t *src, uint16_t length);
void USART6_Send_String(char *src);
void USART6_Clear_Buffer(void);


#endif

