/**
  ******************************************************************************
  * @file    MDR32F9Qx_eeprom.c
  * @author  Phyton Application Team
  * @version V1.2.0
  * @date    11/06/2010
  * @brief   This file contains all the EEPROM firmware functions.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE MDR32F9Qx_eeprom.c
  */

/* Includes ------------------------------------------------------------------*/
#include "OPORA_eeprom.h"

#define FLASH_PROG_FREQ_MHZ             (8.0)
#define DELAY_LOOP_CYCLES               (8UL)
#define GET_US_LOOPS(N)                 ((uint32_t)((float)(N) * FLASH_PROG_FREQ_MHZ / DELAY_LOOP_CYCLES))

#define EEPROM_REG_ACCESS_KEY           ((uint32_t)0x8AAA5551)
#define EEPROM_CMD_DELAY_Msk            ((uint32_t)0x00000038)

__RAMFUNC static void ProgramDelay(uint32_t Loops) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

__RAMFUNC static void ProgramDelay(uint32_t Loops)
{
  volatile uint32_t i = Loops;
  for (; i > 0; i--)
  {
  }
}

/**
  * @brief  Reads the 32-bit EEPROM memory value.
  * @param  Address: The EEPROM memory word address (four byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval The selected EEPROM memory value.
  */
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Data;

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  EEPROM->DO;   /* Idle Reading for Delay */
  Data = EEPROM->DO;
  Command &= EEPROM_CMD_DELAY_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
  return Data;
}

/**
  * @brief  Erases one page of the selected EEPROM memory bank.
  * @param  Address: Page Address in the EEPROM memory.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @retval None
  */
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Offset;

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  EEPROM->CMD = Command;

  for (Offset = 0; Offset < (4 << 2); Offset += 4)
  {
    EEPROM->ADR = Address + Offset;             /* Page Address */
    EEPROM->DI = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
    Command |= EEPROM_CMD_NVSTR;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(40000));          /* Wait for 40 ms */
    Command &= ~EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(1));              /* Wait for 1 us */
  }
  Command &= EEPROM_CMD_DELAY_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
}

/**
  * @brief  Programs the 32-bit EEPROM memory value.
  * @param  Address: The EEPROM memory word address (four byte aligned).
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_Info_Bank_Select:      The EEPROM Information Bank selector.
  * @param  Data: The data value to be programmed.
  * @retval None
  */
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, uint32_t BankSelector, uint32_t Data)
{
  uint32_t Command;

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  BankSelector = (BankSelector == EEPROM_Info_Bank_Select) ? EEPROM_CMD_IFREN : 0;
  Command = EEPROM->CMD & EEPROM_CMD_DELAY_Msk;
  Command |= EEPROM_CMD_CON | BankSelector;
  EEPROM->CMD = Command;
  EEPROM->ADR = Address;
  EEPROM->DI  = Data;
  Command |= EEPROM_CMD_XE | EEPROM_CMD_PROG;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
  Command |= EEPROM_CMD_NVSTR;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(10));               /* Wait for 10 us */
  Command |= EEPROM_CMD_YE;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(40));               /* Wait for 40 us */
  Command &= ~EEPROM_CMD_YE;
  EEPROM->CMD = Command;
  Command &= ~EEPROM_CMD_PROG;
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
  Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
  EEPROM->CMD = Command;
  ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */

  EEPROM->CMD = Command & EEPROM_CMD_DELAY_Msk;
  EEPROM->KEY = 0;
}


/**
  * @brief  Erases all pages of the selected EEPROM memory bank.
  * @param  BankSelector: Selects EEPROM Bank (Main Bank or Information Bank).
  *         This parameter can be one of the following values:
  *           @arg EEPROM_Main_Bank_Select:      The EEPROM Main Bank selector.
  *           @arg EEPROM_All_Banks_Select:      The EEPROM All Banks selector.
  * @retval None
  */
__RAMFUNC void EEPROM_EraseAllPages(uint32_t BankSelector)
{
  uint32_t Command;
  uint32_t Offset;

  assert_param(IS_EEPROM_ERASE_SELECTOR(BankSelector));

  EEPROM->KEY = EEPROM_REG_ACCESS_KEY;
  Command = (EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON;
  Command |= (BankSelector == EEPROM_All_Banks_Select) ? EEPROM_CMD_IFREN : 0;

  EEPROM->CMD = Command;

  for (Offset = 0; Offset < (4 << 2); Offset += 4)
  {
    EEPROM->ADR = Offset;
    EEPROM->DI = 0;
    Command |= EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
    Command |= EEPROM_CMD_NVSTR;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(40000));            /* Wait for 40 ms */
    Command &= ~EEPROM_CMD_ERASE;
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(100));              /* Wait for 100 us */
    Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_NVSTR);
    EEPROM->CMD = Command;
    ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */
  }
  Command &= EEPROM_CMD_DELAY_Msk;
  EEPROM->CMD = Command;
  EEPROM->KEY = 0;
}


