#define __MAIN__
#include "main.h"
// Переферия
#include "timer.h"
#include "peripheral.h"
// Драйвер
#include "FSM_Client.h"
//Ethernet
#include "EthernetMain.h"
#include <stdlib.h>
#include <string.h>
#include "fsm_client.h"
#include "flashFunctions.h"
#include "RS485.h"

extern struct FSMDEV fsmd[FSMDevCount];  
char i;
int main(){	
	
	
	TIM_initialization();													// Системный таймер
	PER_initialization();		
  memset(&fsmd[0],0,sizeof(struct FSMDEV));
	//if ( ! flashReadArray(0,(uint8_t*)&fsmd[0].fsm_ss)){
	//	flashClear();
	//}
  
	fsmd[0].fsm_ss.fsmsdc.MyMac[0]=0x0102;
	fsmd[0].fsm_ss.fsmsdc.MyMac[1]=0x0304;
	fsmd[0].fsm_ss.fsmsdc.MyMac[2]=0x0506;

	
	EthernetStart();													 	// Старт Ethernet модуля
	FSMDevice_Init(0);
	RS485_Init();
	while(1)
	{
		FSM_Wait(0);
		FSMProcess(0);
		RS485_SendByte(i++,0);
  }
}