#ifndef  __SYN7318_H
#define  __SYN7318_H
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#define  USART_BAUD		57600

/*命令*/
#define  VERSION_CMD	0x28

/*数据帧结构体*/
typedef struct 
{
	u8 header; 			/*帧头*/
	u8 datalen[2]; 		/*数据区长度，高字节在前*/
	u8 databuf[1024];	/*数据区*/
}SYN7318_DataFrameTypeDef;


void SYN7318_Init(void);

#endif