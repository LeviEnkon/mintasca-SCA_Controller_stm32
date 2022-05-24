/**
  ******************************************************************************
  * @��	�� �� bsp.c
  * @��	�� �� INNFOS Software Team
  * @��	�� �� V1.0.0
  * @��	�� �� 2019.6.14
  * @ժ	Ҫ �� �ײ�������ʼ��
  ******************************************************************************/
  
/* Includes ----------------------------------------------------------------------*/
#include "bsp.h" 
 
/* Funcation defines -------------------------------------------------------------*/

/**
  * @��	��	����LED��ʼ��
  * @��	��	��
  * @��	��	��
  */
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_2 | GPIO_Pin_3);
}

/**
  * @��	��	�ײ�������ʼ������
  * @��	��	��
  * @��	��	��
  */
void BSP_Init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	delay_init(180);  		 
	uart_init(115200);		
	CAN1_Initializes();
	CAN2_Initializes();	
}
