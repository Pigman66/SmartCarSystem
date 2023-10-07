#include "c1016.h"

uint8_t aRxBuffer[100];       //返回数据存储
static char str_identify[50]; //指纹状态数组
uint8_t ed24=0;           //校验位
uint8_t ed25=0;           //校验位
uint8_t c1016_identify_state = 1;    //指纹识别标志位
uint8_t c1016_identify_id = 0;       //获取返回数据中指纹ID
uint8_t c1016_identify_key = 0;      //指纹录入标志
uint8_t c1016_identify_id_select = 0;//指定识别指纹ID
uint16_t setidnnumber = 1;           //录入ID
uint8_t c1016_Weakup_flag = 0;       //指纹检测标志
uint8_t c1016_rx_flag = 0;           //串口接收完成标志

char str1[20]={0};

/*******************************************指纹模块指令集****************************************************/

//从采集器采集指纹图像并暂存于 ImageBuffer 中
uint8_t CMD_GET_IMAGE[] =       {0x55,0xAA,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x01};
//检测指纹输入状态（有/无手指）
uint8_t CMD_FINGER_DETECT[] =   {0x55,0xAA,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	                             0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x01};
//打开背光
uint8_t CMD_Open_Backlight[] =  {0x55,0xaa,0x00,0x00,0x24,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x01};
//关闭背光
uint8_t CMD_Close_Backlight[] = {0x55,0xAA,0x00,0x00,0x24,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x01};
//打开红色背光
uint8_t CMD_RED_LED[] =         {0x55,0xAA,0x00,0x00,0x24,0x00,0x04,0x00,0x01,0x02,0x00,0x00,0x00,
	                             0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2A,0x01};
//打开绿色背光
uint8_t CMD_GREEN_LED[] =       {0x55,0xAA,0x00,0x00,0x24,0x00,0x04,0x00,0x01,0x01,0x04,0x09,0x00,
	                             0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x01};
//将暂存于指定 Ram Buffer 中的指纹模板保存于指定编号的模块指纹库中
uint8_t CMD_STORE_CHAR[] =      {0x55,0xAA,0x00,0x00,0x40,0x00,0x04,0x00,0x01,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x01};
//删除指纹库中的指定编号范围内的所有指纹模板
uint8_t CMD_DEL_CHAR[] =        {0x55,0xAA,0x00,0x00,0x44,0x00,0x04,0x00,0x01,0x00,0x32,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x02};
//获取指定编号的模板注册状态
uint8_t CMD_GET_STATUS[] =      {0x55,0xAA,0x00,0x00,0x46,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x01};								 
//从 ImageBuffer 中的指纹图像产生指纹模板 Template 并保存于指定 RamBuffer0 中
uint8_t CMD_GENERATE[] =        {0x55,0xAA,0x00,0x00,0x60,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x61,0x01};
//从 ImageBuffer 中生成模板数据保存在 RamBuffer1 中
uint8_t CMD_62[] =              {0x55,0xAA,0x00,0x00,0x60,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,
	                             0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x62,0x01};
//从 ImageBuffer 中生成模板数据保存在 RamBuffer2 中
uint8_t CMD_63[] =              {0x55,0xAA,0x00,0x00,0x60,0x00,0x02,0x00,0x02,0x00,0x00,0x00,0x00,
	                             0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x01};
// 将暂存于 Ram Buffer 中的两或三个模板数据融合成一个模板数据
//注： 融合后的模板数据暂存在 RamBuffer 0
uint8_t CMD_MERGE[] =           {0x55,0xAA,0x00,0x00,0x61,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x01};						 
//指定编号范围内的 1： N 识别
uint8_t CMD_SEARCH[] =          {0x55,0xAA,0x00,0x00,0x63,0x00,0x06,0x00,0x00,0x00,0x01,0x00,0x50,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x02};
//指定 Ram Buffer 中的指纹模板与指纹库中指定编号的指纹模板之间进行 1:1 比对（验证）
uint8_t CMD_VERIFY[] =          {0x55,0xAA,0x00,0x00,0x64,0x00,0x04,0x00,0x01,0x00,0x00,0x00,0x00,
                                 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x01};

/**********************************************************************************************************/								 


/**********************************************************
功  能：计算校验位
参  数: *da  指令   len 指令长度
返回值: 无
***********************************************************/
void C1016_Data_Verification(uint8_t *da,uint8_t len)
{
    uint32_t lenl, lenh, lensum;
    if(len >= 26)
    {
        lenl = da[0] + da[1] + da[2] + da[3] +da[4] +da[5] +da[6] +da[7] + da[8] + da[9] + da[10];
        lenh = da[11] + da[12] + da[13] + da[14] +da[15] +da[16] +da[17] +da[18] + da[19] + da[20] + da[21] + da[22] + da[23];
        lensum = (lenl + lenh) % 65536;
        da[24] = lensum % 256;
        da[25] = lensum / 256;
        ed24 = lensum % 256;
        ed25 = lensum / 256;
    }
}

/**********************************************************
功  能：计算校验和
参  数: *da  指令   len 指令长度
返回值: 无
***********************************************************/
uint16_t C1016_Get_Verification(uint8_t *da,uint8_t len)
{
    uint32_t lenl, lenh, lensum = 0;
    if(len >= 26)
    {
        lenl = da[0] + da[1] + da[2] + da[3] +da[4] +da[5] +da[6] +da[7] + da[8] + da[9] + da[10];
        lenh = da[11] + da[12] + da[13] + da[14] +da[15] +da[16] +da[17] +da[18] + da[19] + da[20] + da[21] + da[22] + da[23];
        lensum = (lenl + lenh) % 65536;
    }
    return lensum;
}

/**********************************************************
功  能：清空指纹  范围：1~32
参  数: 无
返回值: 无
***********************************************************/
void C1016_cmd_Delete(void)
{
	C1016_Data_Verification(CMD_DEL_CHAR,sizeof(CMD_DEL_CHAR));
    C1016_Send_Data(CMD_DEL_CHAR,sizeof(CMD_DEL_CHAR));
}

/**********************************************************
功  能：将暂存在 ImageBuffer 中的指纹图像生成模板数据， 
         并保存于指定编号的 Ram Buffer 中
参  数: 无
返回值: 无
***********************************************************/
void C1016_cmd_Generate(uint16_t RamBufferx)
{
    CMD_GENERATE[8] = RamBufferx & 0xFF;
    CMD_GENERATE[9] = (RamBufferx >> 8) & 0xFF;
    C1016_Data_Verification(CMD_GENERATE,sizeof(CMD_GENERATE));
    C1016_Send_Data(CMD_GENERATE,sizeof(CMD_GENERATE));
}

/**********************************************************
功  能：指令发送
参  数: *da  指令   len: 指令长度
返回值: 无
***********************************************************/
void C1016_Send_Data(uint8_t *da, uint8_t len)
{
    USART6_SendLength(da, len);
}

/**********************************************************
功  能：数据返回判断函数
参  数: *rad  返回数据   len: 数据长度
返回值: 无
***********************************************************/
uint16_t C1016_Check_id_Registration(uint8_t *rad, uint8_t len)
{
    uint16_t SRC_CMD;
    uint16_t Verif;
    uint16_t refl;

    refl = 0;
    if(c1016_rx_flag == 1)
    {
        if(len >= 26)												//判断数据长度
        {
            SRC_CMD = (rad[5] << 8) + rad[4]; 						//得到指令
            Verif = (rad[25] << 8) + rad[24];						//得到校验

            if((rad[0] == 0xAA) && (rad[1] == 0x55))  				//判断帧头
            {
                if(C1016_Get_Verification(rad,len) == Verif)		//判断校验
                {
                    if(SRC_CMD == 0x0046)							//判断指令
                    {
                        if(rad[10] == 0x01)							//ID已经注册
                        {
                            refl = 0;
                        }
                        else
                         {									//ID可以注册
                            refl = 1;
                            C1016_Send_Data(CMD_Open_Backlight,sizeof(CMD_Open_Backlight));//打开背光
                        }
                    }
                    else if(SRC_CMD == 0x0020)
                    {
                         refl = 1;
                    }
                    else if(SRC_CMD == 0x0060)
                    {
                        refl = 1;
                    }
                    else if(SRC_CMD == 0x0040)
                    {
                        refl = 1;
                    }
                    else if(SRC_CMD == 0x0061)
                    {
                        refl = 1;
                    }
					 else if(SRC_CMD == 0x0063)
                    {
                        c1016_identify_id = ((rad[11] << 8) + rad[10]);
                         refl = ((rad[11] << 8) + rad[10]);
                    }
                    else if(SRC_CMD == 0x0064)
                    {
                         c1016_identify_id = ((rad[11] << 8) + rad[10]);
                         refl = ((rad[11] << 8) + rad[10]);
                    }
                    else
                    {
                        refl = 0;
                    }
                }
                else
                {
                    refl = 0;
                }
            }
            else
            {
                refl = 0;
            }
        }
        c1016_rx_flag = 0;
    }
    return refl;
}


/**********************************************************
功  能：指纹模块触发外部中断初始化
参  数: 无
返回值: 无
***********************************************************/
void C1016_Weakup_EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_TypeDefStructure;
    EXTI_InitTypeDef EXTI_TypeDefStructure;
    NVIC_InitTypeDef NVIC_TypeDefStructure;

    //开启中断输入端口时钟
    RCC_AHB1PeriphClockCmd(TOUCHOUT_CLK,ENABLE);
    //开启外部中断时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

    //KEY0 for EXTI in Pin
    GPIO_TypeDefStructure.GPIO_Pin = TOUCHOUT_PIN;
    GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;		//通用输入模式
    GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_DOWN;   //下拉
    GPIO_Init(TOUCHOUT_PORT,&GPIO_TypeDefStructure);

    //中断线关联
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG,EXTI_PinSource0);

    EXTI_TypeDefStructure.EXTI_Line = TOUCHOUT_EXTILINE;				//中断线选择
    EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断触发
    EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//下降沿触发
    EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;				//中断线使能
    EXTI_Init(&EXTI_TypeDefStructure);							//初始化配置

    //EXTI1_IRQn中断向量优先级设置
    NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI0_IRQn;		    //选择中断通道
    NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0;//设置先占优先级
    NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 1;		//设置从优先级
    NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;			//设置中断通道开启
    NVIC_Init(&NVIC_TypeDefStructure);							//初始化配置中断优先级

}

/**********************************************************
功  能：外部中断向量1服务函数
参  数: 无
返回值: 无
***********************************************************/
void EXTI0_IRQHandler()
{
    if(EXTI_GetITStatus(TOUCHOUT_EXTILINE) == SET)
    {
        if(c1016_Weakup_flag == 0)
        {
            c1016_Weakup_flag = 1;
        }
        EXTI_ClearITPendingBit(TOUCHOUT_EXTILINE);
    }
}

/**********************************************************
功  能：指纹模块初始化
参  数: 无
返回值: 无
***********************************************************/
void C1016_Init()
{
    USART6_Init(115200);	//串口初始化
    C1016_Weakup_EXTI_Init();
	C1016_Send_Data(CMD_GREEN_LED,sizeof(CMD_GREEN_LED));

}


/**********************************************************
功  能：指纹模块录入
        注册流程
		1、判断注册ID是否存在（CMD_GET_STATUSS）
		2、采集指纹图像（CMD_GET_IMAGE）
		3、转化成特征模板（CMD_GENERATE）
		4、融合指纹模板（CMD_MERGE）
		5、保存指纹模板（CMD_STORE_CHAR）
参  数: id_number  录入ID
返回值: 无
***********************************************************/
void C1016_Enroll(uint16_t id_number)
{
    uint32_t c1016_enroll_time = 0;
    uint32_t c1016_enroll_time_out = 0;
    c1016_enroll_time_out =  gt_get() + 5000;
    c1016_identify_state = 0;  //指纹识别标志
	
	USART_SendString(USART1, "Start enroll\r\n");
	sprintf(str1, "Enroll ID:%d \r\n", setidnnumber);  //显示录入ID
	USART_SendString(USART1, str1);		
             						
	c1016_identify_key = 1;  //指纹录入标志
	
    while(1)
    {
		
        if(c1016_Weakup_flag == 1 && c1016_identify_key == 1)
        {
			USART_SendString(USART1, "Enrolling\r\n");
            CMD_GET_STATUS[8] = id_number & 0xFF;								//判断id_number 是否已经注册
            CMD_GET_STATUS[9] = (id_number >> 8) & 0xFF;
            C1016_Data_Verification(CMD_GET_STATUS,sizeof(CMD_GET_STATUS));
            C1016_Send_Data(CMD_GET_STATUS,sizeof(CMD_GET_STATUS));
            c1016_enroll_time =  gt_get() + 1000;
            
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))//& (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {                  
					break;
                }
            }
           
            C1016_Data_Verification(CMD_GET_IMAGE,sizeof(CMD_GET_IMAGE));		//采集指纹图像
            C1016_Send_Data(CMD_GET_IMAGE,sizeof(CMD_GET_IMAGE));
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )//& (Sub_time(c1016_enroll_time))
            {

                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
			
            C1016_cmd_Generate(0);												//保存到缓存区0
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))//& (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }

            C1016_cmd_Generate(1);												//保存到缓存区1
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))//& (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }

            C1016_cmd_Generate(2);												//保存到缓存区2
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
  
            C1016_Data_Verification(CMD_GENERATE,sizeof(CMD_GENERATE));	 //将暂存在 Ram Buffer 中的模板合并生成模板数据并后保存于指定的 Ram Buffer 中
            C1016_Send_Data(CMD_GENERATE,sizeof(CMD_GENERATE));          //生成指纹模块
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
					
                }
            }
                      
            C1016_Data_Verification(CMD_FINGER_DETECT,sizeof(CMD_FINGER_DETECT));   //检测指纹输入状态（有/无手指）
            C1016_Send_Data(CMD_FINGER_DETECT,sizeof(CMD_FINGER_DETECT));           //检测手指
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
			
            C1016_Data_Verification(CMD_62,sizeof(CMD_62));  //将暂存在 Ram Buffer 中的模板合并生成模板数据并后保存于指定的 Ram Buffer 中
            C1016_Send_Data(CMD_62,sizeof(CMD_62));          //生成指纹模块
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
			
            C1016_Data_Verification(CMD_FINGER_DETECT,sizeof(CMD_FINGER_DETECT));	//检测指纹输入状态
            C1016_Send_Data(CMD_FINGER_DETECT,sizeof(CMD_FINGER_DETECT));      
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
			
             C1016_Data_Verification(CMD_63,sizeof(CMD_63));	//将暂存在 Ram Buffer 中的模板合并生成模板数据并后保存于指定的 Ram Buffer 中
            C1016_Send_Data(CMD_63,sizeof(CMD_63));             //生成指纹模块
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
			
             C1016_Data_Verification(CMD_MERGE,sizeof(CMD_MERGE));  //将暂存于 Ram Buffer 中的两或三个模板数据融合成一个模板数据
            C1016_Send_Data(CMD_MERGE,sizeof(CMD_MERGE));
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )// & (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }
            }
            

            CMD_STORE_CHAR[8] = id_number & 0xFF;
            CMD_STORE_CHAR[9] = (id_number >> 8) & 0xFF;
            C1016_Data_Verification(CMD_STORE_CHAR,sizeof(CMD_STORE_CHAR));	  //保存指定编号 RamBuffer 中的模板数据到指定编号的指纹库中
            C1016_Send_Data(CMD_STORE_CHAR,sizeof(CMD_STORE_CHAR));			
            c1016_enroll_time =  gt_get() + 1000;
            while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))//& (Sub_time(c1016_enroll_time))
            {
                if(gt_get_sub(c1016_enroll_time)==0)
                {
                    break;
                }                
            }
			USART_SendString(USART1, "Enroll Success\r\n");
            sprintf(str_identify,"    ID:%d     \r\n",id_number);
			USART_SendString(USART1, str_identify);
  		
            C1016_Send_Data(CMD_Close_Backlight,sizeof(CMD_Close_Backlight));
            setidnnumber++;	   
            c1016_identify_state = 1;
            c1016_identify_key = 0;			
            c1016_Weakup_flag = 0;
			Delay_ms(500);
			Delay_ms(500);  
            break;
        }

        if(gt_get_sub(c1016_enroll_time_out)==0)
        {
			USART_SendString(USART1, "Enroll timeout\r\n");
            Delay_ms(500);
            Delay_ms(500);           
            c1016_Weakup_flag = 0;
			c1016_identify_key = 0;	
            c1016_identify_state = 1;				
            break;
        }

    }
}

/**********************************************************
功  能：指纹识别     
参  数: 无
返回值: 无
***********************************************************/
void C1016_Identify(void)
{
    uint32_t c1016_identify_time = 0;
    
    if(c1016_Weakup_flag == 1 && c1016_identify_state == 1)
    {
		USART_SendString(USART1, "Identify ID\r\n");			
		
        C1016_Data_Verification(CMD_GET_IMAGE,sizeof(CMD_GET_IMAGE));	//采集指纹图像
        C1016_Send_Data(CMD_GET_IMAGE,sizeof(CMD_GET_IMAGE));
        c1016_identify_time =  gt_get() + 1000;
		Delay_ms(50);
        while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)) )//& (Sub_time(c1016_enroll_time))
        {
            if(gt_get_sub(c1016_identify_time)==0)
            {
                C1016_Send_Data(CMD_RED_LED,sizeof(CMD_RED_LED));
                break;
            }
        }
        
        C1016_cmd_Generate(0);            //保存到缓存区0
        c1016_identify_time =  gt_get() + 1000;
         Delay_ms(200);
        while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))//& (Sub_time(c1016_enroll_time))
        {
            if(gt_get_sub(c1016_identify_time)==0)
            {
                break;
            }
        }

        C1016_Data_Verification(CMD_SEARCH,sizeof(CMD_SEARCH));    //搜索指定范围内的指纹     
        C1016_Send_Data(CMD_SEARCH,sizeof(CMD_SEARCH));		
        c1016_identify_time =  gt_get() + 2000;
         Delay_ms(200);
        while(!C1016_Check_id_Registration(aRxBuffer,sizeof(aRxBuffer)))
        {
            if(gt_get_sub(c1016_identify_time)==0)
            {
                break;
            }
        }	
        
        while(c1016_Weakup_flag)
        {
            if(c1016_identify_id != 0 ) //搜索到指纹ID
            {
				USART_SendString(USART1, "Identify ID Success\r\n");				
                BEEP_On();
                Delay_ms(100);
                BEEP_Off();
                sprintf(str_identify,"Identify ID:%d\r\n",c1016_identify_id);
				USART_SendString(USART1, str_identify);		
                C1016_Send_Data(CMD_GREEN_LED,sizeof(CMD_GREEN_LED));
                Delay_ms(500);
                Delay_ms(500);
                Delay_ms(500);				
                c1016_identify_id=0;				
                c1016_Weakup_flag = 0;
            } else
            {
				USART_SendString(USART1, "Identify ID timeout\r\n");
				C1016_Send_Data(CMD_RED_LED,sizeof(CMD_RED_LED));
				Delay_ms(500);
				Delay_ms(500);
				Delay_ms(500);
				c1016_identify_id=0;		
				c1016_Weakup_flag = 0;

            }

        }
    }       
}
