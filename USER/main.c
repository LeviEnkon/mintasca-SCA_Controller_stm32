/**
  ******************************************************************************
  * @��	�� �� main.c
  * @��	�� �� INNFOS Software Team
  * @��	�� �� V1.5.1
  * @��	�� �� 2019.9.10
  * @ժ	Ҫ �� ���������
  ******************************************************************************/
  
/* Includes ----------------------------------------------------------------------*/
#include "bsp.h"
#include "SCA_API.h"
#include "SCA_APP.h"

/* Variable defines --------------------------------------------------------------*/
uint8_t cmd = 0;					//�ⲿ��������

/* Forward Declaration -----------------------------------------------------------*/
static void Log(void);
static void CMD_Handler(uint8_t cmd);

/**
  * @��	��	���������
  * @��	��	��
  * @��	��	��
  */
int main(void)
{ 
	/* �ײ�������ʼ�� */
	BSP_Init();			

	/* �ȴ�ִ�����ȶ� */
	delay_ms(500);	
	
	/* ����1��ӡLOG��Ϣ */
	Log();
	
	/* �ȴ������ */
	while(1)
	{	
		if(cmd)
		{
			CMD_Handler(cmd);
			cmd = 0;
		}
		else
			delay_ms(10);
	}       
}

/**
  * @��	��	���ڴ�ӡ��ʾ��Ϣ
  * @��	��	��
  * @��	��	��
  */
static void Log()
{
	printf("\r\n��ӭʹ�� INNFOS SCA �������ԣ�\r\n");
	printf("��ϸͨ��Э��μ� INNFOS WIKI ��\r\n");
	printf("���� 1 ��ѯ�����ϵ�ִ����ID ��\r\n");
	printf("���� 2 ʹ��Ĭ��ID��ʼ��SCA������ ��\r\n");
	printf("���� 3 ����λ�ù�����Գ��� ��\r\n");
	printf("���� 4 ��������ת���Գ��� ��\r\n");
	printf("���� 5 ����ߵ��ٲ��Գ��� ��\r\n");
	printf("���� 6 ��ִ�����ػ� ��\r\n");
	printf("���� 7 ��ʾ������Ϣ ��\r\n");
}

/**
  * @��	��	�����������
  * @��	��	cmd�����յ���ָ��
  * @��	��	��
  */
static void CMD_Handler(uint8_t cmd)
{
	switch(cmd)
	{
		case 1:
			printf("\r\nִ����ѯ����\r\n");
		
			/* ������ѯ���� */
			SCA_Lookup();
		
			printf("��ѯ������\r\n");
		break;
		
		case 2:
			printf("\r\nSCA��ʼ����\r\n");
		
			/* ���ó�ʼ������ */
			SCA_Init();
		
			/* �ȴ�ִ�����ȶ� */
			delay_ms(500);
		
			printf("SCA��ʼ��������\r\n");
			break;
		
		case 3:
			printf("\r\n����λ�ù�����ԣ�\r\n");
		
			/* ���ò��Գ��� λ�ù��� */
			SCA_Homing();
		
			printf("λ�ù�����Խ�����\r\n");
			break;
			
		case 4:
			printf("\r\n��������ת�л����ԣ�\r\n");
		
			/* ���ò��Գ��� ����ת�л� */
			SCA_Exp1();
		
			printf("����ת�л����Խ�����\r\n");
			break;
		
		case 5:
			printf("\r\n����ߵ����л����ԣ�\r\n");
			
			/* ���ò��Գ��� �ߵ����л� */
			SCA_Exp2();
		
			printf("�ߵ����л����Խ�����\r\n");
			break;
		
		case 6:
			printf("\r\nִ�����ػ���\r\n");
			
			/* �ر�����ִ���� */
			disableAllActuators();
		
			printf("ִ�����ػ�������\r\n");
			break;
		
		default:
			Log();
			break;
	}
	
}








