/*

 G_Ult_detectionEnable  Motion.US_sensitivity要定义成全局变量

 SIZEOF_ULTAVESAMP_BUF
 ADC_ULTRA,TDETCTDURATION,MINPULSEWTH,TULTCHECK,DETECTCNTOP2,T50USEC
 OP1_SMPAVG,OP1_NUMSAMPAVG,OP2_NUMSAMPAVG,OP3_NUMSAMPAVG,OP4_NUMSAMPAVG
 OP1_ULTDETECT，OP2_ULTDETECT，OP3_ULTDETECT，OP4_ULTDETECT，
 OP1_AVGSHIFT，OP2_AVGSHIFT，OP3_AVGSHIFT，OP4_AVGSHIFT，

 */
#include "board.h"
 //ultrasonic的参数定义

#define OP1_NUMSAMPAVG          2
#define OP1_AVGSHIFT            1

#define OP2_NUMSAMPAVG          4
#define OP2_AVGSHIFT            2

#define OP3_NUMSAMPAVG          8
#define OP3_AVGSHIFT            3

#define OP4_NUMSAMPAVG          16
#define OP4_AVGSHIFT            4

#define OP1_HAVGSAMP            2
#define OP1_HAVGSHIFT           1

#define OP2_HAVGSAMP            4
#define OP2_HAVGSHIFT           2

#define OP3_HAVGSAMP            8
#define OP3_HAVGSHIFT           3

#define OP4_HAVGSAMP            16
#define OP4_HAVGSHIFT           4

#define OP1_ULTDETECT           5           /* 2 number of detection for Option1 */
#define OP2_ULTDETECT           10				//默认是10，现在修改成为5
#define OP3_ULTDETECT           20
#define OP4_ULTDETECT           30

#ifdef CELIING
/*
	//for PWM driver 40K
	#define LOW_USSENSITIVITY     0x40//0x90
	#define Medium_USSENSITIVITY  0x30//0x80
	#define HIGH_USSENSITIVITY    0x1B//0x60
	#define MAX_USSENSITIVITY   0x10//0x50
*/
  #define LOW_USSENSITIVITY     0x50//0x90
	#define Medium_USSENSITIVITY  0x40//0x80
	#define HIGH_USSENSITIVITY    0x30//0x60
	#define MAX_USSENSITIVITY   0x26//0x50
#endif

#ifdef WALLCORNER
	#define LOW_USSENSITIVITY     0x50//0xA8
	#define Medium_USSENSITIVITY  0x40//0xA0
	#define HIGH_USSENSITIVITY    0x30//0x90
	#define MAX_USSENSITIVITY   0x2A//0x80
#endif

#define 	ADC_ULTRA               1        /* ADC Channel 1 */
#define		ADCSRA_INIT			0x03		//ADC enable, clear IF, use CK/8 as clock source
	
#define 	T50USEC 		 		100
#define		T200USEC				200

#define 	TULTCHECK 		 	20         /* 40 X 100 uSec = 4mSec, Check average array of Ultra signal at every 4 mSec) */

#define 	MINPULSEWTH  		 	1600       // MIN = 800	/* 800uSec to ignore signal more tha 1.25 frequency */
#define 	MIDPULSEWTH  		 	4000 			// MAX = 16000
#define 	MAXPULSEWTH  		 	10000 		// MAX = 16000
#define		MIN_Threshold 			4
#define		MID_Threshold 			2
#define		ValidPulses_Threshold	5

#define 	TDETCTDURATION 		 		20         /* 4mSec *25 =100mSec */

#define 	ULTDETECTCNT_MASK     0x0C

#define 	ISAMPLECNT_MASK       0x03

#define 	SIZEOF_ULTAVESAMP_BUF   20  		//数组最多存储20个信号

//#define SIZEOF_HISAVESAMP_BUF    16


 unsigned char ReadADC8Bit(char AD_CHANNEL);
 void US_SENSE_SET(void);
 void ultWarmUpEvents( void );
 void ulrStoreSampleAvg (void);
 void ServiceUltra (void);
 void us_detection(void);

