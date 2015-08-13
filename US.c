
/*
	������ģ��ĵ���������200us

 G_Ult_detectionEnable  Motion.US_sensitivityҪ�����ȫ�ֱ���

 SIZEOF_ULTAVESAMP_BUF
 ADC_ULTRA,TDETCTDURATION,MINPULSEWTH,TULTCHECK,DETECTCNTOP2,T50USEC
 OP1_SMPAVG,OP1_NUMSAMPAVG,OP2_NUMSAMPAVG,OP3_NUMSAMPAVG,OP4_NUMSAMPAVG
 OP1_ULTDETECT��OP2_ULTDETECT��OP3_ULTDETECT��OP4_ULTDETECT��
 OP1_AVGSHIFT��OP2_AVGSHIFT��OP3_AVGSHIFT��OP4_AVGSHIFT��

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
	Usonic.fULTdetectEnable = ENABLED;	      		//���Գ����ǽ�Usonic.fULTdetectEnableʹ��
	
	Usonic.ultwindow = HIGH_USSENSITIVITY ;       // set the Sensitibity of Usonicsonic
	
	Usonic.ultHAvgSamples =  0x29;                // ������ƽ��ƫ��ֵ��when Vcc=5.0V and for 8 bit res ADC to get 820mV :  from .82/(5.0/255)= OX29
	
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
	Usonic.ultIndivSampleCount++; // ����ɼ��źŵĴ��������ɼ���Ŀ���趨��OPx_NUMSAMPAVG��Ⱥ󣬲ſ�����ƽ������
	
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
				Usonic.ultAvgSampleCnt = OP1_NUMSAMPAVG;        //���ڼ�����Ч�źŵĿ��
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
				Usonic.ultAvgSampleCnt = OP4_NUMSAMPAVG;		//���ڼ���������
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
								Usonic.fULTdetectPulse = ENABLED;					// ��һ���������Ѿ�ͳ�Ƶ���һ����Ч�ź�
				        Usonic.ultPulseWidthTimer = 0;          	// reset the pulse width timer
          		}
							if (Usonic.fULTdetDurationSet == DISABLED)
							{
             		Usonic.fULTdetDurationSet = ENABLED;			//����֮���ʹ���жϳ���
             		Usonic.ultDetectDurationTimer = 0;		
             		Usonic.ultOccDetectionCount = 1;        	// ��⵽��һ����Ч�źź󣬿�ʼ������Ч���������
         			}

			        Usonic.ultOccDetectionCount++;       				// ͳ����Ч�Ĵ����ź�
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
			//ÿ100ms����һ�δ����źŵ�ͳ���жϣ��ж��Ժ�Ὣ Usonic.ultOccDetectionCount���㡣���Ծ�����ɼ�����
      if( Usonic.ultDetectDurationTimer >= Usonic.ultDDurationTime )
			{							
			// Usonic.ultDDurationTime = TDETCTDURATION = 25*4 MS
			Usonic.ultDetectDurationTimer= 0;           // Reset detection counter
			Usonic.fULTdetDurationSet = DISABLED;        // Clear flag for detection duration enable

			ultDetectCnt = 1;  	//����...	
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
		
		if(Usonic.SampleAvg_check++ >= TULTCHECK)		//20 X 200 uSec = 4mSec,ÿ4ms����һ��
		{
			Usonic.SampleAvg_check = 0;
			
			ServiceUltra ();		
		}
		
	}	
}
*/


/*******************************************************************************
**		US ������� 0615
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
									Usonic.ultmaxCount++;																					// ͳ�������Ч����		validly detection
							}	
							else if (Pulse_width_Timer >= MIDPULSEWTH )
							{
									Usonic.ultminCount++;       																	// ͳ����խ��Ч�������						
							}	
							else if(Pulse_width_Timer >= MINPULSEWTH )
							{
									Usonic.ultmidCount++;																					// ͳ���е���Ч�������
							}
					
							Usonic.ultPulseWidthTimer= 0;
							Pulse_width_Timer = 0;
					}
				
					if(++Usonic.ultSample >= 19)																					// 20*OPn_NUMSAMPAVG�������źš�
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