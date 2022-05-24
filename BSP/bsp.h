/**
  ******************************************************************************
  * @��	�� �� bsp.h
  * @��	�� �� INNFOS Software Team
  * @��	�� �� V1.0.0
  * @��	�� �� 2019.6.14
  * @ժ	Ҫ �� �ײ�������ʼ��
  ******************************************************************************/
#ifndef __BSP_H
#define __BSP_H

/* Includes ----------------------------------------------------------------------*/
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "bsp_can.h"

/* Port defines-------------------------------------------------------------------*/
#define LED1 PDout(2)	
#define LED2 PDout(3)	 

#define LED1_ON()		GPIO_ResetBits(GPIOD, GPIO_Pin_2)
#define LED1_OFF()		GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define LED1_TOGGLE()	(GPIOD->ODR ^= GPIO_Pin_2)

#define LED2_ON()		GPIO_ResetBits(GPIOD, GPIO_Pin_3)
#define LED2_OFF()		GPIO_SetBits(GPIOD, GPIO_Pin_3)
#define LED2_TOGGLE()	(GPIOD->ODR ^= GPIO_Pin_3)



void BSP_Init(void);

#endif
