/***********************************************************************************************
*	DRI_LCD.C
*	descreption: driver for LCD
*	autor	: David Wei
*	date	: May, 13, 2009
************************************************************************************************/
#ifndef ENABLE_BIT_DEFINITIONS
#define ENABLE_BIT_DEFINITIONS
#endif

#include <ioavr.h>
#include <inavr.h>
#include "DRI_LCD.H"
#include "DRI_LCDCHARACTERS.H"
#include "font.h"
#include "global_variable.h"

__eeprom unsigned char ee_back_light_duty = 128;
unsigned char Lcd_dis_data[10]={0,0,0,0,0,0,0,0,0,0};
void LCD_init()
{
	/*
		SET_RD;
    LCD_RST_0;
    delay_ms(5);
    LCD_RST_1;
    delay_us(200);

    LCD_wr_command(0xe2);   //system reset
    delay_ms(1);
    LCD_wr_command(0x31);   //set advanced program control
    LCD_wr_command(0x08);
    LCD_wr_command(0x2b);   // external power control
    LCD_wr_command(0x26); //set TC=-0.05%
    LCD_wr_command(0xA2);   //set line rate //A2:37.0Klps
    LCD_wr_command(0xe9);   //0XEb//set bias1/10  //ea//eb
    LCD_wr_command(0xf1);   //set com end
    LCD_wr_command(0x9f);   //set duty :1/160
    LCD_wr_command(0x81);   //set VLCD value
    LCD_wr_command(0xcb);   //VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)//94//7c????16.7V
    LCD_wr_command(0xc4);   //0XC4 //set LCD mapping control  //scan dirction com0~127
    LCD_wr_command(0x89);   //set RAM address control
    LCD_wr_command(0xd1);   // R_G_B
    LCD_wr_command(0xd5);   //4k color
    LCD_wr_command(0xc8);
    LCD_wr_command(0x16);
    LCD_wr_command(0x25);
    LCD_wr_command(0xad);  //0xad//display  on
    LCD_wr_command(0xad);   //0xad//display  on

    LCD_Clr();
    LCD_wr_command(0xf4);  //set oolumn start address
    LCD_wr_command(0x25);  //  start address
    LCD_wr_command(0xf6);  //  set column end address
    LCD_wr_command(0x5a);  //(0x4f+1)*3=240  5a   //90

    LCD_wr_command(0xf5);  //set row start address
    LCD_wr_command(0x00);  //start address=0x00
    LCD_wr_command(0xf7); //set row end address
    LCD_wr_command(0x9f); //row end address=9f
	*/
	DDRA = 0xFF;
	SET_RD;
	LCD_RST_0;
	delay_us(200);
	LCD_RST_1;
	delay_us(200);
	
	LCD_wr_command(0xe2);   //system reset
	delay_us(200);
	LCD_wr_command(0x31);   //set advanced program control
	LCD_wr_command(0x08);
	LCD_wr_command(0x2b);   // external power control
	LCD_wr_command(0x26); //set TC=-0.05%
	LCD_wr_command(0xA2);   //set line rate //A2:37.0Klps
	LCD_wr_command(0xe9);   //0XEb//set bias1/10  //ea//eb
	LCD_wr_command(0xf1);   //set com end
	LCD_wr_command(0x9f);   //set duty :1/160
	LCD_wr_command(0x81);   //set VLCD value
	LCD_wr_command(0xcb);   //VLCD=(CV0+Cpm*pm)*(1+(T-25)*CT%)//94//7c¡¡¡¡16.7V
	LCD_wr_command(0xc4);   //0XC4 //set LCD mapping control  //scan dirction com0~127
	LCD_wr_command(0x89);   //set RAM address control
	LCD_wr_command(0xd1);   // R_G_B
	LCD_wr_command(0xd5);   //4k color
	LCD_wr_command(0xc8);   //
	
	LCD_wr_command(0x16);
	LCD_wr_command(0x25);
	LCD_wr_command(0xad);   //0xad//display  on
	delay_us(200);
	
	LCD_Clr();
	LCD_wr_command(0xf4);  //set oolumn start address
	LCD_wr_command(0x25);  //  start address
	LCD_wr_command(0xf6);  //  set column end address
	LCD_wr_command(0x5a);  //(0x4f+1)*3=240  5a   //90
	
	LCD_wr_command(0xf5);  //set row start address
	LCD_wr_command(0x00);  //start address=0x00
	LCD_wr_command(0xf7); //set row end address
	LCD_wr_command(0x9f); //row end address=9f
}

//volatile unsigned char temp;
void LCD_wr_command(unsigned char command)
{
	LCDCS;
	CLR_LCD_A0;          //write command
	CLR_WR;
	PORTA = byte_reverse(command);
	SET_WR;
	SET_LCD_A0;
	NONECS;
}
void LCD_wr_data(unsigned char datas)
{
	LCDCS;
	CLR_WR;
	SET_LCD_A0;;          //write display datas
	PORTA = byte_reverse(datas);
	SET_WR;
	CLR_LCD_A0;
	NONECS;
}
///read 1 byte data from LCD
unsigned char LCD_rd_data(void)
{
	unsigned char temp;
	
	SET_WR;
	DDRA=0;
	LCDCS;
	SET_LCD_A0;
	CLR_RD;
	temp = byte_reverse(PORTA);
	SET_RD;
	CLR_WR;
	CLR_LCD_A0;
	NONECS;
	DDRA=0xff;
	return temp;
}

unsigned char byte_reverse(unsigned char data)
{
	/*
#ifndef FINAL_VERSION2
	for(i=0;i<8;i++)
	{
		if(GetBit(data,7-i))
			SetBit(temp,i);
	}
	return temp;
#else
	return data;
#endif
	*/
#ifdef FINAL_VERSION2
	return data;
#else
	unsigned char i;
	unsigned char temp = 0;
	
	for(i=0;i<8;i++)
	{
		if(GetBit(data,7-i))
			SetBit(temp,i);
	}
	return temp;
#endif
}

void LCD_RAM_ADDRESS()
{
	LCD_wr_command(0xf4);  //set oolumn start address
	LCD_wr_command(0x25);  //  start address
	LCD_wr_command(0xf6);  //  set column end address
	LCD_wr_command(0x5a);  //(0x4f+1)*3=240  5a   //90
	
	LCD_wr_command(0xf5);  //set row start address
	LCD_wr_command(0x00);  //start address=0x00
	LCD_wr_command(0xf7); //set row end address
	LCD_wr_command(0x9f); //row end address=9f
	LCD_wr_command(0x70);  //set row MSB address
	LCD_wr_command(0x60);  //set row LSB address
	LCD_wr_command(0x12);  //set column MSB address  //    12
	LCD_wr_command(0x05);  //set column LSB address  //37  05
	LCD_wr_command(0xf8); //inside mode
}

void LCD_display_datas(unsigned char datas)    //R-G-B=4-4-4
{
	unsigned int i,j;
	
	LCD_RAM_ADDRESS();
	
	for(i=0;i<160;i++)
	{
    for(j=0;j<81;j++)
      LCD_wr_data(datas);
	}
 }


/**************************************************************
*    name: 		LCD_disdatatrans
*    function: 	translate display data from 1Byte to 4Byte
*	 input:		1Byte unsigned char datas
*	 return:	an unsigned char pointer to point the 4 Byte datas
*
***************************************************************/
void LCD_disdatatrans(unsigned char datas)
{
unsigned char i=0;
for (i=0;i<4;i++)
	{
	if ((datas&0x80)==0)
		{
		Lcd_dis_data[i]=0;
		}
	else
		{
		Lcd_dis_data[i]=0xF0;
		}
	datas= datas<<1;
	if ((datas&0x80)!=0)
		{
		Lcd_dis_data[i]|=0x0F;
		}
	datas= datas<<1;
	}
}


/**************************************************************
*    name: 		LCD_dischar1616
*    function: 	display a 16*16 leble
*	 input:		16*16 lebel display, x and y coordinates
*	 return:	none
*
***************************************************************/
void LCD_dischar1616(unsigned char __flash * dis_datas, unsigned char x, unsigned char y)
{
    unsigned char i,j,k;
    j=0;
    for (j=0;j<16;j++)
    {
        LCD_wr_command(0x70+(y+j)/16);  //set row MSB address
        LCD_wr_command(0x60+(y+j)%16);  //set row LSB address
        LCD_wr_command(0x12+(x+5)/16);  //set column MSB address  //    12
        LCD_wr_command(0x00+(x+5)%16);  //set column LSB address  //37  05
        for(k=0;k<2;k++)
        {
            LCD_disdatatrans(*(dis_datas+k+2*j));	
            {
                for(i=0;i<4;i++)
                LCD_wr_data(Lcd_dis_data[i]);
            }
        }
        LCD_wr_data(0);
    }
}
/**************************************************************
*    name: 		LCD_dischar88
*    function: 	display a 88 leble
*	 input:		16*16 lebel display, x and y coordinates,,each x =3 line, each y=1 line
*	 return:	none
*
***************************************************************/

void LCD_dischar88 (unsigned char *dis_datas, unsigned char x, unsigned char y)
{
unsigned char j,i;
j=0;
for (j=0;j<8;j++)
{
	LCD_wr_command(0x70+((y+j)/16));  //set row MSB address
	LCD_wr_command(0x60+((y+j)%16));  //set row LSB address
	LCD_wr_command(0x12+((x+5)/16));  //set column MSB address  //    12
	LCD_wr_command((0x05+x)%16);  //set column LSB address  //37  05
	LCD_disdatatrans(*(dis_datas+j));	
	{
	for(i=0;i<4;i++)
	LCD_wr_data(Lcd_dis_data[i]);
	}
	LCD_wr_data(0);
}
}
/**************************************************************
*    name: 		LCD_Clr
*    function: 	display a char
*	 input:		1Byte unsigned char datas, x and y coordinates
*	 return:	none
*
***************************************************************/


void LCD_Clr()
{
	unsigned char i,j;
	LCD_RAM_ADDRESS();
	for(i=0;i<160;i++)
	{
		for(j=0;j<82;j++)
			LCD_wr_data(0x00);
	}
}

/**************************************************************
*    name: 		LCD_display_line
*    function: 	display a line on x y
*	 input:		x, y
*	 return:	none
*
***************************************************************/

void LCD_display_line(unsigned char y)
{
	unsigned char i;
	LCD_wr_command(0x70+(y/16));  //set row MSB address
	LCD_wr_command(0x60+(y%16));  //set row LSB address
	LCD_wr_command(0x12);  //set column MSB address  //    12
	LCD_wr_command(0x05);  //set column LSB address  //37  05
	for(i=0;i<80;i++)
		{
		LCD_wr_data(0xff);
		}
	LCD_wr_data(0x00);
}

void WRITE16X16(unsigned char low,unsigned char high,unsigned char datas)
{ unsigned char i,j;
  LCD_RAM_ADDRESS();
  for (i=0;i<high;i++)
	{
	 for(j=0;j<81;j++)
	 LCD_wr_data(0x00);
	}
  for (i=0;i<16;i++)
        {
	 for(j=0;j<low;j++)
	 LCD_wr_data(0x00);
	 for(j=0;j<8;j++)
	 LCD_wr_data(datas);
	 for(j=0;j<81-8-low;j++)
	 LCD_wr_data(0x00);
	}
  for (i=0;i<160-16-high;i++)
        {
	 for(j=0;j<81;j++)
	 LCD_wr_data(0x00);
	}
}


void LCD_display_single_line(unsigned char y)
{
	unsigned char i;
	LCD_wr_command(0x70+(y/16));  //set row MSB address
	LCD_wr_command(0x60+(y%16));  //set row LSB address
	LCD_wr_command(0x12);  //set column MSB address  //    12
	LCD_wr_command(0x05);  //set column LSB address  //37  05
	for(i=0;i<80;i++)
	{
			LCD_wr_data(0xff);
	}
	LCD_wr_data(0x00);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//ÏÔÊ¾1¸ö×Ö·û´®£¬x×ø±ê·¶Î§0~159  y×ø±ê·¶Î§0~159
void LCD_disstr_V3(unsigned char *str, unsigned char x, unsigned char y, unsigned char Reverse_flag)
{
	unsigned char i=0,j=0,k=0,c=0,number=0,flag=0,width=0;
	unsigned char data1,data2,move=0;
	unsigned int data16=0;
	while(*(str+number)!='\0')
		{
		number++;
		}
	for(i=0;i<16;i++)
	{
		LCD_wr_command(0x70+(y+i)/16);  //set row MSB address
		LCD_wr_command(0x60+(y+i)%16);  //set row LSB address
		
		LCD_wr_command(0x12+(x/3+5)/16);  //set column MSB address  //    12
		LCD_wr_command(0x00+(x/3+5)%16);   //set column LSB address  //37  05
		flag=0;
		move=0;
		for(j=0;j<number;j++)
		{	
			c=*(str+j);
			
			width=FontTrebuchetMS16_CharInfo[c-0x20].distance;
			
			if(FontTrebuchetMS16_CharInfo[c-0x20].bytes==2)
			{	data1=ASC[c-0x20][i*2];
				data2=ASC[c-0x20][i*2+1];
			}
			else
			{
				data1=ASC[c-0x20][i];
				data2=0;
			}
			data16=data1*256+data2;
			
			if (j==0)
				move=x%3;
			else
				move=0;
			if(GetBit(flag,0))
				move++;
			width+=move;
			data16=data16>>move;
			if(GetBit(flag,1))
				data16|=8000;
			flag=0;

			for(k=0;k<(width-width%2)/2;k++)
			{	
				if ((data16&0x8000)==0)
				{
					Lcd_dis_data[0]=0;
				}
				else
				{
					Lcd_dis_data[0]=0xF0;
				}
				data16= data16<<1;
				if ((data16&0x8000)!=0)
				{
					Lcd_dis_data[0]|=0x0F;
				}
				data16= data16<<1;
				if(Reverse_flag)
					LCD_wr_data(~Lcd_dis_data[0]);
				else
					LCD_wr_data(Lcd_dis_data[0]);
			}
			if((width%2)==1)
			{
				if((data16&0x8000)!=0)
					flag=3;
				else
					flag=1;
			}
		}
		if(Reverse_flag)
		LCD_wr_data(0xFF);
		else
				LCD_wr_data(0);

	}
}

//ÏÔÊ¾1¸ö×Ö·ûÐÂ×ø±ê±í·¶Î§0~159  y×ø±ê·¶Î§0~159
unsigned char LCD_dischar(unsigned char c, unsigned char x, unsigned char y, unsigned char Reverse_flag)
{
	unsigned char i,j,k;
	j=0;
	FONT_CHARINFO a=FontTrebuchetMS16_CharInfo[c-0x20];
	for (j=0;j<16;j++)
	{
		LCD_wr_command(0x70+(y+j)/16);  //set row MSB address
		LCD_wr_command(0x60+(y+j)%16);  //set row LSB address
		
		LCD_wr_command(0x12+(x/3+5)/16);  //set column MSB address  //    12
		LCD_wr_command(0x00+(x/3+5)%16);   //set column LSB address  //37  05

		k=datatrans(ASC[c-0x20]+j*a.bytes,a.bytes,a.distance,x);	

		for(i=0;i<k;i++)
		{
		    if(Reverse_flag == 1)
			LCD_wr_data(~Lcd_dis_data[i]);
		    else
			LCD_wr_data(Lcd_dis_data[i]);
		}
		LCD_wr_data(0);
	}
	return (FontTrebuchetMS16_CharInfo[c-0x20].distance+1);
}

unsigned char  datatrans(unsigned char const __flash *datas,unsigned char bytenumber,unsigned char distance, unsigned char x)
{
	unsigned char i=0,j=0,data1,data2;
	//	for(i=0;i++;i<(width+x%3)/2+(x%3)%2)
	unsigned int data16=0;
	data1=*datas;
	if(bytenumber==2)
	{
		datas++;
		data2=*datas;	
	}
	else
		data2=0;
	data16=data1*256+data2;
	data16=data16>>(x%3);

	for(i=0;i<((distance+x%3)/2+(distance+x%3)%2);i++)
	{
		j++;
		if ((data16&0x8000)==0)
		{
			Lcd_dis_data[i]=0;
		}
		else
		{
			Lcd_dis_data[i]=0xF0;
		}
		data16= data16<<1;
		if ((data16&0x8000)!=0)
		{
			Lcd_dis_data[i]|=0x0F;
		}
		data16= data16<<1;	
	}
	return j;

}

/**************************************************************
*    name: 		LCD_distring    //wang
*    function: 	display a string 
*	 input:		"string",x,y coordinates  
*	 return:	none
*
***************************************************************/

void LCD_distring(unsigned char *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag)
{
	unsigned char i = 0;
    
	do
	{
      LCD_dischar0811(ASC0811[*(dis_datas+i) - 32], x+2*i, y, Reverse_flag);
			i++;            
	}
	while((*(dis_datas + i)) != 0);
	//while((*(dis_datas + i)) != '\0');	
}

void LCD_distring_V2(unsigned char __flash *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag)
{
	unsigned char i = 0;

	g_temp = *dis_datas;
	do
	{
        LCD_dischar0811(ASC0811[*(dis_datas+i) - 32], x+2*i, y, Reverse_flag);
		i++;
	}
	while((*(dis_datas + i)) != '\0');

}

void LCD_distring_ee(unsigned char __eeprom *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag)
{
	unsigned char i = 0;
    
	do
	{
      LCD_dischar0811(ASC0811[*(dis_datas+i) - 32], x+2*i, y, Reverse_flag);
			i++;            
	}
	while((*(dis_datas + i)) != '\0');	
}

void LCD_dischar0811(unsigned char __flash * dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag)
{
	unsigned char i,j;
	j=0;
	for (j=0;j<11;j++)
	{
		LCD_wr_command(0x70+(y+j)/16);  //set row MSB address
		LCD_wr_command(0x60+(y+j)%16);  //set row LSB address
		LCD_wr_command(0x12+(x+5)/16);  //set column MSB address  //    12
		LCD_wr_command(0x00+(x+5)%16);   //set column LSB address  //37  05
        
		LCD_disdatatrans(*(dis_datas+j));	
		for(i=0;i<4;i++)
		{
		    if(Reverse_flag == 1)
				    LCD_wr_data(~Lcd_dis_data[i]);
		    else
			LCD_wr_data(Lcd_dis_data[i]);            
		}

		if(Reverse_flag)
			LCD_wr_data(255);
		else
			LCD_wr_data(0);
	}
}

void light_adj(void)
{
	if(get_key())
		{
			ee_back_light_duty += 4;
			if(ee_back_light_duty >= 252)
				ee_back_light_duty = 0;
			
			OCR2A=ee_back_light_duty;
			delay_ms(20);
		}
}