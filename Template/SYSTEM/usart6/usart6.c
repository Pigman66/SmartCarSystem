#include "usart6.h"


//Usart6的缓冲区长度
uint16_t usart6_length = 0;

uint8_t voice_falg = 0;

void USART6_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

	//打开时钟
    RCC_AHB1PeriphClockCmd(USART6_TX_CLK | USART6_RX_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(USART6_CLK, ENABLE);

    //设置复用
    GPIO_PinAFConfig(USART6_TX_PORT, GPIO_PinSource6, GPIO_AF_USART6);
    GPIO_PinAFConfig(USART6_RX_PORT, GPIO_PinSource7, GPIO_AF_USART6);

    //GPIOC6 - Tx
    GPIO_InitStructure.GPIO_Pin = USART6_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(USART6_TX_PORT, &GPIO_InitStructure);

    //GPIOC7 - Rx
    GPIO_InitStructure.GPIO_Pin = USART6_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(USART6_RX_PORT, &GPIO_InitStructure);

    //usart外设初始化
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_Init(USART6, &USART_InitStructure);

    //usart中断初始化
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //使能接收中断
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

    //是能usart6
    USART_Cmd(USART6, ENABLE);
}


uint8_t usart6_buffer[USART6_RX_SIZE] = { 0 };
uint8_t usart6_flag = 0;	
uint8_t usart6_date = 0;	
/*中断服务函数*/
void USART6_IRQHandler(void)
{
	if(USART_GetITStatus(USART6, USART_IT_RXNE) == SET)
	{
		usart6_date = USART_ReceiveData(USART6);

		if (usart6_flag == 0x00)
		{
			//接收到自定义数据帧
			if (usart6_date == 0x55)				
			{
			 usart6_flag = 0x01;
			 usart6_buffer[0] = usart6_date;	
			 usart6_buffer[1] = 0x00;
			 usart6_buffer[2] = 0x00;
			 usart6_buffer[3] = 0x00;
			}
		}
		else if (usart6_flag == 0x01)
		{
			usart6_flag = 0x02;
			usart6_buffer[1] = usart6_date;		
		}
		else if(usart6_flag == 0x02)
		{
			usart6_flag = 0x03;
			usart6_buffer[2] = usart6_date;
			voice_falg = 0x01;					
		}
		else if(usart6_flag == 0x03)
		{
			usart6_flag = 0x00;
			usart6_buffer[3] = usart6_date;			 
		}
		else
		{
			usart6_flag = 0x00;
			voice_falg = 0x00;
			usart6_buffer[0] = 0x00;
		}
	}

    USART_ClearITPendingBit(USART6, USART_IT_RXNE);
}

/*发送一个字节数据*/
void USART6_Send_Byte(uint8_t src)
{
    USART_SendData(USART6, src);

    while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
}

/*发送多个字节数据*/
void USART6_SendLength(uint8_t *src, uint16_t length)
{
    uint16_t Tx_cut = 0;
    uint16_t Tx_length = 0;
    Tx_length = length;

    while(Tx_cut != Tx_length)
    {
        USART6_Send_Byte(*(src + Tx_cut));
        Tx_cut++;
    }
}

/*发送字符串*/
void USART6_SendString(char *src)
{
    uint16_t Tx_cut = 0;

    while(*(src + Tx_cut) != '\0')
    {
        USART6_Send_Byte(*(src + Tx_cut));
        Tx_cut++;
    }
}

/*清空缓冲区*/
void USART6_Clear_Buffer(void)
{
    while(usart6_length)	  
    {
        usart6_length--;
        usart6_buffer[usart6_length] = 0;
    }
}
