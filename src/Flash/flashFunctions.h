#ifndef __FLASH_FUNC_H
#define __FLASH_FUNC_H

#include "intTypes.h"// int types
#include "OPORA_eeprom.h"// для опоры размещать все в IRAM2

#define MAX_NUMBER_FLASH_ARRAY 16
#define ALIGN_VARIABLE_IN_MEMORY __align(4)

//#define EXECUTABLE_MEMORY_SECTION
#if !defined(EXECUTABLE_MEMORY_SECTION)
	#define EXECUTABLE_MEMORY_SECTION __attribute__((section("EXECUTABLE_MEMORY_SECTION")))
#endif
//#define FUNCTION_IN_RAM
#if !defined(FUNCTION_IN_RAM)
	#define FUNCTION_IN_RAM __RAMFUNC
#endif



FUNCTION_IN_RAM void flashInit(void) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM void flashClear(void) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM void flashProgramClear(void) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM uint8_t flashWrite(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM uint8_t flashRead( uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM uint8_t flashProgramWrite(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray) EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM uint8_t flashProgramRead( uint32_t begAdr , uint8_t *Array, uint32_t sizeArray) EXECUTABLE_MEMORY_SECTION;

FUNCTION_IN_RAM uint8_t  flashWriteArray(uint8_t *Array, uint32_t sizeArray)  EXECUTABLE_MEMORY_SECTION;
FUNCTION_IN_RAM uint32_t flashReadArray(uint32_t numberArray, uint8_t *Array) EXECUTABLE_MEMORY_SECTION;

FUNCTION_IN_RAM uint8_t WriteProgamToFlash(uint32_t begAdr , uint8_t *Array, uint32_t sizeArray ) EXECUTABLE_MEMORY_SECTION;

#endif

