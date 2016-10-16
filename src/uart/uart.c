#include "uart.h"
#include "rst_clk.h"

void UART_Init ( UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct )
{
	uint32_t tmpreg, cpuclock;
	uint32_t realspeed, speederror;
	uint32_t divider;
	uint32_t integerdivider;
	uint32_t fractionaldivider;
	RST_CLK_FreqTypeDef RST_CLK_Clocks;

	/* Configure the UART Baud Rate */
	RST_CLK_GetClocksFreq(&RST_CLK_Clocks);
	
	cpuclock = RST_CLK_Clocks.CPU_CLK_Frequency;

	tmpreg = RST_CLK->UART_CLOCK;

	if (UARTx == UART1) {
		cpuclock /= (1 << (tmpreg & UART1_BRG_Mask));
	}
	else
	if (UARTx == UART2) {
		cpuclock /= (1 << ((tmpreg & UART2_BRG_Mask) >> UART2_BRG_Offs));
	}

	/* Determine the integer part */
	divider = cpuclock / (UART_InitStruct->UART_BaudRate >> 2);
	integerdivider = divider >> 6;
	/* Determine the fractional part */
	fractionaldivider = (divider & FBRD_Fract_Mask);
	/* Determine the speed error */
	realspeed = (cpuclock * 4) / ((integerdivider * 64) + fractionaldivider);
	speederror = ((realspeed - UART_InitStruct->UART_BaudRate) * 128)
			/ UART_InitStruct->UART_BaudRate;
	if (speederror > 2) {
		return;
	}
	/* Write UART Baud Rate */
	UARTx->IBRD = integerdivider;
	UARTx->FBRD = fractionaldivider;

	/* UART LCR_H configuration */
	/* Set the WLEN bits according to UART_WordLength value */
	/* Set STP2 bit according to UART_StopBits value */
	/* Set PEN, EPS and SPS bits according to UART_Parity value */
	/* Set FEN bit according to UART_FIFOMode value */
	tmpreg = UARTx->LCR_H;
	tmpreg |= UART_InitStruct->UART_WordLength | UART_InitStruct->UART_StopBits
			| UART_InitStruct->UART_Parity | UART_InitStruct->UART_FIFOMode;
	UARTx->LCR_H = tmpreg;

	/* UART CR configuration */
	tmpreg = UARTx->CR;
	/* Clear UART CR Flow control bits */
	tmpreg &= ~CR_FC_Mask;
	/* Set UART CR Flow control bits */
	tmpreg |= UART_InitStruct->UART_HardwareFlowControl;
	/* Write to UART CR */
	UARTx->CR = tmpreg;
}

void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_BaudRate = 9600;
  UART_InitStruct->UART_WordLength = UART_WordLength8b;
  UART_InitStruct->UART_StopBits = UART_StopBits1;
  UART_InitStruct->UART_Parity = UART_Parity_No;
  UART_InitStruct->UART_FIFOMode = UART_FIFO_OFF;
  UART_InitStruct->UART_HardwareFlowControl = 0;
}

void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the UARTEN bit in the CR register */
    UARTx->CR |= CR_EN_Set;
  }
  else
  {
    /* Disable the selected UART by clearing the UARTEN bit in the CR register */
    UARTx->CR &= CR_EN_Reset;
  }
}

void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    UARTx->IMSC |= UART_IT;
  }
  else
  {
    UARTx->IMSC &= ~UART_IT;
  }
}
