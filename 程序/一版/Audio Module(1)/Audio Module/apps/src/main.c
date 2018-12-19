#include "gd32f1x0.h"               
#include "Driver.h" 
#include "SG.h"

int main (void) 
{
  SystemCoreClockUpdate(); 
	nvic_irq_enable(USART1_IRQn,0,0);
	nvic_irq_enable(DMA_Channel1_2_IRQn,0,1);
	UART1_Init(9600);
  LED_Init();
	//printf("System initialize OK,Fcpu =%ld Hz\n",SystemCoreClock);
	SG_Init(1);
	Timer5_Init();
	DMA_Init();
	DAC0_Init();
  while(1) 
	{                                   
		if(UART_Receive_Cmd_Stastu==2)
		{
			UART_Receive_Cmd_Stastu =0;
			Decode_UART_CMD();
		}
		if((SW_Buf==1)||(SW_Buf==3))//Execute update operate if DMA_BUFF have't been update
		{
			Update_DMA_BUFF();
		}
  }
}
