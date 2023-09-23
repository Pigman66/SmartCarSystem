#ifndef  __DHT11_H
#define  __DHT11_H
#include "stm32f4xx.h"
#include "delay.h"


#define  DHT11_CLK				RCC_AHB1Periph_GPIOF
#define	 DHT11_DQ_PORT			GPIOF
#define  DHT11_DQ_PIN			GPIO_Pin_8

#define  DHT11_DQ_In		GPIO_ReadInputDataBit(DHT11_DQ_PORT, DHT11_DQ_PIN)
#define  DHT11_DQ_Out(X)	GPIO_WriteBit(DHT11_DQ_PORT, DHT11_DQ_PIN, (BitAction)X)

u8 DHT11_Init(void);
void DHT11_Rst(void);
u8 DHT11_Check(void);
void DHT11_IO_In(void);
void DHT11_IO_Out(void);
u8 DHT11_ReadBit(void);
u8 DHT11_ReadByte(void);
u8 DHT11_ReadData(u16 *temp, u16 *humi);



#endif