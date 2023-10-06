#ifndef  __ID1016C_H
#define  __ID1016C_H
#include "stm32f4xx.h"
#include "usart6.h"

/*定义通讯包识别码*/
#define CMDPACKET_CODE			0xAA55	//命令包识别码
#define RESPPACKET_CODE			0x55AA	//响应包识别码
#define CMDDATAPACKET_CODE		0xA55A	//指令数据包识别码
#define RESPDATAPACKET_CODE		0x5AA5	//相应数据包识别码

void ID1016C_Init(void);								/*初始化*/
void ID1016C_EXTI_Init(void);							/*指纹模块触发外部中断初始化*/
u16 ID1016C_GetVerification(u8 *cmd, u8 len);			/*计算校验和*/
void ID1016C_SendData(u8 *cmd, u16 len);				/*发送数据到模块*/
u8 ID1016C_Check();										/*指纹识别*/
u8 ID1016C_Register(u16 id_num);						/*指纹录入*/

#endif