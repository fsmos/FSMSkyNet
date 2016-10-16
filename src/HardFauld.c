#include "main.h"
#include "HardFauld.h"
void pop_registers_from_fault_stack(unsigned int * hardfault_args);

void HardFault_Handler(void){


#ifdef _DEBUG	
	RST_CLK->PER_CLOCK |= (1<<23);											// Тактирование порта 
	RST_CLK->PER_CLOCK |= (1<<6);											// Тактирование UART1
	RST_CLK->UART_CLOCK |= (1<<24) | (0<<0);								// Тактирование узла
	PORTC->OE     |= (1<<3) | (0<<4);										// TX выход C3, RX вход C4 
  	PORTC->FUNC   |= (1<<6) | (1<<8);										// Функция порта (основная)
  	PORTC->ANALOG |= (1<<3) | (1<<4);										// Цифровой режим
 	PORTC->PWR    |= (3<<6) | (3<<8);																			
	UART1->IBRD = 0x0034;	
	UART1->FBRD = 0x0008;	
	UART1->LCR_H = (3<<5) | (0<<4) | (0<<3);								// FIFO off, 8бит 1 стоп бит
	UART1->CR = (1<<0) | (1<<8) | (1<<9);									// UART on, TX on, RX on
	UART1->IMSC |= (1<<4);
	
	_printf("EHardFault_Handler\n\r");
	
	_contr_reg = __get_CONTROL();
	if(_contr_reg & 2){
		hardfault_args = __get_PSP();	// asm("MRS R0, PSP");
	}else{
		hardfault_args = __get_MSP();	// asm("MRS R0, MSP");
	}
	pop_registers_from_fault_stack((unsigned int*) hardfault_args);
#endif
	RST_CLK->PER_CLOCK |= (1<<12);
	WWDG->CFR = 0x00;
	WWDG->CR = 0xFF;
	WWDG->CR = 0xFF;	
	while(1){;}
}
#ifdef _DEBUG
void pop_registers_from_fault_stack(unsigned int * hardfault_args)
{
	volatile unsigned int stacked_r0;
	volatile unsigned int stacked_r1;
	volatile unsigned int stacked_r2;
	volatile unsigned int stacked_r3;
	volatile unsigned int stacked_r12;
	volatile unsigned int stacked_lr;
	volatile unsigned int stacked_pc;
	volatile unsigned int stacked_psr;

	stacked_r0 = ((unsigned long) hardfault_args[0]);
	stacked_r1 = ((unsigned long) hardfault_args[1]);
	stacked_r2 = ((unsigned long) hardfault_args[2]);
	stacked_r3 = ((unsigned long) hardfault_args[3]);

	stacked_r12 = ((unsigned long) hardfault_args[4]);
	stacked_lr = ((unsigned long) hardfault_args[5]);
	stacked_pc = ((unsigned long) hardfault_args[6]);
	stacked_psr = ((unsigned long) hardfault_args[7]);

	_printf("7[pop_registers_from_fault_stack - all numbers in hex]\r\n");
	_printf("7\tR0 = %x\r\n", stacked_r0);
	_printf("7\tR1 = %x\r\n", stacked_r1);
	_printf("7\tR2 = %x\r\n", stacked_r2);
	_printf("7\tR3 = %x\r\n", stacked_r3);
	_printf("7\tR12 = %x\r\n", stacked_r12);
	_printf("7\tLR [R14] = %x  subroutine call return address\r\n", stacked_lr);
	_printf("7\tPC [R15] = %x  program counter\r\n", stacked_pc);
	_printf("7\tPSR = %x\r\n", stacked_psr);
}
#endif
void ProgrammReset(void){

#ifdef _DEBUG
	_printf("Reset\n\r");
#endif
	RST_CLK->PER_CLOCK |= (1<<12);
	WWDG->CFR = 0x00;
	WWDG->CR = 0xFF;
	WWDG->CR = 0xFF;
	while(1);

}
