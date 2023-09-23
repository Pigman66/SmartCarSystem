#include "syn7318.h"

/*初始化SYN7318*/
void SYN7318_Init(void)
{	
	SYN7318_DataFrameTypeDef frame;
	
	//初始化串口6与SYN7318通信
	USART6_Init(USART_BAUD);
	
	frame.header = 0xFD;
	frame.datalen[0] = 0; //高位
	frame.datalen[1] = 1; //低位
	frame.databuf[0] = VERSION_CMD;
	
	//获取当前设备的版本号
	
	
}

/*发送一个数据帧*/
void SYN7318_SendFrameData(SYN7318_DataFrameTypeDef frame)
{
	u8 i;
	u16 datalen, tmp;
	
	datalen = (frame.datalen[0] << 8) | (frame.datalen[1] << 0); 
	USART_SendByte(USART6, frame.header);
	Delay_ms(2);
	for(i = 0; i < 16; i++)
	{
		tmp = (datalen & 0x80);
	}
	
	
	for(i = 0; i < datalen; i++)
	{
	}
}