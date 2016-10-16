#ifndef __CRC32_IEEE__
#define __CRC32_IEEE__

#include "stdint.h"

// ������������ ��������� ���������� (������� 1�� ��� ��� �������)
//#define TABLE_CRC

// ���������� CRC32 ��� ������������� �������
uint32_t crc32NT(uint32_t crc, uint8_t *buf,uint32_t len);

#ifdef TABLE_CRC
// ������� ������� CRC32, ����� �������������� ������� ��� ������������� ���������
void init_crc32_table(void);
// ���������� CRC32 � �������������� �������
uint32_t crc32T(uint32_t crc, uint8_t *buf,uint32_t len);
#endif

#endif
