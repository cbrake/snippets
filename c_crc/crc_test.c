#include <stdio.h>
#include <stdint.h>

#define POLY 0x8408

/*
 * from:
 * http://www.stjarnhimlen.se/snippets/crc-16.c
 *
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/

unsigned short crc16(char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}

// kermit
// from: https://forum.arduino.cc/t/help-with-crc16-ccitt-reversed-checksum-and-packet/641242/22
uint16_t CRC16K(uint8_t *x, uint8_t len) {
    uint8_t *data = x;
    uint16_t crc=0;

    while (len--) {
        crc ^= *data++;
        for (uint8_t k = 0; k < 8; k++)
            if (crc & 1)
               crc =(crc >> 1) ^ 0x8408;
            else
               crc = crc >> 1;
    }

    return crc;
}

void main()
{

	static char data[] = {0x1, 0x2};

	printf("crc16: 0x%x\n", crc16(data, 2));
	printf("CRC16K: 0x%x\n", CRC16K(data, 2));
}

/* this program returns:
 *
 * crc16: 0x8d35
 * CRC16K: 0x3aca
 *
 */
