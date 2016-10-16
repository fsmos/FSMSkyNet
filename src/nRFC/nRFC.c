#include "nRFC.h"
struct nRFCData nRFCDev[nRFC_ChannelCount];
void nRFC_Init(nRFCRecivePacket  PacketHandler, char channel )
{
	nRFCDev[channel].PacketHandler=PacketHandler;
}
void nRFC_SendBytes(uint8_t* Data, unsigned short Len,char channel)
{
	
}
