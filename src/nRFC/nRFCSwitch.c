#include "nRFC.h"
#include "FSM_Client.h"
#include "nRFCSwitch.h"
extern struct FSMDEV fsmd[FSMDevCount];  
void nRFC_Commutator_Handler(uint8_t* data,unsigned short len)
{
	FSM_SendPacket(0,(char*)data,len);
}
void nRFC_CommutatorInit(char channel)
{
	nRFC_Init(nRFC_Commutator_Handler,channel);
}
char nRFC_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len)
{
	int i=0;
	unsigned short id=((struct FSM_Header*)data)->IDDevice;
	for(i=0;i<switch_count;i++)
	{
		if(fsmd[0].fsm_ss.fsmsdc.nRFC_st.devs[i].dev_id==id)
		{
		nRFC_SendBytes(data,len,fsmd[0].fsm_ss.fsmsdc.nRFC_st.devs[i].channel);
		return 0;
		}
		//����� ������ ���� �������� 
		
	}
	return -1;
}
