#ifndef _ETHERNET_MAIN_H
#define _ETHERNET_MAIN_H
#include "main.h"
typedef struct
{
        unsigned short Data[MAX_DATA]; //размер принимаемого пакета
        unsigned short Counter;         //счетчик кол-ва байт данных в буфере Data
		unsigned short Status;
} _Rec_Frame;

uint8_t EthernetStart(void);
void PacketAnaliser(_Rec_Frame *);

void SetServIPAddress(uint8_t, uint8_t, uint8_t, uint8_t);

int32_t SendEthPacket(uint16_t *, uint32_t);

void ResLAN(void);
void Ethernet_config(void);

#endif
