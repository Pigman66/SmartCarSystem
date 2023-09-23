#ifndef  __BH1750FVI_H
#define  __BH1750FVI_H
#include "stm32f4xx.h"
#include "i2c.h"

// BH1750指令
#define POWER_OFF				0x00
#define POWER_ON				0x01
#define MODULE_RESET			0x07
#define	CHMODE_CMD				0x10
#define CHMODE2_CMD				0x11
#define CLMODE2_CMD				0x13
#define OHMODE_CMD				0x20
#define OHMODE2_CMD				0x21
#define OLMODE_CMD				0x23

/*测量模式*/
typedef enum {
	CONTINUE_H_Mode = 0,
	CONTINUE_H_Mode2,
	CONTINUE_L_Mode,
	ONETIME_H_Mode,
	ONETIME_H_Mode2,
	ONETIME_L_Mode
}BH1750Mode_t;

#define  I2C_WRITE_ADDR		0x46	//写操作地址
#define  I2C_READ_ADDR		0x47	//读操作地址

u8 BH1750_Init(BH1750Mode_t mode);
void BH1750_ReadByte();
void BH1750_WriteByte(u8 data);
float BH1750_GetLight();

#endif