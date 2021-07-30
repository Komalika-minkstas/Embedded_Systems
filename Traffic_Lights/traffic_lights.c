#include<LPC21XX.h>
unsigned int a[]={0xf3,0x12,0x163,0x133,0x192,0x1b1};
void delay()
{
  unsigned int d;
  for(d=0;d<40000;d++);
}
void count()
{  
  unsigned int i;
  IO1DIR=0xFFFFFFFF;
   for(i=0;i<6;i++)
  {
    IO1PIN=i<<16;
	delay();
  }
}
void main()
{	 
  IO0DIR=0xFFFFFFFF;
  IO1DIR=0xFFFFFFFF;
  while(1)
  {
 IO0PIN=0x00000889;
 delay();
 count();
IO0PIN=0x00000311;
delay();
 count();
IO0PIN=0x00000262;
delay();
 count();
IO0PIN=0x0000044C;
delay();
 count();
 }

}