#include "dht11.h"

u8 DHT11_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(DHT11_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Pin = DHT11_DQ_PIN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(DHT11_DQ_PORT, &gpio);
	GPIO_SetBits(DHT11_DQ_PORT, DHT11_DQ_PIN); //默认拉高信号线
	
	DHT11_Rst();
	
	return DHT11_Check();
}

/*产生DHT11复位信号*/
void DHT11_Rst(void)
{
	DHT11_IO_Out();
	DHT11_DQ_Out(0);
	Delay_ms(20);
	DHT11_DQ_Out(1);
	Delay_us(40);	
}

u8 DHT11_Check(void) 	   
{
	u8 retry=0;
	DHT11_IO_In();							
    while (DHT11_DQ_In && retry<100)		
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_In && retry<100)
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)return 1;	    
	return 0;
}

/*设置DHT11_DQ为输入*/
void DHT11_IO_In(void)
{
	GPIO_InitTypeDef gpio;
	
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Pin = DHT11_DQ_PIN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DHT11_DQ_PORT, &gpio);
}

/*设置DHT11_DQ为输出*/
void DHT11_IO_Out(void)
{
	GPIO_InitTypeDef gpio;
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Pin = DHT11_DQ_PIN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(DHT11_DQ_PORT, &gpio);
}

/*读取一个位的数据*/
u8 DHT11_ReadBit(void)
{
	u8 retry = 0;
	while(DHT11_DQ_In && retry < 100)//等待总线为低电平
	{
		retry++;
		Delay_us(1);
	}		
	retry = 0;
	while(!DHT11_DQ_In && retry < 100)//等待总线为高电平
	{
		retry++;
		Delay_us(1);
	}
	Delay_us(40);
	if(DHT11_DQ_In) return 1;
	else return 0;
}

/*读取一个字节的数据*/
u8 DHT11_ReadByte(void)
{
	u8 val = 0;
	u8 i;
	for(i = 0; i < 8; i++)
	{
		val <<= 1;
		val |= DHT11_ReadBit();
	}
	return val;
}

/*一次采样的数据*/
u8 DHT11_ReadData(u16 *temp, u16 *humi)
{
	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check() == 0)
	{
		for(i = 0; i < 5; i++)
			buf[i] = DHT11_ReadByte();
		
		if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
		{
		
			*humi = buf[0] * 10 + buf[1];
			*temp = buf[2] * 10 + buf[3];
		}
	}
	else return 1;
	
	return 0;
	
}


