#include <STC12C5A60S2.h>
#include <intrins.h>


void delay1(unsigned int z)		
{
unsigned char a,b,c;
	for(c=z;c>0;c--)
	 for(b=21;b>0;b--)
        for(a=130;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void sendChar(unsigned char a)	 			
{
	SBUF = a;
	while(TI==0);
	TI=0;	
}

void sendString(unsigned char *s)		//uart通讯	
{
	while(*s!='\0')
	{
		sendChar(*s);
		s++;
	}
		
}
void ESPinit()
{	
	delay1(1000);
  sendString("AT+CWMODE=3\r\n");		
	delay1(1000);						
	sendString("AT+RST\r\n");			
	delay1(1000);
	sendString("AT+CIFSR\r\n");			
	delay1(1000);
	sendString("AT+CWJAP=\"TP-LINK_506\",\"5065688523\"\r\n");//连接5楼自习室WiFi
	delay1(15000);
	delay1(15000);
	delay1(15000);
	delay1(15000);
	delay1(15000);
}
