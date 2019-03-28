#include "UART1.h"
#include <stdio.h>

//Reciver 1
// U1Rx -  PC4
// U1Tx -  PC5

//Reciver 2
// U2Rx -  PD6
// U2Tx -  PD7

//Reciver 3
// U3Rx -  PC6
// U3Tx -  PC7

//Bluetooth Module
// U5Rx -  PE4
// U5Tx -  PE5
	
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable

#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))// deprecated clock register ~ (only can use UARTS 0-3) with it
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) 
#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618)) // correct register to use ALL UART modules 
	
// PortC Defines
#define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
#define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))
#define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))
// PortD Defines
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
	
// PortE Defines
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
//RECEIVER 1 - UART1
#define UART1_DR_R              (*((volatile unsigned long *)0x4000D000))
#define UART1_FR_R              (*((volatile unsigned long *)0x4000D018))
#define UART1_IBRD_R            (*((volatile unsigned long *)0x4000D024))
#define UART1_FBRD_R            (*((volatile unsigned long *)0x4000D028))
#define UART1_LCRH_R            (*((volatile unsigned long *)0x4000D02C))
#define UART1_CTL_R             (*((volatile unsigned long *)0x4000D030))

#define SYSCTL_RCGC1_UART1      0x00000002  // UART1 Clock Gating Control
#define SYSCTL_RCGC2_GPIOC      0x00000004  // port C Clock Gating Control

//RECEIVER 2 - UART2
#define UART2_DR_R              (*((volatile unsigned long *)0x4000E000))
#define UART2_FR_R              (*((volatile unsigned long *)0x4000E018))
#define UART2_IBRD_R            (*((volatile unsigned long *)0x4000E024))
#define UART2_FBRD_R            (*((volatile unsigned long *)0x4000E028))
#define UART2_LCRH_R            (*((volatile unsigned long *)0x4000E02C))
#define UART2_CTL_R             (*((volatile unsigned long *)0x4000E030))

#define SYSCTL_RCGC1_UART2      0x00000004  // UART2 Clock Gating Control
#define SYSCTL_RCGC2_GPIOD      0x00000008  // port D Clock Gating Control

//RECEIVER 3 - UART3
#define UART3_DR_R              (*((volatile unsigned long *)0x4000F000))
#define UART3_FR_R              (*((volatile unsigned long *)0x4000F018))
#define UART3_IBRD_R            (*((volatile unsigned long *)0x4000F024))
#define UART3_FBRD_R            (*((volatile unsigned long *)0x4000F028))
#define UART3_LCRH_R            (*((volatile unsigned long *)0x4000F02C))
#define UART3_CTL_R             (*((volatile unsigned long *)0x4000F030))

#define SYSCTL_RCGCUART_R3        0x00000008  // UART Module 3 Run Mode Clock
                                              // Gating Control
//#define SYSCTL_RCGC1_UART3      0x00000008  // UART3 Clock Gating Control (deprecated)
//UART5: 0x4001.1000
//Bluetooth Module - UART5
#define UART5_DR_R              (*((volatile unsigned long *)0x40011000))
#define UART5_FR_R              (*((volatile unsigned long *)0x40011018))
#define UART5_IBRD_R            (*((volatile unsigned long *)0x40011024))
#define UART5_FBRD_R            (*((volatile unsigned long *)0x40011028))
#define UART5_LCRH_R            (*((volatile unsigned long *)0x4001102C))
#define UART5_CTL_R             (*((volatile unsigned long *)0x40011030))
	
#define SYSCTL_RCGCUART_R5        0x00000020  // UART Module 3 Run Mode Clock 
																							// Gating Control
#define SYSCTL_RCGC2_GPIOE        0x00000010  // port D Clock Gating Control 


//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 9600 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none

void UART1_Init(void){	
	SYSCTL_RCGC1_R |= 0x00000002;  // activate UART 1
  SYSCTL_RCGC2_R |= 0x00000004;  // activate port C	
  UART1_CTL_R &= ~0x00000001;    // disable UART
  UART1_IBRD_R = 260;     // IBRD = int(80,000,000/(16*19200)) = int(520.8333)
  UART1_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000001;     // enable UART		
  GPIO_PORTC_AFSEL_R |= 0xF0;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0xF0;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0xF0;   // disable analog on PC5-4
}

void UART2_Init(void){
	SYSCTL_RCGC1_R |= 0x00000004;  // activate UART2
  SYSCTL_RCGC2_R |= 0x00000008;  // activate port D
  UART2_CTL_R &= ~0x00000001;    // disable UART
  UART2_IBRD_R = 260;     // IBRD = int(80,000,000/(16*19200)) = int(260)
  UART2_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART2_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART2_CTL_R |= 0x00000001;     // enable UART	
  GPIO_PORTD_AFSEL_R |= 0xC0;    // enable alt funct on PD6-7
  GPIO_PORTD_DEN_R |= 0xC0;      // configure PD6-7 as UART1
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTD_AMSEL_R &= ~0xC0;   // disable analog on PD6-7
}

void UART3_Init(void){
	SYSCTL_RCGCUART_R |= 0x00000008;  // activate UART3
  SYSCTL_RCGC2_R |= 0x00000004;  // activate port C
  UART3_CTL_R &= ~0x00000001;    // disable UART
  UART3_IBRD_R = 260;     // IBRD = int(80,000,000/(16*9600)) = int(520.8333)
  UART3_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART3_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
	UART3_CTL_R |= 0x00000001;     // enable UART
  GPIO_PORTC_AFSEL_R |= 0xC0;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0xC0;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000;
  GPIO_PORTC_AMSEL_R &= ~0xC0;   // disable analog on PC5-4	
}

void UART5_Init(void){
	SYSCTL_RCGCUART_R |= 0x00000020;  // activate UART5
  SYSCTL_RCGC2_R |= 0x00000010;  // activate port E
  UART5_CTL_R &= ~0x00000001;    // disable UART
  UART5_IBRD_R = 260;     // IBRD = int(80,000,000/(16*19200)) = int(260)
  UART5_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART5_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
	UART5_CTL_R |= 0x00000001;     // enable UART
  GPIO_PORTE_AFSEL_R |= 0x30;    // enable alt funct on PE4-5
  GPIO_PORTE_DEN_R |= 0x30;      // configure PE4-5 as UART5
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFF00FFFF)+0x00110000;
  GPIO_PORTE_AMSEL_R &= ~0x30;   // disable analog on PE4-5
}


//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed


unsigned char UART1_InChar(void){
	while((UART1_FR_R&UART_FR_RXFE) != 0);   // wait until RXFE is 0
  return((unsigned char)(UART1_DR_R&0xFF));
}

unsigned char UART2_InChar(void){
	while((UART2_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0

  return((unsigned char)(UART2_DR_R&0xFF));
}

unsigned char UART3_InChar(void){
	while((UART3_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
	//printf("uart3 val = %c",t);
  return((unsigned char)(UART3_DR_R&0xFF));
}

unsigned char UART5_InChar(void){
    while((UART5_FR_R&UART_FR_RXFE) != 0);      // wait until RXFE is 0
  return((unsigned char)(UART5_DR_R&0xFF));
}

//void UART1_InData(unsigned char *array, size_t n) {
//	while((UART1_FR_R&UART_FR_RXFE) != 0){}
//
//	for (size_t i = 0; i < n; ++i) {
//		array[i] = (unsigned char)(UART1_DR_R & 0xFF);
//		if (array[i] == '\n') {
//			break;
//		}
//		// make sure the next char is in the register
//		printf("%c",array[i]);
//	}
//}


//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none


void UART5_OutChar(unsigned char data){
	while((UART5_FR_R&UART_FR_TXFF)){}    // wait until TXFF is 0
  UART5_DR_R = data;
}
// Immediately return input or 0 if no input

unsigned char UART1_InCharNonBlocking(void){
	return ((UART1_FR_R & UART_FR_RXFE) == 0)? (unsigned char)(UART1_DR_R & 0xFF): 0;
}
unsigned char UART2_InCharNonBlocking(void){
    return ((UART2_FR_R & UART_FR_RXFE) == 0)? (unsigned char)(UART2_DR_R & 0xFF): 0;
}
unsigned char UART3_InCharNonBlocking(void){
    return ((UART3_FR_R & UART_FR_RXFE) == 0)? (unsigned char)(UART3_DR_R & 0xFF): 0;
}
unsigned char UART5_InCharNonBlocking(void){
    return ((UART3_FR_R & UART_FR_RXFE) == 0)? (unsigned char)(UART3_DR_R & 0xFF): 0;
}
//int UART1_InDataNonBlocking(unsigned char *array, size_t n) {
//	if ((UART1_FR_R & UART_FR_RXFE) == 0) {
//		return 1;
//	}
//
//	for (size_t i = 0; i < n; ++i) {
//		array[i] = (unsigned char)(UART1_DR_R & 0xFF);
//		if (array[i] == '\n') {
//			break;
//		}
//		// make sure the next char is in the register
//	}
//
//	return 0;
//}

void Bluetooth_Out_String(char *string) {
  while(*string) { //The pointer is assigned to the input. If there is a character it would return 1, so would run for as long the string is
       UART5_OutChar(*string);//output via uart to bluetooth module so that its transmitted to the app
        string++; //The pointer increments to the next character 
  }
}
