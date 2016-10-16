#ifndef nRFC_Switch_H
#define nRFC_Switch_H
#include "main.h"
void nRFC_Commutator_Handler(uint8_t* data,unsigned short len);
void nRFC_CommutatorInit(char channel);
char nRFC_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len);

#endif
