#ifndef  __I2C_H
#define  __I2C_H
#include "stm32f4xx.h"
#include "delay.h"

#define  SCL_PORT_CLK		RCC_AHB1Periph_GPIOB
#define  SCL_PORT			GPIOB
#define  SCL_PIN			GPIO_Pin_1
#define  SDA_PORT_CLK		RCC_AHB1Periph_GPIOF
#define  SDA_PORT			GPIOF
#define  SDA_PIN			GPIO_Pin_10

#define  SCL_High()			GPIO_SetBits(SCL_PORT, SCL_PIN)
#define  SCL_Low()			GPIO_ResetBits(SCL_PORT, SCL_PIN)
#define  SDA_High()			GPIO_SetBits(SDA_PORT, SDA_PIN)
#define  SDA_Low()			GPIO_ResetBits(SDA_PORT, SDA_PIN)
#define  SDA_Data()			GPIO_ReadInputDataBit(SDA_PORT, SDA_PIN)


void IIC_Init(void);
void IIC_SDAOut(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Ack(void);
void IIC_NAck(void);
u8 IIC_WaitAck(void);
void IIC_SendByte(u8 data);
u8 IIC_ReadByte(void);


#endif