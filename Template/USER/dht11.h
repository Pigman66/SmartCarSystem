#ifndef  __DHT11_H
#define  __DHT11_H
#include "stm32f4xx.h"

#define  DHT11_CLK				RCC_APB2Periph_GPIOC
#define	 DHT11_DQ_PORT			GPIOC
#define  DHT11_DQ_PIN			GPIO_Pin_5

#define  DHT11_DQ_Out(x)	GPIO_WriteBit(DHT11_DQ_PORT, DHT11_DQ_PIN, (x))
#define  DHT11_DQ_In		GPIO_ReadInputDataBit(DHT11_DQ_PORT, DHT11_DQ_PIN)

u8 DHT11_Init(void);
void DHT11_Rst(void);
u8 DHT11_Check(void);
void DHT11_IO_In(void);
void DHT11_IO_Out(void);
u8 DHT11_ReadBit(void);
u8 DHT11_ReadByte(void);
u8 DHT11_ReadData(u16 *temp, u16 *humi);


#endif