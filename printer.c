#include <ioavr.h>
#include <inavr.h>
#include <string.h>
#include "printer.h"
#include "global_variable.h"
#include "decode_scs_next.h"
#include "DRI_LCD.H"
#include "DRI_TOUCH.H"
#include "application.h"
#include <string.h>
#include "decode_scs.h"
#include "usart.h"
#include <math.h>
#include "dataflash.h"
#include "usb_command.h"
/*
#include "board.h"
#include "usart.h"
#include "decode_scs.h"
#include "stdlib.h"
#include "moudle_SCS.h"
#include "PIR.h"
#include "configuration.h"
#include "global_variable.h"
#include "IR.h"
#include "application.h"
#include "decode_scs_next.h"
#include "moudle_scs.h"
#include "string.h"
#include <intrinsics.h>
#include "function_service.h"
#include "font.h"
#include "DRI_TOUCH.h"
#include "printer.h"
#include "DRI_LCD.H"
*/
// 	1      2      3      A
//30 48  60 48  90 48  120 48
// 	4      5      6      B
//30 72  60 72  90 72  120 72
// 	7      8      9      C
//30 96  60 96  90 96  120 96
// 	E      0      F      D
//30 120 60 120 90 120 120 120
static struct S_location key_initial[16]=
{
	60,120,0,0, //0
	30,48,0,0,	//1	
	60,48,0,0,	//2
	90,48,0,0,	//3
	30,72,0,0,	//4
	60,72,0,0,	//5
	90,72,0,0,  //6
	30,96,0,0, 	//7
	60,96,0,0,	//8 
	90,96,0,0, 	//9 
	120,48,0,0,	//A
	120,72,0,0,	//B
	120,96,0,0,	//C
	120,120,0,0,//D
	30,120,0,0,	//E 
	90,120,0,0	//F 
};
unsigned char g_touched = 0;
#pragma vector = PCINT3_vect
__interrupt void TOUCH_INT(void)
{
	g_touched = 1;
}

void print_initial(void)
{
	// USART1 initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART1 Receiver: Off
	// USART1 Transmitter: On
	// USART1 Mode: Asynchronous
	// USART1 Baud Rate: 9600
	UCSR1A=0x00;
	//UCSR1B=0x08; //without interrupt
	UCSR1B=0x98; //interrupt
	UCSR1C=0x06;
	UBRR1H=0x00;
	UBRR1L=0x2F;
}

void print_out(unsigned char *data)
{
	do{
		if(*data == '^')
		{
			delay_ms(100);
		}
		while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
		UDR1 = *data;
	}while(*(++data));
}

void print_out_flash(unsigned char __flash *data)
{
	do{
		if(*data == '^')
		{
			delay_ms(100);
		}
		while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
		UDR1 = *data;
	}while(*(++data));
}

/*
__flash unsigned char label_1[] = "^XA~TA0~JSO^LT0^MMT^MNW^MTT^PON^PMN^LH0,0^JMA^PR2,2^MD30^JUS^LRN^CI0^XZ~DG001.GRF,00768,012,,:::::::::::::U0C,T024,T0H4,T082,S0102,S0401,S0C01,N03FE010H080,L01C0H0160H080,K0180,K0C0O040,J020,J0C0P020,I020Q0E0,I040N0407,I080O030,H010O0180,H020H038008018,H040070H014040,H080180H0206,H08040I0H40,01030J0A,05040I010,0210,0220,0240,04C0,05,:06,04,,::::::::::::::::::^XA^LL0120^PW296^FT160,64^XG001.GRF,1,1^FS^BY36,36^FT250,59^BXN,2,200,0,0,1";
__flash unsigned char label_2[] = "^FS^FO,26^FS^FT165,66^A0N,21,19^FH\\^FD";
__flash unsigned char label_3[] = "^FS^FO,31^FS^FT165,96^A0N,25,24^FH\\^FDID:";
__flash unsigned char label_4[] = "^FS^BY48,48^FT55,98^BXB,2,200,0,0,1^FH\\^FD";
__flash unsigned char label_5[] = "^FS^FO,22^FS^FT126,98^A0B,18,16^FH\\^FDID:";
__flash unsigned char label_6[] = "^FS^FO,21^FS^FT109,98^A0B,17,16^FH\\^FD";
__flash unsigned char label_7[] = "^FS^FO,21^FS^FT76,98^A0B,17,16^FH\\^FD";
__flash unsigned char label_8[] = "^FS^FO,22^FS^FT93,98^A0B,17,16^FH\\^FD";
__flash unsigned char label_9[] = " 007^FS^PQ1,0,1,Y^XZ^XA^ID000.GRF^FS^XZ";
void print_label(unsigned char *id,unsigned char *model, unsigned char *date, unsigned char *fireware_version, unsigned char *hard_version)
{
	unsigned char buffer_mode[3];
	unsigned char buffer[10];
	unsigned char model_number;
	
	init_USART1(9600);
	buffer_mode[0] = g_model[4];
	buffer_mode[1] = g_model[5];
	buffer_mode[2] = 0;
	
	model_number = StrToChar(buffer_mode);
	
		buffer[9] = 0;
		buffer[0] = *(hard_version);
		buffer[1] = *(hard_version + 1);
		
		buffer[2] = 32;
		buffer[3] = *fireware_version;
		buffer[4] = *(fireware_version+1);
		buffer[5] = *(fireware_version+2);
		buffer[6] = *(fireware_version+3);
		buffer[7] = *(fireware_version+4);
		buffer[8] = *(fireware_version+5);
	
		print_out_flash(label_1);
		print_out("^FH\\^FD");
		
		print_model(model_number);
		print_out("\\0D\\0AID:");
		print_out(id); //ok
		///////////////////      1      /////////////////////////////////////////
		print_out_flash(label_2); //Reyno 2009 12 03

		print_model(model_number);
		///////////////////      2      ////////////////////////////////////////
		print_out_flash(label_3);//ok
	
		print_out(id);
		///////////////////      3      ////////////////////////////////////////
		print_out_flash(label_4); //ok

		print_model(model_number);
		print_out("\\0D\\0A");
		print_out(date);
		print_out(" 007\\0D\\0A");

		print_out(buffer);
		print_out("\\0D\\0AID:");
		print_out(id);
		print_out_flash(label_5);
		print_out(id);
		print_out_flash(label_6);
		print_out(buffer);
		print_out_flash(label_7);
		print_model(model_number);
		print_out_flash(label_8);
		print_out(date);
		print_out_flash(label_9);
		
		init_USART1(115200);
}
*/

__flash unsigned char label_1[] = "^XA~TA0~JSO^LT0^MMT^MNW^MTT^PON^PMN^LH0,0^JMA^PR2,2^MD30^JUS^LRN^CI0^XZ~DG001.GRF,00768,012,,::::::T010,T068,T0H8,S0184,S0204,S0402,R01002,M080800280A,M0F0H07C001,K0180M01,K0C0O080,J020P080,J080P040,I020Q040,I040P01,H0180J080H0838,H020O0180,H060I0IF800C,H04001C0010040,H0800C0H028380,010040I0470,02030J0B80,02040I018,02080I028,0420,0440,H080,09,0A,:04,08,,::::::::::::::::::::::::^XA^LL0096^PW296^FT160,64^XG001.GRF,1,1^FS^BY36,36^FT247,46^BXN,2,200,0,0,1";
__flash unsigned char label_2[] = "^FS^FO,26^FS^FT164,62^A0N,21,19^FH\\^FD";
__flash unsigned char label_3[] = "^FS^FO,28^FS^FT164,89^A0N,23,24^FH\\^FDID:";
__flash unsigned char label_4[] = "^FS^BY48,48^FT54,94^BXB,2,200,0,0,1^FH\\^FD";
__flash unsigned char label_5[] = "^FS^FO,21^FS^FT125,94^A0B,17,16^FH\\^FDID:";
__flash unsigned char label_6[] = "^FS^FO,21^FS^FT107,94^A0B,17,16^FH\\^FD";
__flash unsigned char label_7[] = "^FS^FO,21^FS^FT72,94^A0B,17,16^FH\\^FD";
__flash unsigned char label_8[] = "^FS^FO,21^FS^FT89,94^A0B,17,16^FH\\^FD";
__flash unsigned char label_9[] = " 007^FS^PQ1,0,1,Y^XZ^XA^ID000.GRF^FS^XZ";
void print_label(unsigned char *id,unsigned char *model, unsigned char *date, unsigned char *fireware_version, unsigned char *hard_version)
{
	unsigned char buffer_mode[3];
	unsigned char buffer[10];
	unsigned char model_number;
	
	init_USART1(9600);
	buffer_mode[0] = g_model[4];
	buffer_mode[1] = g_model[5];
	buffer_mode[2] = 0;
	
	model_number = StrToChar(buffer_mode);
	
		buffer[9] = 0;
		buffer[0] = *(hard_version);
		buffer[1] = *(hard_version + 1);
		
		buffer[2] = 32;
		buffer[3] = *fireware_version;
		buffer[4] = *(fireware_version+1);
		buffer[5] = *(fireware_version+2);
		buffer[6] = *(fireware_version+3);
		buffer[7] = *(fireware_version+4);
		buffer[8] = *(fireware_version+5);
	
		print_out_flash(label_1);
		print_out("^FH\\^FD");
		
		print_model(model_number);
		print_out("\\0D\\0AID:");
		print_out(id); //ok
		///////////////////      1      /////////////////////////////////////////
		print_out_flash(label_2); //Reyno 2009 12 03

		print_model(model_number);
		///////////////////      2      ////////////////////////////////////////
		print_out_flash(label_3);//ok
	
		print_out(id);
		///////////////////      3      ////////////////////////////////////////
		print_out_flash(label_4); //ok

		print_model(model_number);
		print_out("\\0D\\0A");
		print_out(date);
		print_out(" 007\\0D\\0A");

		print_out(buffer);
		print_out("\\0D\\0AID:");
		print_out(id);
		print_out_flash(label_5);
		print_out(id);
		print_out_flash(label_6);
		print_out(buffer);
		print_out_flash(label_7);
		print_model(model_number);
		print_out_flash(label_8);
		print_out(date);
		print_out_flash(label_9);
		
		init_USART1(115200);
}


void print_model(unsigned char data)
{
	unsigned char brand;

	switch(g_model[2])
	{
		case '1':
			brand = 1;
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '1';
		break;
		
		case '2':
			brand = 2;
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '2';
		break;
		
		default: 
			brand = 2;
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '2';
		break;
	}
	
	stru_sensor.device_model[0] = g_model[0];
	stru_sensor.device_model[1] = g_model[4];
	stru_sensor.device_model[2] = g_model[5];
	
		if(brand == 2)
		{
			switch(data)
			{
				case 0x20:
					print_out("048820");
				break;
				
				case 0x21:
					print_out("048821");
				break;
				
				case 0x22:
					print_out("048822");
				break;
				
				case 0x23:
					print_out("048823");
				break;
				
				case 0x24:
					print_out("048824");
				break;
				
				case 0x25:
					print_out("048825");
				break;
				
				case 0x26:
					print_out("048826");
				break;
				
				case 0x27:
					print_out("048829");
				break;
				
				case 0x28:
					print_out("048828");
				break;
				
				case 0x29:
					print_out("048831");
				break;
				
				case 0x30:
					print_out("048830");
					stru_sensor.device_model[1] = '2';
					stru_sensor.device_model[2] = 'A';
				break;
				
				default:break;
			}
		}
		else if(brand == 1)
		{
			switch(data)
			{
				case 0x20:
					print_out("BMSE3001");
				break;
				
				case 0x21:
					print_out("BMSE3002");
				break;
				
				case 0x22:
					print_out("BMSE3003");
				break;
				
				case 0x23:
					print_out("BMSE2005");
				break;
				
				case 0x24:
					print_out("BMSE2001");
				break;
				
				case 0x25:
					print_out("BMSE2002");
				break;
				
				case 0x26:
					print_out("BMSE2003");
				break;
				
				case 0x27:
					print_out("BMSE2004");
				break;
				
				case 0x28:
					print_out("BMSE3005");
				break;
				
				case 0x29:
					print_out("BMSE2007");
				break;
				
				case 0x30:
					print_out("BMSE2006");
					stru_sensor.device_model[1] = '2';
					stru_sensor.device_model[2] = 'A';
				break;
				
				default:break;
			}
		}
}

void model_convert(void)
{
	unsigned char model_number;
	unsigned char buffer_mode[3];
	
	buffer_mode[0] = g_model[4];
	buffer_mode[1] = g_model[5];
	buffer_mode[2] = 0;
	
	model_number = StrToChar(buffer_mode);
	switch(g_model[2])
	{
		case '1':
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '1';
		break;
		
		case '2':
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '2';
		break;
		
		default: 
			stru_sensor.brand[0] = '0';
			stru_sensor.brand[1] = '2';
		break;
	}
	
	stru_sensor.device_model[0] = g_model[0];
	stru_sensor.device_model[1] = g_model[4];
	stru_sensor.device_model[2] = g_model[5];
	
	switch(model_number)
	{
		case 0x30:
			stru_sensor.device_model[1] = '2';
			stru_sensor.device_model[2] = 'A';
		break;
		
		default:break;
	}
}
	
void external_interrupt_initial(void)
{
	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// INT2: Off
	// Interrupt on any change on pins PCINT0-7: Off
	// Interrupt on any change on pins PCINT8-15: Off
	// Interrupt on any change on pins PCINT16-23: Off
	// Interrupt on any change on pins PCINT24-31: On
	EICRA=0x00;
	EIMSK=0x00;
	PCMSK3=0x20;
	PCICR=0x08;
	PCIFR=0x08;
}

static unsigned long int base = 150, top = 1880;
static struct S_location key[16];
void key_parameter_initial(void)
{
	unsigned char i;
	static unsigned long int weigth;
	static unsigned long int height;
	
	weigth = (top - base) * 30 /160;
	height = (top - base) * 34 /160;
	
	weigth -= 150;
	height -= 150;
	
	for(i=0;i<16;i++)
	{
		key[i].x1 = (top - base) * (key_initial[i].x1+3) / 160 - weigth/2;
		key[i].y1 = (top - base) * (key_initial[i].y1+5) / 160 - height/2;
		key[i].x2 = key[i].x1 + weigth;
		key[i].y2 = key[i].y1 + height;
	}
	asm("nop");
}

unsigned int cur_x,cur_y;
unsigned char get_touch_key(void)
{
	unsigned char i;

	if((avg_x > base && avg_x <top) && (avg_y > base && avg_y < top))
	{
		cur_x = top - avg_x;
		cur_y = top - avg_y;
		asm("nop");
	}
	
	for(i=0;i<16;i++)
	{
		if(cur_x > key[i].x1 && cur_x < key[i].x2)
		{
			if(cur_y > key[i].y1 && cur_y <key[i].y2)
			{
				return i;
			}
		}
	}
	
	if(cur_x > (key[0].x1+key[0].x2)/2 && cur_x < (key[15].x1+key[15].x2)/2 && cur_y > key[15].y2 && Menu_status == 0x02)	//alan
		return 19;
	else if(cur_x > key[13].x1 && cur_y > key[13].y2)
		return 16;
	else if(cur_x < key[14].x2 && cur_y > key[14].y2)
		return 17;
	
	//if(cur_x > key[0].x1 && cur_x < key[0].x2 && cur_y > key[0].y2 && Menu_status == 0x02)		//alan
	//	return 18;
	
	if(cur_x > (key[0].x1+key[0].x2)/2 && cur_x < (key[15].x1+key[15].x2)/2 && cur_y > key[15].y2 && Menu_status == 0x02)	//alan
		return 19;
	
	return 0xFF;
}


unsigned char get_touch_menu_00(void)
{
	if((avg_x > base && avg_x <top) && (avg_y > base && avg_y < top))
	{
		cur_x = top - avg_x;
		cur_y = top - avg_y;
		asm("nop");
	}
	
	if(cur_y > 108 * 5 && cur_y < 108 * 6)
	{
		return 0;
	}
	else if(cur_y > 108 * 8 && cur_y < 108 * 9)
	{
		return 1;
	}
	else if(cur_y > 108 * 11 && cur_y < 108 * 12)
	{
		return 2;
	}
	
	return 0xFF;
}

volatile unsigned char g_buffer_tx[17] = "D000010200000000";
void id_setting(unsigned char *data)
{
	//volatile unsigned char buffer_tx[17] = "D000010200000000";
	//volatile unsigned char buffer2_tx[17] = "D000010500000000";
	g_buffer_tx[7] = '2';
	strncpy(&g_buffer_tx[8],data,9);
	//strncpy(&buffer2_tx[8],data,9);
	
	send_frame_pp_ext_broad(g_buffer_tx,500);
	
	g_buffer_tx[7] = '5';
	send_frame_pp_ext_broad(g_buffer_tx,200);
}

void id_setting_ee(unsigned char __eeprom *data)
{
	//volatile unsigned char buffer_tx[17] = "D000010200000000";
	//volatile unsigned char buffer2_tx[17] = "D000010500000000";
	g_buffer_tx[7] = '2';
	strncpy(&g_buffer_tx[8],data,9);
	//strncpy(&buffer2_tx[8],data,9);
	
	send_frame_pp_ext_broad(g_buffer_tx,500);
	
	g_buffer_tx[7] = '5';
	send_frame_pp_ext_broad(g_buffer_tx,200);
}

void touch_key_blink(unsigned char index,unsigned int ms)
{
	switch(index)
	{
	case 0:
		LCD_distring("0", 20, 120, 1);
		delay_ms(ms);
		LCD_distring("0", 20, 120, 0);
		break;
		
	case 1:
		LCD_distring("1", 10, 48, 1);
		delay_ms(ms);
		LCD_distring("1", 10, 48, 0);
		break;
		
	case 2:
		LCD_distring("2", 20, 48, 1);
		delay_ms(ms);
		LCD_distring("2", 20, 48, 0);
		break;
		
	case 3:
		LCD_distring("3", 30, 48, 1);
		delay_ms(ms);
		LCD_distring("3", 30, 48, 0);
		break;
		
	case 4:
		LCD_distring("4", 10, 72, 1);
		delay_ms(ms);
		LCD_distring("4", 10, 72, 0);
		break;
		
	case 5:
		LCD_distring("5", 20, 72, 1);
		delay_ms(ms);
		LCD_distring("5", 20, 72, 0);
		break;
		
	case 6:
		LCD_distring("6", 30, 72, 1);
		delay_ms(ms);
		LCD_distring("6", 30, 72, 0);
		break;
		
	case 7:
		LCD_distring("7", 10, 96, 1);
		delay_ms(ms);
		LCD_distring("7", 10, 96, 0);
		break;
		
	case 8:
		LCD_distring("8", 20, 96, 1);
		delay_ms(ms);
		LCD_distring("8", 20, 96, 0);
		break;
		
	case 9:
		LCD_distring("9", 30, 96, 1);
		delay_ms(ms);
		LCD_distring("9", 30, 96, 0);
		break;
		
	case 10:
		LCD_distring("A", 40, 48, 1);
		delay_ms(ms);
		LCD_distring("A", 40, 48, 0);
		break;
		
	case 11:
		LCD_distring("B", 40, 72, 1);
		delay_ms(ms);
		LCD_distring("B", 40, 72, 0);
		break;
		
	case 12:
		LCD_distring("C", 40, 96, 1);
		delay_ms(ms);
		LCD_distring("C", 40, 96, 0);
		break;
		
	case 13:
		LCD_distring("D", 40, 120, 1);
		delay_ms(ms);
		LCD_distring("D", 40, 120, 0);
		break;
		
	case 14:
		LCD_distring("E", 10, 120, 1);
		delay_ms(ms);
		LCD_distring("E", 10, 120, 0);
		break;
		
	case 15:
		LCD_distring("F", 30, 120, 1);
		delay_ms(ms);
		LCD_distring("F", 30, 120, 0);
		break;
		
	case 16:
		LCD_distring("Confirm", 36, 140, 1);
		delay_ms(ms);
		LCD_distring("Confirm", 36, 140, 0);
		break;
		
	case 17:
		LCD_distring("Delete", 2, 140, 1);
		delay_ms(ms);
		LCD_distring("Delete", 2, 140, 0);
		break;
	//case 18:
	//	LCD_distring("Retry", 18, 140, 1);
	//	delay_ms(ms);
	//	LCD_distring("Retry", 18, 140, 0);
	//	break;
	case 19:
		LCD_distring("Next", 22, 140, 1);
		delay_ms(ms);
		LCD_distring("Next", 22, 140, 0);
		break;	
		
	default:break;
	}
}

void touch_key_blink_01(unsigned char index,unsigned int ms)
{
	switch(index)
	{
	case 0:
		LCD_distring("0", 20, 120, 1);
		delay_ms(ms);
		LCD_distring("0", 20, 120, 0);
		break;
		
	case 1:
		LCD_distring("1", 10, 48, 1);
		delay_ms(ms);
		LCD_distring("1", 10, 48, 0);
		break;
		
	case 2:
		LCD_distring("2", 20, 48, 1);
		delay_ms(ms);
		LCD_distring("2", 20, 48, 0);
		break;
		
	case 3:
		LCD_distring("3", 30, 48, 1);
		delay_ms(ms);
		LCD_distring("3", 30, 48, 0);
		break;
		
	case 4:
		LCD_distring("4", 10, 72, 1);
		delay_ms(ms);
		LCD_distring("4", 10, 72, 0);
		break;
		
	case 5:
		LCD_distring("5", 20, 72, 1);
		delay_ms(ms);
		LCD_distring("5", 20, 72, 0);
		break;
		
	case 6:
		LCD_distring("6", 30, 72, 1);
		delay_ms(ms);
		LCD_distring("6", 30, 72, 0);
		break;
		
	case 7:
		LCD_distring("7", 10, 96, 1);
		delay_ms(ms);
		LCD_distring("7", 10, 96, 0);
		break;
		
	case 8:
		LCD_distring("8", 20, 96, 1);
		delay_ms(ms);
		LCD_distring("8", 20, 96, 0);
		break;
		
	case 9:
		LCD_distring("9", 30, 96, 1);
		delay_ms(ms);
		LCD_distring("9", 30, 96, 0);
		break;
		
	case 16:
		LCD_distring("Confirm", 36, 140, 1);
		delay_ms(ms);
		LCD_distring("Confirm", 36, 140, 0);
		break;
		
	case 17:
		LCD_distring("Delete", 2, 140, 1);
		delay_ms(ms);
		LCD_distring("Delete", 2, 140, 0);
		break;
		
	//case 18:
	//	LCD_distring("Retry", 12, 140, 1);
	//	delay_ms(ms);
	//	LCD_distring("Retry", 12, 140, 0);
	//	break;
	case 19:
		LCD_distring("Next", 22, 140, 1);
		delay_ms(ms);
		LCD_distring("Next", 22, 140, 0);
		break;	
		
	default:break;
	}
}

void touch_key_blink_02(unsigned char index,unsigned int ms)
{
	switch(index)
	{
	case 0:
		LCD_distring("0", 20, 120, 1);
		delay_ms(ms);
		LCD_distring("0", 20, 120, 0);
		break;
		
	case 1:
		LCD_distring("1", 10, 48, 1);
		delay_ms(ms);
		LCD_distring("1", 10, 48, 0);
		break;
		
	case 2:
		LCD_distring("2", 20, 48, 1);
		delay_ms(ms);
		LCD_distring("2", 20, 48, 0);
		break;
		
	case 3:
		LCD_distring("3", 30, 48, 1);
		delay_ms(ms);
		LCD_distring("3", 30, 48, 0);
		break;
		
	case 4:
		LCD_distring("4", 10, 72, 1);
		delay_ms(ms);
		LCD_distring("4", 10, 72, 0);
		break;
		
	case 5:
		LCD_distring("5", 20, 72, 1);
		delay_ms(ms);
		LCD_distring("5", 20, 72, 0);
		break;
		
	case 6:
		LCD_distring("6", 30, 72, 1);
		delay_ms(ms);
		LCD_distring("6", 30, 72, 0);
		break;
		
	case 7:
		LCD_distring("7", 10, 96, 1);
		delay_ms(ms);
		LCD_distring("7", 10, 96, 0);
		break;
		
	case 8:
		LCD_distring("8", 20, 96, 1);
		delay_ms(ms);
		LCD_distring("8", 20, 96, 0);
		break;
		
	case 9:
		LCD_distring("9", 30, 96, 1);
		delay_ms(ms);
		LCD_distring("9", 30, 96, 0);
		break;
		
	case 16:
		LCD_distring("  PnG ", 36, 140, 1);
		delay_ms(ms);
		LCD_distring("  PnG ", 36, 140, 0);
		break;
		
	case 17:
		LCD_distring("Delete", 2, 140, 1);
		delay_ms(ms);
		LCD_distring("Delete", 2, 140, 0);
		break;
		
	//case 18:
	//	LCD_distring("Retry", 12, 140, 1);
	//	delay_ms(ms);
	//	LCD_distring("Retry", 12, 140, 0);
	//	break;
	case 19:
		LCD_distring("Next", 22, 140, 1);
		delay_ms(ms);
		LCD_distring("Next", 22, 140, 0);
		break;	
		
	default:break;
	}
}

void touch_key_blink_03(unsigned char index,unsigned int ms)
{
	switch(index)
	{
		case 16:
			LCD_distring("  PnG ", 36, 140, 1);
			delay_ms(ms);
			LCD_distring("  PnG ", 36, 140, 0);
		break;
		
		default:break;
	}
}

__flash const unsigned char calibration[] = "Calibration Station";
__flash const unsigned char Delivery[] = "Delivery Station";
__flash const unsigned char Test[] = "Test Functionality";
void menu_00(void)
{
	LCD_distring(__DATE__, 28, 0, 0);
	LCD_distring(__TIME__, 28,12, 0);
	LCD_distring_V2(calibration, 8, 50, 0);
//#ifdef FINAL_VERSION2
	LCD_distring_V2(Delivery, 10, 80, 0);
//#endif
	LCD_distring_V2(Test, 8, 110, 0);
}

void menu_01(void)
{
	unsigned char temp = 0;
	unsigned char col = 24;
	unsigned char buffer[3];
	static unsigned int ui_lux;
	static unsigned char lux_high;
	static unsigned char lux_low;
	unsigned char buffer_tx[17] = "D200014210000000";
	unsigned int temp_int;
	
	LCD_distring_V2(calibration, 8, 4, 0);
	LCD_distring("     Lux:", 0, 24, 0);
	//LCD_distring("123456789012345678901234567", 0, 38, 0);
	LCD_distring("1    2    3     ", 10, 48, 0);
	LCD_distring("4    5    6     ", 10, 72, 0);
	LCD_distring("7    8    9     ", 10, 96, 0);
	LCD_distring("     0          ", 10, 120, 0);
	LCD_distring("Delete", 2, 140, 0);
	LCD_distring("Confirm", 36, 140, 0);
	
	timer_flex2_initial(500);
	g_lux[0] = '0';
	g_lux[1] = '0';
	g_lux[2] = '0';
	g_lux[3] = '0';
	g_lux[4] = 0;
	
	while(1)
	{
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		if(IS_PEN == 0)
		{
			TOUCH_getdata();
			temp_int = get_touch_key();
			touch_key_blink_01(temp_int,100);
			
			if(temp_int <= 9 || temp_int == 16 || temp_int == 17)
			{
				if(temp_int <= 9)
				{
					if(col >= 24 & col< 24 + 8)
					{
						buffer[0] = 48 + temp_int;
						buffer[1] = 0;
						LCD_distring(buffer,col,24,0);
						switch(col)
						{
							case 24:
								g_lux[0] = temp_int;
							break;
							
							case 26:
								g_lux[1] = temp_int;
							break;
							
							case 28:
								g_lux[2] = temp_int;
							break;
							
							case 30:
								g_lux[3] = temp_int;
							break;
							
							default:break;
						}
						
						col += 2;
					}
				}
				else if(temp_int == 16)		// "Confirm"
				{
					if(col == 32)
					{
						
						ui_lux = 1000 * (unsigned int)g_lux[0] + 100 * (unsigned int)g_lux[1] + 10 * (unsigned int)g_lux[2] + g_lux[3];
						lux_high = ui_lux >> 8;
						lux_low = ui_lux;
						
						send_frame_pp_ext_broad("D200014214000001",2000);
						strncpy(buffer_tx,"D200014210000000",17);
						CharToStr(lux_high,buffer);
						buffer_tx[12] = buffer[0];
						buffer_tx[13] = buffer[1];
						CharToStr(lux_low,buffer);
						buffer_tx[14] = buffer[0];
						buffer_tx[15] = buffer[1];
						send_frame_pp_ext_broad(buffer_tx,2000);
						send_frame_pp_ext_broad("D2000142140000FF",200);
						
						col = 24;
						g_lux[0] = 0;
						g_lux[1] = 0;
						g_lux[2] = 0;
						g_lux[3] = 0;
						LCD_distring("     ",col,24,0);
						asm("nop");
					}
				}
				else if(temp_int == 17)		// "Delete"
				{
					if(col >24)
					{
						LCD_distring(" ",col,24,0);
						col -= 2;
					}
				}
			}
		}
		
		if(Time_delay.timer_flex2.time_out == 1)
		{
			temp = ~temp;
			timer_flex2_initial(500);
			if(temp)
				LCD_distring("_",col,24,0);
			else
				LCD_distring(" ",col,24,0);
		}
		
		light_adj();
	}
}

//extern char	  Menu_status;	//alan
void menu_02(void)
{
	unsigned char i;
	unsigned char temp = 0;
	unsigned char col = 24;
	unsigned char buffer[2];
	unsigned int temp_int;
	unsigned char g_id[9];
	unsigned char year_week[6] = "00W00";
	unsigned char buffer_tx[17];
	unsigned char buffer_received[9];
	unsigned long int id_long;
	
	buffer_received[8] = 0;
	
	
	Menu_status = 0x02;		//alan
	
	year_week[0] = g_year[0];
	year_week[1] = g_year[1];
	
	year_week[3] = g_week[0];
	year_week[4] = g_week[1];
	
	LCD_distring("Delivery Station", 12, 4, 0);
	LCD_distring("Input ID:", 0, 24, 0);
	LCD_distring("   Infor:", 0, 36, 0);
	//LCD_distring("123456789012345678901234567", 0, 38, 0);
	LCD_distring("1    2    3    A", 10, 48, 0);
	LCD_distring("4    5    6    B", 10, 72, 0);
	LCD_distring("7    8    9    C", 10, 96, 0);
	LCD_distring("E    0    F    D", 10, 120, 0);
	LCD_distring("Delete", 2, 140, 0);
	//LCD_distring("Retry", 12, 140, 0);		//alan		18
	LCD_distring("Next", 22, 140, 0);			//alan		19
	LCD_distring("Confirm", 36, 140, 0);
	
	timer_flex2_initial(500);
	
	ee_printed_id[8] = 0;
	for(i=0;i<8;i++)
	{
		g_id[i] = ee_printed_id[i];
	}
	LCD_distring_ee(ee_printed_id,24,24,0);
	col = 40;
	
	while(1)
	{
		while(decode_SCS());
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		
		switch(state.main_state)
		{
			case FINAL_ID_STEP1:
				id_setting(g_id);
				state.main_state = FINAL_ID_STEP2;
			break;
			
			case FINAL_ID_STEP2:
				if(g_asc_reception_buffer[0] == 0xD0 && g_asc_reception_buffer[3] == 0x04)
				{
					strncpy(&g_reception_buffer[8],buffer_received,8);
					buffer_received[8] = 0;
					if(strcmp(buffer_received,g_id))
					{
						state.main_state = FINAL_ID_STEP3;
					}
				}
			break;
			
			case FINAL_ID_STEP3:
				delay_ms(200);
				strncpy(buffer_tx,"D200014280000000",17);
				strncpy(&buffer_tx[10],g_model,6);
				if(g_model[4] == '3' && g_model[5] == '0')
				{
					buffer_tx[14] = '2';
					buffer_tx[15] = 'A';
				}
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY); //brand & production line
				state.main_state = FINAL_ID_STEP4;
			break;
			
			case FINAL_ID_STEP4:
				if(g_asc_reception_buffer[0]  == 0xD2 && g_asc_reception_buffer[3] == 0x34)
				{
					if(g_asc_reception_buffer[4] == 0x80)
					{
						if(g_reception_buffer[10] == g_model[0] && g_reception_buffer[14] == g_model[4] && g_reception_buffer[15] == g_model[5])
						{
							if(g_reception_buffer[12] == g_model[2] && g_reception_buffer[13] == g_model[3])
							{
								state.main_state = FINAL_ID_STEP5;
							}
						}
						else
						{
							if(g_reception_buffer[10] == g_model[0])
							{
								if(g_asc_reception_buffer[7] == 0x2A && g_model[4] == '3' && g_model[5] == '0')
								{
									state.main_state = FINAL_ID_STEP5;
								}
							}
						}
					}
				}
			break;
			
			case FINAL_ID_STEP5:
				delay_ms(200);
				strncpy(buffer_tx,"D200014282000000",17);
				buffer_tx[10] = g_hard[0];
				buffer_tx[11] = g_hard[1];
				buffer_tx[12] = g_year[0];
				buffer_tx[13] = g_year[1];
				buffer_tx[14] = g_week[0];
				buffer_tx[15] = g_week[1];
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				state.main_state = FINAL_ID_STEP6;
			break;
			
			case FINAL_ID_STEP6:
				if(g_asc_reception_buffer[0]  == 0xD2 && g_asc_reception_buffer[3] == 0x34)
				{
					if(g_asc_reception_buffer[4] == 0x82)
					{
						if(g_reception_buffer[10] == g_hard[0] && g_reception_buffer[11] == g_hard[1])
						{
							if(g_reception_buffer[12] == g_year[0] && g_reception_buffer[13] == g_year[1] && g_reception_buffer[14] == g_week[0] && g_reception_buffer[15] == g_week[1])
							{
								send_frame_pp_ext_broad("D200014385000000",TRANS_DELAY);
								state.main_state = FINAL_ID_STEP7;
							}
						}
					}
				}
			break;
			
			case FINAL_ID_STEP7:
				if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x85)
				{
					for(i=0;i<6;i++)
					{
						stru_sensor.gateway_version[i] = g_reception_buffer[10 + i];
					}
					state.main_state = FINAL_ID_STEP8;
				}
			break;
			
			case FINAL_ID_STEP8:
#ifdef FINAL_VERSION2
				model_convert();
				input_to_stru(g_id);
				if(write_flash(0,stru_sensor) == 0)
				{
					print_label(g_id,g_model,year_week,g_soft,g_hard);
					
					for(i=0;i<8;i++)
					{
						ee_printed_id[i] = g_id[i];
					}
					LCD_distring(g_id,24,24,0);		// display the ID sent last time
					LCD_distring("ID Programmed",20,36,0);
					led_blinking(120,0);
					state.main_state = NORMAL;
				}
				else
				{
					state.main_state = FINAL_ID_STEP9;
				}
#else
				print_label(g_id,g_model,year_week,g_soft,g_hard);
					
				for(i=0;i<8;i++)
				{
					ee_printed_id[i] = g_id[i];
				}
				LCD_distring(g_id,24,24,0);		// display the ID sent last time
				LCD_distring("ID Programmed",20,36,0);
				led_blinking(120,0);
				state.main_state = NORMAL;
#endif
				
			break;
			
			default:break;
		}
		
		if(state.main_state != NORMAL)
		{
			if(Time_delay.timer_flex.time_out == 1)
			{
				switch(state.main_state)
				{
					case FINAL_ID_STEP2:
						LCD_distring_V2(error_111,20,36,0);
					break;
					
					case FINAL_ID_STEP4:
						LCD_distring_V2(error_112,20,36,0);
					break;
					
					case FINAL_ID_STEP6:
						LCD_distring_V2(error_113,20,36,0);
					break;
					
					case FINAL_ID_STEP9:
						LCD_distring_V2(error_110,20,36,0);
					break;
					
					default:
						LCD_distring_V2(error_109,20,36,0);
					break;
				}
				state.main_state = NORMAL;
			}
		}
		
		if(IS_PEN == 0)
		{
			TOUCH_getdata();
			temp_int = get_touch_key();
			
			touch_key_blink(temp_int,100);
			
			//if(temp_int <= 0x11)
			if(temp_int <= 19)		//alan
			{
				if(temp_int <= 9)
				{
					if(col >= 24 & col< 24 + 16)
					{
						buffer[0] = 48 + temp_int;
						buffer[1] = 0;
						LCD_distring(buffer,col,24,0);
			
						switch(col)
						{
						case 24:
								g_id[0] = buffer[0];
							break;
							
						case 26:
								g_id[1] = buffer[0];
							break;
							
						case 28:
								g_id[2] = buffer[0];
							break;
							
						case 30:
								g_id[3] = buffer[0];
							break;
							
						case 32:
								g_id[4] = buffer[0];
							break;
							
						case 34:
								g_id[5] = buffer[0];
							break;
							
						case 36:
								g_id[6] = buffer[0];
							break;
							
						case 38:
								g_id[7] = buffer[0];
							break;
							
						default:break;
						}
						
						col += 2;
					}
				}
				else if(temp_int <= 15)
				{
					if(col >= 24 & col< 24 + 16)
					{
						buffer[0] = 65 - 10 + temp_int;
						buffer[1] = 0;
						LCD_distring(buffer,col,24,0);
						switch(col)
						{
						case 24:
								g_id[0] = buffer[0];
							break;
							
						case 26:
								g_id[1] = buffer[0];
							break;
							
						case 28:
								g_id[2] = buffer[0];
							break;
							
						case 30:
								g_id[3] = buffer[0];
							break;
							
						case 32:
								g_id[4] = buffer[0];
							break;
							
						case 34:
								g_id[5] = buffer[0];
							break;
							
						case 36:
								g_id[6] = buffer[0];
							break;
							
						case 38:
								g_id[7] = buffer[0];
							break;
							
						default:break;
						}
						col += 2;
					}
				}
				else if((temp_int == 16)||(temp_int == 18))		//"confirm"
				{
					if(col == 40)
					{
						g_id[8] = 0;
						LCD_distring(g_id,24,24,1);		// display the ID sent last time
						LCD_distring("                 ",20,36,0);
						led_blinking_disable(0);
						timer_flex_initial(5000);
						state.main_state = FINAL_ID_STEP1;
					}
				}
				else if(temp_int == 17)		// "delete"
				{
					if(col >24)
					{
						LCD_distring(" ",col,24,0);
						col -= 2;
					}
				}
				else if(temp_int == 19)		//"Next" alan
				{
					id_long = 0;
					id_long = StrToChar(g_id);
					id_long = (id_long << 8) + StrToChar(&g_id[2]);
					id_long = (id_long << 8) + StrToChar(&g_id[4]);
					id_long = (id_long << 8) + StrToChar(&g_id[6]);
					id_long++;
					CharToStr((unsigned char)id_long,buffer);
					g_id[6] = buffer[0];
					g_id[7] = buffer[1]; 
					CharToStr((id_long & 0x0000FF00) >> 8,buffer);
					g_id[4] = buffer[0];
					g_id[5] = buffer[1]; 
					CharToStr((id_long & 0x00FF0000) >> 16,buffer);
					g_id[2] = buffer[0];
					g_id[3] = buffer[1]; 
					CharToStr((id_long & 0xFF000000) >> 24,buffer);
					g_id[0] = buffer[0];
					g_id[1] = buffer[1]; 

					if(col == 40)
					{
						g_id[8] = 0;
						LCD_distring(g_id,24,24,1);		// alan,display the ID sent last time
						LCD_distring("                 ",20,36,0);
						led_blinking_disable(0);
						timer_flex_initial(5000);
						state.main_state = FINAL_ID_STEP1;
					}
				}
			}
		}
		
		if(Time_delay.timer_flex2.time_out == 1)
		{
			temp = ~temp;
			timer_flex2_initial(500);
			if(temp)
				LCD_distring("_",col,24,0);
			else
				LCD_distring(" ",col,24,0);
		}
		
		all_reception_buffer_clear();
		light_adj();
	}
}

unsigned char input_screen(unsigned char *title,unsigned char *input_result,unsigned char flag)
{
	unsigned char temp = 0;
	unsigned char col = 24;
	unsigned char buffer[3];
	unsigned int temp_int;
	
	unsigned char i;
	static unsigned char len;
	len = strlen(input_result);
		
	LCD_Clr();
	LCD_distring(title, 12, 4, 0);
	LCD_distring("   Input:", 0, 24, 0);
	//LCD_distring("123456789012345678901234567", 0, 38, 0);
	LCD_distring("1    2    3     ", 10, 48, 0);
	LCD_distring("4    5    6     ", 10, 72, 0);
	LCD_distring("7    8    9     ", 10, 96, 0);
	LCD_distring("     0          ", 10, 120, 0);
	LCD_distring("Delete", 2, 140, 0);
	//LCD_distring("Again", 10, 140, 0);		//alan		18
	//LCD_distring("Next", 24, 140, 0);			//alan		19
	LCD_distring("Confirm", 36, 140, 0);
	
	timer_flex2_initial(500);
	g_lux[0] = '0';
	g_lux[1] = '0';
	g_lux[2] = '0';
	g_lux[3] = '0';
	g_lux[4] = 0;
	
	switch(flag)
	{
		case INPUT_MODEL:
			for(i=0;i<6;i++)
			{
				g_model[i] = ee_model[i]; 
			}
			LCD_distring_ee(ee_model,24,24,0);
		break;
		
		case INPUT_YEAR:
			for(i=0;i<2;i++)
			{
				g_year[i] = ee_year[i];
			}
			LCD_distring_ee(ee_year,24,24,0);
		break;
		
		case INPUT_WEEK:
			for(i=0;i<2;i++)
			{
				g_week[i] = ee_week[i];
			}
			LCD_distring_ee(ee_week,24,24,0);
		break;
		
		case INPUT_SOFTWARE_VERSION:
			for(i=0;i<6;i++)
			{
				g_soft[i] = ee_soft[i];
			}
			LCD_distring_ee(ee_soft,24,24,0);
		break;
		
		case INPUT_HARDWARE_VERSION:
			for(i=0;i<2;i++)
			{
				g_hard[i] = ee_hard[i];
			}
			LCD_distring_ee(ee_hard,24,24,0);
		break;
		
		default:break;
	}
	
	col = 24 + 2 * len;
	
	while(1)
	{
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		if(IS_PEN == 0)
		{
			TOUCH_getdata();
			temp_int = get_touch_key();
			touch_key_blink_01(temp_int,100);
			
			if(temp_int <= 9 || temp_int == 16 || temp_int == 17)
			{
				if(temp_int <= 9)
				{
					if(col >= 24 & col< 24 + 2 * len)
					{
						buffer[0] = 48 + temp_int;
						buffer[1] = 0;
						LCD_distring(buffer,col,24,0);
						
						i = (col - 24) / 2;
						
						*(input_result + i) = temp_int + 48;
						col += 2;
					}
				}
				else if(temp_int == 16)
				{
					if(col == 24 + 2 * len)
					{
						col = 24;
						LCD_distring("          ",col,24,0);
						switch(flag)
						{
							case INPUT_MODEL:
								for(i=0;i<6;i++)
								{
									ee_model[i] = g_model[i]; 
								}
							break;
							
							case INPUT_YEAR:
								for(i=0;i<2;i++)
								{
									ee_year[i] = g_year[i];
								}
							break;
							
							case INPUT_WEEK:
								for(i=0;i<2;i++)
								{
									ee_week[i] = g_week[i];
								}
							break;
							
							case INPUT_SOFTWARE_VERSION:
								for(i=0;i<6;i++)
								{
									ee_soft[i] = g_soft[i];
								}
							break;
							
							case INPUT_HARDWARE_VERSION:
								for(i=0;i<2;i++)
								{
									ee_hard[i] = g_hard[i];
								}
							break;
							
							default:break;
						}
						return 0;
					}
				}
				else if(temp_int == 17)
				{
					if(col >24)
					{
						LCD_distring(" ",col,24,0);
						col -= 2;
					}
				}
			}
		}
		
		if(Time_delay.timer_flex2.time_out == 1)
		{
			temp = ~temp;
			timer_flex2_initial(500);
			if(temp)
				LCD_distring("_",col,24,0);
			else
				LCD_distring(" ",col,24,0);
		}
		
		light_adj();
	}
}

unsigned char test_screen_all(unsigned char *title,unsigned char *input_result)
{
	unsigned int temp_int;
	unsigned char buffer_tx[17];
	unsigned char buffer_tx_short[9];
	unsigned char model;
	unsigned char buffer_last_8[9];
	unsigned char buffer_last_16[17];
	
	unsigned char i;
	
	unsigned char frames = 0;
	unsigned char frames_last = 0;
	buffer_last_16[16] = 0;
		
	LCD_Clr();
	LCD_distring(title, 12, 4, 0);
	LCD_distring("Result:",0,20,0);
	LCD_distring("  PnG ", 36, 140, 0);
	
	for(i=0;i<16;i++)
	{
		buffer_last_16[i] = 0x00;
	}
	
	for(i=0;i<8;i++)
	{
		buffer_last_8[i] = 0x00;
	}
	
	buffer_tx[16] = 0;
	buffer_last_16[16] = 0;
	
	buffer_tx_short[8] = 0;
	
	product_information.conf_type = ADVANCED;
	led_blinking_disable(0);
	
	timer_second_initial(86400);
	while(1)
	{
		while(decode_SCS());
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		if(g_asc_short_buffer[2] == 0x12)
		{
			if(g_asc_short_buffer[3] == 0x00)
			{
				led_blinking_disable(1);
			}
			else if(g_asc_short_buffer[3] == 0x01)
			{
				led_blinking_disable(0);
			}
		}
		else if(g_asc_short_buffer[2] == 0x1D)
		{
			if(g_asc_short_buffer[3] == 0x00)
			{
				led_blinking(500,500);
			}
		}
		
		strncpy(buffer_tx,g_reception_buffer,16);

		strncpy(buffer_tx_short,g_short_buffer,8);
		
		if(strcmp(buffer_last_16,buffer_tx))
		{
			frames_last = frames - 1;
			if(frames_last == 0xFF)
				frames_last = 7;
			//LCD_distring("    ",0,36+frames_last*12,0);
			/*
			for(i = 0;i< 8;i++)
			{
				LCD_distring("    ",0,36+i*12,0);
			}
			*/
      //LCD_distring(buffer_last_16,10,36+frames*12,0);
      //LCD_distring("LAST",0,36+frames*12,0);
      
      if(buffer_last_16[0] != 0)
      {
        LCD_distring(buffer_last_16,10,36+frames*12,0);
				LCD_distring("    ",0,36+frames_last*12,0);
        LCD_distring("LAST",0,36+frames*12,0);
        frames++;
      }
      strncpy(buffer_last_16,buffer_tx,16);
      if(frames >= 8)
        frames = 0;
		}
		else if(strcmp(buffer_last_8,buffer_tx_short))
		{
			/*
				for(i = 0;i< 8;i++)
				{
					LCD_distring("    ",0,36+i*12,0);
				}
			*/
			frames_last = frames - 1;
			if(frames_last == 0xFF)
				frames_last = 7;
      
      if(buffer_last_8[0] != 0)
			{
				LCD_distring("    ",0,36+frames_last*12,0);
			
				LCD_distring(buffer_last_8,10,36 + frames*12,0);
				LCD_distring("        ",10+16,36 + frames*12,0);
				//LCD_distring("    ",0,36+frames*12,1);
				LCD_distring("LAST",0,36+frames*12,0);
      	frames++;
			}
      strncpy(buffer_last_8,buffer_tx_short,8);
      if(frames >= 8)
        frames = 0;
		}
		
		switch(state.main_state)
		{
			case AFTER_REQUEST_ID:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[0] == 0xD0 && g_reception_buffer[7] == '4')
					{
						strncpy(buffer_tx,"D000010600000000",17);
						strncpy(&buffer_tx[8],&g_reception_buffer[8],8);
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
#ifdef FINAL_VERSION2
						timer_flex_initial(4000);
#else
						timer_flex_initial(10000);
#endif
						state.main_state = FINAL_STEP1;
						asm("nop");
					}
				}
				else
				{
					id_setting("FFFFFFFF");
					send_frame_pp_ext_broad("D000010300000000",TRANS_DELAY);
					timer_flex_initial(1000);
					state.main_state = AFTER_SETTING_ID;
				}
			break;
		
			case AFTER_SETTING_ID:
				if(Time_delay.timer_flex.time_out)
				{
					LCD_distring_V2(error_111,16,20,0);
					state.main_state = NORMAL;
				}
			break;
	
			case FINAL_STEP1:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x80)
					{
						model = g_asc_reception_buffer[7];
						state.main_state = FINAL_STEP2;
					}
				}
			break;
			
			case FINAL_STEP2:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x8B)
					{
						if(g_asc_reception_buffer[5] == 0x02 && g_asc_reception_buffer[6] == 0x03 && g_asc_reception_buffer[7] == 0x81)
						{
							state.main_state = FINAL_STEP3;
						}
						else if(g_asc_reception_buffer[7] == 0x01)
						{
							state.main_state = FINAL_STEP5;
						}
					}
				}
				else if(Time_delay.timer_flex.time_out == 1)
				{
					LCD_distring_V2(error_111,16,20,0);
					send_frame_pp_ext_broad("D20101428C0000FF",TRANS_DELAY);
					state.main_state = NORMAL;
				}
			break;
			
			case FINAL_STEP3:
				//if(Time_delay.timer_flex.time_out)
				if((g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x8C && g_asc_reception_buffer[7] == 0xAA) || Time_delay.timer_flex.time_out)
				{
					switch(model)
					{
						case 0x20:
						case 0x21:
						case 0x22:
						case 0x23:
						case 0x24:
						case 0x25:
						case 0x26:
						case 0x27:
						case 0x28:
						case 0x29:
						case 0x2A:
							PnG_048820();
							state.main_state = FINAL_STEP4;
						break;
						default:break;
					}
					asm("nop");
				}
			break;
			
			case FINAL_STEP4:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x8C && g_asc_reception_buffer[7] == 0xAB)
					{
						LCD_distring_V2(right_100,16,20,0);
					}
					state.main_state = NORMAL;
				}
				else
				{
					LCD_distring_V2(error_114,16,20,0);
					state.main_state = NORMAL;
				}
			break;
			
			default:break;
		}
		
		if(Time_delay.timer_flex.time_out)
		{
			switch(state.main_state)
			{
				case FINAL_STEP5:
					LCD_distring_V2(right_101,16,20,0);
					send_frame_pp_ext_broad("D20101428C0000FF",TRANS_DELAY);
					state.main_state = NORMAL;
				break;
			}
		}
		
		if(IS_PEN == 0)
		{
			TOUCH_getdata();
			temp_int = get_touch_key();
			touch_key_blink_03(temp_int,100);
			
			if(temp_int == 16)
			{
				led_blinking_disable(0);
				LCD_distring_V2(blank,16,20,0);
				send_frame_pp_ext_broad("D000010300000000",TRANS_DELAY);
				timer_flex_initial(1000);
				state.main_state = AFTER_REQUEST_ID;
			}
		}
		
		light_adj();
		all_reception_buffer_clear();
	}
}

unsigned char test_screen(unsigned char *title,unsigned char *input_result)
{
	unsigned char temp = 0;
	unsigned char col = 24;
	unsigned char buffer[3];
	unsigned int temp_int;
	unsigned char buffer_tx[17];
	unsigned char buffer_tx_short[9];
	unsigned char model;
	unsigned char buffer_last_8[9];
	unsigned char buffer_last_16[17];
	
	unsigned char i;
	static unsigned char len;
	len = strlen(input_result);
		
	LCD_Clr();
	LCD_distring(title, 12, 4, 0);
	LCD_distring("   Input:", 0, 24, 0);
	LCD_distring("   Frame:", 0, 36, 0);
	//LCD_distring("123456789012345678901234567", 0, 38, 0);
	LCD_distring("1    2    3     ", 10, 48, 0);
	LCD_distring("4    5    6     ", 10, 72, 0);
	LCD_distring("7    8    9     ", 10, 96, 0);
	LCD_distring("     0          ", 10, 120, 0);
	LCD_distring("Delete", 2, 140, 0);
	//LCD_distring("Again", 10, 140, 0);		//alan		18
	//LCD_distring("Next", 24, 140, 0);			//alan		19
	LCD_distring("  PnG ", 36, 140, 0);
	
	timer_flex2_initial(500);
	g_lux[0] = '0';
	g_lux[1] = '0';
	g_lux[2] = '0';
	g_lux[3] = '0';
	g_lux[4] = 0;
	
	for(i=0;i<16;i++)
	{
		buffer_last_16[i] = 0x00;
	}
	
	for(i=0;i<8;i++)
	{
		buffer_last_8[i] = 0x00;
	}
	
	buffer_tx[16] = 0;
	buffer_last_16[16] = 0;
	
	buffer_tx_short[8] = 0;
	
	product_information.conf_type = ADVANCED;
	led_blinking_disable(0);
	
	while(1)
	{
		while(decode_SCS());
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		if(g_asc_short_buffer[2] == 0x12)
		{
			if(g_asc_short_buffer[3] == 0x00)
			{
				led_blinking_disable(1);
			}
			else if(g_asc_short_buffer[3] == 0x01)
			{
				led_blinking_disable(0);
			}
		}
		else if(g_asc_short_buffer[2] == 0x1D)
		{
			if(g_asc_short_buffer[3] == 0x00)
			{
				led_blinking(500,500);
			}
		}
		
		strncpy(buffer_tx,g_reception_buffer,16);

		strncpy(buffer_tx_short,g_short_buffer,8);
		
		if(strcmp(buffer_last_16,buffer_tx))
		{
			if(buffer_last_16[0] != 0x00)
				LCD_distring(buffer_last_16,20,36,0);
			strncpy(buffer_last_16,buffer_tx,16);
		}
		else if(strcmp(buffer_last_8,buffer_tx_short))
		{
			if(buffer_last_8[0] != 0x00)
			{	
				LCD_distring(buffer_last_8,20,36,0);
				LCD_distring("        ",20+16,36,0);
			}
			strncpy(buffer_last_8,buffer_tx_short,8);
		}
		
		switch(state.main_state)
		{
			case AFTER_REQUEST_ID:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[0] == 0xD0 && g_reception_buffer[7] == '4')
					{
						strncpy(buffer_tx,"D000010600000000",17);
						strncpy(&buffer_tx[8],&g_reception_buffer[8],8);
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
						timer_flex_initial(4000);
						state.main_state = FINAL_STEP1;
						asm("nop");
					}
				}
				else
				{
					id_setting("FFFFFFFF");
					send_frame_pp_ext_broad("D000010300000000",TRANS_DELAY);
					timer_flex_initial(1000);
					state.main_state = AFTER_REQUEST_ID;
				}
			break;
			
			case FINAL_STEP1:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x80)
					{
						model = g_asc_reception_buffer[7];
						state.main_state = FINAL_STEP2;
					}
				}
			break;
			
			case FINAL_STEP2:
				if(Time_delay.timer_flex.time_out == 0)
				{
					if(g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x8B)
					{
						if(g_asc_reception_buffer[5] == 0x02 && g_asc_reception_buffer[6] == 0x03 && g_asc_reception_buffer[7] == 0x81)
						{
							state.main_state = FINAL_STEP3;
						}
					}
				}
				else if(Time_delay.timer_flex.time_out == 1)
				{
					send_frame_pp_ext_broad("D20101428C0000FF",TRANS_DELAY);
					state.main_state = NORMAL;
				}
			break;
			
			case FINAL_STEP3:
				//if(Time_delay.timer_flex.time_out)
				if((g_asc_reception_buffer[3] == 0x34 && g_asc_reception_buffer[4] == 0x8C && g_asc_reception_buffer[7] == 0xAA) || Time_delay.timer_flex.time_out)
				{
					switch(model)
					{
						case 0x20:
						case 0x21:
						case 0x22:
						case 0x23:
						case 0x24:
						case 0x25:
						case 0x26:
						case 0x27:
						case 0x28:
						case 0x29:
						case 0x2A:
							PnG_048820();
							state.main_state = FINAL_STEP4;
						break;
						default:break;
					}
					asm("nop");
				}
			break;
			
			default:break;
		}
		
		if(IS_PEN == 0)
		{
			TOUCH_getdata();
			temp_int = get_touch_key();
			touch_key_blink_02(temp_int,100);
			
			if(temp_int <= 9 || temp_int == 16 || temp_int == 17)
			{
				if(temp_int <= 9)
				{
					if(col >= 24 & col< 24 + 2 * len)
					{
						buffer[0] = 48 + temp_int;
						buffer[1] = 0;
						LCD_distring(buffer,col,24,0);
						
						i = (col - 24) / 2;
						
						*(input_result + i) = temp_int + 48;
						col += 2;
					}
				}
				else if(temp_int == 16)
				{
					led_blinking_disable(0);
					
					if(col == 24 + 2 * len)
					{
						//col = 24;
						//LCD_distring("          ",col,24,0);
						//return 0;
						
						if(g_model[0] == '0' && g_model[1] == '4' && g_model[2] == '8' && g_model[3] == '8')
						{
							buffer[0] = g_model[4];
							buffer[1] = g_model[5];
							buffer[2] = 0;
							
							switch(StrToChar(buffer))
							{
								case 0x20:
								case 0x21:
								case 0x22:
								case 0x23:
								case 0x24:
								case 0x25:
								case 0x26:
								case 0x29:
								case 0x30:
									send_frame_pp_ext_broad("D000010300000000",TRANS_DELAY);
									timer_flex_initial(1000);
									state.main_state = AFTER_REQUEST_ID;
								break;
								default:break;
							}
						}
					}
				}
				else if(temp_int == 17)
				{
					if(col >24)
					{
						LCD_distring(" ",col,24,0);
						col -= 2;
					}
				}
			}
		}
		
		if(Time_delay.timer_flex2.time_out == 1)
		{
			temp = ~temp;
			timer_flex2_initial(500);
			if(temp)
				LCD_distring("_",col,24,0);
			else
				LCD_distring(" ",col,24,0);
		}
		
		light_adj();
		
		//delay_ms(10);
		all_reception_buffer_clear();
	}
}

void PnG_048820(void)
{
	send_frame_pp_ext_broad("D20101428B00A801",TRANS_DELAY +50);
	//send_frame_pp_ext_broad("D20101428D020101",TRANS_DELAY);
	setting_parameter(0x02,0x01);
	//send_frame_pp_ext_broad("D20101428D020501",TRANS_DELAY);
	setting_parameter(0x02,0x05);
	//send_frame_pp_ext_broad("D20101428D020601",TRANS_DELAY);
	setting_parameter(0x02,0x06);
	//send_frame_pp_ext_broad("D20101428D000701",TRANS_DELAY);
	setting_parameter(0x00,0x07);
	//send_frame_pp_ext_broad("D20101428D000801",TRANS_DELAY);
	setting_parameter(0x00,0x08);
	//send_frame_pp_ext_broad("D20101428D010D01",TRANS_DELAY);
	setting_parameter(0x01,0x0D);
	//send_frame_pp_ext_broad("D20101428D010E01",TRANS_DELAY);
	setting_parameter(0x01,0x0E);
	//send_frame_pp_ext_broad("D20101428D011C01",TRANS_DELAY);
	setting_parameter(0x01,0x1C);
	//send_frame_pp_ext_broad("D20101428D021D01",TRANS_DELAY);
	setting_parameter(0x02,0x1D);
	send_frame_pp_ext_broad("D20101428C0000AA",TRANS_DELAY + 50);
	send_frame_pp_ext_broad("D20101428C0000FF",TRANS_DELAY);
}

void setting_parameter(unsigned char value, unsigned char index)
{
	unsigned char buffer[3];
	unsigned char buffer_tx[17];
	//CharToStr(KO_conf.PirSens,buffer);
	CharToStr(value,buffer);
	strncpy(buffer_tx,"D20101428D020101",17);
	buffer_tx[10] = buffer[0];
	buffer_tx[11] = buffer[1];
	CharToStr(index,buffer);
	buffer_tx[12] = buffer[0];
	buffer_tx[13] = buffer[1];
	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY + 50);
}
/*
void print_label(unsigned char *id,unsigned char *model, unsigned char *date, unsigned char *fireware_version, unsigned char *hardware_version)
{
	print_out("^XA~TA0~JSO^LT0^MMT^MNW^MTT^PON^PMN^LH0,0^JMA^PR2,2^MD30^JUS^LRN^CI0^XZ~DG001.GRF,00512,008,::::::::::::::::::::N020,N060,N0E0,M03B0,M0A28,J07FFC18,I0EA8A808,H01C0I01C,H0280J0A,H0601C007C,H0E2EA8AE8,018F071F,03B80BA8,03E00F,0A8008,07,0A,04,H8,,:::::::::::::::::::::::^XA^LL0120^PW296^BY32,32^FT247,54^BXN,2,200,0,0,1");
	//modle & ID
	print_out("^FH\\^FD048822 ID:00050162^FS"); 
	print_out("^FO,31^FS");
	print_out("^FT160,98^A0N,25,24^FH\\^FDID:00050162^FS");
	print_out("^BY43,44^FT43,100^BXB,2,200,0,0,1");
	print_out("^FH\\^FD048822 09W28 007 01 010000 ID:00050162^FS");
	print_out("^FO,22^FS");
	print_out("^FT124,100^A0B,18,16^FH\\^FDID:00050162^FS");
	print_out("^FT160,64^XG001.GRF,1,1^FS");
	print_out("^FO,26^FS");
	print_out("^FT160,66^A0N,21,21^FH\\^FD048822^FS");
	print_out("^FO,22^FS");
	print_out("^FT101,100^A0B,18,16^FH\\^FD01 010000^FS");
	print_out("^FO,22^FS");
	print_out("^FT59,100^A0B,18,16^FH\\^FD048822^FS");
	print_out("^FO,22^FS");
	print_out("^FT79,100^A0B,18,16^FH\\^FD09W28 007^FS");
	print_out("^PQ1,0,1,Y^XZ");
	print_out("^XA^ID000.GRF^FS^XZ");
}
*/

unsigned char write_flash(unsigned char page, struct S_sensor_info sensor)
{
	unsigned int i = 0;
	unsigned char page_buffer[264];
	
	if(ee_page >= TOP_PAGE)
	{
		return M_DATAFLASH_FULL;
	}
	else
	{
		Dled_light_on_ms(2);
		
		DF_SPI_init();

		Cont_Flash_Read_Enable (ee_page ,0);
		
		for (i=0;i<264;i++)
		{
			page_buffer[i] = DF_SPI_RW(0x00);
		}
			
		i = 0;
		do
		{
			page_buffer[g_dataflash_page_address] = sensor.start[i];
			i++;
			g_dataflash_page_address++;
		}while(i < STRUCT_SENSOR_LENGTH_BYTE);
		
		Buffer_Write_Enable (1, 0);
		for (i=0;i<264;i++)
		{
			//Buffer_Write_Byte(1,i,g_page_buffer[i]);
			DF_SPI_RW(page_buffer[i]);
		}
		
		ee_page_address = g_dataflash_page_address;
		
		//page_erease(ee_page);
		Buffer_To_Page (1,ee_page);             //transfer to DataFlash
		
		if(g_dataflash_page_address >= STRUCT_SENSOR_LENGTH_BYTE * 6)
		{
			ee_page++;
			ee_page_address = 0;
			g_dataflash_page_address = 0;
		}

		ee_page_address = g_dataflash_page_address;
		
		DF_SPI_disable();
		return 0;
	}
}

unsigned char dataflash_chip_erease(void)
{
	unsigned int i;
	unsigned char buffer_tx[] = "02030000";
	
	DF_SPI_init();
	led_blinking(50,50);
	
	for(i = 0;i< 264;i++)
	{
		Buffer_Write_Byte(1,i,0xFF);
	}
	
	for(i = 0;i<TOP_PAGE;i++)
	{
		//page_erease(i);
		Buffer_To_Page (1,i);
		//page_erease(i);
		
		if(i == 204)
		{
			buffer_tx[7] = '1';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *2)
		{
			buffer_tx[7] = '2';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *3)
		{
			buffer_tx[7] = '3';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *4)
		{
			buffer_tx[7] = '4';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *5)
		{
			buffer_tx[7] = '5';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *6)
		{
			buffer_tx[7] = '6';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *7)
		{
			buffer_tx[7] = '7';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *8)
		{
			buffer_tx[7] = '8';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == 204 *9)
		{
			buffer_tx[7] = '9';
			print_out("$");
			print_out(buffer_tx);
		}
		else if(i == TOP_PAGE -1)
		{
			buffer_tx[7] = '0';
			print_out("$");
			print_out(buffer_tx);
		}
	}
	
	ee_page = 0;
	ee_page_address = 0;
	g_dataflash_page_address = 0;
	
	DF_CS_inactive;  
	DF_SPI_disable();
	led_blinking_disable(0);
	return 0;
}

void input_to_stru(unsigned char *id)
{
	unsigned char i;
	
	stru_sensor.date[0] = g_year[0];
	stru_sensor.date[1] = g_year[1];
	stru_sensor.date[2] = g_week[0];
	stru_sensor.date[3] = g_week[1];
	stru_sensor.date[4] = 0;
	
	for(i = 0;i<8;i++)
	{
		stru_sensor.id[i] = *(id+i);
	}
	stru_sensor.id[8] = 0;
	
	stru_sensor.hardware_version[0] = g_hard[0];
	stru_sensor.hardware_version[1] = g_hard[1];
	
	for(i=0;i<6;i++)
	{
		stru_sensor.software_version[i] = g_soft[i];
	}
	stru_sensor.software_version[6] = 0;
	
	stru_sensor.start[0] = 'S';
	stru_sensor.start[1] = 0;
	stru_sensor.end[0] = 'N';
	stru_sensor.end[1] = 0;
}

void timer_second_initial(unsigned long int on_ms)
{
	Time_delay.second.count = 0;
	Time_delay.second.stack_top = on_ms;
	Time_delay.second.time_out = 0;
	Time_delay.second.enabled = 1;
}