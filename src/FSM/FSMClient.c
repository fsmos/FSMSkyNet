#include "FSM_Client.h"
#include "EthernetMain.h"  
#include "timer.h"
#include <string.h>

#include "flashFunctions.h"
	struct FSM_SendCmdTS fsmdc;
struct FSMDEV fsmd[FSMDevCount];  
int timer=0;
void FSM_SendPacket(char channel,char* data,char len)
{
	int res;
	uint16_t Buff[MAX_DATA];
	uint16_t *Datas;
	Buff[0] = fsmd[channel].Mac[0];
	Buff[1] = fsmd[channel].Mac[1];
	Buff[2] = fsmd[channel].Mac[2];
	// наш MAC
	Buff[3] = fsmd[channel].MyMac[0];
	Buff[4] = fsmd[channel].MyMac[1];
	Buff[5] = fsmd[channel].MyMac[2];
	// тип протокола
	Buff[6] = 0x9619;// IP-тип
	Datas=Buff+7;
	memcpy(Datas,data,len);
	res=SendEthPacket( Buff, len+14);
	res=res+1;
}
void FSMDevice_Init(char channel)
{
	//
	fsmd[channel].Mac[0]=0xFFFF;
	fsmd[channel].Mac[1]=0XFFFF;
	fsmd[channel].Mac[2]=0xFFFF;
	fsmd[channel].status=UnRegistred;
	memcpy(fsmd[channel].MyMac,&fsmd[0].fsm_ss.fsmsdc.MyMac,sizeof(fsmd[0].fsm_ss.fsmsdc.MyMac));
	FSMRegister(channel,10,Switch,SkyNet,K1986BE1T,BLE_nRFC_RS485_Ethernet);
	fsmd[channel].applay=0;
	fsmd[channel].sendsetting=0;
	timer=0;
}

void FSMRegister(char channel,unsigned short IDDevice, unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice)
{
	struct FSM_DeviceRegistr dev_reg;
	memset(&dev_reg,0,sizeof(struct FSM_DeviceRegistr));
	dev_reg.CRC=0;
	dev_reg.IDDevice=IDDevice;
	dev_reg.KodDevice=KodDevice;
	dev_reg.PodVidDevice=PodVidDevice;
	dev_reg.VidDevice=VidDevice;
	dev_reg.type=type;
	dev_reg.opcode=RegDevice;
	fsmd[channel].id=IDDevice;
	FSM_SendPacket(channel,(char*)&dev_reg,sizeof(dev_reg));
}
void FSM_Run(char num_ch)
{
	
}
void FSMKeyProcess()
{
	
}
void FSMProcess(char channel)
{
	if(fsmd[channel].applay)
	{
		FSMApplaySetting(channel);
		fsmd[channel].applay=0;
	}
	if(fsmd[channel].sendsetting)
	{
		FSMSendSetting(channel);
		fsmd[channel].sendsetting=0;
	}
}
void FSMDeregister(char channel)
{
	struct FSM_DeviceDelete delp;
	memset(&delp,0,sizeof(struct FSM_DeviceDelete));
	delp.IDDevice=fsmd[channel].id;
	delp.opcode=DelLisr;
	FSM_SendPacket(channel,(char*)&delp,sizeof(struct FSM_DeviceDelete));
}
void FSMApplaySetting(char channel)
{
	FSMDeregister(0);
	flashClear();
  flashWriteArray((uint8_t*)&fsmd[0].fsm_ss, sizeof(struct fsm_switch_subscriber));	
	RST_CLK->PER_CLOCK |= (1<<12);
	WWDG->CFR = 0x00;
	WWDG->CR = 0xFF;
	WWDG->CR = 0xFF;
}
void FSMSendSetting(char channel)
{

	memset(&fsmdc,0,sizeof(struct FSM_SendCmdTS));
	fsmdc.opcode=SendCmdToServer;
	fsmdc.countparam=1;
	fsmdc.IDDevice=fsmd[channel].id;
	fsmdc.cmd=AnsGetSettingSwitch;
	memcpy(fsmdc.Data,&fsmd[0].fsm_ss,sizeof(struct fsm_switch_subscriber));
	FSM_SendPacket(channel,(char*)&fsmdc,sizeof(struct FSM_SendCmdTS)-sizeof(fsmdc.Data)+sizeof(struct fsm_switch_subscriber));
}
void FSM_Wait(char channel)
{
	if(fsmd[0].status==UnRegistred)
	{
		if((GetTime()-timer)>10000)
		{
		timer=GetTime();
		FSMRegister(channel,10,Switch,SkyNet,K1986BE1T,BLE_nRFC_RS485_Ethernet);
		}
	}
}
