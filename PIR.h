//PIR.h

#define	ADCSRA_init		0X03		//ADC enable, clear IF, use CK/8 as clock source
#define	PIR_SENSE			0               /* ADC Channel 0 */
#define	PIR2_SENSE		2               /* ADC Channel 2 */		//0525

#define	RedLEDONCYCLE		10  		// 选择合适的RED LED的闪烁时间



/*  PIR信号检测限定 */
#define MIN_WIDTH 2
#define MID_WIDTH 35
#define MAX_WIDTH 140
#define MIN_SPACE 5
#define PIR_CENTER 105
#define MAX_PIR (PIR_CENTER*2)


/* PIR灵敏度定义 */		
#define LOW_PIRSENSITIVITY     		0x32			
#define Medium_PIRSENSITIVITY  		0x28
#define HIGH_PIRSENSITIVITY    		0x1A		
#define MAX_PIRSENSITIVITY   			0x12 		


typedef enum DTFLAG_STATUS { DISABLED,
                             ENABLED } DTFLAG_STATUS;

struct PIR
{
	unsigned char center;
	unsigned char window;
	unsigned	fPIROCCDetected:1;
	unsigned	fPIRdetectionEnable:1;		
};

void PIR_SENSE_SET(void);

unsigned char PIR_detect(void);





