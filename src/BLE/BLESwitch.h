#ifndef BLE_Switch_H
#define BLE_Switch_H
#include "main.h"
void BLE_Commutator_Handler(uint8_t* data,unsigned short len);
void BLE_CommutatorInit(char channel);
char BLE_Commutator_Ethernet_Handler(uint8_t* data,unsigned short len);

#endif
