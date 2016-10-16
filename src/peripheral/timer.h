/**/
#ifndef _TIMER_H
#define _TIMER_H

#include "stdint.h"

#define TIMER_1MSEC (96000 - 1)// �������� � 1 �� ��� 96 ���

void TIMER1_Handler(void);
/**********************************************************************/	

void TIM_initialization(void);
/**********************************************************************/
/*
   ������� ���������� ������� ��������� �����
		���������: ���
		����������: ��������� ����� � �� 
*/
uint32_t GetTime(void);
/**********************************************************************/
/*
	��������� ������ �������
		���������: ���
		����������: ���
*/
void TimerReset(void);
/**********************************************************************/
/*	
	��������� ���������� ��������
	���������: ����� ������� � ��
	����������: ���
*/
void delay_ms(uint32_t);
/**********************************************************************/
#endif
