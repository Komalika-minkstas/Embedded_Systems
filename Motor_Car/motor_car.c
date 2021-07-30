
// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
//#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
//#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000
#define l RB3
#define m RB4
#define n RB5
#define o RB6
#define rs RB0
#define rw RB1
#define en RB2

unsigned int cmmd[]={0x38,0x0E,0x01,0x06,0x80,0x01};
unsigned char a;
unsigned int b,c;
unsigned char data1[]="FORWARD";
unsigned char data2[]="BACKWARD";
unsigned char data3[]="LEFT";
unsigned char data4[]="RIGHT";
unsigned char data5[]="STOP";
void delay()
{
  unsigned int x;
  for(x=0;x<10000;x++);
}
void cmm()
{
  rs=0;
  rw=0;
  en=1;
  delay();
  en=0;
}
void dat()
{
  rs=1;
  rw=0;
  en=1;
  delay();
  en=0;
}
void main()
{
    TRISB=0;
    TRISD=0;
    TRISC7=1;
    RCSTA=0x90;
    SPBRG=31;
    while(RCIF==0);
    a=RCREG;
    RCIF=0;
    l=m=n=o=0;
    if(a=='F')
	{
	  l=1;
	  m=0;
	  n=1;
	  o=0;
    for(b=0;b<6;b++)
    {
      PORTD=cmmd[b];
      cmm();
     }
    for(c=0;c<sizeof data1;c++)
	{
	  PORTD=data1[c];
	  dat();
	}
	l=m=n=o=0;
  }
	else if(a=='B')
	{
	  l=0;
	  m=1;
	  n=0;
	  o=1;
	for(b=0;b<6;b++)
    {
      PORTD=cmmd[b];
      cmm();
     }
    for(c=0;c<sizeof data2;c++)
	{
	  PORTD=data2[c];
	  dat();
	}
	l=m=n=o=0;
  }
	
	else if(a=='R')
	{
	  l=0;
	  m=0;
	  n=1;
	  o=0;
	  for(b=0;b<6;b++)
    {
      PORTD=cmmd[b];
      cmm();
     }
   for(c=0;c<sizeof data4;c++)
	{
	  PORTD=data4[c];
	  dat();
	}
	l=m=n=o=0;
  }
	else if(a=='L')
	{
	  l=1;
	  m=0;
	  n=0;
	  o=0;
	  for(b=0;b<6;b++)
    {
      PORTD=cmmd[b];
      cmm();
     }
   for(c=0;c<sizeof data3;c++)
	{
	  PORTD=data3[c];
	  dat();
	}
	l=m=n=o=0;
	}
	else if(a=='S')
	{
	  l=m=n=o=0;
	   for(b=0;b<6;b++)
    {
      PORTD=cmmd[b];
      cmm();
     }
   for(c=0;c<sizeof data5;c++)
	{
	  PORTD=data5[c];
	  dat();
	}
	l=m=n=o=0;
	}
}