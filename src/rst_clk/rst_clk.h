#ifndef _RST_CLK_H
#define _RST_CLK_H
#include "main.h"

typedef struct
{
  uint32_t CPU_CLK_Frequency;
  uint32_t ADC_CLK_Frequency;
  uint32_t ADCIU_CLK_Frequency;
  uint32_t RTCHSI_Frequency;
  uint32_t RTCHSE_Frequency;
}RST_CLK_FreqTypeDef;

#define FLAG_MASK                   ((uint8_t)0x1F)
#define FLAG_SFR_MASK               ((uint8_t)0xE0)

#ifndef HSI_Value
/* Typical Value of the HSI in Hz */
 #define HSI_Value                  ((uint32_t)8000000)
#endif /* HSI_Value */

#ifndef HSE_Value
/* Typical Value of the HSE in Hz */
 #define HSE_Value                  ((uint32_t)8000000)
#endif /* HSE_Value */

#ifndef LSI_Value
/* Typical Value of the LSI in Hz */
 #define LSI_Value                  ((uint32_t)40000)
#endif /* LSI_Value */

#ifndef LSE_Value
/* Typical Value of the LSE in Hz */
 #define LSE_Value                  ((uint32_t)32768)
#endif /* LSE_Value */

#ifndef HSEonTimeOut
/* Time out for HSE start up */
 #define HSEonTimeOut               ((uint16_t)0x0600)
#endif /* HSEonTimeOut */

#ifndef LSEonTimeOut
/* Time out for LSE start up */
 #define LSEonTimeOut               ((uint16_t)0x0600)
#endif /* LSEonTimeOut */

#ifndef HSIonTimeOut
/* Time out for HSI start up */
 #define HSIonTimeOut               ((uint16_t)0x0600)
#endif /* HSIonTimeOut */

#ifndef LSIonTimeOut
/* Time out for LSI start up */
 #define LSIonTimeOut               ((uint16_t)0x0600)
#endif /* LSIonTimeOut */

#ifndef PLLCPUonTimeOut
/* Time out for PLLCPU start up */
 #define PLLCPUonTimeOut            ((uint16_t)0x0600)
#endif /* PLLCPUonTimeOut */


#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos                   0
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos                   2
#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos                   4
#define RST_CLK_CPU_CLOCK_HCLK_SEL_Pos                     8

/* Bit field masks: */
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk                   ((uint32_t)0x00000003)
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL                       ((uint32_t)0x00000004)
#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk                   ((uint32_t)0x000000F0)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_Msk                     ((uint32_t)0x00000300)

/* Bit field positions: */
#define RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Pos               0
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_C1_SEL_Pos             2
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_C3_SEL_Pos             4
#define RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Pos               8
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_CLK_EN_Pos             12
#define RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN_Pos               13

/* Bit field masks: */
#define RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Msk               ((uint32_t)0x00000003)
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_C1_SEL_Msk             ((uint32_t)0x0000000C)
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_C3_SEL_Msk             ((uint32_t)0x000000F0)
#define RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Msk               ((uint32_t)0x00000F00)
#define RST_CLK_ADC_MCO_CLOCK_ADCIU_CLK_EN                 ((uint32_t)0x00001000)
#define RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN                   ((uint32_t)0x00002000)

/* Bit field positions: */
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON_Pos                 2
#define RST_CLK_PLL_CONTROL_PLL_CPU_PLD_Pos                3
#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos                8

/* Bit field masks: */
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON                     ((uint32_t)0x00000004)
#define RST_CLK_PLL_CONTROL_PLL_CPU_PLD                    ((uint32_t)0x00000008)
#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk                ((uint32_t)0x00000F00)

/* Bit field positions: */
#define RST_CLK_RTC_CLOCK_HSE_SEL_Pos                      0
#define RST_CLK_RTC_CLOCK_HSI_SEL_Pos                      4
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN_Pos                   8
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN_Pos                   9

/* Bit field masks: */
#define RST_CLK_RTC_CLOCK_HSE_SEL_Msk                      ((uint32_t)0x0000000F)
#define RST_CLK_RTC_CLOCK_HSI_SEL_Msk                      ((uint32_t)0x000000F0)
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN                       ((uint32_t)0x00000100)
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN                       ((uint32_t)0x00000200)


#define RST_CLK_HSE_OFF                      ((uint32_t)0x00000000)
#define RST_CLK_HSE_ON                       ((uint32_t)0x00000001)
#define RST_CLK_HSE_Bypass                   ((uint32_t)0x00000002)

#define IS_RST_CLK_HSE(HSE)                  (((HSE) == RST_CLK_HSE_OFF) || \
                                              ((HSE) == RST_CLK_HSE_ON)  || \
                                              ((HSE) == RST_CLK_HSE_Bypass))

/** @} */ /* End of group HSE_configuration */

/** @defgroup LSE_configuration LSE configuration
  * @{
  */

/**
  * @brief RST_CLK LSE (Low Speed External) clock mode and source selection constants
  */

#define RST_CLK_LSE_OFF                      ((uint32_t)0x00000000)
#define RST_CLK_LSE_ON                       ((uint32_t)0x00000001)
#define RST_CLK_LSE_Bypass                   ((uint32_t)0x00000002)

#define IS_RST_CLK_LSE(LSE)                  (((LSE) == RST_CLK_LSE_OFF) || \
                                              ((LSE) == RST_CLK_LSE_ON)  || \
                                              ((LSE) == RST_CLK_LSE_Bypass))

/** @} */ /* End of group LSE_configuration */

/** @defgroup CPU_PLL_entry_clock_source CPU PLL entry clock source
  * @{
  */

/**
  * @brief RST_CLK CPU_PLL clock mode and source selection constants
  */

#define RST_CLK_CPU_PLLsrcHSIdiv1           ((uint32_t)0x00000000)
#define RST_CLK_CPU_PLLsrcHSIdiv2           ((uint32_t)0x00000001)
#define RST_CLK_CPU_PLLsrcHSEdiv1           ((uint32_t)0x00000002)
#define RST_CLK_CPU_PLLsrcHSEdiv2           ((uint32_t)0x00000003)

#define IS_RST_CLK_CPU_PLL_SOURCE(SRC)      (((SRC) == RST_CLK_CPU_PLLsrcHSIdiv1) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSIdiv2) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSEdiv1) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSEdiv2))

/** @} */ /* End of group CPU_PLL_entry_clock_source */

/** @defgroup CPU_PLL_clock_multiplier CPU_PLL clock multiplier
  * @{
  */

/**
  * @brief RST_CLK PLL_CPU_MUL multiplier of the CPU_C1 clock constants
  */

#define RST_CLK_CPU_PLLmul1                     ((uint32_t)0x00000000)
#define RST_CLK_CPU_PLLmul2                     ((uint32_t)0x00000001)
#define RST_CLK_CPU_PLLmul3                     ((uint32_t)0x00000002)
#define RST_CLK_CPU_PLLmul4                     ((uint32_t)0x00000003)
#define RST_CLK_CPU_PLLmul5                     ((uint32_t)0x00000004)
#define RST_CLK_CPU_PLLmul6                     ((uint32_t)0x00000005)
#define RST_CLK_CPU_PLLmul7                     ((uint32_t)0x00000006)
#define RST_CLK_CPU_PLLmul8                     ((uint32_t)0x00000007)
#define RST_CLK_CPU_PLLmul9                     ((uint32_t)0x00000008)
#define RST_CLK_CPU_PLLmul10                    ((uint32_t)0x00000009)
#define RST_CLK_CPU_PLLmul11                    ((uint32_t)0x0000000A)
#define RST_CLK_CPU_PLLmul12                    ((uint32_t)0x0000000B)
#define RST_CLK_CPU_PLLmul13                    ((uint32_t)0x0000000C)
#define RST_CLK_CPU_PLLmul14                    ((uint32_t)0x0000000D)
#define RST_CLK_CPU_PLLmul15                    ((uint32_t)0x0000000E)
#define RST_CLK_CPU_PLLmul16                    ((uint32_t)0x0000000F)

#define IS_RST_CLK_CPU_PLL_MUL(SRC)             (SRC < 16)


/** @} */ /* End of group CPU_PLL_clock_multiplier */

/** @defgroup CPU_CLK_divider CPU CLK divider
  * @{
  */

/**
  * @brief RST_CLK CPU_PLL output clock CPU_CLK_DIV divider constants
  */

#define RST_CLK_CPUclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_CPUclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_CPUclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_CPUclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_CPUclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_CPUclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_CPUclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_CPUclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_CPUclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_CPUclkDIV(DIV)             (((DIV) == RST_CLK_CPUclkDIV1)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV2)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV4)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV8)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV16)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV32)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV64)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV128) || \
                                               ((DIV) == RST_CLK_CPUclkDIV256))

/** @} */ /* End of group CPU_CLK_divider */

/** @defgroup CPU_CLK_selector CPU CLK selector
  * @{
  */

/**
  * @brief RST_CLK CPU_CLK source CPU_CLK selector constants
  */

#define RST_CLK_CPUclkHSI                     ((uint32_t)0x00000000)
#define RST_CLK_CPUclkCPU_C3                  ((uint32_t)0x00000100)
#define RST_CLK_CPUclkLSE                     ((uint32_t)0x00000200)
#define RST_CLK_CPUclkLSI                     ((uint32_t)0x00000300)

#define IS_RST_CPU_CLK(SRC)                   (((SRC) == RST_CLK_CPUclkHSI)    || \
                                               ((SRC) == RST_CLK_CPUclkCPU_C3) || \
                                               ((SRC) == RST_CLK_CPUclkLSE)    || \
                                               ((SRC) == RST_CLK_CPUclkLSI))

/** @} */ /* End of group CPU_CLK_selector */

/** @defgroup ADC_MCO_CLOCK_source ADC clock source
  * @{
  */

/**
  * @brief RST_CLK ADC_CLK selector constants
  */
#define RST_CLK_ADCclkCPU_C1                  ((uint32_t)0x00000000)
#define RST_CLK_ADCclkPER1_C1                 ((uint32_t)0x00000001)
#define RST_CLK_ADCclkPLLCPU                  ((uint32_t)0x00000002)
#define RST_CLK_ADCclkHSI_CLK                 ((uint32_t)0x00000003)


#define IS_RST_CLK_ADCclk(SRC)                (((SRC) == RST_CLK_ADCclkCPU_C1)  || \
                                               ((SRC) == RST_CLK_ADCclkPER1_C1) || \
                                               ((SRC) == RST_CLK_ADCclkPLLCPU)  || \
                                               ((SRC) == RST_CLK_ADCclkHSI_CLK))
/** @} */ /* End of group ADC_MCO_CLOCK_source */

/** @defgroup ADC_MCO_CS3_SEL ADC clock divider
  * @{
  */

/**
  * @brief RST_CLK ADC_CS2_SEL output clock ADC_CS3_SEL divider constants
  */

#define RST_CLK_ADCclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_ADCclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_ADCclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_ADCclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_ADCclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_ADCclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_ADCclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_ADCclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_ADCclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_ADCclkDivValue(SRC)        (((SRC) == RST_CLK_ADCclkDIV1)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV2)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV4)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV8)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV16)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV32)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV64)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV128)  || \
                                               ((SRC) == RST_CLK_ADCclkDIV256))

/** @} */ /* End of group ADC_MCO_CS3_SEL */

/** @defgroup ADCIU_MCO_CLOCK_source ADCIU clock source
 *  @{
 */

/**
 * @brief RST_CLK ADCIU_CLK selector constants
 */
#define RST_CLK_ADCIUclkCPU_C1						((uint32_t)0x00000000)
#define RST_CLK_ADCIUclkPER1_C1						((uint32_t)0x00000004)
#define RST_CLK_ADCIUclkPLLCPU						((uint32_t)0x00000008)
#define RST_CLK_ADCIUclkHSI_CLK						((uint32_t)0x0000000C)

#define IS_RST_CLK_ADCIUclk(SRC)					 (((SRC) == RST_CLK_ADCIUclkCPU_C1) || \
													  ((SRC) == RST_CLK_ADCIUclkPER1_C1) || \
													  ((SRC) == RST_CLK_ADCIUclkPLLCPU)  || \
													  ((SRC) == RST_CLK_ADCIUclkHSI_CLK))
/** @} */ /* End of group ADCIU_MCO_CLOCK_source */

/** @defgroup ADCIUclkDIV_divider ADCIU MCO divider
 *	@{
 */

 /**
  * @brief ADCIU_MCO_CLK ADCIU_CLK output clock ADCIU_CLK_DIV divider
  */
#define RST_CLK_ADCIUclkDIV1						((uint32_t)0x00000000)
#define RST_CLK_ADCIUclkDIV2						((uint32_t)0x00000080)
#define RST_CLK_ADCIUclkDIV4						((uint32_t)0x00000090)
#define RST_CLK_ADCIUclkDIV8						((uint32_t)0x000000A0)
#define RST_CLK_ADCIUclkDIV16						((uint32_t)0x000000B0)
#define RST_CLK_ADCIUclkDIV32						((uint32_t)0x000000C0)
#define RST_CLK_ADCIUclkDIV64						((uint32_t)0x000000D0)
#define RST_CLK_ADCIUclkDIV128						((uint32_t)0x000000E0)
#define RST_CLK_ADCIUclkDIV256						((uint32_t)0x000000F0)

#define IS_RST_CLK_ADCIUclkDIV(DIV)					(((DIV) == RST_CLK_ADCIUclkDIV1)   || \
													 ((DIV) == RST_CLK_ADCIUclkDIV2)   || \
													 ((DIV) == RST_CLK_ADCIUclkDIV4)   || \
													 ((DIV) == RST_CLK_ADCIUclkDIV8)   || \
													 ((DIV) == RST_CLK_ADCIUclkDIV16)  || \
													 ((DIV) == RST_CLK_ADCIUclkDIV32)  || \
													 ((DIV) == RST_CLK_ADCIUclkDIV64)  || \
													 ((DIV) == RST_CLK_ADCIUclkDIV128) || \
													 ((DIV) == RST_CLK_ADCIUclkDIV256))
/** @} */ /* End of group ADCIUclkDIV_divider */


/** @defgroup CLK_peripheral CLK peripheral
  * @{
  */

/**
  * @brief RST_CLK peripheral modules clock constants
  */

#define PCLK_BIT(BASE)              ((uint32_t)(1 << ((((uint32_t)BASE) >> 15) & 0x1F)))

#define RST_CLK_PCLK_SSP1			PCLK_BIT(MDR_SSP1_BASE)
#define RST_CLK_PCLK_UART1			PCLK_BIT(MDR_UART1_BASE)
#define RST_CLK_PCLK_UART2			PCLK_BIT(MDR_UART2_BASE)
#define RST_CLK_PCLK_EEPROM			PCLK_BIT(MDR_EEPROM_BASE)
#define RST_CLK_PCLK_RST_CLK		PCLK_BIT(MDR_RST_CLK_BASE)
#define RST_CLK_PCLK_DMA			PCLK_BIT(MDR_DMA_BASE)
#define RST_CLK_PCLK_COMP			PCLK_BIT(MDR_COMP_BASE)
#define RST_CLK_PCLK_DAC			PCLK_BIT(MDR_DAC_BASE)
#define RST_CLK_PCLK_ADC			PCLK_BIT(MDR_ADC_BASE)
#define RST_CLK_PCLK_WWDG			PCLK_BIT(MDR_WWDG_BASE)
#define RST_CLK_PCLK_IWDG			PCLK_BIT(MDR_IWDG_BASE)
#define RST_CLK_PCLK_POWER			PCLK_BIT(MDR_POWER_BASE)
#define RST_CLK_PCLK_BKP			PCLK_BIT(MDR_BKP_BASE)
#define RST_CLK_PCLK_ADCUI			PCLK_BIT(MDR_ADCIU_BASE)
#define RST_CLK_PCLK_TIMER1			PCLK_BIT(MDR_TIMER1_BASE)
#define RST_CLK_PCLK_TIMER2			PCLK_BIT(MDR_TIMER2_BASE)
#define RST_CLK_PCLK_PORTA			PCLK_BIT(MDR_PORTA_BASE)
#define RST_CLK_PCLK_PORTB			PCLK_BIT(MDR_PORTB_BASE)
#define RST_CLK_PCLK_PORTC			PCLK_BIT(MDR_PORTC_BASE)
#define RST_CLK_PCLK_CRC			PCLK_BIT(MDR_CRC_BASE)

#define RST_CLK_PCLK_MASK			(RST_CLK_PCLK_SSP1 		| RST_CLK_PCLK_UART1 	|\
									 RST_CLK_PCLK_UART2 	| RST_CLK_PCLK_EEPROM 	|\
									 RST_CLK_PCLK_RST_CLK 	| RST_CLK_PCLK_DMA	 	|\
									 RST_CLK_PCLK_COMP 		| RST_CLK_PCLK_DAC 		|\
									 RST_CLK_PCLK_ADC 		| RST_CLK_PCLK_WWDG 	|\
									 RST_CLK_PCLK_IWDG 		| RST_CLK_PCLK_POWER 	|\
									 RST_CLK_PCLK_BKP 		| RST_CLK_PCLK_ADCUI 	|\
									 RST_CLK_PCLK_TIMER1 	| RST_CLK_PCLK_TIMER2 	|\
									 RST_CLK_PCLK_PORTA 	| RST_CLK_PCLK_PORTB 	|\
									 RST_CLK_PCLK_PORTC 	| RST_CLK_PCLK_CRC	)


#define IS_RST_CLK_PCLK(PCLK)       ((PCLK & RST_CLK_PCLK_MASK) == PCLK)

/** @} */ /* End of group CLK_peripheral */

/** @defgroup RST_CLK_PER1_CLK1_CLK_SRC RST_CLK_PER1_CLK1 CLK_SRC
  * @{
  */

#define RST_CLK_PER1_C1_CLK_SRC_LSI				((uint32_t)0x00000000)
#define RST_CLK_PER1_C1_CLK_SRC_LSI_2			((uint32_t)0x00000001)
#define RST_CLK_PER1_C1_CLK_SRC_LSE				((uint32_t)0x00000002)
#define RST_CLK_PER1_C1_CLK_SRC_LSE_2			((uint32_t)0x00000003)

#define IS_RST_CLK_PER1_C1_CLK_SRC(CLK_SRC)		((CLK_SRC == RST_CLK_PER1_C1_CLK_SRC_LSI) ||\
												 (CLK_SRC == RST_CLK_PER1_C1_CLK_SRC_LSI_2)||\
												 (CLK_SRC == RST_CLK_PER1_C1_CLK_SRC_LSE)	||\
												 (CLK_SRC == RST_CLK_PER1_C1_CLK_SRC_LSE_2))

/** @} */ /* End of group RST_CLK_PER1_CLK1_CLK_SRC */

/** @defgroup RST_CLK_PER1_C2_CLK_SRC RST_CLK_PER1_C2 CLK_SRC
  * @{
  */

#define RST_CLK_PER1_C2_CLK_SRC_CPU_C1				((uint32_t)0x00000000)
#define RST_CLK_PER1_C2_CLK_SRC_PER1_C1				((uint32_t)0x00000004)
#define RST_CLK_PER1_C2_CLK_SRC_PLLCPU				((uint32_t)0x00000008)
#define RST_CLK_PER1_C2_CLK_SRC_HSI_CLK				((uint32_t)0x0000000C)

#define IS_RST_CLK_PER1_C2_CLK_SRC(CLK_SRC)			((CLK_SRC == RST_CLK_PER1_C2_CLK_SRC_CPU_C1) ||\
													 (CLK_SRC == RST_CLK_PER1_C2_CLK_SRC_PER1_C1)||\
													 (CLK_SRC == RST_CLK_PER1_C2_CLK_SRC_PLLCPU) ||\
													 (CLK_SRC == RST_CLK_PER1_C2_CLK_SRC_HSI_CLK))

/** @} */ /* End of group RST_CLK_PER1_C2_CLK_SRC */

/** @defgroup RST_CLK_Flag RST_CLK Flag
  * @{
  */

/**
  * @brief RST_CLK flag identifiers
  */

#define RST_CLK_FLAG_HSIRDY                   ((uint32_t)(0x00 | 23))
#define RST_CLK_FLAG_LSIRDY                   ((uint32_t)(0x00 | 21))
#define RST_CLK_FLAG_HSERDY                   ((uint32_t)(0x20 |  2))
#define RST_CLK_FLAG_HSE2RDY	           	  ((uint32_t)(0x20 |  3))
#define RST_CLK_FLAG_LSERDY                   ((uint32_t)(0x00 | 13))
#define RST_CLK_FLAG_PLLCPURDY                ((uint32_t)(0x20 |  1))

#define IS_RST_CLK_FLAG(FLAG)                 (((FLAG) == RST_CLK_FLAG_HSIRDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_LSIRDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_HSERDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_HSE2RDY)	  || \
                                               ((FLAG) == RST_CLK_FLAG_LSERDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_PLLCPURDY))

/** @} */ /* End of group RST_CLK_Flag */

#define IS_RCC_CLK_HSI_TRIM_VALUE(TRIM)       ((TRIM) <= 0x3F)
#define IS_RCC_CLK_LSI_TRIM_VALUE(TRIM)       ((TRIM) <= 0x1F)

/** @defgroup RST_CLK_HSI_C1_SEL HSI clock divider
  * @{
  */

/**
  * @brief RST_CLK HSI clock HSI_C1_SEL divider constants
  */

#define RST_CLK_HSIclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_HSIclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_HSIclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_HSIclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_HSIclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_HSIclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_HSIclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_HSIclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_HSIclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_HSIclkDivValue(SRC)        (((SRC) == RST_CLK_HSIclkDIV1)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV2)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV4)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV8)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV16)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV32)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV64)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV128)  || \
                                               ((SRC) == RST_CLK_HSIclkDIV256))

/** @} */ /* End of group RST_CLK_HSI_C1_SEL */

/** @defgroup RST_CLK_HSE_C1_SEL HSE clock divider
  * @{
  */

/**
  * @brief RST_CLK HSE clock HSE_C1_SEL divider constants
  */
#define RST_CLK_HSEclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_HSEclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_HSEclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_HSEclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_HSEclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_HSEclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_HSEclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_HSEclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_HSEclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_HSEclkDivValue(SRC)        (((SRC) == RST_CLK_HSEclkDIV1)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV2)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV4)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV8)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV16)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV32)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV64)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV128)  || \
                                               ((SRC) == RST_CLK_HSEclkDIV256))
void RST_CLK_GetClocksFreq(RST_CLK_FreqTypeDef* RST_CLK_Clocks);													
#endif
