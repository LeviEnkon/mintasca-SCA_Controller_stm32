/**
  ******************************************************************************
  * @�ļ���	�� bsp_can.h
  * @����	�� INNFOS Software Team
  * @�汾	�� V1.0.0
  * @����	�� 2019.6.14
  * @ժҪ	�� CAN�ײ�Դ�ļ�
  ******************************************************************************/
#ifndef _BSP_CAN_H
#define _BSP_CAN_H

/* Includes ----------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Port defines-------------------------------------------------------------------*/
#define CAN1_CLK                   RCC_APB1Periph_CAN1
#define CAN1_GPIO_CLK              RCC_AHB1Periph_GPIOA
#define CAN1_RX_PIN                GPIO_Pin_11
#define CAN1_TX_PIN                GPIO_Pin_12
#define CAN1_GPIO_PORT             GPIOA                   
#define CAN1_RX_IRQn               CAN1_RX0_IRQn
#define CAN1_RX_Priority           0                       

#define CAN2_CLK                   RCC_APB1Periph_CAN2
#define CAN2_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define CAN2_RX_PIN                GPIO_Pin_5
#define CAN2_TX_PIN                GPIO_Pin_6
#define CAN2_GPIO_PORT             GPIOB                    
#define CAN2_RX_IRQn               CAN2_RX1_IRQn
#define CAN2_RX_Priority           0                      

#define CAN1_INT_EN		1		//�Ƿ�ʹ��CAN1�жϽ���
#define CAN2_INT_EN		1		//�Ƿ�ʹ��CAN2�жϽ���

/* �������� ------------------------------------------------------------------*/
void CAN1_Initializes(void);
uint8_t CAN1_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len);
uint8_t CAN1_Receive_Msg(CanRxMsg* RxMessage);

void CAN2_Initializes(void);
uint8_t CAN2_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len);
uint8_t CAN2_Receive_Msg(CanRxMsg* RxMessage);



#endif /* _BSP_CAN_H */


