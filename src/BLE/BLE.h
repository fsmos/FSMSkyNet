#ifndef BLE_H
#define BLE_H
#include "main.h"
typedef void (*BLERecivePacket)(uint8_t* byte,unsigned short len);
struct BLEData
{
	BLERecivePacket  PacketHandler;
};
#define BLE_ChannelCount 2
void BLE_Init(BLERecivePacket  PacketHandler,char channel);
void BLE_SendBytes(uint8_t* Data, unsigned short Len,char channel);
#endif

