#include "stm32f4xx.h"
#include "./485/bsp_485.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "modbus.h"
#include "./key/bsp_key.h"
#include "./adc/bsp_adc.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define ARRAY_SIZE 100

extern __IO uint16_t ADC_ConvertedValue;
float ADC_Vol; 

void initDevice(uint8_t deviceIndex, uint8_t address)
{
    devices[deviceIndex].address = address;
    // 初始化其他必要的设备参数
}

void configureDevice(uint8_t deviceIndex)
{
    // 配置设备参数
    biaozhiwei[0] = 1;
    Modbus_Service_SEND(deviceIndex);
    biaozhiwei[0] = 0;
    delay_ms(500);
    biaozhiwei[3] = 1;
    Modbus_Service_SEND(deviceIndex);
    biaozhiwei[3] = 0;
}

void moveDevice(uint8_t deviceIndex, int direction, int duration)
{
    // 移动设备
    biaozhiwei[direction] = 1;
    Modbus_Service_SEND(deviceIndex);
    biaozhiwei[direction] = 0;
    delay_ms(duration);
    biaozhiwei[0] = 1;
    Modbus_Service_SEND(deviceIndex);
    biaozhiwei[0] = 0;
}

int main(void)
{
    delay_init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    _485_Config();
    Debug_USART_Config();
    Rheostat_Init();
    LED_GPIO_Config();
    TIM3_Int_Init(7200-1,0);

    // 初始化两个设备
    initDevice(0, DEVICE_1_ADDRESS);
    initDevice(1, DEVICE_2_ADDRESS);

    // 配置两个设备
    configureDevice(0);
    configureDevice(1);

    int T = 3000;  // 运行时间ms

    while(1)
    {
        if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
        {   
            moveDevice(0, 1, 20000);  // 设备1向下移动
            moveDevice(1, 2, 20000);  // 设备2向上移动
        }

        if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON)
        {
            moveDevice(0, 2, 10000);  // 设备1向上移动
            moveDevice(1, 1, 10000);  // 设备2向下移动
        }

        if(Key_Scan(KEY3_GPIO_PORT,KEY3_PIN) == KEY_ON)
        {   
            moveDevice(0, 1, 4000);  // 设备1正转
            moveDevice(1, 1, 4000);  // 设备2正转
        }

        if(Key_Scan(KEY4_GPIO_PORT,KEY4_PIN) == KEY_ON)
        {   
            moveDevice(0, 2, 0);  // 设备1反转启动
            moveDevice(1, 2, 0);  // 设备2反转启动
        }

        if(Key_Scan(KEY5_GPIO_PORT,KEY5_PIN) == KEY_ON)
        {   
            while(1)
            {
                moveDevice(0, 2, 3000);  // 设备1向上
                delay_ms(8000);
                moveDevice(0, 1, 3000);  // 设备1向下
                delay_ms(5000);

                moveDevice(1, 1, 3000);  // 设备2向下
                delay_ms(8000);
                moveDevice(1, 2, 3000);  // 设备2向上
                delay_ms(5000);
            }
        }

        printf("Device 1 data: %d, Device 2 data: %d\r\n", devices[0].data, devices[1].data);
    }
}
