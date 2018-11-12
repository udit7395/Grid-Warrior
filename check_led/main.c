#include"sra.c"


void init_led()
{

DDRC=0xFF;
PORTC=0x00;
flickgrid(1);

DDRD=0xF0;
PORTD=0x0F;
flickgrid(2);

}

void flickgrid(int a)
{

if(a==1)
{
unsigned int i=0;

	for(i=0;i<5;i++)
	{
		LED=0xff;
		delay_millisec(100);
		LED=0x00;
		delay_millisec(100);
	}

}

if(a==2)
{
unsigned int i=0;

	for(i=0;i<5;i++)
	{
		PORTD=0b11000000;
		delay_millisec(100);
		PORTD=0x00;
		delay_millisec(100);
	}

}

}



void main()
{
port_init();

init_led();


}
