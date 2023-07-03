/*  This file contains user defined functions related to UART0 and UART1  */
#include <LPC21xx.h>
#include "LPC2129.h"        //Header File

/********************************************************.UART 0 ************************************************************/

/****** UART Initialization ******/

/*  This Function initialize UART0 and make it ready for transmisitting and receiving data.
    Call this function in main function and pass baudrate(integer) value.
    e.g.-
          uart0_init(9600);   */

void uart0_init(unsigned int boud)
{
    int boudrate;
    boudrate=15000000/(boud*16);           //Calculate Divisor Latch LSB register value(DLL)
 				           //formula = PCLK / (boudrate * 16)
    
    PINSEL0=0x05;                   //PINSEL0 controls modes of P0.0 to P0.15 pins 
                                    //P0.0 --> Tx0(1st bit =0, 0th bit=1 (01))  //P0.1 --> Rx0(3rd bit =0, 2nd bit=1 (01)  //0101 
    U0LCR=0x83;                     //It will set word select(0th, 1st bit) -->8 bit, DLAB(7th bit) --> unlock
    U0DLL=boudrate;                 //Set boudrate
                                    //Default PCLK= 15 MHz
    U0DLM=0;                        //Divisor Latch MSB value 0
    U0LCR=0x03;                     //It will clear DLAB(7th bit) --> lock , boudrate is locked , word select as it is.
}

/****************************************************************************************************************************/

/***** Character Transmission *****/

/*  This function Transmitt single character via UART0. 
    Call this function in main function and pass ASCII character.
    e.g.-
          uart0_tx_char('A');   */

#define THRE (U0LSR>>5&1)           //5th bit of U0LSR register is THRE flag 

void uart0_tx_char(unsigned char ch)
{
  U0THR=ch;                         //Load Character into U0THR register
  while(THRE!=1);                   //Wait until transmit THRE=0 -->U0THR Full    THRE=1 -->U0THR Empty (transmitted)
}

/****************************************************************************************************************************/

/***** Character Reception *****/

/*  This function Receives single character via UART0. 
    Call this function in main function and it will return ASCII character.
    e.g.-
          unsigned char ch = uart0_rx_char();   */

#define RDR (U0LSR>>0&1)           //0th bit of U0LSR register is RDR flag 

unsigned char uart0_rx_char()
{
  while(RDR!=1);                   //Wait until receive RDR=0 -->U0RBR Empty    RDR=1 -->U0RBR Full (Received)
  return U0RBR;                    //U0RBR register holds received character, return received character to main function  
}

/****************************************************************************************************************************/

/***** String Transmission *****/

/*  This function Transmitt string via UART0. 
    Call this function in main function and pass base address of string.
    e.g.-
          uart0_tx_string(<string base address>);   */

void uart0_tx_string(char *ptr)
{	
    while(*ptr)                     //Loop continusly executes until *ptr != \0
    {
        //uart0_tx_char(*ptr);      //Transmitt single characte of string
        U0THR=*ptr;                 //For faster execution directly load single character into THR register
        while(THRE!=1);             //Wait until transmit THRE=0 -->U0THR Full    THRE=1 -->U0THR Empty (transmitted)
        ptr++;                      //pointer point to next character of the string
    }
}

/****************************************************************************************************************************/

/***** String reception *****/

/*  This function receives string via UART0. 
    Call this function in main function and pass base address of character array [20].
    e.g.-
            char s[20];
          uart0_rx_string(<string base address>,size);   */

void uart0_rx_string(char *ptr,int size)
{
    int i,size;
    for(i=0;i<size-1;i++)
    {
        while(RDR!=1);              //Wait until receive, RDR=0 -->U0RBR Empty    RDR=1 -->U0RBR Full (Received) 
        //ptr[i]=uart0_rx_char();
        ptr[i]=U0RBR;               //For faster execution directly assign U0RBR to ptr
        if(ptr[i]=='\n')              //if user press enter on terminal it will transmitt '\r' (indicates end of string)
            break;
    }
    ptr[i-1]='\0';                   //at the end of string add '\o' 
}

/****************************************************************************************************************************/

/***** Transmit Integer *****/
uart0_tx_integer(int num)
{
	char s[10];
	int i;
	if(num==0)
	{
		uart0_tx_char('0');
	}
	if(num<0)
	{
		num=-num;
		uart0_tx_char('-');
	}
	for(i=0;num;num=num/10,i++)
	{
		s[i]=(num%10)+48;
	}
	s[i]='\0';
	for(i=i-1;i>=0;i--)
	{
		//uart0_tx_char(s[i]);		    //For faster execusion
		U0THR=s[i];                         //Load Character into U0THR register
 		while(THRE!=1);
	}
	//uart0_tx_string('\r\n');
}
/****************************************************************************************************************************/
/***** Transmit float *****/

void uart0_tx_float(float f)
{
    int i;
    char s[15];
    float f1;
    int num;
    if(f==0)
    {
	    uart0_tx_string("0.000")
    }
    if(f<0)
    {
        uart0_tx_char('-');
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
	//uart0_tx_char(s[i]);		    //For faster execusion
	U0THR=s[i];                         //Load Character into U0THR register
 	while(THRE!=1);
    }
    //uart0_tx_string(s);
    uart0_tx_char('.');
	
    f1=f1*1000;     //resolution upto 3 digits
    num=(int)f1;
    if(num==0)
    {
	uart0_tx_string("000");
	return;
    }
    if(num<10)
    {
        uart0_tx_string("00");
    }
    else if(num<100)
    {
       	U0THR='0';                         //Load Character into U0THR register
  	while(THRE!=1);                   //Wait until transmit THRE=0 -->U0THR Full    THRE=1 -->U0THR Empty (transmitted)
    }
    for(i=0;num;num=num/10,i--)
    {
        s[i]=(num%10)+48;
    }
    s[i]='\0';
    for(i=i-1;i>=0;i--)
    {
	//uart0_tx_char(s[i]);		    //For faster execusion
	U0THR=s[i];                         //Load Character into U0THR register
 	while(THRE!=1);
    }
    //uart0_tx_string(s);
}

/****************************************************************************************************************************/
/***** Transmit Hexa *****/
/********************************************************.UART 1 ************************************************************/












