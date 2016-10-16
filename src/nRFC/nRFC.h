#ifndef nRFC_H
#define nRFC_H
#include "main.h"
typedef void (*nRFCRecivePacket)(uint8_t* byte,unsigned short len);
struct nRFCData
{
	nRFCRecivePacket  PacketHandler;
};
#define nRFC_ChannelCount 2
void nRFC_Init(nRFCRecivePacket  PacketHandler,char channel);
void nRFC_SendBytes(uint8_t* Data, unsigned short Len,char channel);

#endif
