#ifndef  __USART_H
#define  __USART_H
#include "stm32f4xx.h"

/*缓冲区大小*/
#define  USART_BUFFER_SIZE		50

#define  USART1_CLK				RCC_APB2Periph_USART1
#define  USART1_TX_PORT_CLK		RCC_AHB1Periph_GPIOA
#define  USART1_TX_PORT			GPIOA
#define  USART1_TX_PIN			GPIO_Pin_9
#define  USART1_RX_PORT_CLK		RCC_AHB1Periph_GPIOA
#define  USART1_RX_PORT			GPIOA
#define  USART1_RX_PIN			GPIO_Pin_10

#define  USART6_CLK				RCC_APB2Periph_USART6
#define  USART6_TX_PORT_CLK		RCC_AHB1Periph_GPIOC
#define  USART6_TX_PORT			GPIOC
#define  USART6_TX_PIN			GPIO_Pin_6
#define  USART6_RX_PORT_CLK		RCC_AHB1Periph_GPIOC
#define  USART6_RX_PORT			GPIOC
#define  USART6_RX_PIN			GPIO_Pin_7

void USART1_Init(u32 baudrate);
void USART6_Init(u32 baudrate);
void USART1_ClearBuf(void);
void USART6_ClearBuf(void);
void USART_SendByte(USART_TypeDef *USARTx, u8 data);
void USART_SendLength(USART_TypeDef *USARTx, u8 *data, u16 len);
void USART_SendString(USART_TypeDef *USARTx, char *str);


#endif