/*1****�û���͸�� P3.006 �����滮 DI���ο�8-110��������������ԴΪ�ⲿ���ӻ�ͨѶ���� P4.007��������ѡ��ͨѶ�������ƣ�
2******p2.010~p2.015ΪDI1~5����ڣ�����������Ϊ���տڣ��ο�8-75�������������Ƕ�Ӧ�Ĺ��ܣ��ο���8.1������������DI1��DI2ΪSP0��SP1��Ӧ���ţ�������Ϊ���գ�
3******P4.007���ڿ���DI1~DI5�Ĵ򿪺͹رգ��ο�8-118��4.4.3��

��Ҫ�����Ĳ����У�
1������Ϊ�ٶ�ģʽ****************************P1.001=0102��
2�����������ٶȼĴ�����ֵ*******************P1.009=0�� P1.010=500�� P1.011=-500��
3������ǰ5��DI�Ĳ�����������������ǰ����ֵ��ʾѡ��Ĺ��ܣ�������Ϊ0��ʾ���գ�����Ӧ����ֵ=1����֮���෴��*********
   ********************************************P2.010��DI1��=0001��0101Ϊ�ŷ��������� P2.011��DI2��=0109��Ť�����ƣ���P2.012��DI3��=0014��SPD0���գ��� P2.013��DI4��=0115��SPD1����-ָ��·���� P2.014��DI5��=0102���쳣���ã���
4��ͨ����������ö�ӦDIʹ��P4.007ͨѶ����***P3.006=0x000C������DI3��DI4ΪP4.007ͨѶ���ƣ���
5��ͨ��������P4.007���͸�������
*/


#include "stm32f4xx.h"
//#include "./usart/bsp_debug_usart.h"
#include "./485/bsp_485.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "sys.h"
#include "modbus.h"
#include "./key/bsp_key.h"
//#include "usart.h"
#include "./adc/bsp_adc.h"
#include "./usart/bsp_debug_usart.h"

extern __IO uint16_t ADC_ConvertedValue;
float ADC_Vol; 
#include "./led/bsp_led.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define ARRAY_SIZE 100


int main(void)
{
	delay_init(168);	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	_485_Config();     //485����
	Debug_USART_Config();  //��������
	Rheostat_Init();	   //�ڲ���������ʼ��
	LED_GPIO_Config();
	TIM3_Int_Init(7200-1,0);  //��ʼ��TIM3��ʱ�����жϹ��ܣ�����������Ӧ��Ԥ��Ƶ������ֵ
	
	biaozhiwei[0]=1;
	Modbus_Service_SEND();
	biaozhiwei[0]=0;
		delay_ms(500); //��ʱ0.5s
	biaozhiwei[3]=1;
	Modbus_Service_SEND();
	biaozhiwei[3]=0;
	int T = 3000;  //����ʱ��ms
	
while(1){
/***************key1���£������ƶ�һ��ʱ���ֹͣ***************/
	if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON ){   
		/*��ת����*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	  delay_ms(20000); //��ʱ
		/*ֹͣ*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	}
/***************key2���£������ƶ�һ��ʱ���ֹͣ***************/
	if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)== KEY_ON )
		{
		/*��ת����*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	  delay_ms(10000); //��ʱ3s
		/*ֹͣ*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
						//LED_GREEN;��������led
		}
/***********************key3���£���ת����**********************/
	if( Key_Scan(KEY3_GPIO_PORT,KEY3_PIN) == KEY_ON ){   
		/*��ת����*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	delay_ms(4000); //��ʱ3s
		/*ֹͣ*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	}
/***********************key4���£���ת����**********************/
	if( Key_Scan(KEY4_GPIO_PORT,KEY4_PIN) == KEY_ON ){   
		/*��ת����*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	}
	
/***********************key5���£���ת����**********************/
	if( Key_Scan(KEY5_GPIO_PORT,KEY5_PIN) == KEY_ON ){   
		while(1){
		/*��ת����*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	delay_ms(3000); //��ʱ3s0000000000000000����
		/*ֹͣ*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	delay_ms(8000); //��ʱ3s
		/*��ת����*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	delay_ms(3000); //��ʱ3s00000000000000000����
		/*ֹͣ*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	delay_ms(5000); //��ʱ3s
		}
	}
	
		
		printf("%d \r\n",data);

		}
	}
