#ifndef UART1_h
#define UART1_h
#include <stdio.h>

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
void UART3_OutChar(unsigned char data);
unsigned char UART1_InChar(void);
unsigned char UART2_InChar(void);
unsigned char UART3_InChar(void);
unsigned char UART5_InChar(void);
void UART1_InData(unsigned char *array, size_t n) ;
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(unsigned char data);
void UART5_OutChar(unsigned char data);
void Bluetooth_Out_String(char *string) ;

unsigned char UART1_InCharNonBlocking(void);
unsigned char UART2_InCharNonBlocking(void);
unsigned char UART3_InCharNonBlocking(void);
unsigned char UART5_InCharNonBlocking(void);

#endif
