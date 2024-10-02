
#include "./key/bsp_key.h" 

/// ����ȷ����ʱ
void Key_Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY3_GPIO_CLK|KEY4_GPIO_CLK|KEY5_GPIO_CLK,ENABLE);
	
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;  
  
  /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /*�������Ų�����Ҳ������*/
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);  
  
  
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN; 
  
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
  
  	GPIO_InitStructure.GPIO_Pin = KEY3_PIN; 
  
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);
	
	  	GPIO_InitStructure.GPIO_Pin = KEY4_PIN; 
  
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);
	  	GPIO_InitStructure.GPIO_Pin = KEY5_PIN; 
  
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY5_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief   ����Ƿ��а�������
  * @param   ����Ķ˿ںͶ˿�λ
  *		@arg GPIOx: x�����ǣ�A...G�� 
  *		@arg GPIO_PIN ������GPIO_PIN_x��x������1...16��
  * @retval  ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*�ȴ������ͷ� */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}
/*********************************************END OF FILE**********************/