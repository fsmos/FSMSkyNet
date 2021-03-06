#include "RS485.h"
#include "FSM_Client.h"
#include "RS485Switch.h"
extern struct FSMDEV fsmd[FSMDevCount];  
void RS485_Commutator_Handler(uint8_t* data,unsigned short len)
{
	FSM_SendPacket(0,(char*)data,len);
}
void RS485_CommutatorInit(char channel)
{
	RS485_Init_PacketMode(RS485_Commutator_Handler,channel);
}
char RS485_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len)
{
	int i=0;
	unsigned short id=((struct FSM_Header*)data)->IDDevice;
	for(i=0;i<switch_count;i++)
	{
		if(fsmd[0].fsm_ss.fsmsdc.rs485_st.devs[i].dev_id==id)
		{
		RS485_SendBytes(data,len,fsmd[0].fsm_ss.fsmsdc.rs485_st.devs[i].channel);
		return 0;
		}
		//����� ������ ���� �������� 
		
	}
	return -1;
}
