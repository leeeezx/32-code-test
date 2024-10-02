/*1****用户先透过 P3.006 参数规划 DI（参考8-110），决定控制来源为外部端子或通讯参数 P4.007，在这里选择通讯参数控制；
2******p2.010~p2.015为DI1~5软件口，需设置他们为常闭口（参考8-75），并设置他们对应的功能（参考表8.1），这里设置DI1和DI2为SP0和SP1对应符号，并设置为常闭；
3******P4.007用于控制DI1~DI5的打开和关闭（参考8-118或4.4.3）

需要调整的参数有：
1、更改为速度模式****************************P1.001=0102；
2、设置三个速度寄存器的值*******************P1.009=0， P1.010=500， P1.011=-500；
3、设置前5个DI的参数（从右往左数，前两个值表示选择的功能，第三个为0表示常闭，即对应参数值=1，反之则相反）*********
   ********************************************P2.010（DI1）=0001（0101为伺服启动）， P2.011（DI2）=0109（扭矩限制），P2.012（DI3）=0014（SPD0常闭）， P2.013（DI4）=0115（SPD1常开-指开路）， P2.014（DI5）=0102（异常重置）；
4、通过代码可设置对应DI使用P4.007通讯控制***P3.006=0x000C（设置DI3和DI4为P4.007通讯控制）；
5、通过代码向P4.007发送更改数据
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
	delay_init(168);	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	_485_Config();     //485配置
	Debug_USART_Config();  //串口配置
	Rheostat_Init();	   //内部变阻器初始化
	LED_GPIO_Config();
	TIM3_Int_Init(7200-1,0);  //初始化TIM3定时器的中断功能，并设置了相应的预分频和重载值
	
	biaozhiwei[0]=1;
	Modbus_Service_SEND();
	biaozhiwei[0]=0;
		delay_ms(500); //延时0.5s
	biaozhiwei[3]=1;
	Modbus_Service_SEND();
	biaozhiwei[3]=0;
	int T = 3000;  //运行时间ms
	
while(1){
/***************key1按下，向下移动一段时间后停止***************/
	if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON ){   
		/*正转启动*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	  delay_ms(20000); //延时
		/*停止*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	}
/***************key2按下，向上移动一段时间后停止***************/
	if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)== KEY_ON )
		{
		/*反转启动*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	  delay_ms(10000); //延时3s
		/*停止*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
						//LED_GREEN;点亮板载led
		}
/***********************key3按下，正转启动**********************/
	if( Key_Scan(KEY3_GPIO_PORT,KEY3_PIN) == KEY_ON ){   
		/*正转启动*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	delay_ms(4000); //延时3s
		/*停止*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	}
/***********************key4按下，反转启动**********************/
	if( Key_Scan(KEY4_GPIO_PORT,KEY4_PIN) == KEY_ON ){   
		/*反转启动*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	}
	
/***********************key5按下，反转启动**********************/
	if( Key_Scan(KEY5_GPIO_PORT,KEY5_PIN) == KEY_ON ){   
		while(1){
		/*反转启动*/
		biaozhiwei[2]=1;
		Modbus_Service_SEND();
		biaozhiwei[2]=0;
	delay_ms(3000); //延时3s0000000000000000向上
		/*停止*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	delay_ms(8000); //延时3s
		/*正转启动*/
		biaozhiwei[1]=1;
		Modbus_Service_SEND();
		biaozhiwei[1]=0;
	delay_ms(3000); //延时3s00000000000000000向下
		/*停止*/
		biaozhiwei[0]=1;
		Modbus_Service_SEND();
		biaozhiwei[0]=0;
	delay_ms(5000); //延时3s
		}
	}
	
		
		printf("%d \r\n",data);

		}
	}
