#include <LPC21xx.h>
#include "LPC2129.h"  //Header File

/******************************************************** TIMER 0 ************************************************************/

/****** Mili Seconds delay generation ******/

/*  This Function utilize Timer 0 to generate delay in mili seconds.
    Call this function in main function and pass miliseconds (integer) value.
    e.g.-
          delay_ms(1000);   */
void delay_ms(unsigned int delay)
{
  T0PR=15000-1;       //Prescaled register holds number of pulses to count. 
                      //Default PCLK 15 MHz.(15000000 Pulses/s) for 1ms --> 15000000/1000 = 15000.
  T0PC=0;             //Prescaled counter holds number of pulses counted. Load with 0
  T0TC=0;             //When Prescaled counter (PC) counts pulses upto Prescaled register value, TC incremented by one.
  T0TCR=1;            //To start the timer
  while(T0TC<delay);  //wait until timer counter (TC) reaches provided delay value.
  T0TCR=0;            //Stop the timer.
}

/****** Seconds delay generation ******/

/*  This Function utilize Timer 0 to generate delay in seconds.
    Call this function in main function and pass seconds (integer) value.
    e.g.-
          delay_s(1);   */
void delay_s(unsigned int delay)
{
  T0PR=15000000-1;       //Prescaled register holds number of pulses to count. 
                      //Default PCLK 15 MHz.(15000000 Pulses/s) for 1 S --> 15000000/1 = 15000000.
  T0PC=0;             //Prescaled counter holds number of pulses counted. Load with 0
  T0TC=0;             //When Prescaled counter (PC) counts pulses upto Prescaled register value, TC incremented by one.
  T0TCR=1;            //To start the timer
  while(T0TC<delay);  //wait until timer counter (TC) reaches provided delay value.
  T0TCR=0;            //Stop the timer.
}

/******************************************************** TIMER 1 ************************************************************/
