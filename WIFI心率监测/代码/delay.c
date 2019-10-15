#include <intrins.h>
#include <STC12C5A60S2.h>

void delay1us(unsigned char b)   //?? -0.005353009259us
{
    unsigned char a;
    for(a=b;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}


void delay1ms(unsigned char c)   //?? -0.018084490741us
{
unsigned char e,f,g;
    for(g=c;g>0;g--)
		{	for(f=21;f>0;f--)
			{
				for(e=130;e>0;e--)
					_nop_();
			}
		}  //if Keil,require use intrins.h
}
