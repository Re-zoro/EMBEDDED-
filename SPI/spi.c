                               /* spi.c */
#include <LPC214x.h>
#include "types.h"
#include "pin_function_defines.h"
#include "spi_defines.h"
#include "defines.h"

// peripheral/hw spi
void Init_SPI0(void)
{
	
	PINSEL0 |=0X00001500;
  S0SPCCR = SPI_RATE;             // cfg bit clock rate 
  S0SPCR  = (1<<MSTR_BIT|Mode_3); //spi module in master mode,
                                  //CPOL =1,CCPHA = 1. MSB first
	SETBIT(IOPIN0,CS);
	SETBIT(IODIR0,CS);
}

u8 SPI0(u8 data)
{
   u8 stat;
   stat = S0SPSR;    //clear SPIF 
   S0SPDR = data;   // load spi tx reg
   while(READBIT(S0SPSR,SPIF_BIT)==0); // wait for transmission to complete
   return S0SPDR;    // read data from SPI data reg, place into buffer 
}
				/* end of spi.c */

