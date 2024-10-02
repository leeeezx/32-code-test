#ifndef __modbus_H
#define __modbus_H
#include "stdio.h"
#include "stm32f4xx.h"                  // Device header

//modbus�õĴ��ں�
#define MODUBS_UART UART4

extern uint8_t biaozhiwei[20];
//
extern uint16_t	Modbus_IO[];
extern uint16_t	Modbus_RX_CNT;//���ռ�����
extern uint8_t	Modbus_RX_BUFF[200];//���ջ�����2048�ֽ�
extern uint8_t	Modbus_TX_BUFF[200];//���ջ�����2048�ֽ�
extern uint8_t	Modbus_FrameFlag;//֡�������
extern uint16_t	Modbus_RX_EN;//���յ���ʱ
extern uint16_t 	is_fasong_06;//�Ƿ���06
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
extern uint16_t is_fasong_16;//�Ƿ���16
void Modbus_Service(void);
void Modbus_Service_SEND(void);
void Modbus_01_Solve(void);
void Modbus_03_Solve(void);
void Modbus_06_Solve(void);
void Modbus_16_Solve(void);
void Modbus_SendData(uint8_t *buff,uint8_t len);
void shunxuzhixing(void);

//���ڴ��ڽ����жϣ��������
void Modbus_zubao(uint8_t Res);

//���ڶ�ʱ�����ж��Ƿ�������
void Modbus_Is_jieshou(void);

void Modbus_Is_fasong(void);
#endif
