#ifndef SG_H
#define SG_H
#include "gd32f1x0.h" 
#include "Driver.h"
#define SampleN 240 //Set sample rate as 240, then the sample frequency is F0*SampleX
#define High_Priority_Led_Period 500 //1000/2Hz =500ms
#define High_Priority_Led_Duty   200 //40% duty    
#define Medium_Priority_Led_Period 2000 //1000/0.5Hz =2000ms
#define Medium_Priority_Led_Duty   800 //40% duty 

extern uint16_t DMA_BUFF1[SampleN];
extern uint16_t DMA_BUFF2[SampleN];

void SG_Init(uint8_t Who);
void Calculate_Ref_Signal(void);//Calculate modulation signal 
void Update_DMA_BUFF(void);     //Modulate to generate audio signal output
void Decode_UART_CMD(void);     //Decode and execute command from UART 
void LED_CTL(void);             //Warning LEDs control


#endif



