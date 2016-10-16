#include "main.h"
#include "RS485.h"
#include "RS485Switch.h"
uint8_t fsm_sdtp_buf[400];
unsigned short buf_count;
uint8_t fc;
struct RS485Data RS485_Data[RS485_ChannelCount];

void RS485_Init_SingleMode(RS485Recive Handler,char channel)
{
	RS485_Data[channel].Handler=Handler;
}
void RS485_Init_PacketMode(RS485RecivePacket  PacketHandler,char channel)
{
	RS485_Data[channel].PacketHandler=PacketHandler;
}
void RS485_SendByte(uint16_t byte,char channel)
{
	while((UART2->FR&(1<<(5))) == (1<<((5))));
	PORTC->RXTX|=1<<10;
	PORTD->RXTX|=1<<15;
	UART2->DR=byte;
	while((UART2->FR&(1<<(3))) == (1<<((3))));
	while((UART2->FR&(1<<(7))) == 0);
	PORTC->RXTX&=~(1<<10);
	PORTD->RXTX&=~(1<<15);
}

void RS485_SendBytes(uint8_t* byte,unsigned short len,char channel)
{
unsigned int i=0;
RS485_SendByte(0xFD,channel);
for(i=0;i<len;i++)
{
	
	switch(byte[i])
	{
		case 0xFC:
		case 0xFD:
		case 0xFE:
		RS485_SendByte(0xFC,channel);
		break;
	}
	RS485_SendByte(byte[i],channel);
}
RS485_SendByte(0xFE,channel);
}
void  FSM_PacketProcess()
{
	uint8_t read;
	uint16_t time;
	if((UART2->FR&(1<<(4)))==(1<<(4))) return;
	read = (uint8_t)UART2->DR;
	if(fc)
	{
		fsm_sdtp_buf[buf_count] = read;
		buf_count++;
		fc=0;
		return;
	}
	switch(read)
	{
		case 0xFC:
		fc=1;
		break;
		case 0xFD:
		buf_count=0;
		break;
		case 0xFE:
		//FSM_SendSDTPPacket((uint8_t*)fsm_sdtp_buf,buf_count);
		RS485_Commutator_Handler(fsm_sdtp_buf,buf_count);
		buf_count=0;
		break;
		default:
		fsm_sdtp_buf[buf_count] = read;
		buf_count++;
		break;
	}
}
void RS485_Init()
{
	RST_CLK->PER_CLOCK |= 1<<24;
	RST_CLK->PER_CLOCK |= 1<<23;
	RST_CLK->PER_CLOCK |= 1<<7;
	RST_CLK->UART_CLOCK |= ((3 << 8) 
                        |(1 << 25));  
  
	 UART2->IBRD = 0x34; 
   UART2->FBRD = 0x5; 


	UART2->LCR_H = ((0 << 1) 
                      |(0 << 2)
                      |(0 << 3) 
                      |(3 << 5) 
                      |(0 << 7)); 

	
	PORTD->OE|=1<<15;
	PORTD->ANALOG|=(1<<15)|(1<<14)|(1<<13);
	PORTD->PWR|=(1<<30)|((3 << 28) | (3 << 26));
	PORTD->FUNC|=(1<<28)| (1<<26);

	
	PORTC->OE|=1<<10;
	PORTC->ANALOG|=(1<<13)|(1<<14)|(1<<10);
	PORTC->PWR|=(1<<26)|((3 << 28) | (3 << 20));
	PORTC->FUNC|=(3<<28)| (3<<26);
	
	UART2->CR = ((1 << 8)|(1 << 9)|1);
	fc =0;
}
