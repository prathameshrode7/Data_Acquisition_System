#include<LPC21xx.h>
#include "LPC2129.h"

#define Ref_vtg 3.3   //Reference Voltage used for ADC and IC (max voltage 3.3V)
#define V0 0.5        //voltage at 0 degree Celsius produced by IC 0.5mV
#define Vtemp 0.01    //Voltage pre degree Celsius 0.01mV

int main()
{
  unsigned int result;
  float Temperature,Vout;
  adc_init();
  uart0_init(9600);
  while(1)
  {
      
      result=adc_read(0);
      Vout=(float)(result/1024)*Ref_vtg;
      Temperature=(Vout-V0)/Vtemp;
      uart0_tx_float(Vout);
      uart0_tx_string("V  ");
      uart0_tx_float(Temperature);
      uart0_tx_string("C\r\n");
      dalay_ms(500);
  }
}
