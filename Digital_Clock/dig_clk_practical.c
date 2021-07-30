#include<reg51.h>
unsigned int h1,h2,m1,m2,s;
unsigned char arr[]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};

void delay()
{
unsigned int x;
TMOD=0x01;

 
for(x=0;x<7;x++)
  {
  TH0=0;
	TL0=0;
	TR0=1;
	while(TF0==0);
	TF0=0;
	TR0=0;
  }
}
void main()
{
	h1=h2=m1=m2=arr[0];
for(h2=1;h2<2;h2++)
{
  for(h1=1;h1<10;h1++)
  {
  
  for(m2=1;m2<6;m2++)
  {
    for(m1=1;m1<10;m1++)
	{
	  for(s=0;s<0x3C;s++)
	  {
			delay();
	  }
	   P0=arr[m1];
	}
	m1=0;
	P2=arr[m2];
 }
	m2=0;
 P3=arr[h1];
}
	h1=0;
P1=arr[h2];
}
}
