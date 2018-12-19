#include "SG.h"
#include "Driver.h"
#define EPS 0.000001

int16_t RAW_DATA[SampleN] ={//Rae data
1201,1331,1450,1554,1642,1713,1766,1799,1811,1802,1772,1721,1648,1555,1443,1312,1164,1001,824,636, 
439,236,28,-181,-390,-594,-792,-982,-1160,-1324,-1473,-1604,-1716,-1807,-1876,-1922,-1945,-1944,-1919,-1871, 
-1801,-1708,-1595,-1463,-1314,-1149,-970,-780,-582,-376,-167,44,254,460,661,854,1038,1210,1368,1512 ,
1640,1751,1845,1921,1979,2019,2042,2048,2038,2013,1975,1925,1864,1794,1716,1634,1547,1459,1371,1284 ,
1201,1121,1048,982,923,873,832,800,778,766,762,768,781,801,827,858,892,929,967,1004 ,
1040,1072,1099,1120,1134,1140,1136,1122,1098,1063,1016,958,888,808,717,616,507,389,265,134 ,
0,-137,-276,-415,-552,-686,-816,-940,-1056,-1165,-1265,-1354,-1433,-1500,-1556,-1599,-1630,-1650,-1658,-1654 ,
-1640,-1616,-1583,-1541,-1493,-1438,-1378,-1315,-1249,-1182,-1114,-1047,-981,-919,-859,-803,-752,-706,-666,-630 ,
-600,-576,-556,-542,-531,-525,-521,-520,-521,-523,-526,-528,-529,-529,-526,-520,-511,-499,-483,-463, 
-439,-412,-382,-348,-312,-274,-235,-195,-156,-118,-81,-48,-19,6,26,40,47,46,39,23, 
0,-31,-70,-116,-168,-227,-291,-359,-430,-503,-577,-650,-720,-787,-849,-905,-953,-991,-1019,-1036 ,
-1040,-1031,-1008,-970,-919,-853,-772,-678,-572,-453,-323,-184,-36,117,275,435,596,755,911,1060, 
};

uint16_t DMA_BUFF1[SampleN] ={
3249,3379,3498,3602,3690,3761,3814,3847,3859,3850,3820,3769,3696,3603,3491,3360,3212,3049,2872,2684, 
2487,2284,2076,1867,1658,1454,1256,1066,888,724,575,444,332,241,172,126,103,104,129,177, 
247,340,453,585,734,899,1078,1268,1466,1672,1881,2092,2302,2508,2709,2902,3086,3258,3416,3560, 
3688,3799,3893,3969,4027,4067,4090,4094,4086,4061,4023,3973,3912,3842,3764,3682,3595,3507,3419,3332, 
3249,3169,3096,3030,2971,2921,2880,2848,2826,2814,2810,2816,2829,2849,2875,2906,2940,2977,3015,3052, 
3088,3120,3147,3168,3182,3188,3184,3170,3146,3111,3064,3006,2936,2856,2765,2664,2555,2437,2313,2182, 
2048,1911,1772,1633,1496,1362,1232,1108,992,883,783,694,615,548,492,449,418,398,390,394, 
408,432,465,507,555,610,670,733,799,866,934,1001,1067,1129,1189,1245,1296,1342,1382,1418, 
1448,1472,1492,1506,1517,1523,1527,1528,1527,1525,1522,1520,1519,1519,1522,1528,1537,1549,1565,1585, 
1609,1636,1666,1700,1736,1774,1813,1853,1892,1930,1967,2000,2029,2054,2074,2088,2095,2094,2087,2071, 
2048,2017,1978,1932,1880,1821,1757,1689,1618,1545,1471,1398,1328,1261,1199,1143,1095,1057,1029,1012, 
1008,1017,1040,1078,1129,1195,1276,1370,1476,1595,1725,1864,2012,2165,2323,2483,2644,2803,2959,3108, 
};

uint16_t DMA_BUFF2[SampleN] ={
3249,3379,3498,3602,3690,3761,3814,3847,3859,3850,3820,3769,3696,3603,3491,3360,3212,3049,2872,2684, 
2487,2284,2076,1867,1658,1454,1256,1066,888,724,575,444,332,241,172,126,103,104,129,177, 
247,340,453,585,734,899,1078,1268,1466,1672,1881,2092,2302,2508,2709,2902,3086,3258,3416,3560, 
3688,3799,3893,3969,4027,4067,4090,4094,4086,4061,4023,3973,3912,3842,3764,3682,3595,3507,3419,3332, 
3249,3169,3096,3030,2971,2921,2880,2848,2826,2814,2810,2816,2829,2849,2875,2906,2940,2977,3015,3052, 
3088,3120,3147,3168,3182,3188,3184,3170,3146,3111,3064,3006,2936,2856,2765,2664,2555,2437,2313,2182, 
2048,1911,1772,1633,1496,1362,1232,1108,992,883,783,694,615,548,492,449,418,398,390,394, 
408,432,465,507,555,610,670,733,799,866,934,1001,1067,1129,1189,1245,1296,1342,1382,1418, 
1448,1472,1492,1506,1517,1523,1527,1528,1527,1525,1522,1520,1519,1519,1522,1528,1537,1549,1565,1585, 
1609,1636,1666,1700,1736,1774,1813,1853,1892,1930,1967,2000,2029,2054,2074,2088,2095,2094,2087,2071, 
2048,2017,1978,1932,1880,1821,1757,1689,1618,1545,1471,1398,1328,1261,1199,1143,1095,1057,1029,1012, 
1008,1017,1040,1078,1129,1195,1276,1370,1476,1595,1725,1864,2012,2165,2323,2483,2644,2803,2959,3108, };

typedef struct MY_SG
{
	//Signal character, whitch compliy with YY0709 standard(Electric divce part)
	//Note:when configure SG parameter, the condition which (Td1+x)<=(Td2+y) must be satisfied
	float Rate;              //Set the decrease coefficient
	//Time equency character, whitch compliy with YY0709 standard(Electric divce part)
	uint8_t Td1; //Signal continue time for high priority(75ms<=Td1<=200ms)
	uint8_t Td2; //Signal continue time for low priority(125ms<=Td1<=250ms)
	uint8_t Tr;  //Signal riseing time,range from (10%~20%)*Td,where Td=(Td1+Td2)/2
	uint8_t X;   //X time(50ms<=X<=125ms)
	uint8_t Y;   //Y time(125ms<=Y<=250ms)
	uint32_t Ts; /*Time between two pulse group*/
	//float Rate_Tf =0.5;//Ecoeffient to calculate Tf time(0<Rate_Tf<1)
	uint8_t Tf;     /*Signal falling time,this value must <=Td-Tr*/
	uint8_t Tb1;    //Time between two pulse group for high prirority(2.5s<=Tb1<=15s),Unit(0.1s)    
  uint8_t Tb2;    //Time between two pulse group for medium prirority(2.5s<=Tb2<=30s),Unit(0.1s)        
	uint8_t Tb3;    //Time between two pulse group for low prirority(Tb3>15s or not repeat(0s)),Unit(0.1s)    
	uint8_t M;      //Number of pulse for low priority,other(10 for high priority and 3for medium priority)
	uint8_t Ts_Tab_H[9];//Time between two pulse group for high priority
  uint16_t Ts_H; //Value of Ts_Tab_H4(350ms<=TS_H<1300ms)
}SG_t;


SG_t SG =
{
	608,            //Rate
	140,            //Td1
	190,            //Td2
	25,             //Tr
	88,             //X
	188,            //Y
	0,              //Ts
	25,             //Tf
	25,             //Tb1
  50,             //Tb2
	0,              //Tb3
	2,              //M
	{1,1,2,1,3,1,1,2,1},//Ts_Tab_H[9]
  825,            //Ts_H
};


typedef struct LED_PWM
{
	uint8_t Enable;
	uint32_t Period;
	uint32_t Compare;
	uint32_t Counter;
}LED_PWM_t;

LED_PWM_t High_Led ={0,0,0,0};
LED_PWM_t Medium_Led ={0,0,0,0};
LED_PWM_t Low_Led ={0,0,0,0};

//Varibles to generate audio signal
uint8_t Priority =0;//0-No warning 1-Low priority 2-Medium priority 3-High priority
uint8_t Priority1 =0;//Shadow of Priority
uint8_t Next_Priority =0;//Priority of next signal, which will interupt current signal if the priority higher than current.
uint32_t SYS_K =0;//Count for sequence
float A_ref =0;//Amplitude of reference signal to generate audio signal(0<=A_ref<=1)
int8_t SG_Index =0;
uint8_t SG_Index1 =0;
uint32_t SG_Time =0;
float dA =0;
uint8_t Cal_Flag =0;
uint8_t Voice_Level =3; //1->low 2->medium 3->high
uint8_t Voice_Level1 =3;//1->low 2->medium 3->high
uint16_t Td =500;//Td time for voice of key down(ms)
uint16_t SW_Delay =10;//The time dalay for Switch between tow status(ms)

void SG_Init(uint8_t Who)
{
	uint16_t i;
	if(Who==0)
	{
		SG.Tr *=1.25;
		SG.Tf *=1.25;
		SG.Td1 -=(uint8_t)(0.1*(SG.Tr+SG.Tf));
		SG.Td2 -=(uint8_t)(0.1*(SG.Tr+SG.Tf));
		for(i=0;i<SampleN;i++) 
		{
			DMA_BUFF1[i] =2048;
		}
	  dT =1000.0/Base_Frequency;
		High_Led.Period =(uint32_t)(High_Priority_Led_Period/dT);
		High_Led.Compare =(uint32_t)(High_Priority_Led_Duty/dT);
		Medium_Led.Period =(uint32_t)(Medium_Priority_Led_Period/dT);
		Medium_Led.Compare =(uint32_t)(Medium_Priority_Led_Duty/dT);
	}
	else if(Who==1)
	{
		for(i=0;i<SampleN;i++) 
		{
			DMA_BUFF1[i] =2048;
		}
	}
	else
	{
		for(i=0;i<SampleN;i++) 
		{
			DMA_BUFF2[i] =2048;
		}
	}
}

void Calculate_Ref_Signal(void)
{
	if(Cal_Flag==1)
	{
		Cal_Flag =2;
		SG_Index1 =0;
		SG_Time =0;
		SYS_K =0;
		if(Priority==1)//Flag for high priority audio signal
		{
			if(SG_Index<9)//0 1 2...9
			{
				if(SG.Ts_Tab_H[SG_Index]==1) SG.Ts =SG.X;
				else if(SG.Ts_Tab_H[SG_Index]==2) SG.Ts =2*SG.X+SG.Td1;
				else if(SG.Ts_Tab_H[SG_Index]==3) SG.Ts =SG.Ts_H;
				SG.Ts -=0.8*(SG.Tr+SG.Tf);
			}
			else 
			{
				if((Next_Priority!=0)&&(Next_Priority!=6))
				{
					SG.Ts =SW_Delay; 
				}
				else 
				{
					SG.Ts =SG.Tb1*100;
					SG.Ts -=0.8*(SG.Tr+SG.Tf);
				}
				SG_Index =-1;
			}
		}
		else if(Priority==2)//Flag for medium priority audio signal
		{
			if(SG_Index<2)//0 1
			{
				SG.Ts =SG.Y;
				SG.Ts -=0.8*(SG.Tr+SG.Tf);
			}
			else 
			{
				if((Next_Priority!=0)&&(Next_Priority!=6))
				{
					SG.Ts =SW_Delay; 
				}
				else 
				{
					SG.Ts =SG.Tb2*100;
					SG.Ts -=0.8*(SG.Tr+SG.Tf);
				}
				SG_Index =-1;
			}
		}
		else if(Priority==3)//Flag for Low priority audio signal or voice for key down
		{
			SG.Ts =0xffffffff;
			SG_Index =-1;
		}
		else if(Priority==5)//Flag for voice of key down
		{
			SG.Ts =10;
			SG_Index =-1;
		}
	}
  if(Cal_Flag==2)
	{
		SYS_K ++;
		if(SG_Time==0)//Start to genrate riseing edge
		{
			dA =dT/(SG.Tr+1);
			SG_Time =(uint32_t)(1/(dA+EPS));
			A_ref =-dA;
			SG_Index1 =1;
		}
		if(SG_Index==-1)//1-High 2=Medium 3-Low 4-Stop 5-Key voice 6-Adjust voice
		{
			if((Priority==3)&&((Next_Priority!=0))&&(SG_Index1==4)) SYS_K =SG_Time;
		}
		if(SYS_K<=SG_Time) 
		{
			if(SYS_K==SG_Time)//A event happen
			{
				if(SG_Index1==1)//Start to genrate continue segment
				{
					dA =0;
					A_ref =1;
					if(Priority==5)
					{
						SG_Time +=(uint32_t)(Td/(dT+EPS));
						Priority =3;
						Next_Priority =4;
					}
					else SG_Time +=(uint32_t)(SG.Td1/(dT+EPS));
					SG_Index1 =2;
				}
				else if(SG_Index1==2)//Start to genrate falling edge
				{
					//SG.Tf =SG.Rate*(Td1+Td2)/2;
					dA =dT/(SG.Tf+1);
					SG_Time +=(uint32_t)(1/(dA+EPS));
					dA =-dA;
					SG_Index1 =3;
				}
				else if(SG_Index1==3)//Stop output signal
				{
					A_ref =0;
					dA =0;
					SG_Time +=(uint32_t)(SG.Ts/(dT+EPS));
					SG_Index1 =4;
				}
				else if(SG_Index1==4)
				{
					if(SG_Index==-1)//one cycle signals output finished
					{
						if(Next_Priority==6)//Adjust voice level
						{
							Next_Priority =0;
							Voice_Level =Voice_Level1;
						}
						if(Next_Priority==4)//Stop output 
						{
							Priority =0;
							Next_Priority =0;
							if(Buf_Busy==1) SG_Init(2);
							else SG_Init(1);
							Cal_Flag =0;
							SG_Index =0;
							SW_Buf =4;					
						}
						else if((Next_Priority==1)||(Next_Priority==2))//Switch warning level
						{
							Priority =Next_Priority;
							Next_Priority =0;
							Cal_Flag =1;
							SG_Index ++;
						}
						else if(Priority==3)
						{
							Priority =0;
							Cal_Flag =0;
							if(Buf_Busy==1) SG_Init(2);
							else SG_Init(1);
							SW_Buf =4;					
						}
						else
						{
							Cal_Flag =1;
							SG_Index ++;
						}
					}
					else
					{
						Cal_Flag =1;
						SG_Index ++;
					}
				}
			}
			A_ref +=dA;//Generate modulation signal
		}
	}
}

void Update_DMA_BUFF(void)
{
	uint16_t i;
	float Gain =0;
	if(Cal_Flag==0) return;
	Calculate_Ref_Signal();//Calculate modulation signal
	if(Voice_Level==1) Gain =0.333333;
	else if(Voice_Level==2) Gain =0.666666;
	else Gain =0.999999;
	//A_ref =1;
	if(Buf_Busy==1)//Update DMA buffer2 if buffer1 is busy
	{
		for(i=0;i<SampleN;i++) 
		{
			DMA_BUFF2[i] =(uint16_t)((float)RAW_DATA[i]*A_ref*Gain+2048);
		}
	}
	else
	{
		for(i=0;i<SampleN;i++) 
		{
			DMA_BUFF1[i] =(uint16_t)((float)RAW_DATA[i]*A_ref*Gain+2048);
		}
	}
	SW_Buf =2;//Trigger dma switch transmit buffer
}

void Decode_UART_CMD(void)
{
	uint8_t CRC;
	switch(UART_RX_BUF[2])//Decode command package
	{
		case 0://Trigger high priority warning:0xaa 02 00 cc
		{
			//ACK:0xaa 03 00 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x00;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority==0) //Trigger now
			{
				Priority =1;
				Cal_Flag =1;
				SW_Buf =1;
			}
			else if((Priority==2)||(Priority==3))//Trigger later
			{
				Next_Priority =1;
			}
			break;
		}
		case 1://Trigger medium priority warning:0xaa 02 01 cc
		{
			//ACK:0xaa 03 00 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x01;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority==0)//Trigger now
			{
				Priority =2;
				Cal_Flag =1;
				SW_Buf =1;
			}
			else if(Priority==1)//Faild to execute:The priority is too low
			{
				UART_TX_BUF[3] =0x01;
			}
			else if(Priority==3)//Trigger later
			{
				Next_Priority =2;
			}
			break;
		}
		case 2://Trigger low priority warning:0xaa 02 02 cc
		{
			//ACK:0xaa 03 02 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x02;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority==0)//Trigger now
			{
				Priority =3;
				Cal_Flag =1;
				SW_Buf =1;
			}
			else if((Priority==1)||(Priority==2))//Faild to execute:The priority is too low
			{
				UART_TX_BUF[3] =0x01;
			}
			break;
		}
		case 3://Stop warning:0xaa 02 03 cc
		{
			//ACK:0xaa 03 02 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x03;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority!=0) Next_Priority =4;//Stop warning
			break;
		}
		case 4://Stop warning:0xaa 02 04 cc
		{
			//ACK:0xaa 03 02 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x04;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority!=0) Next_Priority =4;//Stop warning
			break;
		}
		case 5://Change voice level:0xaa 03 05 03 cc
		{
			//ACK:0xaa 03 02 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x05;
			if((UART_RX_BUF[3]==1)||(UART_RX_BUF[3]==2)||(UART_RX_BUF[3]==3))
			{
				if(Priority==0) Voice_Level =UART_RX_BUF[3];
				else 
				{
					Voice_Level1 =UART_RX_BUF[3];
					Next_Priority =6;
				}
				UART_TX_BUF[3] =0x00;
			}
			else UART_TX_BUF[3] =0x01;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			break;
		}
		case 6://Generate voice for key down:0xaa 02 06 cc
		{
			//ACK:0xaa 03 00 00 cc
			UART_TX_BUF[1] =0x03;
			UART_TX_BUF[2] =0x06;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =0xcc;
			UART_TX_Len =5;
			if(Priority==0) //Trigger now
			{
				Priority =5;
				Cal_Flag =1;
				SW_Buf =1;
			}
			else //Trigger failed
			{
				UART_TX_BUF[3] =0x01;
			}
			break;
		}
		case 100://Generate voice for key down:0xaa 02 64 cc
		{
			//ACK:0xaa 03 00 00 cc
			UART_TX_BUF[1] =0x04;
			UART_TX_BUF[2] =0x64;
			UART_TX_BUF[3] =0x00;
			if((Priority==1)||(Priority==2)||(Priority==3)) 
			{
				UART_TX_BUF[4] =Priority-1;
			}
			else UART_TX_BUF[4] =3;
			UART_TX_BUF[5] =0xcc;
			UART_TX_Len =6;
			break;
		}
		case 105://Generate voice for key down:0xaa 02 64 cc
		{
			//ACK:0xaa 03 00 00 cc
			UART_TX_BUF[1] =0x04;
			UART_TX_BUF[2] =0x69;
			UART_TX_BUF[3] =0x00;
			UART_TX_BUF[4] =Voice_Level;
			UART_TX_BUF[5] =0xcc;
      UART_TX_Len =6;
			break;
		}
		default: break;
	}
	if(UART_TX_Len==5)//aa 03 03 00 
	{
		CRC =UART_TX_BUF[1]^UART_TX_BUF[2]^UART_TX_BUF[3];
		UART_TX_BUF[4] =CRC;
		UART_Send();
	}	
	else if(UART_TX_Len==6)
	{
		CRC =UART_TX_BUF[1]^UART_TX_BUF[2]^UART_TX_BUF[3]^UART_TX_BUF[4];
		UART_TX_BUF[5] =CRC;
		UART_Send();
	}
}

void LED_CTL(void)
{
	if(Priority!=Priority1)
	{
		if(Priority==1)//High priority warning
		{
			if(Priority1==2)
			{
				Medium_Led.Enable =0;
				Medium_Led.Counter =0;
				LED_SW(Blue_LED,OFF);
			}
			else if(Priority1==3)
			{
				LED_SW(Yellow_LED,OFF);
			}
			High_Led.Enable =1;
			High_Led.Counter =0;
			LED_SW(Red_LED,ON);
		}
		if(Priority==2)//Medium priority warning
		{
			if(Priority1==1)
			{
				High_Led.Enable =0;
				High_Led.Counter =0;
				LED_SW(Red_LED,OFF);
			}
			else if(Priority1==3)
			{
				LED_SW(Yellow_LED,OFF);
			}
			Medium_Led.Enable =1;
			Medium_Led.Counter =0;
			LED_SW(Blue_LED,ON);
		}
		if(Priority==3)//Medium priority warning
		{
			if(Priority1==1)
			{
				High_Led.Enable =0;
				High_Led.Counter =0;
				LED_SW(Red_LED,OFF);
			}
			if(Priority1==2)
			{
				Medium_Led.Enable =0;
				Medium_Led.Counter =0;
				LED_SW(Blue_LED,OFF);
			}
			LED_SW(Yellow_LED,ON);
		}
		else if(Priority==0)//Stop warning
		{
			if(Priority1==1)
			{
				High_Led.Enable =0;
				High_Led.Counter =0;
				LED_SW(Red_LED,OFF);
			}
			else if(Priority1==2)
			{
				Medium_Led.Enable =0;
				Medium_Led.Counter =0;
				LED_SW(Blue_LED,OFF);
			}
			else if(Priority1==3) LED_SW(Yellow_LED,OFF);
		}
		Priority1 =Priority;
	}
	if(High_Led.Enable==1)
	{
		High_Led.Counter ++;
		if(High_Led.Counter==High_Led.Compare) LED_SW(Red_LED,OFF); 
		else if(High_Led.Counter==High_Led.Period)
		{
			High_Led.Counter =0;
			LED_SW(Red_LED,ON); 
		}
	}
	if(Medium_Led.Enable==1)
	{
		Medium_Led.Counter ++;
		if(Medium_Led.Counter==Medium_Led.Compare) LED_SW(Blue_LED,OFF); 
		else if(Medium_Led.Counter==Medium_Led.Period)
		{
			Medium_Led.Counter =0;
			LED_SW(Blue_LED,ON); 
		}
	}
}

