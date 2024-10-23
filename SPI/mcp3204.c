                        /*  file: mcp3204.c */
#include <LPC21xx.h>
#include "types.h"
#include "spi.h"
#include "spi_defines.h"
#include "defines.h"

f32 Read_ADC_MCP3204(u8 channelNo)
{
  u8 hByte,lByte;
  u32 adcVal=0;
   
  //select/activate chip 
  CLRBIT(IOPIN0,CS);
	//delay_ms(100);
	
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);
	
	//de-select/de-activate chp
	SETBIT(IOPIN0,CS);
	//delay_ms(100);
  adcVal=((hByte&0x0f)<<8)|lByte;
  return ((adcVal*3.3)/4096);
}
                     /* end of mcp3204.c */
