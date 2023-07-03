/*************** ADC Drivers *****************/
#include<LPC21xx.h>
#include "LPC2129.h"

void adc_init()
{     
  PINSEL1=0x15400000;          //PINSEL1    0000 0000  0010 0000  0000 0100  0000 0000
                               //     0x 
  ADCR=0x00200400;             //ADCR   0000 0000  0010 0000  0000 0100  0000 0000
                               //  0x      0    0     2    0     0    4     0    0
}





#define  select_channel (ADCR|(1<<channel))
#define diselect_channel (ADCD&~(1<<channel))
#define START_ADC (ADCR|(1<<24))
#define STOP_ADC (ADCR&~(1<<24))
#define DONE (ADCR>>31&1)

unsigned int adc_read(int channel)
{
  unsigned int result=0;

  ADCR=select_channel;
  ADCR=START_ADC;
  while(DONE!=1);
  ADCR=STOP_ADC;
  ADCR=diselect_channel;
  result=(ADDR>>6)&3FF;
  return result;
}
