#ifndef FSMMN524_Client
#define FSMMN524_Client
#include "fcmprotocol.h"
#include "fsm_switch.h"
#include "fsm_subscriber_switch.h"

#define FSMDevCount 1
enum FSMDEV_Status
{
	Wait_Register,
	Registred,
	Wait_Unregistred,
	UnRegistred
};
struct FSMDEV 
{
	struct fsm_switch_subscriber fsm_ss;
	enum FSMDEV_Status status;
	unsigned short id;
	unsigned short idstream;
	short Mac[3];
	short MyMac[3];
	short hlen;
	unsigned char applay;
	unsigned char sendsetting;
	char InBuffer[2000];
};
void FSMRegister(char channel,unsigned short IDDevice, unsigned char type,unsigned char VidDevice, unsigned char PodVidDevice,unsigned char KodDevice);
void FSMDevice_Init(char channel);
void FSM_SendPacket(char channel,char* data,char len);
void FSMConnect(char nchannel,unsigned short id,unsigned short channel);
void FSMDisConnect(char channel);
void FSMKeyProcess(void);
void FSMProcess(char channel);
void FSMDeregister(char channel);
void FSMApplaySetting(char channel);
void FSMSendSetting(char channel);
void FSM_Wait(char channel);
#endif
