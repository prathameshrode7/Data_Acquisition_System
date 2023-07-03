#include<LPC21xx.h>
#include "LPC2129.h"

#define Ref_vtg 3.3   //Reference Voltage used for ADC and IC (max voltage 3.3V)
#define V0 0.5        //voltage at 0 degree Celsius produced by IC 0.5mV
#define Vtemp 0.01    //Voltage pre degree Celsius 0.01mV

int main()
{
  unsigned int result;
  int Light_Intensity;
  float Temperature,Vout;
  adc_init();
  uart0_init(9600);
  uart0_tx_string("************* Data Acquisition System *************\r\n");
  while(1)
  {
      
      result=adc_read(0);    //MCP9700 Thermister is interfaced at AIN0 
      Vout=(float)(result/1024)*Ref_vtg;
      Temperature=(Vout-V0)/Vtemp;
      uart0_tx_string("Temperature(C)    Light Intensity(%)    POT(Vtg)\r\n");
      uart0_tx_float(Temperature);
      uart0_tx_string("C    ");

      result=adc_read(1);    //LDR is interfaced at AIN1
      Vout=(float)(result/1024)*Ref_vtg;
      Light_intensity=(Vout/Ref_vtg)*100;
      uart0_tx_float(Light_Intensity);
      uart0_tx_string("%    ");

      result=adc_read(2);    //Potentiometer is interfaced at AIN2
      Vout=(float)(result/1024)*Ref_vtg;
      uart0_tx_float(Vout);
      uart0_tx_string("V    ");
      dalay_ms(500);
  }
}
