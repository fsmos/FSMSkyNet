#ifndef RS485_H
#define RS485_H
#include "main.h"
typedef void (*RS485Recive)(uint16_t byte);
typedef void (*RS485RecivePacket)(uint8_t* byte,unsigned short len);
struct RS485Data
{
	RS485Recive Handler;
	RS485RecivePacket  PacketHandler;
};
#define RS485_ChannelCount 2
void RS485_Init_SingleMode(RS485Recive Handler,char channel);
void RS485_Init_PacketMode(RS485RecivePacket  PacketHandler,char channel);
void RS485_SendByte(uint16_t byte,char channel);
void RS485_SendBytes(uint8_t* byte,unsigned short len,char channel);

#endif
