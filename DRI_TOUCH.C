/*****************************
   TEST TO 1N4249-TP
   CONTROLLER:  UC1698
   INTERFACE: 8bit/B\W FSTN
   SIZE: 160*160  DOTS
   PROGRAMMED: ANDY_Q
   DATE: 
 更改扫描方向
*****************************/
#ifndef ENABLE_BIT_DEFINITIONS
#define ENABLE_BIT_DEFINITIONS
#endif

#include <ioavr.h>
#include <inavr.h>
#include "DRI_LCD.H"
#include "DRI_TOUCH.H"
#include "global_variable.h"
#include "application.h"

//***********************************FUNCTION***************************************************
//#define uchar unsigned char
/*
#pragma vector = INT4_vect
__interrupt void TOUCH_INT(void)
{
CLI();
if((eventflag2_g&0xe0)==0)
	{
	BIT_SET(eventflag2_g,7);
	}

SEI();
}
*/
unsigned char  error;
/*********MAIN**********/

void delay(unsigned int t)
{
unsigned char i;
  while(--t)
  for(i=0;i<100;i++);
} 


//获取当前触摸屏按键的坐标(0,0)~(160,160)
void TOUCH_getdata()
{
	average1();
	/*
	if ((avg_x<xmin)||(avg_x>xmax)||(avg_y<ymin)||(avg_y>ymax))
	{
		avg_x=255;
		avg_y=255;
	}
	else
	{
		avg_x=160-(unsigned int)((avg_x-xmin)/x_para);
		avg_y=160-(unsigned int)((avg_y-ymin)/y_para);	
	}
	*/
}

void average1()
{
	unsigned int sum_x=0,sum_y=0;
	unsigned int position[SAMPLE_NUM][2];
	unsigned int temp;
	
	unsigned char i = 0;
	
	vx=vy=0;error=0;
	timer_flex_initial(500);
	
	while(Time_delay.timer_flex.time_out == 0)
	{
		if(IS_PEN == 0)
		{
			TOUCH_CAIJI1();
			delay_us(20);
		}
		
		position[i][0] = vx;
		position[i][1] = vy;
		
		if(++i >= SAMPLE_NUM) break;
	}
	 
	asm("nop");
	
	if( i == SAMPLE_NUM )
	{
		for(i=0;i<SAMPLE_NUM - 1;i++)
		{
			if(position[i][0] < position[i+1][0])
			{
				temp = position[i][0];
				position[i][0] = position[i+1][0];
				position[i+1][0] = temp;
				
				temp = position[i][1];
				position[i][1] = position[i+1][1];
				position[i+1][1] = temp;
			}
		}
		
		asm("nop");
		
		for(i=SAMPLE_NUM - 1;i > 0;i--)
		{
			if(position[i][0] > position[i-1][0])
			{
				temp = position[i][0];
				position[i][0] = position[i-1][0];
				position[i-1][0] = temp;
				
				temp = position[i][1];
				position[i][1] = position[i-1][1];
				position[i-1][1] = temp;
			}
		}
		
		asm("nop");
		
		for(i=1;i < SAMPLE_NUM - 1;i++)
		{
			sum_x += position[i][0];
			sum_y += position[i][1];
		}
		
		avg_x = sum_x/(SAMPLE_NUM - 2);
		avg_y = sum_y/(SAMPLE_NUM - 2);
	}
	else
	{
		avg_x = 0;
		avg_y = 0;
	}
}

void caijicomp()
{
	
	vx=vy=0;error=0;
	if(IS_PEN == 0)
	{
		delay_us(20);
		TOUCH_CAIJI1();  
	}
}

void TOUCH_CAIJI1(void)    
{
	LCD_DCLK_0;   
	LCD_DCST_0; 
	TOUCH_WRITE1(0Xd0);         
	vx = ((TOUCH_READ1()) & 0x0fff);    
	LCD_DCST_1;
	LCD_DCST_0;
	TOUCH_WRITE1(0X90);         
	vy = ((TOUCH_READ1()) & 0x0fff);  
	LCD_DCST_1;
}

void TOUCH_WRITE1(unsigned char command)
 { 
   unsigned char count;
   LCD_DCLK_0;
   for (count=0;count<8;count++)
      { 
        if (command&0x80)
		{LCD_DIN_1;}
	else
		{LCD_DIN_0;}
        command<<=1;   
        LCD_DCLK_1;// _nop_();
        delay_us(10);
        LCD_DCLK_0;// _nop_();
      }
 }

unsigned int TOUCH_READ1(void)
 {
  unsigned int  xy=0x0000;
  unsigned char i;            
	LCD_DCLK_0;
	for (i=0;i<12;i++)
	{    
 		xy<<=1;
		
		if (IS_DOUT) xy++;
			LCD_DCLK_1; 
			
		delay_us(1);
		LCD_DCLK_0;               
	}
	return  xy;    
 }
//校准触摸屏，并将校准值存入EEPROM
/*
unsigned char TOUCH_adj()
{
	float tempx, tempy;
	LCD_touchadj1();
	LCD_dischar1616(ICON1616[11], 48, 144);
	while(BIT_NCHK(eventflag2_g,5)) //flag in interrupt
		{NOP();}
	BIT_CLR(eventflag2_g,5);
	BIT_CLR(EIMSK, INT4);
	average1();
	delay_us(10);
	BIT_SET(EIFR,4);
	BIT_SET(EIMSK, INT4);
	BEEPON;
	xmin=avg_x;
	ymin=avg_y;
	LCD_touchadj2();
	LCD_dischar1616(ICON1616[9], 0, 0);
	
	while(BIT_NCHK(eventflag2_g,5))
		{NOP();}
	BIT_CLR(eventflag2_g,5);
	BIT_CLR(EIMSK, INT4);
	average1();
	delay_us(10);
	BIT_SET(EIFR,4);
	BIT_SET(EIMSK, INT4);
	BEEPON;
	xmax=avg_x;
	ymax=avg_y;
	cell_W=xmax-xmin;
	cell_H=ymax-ymin;
	LCD_Clr();
	if ((cell_W<1600)||(cell_W>1800)||(cell_H<1600)||(cell_H>1800))
		return 1;
	x_para = (float) (xmax-xmin);
	y_para = (float) (ymax-ymin);
	x_para = x_para/160.0;
	y_para = y_para/160.0;
	tempx=x_para*1000.0;
	tempy=y_para*1000.0;
	
	cell_W=(unsigned int)tempx;   //X坐标
	cell_H=(unsigned int)tempy;   //Y坐标
	
	LCD_Clr();

	__EEPUT(EEPROM_TOUCHADR,xmin/256);
	__EEPUT(EEPROM_TOUCHADR+1,xmin%256);
	__EEPUT(EEPROM_TOUCHADR+2,xmax/256);
	__EEPUT(EEPROM_TOUCHADR+3,xmax%256);
	__EEPUT(EEPROM_TOUCHADR+4,ymin/256);
	__EEPUT(EEPROM_TOUCHADR+5,ymin%256);
	__EEPUT(EEPROM_TOUCHADR+6,ymax/256);
	__EEPUT(EEPROM_TOUCHADR+7,ymax%256);

return 0;
}
*/
//获取触摸屏的按键值
/*
unsigned char TOUCH_getkeynumber()
{
unsigned int i;
TOUCH_getdata();
	for(i=PageList[screen_number_g].startkey;i<=PageList[screen_number_g].endkey;i++)
	{
	if ((avg_x>=KeyList[i].start_x)&&(avg_x<=KeyList[i].end_x)&&(avg_y>=KeyList[i].start_y)&&(avg_y<=KeyList[i].end_y))
		return KeyList[i].key_number;
	}
return 255;
}
*/