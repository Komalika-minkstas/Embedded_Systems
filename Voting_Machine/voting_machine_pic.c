
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
#define msec 50
#define lcd_data_str_pin PORTC 
#define ini_pin RB0
#define party_1 RB1
#define party_2 RB2
#define party_3 RB3
#define stop_pin RB4
#define rs RD3
#define rw RD4
#define en RD5

unsigned int p;
int vote_amt[3],j;
unsigned int vote_1,vote_2,vote_3;

unsigned char arr3[18]="Press init button";

int arr[3];
int max=0;
int carry = 0;

void delay(int delay_time)  // Time delay function
{
int j,k;
for(j=0;j<=delay_time;j++)
  for(k=0;k<=1000;k++);
}

void lcd_cmd(unsigned char cmd_addr)  //Function to send command to LCD
{
lcd_data_str_pin = cmd_addr;
en = 1;
rs = 0;
rw = 0;
delay(1);
en = 0;
return;
}

void lcd_data_str(char str[50])  //Function to send string
{ 
int p;
for(p=0;str[p]!='\0';p++)
{
  lcd_data_str_pin = str[p];
  rw = 0;
  rs = 1;
  en = 1;
  delay(1);
  en = 0;
}
return;
}

void lcd_data_int(unsigned int vote)  //Function to send 0-9 character values
{ 
char dig_ctrl_var;
int p;
for (j=2;j>=0;j--)
{
  vote_amt[j]=vote%10;
  vote=vote/10;
}

for (p=0;p<=2;p++)
{
  dig_ctrl_var = vote_amt[p]+48;
  lcd_data_str_pin = dig_ctrl_var;
  rw = 0;
  rs = 1;
  en = 1;
  delay(1);
  en = 0;
}
return;
} 

void vote_count()  // Function to count votes
{
while (party_1==0 && party_2==0 && party_3==0);
if (party_1==1)
{
  while (party_1 == 1);
   {
    vote_1 = vote_1 + 1;
   }
}

if (party_2==1)
{
  while (party_2 == 1);
   {
    vote_2 = vote_2 + 1;
   }
}

if (party_3==1)
{
  while (party_3 == 1);
   {
    vote_3 = vote_3 + 1;
   }
}
}

void lcd_ini()
{
    lcd_cmd(0x38);
delay(msec);
lcd_cmd(0x0E);
delay(msec);
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x81);
delay(msec);
lcd_data_str("Welcome!!!");
delay(100);
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x80);
delay(msec);
lcd_data_str( "Press" );
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("button");
delay(msec);

delay(msec);
lcd_cmd(0xC0);
delay(msec);
lcd_data_str("to");
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("vote");
delay(100);
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x80);
delay(msec);
lcd_data_str("BJP");
delay(msec);
lcd_cmd(0x84);
delay(msec);
lcd_data_str("Congress");
delay(msec);
lcd_cmd(0x88);
delay(msec);
lcd_data_str("BJD");
delay(msec);
lcd_cmd(0x8C);
delay(msec);

vote_count();
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x85);
delay(msec);
lcd_data_str("Thank");
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("You!!");
delay(100);
}

void results()  // Function to show results
{
int i;
carry = 0;
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x80);
delay(msec);
lcd_data_str("Results");
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("Are");
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("Out");
delay(msec);

  lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x80);
delay(msec);
lcd_data_str("BJP");
delay(msec);
lcd_cmd(0x84);
delay(msec);
lcd_data_str("Congress");
delay(msec);
lcd_cmd(0x88);
delay(msec);
lcd_data_str("BJD");
delay(msec);
lcd_cmd(0x8C);
delay(msec);


lcd_cmd(0xC0);
delay(100);
lcd_data_int(vote_1);
delay(msec);

lcd_cmd(0xC4);
delay(msec);
lcd_data_int(vote_2);
delay(msec);

lcd_cmd(0xC8);
delay(msec);
lcd_data_int(vote_3);

delay(300);

arr[0] = vote_1;
arr[1] = vote_2;
arr[2] = vote_3;


for( i=0; i<3; i++)
{
  if(arr[i]>=max)
  max = arr[i];
}

if ( (vote_1 == max) && ( vote_2 != max) && (vote_3 != max) )
{
  carry = 1;
  lcd_cmd(0x01);
  delay(msec);
  lcd_cmd(0x82);
  delay(msec);
  lcd_cmd(0xC4);
  delay(msec);
  lcd_data_str("BJP");
  delay(msec);
  lcd_cmd(0x14);
  delay(msec);
  lcd_data_str("wins");
  delay(msec);
}

if ( (vote_2 == max) && ( vote_1 != max) && (vote_3 != max))
{
  carry = 1;
  lcd_cmd(0x01);
  delay(msec);
  lcd_cmd(0x82);
  delay(50);
  lcd_cmd(0xC4);
  delay(msec);
  lcd_data_str("Congress");
  delay(msec);
  lcd_cmd(0x14);
  delay(msec);
  lcd_data_str("wins");
  delay(msec);
}

if ( (vote_3 == max) && ( vote_2 != max) && (vote_1 != max))
{
  carry = 1;
  lcd_cmd(0x01);
  delay(msec);
  lcd_cmd(0x82);
  delay(50);
  lcd_cmd(0xC4);
  delay(msec);
  lcd_data_str("BJD");
  delay(msec);
  lcd_cmd(0x14);
  delay(msec);
  lcd_data_str("wins");
  delay(msec);
}


if (carry==0)
{
  lcd_cmd(0x01);
  delay(msec);
  lcd_cmd(0x82);
  delay(msec);
  lcd_data_str("clash");
  delay(50);
  lcd_cmd(0x14);
  delay(msec);
  lcd_data_str("between!!!");
  delay(50);
  if(vote_2 == max)
  {
   lcd_cmd(0xC5);
   lcd_data_str("P2");
   delay(50);
  }
  if(vote_3 == max)
  {
   lcd_cmd(0xC9);
   lcd_data_str("P3");
   delay(50);
  }
}
}
void main()
{
    TRISD3=0;
    TRISD4=0;
    TRISD5=0;
    TRISB=1;
    TRISC=0;
ini_pin = stop_pin = 1;
vote_1 = vote_2 = vote_3 =0;
party_1 = party_2 = party_3 =  0;
lcd_cmd(0x38);
delay(msec);
lcd_cmd(0x0E);
delay(msec);
lcd_cmd(0x01);
delay(msec);
lcd_cmd(0x80);
delay(msec);
lcd_data_str( "Press" );
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("init");
delay(msec);

delay(msec);
lcd_cmd(0xC0);
delay(msec);
lcd_data_str("to");
delay(msec);
lcd_cmd(0x14);
delay(msec);
lcd_data_str("begin");
delay(100);
while(1)
{
  while(ini_pin != 0)
  {
   if (stop_pin == 0)
   break;
  }
  if (stop_pin == 0)
  {
  break;
  }
  lcd_ini();
}

while(1)
{
results();
}
}