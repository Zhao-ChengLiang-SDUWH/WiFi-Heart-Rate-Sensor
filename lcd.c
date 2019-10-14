
#include <intrins.h>
#include "lcd.h"
/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能		   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在11.0592MHZ晶振下
*******************************************************************************/

void Lcd1602_Delay1ms(unsigned char c)   
{
  unsigned char t;
  while(c--)
  {
    for (t=0;t<120;t++);
  }
    	
}

/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
void LcdWriteCom(unsigned char com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}

/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		    
void LcdWriteData(unsigned char dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}

/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}

void LcdSetCursor(unsigned char x , unsigned char y)
{
	unsigned char addr;
	if (y==0)
		addr=0x00+x;
	else
		addr=0x40+x;
	LcdWriteCom(addr|0x80);
}

void LcdShowStr(unsigned char x,unsigned char y ,unsigned char *str)
{
	LcdSetCursor(x,y);
	while(*str!='\0')
	{
		LcdWriteData(*str++);
	}
}

void LCD1602_DisplayOneCharOnAddr(unsigned char x,unsigned char y,unsigned char ucData)
{
	LcdSetCursor(x,y);   //光标位置
	LcdWriteData(ucData);	  //写入数据
}
void delay(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<100;j++);
}