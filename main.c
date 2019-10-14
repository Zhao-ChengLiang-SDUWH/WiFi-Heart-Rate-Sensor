
#include "stdio.h"
#include <lcd.h>
#include <AD.h>
#include <ESP8266.h>
#include <st7735.h>
#define false 0
#define true 1
#define FOSC 11059200L		
#define BAUD 115200				
#define T0MS (65536-FOSC/12/500)		
#define MCU_STC12



void UART_init(void); 
void ADC_init(unsigned char channel);
void T0_init(void);

void UART_send(char dat);

unsigned char PulsePin = 0;       // Pulse Sensor purple wire connected to analog pin 0
//sbit blinkPin = P1^7;                // pin to blink led at each beat
//sbit fadePin = P2^3;                  // pin to do fancy classy fading blink at each beat
//sbit led1 = P2^1;
//sbit led2 = P2^2;
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin


// these variables are volatile because they are used during the interrupt service routine!
volatile unsigned int BPM;                   // used to hold the pulse rate
volatile unsigned int Signal;                // holds the incoming raw data
volatile unsigned int IBI = 600;             // holds the time between beats, must be seeded! 
volatile bit Pulse = false;     // true when pulse wave is high, false when it's low
volatile bit QS = false;        // becomes true when Arduoino finds a beat.
volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int Peak =512;                      // used to find peak in pulse wave, seeded
volatile int Trough = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 512;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile bit firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile bit secondBeat = false;      // used to seed rate array so we startup with reasonable BPM
static unsigned char order=0;
unsigned int HR[]={0,0,0,0,0,0,0,0,0,0};
unsigned char code ucForum0[]="Heart Rate ";
unsigned char code ucForum1[]="BPM:";
unsigned char DisBuff[4]={0};
unsigned char heart_rate1[]="{\"heart_rate1\":000}";
unsigned char heart_rate2[]="{\"heart_rate1\":00}";
unsigned char j=1;
unsigned char h=13;
void sys_init()
{
  UART_init();             //串口初始化
	ADC_init(PulsePin);              //AD转换
	LcdInit();        //LCD1602初始化
  ESPinit();        //ESP8266初始化
	#ifdef MCU_STC12
	P3M1 &= ~(1<<2),	P3M0 |=  (1<<2);	
  #endif
	lcd_initial(); // st7735 液晶屏初始化
	dsp_single_colour(WHITE);
	//清屏
	
}

void main(void)
{
	
  
	
		
	sys_init();
	showcoordinate();// 在液晶屏上显示坐标
	LcdShowStr(0,0,"Initializing");
	
	LcdShowStr(0,0,ucForum0);	//初始化
		
	LcdShowStr(0,1,ucForum1);	//
	T0_init();
	while(1)
	{
		
		LcdShowStr(5,1,DisBuff);  //在LCD1602上显示心率数值
		//Display_ASCII8X16(10,10,DisBuff);
		//Drawline(h,HR[j],h+10,HR[j+1]);
		
			
	}
  
}








void UART_init(void)
{
	 PCON &= 0x7f;  
   SCON = 0x50;  
   BRT = 0xFD;    
   AUXR |= 0x04;  
   AUXR |= 0x01;  
   AUXR |= 0x10;  
}
 
void T0_init(void){     
  
	TMOD |= 0x01;	//定时器0 模式1 每2ms中断
	TL0=T0MS;
	TH0=T0MS>>8;
	TR0=1;		
	ET0=1;		
  EA=1;                 
} 

void senddata1()
{
	
	sendString("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n");//
	delay1(50);
	sendString("AT+CIPMODE=1\r\n");  	
	delay1(50);
	sendString("AT+CIPSEND\r\n"); 		
	delay1(50);
	sendString("POST /devices/549699867/datapoints?type=3 HTTP/1.1\r\n");
	delay1(50);
	sendString("api-key:oFm0C6hnRqcKm6QtSFLc6nwzIZg=\r\n"); 
	delay1(50);
	sendString("Host:api.heclouds.com\r\n");  
	delay1(50);
	sendString("Content-Length:19\r\n"); 
	delay1(50);
	sendString("\r\n"); 
	delay1(100);
	sendString(heart_rate1);
	delay1(1000);
}
void senddata2()
{
	
	sendString("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n");//与中国移动onenet服务器建立tcp连接
	delay1(50);
	sendString("AT+CIPMODE=1\r\n");  	
	delay1(50);
	sendString("AT+CIPSEND\r\n"); 		//开始传输
	delay1(50);
	sendString("POST /devices/549699867/datapoints?type=3 HTTP/1.1\r\n");//设备id
	delay1(50);
	sendString("api-key:oFm0C6hnRqcKm6QtSFLc6nwzIZg=\r\n"); // apikey
	delay1(50);
	sendString("Host:api.heclouds.com\r\n");  
	delay1(50);
	sendString("Content-Length:18\r\n"); 
	delay1(50);
	sendString("\r\n"); 
	delay1(100);
	sendString(heart_rate2);
	delay1(1000);
}

void Timer0_rountine(void) interrupt 1
{                       
  int N;
	unsigned char i;
	
  unsigned int runningTotal = 0;                  

	EA=0; 	
	TL0=T0MS;
	TH0=T0MS>>8;				
  Signal = analogRead(PulsePin);              
  sampleCounter += 2;                        
  N = sampleCounter - lastBeatTime; 
	if(j>9)j=1;
    
  if(Signal < thresh && N > (IBI/5)*3){       
    if (Signal < Trough){                       
      Trough = Signal;                        
    }
  }

  if(Signal > thresh && Signal > Peak){        
    Peak = Signal;                             
  }                                       
  if (N > 250){                                  
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
      Pulse = true;                              

      IBI = sampleCounter - lastBeatTime;         
      lastBeatTime = sampleCounter;               

      if(secondBeat){                        
        secondBeat = false;                  
        for(i=0; i<=9; i++){             
          rate[i] = IBI;                      
        }
      }

      if(firstBeat){                        
        firstBeat = false;                   
        secondBeat = true;                   
        EA=1;                               
        return;                              
      }   



      for(i=0; i<=8; i++){                
        rate[i] = rate[i+1];                  
        runningTotal += rate[i];             
      }
     
      rate[9] = IBI;                          
      runningTotal += rate[9];                
      runningTotal /= 10;                     
      BPM = 60000/runningTotal;
			
			//put_bigpixel(h,Signal);
      
			if(BPM>150)BPM=150;			
			if(BPM<40)BPM=40;			
			DisBuff[2]   = BPM%10+48;
			DisBuff[1]   = BPM%100/10+48; 
			DisBuff[0]   = BPM/100+48;	   
			if(DisBuff[0]==48)
				DisBuff[0]=32;
			HR[j]=149-BPM;
			
			
			Drawline(h,HR[j-1],h+10,HR[j]);//画线
			j++;
			h=h+10;
			HR[0]=HR[9];
			if(BPM>100)
	 {
		 heart_rate1[15]=BPM/100+'0';
		 heart_rate1[16]=BPM%100/10+'0';
		 heart_rate1[17]=BPM%10+'0';
		
		 senddata1();

	 }
	 if (BPM<=100)
	 {
		 heart_rate2[15]=BPM/10+'0';
		 heart_rate2[16]=BPM%10+'0';
		
		 senddata2();//上传数据
		 
	 } 
      QS = true;                             
      
    }                       
  }

  if (Signal < thresh && Pulse == true){   

    Pulse = false;                         
    amp = Peak - Trough;                           
    thresh = amp/2 + Trough;                    
    Peak = thresh;                            
    Trough = thresh;
  }

  if (N > 2500){                           
    thresh = 512;                          
    Peak = 512;                               
    Trough = 512;                               
    lastBeatTime = sampleCounter;             
    firstBeat = true;                      
    secondBeat = false;                    
  }
  
	
	
	
	if(h>=150)
	{
		h=13;
		clean1();
	}
  
	EA=1;
	
}
