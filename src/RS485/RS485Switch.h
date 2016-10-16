#ifndef RS485_Switch_H
#define RS485_Switch_H
#include "main.h"
void RS485_Commutator_Handler(uint8_t* data,unsigned short len);
void RS485_CommutatorInit(char channel);
char RS485_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len);
#endif
