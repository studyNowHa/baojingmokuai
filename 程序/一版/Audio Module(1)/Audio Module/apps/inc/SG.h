#ifndef SG_H
#define SG_H
#include "gd32f1x0.h" 
#include "Driver.h"
#define DT 2
#define SampleN 240 //Set sample rate as 240, then the sample frequency is F0*SampleX

extern uint16_t DMA_BUFF1[SampleN];
extern uint16_t DMA_BUFF2[SampleN];

void SG_Init(uint8_t Who);
void Calculate_Ref_Signal(void);//Calculate modulation signal 
void Update_DMA_BUFF(void);     //Modulate to generate audio signal output
void Decode_UART_CMD(void);     //Decode and execute command from UART 


#endif



