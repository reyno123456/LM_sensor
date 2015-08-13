#ifndef _PRINTER_H
#define _PRINTER_H
#include "moudle_SCS.h"

#define DATA_REGISTER_EMPTY (1<<UDRE)
#define UDRE 5

struct S_location
{
	unsigned long int x1;
	unsigned long int y1;
	unsigned long int x2;
	unsigned long int y2;
};

extern unsigned char g_touched;
void print_initial(void);
void print_out(unsigned char *data);
void print_out_flash(unsigned char __flash *data);
void print_model(unsigned char data);
void print_label(unsigned char *id,unsigned char *model, unsigned char *date, unsigned char *fireware_version, unsigned char *hardware_version);
void external_interrupt_initial(void);
void key_parameter_initial(void);
unsigned char get_touch_key(void);
unsigned char get_touch_menu_00(void);
void id_setting(unsigned char *data);
void id_setting_ee(unsigned char __eeprom *data);
void touch_key_blink(unsigned char index,unsigned int ms);
void touch_key_blink_01(unsigned char index,unsigned int ms);
void touch_key_blink_02(unsigned char index,unsigned int ms);
void touch_key_blink_03(unsigned char index,unsigned int ms);
void menu_00(void);
void menu_01(void);
void menu_02(void);
unsigned char input_screen(unsigned char *title,unsigned char *input_result,unsigned char flag);
unsigned char test_screen(unsigned char *title,unsigned char *input_result);
unsigned char test_screen_all(unsigned char *title,unsigned char *input_result);
void PnG_048820(void);
void setting_parameter(unsigned char value, unsigned char index);
unsigned char write_flash(unsigned char page, struct S_sensor_info sensor);
unsigned char dataflash_chip_erease(void);
void model_convert(void);
void input_to_stru(unsigned char *id);
void timer_second_initial(unsigned long int on_ms);
#endif