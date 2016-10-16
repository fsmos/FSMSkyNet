#include "main.h"
#include "timer.h"
#include "EthFunc.h"
#include "string.h"
#include "EthernetMain.h"
#include "FSM_Client.h"
#include "RS485Switch.h"

extern struct FSMDEV fsmd[FSMDevCount]; 


void ResLAN(void)
{

}
uint8_t EthernetStart()
{
	RST_CLK->ETH_CLOCK =(1<<24)|(3<<28)|(1<<27)|(0<<16);
	EthernetConfig();
 	NVIC_EnableIRQ(ETHERNET_IRQn);
	delay_ms(1000);

	return 1;
}
int32_t SendEthPacket(uint16_t *data, uint32_t data_cntr)
{
	return SendPacket(data, data_cntr);
}

void ETHERNET_Handler()
{
	unsigned short Status, r_count;
	_Rec_Frame Frame;
	int cntr = 0;
	extern unsigned int ETH_RecCntr;

	NVIC_DisableIRQ( ETHERNET_IRQn );

	/* */
	Status = ETHERNET->IFR;
	ETHERNET->IFR = Status;
	r_count = ETHERNET->STAT;
	ETHERNET->STAT = 0;// сброс регистра STAT
	r_count = (r_count >> 5) & 0x07;

	while(/*r_count != 0*/(Frame.Counter = ReadPacket(&Frame))!=0)
	{
		r_count--;
		//Frame.Counter = ReadPacket(&Frame);
		PacketAnaliser(&Frame);
		cntr++;
	}

  NVIC_ClearPendingIRQ(ETHERNET_IRQn);
	NVIC_EnableIRQ(ETHERNET_IRQn);
}

//*** Функция разбора полученного пакета
void PacketAnaliser(_Rec_Frame *frame)
{
	uint16_t  *data,data_len;
	uint16_t IpType;
	//-------------------------------------------
	/**/
	data = frame->Data;
	data_len = frame->Counter;
	IpType = data[6];// получили тип протокола IP, далее разбираем пакет в зависимости от протокола
	switch(IpType)
	{
		case 0x9619:
		memcpy(fsmd[0].InBuffer,data+7,data_len-14);
		if(fsmd[0].id==((struct FSM_Header*) (fsmd[0].InBuffer))->IDDevice)
		{
			switch(data[7] & 0x00ff)
			{
				case AnsRegDevice:
				
						fsmd[0].status=Registred;
						memcpy(fsmd[0].Mac,data+3,6);
						fsmd[0].sendsetting=1;
					break;
				case AnsDelList:

					break;
					case SendCmdToDevice:
						switch(((struct FSM_SendCmd*) (data+7))->cmd)
						{
				       case SetSettingSwitch:
							memcpy(&fsmd[0].fsm_ss,(((struct FSM_SendCmd*) (fsmd[0].InBuffer))->Data),sizeof(struct fsm_switch_subscriber));
							fsmd[0].applay=1;
								break;
							case GetSettingSwitch:
							fsmd[0].sendsetting=1;
							break;
						}
					break;
			}
		}
		else
		{
			if(RS485_Commutator_Ethernet_Handler((char*)fsmd[0].InBuffer,data_len-14)==0) return ;
		}	
		break;	
	}
}
