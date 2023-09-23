#ifndef  __DRV8837_H
#define  __DRV8837_H
#include "stm32f4xx.h"

typedef enum
{
	DRV8837_Mode1 = 0,
	DRV8837_Mode2,
	DRV8837_Mode3,
	DRV8837_Mode4
}DRV8837_Mode_t;

void DRV8837_Mode(DRV8837_Mode_t mode);


#endif