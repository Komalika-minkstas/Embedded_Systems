
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
unsigned char pw[]="1234";
unsigned char wrong[]="WRONG PASSWORD!TRY AGAIN!!";
unsigned char correct[]="CORRECT PASSWORD!WELCOME!!";
unsigned char arr1[]="ENTER PASSWORD";
unsigned char check[4];
unsigned char b='*';
unsigned int x;
unsigned int y;
unsigned int z;
unsigned int flag;
#define a RB1
void delay1()
{
  unsigned int d;
  for(d=0;d<20000;d++);
}
void main()
{
    TRISB1=0;
    TRISC6=0;
    TRISC7=1;
    TXSTA=0x20;
    SPBRG=31;
    SPEN=1;
    RCSTA=0x90;
    a=0;
    for(x=0;x<14;x++)
    {
        TXREG=arr1[x];
        while(TXIF==0);
        TXIF=0;
    }
    TXREG=0x0D;
    while(TXIF==0);
    TXIF=0;
    for(y=0;y<4;y++)
    {
        while(RCIF==0);
        check[y]=RCREG;
        RCIF=0;
        TXREG=y;
        TXREG='*';
        while(TXIF==0);
        TXIF=0;
    }
    TXREG=0x0D;
    while(TXIF==0);
    TXIF=0;
    for(z=0;z<4;z++)
    {
        if(check[z]==pw[z])
        {
            flag=flag+1;
        }
        
    }
    if(flag==4)
    {
        unsigned int m;
        flag=0;
        a=1;
        for(m=0;m<27;m++)
        {
            TXREG=correct[m];
            while(TXIF==0);
            TXIF=0;
        }
        delay1();
        TXREG=0x0D;
        while(TXIF==0);
        TXIF=0;
    }
    else
    {
        unsigned int n;
        flag=0;
        for(n=0;n<27;n++)
        {
            TXREG=wrong[n];
            while(TXIF==0);
            TXIF=0;
        }
    }
    TXREG=0x0D;
    while(TXIF==0);
    TXIF=0;
}