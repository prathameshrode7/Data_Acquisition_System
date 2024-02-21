#include <LPC21xx.h>
#include "LPC2129.h"
//1111 1110  0000 0000 |0000 0000  0000 0000|  P1=0xFE000000;
//0000 0000  0000 0000  0000 0111  1111 1111   P0=0x000007FF;

#define RS (1<<8)
#define RW (1<<9)
#define EN (1<<10)



void LCD_INIT()
{
  IODIR0|=0x7FF;
  //IOCLR0|=0x7FF;
  LCD_CMD(0x38);
  LCD_CMD(0x0E);
  LCD_CMD(0x01);
  //IOSET0|=0x38;
  //IOSET0|=0x0E;
  //IOSET0|=0x01;
  
}

void LCD_CMD(unsigned char CMD)
{
  //IOCLR0|=0x7FF;
  IOCLR0|=0xFF;
  IOSET0|=CMD;
  IOCLR0|=RS;    //RS=0
  //IOCLR0|=RW;    //RW=0
  IOSET0|=EN;   //EN=1
  delay_ms(2);
  IOCLR0|=EN;   //EN=0
}

void LCD_DATA(unsigned char DATA)
{
  IOCLR0|=0xFF;
  IOSET0|=DATA;
  IOSET0|=RS;    //RS=1
  //IOCLR0|=RW;    //RW=0
  IOSET0|=EN;   //EN=1
  delay_ms(2);
  IOCLR0|=EN;   //EN=0
}

void LCD_STRING(Char *s)
{
  while(*p)
  {
    LCD_DATA(*p);
    p++;
  }
}

void LCD_INTEGER(int num)
{
  int i;
  char s[10];
	if(num==0)
	{
		LCD_DATA('0');
	}
	if(num<0)
	{
		num=-num;
		LCD_DATA('-');
	}
	for(i=0;num;num=num/10,i++)
	{
		s[i]=(num%10)+48;
	}
  s[i]='\0';
	for(i=i-1;i>=0;i--)
  {
    LCD_DATA(s[i]);
	}
}

void LCD_FLOAT(float f)
{
    int i;
    char s[15];
    float f1;
    int num;
    if(f==0)
    {
	    LCD_STRING("0.000");
    }
    if(f<0)
    {
        LCD_DATA('-');
        f=-f;
    }
    num=(int)f;
    f1=f-(float)num;

    for(i=0;num;num=num/10,i++)
    {
        s[i]=(num%10)+48;
    }
    s[i]='\0';
  
    for(i=i-1;i>=0;i--)
    {
      LCD_DATA(s[i]);
	  }

    LCD_DATA('.');

    f1=f1*1000;     //resolution upto 3 digits
    num=(int)f1;
    if(num==0)
    {
	    LCD_STRING("000");
	    return;
    }
    if(num<10)
    {
        LCD_STRING("00");
    }
    else if(num<100)
    {
       	LCD_DATA('0');           
    }

    for(i=0;num;num=num/10,i++)
    {
        s[i]=(num%10)+48;
    }
    s[i]='\0';
  
    for(i=i-1;i>=0;i--)
    {
      LCD_DATA(s[i]);
	  }
}
