/**
  ******************************************************************************
  * @file    system_MDR1986VE1T.c
  * @author  Andrey Sidorov
  * @version V1.2.0
  * @date    27/02/2013
  * @brief   CMSIS Cortex-M1 Device Peripheral Access Layer System Source File.
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
  * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
  ******************************************************************************
  * FILE system_MDR1986VE1T.c
  */


/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @addtogroup MDR1986VE1T MDR1986VE1T
 *  @{
 */

/** @defgroup MDR1986VE1T_System_ARM MDR1986VE1T System ARM
  * @{
  */

/** @addtogroup System_Private_Includes System Private Includes
  * @{
  */


/** @} */ /* End of group System_Private_Includes */

/** @defgroup __MDR1986VE1T_System_Private_Variables MDR1986VE1T System Private Variables
  * @{
  */
#include "1986VE1T.h" 

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
  uint32_t SystemCoreClock = (uint32_t)8000000;         /*!< System Clock Frequency (Core Clock)
                                                         *   default value */

/** @} */ /* End of group __MDR1986VE1T_System_Private_Variables */

/** @defgroup __MDR1986VE1T_System_Private_Functions MDR1986VE1T System Private Functions
  * @{
  */

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  * @note   None
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
	RST_CLK->PER_CLOCK |= (1<<4);				// RST_CLK clock enable
	RST_CLK->HS_CONTROL = (1<<0) | (0<<1) | (1<<2) | (0<<3);// HSE On, HSE2 on, Oscillator mode;
  while((RST_CLK->CLOCK_STATUS&0x0c)!=0x0c);	// Wait until HSE not ready
	RST_CLK->CPU_CLOCK = 0x00000002;			// CPU_C1 = HSE (12.288MHz)
	RST_CLK->PLL_CONTROL=(1<<2)|(3<<8);		// CPU PLL On, PLL_MULL = 8
	while((RST_CLK->CLOCK_STATUS&0x02)!=0x02);	// Wait until PLL not ready
	RST_CLK->PER_CLOCK |= (1<<3);				// EEPROM_CTRL clock enable
	EEPROM->CMD |= (3<<3);
	RST_CLK->PER_CLOCK&=(~0x08);				// EEPROM_CTRL clock disable
	RST_CLK->CPU_CLOCK = ((2 << 0)
                         | (1 << 2)
                         | (0 << 4)
                         | (1 << 8));
}

/**
  * @brief  Setup the microcontroller system
  *         RST clock configuration to the default reset state
  *         Setup SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
	/* Reset the RST clock configuration to the default reset state */

  /* Reset all clock but RST_CLK & BKP_CLC bits */
  RST_CLK->PER_CLOCK   = (uint32_t)0x8000010;

  /* Reset CPU_CLOCK bits */
  RST_CLK->CPU_CLOCK   &= (uint32_t)0x00000000;

  /* Reset PLL_CONTROL bits */
  RST_CLK->PLL_CONTROL &= (uint32_t)0x00000000;

  /* Reset HSEON and HSEBYP bits */
  RST_CLK->HS_CONTROL  &= (uint32_t)0x00000000;

  /* Reset USB_CLOCK bits */
  RST_CLK->USB_CLOCK   &= (uint32_t)0x00000000;

  /* Reset ADC_MCO_CLOCK bits */
  RST_CLK->ADC_MCO_CLOCK   &= (uint32_t)0x00000000;

  SystemCoreClockUpdate();
}

/** @} */ /* End of group __MDR1986VE1T_System_Private_Functions */

/** @} */ /* End of group MDR1986VE1T_System_ARM MDR1986VE1T System ARM */

/** @} */ /* End of group MDR1986VE1T MDR1986VE1T */

/** @} */ /* End of group __CMSIS */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE system_MDR1986VE1T.c */
