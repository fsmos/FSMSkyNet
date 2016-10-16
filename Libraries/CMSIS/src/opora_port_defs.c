#include "1986VE1T.h"

void vPORT_WriteBit(PORT_TypeDef* PORTx, uint32_t PORT_Pin, FlagStatus BitVal)
{
  	uint32_t portdata;
  	/* Check the parameters */
  	assert_param(_PORT_ALL_PERIPH(PORTx));
  	assert_param(_GET_PORT_PIN(PORT_Pin));
  	assert_param(_PORT_BIT_ACTION(BitVal));
 	portdata = PORTx->RXTX;
  	if (BitVal != RESET)
  	{
   		PORTx->RXTX = portdata | PORT_Pin;
 	}
  	else
  	{
    	PORTx->RXTX = portdata & (~PORT_Pin);
  	}
}

uint8_t vPORT_ReadBit(PORT_TypeDef* PORTx, uint32_t PORT_Pin)
{
  	uint8_t bitstatus;
	/* Check the parameters */
  	assert_param(_PORT_ALL_PERIPH(PORTx));
  	assert_param(_GET_PORT_PIN(PORT_Pin));
	if ((PORTx->RXTX & PORT_Pin) != RESET)
  	{
    	bitstatus = (uint8_t)SET;
  	}
 	else
  	{
    	bitstatus = (uint8_t)RESET;
  	}
  	return bitstatus;
}
