
#include <STC12C5A60S2.h>
#include <AD.h>
#define ADC_POWER 0x80			//ADC POWER CONTROL BIT
#define ADC_FLAG 0x10			//ADC COMPLETE FLAG
#define ADC_START 0x08;			//ADC START CONTROL BIT
#define ADC_SPEEDLL 0x00		//540 CLOCKS
#define ADC_SPEEDL 0x20			//360 CLOCKS
#define ADC_SPEEDH 0x40			//180 CLOCKS
#define ADC_SPEEDHH 0x60		//90 CLOCKS
#define ADC_MASK 0x01





void ADC_init(unsigned char channel)
{
	P1ASF=ADC_MASK<<channel;	//enable PlusePin as ADC INPUT
	ADC_RES=0;	//clear former ADC result
	ADC_RESL=0;	//clear former ADC result
	AUXR1 |= 0x04;	//adjust the format of ADC result
	ADC_CONTR=channel|ADC_POWER|ADC_SPEEDLL|ADC_START;	//power on ADC and start conversion
}

unsigned int analogRead(unsigned char channel)
{
	unsigned int result;

	ADC_CONTR &=!ADC_FLAG;	//clear ADC FLAG
	result=ADC_RES;
	result=result<<8;
	result+=ADC_RESL;
	ADC_CONTR|=channel|ADC_POWER|ADC_SPEEDLL|ADC_START;
	return result;
}