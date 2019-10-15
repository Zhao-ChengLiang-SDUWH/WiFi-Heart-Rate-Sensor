#ifndef st7735_H_
#define st7735_H_
#define uchar unsigned char
#define uint unsigned int
#define RED  		0xf800
#define GREEN		0x07e0
#define BLUE 		0x001f
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   
#define GRAY1   0x8410      	
#define GRAY2   0x4208   

#define USE_LANDSCAPE//测试程序横竖屏切换，横屏请开启此宏，竖屏请屏蔽

	//P3M1.n,P3M0.n 	=00--->Standard,	01--->push-pull
	//					=10--->pure input,	11--->open drain



//---------------------------液晶屏接线说明-------------------------------------//
//接线前请参考液晶屏说明书第10页引脚定义
sbit bl        =P3^2;//接模块BL引脚，背光可以采用IO控制或者PWM控制，也可以直接接到高电平常亮
sbit scl       =P1^7;//接模块CLK引脚,接裸屏Pin9_SCL
sbit sda       =P1^5;//接模块DIN/MOSI引脚，接裸屏Pin8_SDA
sbit rs        =P1^2;//接模块D/C引脚，接裸屏Pin7_A0
sbit cs        =P1^3;//接模块CE引脚，接裸屏Pin12_CS
sbit reset     =P3^3;//接模块RST引脚，接裸屏Pin6_RES
//---------------------------End of液晶屏接线---------------------------------//

void Display_Desc();
void delay_ms(uint time);
void  Contrast_Adjust();
void  SPI_WriteData(uchar Data);
void  Lcd_WriteIndex(uchar Data);
void  Lcd_WriteData(uchar Data);
void  LCD_WriteData_16Bit(unsigned int Data);
void clean1();
void showcoordinate();
void Reset();
void lcd_initial();
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);
void PutPixel(uint x_start,uint y_start,uint color);
void put_bigpixel(uint x,uint y,uint color);
void dsp_single_colour(int color);
void Drawline(uint x1,uint y1,uint x2,uint y2);
uchar code Zk_ASCII8X16[];
void Output_Pixel(uint x,uint y);
void Display_ASCII8X16(uint x0,uint y0,uchar *s);
void Hline(uint y,uint x1,uint x2);
void Vline(uint x,uint y1, uint y2);
void Drawline(uint x1,uint y1,uint x2,uint y2);
