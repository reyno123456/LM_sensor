#ifndef _BOARD_H
#define _BOARD_H

#define NONE_CONFED_203
//#define NONE_CONFED_204
//#define NONE_CONFED_1FF

//#define DEBUG

//#define DEMOBOARD

//#define LM018
//#define LM056
//#define LM057
//#define LM076
//#define LM077
//#define LM020
//#define LM028

//#ifdef SMT

#ifdef LM018
	#define HARDWARE_PIR
	#define NO_CONFIGURATOR_HOUSING
	#define CELIING
#endif

#ifdef LM056
	#define HARDWARE_US
	#define NO_CONFIGURATOR_HOUSING
	#define CELIING
#endif

#ifdef LM057
	#define HARDWARE_PIR_US
	#define NO_CONFIGURATOR_HOUSING
	#define CELIING
#endif

#ifdef LM076
	#define HARDWARE_PIR			// 原先的定义错误，076是单PIR的产品
	#define WALLCORNER
#endif

#ifdef LM077
	#define HARDWARE_PIR_US
	#define WALLCORNER
#endif

#ifdef LM020
	#define HARDWARE_PIR
	#define NO_CONFIGURATOR_HOUSING
	#define WALLCORNER
#endif

#ifdef LM028
	#define DAYLIGHT_ONLY
	#define NO_CONFIGURATOR_HOUSING
	#define CELIING
#endif

#define RES_VALUE 100000

#ifdef CELIING
	#define CONST_DAYLIGHT 2143
#endif

#ifdef WALLCORNER
	#define CONST_DAYLIGHT 3343
#endif

#define KO_HARDWARE 515

#define ERROR
#define advance_configuration

#define	SetBit(x,y) (x|=(1<<y))
#define	ClrBit(x,y) (x&=(~(1<<y)))
#define	GetBit(x,y) (x&(1<<y))
#define NotBit(x,y) (x^|=(1<<y))

#define DLED_ON 		ClrBit(PORTC,6)
#define DLED_OFF		SetBit(PORTC,6)

#define LLED_ON 		ClrBit(PORTD,6)
#define LLED_OFF		SetBit(PORTD,6)

#define SET_BUZZER		SetBit(PORTB,4)
#define CLR_BUZZER		ClrBit(PORTB,4)

#define DELAY_20S 1
#define SEC_20	2000

#define BUTTON_SHORT_PRESSED 1000

#ifdef DEMOBOARD
	#define US_OFF SetBit(PORTC,1);
	#define US_ON ClrBit(PORTC,1);
	#define daylight_channel 3
#else
	#define US_OFF SetBit(PORTC,2);
	#define US_ON ClrBit(PORTC,2);
#ifdef SMT
	#define daylight_channel 7
#else
	#define daylight_channel 3
#endif
#endif

#define CHANNEL_RANDOM 2

#define SET_DATAFLASH_RESET SetBit(PORTC,1)
#define CLR_DATAFLASH_RESET ClrBit(PORTC,1)

void buzzer_ms(unsigned int ms);
void IO_Initial();
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);		// alan 0604
void not_bit(unsigned char *data, unsigned bit);
unsigned char StrToChar(unsigned char *data);
unsigned char *CharToStr(unsigned char data,unsigned char *buffer);
unsigned char get_key();

#define ADC_VREF_TYPE 0x40

unsigned char get_PIR_trigger(unsigned char level);
unsigned char get_US_trigger(unsigned char level);
void timer1_initial(void);
void adc_initial();
unsigned int read_adc10bit(unsigned char adc_input);
unsigned char read_adc8bit(unsigned char adc_input);
void system_reset(void);
void WDT_off(void);
void delay_ms_1(void);

#endif
