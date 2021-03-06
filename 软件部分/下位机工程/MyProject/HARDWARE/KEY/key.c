#include "key.h"
#include "delay.h"

/***********************************************
**函数名称：KEY驱动代码
**输入参数：无
**返回值：无
**其他说明：KEY0--PC5 KEY1--PB0  KEY2--PB1
**作者：WFY
************************************************/
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
//KEY0	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC5
//KEY1	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC5
//KEY2	 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOC5
	
} 


/***********************************************
**函数名称：按键处理函数
**输入参数：mode:0,不支持连续按;1,支持连续按;
**返回值：返回按键值
**其他说明： 0，没有任何按键按下
			KEY0_PRES，KEY0按下
			KEY1_PRES，KEY1按下
			WKUP_PRES，WK_UP按下 
			注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
**作者：WFY
************************************************/
u8 KEY_Scan(void)
{
	if((KEY0==0)||(KEY1==0)||(KEY2==0))
	{
		delay_ms(10);
		if(KEY0==0)
		{
			while(!KEY0);
			return KEY0_PRES;
		}
		else if(KEY1==0)
		{
			while(!KEY1);
			return KEY1_PRES;
		}
		else if(KEY2==0)
		{
			while(!KEY2);
			return KEY2_PRES;
		}
		else
		{
			return 0;
		}
	}
}
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==0)
//			return KEY0_PRES;
//		else if(KEY1==0)
//			return KEY1_PRES;
//		else if(KEY2==0)
//			return KEY2_PRES; 
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1)
//		key_up=1; 	     
//	return 0;// 无按键按下�
//}
