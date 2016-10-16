#include "BLE.h"
#include "FSM_Client.h"
#include "BLESwitch.h"
extern struct FSMDEV fsmd[FSMDevCount];  
void BLE_Commutator_Handler(uint8_t* data,unsigned short len)
{
	FSM_SendPacket(0,(char*)data,len);
}
void BLE_CommutatorInit(char channel)
{
	BLE_Init(BLE_Commutator_Handler,channel);
}
char BLE_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len)
{
	int i=0;
	unsigned short id=((struct FSM_Header*)data)->IDDevice;
	for(i=0;i<switch_count;i++)
	{
		if(fsmd[0].fsm_ss.fsmsdc.ble_st.devs[i].dev_id==id)
		{
		BLE_SendBytes(data,len,fsmd[0].fsm_ss.fsmsdc.ble_st.devs[i].channel);
		return 0;
		}
		//Здесь должна быть проверка 
		
	}
	return -1;
}
