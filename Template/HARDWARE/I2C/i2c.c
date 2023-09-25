#include "i2c.h"
#include "usart.h"
#include <stdio.h>


/*初始化I2C2*/
void IIC_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	/*使能I2C2的SCL、SDA引脚时钟*/
	RCC_AHB1PeriphClockCmd(SCL_PORT_CLK | SDA_PORT_CLK, ENABLE);
	
	/*初始化SCL引脚*/
	gpio.GPIO_Pin = SCL_PIN;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(SCL_PORT, &gpio);
	
	/*初始化SDA引脚*/
	gpio.GPIO_Pin = SDA_PIN;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(SDA_PORT, &gpio);
	
	GPIO_SetBits(SCL_PORT, SCL_PIN);
	GPIO_SetBits(SDA_PORT, SDA_PIN);
	
}

/*产生一个起始信号*/
void IIC_Start(void)
{
	
	SCL_High();
	SDA_High();
	Delay_us(4);
	SDA_Low();
	Delay_us(4);
	SCL_Low();
	Delay_us(2);
}

/*产生一个stop信号*/
void IIC_Stop(void)
{
	SDA_Low();
	Delay_us(2);
	SCL_High();
	Delay_us(4);
	SDA_High();
	Delay_us(4);
}

/*产生一个ACK信号*/
void IIC_Ack(void)
{
	SCL_Low();
	Delay_us(2);
	SDA_Low();
	Delay_us(2);
	SCL_High();
	Delay_us(4);
	SCL_Low();
}

/*产生一个NACK信号*/
void IIC_NAck(void)
{
	SCL_Low();
	Delay_us(2);
	SDA_High();
	Delay_us(2);
	SCL_High();
	Delay_us(4);
	SCL_Low();
}


/*等待ACK应答信号*/
u8 IIC_WaitAck(void)
{
	u8 timeout = 0;
	char buf[50];
	SCL_Low();
	Delay_us(1);
	SDA_High();
	Delay_us(1);
	SCL_High();
	Delay_us(1);
	
	sprintf(buf, "SDA:%d\r\n", SDA_Data());
	USART_SendString(USART1, buf);
	
	while(SDA_Data()) //等于1没有接受到ACK信号
	{
		timeout++;
		if(timeout >= 250)
		{
			IIC_Stop(); //发送一个停止信号
			return 1;
		}
	}
	SCL_Low();
	Delay_us(2);
	return 0;
}

/*发送一个字节*/
void IIC_SendByte(u8 data)
{
	u8 i;
	SCL_Low();
	for(i = 0; i < 8; i++)
	{
		if(data & 0x80)
			SDA_High();
		else
			SDA_Low();
		
		Delay_us(2);
		SCL_High();
		Delay_us(2);
		SCL_Low();
		Delay_us(2);
		data <<= 1;
	}
	SDA_High(); //释放SDA线
}

u8 IIC_ReadByte(void)
{
	u8 i;
	u8 reVal = 0;
	
	for(i = 0; i < 8; i++)
	{
		SCL_Low();
		Delay_us(2);
		SCL_High();
		reVal <<= 1;
		if(SDA_Data())
			reVal++;
		Delay_us(2);
	}
	
	return reVal;
}

