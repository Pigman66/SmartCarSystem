#ifndef  __BKRCSPEAK_H
#define  __BKRCSPEAK_H
#include "stm32f4xx.h"
#include "usart6.h"
#include "led.h"

#define  VIDEO_FANON_CMD	0x

u8 Video_Get(void);
void Voice_Control(void);

#endif