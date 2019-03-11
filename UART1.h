#ifndef UART1_h
#define UART1_h


//------------UART_InChar------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART1_Init(void);
void UART2_Init(void);
void UART3_Init(void);
void UART5_Init(void);
//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed

unsigned char UART1_InChar(void);
unsigned char UART2_InChar(void);
unsigned char UART3_InChar(void);
unsigned char UART5_InChar(void);
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(unsigned char data);



#endif
