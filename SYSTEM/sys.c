#include "sys.h"  
 
/* 
	ST�⺯��ʹ����C�������Ķ��Թ��ܣ����������USE_FULL_ASSERT����ô���е�ST�⺯������麯���β�
	�Ƿ���ȷ���������ȷ������ assert_failed() ���������������һ����ѭ���������û������롣
	
	�ؼ��� __LINE__ ��ʾԴ�����кš�
	�ؼ���__FILE__��ʾԴ�����ļ�����
	
	���Թ���ʹ�ܺ����Ӵ����С���Ƽ��û����ڵ���ʱʹ�ܣ�����ʽ�������ʱ��ֹ��

	�û�����ѡ���Ƿ�ʹ��ST�̼���Ķ��Թ��ܡ�ʹ�ܶ��Եķ��������֣�
	(1) ��C��������Ԥ�����ѡ���ж���USE_FULL_ASSERT��
	(2) �ڱ��ļ�ȡ��"#define USE_FULL_ASSERT    1"�е�ע�͡�	
*/

#ifdef USE_FULL_ASSERT

/**
  * @��	��	����
  * @��	��	file��Դ�����ļ����ơ��ؼ���__FILE__��ʾԴ�����ļ�����
  *			line�������кš��ؼ��� __LINE__ ��ʾԴ�����к�
  * @��	��	��
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/*�û���������Լ��Ĵ��뱨��Դ�����ļ����ʹ����кţ����罫�����ļ����кŴ�ӡ������*/
	printf("Wrong parameters value: file %s on line %d\r\n", file, line) 
	
	/* ����һ����ѭ��������ʧ��ʱ������ڴ˴��������Ա����û���� */
	while (1);
}

#endif

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















