/*
*/

#ifndef _ETHFUNC_H
#define _ETHFUNC_H

#include "EthernetMain.h"

void	SetPHYReg(unsigned char,unsigned char,unsigned short);
unsigned short	GetPHYReg(unsigned char,unsigned char);
void	PHYInit(unsigned char,unsigned char);

void MACReset(void);
void ClearMemory(void);

void vResetRx( void );
unsigned int ReadPacket(_Rec_Frame*);
int	SendPacket(void*, int);
void EthernetConfig(void);

#endif
