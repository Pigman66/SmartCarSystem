#include "i2c.h"
#include "delay.h"

/*********************************************************
功  能：初始化IIC
参  数: 无
返回值: 无
**********************************************************/
void IIC_Init(void)
{			
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(SCL_CLK | SDA_CLK, ENABLE);	//使能GPIOD时钟

	//GPIOD12,D13初始化设置
	GPIO_InitStructure.GPIO_Pin = SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(SCL_PORT, &GPIO_InitStructure);				//初始化
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;
	GPIO_Init(SDA_PORT, &GPIO_InitStructure);
	IIC_SCL(1);
	IIC_SDA(1);
}

/**************************************************************
*功  能：配置输出端口
*参  数: 无
*返回值: 无 
**************************************************************/
void SDA_OUT(void)
{ 
 	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;				//PD13端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
 	GPIO_Init(SDA_PORT, &GPIO_InitStructure);				 	//初始化IO口
}

/**************************************************************
*功  能：配置输入端口
*参  数: 无
*返回值: 无 
**************************************************************/
void SDA_IN(void)  
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SDA_PIN;				//PD13端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 	GPIO_Init(SDA_PORT, &GPIO_InitStructure);				 	//初始化IO口

}

/*********************************************************
功  能：产生IIC起始信号
参  数: 无
返回值: 无
**********************************************************/
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	Delay_us(4);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}

/*********************************************************
功  能：产生IIC停止信号
参  数: 无
返回值: 无
**********************************************************/
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL(0);
	IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL(1); 
	IIC_SDA(1);//发送I2C总线结束信号
	Delay_us(4);							   	
}

/*********************************************************
功  能：等待应答信号到来
参  数: 无
返回值: 1，接收应答失败
        0，接收应答成功
**********************************************************/
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	
	SDA_IN();      //SDA设置为输入 	
	IIC_SDA(1);Delay_us(1);	   
	IIC_SCL(1);Delay_us(1);
	 
	while(READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);//时钟输出0 	   
	return 0;  
} 

/*********************************************************
功  能：产生ACK应答
参  数: 无
返回值: 无
**********************************************************/
void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	Delay_us(2);
	IIC_SCL(1);
	Delay_us(2);
	IIC_SCL(0);
}

/*********************************************************
功  能：不产生ACK应答
参  数: 无
返回值: 无
**********************************************************/
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	Delay_us(2);
	IIC_SCL(1);
	Delay_us(2);
	IIC_SCL(0);
}

/*********************************************************
功  能：IIC发送一个字节
参  数: txd 数据
返回值: 无
**********************************************************/
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		Delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL(1);
		Delay_us(2); 
		IIC_SCL(0);	
		Delay_us(2);
    }	 
} 	

/*********************************************************
功  能：读1个字节
参  数: ack=1时，ack=0时
返回值: 发送ACK，发送nACK 
**********************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL(0); 
        Delay_us(2);
		IIC_SCL(1);
        receive<<=1;
        if(READ_SDA())receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

