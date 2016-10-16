#include "CRC32.h"
#include "flashFunctions.h"

#define MAX_WRITE_READ_BYTES 4096
#define MAX_WRITE_READ_BYTES_PROGRAM (128*1024)

#define TRUE  1
#define FALSE 0

// поэкспериментировать с записью во флэшь 
// без предварительного стирания
// записивать в старшие адреса

// hardfault происходит из за того что опоре не нраваятся некоторые адреса
// при возникновении проблем проверять uint8_t *Array
// сбой происходит при чтении 

// перед записью память должна быть отчишена

// выравнивание адреса по 4 байтам

uint32_t localWriteIndex = 0 ;
uint32_t currentNumberArray = 0 ;

// желательно чтобы начальный адрес должен быть кратен 4 
FUNCTION_IN_RAM uint8_t flashWrite(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ){
	uint32_t i;
	uint32_t n_words,n_rem;
	uint32_t *m_adr;
	uint32_t writeAddr = 0;
	
	if (sizeArray == 0) return FALSE;
	if (sizeArray > MAX_WRITE_READ_BYTES) return FALSE;
	
	__disable_irq();	
	RST_CLK->PER_CLOCK |= 0x08;			//EEPROM_CNTRL Clock enable
	
	writeAddr = begAdr / 4 ;
	if (begAdr % 4) writeAddr++;
  m_adr = (uint32_t *)Array;
	n_words = sizeArray / 4 ;
	n_rem = sizeArray % 4;
	if (n_rem) n_words++;
	
	for (i = 0 ; i < n_words ; i++)
		EEPROM_ProgramWord(writeAddr++ << 2, EEPROM_Info_Bank_Select, m_adr[i]);
	
	RST_CLK->PER_CLOCK&=(~0x08);//EEPROM_CNTRL Clock disable
  __enable_irq();	
	
	return TRUE;

}


FUNCTION_IN_RAM uint8_t flashRead(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray){
	uint32_t *m_adr, *bufPointer;
	uint32_t i,j ;
	uint32_t n_words = 0 , n_rem = 0 ;
	uint32_t bufSize;
	uint32_t readAddr;
	uint8_t buffer[5];

	if (sizeArray > MAX_WRITE_READ_BYTES) return FALSE;
	
	__disable_irq();
	RST_CLK->PER_CLOCK|=0x08;											//EEPROM_CNTRL Clock enable
	
	bufPointer = (uint32_t*)&buffer;
	readAddr = begAdr / 4;	
	if (begAdr % 4) readAddr++;	
  m_adr = (uint32_t*)Array;
	n_words = sizeArray / 4 ;
	n_rem = sizeArray % 4;
	if (n_rem) n_words++;

  for (i = 0 ; i < n_words - 1 ; i++ ){
		m_adr[i] = EEPROM_ReadWord( readAddr++ << 2, EEPROM_Info_Bank_Select);  
	}
	
	bufPointer[0] = EEPROM_ReadWord( readAddr++ << 2, EEPROM_Info_Bank_Select);
	
	if ( n_rem == 0 ){
		m_adr[i] = bufPointer[0];
	} else {
		bufSize = sizeArray;
		bufSize = 4 - ( ( 4 * n_words ) - bufSize ) ;
		if (bufSize < 4){
			for (j = 0 ; j < bufSize ; j++){
				Array[i*4+j] = buffer[j];
			}		
		}else {
	    RST_CLK->PER_CLOCK &= (~0x08);	//EEPROM_CNTRL Clock disable
      __enable_irq();				
			return FALSE;
		}
	}
	
	RST_CLK->PER_CLOCK &= (~0x08);	//EEPROM_CNTRL Clock disable
  __enable_irq();		

	return TRUE;
}


FUNCTION_IN_RAM uint8_t flashProgramWrite(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ){
	uint32_t i;
	uint32_t n_words,n_rem;
	uint32_t *m_adr;
	uint32_t writeAddr = 0;
	
	if (sizeArray == 0) return FALSE;
	if (sizeArray > MAX_WRITE_READ_BYTES_PROGRAM) return FALSE;
	
	__disable_irq();	
	RST_CLK->PER_CLOCK |= 0x08;			//EEPROM_CNTRL Clock enable
	EEPROM_EraseAllPages(EEPROM_Main_Bank_Select);
	
	writeAddr = begAdr / 4 ;
	if (begAdr % 4) writeAddr++;
  m_adr = (uint32_t *)Array;
	n_words = sizeArray / 4 ;
	n_rem = sizeArray % 4;
	if (n_rem) n_words++;
	
	for (i = 0 ; i < n_words ; i++){
		EEPROM_ProgramWord(writeAddr++ << 2, EEPROM_Main_Bank_Select, m_adr[i]);	
	}
	RST_CLK->PER_CLOCK&=(~0x08);//EEPROM_CNTRL Clock disable
  __enable_irq();	
	
	return TRUE;
}

FUNCTION_IN_RAM uint8_t flashProgramRead(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray){
	uint32_t *m_adr, *bufPointer;
	uint32_t i,j ;
	uint32_t n_words = 0 , n_rem = 0 ;
	uint32_t bufSize;
	uint32_t readAddr;
	uint8_t buffer[5];

	if (sizeArray > MAX_WRITE_READ_BYTES_PROGRAM) return FALSE;
	
	__disable_irq();
	RST_CLK->PER_CLOCK|=0x08;											//EEPROM_CNTRL Clock enable
	
	bufPointer = (uint32_t*)&buffer;
	readAddr = begAdr / 4;	
	if (begAdr % 4) readAddr++;	
  m_adr = (uint32_t*)Array;
	n_words = sizeArray / 4 ;
	n_rem = sizeArray % 4;
	if (n_rem) n_words++;

  for (i = 0 ; i < n_words - 1 ; i++ ){
		m_adr[i] = EEPROM_ReadWord( readAddr++ << 2, EEPROM_Main_Bank_Select);  
	}
	
	bufPointer[0] = EEPROM_ReadWord( readAddr++ << 2, EEPROM_Main_Bank_Select);
	
	if ( n_rem == 0 ){
		m_adr[i] = bufPointer[0];
	} else {
		bufSize = sizeArray;
		bufSize = 4 - ( ( 4 * n_words ) - bufSize ) ;
		if (bufSize < 4){
			for (j = 0 ; j < bufSize ; j++){
				Array[i*4+j] = buffer[j];
			}		
		}else {
			RST_CLK->PER_CLOCK &= (~0x08);	//EEPROM_CNTRL Clock disable
			__enable_irq();				
			return FALSE;
		}
	}
	
	RST_CLK->PER_CLOCK &= (~0x08);	//EEPROM_CNTRL Clock disable
  __enable_irq();		

	return TRUE;
}



FUNCTION_IN_RAM uint8_t flashWriteArray(uint8_t *Array, uint32_t sizeArray){
	uint32_t i;
	uint32_t n_words,n_rem;
	uint32_t bufCRC32;
	uint32_t *m_adr;

	if (sizeArray == 0 ) return FALSE;
	if (sizeArray > MAX_WRITE_READ_BYTES) return FALSE;

	if ( ( currentNumberArray > MAX_NUMBER_FLASH_ARRAY ) ||
 		   ( localWriteIndex >= (MAX_WRITE_READ_BYTES/4) ) ){
		return FALSE;
	}	
	__disable_irq();	
	RST_CLK->PER_CLOCK |= 0x08;			//EEPROM_CNTRL Clock enable
	
	bufCRC32 = crc32NT(0, Array, sizeArray);
  m_adr = (uint32_t *)Array;
	n_words = sizeArray / 4 ;
	n_rem = sizeArray % 4;
	if (n_rem) n_words++;
	
	EEPROM_ProgramWord(currentNumberArray++ << 2,  EEPROM_Info_Bank_Select,localWriteIndex);
	EEPROM_ProgramWord(localWriteIndex++ << 2,   EEPROM_Info_Bank_Select,sizeArray);
	for (i = 0 ; i < n_words ; i++)
		EEPROM_ProgramWord(localWriteIndex++ << 2, EEPROM_Info_Bank_Select, m_adr[i]);
	EEPROM_ProgramWord(localWriteIndex++ << 2,   EEPROM_Info_Bank_Select,bufCRC32);
	
	RST_CLK->PER_CLOCK&=(~0x08);//EEPROM_CNTRL Clock disable
  __enable_irq();	
	
	return TRUE;
}

FUNCTION_IN_RAM uint32_t flashReadArray(uint32_t numberArray, uint8_t *Array){
	uint32_t originalCRC32 = 0 , bufCRC32 = 0 ;
	uint32_t *m_adr, *bufPointer;
	uint32_t i,j ;
	uint32_t n_words = 0 , n_rem = 0 ;
	uint32_t readIndex = 0 ;
	uint32_t bufSize;
	uint32_t returnSize;
	uint8_t buffer[5];

	__disable_irq();
	RST_CLK->PER_CLOCK|=0x08;											//EEPROM_CNTRL Clock enable
	
	readIndex  = EEPROM_ReadWord(numberArray << 2 , EEPROM_Info_Bank_Select);
	bufSize = EEPROM_ReadWord(readIndex++ << 2 , EEPROM_Info_Bank_Select);
	returnSize = bufSize;
	
	if (bufSize > MAX_WRITE_READ_BYTES){
		RST_CLK->PER_CLOCK&=(~0x08);									//EEPROM_CNTRL Clock disable
		__enable_irq();
		return 0;
	}
/**/
	
	bufPointer = (uint32_t*)&buffer;
  m_adr = (uint32_t*)Array;
	n_words = bufSize / 4 ;
	n_rem = bufSize % 4;
	if (n_rem) n_words++;

  for (i = 0 ; i < n_words - 1 ; i++ ){
		m_adr[i] = EEPROM_ReadWord( readIndex++ << 2, EEPROM_Info_Bank_Select);  
	}
	
	bufPointer[0] = EEPROM_ReadWord( readIndex++ << 2, EEPROM_Info_Bank_Select);
	
	if ( n_rem == 0 ){
		m_adr[i] = bufPointer[0];
	} else {
		bufSize = 4 - ( ( 4 * n_words ) - bufSize ) ;
		if (bufSize < 4){
			for (j = 0 ; j < bufSize ; j++){
				Array[i*4+j] = buffer[j];
			}		
		}else {
			RST_CLK->PER_CLOCK&=(~0x08);									//EEPROM_CNTRL Clock disable
			__enable_irq();
			return 0;
		}
	}
	
	originalCRC32 = EEPROM_ReadWord( readIndex++ << 2, EEPROM_Info_Bank_Select);
	bufCRC32 = crc32NT(0, (uint8_t*)m_adr, returnSize);

	RST_CLK->PER_CLOCK &= (~0x08);	//EEPROM_CNTRL Clock disable
  __enable_irq();		

	if (originalCRC32 != bufCRC32) return 0;
	return returnSize;
};


FUNCTION_IN_RAM void flashClear(void){
	flashInit();
	__disable_irq();
	RST_CLK->PER_CLOCK|=0x08;											//EEPROM_CNTRL Clock enable
	EEPROM_ErasePage(0,EEPROM_Info_Bank_Select);
	RST_CLK->PER_CLOCK&=(~0x08);									//EEPROM_CNTRL Clock disable
  __enable_irq();
};

FUNCTION_IN_RAM void flashProgramClear(void){
	__disable_irq();
	RST_CLK->PER_CLOCK|=0x08;											//EEPROM_CNTRL Clock enable
	EEPROM_EraseAllPages(EEPROM_Main_Bank_Select);
	RST_CLK->PER_CLOCK&=(~0x08);									//EEPROM_CNTRL Clock disable
  __enable_irq();
};


FUNCTION_IN_RAM void flashInit(void){
	localWriteIndex = MAX_NUMBER_FLASH_ARRAY + 1 ;
	currentNumberArray = 0 ;
}


FUNCTION_IN_RAM uint8_t WriteProgamToFlash(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ){
	__disable_irq();
	flashProgramWrite(begAdr , Array, sizeArray );
	__enable_irq();	
	RST_CLK->PER_CLOCK |= (1<<12);
	WWDG->CFR = 0x00;
	WWDG->CR = 0xFF;
	WWDG->CR = 0xFF;
	while(1);
}




