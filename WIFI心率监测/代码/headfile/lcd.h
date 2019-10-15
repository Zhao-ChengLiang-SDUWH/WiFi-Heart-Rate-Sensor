#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
#include <STC12C5A60S2.h>
/**********************************
包含头文件
**********************************/


//---重定义关键词---//


/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P3^4;
sbit LCD1602_RS=P3^5;
sbit LCD1602_RW=P3^6;


void LcdWaitReady();
/**********************************
函数声明
**********************************/
/*在51单片机11.0592MHZ时钟下的延时函数*/
void delay(unsigned int n);
void LcdInit();
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(unsigned char com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(unsigned char dat);
/*LCD1602初始化子程序*/		
void LCD1602_DisplayOneCharOnAddr(unsigned char x,unsigned char y,unsigned char ucData);				  
void LcdSetCursor(unsigned char x , unsigned char y);
void LcdShowStr(unsigned char x,unsigned char y ,unsigned char *str);
void InitUART(void);
#endif
