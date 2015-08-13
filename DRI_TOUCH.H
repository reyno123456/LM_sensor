#ifndef _DRI_TOUCH_H_
#define _DRI_TOUCH_H_ 1

#define SAMPLE_NUM 10

#define LCD_DCLK_0 ClrBit(PORTB,7)
#define LCD_DCLK_1 SetBit(PORTB,7)

#define LCD_DCST_0 ClrBit(PORTC,6)
#define LCD_DCST_1 SetBit(PORTC,6)

#define LCD_DIN_0 ClrBit(PORTB,5)
#define LCD_DIN_1 SetBit(PORTB,5)

#define IS_DOUT GetBit(PINB,6)

#define IS_PEN GetBit(PIND,5)


          
void delay(unsigned int time);
void TOUCH_WRITE1(unsigned char Comnand);
unsigned int TOUCH_READ1(void);
void TOUCH_CAIJI1(void);
void tp_line();
void change1();
void average1();
void mark1();
void caijicomp();
unsigned char TOUCH_adj();
extern unsigned int  cell_W,cell_H, vx,vy,avg_x,avg_y,xmin,ymin,xmax,ymax;
extern float	  x_para,y_para;
extern char	  Menu_status;	//alan
void TOUCH_getdata();
unsigned char TOUCH_getkeynumber();
extern __eeprom unsigned char ee_back_light_duty;
#endif