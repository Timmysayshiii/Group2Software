#include <stdio.h>

#include "TExaS.h"
#include "uart.h"
#include "PLL.h"

#include "PortInit.h"

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// PortB Defines
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

// PortC Defines
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_PUR_R        (*((volatile unsigned long *)0x40006510))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_CR_R         (*((volatile unsigned long *)0x40006524))
#define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
#define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))
#define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))

// PortD Defines
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

// PortE Defines
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
void lcdPortInit(void){ volatile unsigned long delay;
//PortB (0)
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) B clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTB_CR_R = 0x3C;           // allow changes to PB3-0       
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0x3C;          // 5) PB0 output (Tx)
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R = 0x00;          // enable pullup resistors       
  GPIO_PORTB_DEN_R = 0x01;          // 7) enable digital pins PB0
	  
// PortC (4567)
	SYSCTL_RCGC2_R |= 0x00000008;     // 1) C clock
	delay = SYSCTL_RCGC2_R;           // delay
	GPIO_PORTC_LOCK_R = 0x4C4F434B;   // 2) unlock PORTC PD0
	GPIO_PORTC_CR_R = 0x0F;           // allow changes to PD3-0
	GPIO_PORTC_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTC_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
	GPIO_PORTC_DIR_R = 0x0F;          // 5) PD3,PD2,PD1,PD0 output
	GPIO_PORTC_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTC_PUR_R = 0x00;          // disable pullup resistors for outputs
	GPIO_PORTC_DEN_R = 0x0F;          // 7) enable digital pins PD3-PD0
	
// PortD = (67)
	SYSCTL_RCGC2_R |= 0x00000008;     // 1) D clock
	delay = SYSCTL_RCGC2_R;           // delay
	GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2) unlock PortD PD0
	GPIO_PORTD_CR_R = 0x0F;           // allow changes to PD3-0
	GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTD_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
	GPIO_PORTD_DIR_R = 0x0F;          // 5) PD3,PD2,PD1,PD0 output
	GPIO_PORTD_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTD_PUR_R = 0x00;          // disable pullup resistors for outputs
	GPIO_PORTD_DEN_R = 0x0F;          // 7) enable digital pins PD3-PD0

// PortE (4,5)
	SYSCTL_RCGC2_R |= 0x00000010;     // 1) E clock
	delay = SYSCTL_RCGC2_R;           // delay
	GPIO_PORTE_CR_R = 0x0F;           // allow changes to PE3-0
	GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog function
	GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
	GPIO_PORTE_DIR_R = 0x00;          // 5) PF4,PF0 input, PF3,PF2,PF1 output
	GPIO_PORTE_AFSEL_R = 0x00;        // 6) no alternate function
	GPIO_PORTE_PUR_R = 0x0F;          // enable pullup resistors on PD3,PD0
	GPIO_PORTE_DEN_R = 0x0F;          // 7) enable digital pins PD3-PD0
	
}
