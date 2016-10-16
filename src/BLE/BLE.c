#include "BLE.h"
struct BLEData BLEDev[BLE_ChannelCount];
void BLE_Init(BLERecivePacket  PacketHandler, char channel )
{
	BLEDev[channel].PacketHandler=PacketHandler;
}
void BLE_SendBytes(uint8_t* Data, unsigned short Len,char channel)
{
	
}
