#include "Driver.h" 
#include "SG.h"
#define TIME_OUT 200000
#define DAC0_R12DH_ADDR     ((uint32_t)0x40007408)

uint8_t UART_Receive_Cmd_Stastu;
uint8_t UART_CMD_Len;
uint8_t UART_RX_Len =0;//Byte numbers of uart has received
uint8_t UART_RX_BUF[UART_RX_BUF_MAX_LEN];
uint8_t UART_TX_Len =0;//Byte numbers of uart has received
uint8_t UART_TX_BUF[UART_RX_BUF_MAX_LEN];
uint8_t UART_Receive_Cmd_Stastu =0;//UART_Receive_Cmd_Stastu=2 indicate a command has been received.


uint8_t Buf_Busy =1;//This varible indicate the work buffer
uint8_t SW_Buf =0;  //The flag of enable dma output buffer switch operate
float dT =0;

void LED_Init(void)
{
	RCU_AHBEN  |=  (1 << 18);   //Enable GPIOB clock
	RCU_AHBEN  |=  (1 << 17);   //Enable GPIOA clock
	//Config in as output mode 
	//PB3
	GPIO_CTL(GPIOB) &=~(3<<2*3); 
	GPIO_CTL(GPIOB) |=(1<<2*3);
	//PB4
	GPIO_CTL(GPIOB) &=~(3<<2*4); 
	GPIO_CTL(GPIOB) |=(1<<2*4);
	//PA15
	GPIO_CTL(GPIOA) &=~(3<<2*15); 
	GPIO_CTL(GPIOA) |=(1<<2*15);
	//Output mode config:PP mode	
  GPIO_OMODE(GPIOB) &=~(1<<3);//PB3 
	GPIO_OMODE(GPIOB) &=~(1<<4);//PB4
  GPIO_OMODE(GPIOA) &=~(1);   //PA0	
	//Pin speed config:2MHz
  GPIO_OSPD(GPIOB) &=~(3<<2*3);//PB3  
  GPIO_OSPD(GPIOB) &=~(3<<2*4);//PB4 	
	GPIO_OSPD(GPIOA) &=~(3);     //PA0
  //Confige pin output mode1:Pull up output	
  GPIO_PUD(GPIOB) &=~(3<<2*3);//PB3 
	GPIO_PUD(GPIOB) |=(1<<2*3);
	GPIO_PUD(GPIOB) &=~(3<<2*4);//PB4 
	GPIO_PUD(GPIOB) |=(1<<2*4);
	GPIO_PUD(GPIOA) &=~(3);//PA0 
	GPIO_PUD(GPIOA) |=(1);
	//Off all LED
  LED_SW(Red_LED,OFF);
	LED_SW(Blue_LED,OFF);
	LED_SW(Yellow_LED,OFF);
}


void LED_SW(uint8_t nLED,uint8_t CMD)
{
	if(nLED==0)//Red LED-->PA15
	{
		if(CMD==ON) GPIO_BOP(GPIOA) |= (1 << (16+15));
		else GPIO_BOP(GPIOA) |= (1<<15);
	}
	else if(nLED==1)//Blue LED-->PB4
	{
		if(CMD==ON) GPIO_BOP(GPIOB) |= (1 << (16+4));
		else GPIO_BOP(GPIOB) |= (1<<4);
	}
	else if(nLED==2)//Yellow LED-->PB3
	{
		if(CMD==ON) GPIO_BOP(GPIOB) |= (1 << (16+3));
		else GPIO_BOP(GPIOB) |= (1<<3);
	}
}

void UART1_Init(uint32_t BODE)
{
    /* Initialize GPIO clk */
	  rcu_periph_clock_enable(RCU_GPIOA);
	  /* Initialize UART clk */
    rcu_periph_clock_enable(RCU_USART1);
    /* connect port to USARTx_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);
    /* connect port to USARTx_Rx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);
    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_2);
    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ,GPIO_PIN_3);
	
    /* USART configure */
    usart_deinit(USART1);
    usart_baudrate_set(USART1,BODE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
		usart_interrupt_enable(USART1, USART_INT_RBNE);
    usart_enable(USART1);
		UART_TX_BUF[0] =0xaa;
}

int fputc(int ch, FILE *f)
{
		USART_TDATA(USART1) = (USART_TDATA_TDATA & ch);
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    return ch;
}

void Timer5_Init()
{
    float Tmp =0;
		timer_parameter_struct timer_initpara;
	  Tmp =18000000/(Base_Frequency*SampleN)-1;
    rcu_periph_clock_enable(RCU_TIMER5);
    timer_deinit(TIMER5);
    /* TIMER5 configuration */
    timer_initpara.prescaler         = 3;//18MHz PSCK
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (uint16_t)Tmp;//120KHz UPE
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 1;
    timer_init(TIMER5,&timer_initpara);
    /* auto-reload preload enable */
	  //timer_dma_enable(TIMER5, TIMER_DMA_UPD);
		timer_master_output_trigger_source_select(TIMER5,TIMER_TRI_OUT_SRC_UPDATE);
    timer_auto_reload_shadow_enable(TIMER5);
    /* TIMER5 counter enable */
    timer_enable(TIMER5);
}

void DMA_Init(void)
{
	dma_parameter_struct dma_init_struct;
	/* enable DMA clock */
	rcu_periph_clock_enable(RCU_DMA);
	/* initialize DMA channel2 */
	dma_deinit(DMA_CH2);
	 
	dma_init_struct.direction    = DMA_MEMORY_TO_PERIPHERAL;
	dma_init_struct.memory_addr  = (uint32_t)DMA_BUFF1;
	dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT;
	dma_init_struct.number       = SampleN;
	dma_init_struct.periph_addr  = DAC0_R12DH_ADDR;
	dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
	dma_init_struct.priority     = DMA_PRIORITY_ULTRA_HIGH;
	dma_init(DMA_CH2, dma_init_struct);

	/* configure DMA mode */
	dma_circulation_disable(DMA_CH2);
	dma_memory_to_memory_disable(DMA_CH2);
	dma_interrupt_enable(DMA_CH2,DMA_INT_FTF);
	/* enable DMA channel2 */
	dma_channel_enable(DMA_CH2);
}

void DAC0_Init(void)
{
		rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_DAC);
		gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_4);
		dac0_trigger_source_config(DAC_TRIGGER_T5_TRGO);
    dac0_output_buffer_disable();
		dac0_dma_enable();
    dac0_enable();
		DAC_CTL =0x00001007;
}


void USART1_IRQHandler(void)
{
	uint8_t	data;
	uint8_t CRC;
	if(RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE))
	{
		/* receive data */
		data = usart_data_receive(USART1);
		if(data==0xAA)//Header
		{
			UART_Receive_Cmd_Stastu =1;
			UART_RX_Len =0;
		}
		if(UART_Receive_Cmd_Stastu==1)
		{
			UART_RX_BUF[UART_RX_Len++] =data;
			if(UART_RX_Len>=UART_RX_BUF_MAX_LEN) UART_RX_Len =UART_RX_BUF_MAX_LEN-1; 
			if(UART_RX_Len==2) UART_CMD_Len =data;//The lengh of command package from uart
			if(UART_CMD_Len!=0)
			{
				if((UART_RX_Len-2)==UART_CMD_Len)//Command transmit finished
				{
					UART_CMD_Len =0;
					UART_RX_BUF[UART_RX_Len] ='\0';
					CRC =UART_RX_BUF[1];
					if(UART_RX_Len==4) CRC =UART_RX_BUF[1]^UART_RX_BUF[2];
					else if(UART_RX_Len==5) CRC =UART_RX_BUF[1]^UART_RX_BUF[2]^UART_RX_BUF[3];
					if(CRC==UART_RX_BUF[UART_RX_Len-1]) UART_Receive_Cmd_Stastu =2;
				}
			}
		}
	}
}

void UART_Send(void)
{
	uint8_t i;
	uint32_t Time_Out =0;
	for(i=0;i<UART_TX_Len;i++)
	{
		USART_TDATA(USART1) =UART_TX_BUF[i];
		Time_Out =0;
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE))
		{
			Time_Out ++;
			if(Time_Out>=TIME_OUT) break;
		}
	}
}


void DMA_Channel1_2_IRQHandler(void)
{
		if(RESET != dma_interrupt_flag_get(DMA_CH2, DMA_INT_FLAG_FTF))
		{
			if((SW_Buf==2)||(SW_Buf==4))//Dma buffer has been update, execute buffer switch operate
			{
				if(SW_Buf==2) SW_Buf =3;
				else SW_Buf =0;
				dma_channel_disable(DMA_CH2);
				if(Buf_Busy==1)//Switch to DMA_BUFF2 if current buffer is DMA_BUFF1
				{
					dma_memory_address_config(DMA_CH2,(uint32_t)DMA_BUFF2);
					dma_transfer_number_config(DMA_CH2,SampleN);
					Buf_Busy =2;
				}
				else
				{
					dma_memory_address_config(DMA_CH2,(uint32_t)DMA_BUFF1);
					dma_transfer_number_config(DMA_CH2,SampleN);
					Buf_Busy =1;
				}
				dma_channel_enable(DMA_CH2);
			}
			else
			{
				dma_channel_disable(DMA_CH2); 
				dma_transfer_number_config(DMA_CH2,SampleN);
				dma_channel_enable(DMA_CH2);
			}
			LED_CTL();//Update LEDs status
			dma_interrupt_flag_clear(DMA_CH2,DMA_INT_FLAG_FTF);
		}
}

