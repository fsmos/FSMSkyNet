#ifndef __CRC32_IEEE__
#define __CRC32_IEEE__

#include "stdint.h"

// использовать табличные вычисления (требует 1КБ ОЗУ для таблицы)
//#define TABLE_CRC

// вычисление CRC32 без использования таблицы
uint32_t crc32NT(uint32_t crc, uint8_t *buf,uint32_t len);

#ifdef TABLE_CRC
// рассчет таблицы CRC32, можно предварительно вызвать при инициализации программы
void init_crc32_table(void);
// вычисление CRC32 с использованием таблицы
uint32_t crc32T(uint32_t crc, uint8_t *buf,uint32_t len);
#endif

#endif
