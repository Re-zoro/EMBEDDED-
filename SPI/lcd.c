#include<LPC21xx.h>
#define lcd_d 0xff<<8
#define rs 1<<16
//#define rw 1<<18
#define e 1<<18

typedef unsigned int U32;
typedef unsigned char U8;
typedef signed char S8;
typedef float F32;

										 
void delay_milliseconds(U32 milliseconds)
{
	//T0CTCR=0X00;
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<milliseconds);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void lcd_cmd(U8 d)
{
	IOPIN0 = d<<8;
	IOCLR0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_milliseconds(2);
	IOCLR0 =e;
}

void lcd_data(U8 d)
{
	IOPIN0 = d<<8;
	IOSET0 = rs;
	//IOCLR0 = rw;
	IOSET0 =e;
	delay_milliseconds(2);
	IOCLR0 =e;
}

void lcd_init(void)
{
	IODIR0 |= lcd_d|rs|e;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}

void str(U8 *s)
{
	while(*s)
		lcd_data(*s++);
}

void lcd_integer(int n)
{
	S8 arr[5],i=0;
	if(n==0)
		lcd_data('0');
	else
	{
		   if(n<0)
		   {
				 lcd_data('-');
				 n=-n;
       }
	      while(n>0)
      	{
		     arr[i++]=n%10;
		     n=n/10;
        }
        for(--i;i>=0;i--)
   	      lcd_data(arr[i]+48);
  }
}
void Float_display(F32 f_val)
{
  U32 number;
  number = f_val;
  lcd_integer(number);
  lcd_data('.');
  number=(f_val-number)*100;
  lcd_integer(number);	
}

