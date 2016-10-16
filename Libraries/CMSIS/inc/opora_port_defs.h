/**
  ******************************************************************************
  * @file    opora_port_defs.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date
  * @brief   This file contains all the Special Function Registers definitions
  *          for the PORT peripheral unit used in the Milandr OPORA
  *          microcontrollers.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  * FILE opora_port_defs.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OPORA_PORT_DEFS_H
#define __OPORA_PORT_DEFS_H


typedef struct {
  __IO uint32_t RXTX;
  __IO uint32_t OE;
  __IO uint32_t FUNC;
  __IO uint32_t ANALOG;
  __IO uint32_t PULL;
  __IO uint32_t PD;
  __IO uint32_t PWR;
  __IO uint32_t GFEN;
  __IO uint32_t SETTX;
  __IO uint32_t CLRTX;
  __IO uint32_t RDTX;
} PORT_TypeDef;

#define _PORT_BIT_ACTION(ACTION) (((ACTION) == RESET) || ((ACTION) == SET))

#define _PORT_ALL_PERIPH(PERIPH) (((PERIPH) == PORTA) || \
                                    ((PERIPH) == PORTB) || \
                                    ((PERIPH) == PORTC) || \
                                    ((PERIPH) == PORTD) || \
                                    ((PERIPH) == PORTE) || \
                                    ((PERIPH) == PORTF))

#define PORT_Pin_0                  0x0001U  /*!< Pin 0 selected */
#define PORT_Pin_1                  0x0002U  /*!< Pin 1 selected */
#define PORT_Pin_2                  0x0004U  /*!< Pin 2 selected */
#define PORT_Pin_3                  0x0008U  /*!< Pin 3 selected */
#define PORT_Pin_4                  0x0010U  /*!< Pin 4 selected */
#define PORT_Pin_5                  0x0020U  /*!< Pin 5 selected */
#define PORT_Pin_6                  0x0040U  /*!< Pin 6 selected */
#define PORT_Pin_7                  0x0080U  /*!< Pin 7 selected */
#define PORT_Pin_8                  0x0100U  /*!< Pin 8 selected */
#define PORT_Pin_9                  0x0200U  /*!< Pin 9 selected */
#define PORT_Pin_10                 0x0400U  /*!< Pin 10 selected */
#define PORT_Pin_11                 0x0800U  /*!< Pin 11 selected */
#define PORT_Pin_12                 0x1000U  /*!< Pin 12 selected */
#define PORT_Pin_13                 0x2000U  /*!< Pin 13 selected */
#define PORT_Pin_14                 0x4000U  /*!< Pin 14 selected */
#define PORT_Pin_15                 0x8000U  /*!< Pin 15 selected */
#define PORT_Pin_All                0xFFFFU  /*!< All pins selected */

#define _PORT_PIN(PIN)            ((((PIN) & (uint32_t)0xFFFF0000UL) == 0x00) && \
                                     ((PIN) != 0x00))

#define _GET_PORT_PIN(PIN)        (((PIN) == PORT_Pin_0 ) || \
                                     ((PIN) == PORT_Pin_1 ) || \
                                     ((PIN) == PORT_Pin_2 ) || \
                                     ((PIN) == PORT_Pin_3 ) || \
                                     ((PIN) == PORT_Pin_4 ) || \
                                     ((PIN) == PORT_Pin_5 ) || \
                                     ((PIN) == PORT_Pin_6 ) || \
                                     ((PIN) == PORT_Pin_7 ) || \
                                     ((PIN) == PORT_Pin_8 ) || \
                                     ((PIN) == PORT_Pin_9 ) || \
                                     ((PIN) == PORT_Pin_10) || \
                                     ((PIN) == PORT_Pin_11) || \
                                     ((PIN) == PORT_Pin_12) || \
                                     ((PIN) == PORT_Pin_13) || \
                                     ((PIN) == PORT_Pin_14) || \
                                     ((PIN) == PORT_Pin_15))

/** @defgroup Periph_PORT_PORT_FUNC_Bits PORT_FUNC
  * @{
  */

#define PORT_FUNC_MODE0_OFFS                    0
#define PORT_FUNC_MODE0_MASK                    ((uint32_t)0x00000003)

#define PORT_FUNC_MODE1_OFFS                    2
#define PORT_FUNC_MODE1_MASK                    ((uint32_t)0x0000000C)

#define PORT_FUNC_MODE2_OFFS                    4
#define PORT_FUNC_MODE2_MASK                    ((uint32_t)0x00000030)

#define PORT_FUNC_MODE3_OFFS                    6
#define PORT_FUNC_MODE3_MASK                    ((uint32_t)0x000000C0)

#define PORT_FUNC_MODE4_OFFS                    8
#define PORT_FUNC_MODE4_MASK                    ((uint32_t)0x00000300)

#define PORT_FUNC_MODE5_OFFS                    10
#define PORT_FUNC_MODE5_MASK                    ((uint32_t)0x00000C00)

#define PORT_FUNC_MODE6_OFFS                    12
#define PORT_FUNC_MODE6_MASK                    ((uint32_t)0x00003000)

#define PORT_FUNC_MODE7_OFFS                    14
#define PORT_FUNC_MODE7_MASK                    ((uint32_t)0x0000C000)

#define PORT_FUNC_MODE8_OFFS                    16
#define PORT_FUNC_MODE8_MASK                    ((uint32_t)0x00030000)

#define PORT_FUNC_MODE9_OFFS                    18
#define PORT_FUNC_MODE9_MASK                    ((uint32_t)0x000C0000)

#define PORT_FUNC_MODE10_OFFS                   20
#define PORT_FUNC_MODE10_MASK                   ((uint32_t)0x00300000)

#define PORT_FUNC_MODE11_OFFS                   22
#define PORT_FUNC_MODE11_MASK                   ((uint32_t)0x00C00000)

#define PORT_FUNC_MODE12_OFFS                   24
#define PORT_FUNC_MODE12_MASK                   ((uint32_t)0x03000000)

#define PORT_FUNC_MODE13_OFFS                   26
#define PORT_FUNC_MODE13_MASK                   ((uint32_t)0x0C000000)

#define PORT_FUNC_MODE14_OFFS                   28
#define PORT_FUNC_MODE14_MASK                   ((uint32_t)0x30000000)

#define PORT_FUNC_MODE15_OFFS                   30
#define PORT_FUNC_MODE15_MASK                   ((uint32_t)0xC0000000)

/* @defgroup Periph_PORT_PORT_OE_Bits PORT_OE
  * @{
  */
#define PORT_OE_OE0_OFFS						0
#define PORT_OE_OE1_OFFS						1
#define PORT_OE_OE2_OFFS						2
#define PORT_OE_OE3_OFFS						3
#define PORT_OE_OE4_OFFS						4
#define PORT_OE_OE5_OFFS						5
#define PORT_OE_OE6_OFFS						6
#define PORT_OE_OE7_OFFS						7
#define PORT_OE_OE8_OFFS						8
#define PORT_OE_OE9_OFFS						9
#define PORT_OE_OE10_OFFS						10
#define PORT_OE_OE11_OFFS						11
#define PORT_OE_OE12_OFFS						12
#define PORT_OE_OE13_OFFS						13
#define PORT_OE_OE14_OFFS						14
#define PORT_OE_OE15_OFFS						15

/* @defgroup Periph_PORT_PORT_ANALOG_Bits PORT_ANALOG
  * @{
  */
#define PORT_ANALOG_EN0_OFFS					0
#define PORT_ANALOG_EN1_OFFS					1
#define PORT_ANALOG_EN2_OFFS					2
#define PORT_ANALOG_EN3_OFFS					3
#define	PORT_ANALOG_EN4_OFFS					4
#define PORT_ANALOG_EN5_OFFS					5
#define PORT_ANALOG_EN6_OFFS					6
#define PORT_ANALOG_EN7_OFFS					7
#define PORT_ANALOG_EN8_OFFS					8
#define PORT_ANALOG_EN9_OFFS					9
#define PORT_ANALOG_EN10_OFFS					10
#define PORT_ANALOG_EN11_OFFS					11
#define PORT_ANALOG_EN12_OFFS					12
#define PORT_ANALOG_EN13_OFFS					13
#define PORT_ANALOG_EN14_OFFS					14
#define PORT_ANALOG_EN15_OFFS					15

/** @defgroup Periph_PORT_PORT_PWR_Bits PORT_PWR
  * @{
  */

#define PORT_PWR_PWR0_OFFS                      0
#define PORT_PWR_PWR0_MASK                      ((uint32_t)0x00000003)

#define PORT_PWR_PWR1_OFFS                      2
#define PORT_PWR_PWR1_MASK                      ((uint32_t)0x0000000C)

#define PORT_PWR_PWR2_OFFS                      4
#define PORT_PWR_PWR2_MASK                      ((uint32_t)0x00000030)

#define PORT_PWR_PWR3_OFFS                      6
#define PORT_PWR_PWR3_MASK                      ((uint32_t)0x000000C0)

#define PORT_PWR_PWR4_OFFS                      8
#define PORT_PWR_PWR4_MASK                      ((uint32_t)0x00000300)

#define PORT_PWR_PWR5_OFFS                      10
#define PORT_PWR_PWR5_MASK                      ((uint32_t)0x00000C00)

#define PORT_PWR_PWR6_OFFS                      12
#define PORT_PWR_PWR6_MASK                      ((uint32_t)0x00003000)

#define PORT_PWR_PWR7_OFFS                      14
#define PORT_PWR_PWR7_MASK                      ((uint32_t)0x0000C000)

#define PORT_PWR_PWR8_OFFS                      16
#define PORT_PWR_PWR8_MASK                      ((uint32_t)0x00030000)

#define PORT_PWR_PWR9_OFFS                      18
#define PORT_PWR_PWR9_MASK                      ((uint32_t)0x000C0000)

#define PORT_PWR_PWR10_OFFS                     20
#define PORT_PWR_PWR10_MASK                     ((uint32_t)0x00300000)

#define PORT_PWR_PWR11_OFFS                     22
#define PORT_PWR_PWR11_MASK                     ((uint32_t)0x00C00000)

#define PORT_PWR_PWR12_OFFS                     24
#define PORT_PWR_PWR12_MASK                     ((uint32_t)0x03000000)

#define PORT_PWR_PWR13_OFFS                     26
#define PORT_PWR_PWR13_MASK                     ((uint32_t)0x0C000000)

#define PORT_PWR_PWR14_OFFS                     28
#define PORT_PWR_PWR14_MASK                     ((uint32_t)0x30000000)

#define PORT_PWR_PWR15_OFFS                     30
#define PORT_PWR_PWR15_MASK                     ((uint32_t)0xC0000000)


/** @defgroup Periph_PORT_PORT_PD_Bits PORT_PD
  * @{
  */
#define PORT_PD_PD0_OFFS						0
#define PORT_PD_PD1_OFFS						1
#define PORT_PD_PD2_OFFS						2
#define PORT_PD_PD3_OFFS						3
#define PORT_PD_PD4_OFFS						4
#define PORT_PD_PD5_OFFS						5
#define PORT_PD_PD6_OFFS						6
#define PORT_PD_PD7_OFFS						7
#define PORT_PD_PD8_OFFS						8
#define PORT_PD_PD9_OFFS						9
#define PORT_PD_PD10_OFFS						10
#define PORT_PD_PD11_OFFS						11
#define PORT_PD_PD12_OFFS						12
#define PORT_PD_PD13_OFFS						13
#define PORT_PD_PD14_OFFS						14
#define PORT_PD_PD15_OFFS						1



#define OE_IN									0x0
#define OE_IN_ALL								0x0000
#define OE_OUT									0x1
#define OE_OUT_ALL								0xFFFF

#define fPORT									0x0
#define fPORT_ALL								0x00000000
#define fMAIN									0x1
#define fMAIN_ALL								0x55555555
#define fALTER									0x2
#define fALTER_ALL								0xAAAAAAAA
#define fOVERRID 								0x3
#define fOVERRID_ALL							0xFFFFFFFF

#define mANALOG									0x0
#define mANALOG_ALL								0x0000
#define mDIGITAL								0x1
#define mDIGITAL_ALL							0xFFFF

#define sOUTPUT_OFF 							0x0
#define sOUTPUT_OFF_ALL							0x00000000
#define sSLOW      								0x1
#define sSLOW_ALL								0x55555555
#define sFAST									0x2
#define sFAST_ALL								0xAAAAAAAA
#define sMAXFAST 								0x3
#define sMAXFAST_ALL							0xFFFFFFFF


void vPORT_WriteBit(PORT_TypeDef*, uint32_t, FlagStatus);
uint8_t vPORT_ReadBit(PORT_TypeDef*, uint32_t);
#endif /* __OPORA_PORT_DEFS_H */

