#ifndef _DRI_LCD_H_
#define _DRI_LCD_H_ 1

#include "board.h"
#define SET_RD SetBit(PORTB,1);
#define CLR_RD ClrBit(PORTB,1);

#define LCD_RST_0 ClrBit(PORTC,7);
#define LCD_RST_1 SetBit(PORTC,7);

#define LCDCS ClrBit(PORTB,0);
#define NONECS SetBit(PORTB,0);

#define SET_WR SetBit(PORTB,2);
#define CLR_WR ClrBit(PORTB,2);

#define SET_LCD_A0 SetBit(PORTB,3);
#define CLR_LCD_A0 ClrBit(PORTB,3);

extern __eeprom unsigned char ee_back_light_duty;
void LCD_init();
void LCD_wr_command(unsigned char command);
void LCD_wr_data(unsigned char datas);
void LCD_RAM_ADDRESS();
void LCD_display_datas(unsigned char datas);
void LCD_disdatatrans(unsigned char datas);
void LCD_dischar1616(unsigned char  __flash  *p_dis, unsigned char x, unsigned char y);
void LCD_dischar88 (unsigned char *dis_datas, unsigned char x, unsigned char y);
void LCD_dischar0811(unsigned char __flash * dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag);
void LCD_Clr();
void LCD_display_line(unsigned char y);
void WRITE16X16(unsigned char low,unsigned char high,unsigned char datas);
void LCD_display_single_line(unsigned char y);
void LCD_distring(unsigned char *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag);
void LCD_distring_V2(unsigned char __flash *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag);
void LCD_distring_ee(unsigned char __eeprom *dis_datas, unsigned char x, unsigned char y,unsigned char Reverse_flag);
unsigned char LCD_rd_data(void);
extern unsigned char Lcd_dis_data[];

unsigned char LCD_dischar(unsigned char c, unsigned char x, unsigned char y, unsigned char Reverse_flag);
unsigned char datatrans(unsigned char const __flash *datas,unsigned char bytenumber,unsigned char distance, unsigned char x);
void LCD_disstr_V3(unsigned char *str, unsigned char x, unsigned char y, unsigned char Reverse_flag);
void light_adj(void);
unsigned char byte_reverse(unsigned char data);

#endif


