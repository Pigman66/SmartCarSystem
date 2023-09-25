#include "usart.h"
#include "delay.h"
#include <stdio.h>

u8 usart1_buf[USART_BUFFER_SIZE] = {0};
u32 buf_len = 0;

void USART1_Init(u32 baudrate)
{
	
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart;
	NVIC_InitTypeDef nvic;
	
	/*是能USART1外设时钟*/
	RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE);
	
	/*使能TX和RXIO时钟*/
	RCC_AHB1PeriphClockCmd(USART1_TX_PORT_CLK | USART1_RX_PORT_CLK, ENABLE);
	
	GPIO_PinAFConfig(USART1_TX_PORT, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(USART1_RX_PORT, GPIO_PinSource10, GPIO_AF_USART1);

	/*初始化TX引脚*/
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_Pin = USART1_TX_PIN;
	GPIO_Init(USART1_TX_PORT, &gpio);
	
	/*初始化RX引脚*/
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_RX_PORT, &gpio);
	
	/*USART1初始化*/
	usart.USART_BaudRate = baudrate;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	USART_Init(USART1, &usart);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能串口接受中断
	
	/*USART1接受中断初始化*/
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&nvic);
	
	USART_Cmd(USART1, ENABLE);//使能USART1
}

/*清空缓冲区*/
void USART1_ClearBuf(void)
{
	while(buf_len)
	{
		usart1_buf[buf_len--] = 0;
	}
}

/*发送一个字节的数据给串口*/
void USART_SendByte(USART_TypeDef *USARTx, u8 data)
{
	USART_SendData(USARTx, data);
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
}

/*发送多个字节的数据给串口*/
void USART_SendLength(USART_TypeDef *USARTx, u8 *data, u16 len)
{
	
	u8 tx_len = 0;
	while(tx_len != len)
	{
		USART_SendByte(USARTx, *(data + tx_len));
		tx_len++;
	}
}

/*发送字符串*/
void USART_SendString(USART_TypeDef *USARTx, char *str)
{
	u8 i = 0;
	while(*(str + i) != '\0')
	{
		USART_SendByte(USARTx, *(str + i));
		i++;
	}
}

/*中断服务函数*/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		usart1_buf[buf_len] = USART_ReceiveData(USART1);
		buf_len++;
		if(buf_len == USART_BUFFER_SIZE)
			buf_len = 0;
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}



