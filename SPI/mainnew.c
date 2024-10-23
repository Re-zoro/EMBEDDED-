                    /* main_hwspi_mcp3204_lcd_test.c */
#include <LPC21xx.h>
#include "types.h"
#include "spi.h"
#include "mcp3204.h"
#include "lcd.c"

main()
{
	f32 f;
	Init_SPI0(); //hw SPI initialisation
	lcd_init();	
	str("MCP3204--");
  while(1)
  {
    f=Read_ADC_MCP3204(0);
		lcd_cmd(0xc0);
		Float_display(f);
	}	
}
					/* end of main.c */
