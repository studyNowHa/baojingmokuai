#ifndef DRIVER_H
#define DRIVER_H
#include "gd32f1x0.h" 
#include <stdio.h>
#define Base_Frequency 700 //,Hz
#define UART_RX_BUF_MAX_LEN 50

#define Red_LED 0
#define Blue_LED 1
#define Yellow_LED 2
#define ON 1
#define OFF 0

extern float dT;
extern uint8_t UART_RX_Len;//Byte numbers of uart has received
extern uint8_t UART_RX_BUF[UART_RX_BUF_MAX_LEN];
extern uint8_t UART_Receive_Cmd_Stastu;//UART_Receive_Cmd_Stastu=2 indicate a command has been received.

extern uint8_t Buf_Busy;
extern uint8_t SW_Buf;
extern uint8_t UART_TX_Len;
extern uint8_t UART_TX_BUF[UART_RX_BUF_MAX_LEN];

/*System led pin initialize:
Red_Led-->PA15
Blue_Led-->PB4
Yellow_Led-->PB3
*/
void LED_Init(void);
//Led control function,Where nLED=<Red_LED/Blue_LED/Yellow_LED> CMD=<ON/OFF>
void LED_SW(uint8_t nLED,uint8_t CMD);
//Initialize UART:Where COM_ID indicate COM number, BODE indicate comunication speed
void UART1_Init(uint32_t BODE);
void Timer5_Init(void);
void DMA_Init(void);
void DAC0_Init(void);
void USART1_IRQHandler(void);
void DMA_Channel1_2_IRQHandler(void);
void UART_Send(void);

#endif


