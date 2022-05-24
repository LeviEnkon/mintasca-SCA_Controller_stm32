/**
  ******************************************************************************
  * @�ļ���	�� bsp_can.c
  * @����	�� INNFOS Software Team
  * @�汾	�� V1.0.0
  * @����	�� 2019.6.14
  * @ժҪ	�� CAN�ײ�Դ�ļ�
  ******************************************************************************/

/* Includes ----------------------------------------------------------------------*/
#include "bsp_can.h"
#include "SCA_API.h"

/* Funcation defines -------------------------------------------------------------*/

/**
  * @��	��	CAN1�˿ڳ�ʼ��
  * @��	��	��
  * @��	��	��
  */
void CAN1_Initializes(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	CAN_InitTypeDef		CAN_InitStructure;
	CAN_FilterInitTypeDef	CAN_FilterInitStructure;
	
#if CAN1_INT_EN
	NVIC_InitTypeDef	NVIC_InitStructure;
#endif

	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);			

	/* �������� */
	GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);

	/* ���Ÿ���ӳ������ */
	GPIO_PinAFConfig(CAN1_GPIO_PORT,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	GPIO_PinAFConfig(CAN1_GPIO_PORT,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1

	/* ����CAN���� */
	CAN_InitStructure.CAN_TTCM = DISABLE;	/* ��ֹʱ�䴥��ģʽ��������ʱ���), T  */
	CAN_InitStructure.CAN_ABOM = DISABLE;	/* ��ֹ�Զ����߹رչ��� */
	CAN_InitStructure.CAN_AWUM = DISABLE;	/* ��ֹ�Զ�����ģʽ */
	CAN_InitStructure.CAN_NART = ENABLE;	/* ʹ���ٲö�ʧ��������Զ��ش����� */
	CAN_InitStructure.CAN_RFLM = DISABLE;	/* ��ֹ����FIFO����ģʽ */
	CAN_InitStructure.CAN_TXFP = DISABLE;	/* ��ֹ����FIFO���ȼ� */
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	/* ����CANģʽ */

	/* ����CAN������ = 1MBps(45MHz/9/(1+2+2)) */
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 9;
	CAN_Init(CAN1, &CAN_InitStructure);

	/* CAN�������� */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

#if CAN1_INT_EN
	/* NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CAN1_RX_Priority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* ʹ���ж� */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	//ʹ��FIFO0�Һ��ж�
#endif
}

/**
  * @��	��	CAN1�жϽ���
  * @��	��	��
  * @��	��	��
  */
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMsg;

	/* ��FIFO�н������ݰ� */
	CAN_Receive(CAN1, CAN_FIFO0, &RxMsg);
	
	/* ���ݰ�����Э�����н��� */
	canDispatch(&RxMsg);
}

/**
  * @��	��	CAN1���ݷ���
  * @��	��	ID��CAN����֡��ID
  *			msg��Ҫ���͵����ݵ�ַ
  *			len��Ҫ���͵����ݳ���
  * @��	��	0�����ͳɹ�
  *			����������ʧ��
  */
uint8_t CAN1_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len)
{	
	uint8_t mbox;
	uint16_t i=0;
	CanTxMsg TxMessage;
	
	TxMessage.StdId=ID;	 	// ��׼��ʶ��Ϊ0
	TxMessage.ExtId=ID;	 	// ������չ��ʾ����29λ��
	TxMessage.IDE=0;		// ʹ����չ��ʶ��
	TxMessage.RTR=0;		// ��Ϣ����Ϊ����֡��һ֡8λ
	TxMessage.DLC=len;		// ���ݳ���
	for(i=0;i<len;i++)		// װ�ط�������
		TxMessage.Data[i]=msg[i];	
		
	i=0xFFF;
	do
		mbox= CAN_Transmit(CAN1, &TxMessage);   		//�������ݣ�����ʹ�õ�����
	while((mbox == CAN_TxStatus_NoMailBox) && (i--));	//��������������ʱ�ط�
	
	if(mbox == CAN_TxStatus_NoMailBox)	return 2;		//����ʼ�����أ�����ʧ��
	
	i = 0;
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))	i++;//�ȴ����ͽ���
	if(i>=0XFFF)	return 1;	//���ͳ�ʱ����
	return 0;		
}

/**
  * @��	��	CAN1���ݲ�ѯ����
  * @��	��	RxMessage�����ݽ��ջ�������ַ
  * @��	��	�������ݵĳ��ȣ�������ʱ����0
  */
uint8_t CAN1_Receive_Msg(CanRxMsg* RxMessage)
{
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0,RxMessage);//��ȡ����	
	return RxMessage->DLC;	
}

/**
  * @��	��	CAN2�˿ڳ�ʼ��
  * @��	��	��
  * @��	��	��
  */
void CAN2_Initializes(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	CAN_InitTypeDef		CAN_InitStructure;
	CAN_FilterInitTypeDef	CAN_FilterInitStructure;

#if CAN2_INT_EN
	NVIC_InitTypeDef	NVIC_InitStructure;
#endif
	
	/* ʹ��ʱ�� */
	RCC_APB1PeriphClockCmd(CAN2_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(CAN2_GPIO_CLK, ENABLE);			  //ʹ��PORTAʱ��
	
	/* �������� */
	GPIO_InitStructure.GPIO_Pin = CAN2_RX_PIN | CAN2_TX_PIN;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(CAN2_GPIO_PORT, &GPIO_InitStructure);
	
	//���Ÿ���ӳ������
	GPIO_PinAFConfig(CAN2_GPIO_PORT,GPIO_PinSource5,GPIO_AF_CAN2); //GPIOB5����ΪCAN2
	GPIO_PinAFConfig(CAN2_GPIO_PORT,GPIO_PinSource6,GPIO_AF_CAN2); //GPIOB6����ΪCAN2

	/* ����CAN���� */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	
	/* ����CAN������ = 1MBps(45MHz/9/(1+2+2)) */
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 9;
	CAN_Init(CAN2, &CAN_InitStructure);
	
	/* CAN�������� */
	CAN_SlaveStartBank(14);	//ָ����������ʼ��ַ
	CAN_FilterInitStructure.CAN_FilterNumber = 14;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;	//ʹ��FIFO1
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
#if CAN2_INT_EN	
	/* NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CAN2_RX_Priority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* ʹ���ж� */
	CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);
#endif	
}
	
/**
  * @��	��	CAN2�жϽ���
  * @��	��	��
  * @��	��	��
  */
void CAN2_RX1_IRQHandler(void)
{
	CanRxMsg RxMsg;

	/* ��FIFO�н������ݰ� */
	CAN_Receive(CAN2, CAN_FIFO1, &RxMsg);
	
	/* ���ݰ�����Э�����н��� */
	canDispatch(&RxMsg);
}

/**
  * @��	��	CAN2���ݷ���
  * @��	��	ID��CAN����֡��ID
  *			msg��Ҫ���͵����ݵ�ַ
  *			len��Ҫ���͵����ݳ���
  * @��	��	0�����ͳɹ�
  *			����������ʧ��
  */
uint8_t CAN2_Send_Msg(uint8_t ID, uint8_t* msg, uint8_t len)
{	
	uint8_t mbox;
	uint16_t i=0;
	CanTxMsg TxMessage;
	
	TxMessage.StdId=ID;	 	// ��׼��ʶ��Ϊ0
	TxMessage.ExtId=ID;	 	// ������չ��ʾ����29λ��
	TxMessage.IDE=0;		// ʹ����չ��ʶ��
	TxMessage.RTR=0;		// ��Ϣ����Ϊ����֡��һ֡8λ
	TxMessage.DLC=len;		
	for(i=0;i<len;i++)
		TxMessage.Data[i]=msg[i];		
	
	i=0xFFF;
	do
		mbox= CAN_Transmit(CAN2, &TxMessage);   		//�������ݣ�����ʹ�õ�����
	while((mbox == CAN_TxStatus_NoMailBox) && (i--));	//��������������ʱ�ط�
	
	if(mbox == CAN_TxStatus_NoMailBox)	return 2;		//����ʼ�����أ�����ʧ��
	
	i=0;
	while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
	if(i>=0XFFF)return 1;
	return 0;		
}

/**
  * @��	��	CAN2���ݲ�ѯ����
  * @��	��	RxMessage�����ݽ��ջ�������ַ
  * @��	��	�������ݵĳ��ȣ�������ʱ����0
  */
uint8_t CAN2_Receive_Msg(CanRxMsg* RxMessage)
{		   		   
    if(CAN_MessagePending(CAN2,CAN_FIFO1)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN2, CAN_FIFO1,RxMessage);//��ȡ����	
	return RxMessage->DLC;	
}





