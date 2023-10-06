#include "bkrcspeak.h"


uint8_t status = 0;
uint8_t tips = 0;
uint16_t delay_i = 0;

/*初始化控制引脚*/
void Voice_Init(void)
{
	GPIO_InitTypeDef gpio;
	
	RCC_AHB1PeriphClockCmd(CTRL_CLK, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Pin = CTRL_PIN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(CTRL_PORT, &gpio);
	
	GPIO_SetBits(CTRL_PORT, CTRL_PIN); //默认输出高阻态
	
	//USART6_Init(115200); //初始化串口
}

/*语音识别，返回识别到的词条id*/
uint8_t Voice_Manage(void)
{

	
    if ((voice_falg == 0x01) && (usart6_buffer[0] == 0x55))			
    {
        if (usart6_buffer[1] == 0x02)
        {
            switch (usart6_buffer[2])
            {
            case 0x01:             //打开风扇
                status = 0x01;

                break;
            case 0x02:             //关闭风扇
                status = 0x02;
                break;

            case 0x03:            
                status = 0x03;
                break;

            case 0x04:             
                status = 0x04;
                break;
			
			 case 0x05:            
                status = 0x05;
                break;

            default  :
                break;
            }
        }

        voice_falg = 0x00;
    }
    return status;
}

/*语音识别控制模块*/
void Voice_Control(void)
{	
	switch (Voice_Manage())
            {
            case 0x01:            
				TIM_SetCompare1(TIM14, 500);
                break;
            case 0x02:            
                TIM_SetCompare1(TIM14, 0);
                break;
            case 0x03:             
                LED0(1);
                break;
            case 0x04:             
                LED1(1);
                break;
			 case 0x05:            
                LED2(1);
                break;
            default  :
                break;
            }
}
