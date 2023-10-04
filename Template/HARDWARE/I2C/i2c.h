#ifndef __I2C_H
#define __I2C_H
#include "sys.h" 

//IO操作函数	 
#define IIC_SCL(X)  GPIO_WriteBit(SCL_PORT,SCL_PIN,(BitAction)X) 	//SCL
#define IIC_SDA(X)  GPIO_WriteBit(SDA_PORT,SDA_PIN,(BitAction)X) 	//SDA	 
#define READ_SDA()  GPIO_ReadInputDataBit(SDA_PORT,SDA_PIN)	    //输入SDA 


#define  SCL_CLK	RCC_AHB1Periph_GPIOB
#define  SCL_PORT	GPIOB
#define  SCL_PIN	GPIO_Pin_1
#define  SDA_CLK	RCC_AHB1Periph_GPIOF
#define  SDA_PORT	GPIOF
#define  SDA_PIN	GPIO_Pin_10

//IIC所有操作函数
void IIC_Init(void);                		//初始化IIC的IO口	
void SDA_OUT(void);						    //输出
void SDA_IN(void);  						//输入
void IIC_Start(void);					    //发送IIC开始信号
void IIC_Stop(void);	  					//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);						    //IIC发送ACK信号
void IIC_NAck(void);						//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif

