#ifndef __modbus_H
#define __modbus_H
#include "stdio.h"
#include "stm32f4xx.h"                  // Device header

//modbus用的串口号
#define MODUBS_UART UART4

extern uint8_t biaozhiwei[20];
//
extern uint16_t	Modbus_IO[];
extern uint16_t	Modbus_RX_CNT;//接收计数器
extern uint8_t	Modbus_RX_BUFF[200];//接收缓冲区2048字节
extern uint8_t	Modbus_TX_BUFF[200];//接收缓冲区2048字节
extern uint8_t	Modbus_FrameFlag;//帧结束标记
extern uint16_t	Modbus_RX_EN;//接收倒计时
extern uint16_t 	is_fasong_06;//是否发送06
extern uint16_t 	jicunqi_06;
extern int 	neirong_06;

extern int data;
extern int addr;
//extern int startaddr;

extern uint16_t 	jicunqi_16;
extern uint16_t 	changdu_16;
extern uint16_t 	shuju;

extern uint16_t* bufLen;
extern uint16_t regNums;
extern uint16_t regAddr;
extern uint16_t is_fasong_16;//是否发送16
void Modbus_Service(void);
void Modbus_Service_SEND(void);
void Modbus_01_Solve(void);
void Modbus_03_Solve(void);
void Modbus_06_Solve(void);
void Modbus_16_Solve(void);
void Modbus_SendData(uint8_t *buff,uint8_t len);
void shunxuzhixing(void);

//用于串口接收中断，进行组包
void Modbus_zubao(uint8_t Res);

//用于定时器，判断是否接收完成
void Modbus_Is_jieshou(void);

void Modbus_Is_fasong(void);
#endif
