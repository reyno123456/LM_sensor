
/*
	超声波模块的调用周期是200us

 G_Ult_detectionEnable  Motion.US_sensitivity要定义成全局变量

 SIZEOF_ULTAVESAMP_BUF
 ADC_ULTRA,TDETCTDURATION,MINPULSEWTH,TULTCHECK,DETECTCNTOP2,T50USEC
 OP1_SMPAVG,OP1_NUMSAMPAVG,OP2_NUMSAMPAVG,OP3_NUMSAMPAVG,OP4_NUMSAMPAVG
 OP1_ULTDETECT，OP2_ULTDETECT，OP3_ULTDETECT，OP4_ULTDETECT，
 OP1_AVGSHIFT，OP2_AVGSHIFT，OP3_AVGSHIFT，OP4_AVGSHIFT，

 */


#include <ioavr.h>
#include <inavr.h>
#include "US.h"
#include "moudle_SCS.h"
#include "global_variable.h"
#include "application.h"



enum DTFLAG_STATUS { DISABLED,
                     ENABLED }DTFLAG_STATUS;							
							
enum INDSAMPLE_CNT  { OP1_SMPAVG ,
                      OP2_SMPAVG ,
                      OP3_SMPAVG ,
                      OP4_SMPAVG} INDSAMPLE_CNT;

//
struct
{

   union
   {
        unsigned char ultFlags;
       	struct
	 {
              enum INDSAMPLE_CNT    fULTSampleCounter: 2;
		
              enum DTFLAG_STATUS    fULTdetectEnable: 1;        //   Externally enable/ dissable Ultrasonic detection controller flag
		
              enum DTFLAG_STATUS    fULTdetectPulse: 1;
		
              enum DTFLAG_STATUS    fULTdetDurationSet: 1;
		
              enum DTFLAG_STATUS    fULTOCCDetected: 1;        // Set when Ulrasonic motion Detection
		
        };
  };

  unsigned char ultwindow;
  //unsigned char ultSentivityDcnt;
  unsigned char 	ultIndivSampleCount;
  unsigned int 	 	ultSensorSampleValue;
  unsigned char 	ultHAvgSamples;
	unsigned char 	ultPulseCount;			// 0615
	unsigned char		ultmaxCount;
  unsigned char  	ultmidCount;
	unsigned char  	ultminCount;
	unsigned char  	ult_nodetectCount;	// 0615
	unsigned char  	ultOccDetectionCount;
	
  unsigned int  ultMinPulseWidth;
  unsigned int  ultMaxPulseWidth;
  unsigned int  ultPulseWidthTimer;
  unsigned int  ultDetectDurationTimer;
  unsigned int  ultDDurationTime;
  unsigned int  UltraEvent[2];
  unsigned int  ultCheckTimer;
  unsigned char ultSample;				
  unsigned char ultAvgSampleCnt;
  unsigned char SampleAvg_check;


  unsigned char ultAvgSample[SIZEOF_ULTAVESAMP_BUF];


} Usonic;

/*
unsigned char ReadADC8Bit(char AD_CHANNEL)
	{
		
		char adResult;
		ADMUX  = AD_CHANNEL | ADC_VREF_TYPE;
		ADCSRA = ADCSRA_INIT;
		ADCSRA |= (1<<ADEN);
		ADCSRA |= (1<<ADSC);
		while(!(ADCSRA & (1<<ADIF)));	//wait for conversion done, ADIF flag active
		adResult = ADCH;
		g_temp = adResult;
		return adResult;
	}
*/

void US_SENSE_SET(void)
{
	
	switch(KO_conf.USSens)
	{
		case 0:
			Usonic.ultwindow = LOW_USSENSITIVITY;
			break;
		case 1:
			Usonic.ultwindow = Medium_USSENSITIVITY;
			break;	
		case 2:
			Usonic.ultwindow = HIGH_USSENSITIVITY;
			break;	
		case 3:
			Usonic.ultwindow = MAX_USSENSITIVITY;
			 break;
		default:
			Usonic.ultwindow = HIGH_USSENSITIVITY;
			break;
			
	}
}		


void ultWarmUpEvents( void )
{
	unsigned char i;

	Usonic.fULTOCCDetected = DISABLED;
	Usonic.fULTSampleCounter = OP1_SMPAVG;
	
	Usonic.fULTdetectPulse = DISABLED;
	Usonic.fULTdetDurationSet = DISABLED;
	Usonic.fULTdetectEnable = ENABLED;	      		//调试程序是将Usonic.fULTdetectEnable使能
	
	Usonic.ultwindow = HIGH_USSENSITIVITY ;       // set the Sensitibity of Usonicsonic
	
	Usonic.ultHAvgSamples =  0x29;                // 正常的平均偏置值：when Vcc=5.0V and for 8 bit res ADC to get 820mV :  from .82/(5.0/255)= OX29
	
	Usonic.ultIndivSampleCount = 0;
	Usonic.ultSensorSampleValue = 0;
	Usonic.ultOccDetectionCount = 0;
	
	// Usonic.ultCheckTimer = TULTCHECK;
	Usonic.ultMinPulseWidth = MINPULSEWTH;
	Usonic.ultMaxPulseWidth = MAXPULSEWTH;
	
	Usonic.ultDDurationTime = TDETCTDURATION;
	Usonic.ultPulseWidthTimer = 0;
	Usonic.ultDetectDurationTimer = 0;
	Usonic.ultSample =0;
	Usonic.ultAvgSampleCnt =0;
	Usonic.ultFlags = 1;

	for ( i= 0; i<= (SIZEOF_ULTAVESAMP_BUF-1) ; i++)
	{     // clear RAM locations
		Usonic.ultAvgSample[i] = 0;
	}

}

/*
void ulrStoreSampleAvg (void)
{
	unsigned char readUltSample;
	unsigned char opISampleCnt;
	
	readUltSample = ReadADC8Bit (ADC_ULTRA);
	Usonic.ultSensorSampleValue = Usonic.ultSensorSampleValue + (unsigned int) readUltSample;
	Usonic.ultIndivSampleCount++; // 计算采集信号的次数，当采集数目与设定的OPx_NUMSAMPAVG相等后，才可以做平均计算
	
	  //opISampleCnt = Usonic.ultFlags & ISAMPLECNT_MASK;
		
	opISampleCnt = 1;		//debug...
	switch  ( opISampleCnt )
	{
		
     case 1:
			if ( Usonic.ultIndivSampleCount == OP2_NUMSAMPAVG)
			{        					
				Usonic.ultSensorSampleValue = ((Usonic.ultSensorSampleValue) >> OP2_AVGSHIFT ); // get the Op2 average      	
				Usonic.ultIndivSampleCount = 0;
				if(++Usonic.ultSample >= 19)
					Usonic.ultSample = 0;
				Usonic.ultAvgSample[Usonic.ultSample] = Usonic.ultSensorSampleValue;
				Usonic.ultSensorSampleValue = 0;
				Usonic.ultAvgSampleCnt = OP2_NUMSAMPAVG;
      }
		    break;

     case 0:
			if ( Usonic.ultIndivSampleCount == OP1_NUMSAMPAVG)
			{
				// Check Sample counter for Option 1
				Usonic.ultSensorSampleValue = ((Usonic.ultSensorSampleValue) >> OP1_AVGSHIFT );      	
				Usonic.ultIndivSampleCount = 0;            // reset indi sample counter
				Usonic.ultSample++;                         // Adjust next address to be stored
				Usonic.ultAvgSample[Usonic.ultSample] = Usonic.ultSensorSampleValue; // put it in to array
				Usonic.ultSensorSampleValue = 0;
				Usonic.ultAvgSampleCnt = OP1_NUMSAMPAVG;        //用于计算有效信号的宽度
                        }
		     break;
					
		
	
		case 2:
			if( Usonic.ultIndivSampleCount == OP3_NUMSAMPAVG)
			{      	
				Usonic.ultSensorSampleValue = ((Usonic.ultSensorSampleValue) >> OP3_AVGSHIFT ); // get the Op3 average
				Usonic.ultIndivSampleCount = 0;
				Usonic.ultSample++;
				Usonic.ultAvgSample[Usonic.ultSample] = Usonic.ultSensorSampleValue;
				Usonic.ultSensorSampleValue = 0;
				Usonic.ultAvgSampleCnt = OP3_NUMSAMPAVG;
			}
		    break;
	
		case 3:
			if ( Usonic.ultIndivSampleCount == OP4_NUMSAMPAVG)
			{     	 	
				Usonic.ultSensorSampleValue = ((Usonic.ultSensorSampleValue) >> OP4_AVGSHIFT ); // get the Op4 average	 	      					
				Usonic.ultIndivSampleCount = 0;
				Usonic.ultSample++;
				Usonic.ultAvgSample[Usonic.ultSample] = Usonic.ultSensorSampleValue;
				Usonic.ultSensorSampleValue = 0;
				Usonic.ultAvgSampleCnt = OP4_NUMSAMPAVG;		//用于计算脉冲宽度
			}
		    break;

      default:   break;

	}
}

// call this  Ultrasonic detection is necessary for every 4mSec via CompA interrrupt
void ServiceUltra (void)
{
  unsigned char i, VoltageTHold,ultDetectCnt ;
  unsigned int  instPulseTimer;

  Usonic.fULTdetectPulse = DISABLED;     // Every 4mSec segment start with search for new pulse detection
  Usonic.ultPulseWidthTimer =0;
			
  VoltageTHold = Usonic.ultHAvgSamples + Usonic.ultwindow;
			
  for( i=0 ; i <= SIZEOF_ULTAVESAMP_BUF-1 ; i++ )
	{
     if(Usonic.ultAvgSample[i] >= VoltageTHold)
     {
          Usonic.ultPulseWidthTimer++;
					instPulseTimer = (Usonic.ultPulseWidthTimer *((unsigned int)Usonic.ultAvgSampleCnt)*T50USEC) ;
                      // calculate instant pulse with by using time between two Averages Samples
		      if (instPulseTimer  >= Usonic.ultMinPulseWidth )
					{
              if(Usonic.fULTdetectPulse == DISABLED )
							{
								Usonic.fULTdetectPulse = ENABLED;					// 这一组数据中已经统计到第一个有效信号
				        Usonic.ultPulseWidthTimer = 0;          	// reset the pulse width timer
          		}
							if (Usonic.fULTdetDurationSet == DISABLED)
							{
             		Usonic.fULTdetDurationSet = ENABLED;			//允许之后的使能判断程序
             		Usonic.ultDetectDurationTimer = 0;		
             		Usonic.ultOccDetectionCount = 1;        	// 检测到第一个有效信号后，开始计算有效的脉冲个数
         			}

			        Usonic.ultOccDetectionCount++;       				// 统计有效的触发信号
					}
		}     // end of Vth check
    else
		{
        Usonic.ultPulseWidthTimer= 0;
				Usonic.fULTdetectPulse = DISABLED;
    }
	}  // end of For loop for every average sample collected
		
		
		
	if( Usonic.fULTdetDurationSet == ENABLED )
	{		
			Usonic.ultDetectDurationTimer++;		
			//每100ms进行一次触发信号的统计判断，判断以后会将 Usonic.ultOccDetectionCount清零。所以尽量多采集数据
      if( Usonic.ultDetectDurationTimer >= Usonic.ultDDurationTime )
			{							
			// Usonic.ultDDurationTime = TDETCTDURATION = 25*4 MS
			Usonic.ultDetectDurationTimer= 0;           // Reset detection counter
			Usonic.fULTdetDurationSet = DISABLED;        // Clear flag for detection duration enable

			ultDetectCnt = 1;  	//调试...	
			switch( ultDetectCnt )
			{

          case 1:
              if (Usonic.ultOccDetectionCount >= OP2_ULTDETECT )
              {
										//Motion.US_DETECTION = 1;
										us_result = 1;
										Usonic.ultOccDetectionCount = 0;
              }
              break;
                       	
                              case 0:
                                    if (Usonic.ultOccDetectionCount >= OP1_ULTDETECT )
                                    {
                                            //Motion.US_DETECTION = ENABLED;
                                            us_result = 1;
                                            Usonic.ultOccDetectionCount = 0;
                                    }
                                  break;
										


                              case 2:
                                  if (Usonic.ultOccDetectionCount >= OP3_ULTDETECT )
				    											{
                                         us_result = 1;
																					Usonic.ultOccDetectionCount = 0;
                                  }
                                break;

                              case 3:
                                  if (Usonic.ultOccDetectionCount >= OP4_ULTDETECT )
                                  {
                                         us_result = 1;
                                         Usonic.ultOccDetectionCount = 0;
                                  }
                              break;

                              default:break;
                        }
                }
							else
							{
                    us_result = 0;
            	}
        }
		else
        {
               us_result = 0;
        }

         if(us_result == 1)
					 US_detection_en = 1;
}



void us_detection(void)//SIGNAL(TIMER0_COMPA_vect)		
{			
	
	if(1)//Usonic.fULTdetectEnable == 1)
	{	
		
	  	US_SENSE_SET();
		
	  	ulrStoreSampleAvg();
		
		if(Usonic.SampleAvg_check++ >= TULTCHECK)		//20 X 200 uSec = 4mSec,每4ms调用一次
		{
			Usonic.SampleAvg_check = 0;
			
			ServiceUltra ();		
		}
		
	}	
}
*/


/*******************************************************************************
**		US 程序更新 0615
*******************************************************************************/

void Ultrasonic_detection (void)
{
		unsigned char 	readUltSample;
		unsigned char 	VoltageTHold;
		unsigned int		Pulse_width_Timer;
			
		// ReadADC8Bit (ADC_ULTRA);
		 asm("nop");
		 readUltSample = read_adc8bit(ADC_ULTRA);
		 Usonic.ultSensorSampleValue = Usonic.ultSensorSampleValue + readUltSample;
	
		 if ( ++Usonic.ultIndivSampleCount == OP1_NUMSAMPAVG	) 		//											// 4 signals for 1 AvgSample
		 {        					
					Usonic.ultIndivSampleCount = 0;
					Usonic.ultSensorSampleValue = ((Usonic.ultSensorSampleValue) >> OP1_AVGSHIFT ); 						// get the Op2 average      	
				
					Usonic.ultAvgSample[Usonic.ultSample] = Usonic.ultSensorSampleValue;						// 4 signals every AvgSample	---> 4*20	
					Usonic.ultSensorSampleValue = 0;
					Usonic.ultAvgSampleCnt = OP2_NUMSAMPAVG;
				
					VoltageTHold = Usonic.ultHAvgSamples + Usonic.ultwindow;
					if( Usonic.ultAvgSample[Usonic.ultSample] > VoltageTHold )											// calculate the pulse width
					{
							Usonic.ultPulseCount++;
					
							Usonic.ultPulseWidthTimer++;
						
							Pulse_width_Timer = (Usonic.ultPulseWidthTimer * (Usonic.ultAvgSampleCnt) * T200USEC);		// MAX = 20*4*200 = 16000	// MIN = 1*4*200 = 800
					}
					else
					{
							if(Pulse_width_Timer >= MAXPULSEWTH )
							{
									Usonic.ultmaxCount++;																					// 统计最长的有效脉冲		validly detection
							}	
							else if (Pulse_width_Timer >= MIDPULSEWTH )
							{
									Usonic.ultminCount++;       																	// 统计最窄有效脉冲个数						
							}	
							else if(Pulse_width_Timer >= MINPULSEWTH )
							{
									Usonic.ultmidCount++;																					// 统计中等有效脉冲个数
							}
					
							Usonic.ultPulseWidthTimer= 0;
							Pulse_width_Timer = 0;
					}
				
					if(++Usonic.ultSample >= 19)																					// 20*OPn_NUMSAMPAVG个采样信号。
					{
							Usonic.ultSample = 0;
							if((Usonic.ultmaxCount > 0)||(Usonic.ultPulseCount > ValidPulses_Threshold)
								 ||(Usonic.ultminCount > MIN_Threshold)||(Usonic.ultmidCount > MID_Threshold))
							{
									us_result = 1;				// validly detection
							}
							else
							{
									us_result = 0;				// invalidly detection
									Usonic.ult_nodetectCount++;							
							}
							
							if((us_result == 1)||(Usonic.ult_nodetectCount >=5))							// Judgement space = 20*OPn_NUMSAMPAVG or 5*20*OPn_NUMSAMPAVG
							{
								Usonic.ultminCount	= 0;
									Usonic.ultmidCount = 0;
										Usonic.ultmaxCount= 0;
											Usonic.ultPulseCount = 0;
												Usonic.ult_nodetectCount = 0;
												
							}
					}
     }
		
		 if(us_result == 1)		 US_detection_en = 1;
	
}


void us_detection(void)
{			
	  US_SENSE_SET();
		
		Ultrasonic_detection ();
}