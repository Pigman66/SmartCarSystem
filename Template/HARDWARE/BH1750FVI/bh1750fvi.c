#include "bh1750fvi.h"
#include "usart.h"
#include <stdio.h>

static float resolurtion = 0; //测量精度
u8 lightBuf[2];

u8 BH1750_Init(BH1750Mode_t mode)
{
	
	// BH1750上电
	BH1750_WriteByte(POWER_ON);
	
	// 复位BH1750
	BH1750_WriteByte(MODULE_RESET);
	
	//设置测试模式
	BH1750_WriteByte(OLMODE_CMD);
	
	switch(mode)
	{
		case CONTINUE_H_Mode:
			resolurtion = 1;
			break;
		case CONTINUE_H_Mode2:
			resolurtion = 0.5;
			break;
		case CONTINUE_L_Mode:
			resolurtion = 4;
			break;
		case ONETIME_H_Mode:
			resolurtion = 1;
			break;
		case ONETIME_H_Mode2:
			resolurtion = 0.5;
			break;
		case ONETIME_L_Mode:
			resolurtion = 4;
			break;
	}
	
}

/*读两次数据*/
void BH1750_ReadByte()
{
	u16 reVal;
	char buf[30];
	
	IIC_Start();
	IIC_SendByte(I2C_READ_ADDR); //发送设备地址
	while(IIC_WaitAck());
	lightBuf[0] = IIC_ReadByte(); //读取高8位数据
	sprintf(buf, "lightBuf[0]=%#x\r\n", lightBuf[0]);
	USART_SendString(USART1, buf);
	IIC_Ack();
	lightBuf[1] = IIC_ReadByte(); //读取低8位数据
	sprintf(buf, "lightBuf[1]=%#x\r\n", lightBuf[1]);
	USART_SendString(USART1, buf);
#if 0
	reVal |= IIC_ReadByte() << 8; //读取高8位数据
	IIC_Ack();
	reVal |= IIC_ReadByte() << 0; //读取低8位数据
#endif
	IIC_NAck();
	IIC_Stop();
}

/*写指令到BH1750*/
void BH1750_WriteByte(u8 data)
{
	IIC_Start(); //发送start信号
	IIC_SendByte(I2C_WRITE_ADDR); //发送设备地址
	while(IIC_WaitAck());
	IIC_SendByte(data); //发送数据
	while(IIC_WaitAck());
	IIC_Stop();
	
}

/*
计算光照度:
	光照强度（单位lx）=（High Byte + Low Byte）/ 1.2 * 测量精度
*/
float BH1750_GetLight()
{
	float reVal;
	BH1750_ReadByte();
	reVal = (float) ((lightBuf[0] + lightBuf[1]) / 1.2 * resolurtion);
	
	return reVal;
}

