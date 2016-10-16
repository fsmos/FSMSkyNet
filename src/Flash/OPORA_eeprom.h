#ifndef __OPORA_EEPROM_H
#define __OPORA_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include	"1986VE1T.h"

//#define __CC_ARM

#define EEPROM_Latency_0                ((uint32_t)0x00000000)  /*!< EEPROM 0 Latency cycle  (MCU Clock up to  25 MHz) */
#define EEPROM_Latency_1                ((uint32_t)0x00000008)  /*!< EEPROM 1 Latency cycle  (MCU Clock up to  50 MHz) */
#define EEPROM_Latency_2                ((uint32_t)0x00000010)  /*!< EEPROM 2 Latency cycles (MCU Clock up to  75 MHz) */
#define EEPROM_Latency_3                ((uint32_t)0x00000018)  /*!< EEPROM 3 Latency cycles (MCU Clock up to 100 MHz) */
#define EEPROM_Latency_4                ((uint32_t)0x00000020)  /*!< EEPROM 4 Latency cycles (MCU Clock up to 125 MHz) */
#define EEPROM_Latency_5                ((uint32_t)0x00000028)  /*!< EEPROM 5 Latency cycles (MCU Clock up to 150 MHz) */
#define EEPROM_Latency_6                ((uint32_t)0x00000030)  /*!< EEPROM 6 Latency cycles (MCU Clock up to 175 MHz) */
#define EEPROM_Latency_7                ((uint32_t)0x00000038)  /*!< EEPROM 7 Latency cycles (MCU Clock up to 200 MHz) */

#define EEPROM_Latency_MSK      ((uint32_t)0x00000038)

#define EEPROM_Main_Bank_Select         ((uint32_t)0x00000000)  /*!< EEPROM Main Bank Selector */
#define EEPROM_Info_Bank_Select         ((uint32_t)0x00000001)  /*!< EEPROM Information Bank Selector */
#define EEPROM_All_Banks_Select         ((uint32_t)0x00000002)  /*!< EEPROM All Banks Selector */

#if defined ( __ICCARM__ )
   #define __RAMFUNC      __ramfunc
#elif defined (__CMCARM__)
  #define __RAMFUNC       __ramfunc
#elif defined ( __CC_ARM )
  #define __RAMFUNC
#endif

__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, uint32_t BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, uint32_t BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, uint32_t BankSelector, uint32_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
__RAMFUNC void EEPROM_EraseAllPages(uint32_t BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
#endif /* __MDR32F9Qx_EEPROM_H */

