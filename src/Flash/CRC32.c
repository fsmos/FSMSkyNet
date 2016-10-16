#include "CRC32.h"

// вычисление CRC32 IEEE802.3

unsigned int crc32NT(uint32_t crc, uint8_t *buf,uint32_t len) {
   uint32_t i,mask;

   crc = ~crc;
   while (len--) {
	  crc = crc ^ (*buf++); // process next byte
	  i=8;
	  while (i--) { // process 8 bits
		 mask = -(crc & 1);
		 crc = (crc >> 1) ^ (0xEDB88320 & mask);
	  }
   }
   return ~crc;
}

#ifdef TABLE_CRC

uint32_t CRC32_table[256];

void init_crc32_table(){
   int32_t  i;
   uint32_t d, rem, mask;

   for (d = 0; d <= 255; d++) {
	 rem = d;
	 for (i = 7; i >= 0; i--) {
		mask = -(rem & 1);
		rem = (rem >> 1) ^ (0xEDB88320 & mask);
	 }
	 CRC32_table[d] = rem;
   }
}

uint32_t crc32T(uint32_t crc, uint8_t * buf, uint32_t len){
   if (!CRC32_table[1]) init_crc32_table();

   crc = ~crc;
   while (len--) crc = (crc >> 8) ^ CRC32_table[(crc ^ (*buf++)) & 0xFF];
   return ~crc;
}

#endif
