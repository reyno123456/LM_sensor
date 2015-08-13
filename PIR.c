#include <ioavr.h>
#include <inavr.h>
#include "PIR.h"
#include "board.h"
#include "moudle_SCS.h"
#include "global_variable.h"
#include "application.h"


void PIR_SENSE_SET(void)
{
		
		switch(KO_conf.PirSens)	// the value of global variable "INDEX_PIR_SENSITIVITY" is decided by the user via SCS. 
		{
			case 0:
				pir.window = LOW_PIRSENSITIVITY;
				break;
			case 1:
				pir.window = Medium_PIRSENSITIVITY;
				break;
			case 2:
				pir.window = HIGH_PIRSENSITIVITY;
				break;
			case 3:
				pir.window = MAX_PIRSENSITIVITY;
				break;
			default: 
				pir.window = Medium_PIRSENSITIVITY;
				break;
		}
}		 

unsigned char PIR_detect(void)
	{
		static unsigned int ucLastPIRSample = 0;
		static unsigned int ucCurrentPIRSample = 0;
		static unsigned int ucThreshHold=0;
		static unsigned int ucLastLastHighLength = 0;
		static unsigned int ucLastHighLength = 0;
		static unsigned int ucCurHighLength = 0;
		static unsigned int ucLastLowLength = 0;
		static unsigned int ucCurLowLength = 0;

		PIR_SENSE_SET();
/***************************************************
**		for sensor without LM020
**    add on 0525
***************************************************/	
		if(1)//(pir.fPIRdetectionEnable == 1)    //the signal of Warm up
		{
		  pir.fPIROCCDetected = 0;
		  ucThreshHold=pir.window;
		  ucLastPIRSample = ucCurrentPIRSample;
		  ucCurrentPIRSample = read_adc8bit(PIR_SENSE);
			asm("nop");
			ucCurrentPIRSample = read_adc8bit(PIR_SENSE);		// add 0603
			
		  if (ucCurrentPIRSample >= PIR_CENTER)
				ucCurrentPIRSample -= PIR_CENTER;
		  else      
				ucCurrentPIRSample = PIR_CENTER - ucCurrentPIRSample;
				
			if (ucCurrentPIRSample >= ucThreshHold)    			//当前PIR信号大于设定值
			{
				if (ucLastPIRSample < ucThreshHold)  			//但前次信号小于设定值时，令当前信号高部分重新变为一
				{
					ucLastLastHighLength = ucLastHighLength;
					ucLastHighLength = ucCurHighLength;
					ucCurHighLength = 1;
				}
				else if (ucCurHighLength > 0)        		 	//当前PIR信号大于设定值，且前次信号也大于设定值，
				{                                    			//且信号高部分大于零  
					ucCurHighLength++;               		 		//自加35次，MID_WIDTH的值为35
					if (ucCurHighLength >= MID_WIDTH)  			//且信号高部分持续时间大于设定的时间宽度时，PIR触发
					{
					  pir.fPIROCCDetected= 1;               	// alan debug  1;  
					  ucCurHighLength = 0;
						//DLED_ON;
						//delay_ms(200);
						//DLED_OFF;
					}
				}
			}
			else                                      			//当前PIR信号小于设定值
			{	
				if (ucLastPIRSample >= ucThreshHold)   			//当前PIR信号小于设定值，但前次信号大于设定值时
				{
					if (((ucLastHighLength >= MIN_WIDTH) && (ucCurHighLength >= MIN_WIDTH) && ((ucLastHighLength >= MIN_SPACE) || (ucCurHighLength >= MIN_SPACE)) && (ucLastHighLength + ucCurLowLength + ucCurHighLength <= MAX_WIDTH)) 
								|| ((ucLastLastHighLength >= MIN_WIDTH) && (ucLastHighLength >= MIN_WIDTH) && (ucCurHighLength >= MIN_WIDTH) && (ucLastLastHighLength + ucLastLowLength + ucLastHighLength + ucCurLowLength + ucCurHighLength <= MAX_WIDTH)))
					{
					      pir.fPIROCCDetected= 1;		// alan debug  1;  1;  
					      ucCurLowLength = 0;
					      ucCurHighLength = 0;
								//DLED_ON;
								//delay_ms(200);
								//DLED_OFF;
					}
					else
					{
							ucLastLowLength = ucCurLowLength;
							ucCurLowLength = 1;
					}
				}
				else if (ucCurLowLength > 0)      				//当前PIR信号小于设定值，且前次信号也小于设定值，且信号底部宽度大于零
					ucCurLowLength += (ucCurLowLength >= MAX_WIDTH) ? 0 : 1;
				                                 
			}
		}
                
    if(pir.fPIROCCDetected == 1)    
		{
	  	PIR_detection_en = 1;     		// add by alan 20090409          
			return pir.fPIROCCDetected; //reyno 20090527
		}
	
	
/***************************************************
**		for LM020 PIR2			
**    add on 0525
***************************************************/	
#ifdef LM020					// 0525
		
		static unsigned int Pir2_ucLastPIRSample = 0;
		static unsigned int Pir2_ucCurrentPIRSample = 0;
		static unsigned int Pir2_ucThreshHold=0;
		static unsigned int Pir2_ucLastLastHighLength = 0;
		static unsigned int Pir2_ucLastHighLength = 0;
		static unsigned int Pir2_ucCurHighLength = 0;
		static unsigned int Pir2_ucLastLowLength = 0;
		static unsigned int Pir2_ucCurLowLength = 0;
		if(1)//(pir.fPIRdetectionEnable == 1)    //the signal of Warm up
		{
		  pir.fPIROCCDetected = 0;
		  Pir2_ucThreshHold=pir.window;
		  Pir2_ucLastPIRSample = Pir2_ucCurrentPIRSample;
		  Pir2_ucCurrentPIRSample = read_adc8bit(PIR2_SENSE);

		  if (Pir2_ucCurrentPIRSample >= PIR_CENTER)
				Pir2_ucCurrentPIRSample -= PIR_CENTER;
		  else      
				Pir2_ucCurrentPIRSample = PIR_CENTER - Pir2_ucCurrentPIRSample;
				
			if (Pir2_ucCurrentPIRSample >= Pir2_ucThreshHold)    			
			{
				if (Pir2_ucLastPIRSample < Pir2_ucThreshHold)  			
				{
					Pir2_ucLastLastHighLength = Pir2_ucLastHighLength;
					Pir2_ucLastHighLength = Pir2_ucCurHighLength;
					Pir2_ucCurHighLength = 1;
				}
				else if (Pir2_ucCurHighLength > 0)        		 
				{                                    			
					Pir2_ucCurHighLength++;               		 		
					if (Pir2_ucCurHighLength >= MID_WIDTH)  			
					{
					  pir.fPIROCCDetected= 1;               
					  Pir2_ucCurHighLength = 0;
					}
				}
			}
			else                                      			//当前PIR信号小于设定值
			{	
				if (Pir2_ucLastPIRSample >= Pir2_ucThreshHold)   			
				{
					if (((Pir2_ucLastHighLength >= MIN_WIDTH) && (Pir2_ucCurHighLength >= MIN_WIDTH) && ((Pir2_ucLastHighLength >= MIN_SPACE) || (Pir2_ucCurHighLength >= MIN_SPACE)) && (Pir2_ucLastHighLength + Pir2_ucCurLowLength + Pir2_ucCurHighLength <= MAX_WIDTH)) 
								|| ((Pir2_ucLastLastHighLength >= MIN_WIDTH) && (Pir2_ucLastHighLength >= MIN_WIDTH) && (Pir2_ucCurHighLength >= MIN_WIDTH) && (Pir2_ucLastLastHighLength + Pir2_ucLastLowLength + Pir2_ucLastHighLength + Pir2_ucCurLowLength + Pir2_ucCurHighLength <= MAX_WIDTH)))
					{
					      pir.fPIROCCDetected= 1;		
					      Pir2_ucCurLowLength = 0;
					      Pir2_ucCurHighLength = 0;
					}
					else
					{
							Pir2_ucLastLowLength = Pir2_ucCurLowLength;
							Pir2_ucCurLowLength = 1;
					}
				}
				else if (Pir2_ucCurLowLength > 0)      				
					Pir2_ucCurLowLength += (Pir2_ucCurLowLength >= MAX_WIDTH) ? 0 : 1;                            
			}
		}
                
     if(pir.fPIROCCDetected == 1)    
		{
	  	PIR_detection_en = 1;     		// add on 0525       
		}
		
		
#endif
		return pir.fPIROCCDetected;
}
