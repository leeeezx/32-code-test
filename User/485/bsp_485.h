#ifndef __485_H
#define	__485_H

#include "stm32f4xx.h"
#include <stdio.h>
#include "sys.h" 

#define DEVICE_1_ADDRESS 0x01
#define DEVICE_2_ADDRESS 0x02

#define _485_USART                             UART4
#define _485_USART_CLK                         RCC_APB1Periph_UART4
#define _485_USART_BAUDRATE                    19200

#define _485_USART_RX_GPIO_PORT                GPIOC
#define _485_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define _485_USART_RX_PIN                      GPIO_Pin_11
#define _485_USART_RX_AF                       GPIO_AF_UART4
#define _485_USART_RX_SOURCE                   GPIO_PinSource11

#define _485_USART_TX_GPIO_PORT                GPIOC
#define _485_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define _485_USART_TX_PIN                      GPIO_Pin_10
#define _485_USART_TX_AF                       GPIO_AF_UART4
#define _485_USART_TX_SOURCE                   GPIO_PinSource10


#define _485_RE_GPIO_PORT					   GPIOH
#define _485_RE_GPIO_CLK	     		       RCC_AHB1Periph_GPIOH
#define _485_RE_PIN							   GPIO_Pin_9

#define _485_INT_IRQ                 		   UART4_IRQn
#define _485_IRQHandler                        UART4_IRQHandler



#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN__485_USART_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern uint8_t  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern uint16_t USART_RX_STA;         		//����״̬���	

void _485_Config(void);

void bsp_485_IRQHandler(void);




//void _485_SendByte(  uint8_t ch );
//void _485_SendStr_length( uint8_t *str,uint32_t strlen );
//void _485_SendString(  uint8_t *str);




//char *get_rebuff(uint16_t *len);
//void clean_rebuff(void);
#endif /* __485_H */
