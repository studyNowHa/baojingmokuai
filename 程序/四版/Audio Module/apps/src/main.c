#include "gd32f1x0.h"               
#include "Driver.h" 
#include "SG.h"

int main (void) 
{
  rcu_osci_on(RCU_IRC40K);
  rcu_osci_stab_wait(RCU_IRC40K);
	SystemCoreClockUpdate(); 
	nvic_irq_enable(USART1_IRQn,0,0);
	nvic_irq_enable(DMA_Channel1_2_IRQn,0,1);
	UART1_Init(9600);
    printf("RCU_RSTSCK=%x\n",RCU_RSTSCK);

  LED_Init();
	SG_Init(0);
	Timer5_Init();
	DMA_Init();
	DAC0_Init();
	fwdgt_config(320,FWDGT_PSC_DIV64);//625Hz/32=20Hz(50ms)
  fwdgt_enable();
    
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
		fwdgt_counter_reload();
  }
}
