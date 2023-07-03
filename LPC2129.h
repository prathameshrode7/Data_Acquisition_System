/***************************************** USER DEFINED FUNCTION DECLERATIONS *****************************************/

/*************************************************** TIMER 0 & 1 ****************************************************/
  void delay_ms(unsigned int);
  void delay_s(unsigned int);
/*************************************************** UART 0 & 1 *****************************************************/
  void uart0_init(unsigned int);
  void uart0_tx_char(unsigned char);
  unsigned char uart0_rx_char(void);
  void uart0_tx_string(char *);
  void uart0_rx_string(char *,int);
  void uart0_tx_integer(int);
  void uart0_tc_float(float);


  void uart1_init(unsigned int);
  void uart1_tx_char(unsigned char);
  unsigned char uart1_rx_char(void);
  void uart1_tx_string(char *);
  void uart1_rx_string(char *,int);
  void uart1_tx_integer(int);
  void uart1_tc_float(float);
/****************************************************** ADC ********************************************************/
  void adc_init(void);
  unsigned int adc_read(int);
