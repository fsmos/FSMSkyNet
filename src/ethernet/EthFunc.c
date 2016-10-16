#ifndef	__ETH_FUNC_C__
#define __ETH_FUNC_C__

#include "main.h"
#include "EthFunc.h"
#include "timer.h"
#include "fsm_client.h"

extern struct FSMDEV fsmd[FSMDevCount];  
/* Разделение ЛАН-буфера */
#define DELIMITER 0x1000

/* Ethernet buffers MODE */
//#define FIFO_MODE

/* Ethernet regime */
#define LAN_100MB

/*-----------------------------------------------------
*------------------------------------------------------
*------------------------------------------------------
*--------------- Функции контроллра PHY ---------------
*------------------------------------------------------
*------------------------------------------------------
------------------------------------------------------*/

//*** Функция для конфигурирования PHY модуля через MDIO интерфейс ***
//Addr - адрес модуля PHY
//Mode - режим работы контроллера PHY
void	PHYInit(unsigned char Addr, unsigned char Mode)
{
		unsigned int	tmp;

		// Сброс PHY
		ETHERNET->PHY_CTRL &= ~1;
		delay_ms(20);

		tmp = ETHERNET->PHY_CTRL;
		tmp &= 0x0770;// сбросили поля адреса PHY, режима работы по умолчанию, режим FiberOptic
		tmp |= (Addr << 11) | (Mode << 1 ) | 1;
		ETHERNET->PHY_CTRL = tmp;

		// !!! Экспиремент с дополнительными регистрами PHY
		/*tmp = GetPHYReg( Addr, 4 );
		tmp &= ~(0x0F << 5);
		tmp |= (0x03 << 5);// Режим 10 BASE-T FD
		//tmp |= (0x01 << 5);// Режим 10 BASE-T HD
		SetPHYReg( Addr, 4, tmp );
		//
		tmp = GetPHYReg( Addr, 4 );
		tmp += 0;*/

		tmp = ETHERNET->PHY_CTRL;
		tmp &= 0x0770;// сбросили поля адреса PHY, режима работы по умолчанию, режим FiberOptic
		tmp |= (Addr << 11) | (Mode << 1 ) | 1;
		ETHERNET->PHY_CTRL = tmp;
		while((ETHERNET->PHY_STATUS & 0x10) == 0);// ждем пока модуль в состоянии сброса
}

//*** Функция для записи регистров PHY модуля через MDIO интерфейс ***
//Addr	- адрес модуля PHY
//Num	- номер регистра, куда будем записывать данные
//Data	- данные для записи
void	SetPHYReg(unsigned char Addr, unsigned char Num, unsigned short Data)
{
	uint32_t i;
	ETHERNET->MDIO_DATA=Data;
	i=0xC000|((Addr&0x1F)<<8)|(Num&0x1F)|(0x01<<5);
	ETHERNET->MDIO_CTRL=(uint16_t)i;
	while((ETHERNET->MDIO_CTRL&0x8000)==0);
}

//*** Функция для чтения регистров PHY модуля через MDIO интерфейс ***
//Addr	- адрес модуля PHY
//Num	- номер регистра, который необходимо прочитать
//возвращает значение регистра по адресу Num в Addr модуле PHY.
unsigned short	GetPHYReg(unsigned char Addr, unsigned char Num)
{
	uint32_t i;
	i=0xE000|((Addr&0x1F)<<8)|(0x1<<5)|(Num&0x1F);
	ETHERNET->MDIO_CTRL=(uint16_t)i;
	while((ETHERNET->MDIO_CTRL&0x8000)==0);
	return	ETHERNET->MDIO_DATA;
}

/*-----------------------------------------------------
*------------------------------------------------------
*------------------------------------------------------
*--------------- Функции контроллра MAC ---------------
*------------------------------------------------------
*------------------------------------------------------
-----------------------------------------------------*/

//*** Функция для конфигурирования MAC модуля ***
void EthernetConfig()
{
#ifdef LAN_100MB
	//PHYInit(0x1C, 2);// 100 HD, без автоподстройки
	//PHYInit(0x1C, 3);// 100 FD, без автоподстройки
  PHYInit(0x1C, 7);// 100 FD, c автоподстройкой
#else
	PHYInit(0x1C, 1);// 10 FD, без автоподстройки
	//PHYInit(0x1C, 0);// 10 HD, без автоподстройки
	//PHYInit(0x1C, 7);// Полностью автоматический режим
#endif

	ETHERNET->MAC_T = fsmd[0].fsm_ss.fsmsdc.MyMac[0];
	ETHERNET->MAC_M = fsmd[0].fsm_ss.fsmsdc.MyMac[1];
	ETHERNET->MAC_H = fsmd[0].fsm_ss.fsmsdc.MyMac[2];
	MACReset();

	ETHERNET->IMR = 0x0001;// разрешение прерываний при успешном приеме пакета
}

//*** Функция для конфигурирования MAC модуля с исходными значениями регистров ***
void MACReset()
{
#ifdef LAN_100MB
	ETHERNET->G_CFG |= (3 << 16);// RRST=1, XRST=1 сброс приемника и передатчика

	ClearMemory();

	ETHERNET->Delimiter = DELIMITER;

	ETHERNET->HASH0=0;
	ETHERNET->HASH1=0;
	ETHERNET->HASH2=0;
	ETHERNET->HASH3=0x8000;

	ETHERNET->IPG=0x0060;
	ETHERNET->PSC=0x0050;
	ETHERNET->BAG=0x0200;
	ETHERNET->JitterWnd=0x0005;
	ETHERNET->R_CFG=0x8406;
	ETHERNET->X_CFG=0x81FA;

	/* ??? */
	//ETHERNET->X_CFG &= ~(1 << 4);// нет паузы между отправкой пакета

#ifndef FIFO_MODE
	ETHERNET->G_CFG=0x30030080;// | (1 << 12);// линейный режим работы буферов.
#else
	ETHERNET->G_CFG=0x30032080;// режим FIFO
#endif

	ETHERNET->IMR=0;
	ETHERNET->IFR=0xFFFF;

#ifndef FIFO_MODE
	ETHERNET->R_Head=0x0000;
	ETHERNET->X_Tail = DELIMITER;
#endif

	/* Без этого при включеном передатчике приемник пропускал пакеты ??? */
	ETHERNET->G_CFG |= (1 << 10);// полудуплексный режим включен

	ETHERNET->G_CFG &= ~(3 << 16);// RRST=0, XRST=0 штатный режим работы

#else // LAN 10MB
	ETHERNET->G_CFG |= (3 << 16);// RRST=1, XRST=1 сброс приемника и передатчика

	ClearMemory();

	ETHERNET->Delimiter = DELIMITER;

	ETHERNET->HASH0=0;
	ETHERNET->HASH1=0;
	ETHERNET->HASH2=0;
	ETHERNET->HASH3=0x8000;

	ETHERNET->IPG=0x0060;
	ETHERNET->PSC=0x0050;
	ETHERNET->BAG=0x0200;
	ETHERNET->JitterWnd=0x0005;
	ETHERNET->R_CFG=0x8406;
	ETHERNET->X_CFG=0x81FA;

	ETHERNET->X_CFG |= (1 << 4);// есть пауза между отправкой пакета

#ifndef FIFO_MODE
	ETHERNET->G_CFG = 0x30030080;// линейный режим работы буферов
#else
	ETHERNET->G_CFG = 0x30032080;// режим FIFO
#endif

	//ETHERNET->G_CFG |= (1 << 9);// DTRM_EN

	ETHERNET->IMR=0;
	ETHERNET->IFR=0xFFFF;

#ifndef FIFO_MODE
	ETHERNET->R_Head=0x0000;
	ETHERNET->X_Tail = DELIMITER;
#endif

	//ETHERNET->G_CFG |= (1 << 10);// полудуплексный режим включен

	ETHERNET->G_CFG &= ~(3 << 16);// RRST=0, XRST=0 штатный режим работы
#endif
}

//*** Функция для очистки буферов приемника и передатчика MAC модуля ***
//Буфер приемника 4096 байт
//Буфер передатчика 4096 байт
void ClearMemory()
{
	unsigned int Temp;
	unsigned int* ptr;
	ptr=(unsigned int*)0x38000000;
	for(Temp=0;Temp<2048;Temp++)	*ptr++=0;
}



/*---------------------------------------------------------------------------------------------------
*--------------- Функции для работы с буферами приемника и передатчика контроллра MAC ---------------
---------------------------------------------------------------------------------------------------*/
void vResetRx( void )
{
	/* останавливаем приемник */
	ETHERNET->G_CFG |= (1 << 17);

	/* переинициализируем регистры */
	ETHERNET->R_Head=0x0000;

	/* запускаем приемник */
	ETHERNET->G_CFG &= (~(1 << 17));
}
//*** Функция для считывания пакета из буфера приемника ***
//*** *Frame - указтель на структуру пакета
#ifndef FIFO_MODE
unsigned int ReadPacket(_Rec_Frame* Frame)
{
        unsigned short space_start=0,space_end=0,tail,head;
		unsigned int* src;
		unsigned int* dst;
		unsigned int size, i;
		unsigned short tmp[2];

	tail=ETHERNET->R_Tail;
	head=ETHERNET->R_Head;

	if(tail == head)
		return 0;

	if(tail>head)
	{
		space_end=tail-head;
		space_start=0;
	}
	else
	{
		space_end = DELIMITER - head;
		space_start = tail;
	}

	src=(unsigned int*)(0x38000000+head);
	dst=(unsigned int*)(Frame->Data);

	*((unsigned int*)tmp)=*src++;// прочитали кол-во байт в полученном пакете

	space_end-=4;
	if((unsigned short)src > (DELIMITER-1))	src=(unsigned int*)0x38000000;

	size=(tmp[0]+3)/4;
	
	if(size > 1519){
#ifdef _DEBUG
	_printf( "!!! ResetRx !!!\r\n" );
#endif
		vResetRx();
		return 0;
	}	

	if(tmp[0]<=space_end)
	{
		for(i=0;i<size;i++)
			*dst++ = *src++;
	}
	else
	{
		size=size-space_end/4;
		for(i=0; i<(space_end/4); i++)
			*dst++ = *src++;
		src=(unsigned int*)0x38000000;
		for(i=0; i<size; i++)
			*dst++ = *src++;
	}
	if((unsigned short)src>(DELIMITER))	src=(unsigned int*)0x38000000;

	ETHERNET->R_Head=(unsigned short)src;
	ETHERNET->STAT-=0x20;

	return tmp[0];
}
#else
unsigned int ReadPacket(_Rec_Frame* Frame)
{
	unsigned int *src;
	unsigned int *dst;
	unsigned int size, i;
	unsigned int tmp;
	
	src = (unsigned int *) 0x38000000;
	dst = (unsigned int *) Frame->Data;

	tmp = *src;// прочитали кол-во байт в полученном пакете
	tmp &= 0x0000FFFF;

	size = (tmp + 3) >> 2;
	for(i = 0; i < size; i++)
	{
		*dst++ = *src;
	}

	return tmp;
}
#endif

//*** Функция для записи пакета в буфер передатчика ***
//*** *buffer - указтель на буфер данных
//*** size - кол-во отправляемых байт
#ifndef FIFO_MODE
int	SendPacket(void* buffer, int size)
{
	unsigned short	i;
	unsigned int	tmp;
	unsigned int	head;
	unsigned int	tail;
	unsigned int*	src;
	unsigned int*	dst;
	unsigned short	space[2];

	head = ETHERNET->X_Head;
	tail = ETHERNET->X_Tail;

	//вычисляем кол-во свободного места в буфере передатчика
	if(head>tail)
	{
		space[0]=head-tail;
		space[1]=0;
	} else
	{
		space[0]=0x2000-tail;
		space[1]=head-DELIMITER;
	}
	//вычислили кол-во свободного места в буфере передатчика

	if(size>(space[0]+space[1]-8))
		return 0;	//-8, так как 4 байта занимает поле длины данных и 4 байта занимает поле статуса пакета

	tmp=size;
	src=buffer;
	dst=(unsigned int*)(0x38000000+tail);
	
	*dst++ =tmp;
	space[0]-=4;
	if((unsigned short)dst>0x1FFC)	dst=(unsigned int*)(0x38000000+DELIMITER);

	tmp=(size+3)/4;

	if(size<=space[0])
	{
		for(i=0; i<tmp; i++)
			*dst++ = *src++;
	}
	else
	{
		tmp-=space[0]/4;
		for(i=0;i<(space[0]/4);i++)
			*dst++ = *src++;
		dst=(unsigned int*)(0x38000000+DELIMITER);
		for(i=0;i<tmp;i++)
			*dst++ = *src++;
	}
	if((unsigned short)dst>0x1FFC)	dst=(unsigned int*)(0x38000000+DELIMITER);
	tmp=0;
	*dst++ =tmp;
	if((unsigned short)dst>0x1FFC)	dst=(unsigned int*)(0x38000000+DELIMITER);

	ETHERNET->X_Tail=(unsigned short)dst;
	return	size;
}
#else
int	SendPacket(void* buffer, int size)
{
	unsigned int i;
	unsigned int tmp;
	unsigned int *src;
	unsigned int *dst;

	src = buffer;
	dst = (unsigned int *) 0x38000004;
	*dst = size;

	tmp = (size + 3) / 4;
	for(i = 0; i < tmp; i++)
	{
		*dst = *src++;
	}
	*dst = 0;

	return size;
}
#endif


#endif	//__ETH_FUNC_C__
