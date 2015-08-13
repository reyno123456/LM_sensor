#include "global_variable.h"
#include "application.h"
#include "moudle_SCS.h"
#include <ioavr.h>
#include "board.h"
#include "PIR.h"
#include <string.h>
#include "decode_scs.h"
#include "IR.h"
#include "decode_scs_next.h"
#include "configuration.h"
#include "usart.h"
#include "function_service.h"
#include "iccext.h"
#include <math.h>
#include "DRI_LCD.h"

void factory_calibration()
{
	unsigned int temp1;
	unsigned int temp2;

	if(state.main_state == FACTORY_CALIBRATION)
	{
		get_dl_level();
		if(g_asc_reception_buffer[3] == 0x42 && g_asc_reception_buffer[4] == 0x10)
		{
			ee_factory_variable.adc_1 = DLL.day_level;
			ee_factory_variable.lux_1 = g_asc_reception_buffer[6];
			ee_factory_variable.lux_1 = ee_factory_variable.lux_1 << 8;
			ee_factory_variable.lux_1 += g_asc_reception_buffer[7];
			state.main_state = FACTORY_CALIBRATION_STEP1;
			ee_main_state = FACTORY_CALIBRATION_STEP1;
			buzzer_ms(500);
		}
	}
	else if(state.main_state == FACTORY_CALIBRATION_STEP1)
	{
		get_dl_level();
		if(g_asc_reception_buffer[3] == 0x42 && g_asc_reception_buffer[4] == 0x10)
		{
			ee_factory_variable.adc_2 = DLL.day_level;
			ee_factory_variable.lux_2 = g_asc_reception_buffer[6];
			ee_factory_variable.lux_2 = ee_factory_variable.lux_2 << 8;
			ee_factory_variable.lux_2 += g_asc_reception_buffer[7];
			temp2 =  ee_factory_variable.lux_2 - ee_factory_variable.lux_1;
			temp1 =  ee_factory_variable.adc_2 - ee_factory_variable.adc_1;
			g_slope = (double)temp2 / (double)temp1 ;
			//g_slope = (short)((ee_factory_variable.lux_2 - ee_factory_variable.lux_1)/(ee_factory_variable.adc_2 - ee_factory_variable.adc_1));
			ee_slope = g_slope;
			ee_product_information.factory_calibrated = 1;
			buzzer_ms(500);
		}
	}
}

//used in the light calibration(now have been discard)
// D5 00 EE x3 10 0x 22 22		low
// D5 00 EE x3 10 0x 33 33 		medium
// D5 00 EE x3 10 0x 44 44		high

// Enter calibration waiting mode	D1 01 01 42 14 00 00 00
// Exit calibration waiting mode	D1 01 01 42 14 00 00 FF
// Sent calibration lux						D1 01 01 42 10 0X XX XX

//******************************************************************************
// send the frame ON, OFF, Pre, and NO_PRE
//******************************************************************************
void Mode_frame_GR(char GG, char type)
{
	// B5 GG  12 00 "ON"							// Mode_frame_GR(KO_conf.GR,ON);
	// B5 GG  12 01 "OFF"							// Mode_frame_GR(KO_conf.GR,OFF);
	// B5 GG  1D 00 "presence"				// Mode_frame_GR(KO_conf.GR,pre);
	// B5 GG  1D 01 "no presence"			// Mode_frame_GR(KO_conf.GR,nopre);
  // B8 APL 1D 00 "presence for modality"
	
	unsigned char TX_buffer[8];
	unsigned char buffer[2];
	
	if(KO_conf.AddressType == GROUP)		// GR
	{
    CharToStr(GG ,buffer);
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];

		switch(type)
		{
			case pre:
			case Gs1:
			case Gs2:
					TX_buffer[5] = 'D';
					TX_buffer[7] = '0';
			break;
			case ON:
					TX_buffer[5] = '2';
					TX_buffer[7] = '0';
					Sensor_mode.power_on_flag = 1;		// ON FRAME
					//KO_conf.status[1] = Status_ON;		//reyno 0616
					//DLL.lightness_load = T_5min5s;		// start timer 5min5s, start to calibrate the load provision
					//DLL.calc_OK_flag = 0; //reyno 0616
			 break;
			case OFF:
					TX_buffer[5] = '2';
					TX_buffer[7] = '1';
					Sensor_mode.power_on_flag = 0;		// OFF FRAME
					KO_conf.status[1] = Status_OFF;		//reyno 0616
			break;
			case nopre:
					TX_buffer[5] = 'D';
					TX_buffer[7] = '1';
				break;
			default: break;
		}
	
		TX_buffer[0] = 'B';
		TX_buffer[1] = '5';
		TX_buffer[4] = '1';
		TX_buffer[6] = '0';
	}
	else if(KO_conf.AddressType == PP && type==pre)	//P2P
	{
			// B8 APL 1D 00
		TX_buffer[0] = 'B';
		TX_buffer[1] = '8';
    //TX_buffer[2] = Configurators.A;
    //TX_buffer[3] = Configurators.PL;
		CharToStr(KO_conf.DesAdd,buffer);  //reyno 0619
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];
		TX_buffer[4] = '1';
		TX_buffer[5] = 'D';
		TX_buffer[6] = '0';
		TX_buffer[7] = '0';
	}
	
	send_frame_pp_broad(TX_buffer, TRANS_DELAY);
	
	if(type == OFF)		// frame "OFF"
	{
			Time_delay.detect_waitting = OFF_delay_2s;
	}
	if(type == pre)
	{
		Sensor_mode.presence_send =1;
	}
	
}


//******************************************************************************
// 			send the frame P2P
//******************************************************************************
void dimmer_command(unsigned char arg,unsigned char level_value)
{
	// D1 A|Pl 0|1 4|2 0|D 0|0 0|0 0|0 	"ON"					// Mode_frame_P2P('1','2','0','0','0','0','0');
	// D1 A|Pl 0|1 4|2 0|D 0|1 0|0 0|0 	"OFF"					// Mode_frame_P2P('1','2','1','0','0','0','0');
	// D1 A|Pl 0|1 4|2 0|D 0|3 0|2 F|F 	"DIM +"				// Mode_frame_P2P('1','2','3','0','2','F','F');		step == 2	speed==default
	// D1 A|Pl 0|1 4|2 0|D 0|4 0|1 F|F	"DIM -"				// Mode_frame_P2P('1','2','4','0','1','F','F');		step == 1	speed==default
  // D1 A|Pl 0|1 4|2 0|D 0|D X|X F|F	"LEVEL"				// Mode_frame_P2P('1','2','D','X','X','F','F');
	unsigned char buffer_tx[17];
	unsigned char buffer[3];
	strncpy(buffer_tx,"D10001420D000000",17);
	
	if(KO_conf.AddressType == GROUP)
	{	
		CharToStr(KO_conf.Reference,buffer);
		buffer_tx[2] = buffer[0];
		buffer_tx[3] = buffer[1];
	}
	else
	{
		CharToStr(KO_conf.DesAdd,buffer);
		buffer_tx[2] = buffer[0];
		buffer_tx[3] = buffer[1];
	}
	
	switch(arg)
	{
		case ON:
			Sensor_mode.power_on_flag = 1;		    // ON FRAME
			SCS_received.update_on_wait++;
			org_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case OFF:
			buffer_tx[11] = '1';
			Sensor_mode.power_on_flag = 0;						// OFF FRAME
			KO_conf.status[1] = Status_OFF;
			SCS_received.update_off_wait++;
			org_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case DIM_UP:
			buffer_tx[11] = '3';
			buffer_tx[13] = '2';
			buffer_tx[14] = 'F';
			buffer_tx[15] = 'F';
			org_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case DIM_DOWN:
			buffer_tx[11] = '4';
			buffer_tx[13] = '1';
			buffer_tx[14] = 'F';
			buffer_tx[15] = 'F';
			org_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case LEVEL:
			buffer_tx[11] = 'D';
			CharToStr(level_value,buffer);
			buffer_tx[12] = buffer[0];
			buffer_tx[13] = buffer[1];
			buffer_tx[14] = 'F';
			buffer_tx[15] = 'F';
			org_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		default:break;
	}
}

void Mode_frame_P2P(char type,char cmd,char func0, char func1,char func2 ,char func3,char func4)	//Frame for referent:
{
	// D1 A|Pl 0|1 4|2 0|D 0|0 0|0 0|0 	"ON"					// Mode_frame_P2P('1','2','0','0','0','0','0');
	// D1 A|Pl 0|1 4|2 0|D 0|1 0|0 0|0 	"OFF"					// Mode_frame_P2P('1','2','1','0','0','0','0');
	// D1 A|Pl 0|1 4|2 0|D 0|3 0|2 F|F 	"DIM +"				// Mode_frame_P2P('1','2','3','0','2','F','F');		step == 2	speed==default
	// D1 A|Pl 0|1 4|2 0|D 0|4 0|1 F|F	"DIM -"				// Mode_frame_P2P('1','2','4','0','1','F','F');		step == 1	speed==default
  // D1 A|Pl 0|1 4|2 0|D 0|D X|X F|F	"LEVEL"				// Mode_frame_P2P('1','2','D','X','X','F','F');

	unsigned char TX_buffer[16];
	unsigned char buffer[2];

	if(func0 == '0') 	
	{
			Sensor_mode.power_on_flag = 1;		    // ON FRAME
			//KO_conf.status[1] = Status_ON;		//reyno 0616
			SCS_received.update_on_wait++;
			//DLL.lightness_load = T_5min5s;				// start timer 5min5s, start to calibrate the load provision
			//DLL.calc_OK_flag = 0; //reyno 0616
	}
	else if(func0 == '1')
	{
		Sensor_mode.power_on_flag = 0;						// OFF FRAME
		KO_conf.status[1] = Status_OFF;		//reyno 0616
		SCS_received.update_off_wait++;
	}

	if((product_information.conf_type == 1)||(product_information.conf_type == 2))     						// configurate in advanced or Basic virtual
	{
		if((KO_conf.AddressType ==0)&&(KO_conf.DesAdd !=0 ))		CharToStr(KO_conf.DesAdd , buffer);		// P2P ON frame	
		if((KO_conf.AddressType ==2)&&(KO_conf.Reference !=0 ))	CharToStr(KO_conf.Reference, buffer);		// Parital ON frame		
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];
	}
	else if(product_information.conf_type == 0)     // configurate in Basic physical
	{
		//TX_buffer[2] = Configurators.A;
		//TX_buffer[3] = Configurators.PL;
		CharToStr(KO_conf.DesAdd,buffer);  //reyno 0619
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];
	}

	TX_buffer[0]  = 'D';
	TX_buffer[1]  = type;
	TX_buffer[4]  = '0';
	TX_buffer[5]  = '1';
	TX_buffer[6]  = '4';
	TX_buffer[7]  = cmd;
	TX_buffer[8]  = '0';
	TX_buffer[9]  = 'D';
	TX_buffer[10] = '0';
	TX_buffer[11] = func0;
	TX_buffer[12] = func1;
	TX_buffer[13] = func2;
	TX_buffer[14] = func3;
	TX_buffer[15] = func4;
	org_ext_broad(TX_buffer, TRANS_DELAY);
}

//******************************************************************************
// 			used for the modality 2
//******************************************************************************
void frame_M2_answer( unsigned char type)		// D5 GR 01 34 type xx xx xx
{
    	
  		unsigned char TX_buffer[16];
		unsigned char buffer[2];
    	unsigned char value1;
    	unsigned char value2;
    	unsigned char value3;

		TX_buffer[0]  = 'D';
		TX_buffer[1]  = '5';
		TX_buffer[4]  = '0';
		TX_buffer[5]  = '1';
		TX_buffer[6]  = '3';
		TX_buffer[7]  = '4';
		TX_buffer[8]  = '1';
		TX_buffer[9]  = type;
		CharToStr(KO_conf.GR, buffer);
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];

        if(type == '0')     // M2_daylight level
        {
              value1 =  0;
              value2 =  (DLL.current_level&0xFF00)>>8;
              value3 =  DLL.current_level&0x00FF;
			  // the value should be == DLL.current_level*5
        }
        if(type == '5')     // Sensitivity
        {
              value1 =  0;
              value2 =  0;
              value3 =  eep_M2_sens;
        }
        if(type == '6')     // M2_timer
        {
              value1 =  eep_M2_hour;
              value2 =  eep_M2_min;
              value3 =  eep_M2_sec;
        }
		
		/*
        if((Configurators.A==0)&&(Configurators.PL==0))
	  	{
    		CharToStr(KO_conf.DesAdd, buffer);
			TX_buffer[2] = buffer[0];
			TX_buffer[3] = buffer[1];
	  	}
	  	else
	  	{
	  		TX_buffer[2] = Configurators.A;		// sensor in modality 2, A and PL must be insert
      		TX_buffer[3] = Configurators.PL;
	  	}  */
	
      	CharToStr(value1, buffer);
		TX_buffer[10] = buffer[0];
		TX_buffer[11] = buffer[1];
      	CharToStr(value2, buffer);
		TX_buffer[12] = buffer[0];
		TX_buffer[13] = buffer[1];
     		CharToStr(value3, buffer);
		TX_buffer[14] = buffer[0];
		TX_buffer[15] = buffer[1];

		send_frame_pp_ext_broad(TX_buffer, TRANS_DELAY);
      	M2_type = 0;            			// 帧发送完毕后清零标志位，针对modality

}

//******************************************************************************
// 		read the daylight level in calibration waitting mode
//******************************************************************************
void DLL_setpoint(unsigned char point)
{

  DLL.daylight_SampleCount = 0;		// the daylight level point should be gotten 10 points and averaged
	
  while(1)
	{
		get_dl_level();
		delay_ms(60);
		if(DLL.getlevel_finish == 1)
		{	
					switch(point)
      		{
         	 case  1://Low:
               DLL.setpoint_L = DLL.day_level;
               break;
           case  2://Medium:
               DLL.setpoint_M = DLL.day_level;
               break;
           case  3://High:
               DLL.setpoint_H = DLL.day_level;
               break;
           default : break;
         	}
         	eep_setpoint[point] = DLL.day_level;
         	daylight_set_init();        	
					break;
		}
	}
        buzzer_ms(500);	
        //  DLL.minstep = factor_divcalc(2000,(DLL.setpoint_H - DLL.setpoint_L));	
}


//******************************************************************************
//		result = x/y		Value xx.xx (00.01 ~ FF.FF)
//******************************************************************************
unsigned int factor_divcalc(unsigned int x,unsigned int y)		//result = x/y
{
	volatile static unsigned int result;
	volatile static unsigned int remainder;
	volatile static unsigned int Dec,Hex;
	
	Dec = 0;
	Hex = 0;
	result = 0;
	remainder = 0;
	if(x > y)		
	{
    result = x/y;
		result = result<<8;
		remainder = x%y;
		result += ((remainder*10)/y)<<4;
		remainder = (remainder*10)%y;
		result += (remainder*10)/y;
	}
	else			
	{
		if(x*10>y)
		{
			result = (x*10)/y;
			result = result<<4;
			remainder = (x*10)%y;
			result += (remainder*10)/y;															// result Hex
			
			Dec = ((result & 0x00F0)>>4)*10 + (result & 0x000F);		// translate 16 to 10
			Hex = Dec/16;
			remainder = (Dec%16)*5/8;																//remainder =(Dec%16)*10/16;
			result = ((Hex<<4) & 0x00FF) + remainder;
		}
		else if(x*100>y)
		{
			result = (x*100)/y;
		}
	}
	return result;
}

//******************************************************************************
//				result = x*y
//				result = x*y	y是factor,xx.xx,小数点后两位
//******************************************************************************
unsigned int factor_mulcalc(unsigned int x,unsigned int y)				
{
	unsigned int result=0;

	result = x*(y>>8) + x*((y&0x00F0)>>4)/10 + x*(y&0x000F)/100;

	return result;
}

//******************************************************************************
//					Regulation for actuator
//		after both load provision and setpoint had been calibrated
//******************************************************************************
void Actuator_regulation(void)
{
	//if( DLL.calc_OK_flag == 1 && Time_delay.timer_delay_set.enabled ==1 && DLL.start_regulation == 1 )			
	if( DLL.start_regulation == 1 )
	{
		if((DLL.current_level < set_point)&&(Sensor_mode.power_on_flag ==0))
		{
			Time_delay.DLL_low_20s_enable = 1;
			Time_delay.DLL_high_10min_enable = 0;
			if(Time_delay.DLL_low_20s_count > Regulation_20s)
			{
				Time_delay.DLL_low_20s_count = 0;
				Time_delay.DLL_low_20s_enable = 0;
				//if(Configurators.M == '1')	
				//if(KO_conf.LightReg == 1)
					//frame_pp_on_off('0');           				// send frame ON
				//else					
				//Mode_frame_P2P('1','2','0','0','0','0','0');			// send P2P ON frame light on the load
				dimmer_command(ON,0);
				regulation_timer_initial();
			}
		}
		else if((DLL.current_level > DLL.setpoint_OFF)&&(Sensor_mode.power_on_flag ==1)&&(DLL.calc_OK_flag == 1))
		{
			Time_delay.DLL_high_10min_enable = 1;
			Time_delay.DLL_low_20s_enable = 0;
			if(Time_delay.DLL_high_10min_count > Regulation_10min)						// 10min may be too long 	
			{
				Time_delay.DLL_high_10min_count = 0;
				Time_delay.DLL_high_10min_enable = 0;
				//if(Configurators.M == '1')	
				//	frame_pp_on_off('1');           				// send frame Off
				//else					
				//Mode_frame_P2P('1','2','1','0','0','0','0');			// send P2P OFF frame light on the load
				dimmer_command(OFF,0);
				//regulation_timer_initial();
			}
		}
		else
		{
			Time_delay.DLL_low_20s_enable = 0;
			Time_delay.DLL_low_20s_count = 0;
			Time_delay.DLL_high_10min_enable = 0;
			Time_delay.DLL_high_10min_count = 0;	
		}
	}
}

/******************************************************************************
**				Regulation for dimmer
** 			 	after setpoint calibrate finish	
** 			to maintain setpoint~(setpoint+20%)
**				DIM++ 	step==2
**				DIM-- 	step==1
****** 			DLL.current_level< setpoint		dim++ every 200ms
****** 			DLL.current_level> setpoint(1+20%)	dim-- every 20s
****** 			DLL.current_level> setpoint(1+40%)	dim-- every 40s
****** 			DLL.current_level> setpoint(1+40%)	and dim-- == 0, send "OFF"
******************************************************************************/
void Dimmer_regulation(void)												
{
	//unsigned char buffer[2];
  if( DLL.start_regulation == 1 )
	{
			if(KO_conf.TypeLoop == 0)           								// in close loop
			{
				if(DLL.current_level < set_point)														// < setpoint		dim++ every 200ms
				{
					Time_delay.Dim_inc_enable = 1;
					if(Time_delay.Dim_inc_count > Regulation_200ms)
					{
						Time_delay.Dim_inc_count = 0;
						Time_delay.Dim_inc_enable = 0;
						//if(SCS_received.P2P_dimmer_full != 1)
						if(KO_conf.status[1] != 0x64)
						{
							//Mode_frame_P2P('1','2','3','0','2','F','F');					// DIM++ 	step==2
							dimmer_command(DIM_UP,0);
							regulation_timer_initial();
							//SCS_received.P2P_dimmer_zero = 0;											// if DIM++ frame is sent, the flag SCS_received.P2P_dimmer_zero should be cleared
						}
						else
						{
							if(flags.dimmer_ON_sended == 0)
							{	
								dimmer_command(ON,0);
								regulation_timer_initial();
								flags.dimmer_ON_sended = 1;
							}
						}
					}
				}
				else if (DLL.current_level > (set_point + set_point/2))			// > setpoint(1+40%)	dim-- every 40s
				{
						flags.dimmer_ON_sended = 0;
						Time_delay.Dim_dec_enable = 1;
						//if(Time_delay.Dim_dec_count > Regulation_600ms)
						if(Time_delay.Dim_dec_count > Reg_dim_20s)
						{
							Time_delay.Dim_dec_count = 0;
							Time_delay.Dim_dec_enable = 0;
							if (KO_conf.status[1] == 1)
							{
								//Mode_frame_P2P('1','2','1','0','0','0','0'); //  OFF
								dimmer_command(OFF,0);
								//regulation_timer_initial();
							}
							else
							{
								if( KO_conf.status[1] != Status_OFF ) //Reyno 0626
								{
									//Mode_frame_P2P('1','2','4','0','1','F','F'); // DIM-- step==1
									dimmer_command(DIM_DOWN,0);
									regulation_timer_initial();
								}
							}
						}
				}
				else if(DLL.current_level > (set_point + set_point/5))			// > setpoint(1+20%)	dim-- every 20s
				{
						Time_delay.Dim_dec_enable = 1;
						//if(Time_delay.Dim_dec_count > Regulation_200ms)
						if(Time_delay.Dim_dec_count > Reg_dim_60s)
						{
							Time_delay.Dim_dec_count = 0;
							Time_delay.Dim_dec_enable = 0;
							if (KO_conf.status[1] > 1)
							{
								//Mode_frame_P2P('1','2','4','0','1','F','F'); // DIM-- step==1
								dimmer_command(DIM_DOWN,0);
								regulation_timer_initial();
							}
						}
				}
			}
			else if((KO_conf.TypeLoop == 1)&&(SCS_received.Daylight_lux ==1))   // in open loop
			{
				// For a ballast 0-10V
					SCS_received.Daylight_lux = 0;
					DLL.open_lightlevel = (DLL.open_lightlux & 0x000FFFFF)/5;
				// (lux sent by daylight sensor) / (daylight level set by user)
				if((KO_conf.DF ==0)&&(DLL.DF ==0))												//当第一次从close loop转到open loop时，我清零了DF
				{
					DLL.DF = DLL.open_lightlevel / KO_conf.DaylightLev;			// calculate the D.F in the openloop
					KO_conf.DF = DLL.DF;
					// should load this parameter into eep
					//write_ee_KO(22,KO_conf.DF);														// write_ee_KO(unsigned char index,unsigned char data);
				}
				else
				{
					DLL.open_actualevel = DLL.open_lightlevel / DLL.DF;			// calculate the actuallevel in the motion sensor area
					if(DLL.open_actualevel*5 > set_point)
					{
						//Mode_frame_P2P('1','2','1','0','0','0','0');					//  frame OFF
						dimmer_command(OFF,0);
					}
					else
					{
						DLL.open_offset = factor_divcalc((set_point - DLL.open_actualevel*5), DLL.load_provision*5);
						//CharToStr(DLL.open_offset ,buffer);
						//Mode_frame_P2P('1','2','D',buffer[0],buffer[1],'F','F');// Set level for dimmer
						dimmer_command(LEVEL,DLL.open_offset);
					}
				}
			}
	}
}

//******************************************************************************
//				send the frame dimmer--	,	step==1
//******************************************************************************
void Dimmer_dec(void)
{
	if(SCS_received.P2P_dimmer_zero != 1)						
	{
  	Time_delay.Dim_dec_count = 0;
		Time_delay.Dim_dec_enable = 0;
		//Mode_frame_P2P('1','2','4','0','1','F','F');				// DIM--	step==1
		dimmer_command(DIM_DOWN,0);
		SCS_received.P2P_dimmer_full = 0;							// if DIM-- frame is sent, the flag SCS_received.P2P_dimmer_full should be cleared
	}
}
	
//******************************************************************************
//				regulation for actuator or dimmer
// 		after (Lightreg is enabled)&&(load is on)&&(calibrate finished)
//		first judge the dimmer or actuator, then stsrt regulation
//******************************************************************************
void Light_regulation(void)
{	
	if( KO_conf.LightReg == 1 )		// setpoint and provision had been calculated
	{
		if (SCS_received.P2P_actuator_flag  == 1)	
				Actuator_regulation(); //reyno 0604	       						// sensor control a actuator
		else if(SCS_received.P2P_dimmer_flag == 1)		
				Dimmer_regulation(); //reyno 0604	        						// sensor control a dimmer	
	}
}

//******************************************************************************
//			update the dyalight level after calibration
//******************************************************************************
void daylight_set_init(void)
{
	DLL.setpoint_H = eep_setpoint[3];
	//DLL.setpoint_M = eep_setpoint[2]; //reyno 0602
	DLL.setpoint_L = eep_setpoint[1];
	
	if(DLL.setpoint_H > 0)    DLL.setpoint_H = factor_divcalc(2400, DLL.setpoint_H);     	// 600LUX
 // if(DLL.setpoint_M > 0)    DLL.setpoint_M = factor_divcalc(800, DLL.setpoint_M);     	// 200LUX
	if(DLL.setpoint_L > 0)    DLL.setpoint_L = factor_divcalc(1200,  DLL.setpoint_L);     	// 300LUX

       // if((DLL.setpoint_H>0)&&(DLL.setpoint_L>0))      DLL.setpoint_calibrate = 1;     		// calibrate finish
		//if(DLL.setpoint_M > 0)	 DLL.setpoint_calibrate = 1;     								// flag calibrate finish
}


//******************************************************************************
//				calibrate the real daylight level
// DLL.day_level is the daylight level detect by sensor in the housing
// DLL.current_level is the daylight level of the outside calculated by sensor
// DLL.calc_level used for D.F set via IR tools
// DLL.current_level是计算对应外界的实际光亮度
// DLL.day_level是处于外壳内部的sensor读取到的光亮度的值
//DLL.setpoint_M是外部光亮度值LUX与ADC的比率值再乘10
//DLL.day_level是从ADC读取到得值
//******************************************************************************

/*
void real_daylight_calc(void)
{
	//DLL.calc_level unit is lux
     DLL.calc_level = (DLL.setpoint_M * DLL.day_level)/10;									// calculate the daylight level (LUX)around the sensor
	
		 DLL.current_level = DLL.calc_level;
		
	   if((KO_conf.TypeLoop ==0)&&(KO_conf.DF !=0))														// default :KO_conf.DF=5(ceiling sensor),KO_conf.DF=1(wall sensor)
				//DLL.current_level = factor_mulcalc(DLL.current_level, DLL.DF);   	// calitrate real value and value measured by ambient light sensor
		 {
		
		 		if((Sensor_mode.power_on_flag == 1)&&(DLL.calc_OK_flag == 1))					// 0609
		 		{
		 				DLL.current_level = DLL.calc_level + (DLL.load_provision/KO_conf.DF)*(KO_conf.DF - 1);
		 		}
				else
				{
					DLL.current_level = DLL.current_level*KO_conf.DF;	//DLL.current_level*KO_conf.DF/10;
				}
		 }

}
*/

void PofL_calc(void)
{
	unsigned int V1,V2,V3;
	V1 = DLL.loadoff_level;
	V2 = DLL.PLv_5s - V1;
	V3 = DLL.PLv_5min - V1;
	if(V3 < V2 + V2/2)
		DLL.load_provision = V3;
	else
		DLL.load_provision = V2 + V2/2;

	DLL.load_provision = (DLL.load_provision*KO_conf.DF)/10;
	
	if(DLL.load_provision/5 > 0xFF)
		KO_conf.PofL = 0xFF;
	else
		KO_conf.PofL = DLL.load_provision/5;						// does it need to wtite into eep?
}

//******************************************************************************
//		function: get the value of  provision and setpoint OFF
//			Procedure to calculate the provision of light:
//		1)	the sensor stored the daylight value (V1) before light on
//		2)	After 5s, the sensor stored the max value (V2)
//		3)	After 5mn, the sensor stored an another max value (V3)
//		4)	The provision of light (P_l) is :
//			P_l = V3 if V3 < (V2-V1)*(1+50%)
//			Or P_L = (V2-V1)*(1+50%) if V3 >= (V2-V1)*(1+50%)
//******************************************************************************
void daylight_service(void)
{
	if(KO_conf.TypeLoop == 0)           						// in close loop	
	{
  		get_dl_level();

      if(Sensor_mode.power_on_flag == 0)                    	// count the loadoff value when load is powerd down 5s
      {
          DLL.loadoff_level = DLL.calc_level;
					DLL.PLv_5s = DLL.calc_level;
					DLL.lightness_load = T_5min5s;					// 5s
					DLL.PLv_5min = DLL.calc_level;
					DLL.calc_OK_flag = 0;
      }
     	else  if(DLL.calc_OK_flag != 1 && KO_conf.status[1] != 0)							// if the load is light on and load provision have not calibrated yet
      {																						// the provision of load is constant, no need to cablibrate every light on
				if(KO_conf.flag_PofL_Forced == 0)
				{
					//if(DLL.lightness_load > T_5mins && DLL.lightness_load < T_5mins + 2)					// load turn on less than 5 senconds
					if(DLL.lightness_load > T_5mins && DLL.lightness_load)
					{
						if( DLL.lightness_load < T_5mins + 2)
						{
							//reyno 0610
							//if(DLL.PLv_5s <= DLL.current_level)		DLL.PLv_5s = DLL.current_level;
							if(DLL.PLv_5s < (((unsigned long)DLL.calc_level*100)/KO_conf.status[1]))
							{
								DLL.PLv_5s = ((unsigned long)DLL.calc_level*100)/KO_conf.status[1];
								DLL.PLv_5min = ((unsigned long)DLL.calc_level*100)/KO_conf.status[1];
								PofL_calc();
							}
						}
					}
					else if(DLL.lightness_load > 1)						// load turn on less than 5 minutes
					{
							if(DLL.PLv_5min < (((unsigned long)DLL.calc_level*100)/KO_conf.status[1]))
							{
								DLL.PLv_5min = ((unsigned long)DLL.calc_level*100)/KO_conf.status[1];
								PofL_calc();
							}
					}
					else if(DLL.lightness_load == 1 || DLL.lightness_load == 0)					// load on 5min, start to calibrate the provision of load
					{
						/*
						unsigned int V1,V2,V3;
						V1 = DLL.loadoff_level;
						V2 = DLL.PLv_5s - V1;
						V3 = DLL.PLv_5min - V1;
						if(V3 < V2 + V2/2)
							DLL.load_provision = V3;
						else
							DLL.load_provision = V2 + V2/2;
					
						DLL.load_provision = (DLL.load_provision*KO_conf.DF)/10;
						DLL.setpoint_OFF = set_point + DLL.load_provision + DLL.load_provision/2;							//set_point + DLL.load_provision(1+k);
						
						if(DLL.load_provision/5 > 0xFF)
							KO_conf.PofL = 0xFF;
						else
							KO_conf.PofL = DLL.load_provision/5;						// does it need to wtite into eep?
						*/
						PofL_calc();
						DLL.setpoint_OFF = set_point + DLL.load_provision + DLL.load_provision/2;							//set_point + DLL.load_provision(1+k);
						
						DLL.calc_OK_flag = 1; //provision of light calculate OK
					}
				}
				else
				{
					DLL.calc_OK_flag = 1;
					DLL.setpoint_OFF = set_point + KO_conf.PofL * 5 + (KO_conf.PofL * 5) / 2;
				}
			}
	}
	else if(KO_conf.TypeLoop == 1)       									// in open loop
	{
		DLL.calc_OK_flag = 1;																// 兼容close loop
		//DLL.load_provision = KO_conf.PofL;								// set by user
		//DLL.loadoff_level  = KO_conf.DaylightLev;					// set by user
		DLL.loadoff_level = KO_conf.DayLightLevLux[0];
		DLL.loadoff_level = DLL.loadoff_level<<8;
		DLL.loadoff_level = KO_conf.DayLightLevLux[1];
		DLL.current_level  = DLL.open_actualevel;						// (lux sent by daylight) / D.F
		DLL.setpoint_OFF   = DLL.load_provision + set_point;		
	}
}



//******************************************************************************
//		get the value of  provision and setpoint OFF
//		flag__________>>>	DLL.setpoint_calibrate: calibration in the factory via SCS
//				|
//				|____>>>>	KO_conf.DF :calibration by user via IR
//******************************************************************************
/*
void get_dl_level(void)
{
	DLL.getlevel_finish = 0;
	DLL.read_daylightSample = read_adc ( daylight_channel );
	DLL.daylight_SampleValue = DLL.daylight_SampleValue + (unsigned int) DLL.read_daylightSample;
	DLL.daylight_SampleCount++;
	if(DLL.daylight_SampleCount >= 10)				
	{
		
		DLL.daylight_SampleCount = 0;
		DLL.day_level = DLL.daylight_SampleValue / 10;		// ADC value
		DLL.daylight_SampleValue = 0;
		DLL.getlevel_finish = 1;		
		if(DLL.setpoint_calibrate == 1)   							// flag of factory calibrate finished
		  	real_daylight_calc();
    else      							
			DLL.current_level = DLL.day_level;
		
		KO_conf.DayLightLevLux[0] = (DLL.current_level/5)&0x00FF;		//  0515
		KO_conf.DayLightLevLux[1] = (DLL.current_level/5)>>8;				//  0515
	}
}
*/

void get_dl_level(void)
{
	DLL.getlevel_finish = 0;
	DLL.read_daylightSample = read_adc10bit ( daylight_channel );
	DLL.daylight_SampleValue = DLL.daylight_SampleValue + (unsigned int) DLL.read_daylightSample;
	DLL.daylight_SampleCount++;
	if(DLL.daylight_SampleCount >= 10)				
	{
#ifdef DEMOBOARD
		not_bit(&PORTB,0);
#endif
		DLL.daylight_SampleCount = 0;
		DLL.day_level = DLL.daylight_SampleValue / 10;		// ADC value
		DLL.daylight_SampleValue = 0;
		DLL.getlevel_finish = 1;		
		real_daylight_calc();
		//	DLL.day_level is ADC value
		//  DLL.calc_level is the un-corrected value
		// DLL.current_level is the real value

		KO_conf.DayLightLevLux[0] = (DLL.current_level/5)&0x00FF;		//  low byte
		KO_conf.DayLightLevLux[1] = (DLL.current_level/5)>>8;				//  higt byte
	}
}

//		(un-corrected value * D.F - PfL*ratio) / D.F + PfL*ratio
//		un-corrected value + PfL(D.F - 1)

//		(un-corrected value * D.F - PfL) / D.F + PfL
//		un-corrected value - PfL / D.F + PfL
void real_daylight_calc(void)
{
	//DLL.calc_level unit is lux
#ifdef SMT
	DLL.read_lux = exp10(5 * (double)(DLL.day_level)/1024 * 100000 / RES_VALUE);
	DLL.calc_level = (unsigned int)DLL.read_lux ;
#else
	//DLL.calc_level = (CONST_DAYLIGHT * (unsigned long)DLL.day_level)/100;									// calculate the daylight level (LUX)around the sensor
	DLL.calc_level = (unsigned int)(g_slope * (double)DLL.day_level);
#endif
//     DLL.calc_level = (DLL.setpoint_M * DLL.day_level)/10;									// calculate the daylight level (LUX)around the sensor
	
//		DLL.current_level = DLL.calc_level;
	if((KO_conf.TypeLoop == 0)&&(KO_conf.DF !=0))														// default :KO_conf.DF=5(ceiling sensor),KO_conf.DF=1(wall sensor)
	{
		if((Sensor_mode.power_on_flag == 1)&&(DLL.calc_OK_flag == 1))					// 0609
		{
			if(KO_conf.DF > KO_conf.NF)
				DLL.current_level = DLL.calc_level*KO_conf.NF/10 + (((unsigned long)DLL.load_provision * KO_conf.status[1])/100) * ((KO_conf.DF - KO_conf.NF) / KO_conf.DF);
			else
				DLL.current_level = DLL.calc_level * KO_conf.NF / 10;
			//DLL.current_level = DLL.calc_level - ((((unsigned long)DLL.load_provision)*KO_conf.status[1])/100)*KO_conf.DF / 10; //Reyno 0722
			//DLL.current_level = DLL.calc_level;	//DLL.current_level*KO_conf.DF/10;    //Reyno 0722		
		}
		else
		{
			DLL.current_level = DLL.calc_level * KO_conf.NF / 10;	//DLL.current_level*KO_conf.DF/10;
		}
		//DLL.current_level = DLL.calc_level * KO_conf.DF / 10;	//DLL.current_level*KO_conf.DF/10;
	}
}
//******************************************************************************
//			timer for Pir and US cycle
//			200us each interupt
//******************************************************************************
void timer0_enable(void)
{
	ASSR = 0x00;
	TCCR0A = 0x00;
	TCCR0B = 0x03;
	TCNT0 = 0x8D;
	OCR0A = 0x00;
	OCR0B = 0x00;
	SetBit(TIMSK0,TOIE0);
}

//******************************************************************************
//			timer for time delay, 1ms
//******************************************************************************
void timer2_enable(void)
{
	/*
	TCCR0A = (1<<COM0A1)|(0<<COM0A0)|(1<<WGM01)|(0<<WGM00);	// match on clear
	TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(1<<CS00);			// CLOCK/64
	TIMSK0 = (1<<OCIE0A);				        										// enable COMPARE MATCH A interrupt
	TIFR0 = (1<<OCF0A);
	OCR0A = 21;																							//200us each interupt
	*/
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 7372.800 kHz
	// Mode: Normal top=FFh
	// OC0A output: Disconnected
	// OC0B output: Disconnected
	
	/*
	TCCR2A=0x00;
	TCCR2B=0x01;
	TCNT2=0x00;
	OCR2A=0x00;
	OCR2B=0x00;
	TIMSK2=0x01;
	*/
	
	/*
	ASSR=0x00;
TCCR2A=0xF0;
TCCR2B=0x01;
TCNT2=0x00;
OCR2A=0xB8;
OCR2B=0x5C;
	*/
	TCCR2A=0xC1;          //0x43
	TCCR2B = 0xC1;      //0x19
	//TCNT2=0x50;
	OCR2A=ee_back_light_duty;
	//OCR2B = 0x40;
}

/*
unsigned char motion_detect(unsigned char mode)      // add by alan on 20090409
{
		switch(mode)
      {
            case 1:
								if(PIR_detection_en ==1)	return 1;
								else return 0;
            case 2:
								if(US_detection_en ==1)	return 1;
								else return 0;
            case 3:
                if((PIR_detection_en ==1)&&(US_detection_en ==1))
									return 1;
                else
									return 0;
            case 4:
                if((PIR_detection_en ==1)||(US_detection_en ==1))
									return 1;
                else
									return 0;
            default:  return 0;
      }
}
*/

unsigned char motion_detect(unsigned char mode)
{
	unsigned char temp = 0;
	switch(mode)
	{
		case 1:				//PIR only
			US_OFF;
			temp = PIR_detect();
			//PIR_detect();
			asm("nop");
			if(temp)
				asm("nop");
			return temp;
			
		case 2:				//US only
			US_ON;
			get_us();
			return US_detection_en;

		case 3:				//PIR and US
			US_ON;
			temp = PIR_detect();
			//PIR_detect();
			get_us();
			if(US_detection_en && temp)
				return 1;

		case 4:				//PIR or US
			US_ON;
			get_us();
			PIR_detect();
			if(US_detection_en || PIR_detect())
				return 1;

		default:
			return 0;				
	}
}


/******************************************************************************
*	在这里，US的探测停留时间不能太长，否则影响IR tools的参数读取		// alan 0604
******************************************************************************/
unsigned char get_us(void)
{
	unsigned char i;
	if(Time_delay.IR.time_out)
	{
		US_detection_en = 0;
		for(i=0;i<10;i++)
		{
			us_detection();
			delay_us(100);
			if(US_detection_en == 1)
				return 1;
			//else
			//	return 0;
		}
	}
	return 0;
}

void load_update(unsigned char status)
{
  unsigned char buffer_short[9] = "00001200";
  unsigned char buffer_tx[17] = "D10001420D000000";
  unsigned char buffer[3];
  unsigned char buffer_add[3];

  buffer[2] = 0;

  CharToStr(KO_conf.DesAdd,buffer_add);

  switch (KO_conf.AddressType)
  {
    case 0x00://p to p
        CharToStr(KO_conf.DesAdd,buffer);
				buffer_short[0] = buffer[0];
				buffer_short[1] = buffer[1];
        CharToStr(status,buffer);
        buffer_short[6] = buffer[0];
        buffer_short[7] = buffer[1];
				send_frame_pp_broad(buffer_short,TRANS_DELAY); //0707

        CharToStr(status,buffer);
        buffer_tx[10] = buffer[0];
        buffer_tx[11] = buffer[1];
				send_frame_pp_ext(buffer_tx,TRANS_DELAY);
    break;

    case 0x01://area
      buffer_short[0] = 'B';
		  buffer_short[1] = '3';
      CharToStr(KO_conf.DesAdd,buffer);
			buffer_short[2] = buffer[0];
			buffer_short[3] = buffer[1];
      CharToStr(status,buffer);
      buffer_short[6] = buffer[0];
      buffer_short[7] = buffer[1];
			send_frame_pp_broad(buffer_short,TRANS_DELAY); //0707
    break;

    case 0x02://group
      buffer_short[0] = 'B';
		  buffer_short[1] = '5';
		  CharToStr(KO_conf.GR,buffer);
		  buffer_short[2] = buffer[0];
		  buffer_short[3] = buffer[1];
		  send_frame_pp_broad(buffer_short,TRANS_DELAY);
    break;

    case 0x03://general
      buffer_short[0] = 'B';
			buffer_short[1] = '1';
      CharToStr(status,buffer);
      buffer_short[6] = buffer[0];
      buffer_short[7] = buffer[1];
			send_frame_pp_broad(buffer_short,TRANS_DELAY); //0707
    break;

    default:break;
  }
}

void button_press_detect(void)
{
	if(!get_key())
	{
		if(Time_delay.LPB.enabled == 1)
		{
			if(Time_delay.LPB.count != 0)
			{
				if( Time_delay.LPB.count < 1000 )
				{
					key_result.short_pressed = 1;
					//buzzer_ms(100);					//20090211
				}
				else if( Time_delay.LPB.count > 3000 )
				{
					key_result.long_pressed = 1;
					//buzzer_ms(200);					//20090211
				}
				key_time_clear();
			}
		}

		Time_delay.LPB.count = 0;
		Time_delay.LPB.enabled = 0;
	}
	else if(get_key())
	{
		Time_delay.LPB.enabled = 1;
	}
}

void button_release_detect(void)
{
	if(!get_key())
	{
		Time_delay.LPB.count = 0;
		Time_delay.LPB.enabled = 0;
	}
}

unsigned char scs_pnl_advance_master(void)
{
	char buffer_tx[17] = "D20001428C220940";
	char buffer[3];

  buffer[2] = 0;

	static struct
	{
		unsigned char A;
		unsigned char PL;
		unsigned char flag;
		unsigned char group_create_flag;
	}ptop;

	static unsigned char conf_3s;
	//KO_conf.GR = 1;
	if( state.main_state == STATE_NORMAL )
	{
		if(key_result.short_pressed == 1)
		{
			key_result.short_pressed = 0;
			state.main_state = PNL_AD_CONFED_STEP1;
			led_blinking(1000,1000);
      timer_flex_initial(60000);
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP1 )
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
			return 0;
		}
		else if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			state.main_state = PNL_AD_CONFED_STEP2;
			timer_flex_initial(600000);
			led_blinking_stage2_initial(600000);
			led_blinking(250,250);
			send_frame_pp_broad("B0009900",TRANS_DELAY);

			if(KO_conf.GR != 0)
			{
				CharToStr(KO_conf.GR,buffer);
				buffer_tx[10] = buffer[0];
				buffer_tx[11] = buffer[1];
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			}
			else
			{
				state.main_state = PNL_AD_CONFED_STEP8;
				send_frame_pp_ext_broad("D20001428C000940",TRANS_DELAY);
			}
		}			
		else if(Time_delay.LPB.count > 10000)				// group initial
		{
      Time_delay.LPB.count = 0;
      ee_flags.manual_initialize = 1;
			send_group_pnl_frame(SET,KO_conf.GR,GROUP_RELEASE);
      factory_default();
			system_reset();
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP2 )      //group remove
	{
		if(key_result.short_pressed == 1)								//state 6 is here
		{
			key_result.short_pressed = 0;
			led_blinking_disable(0);
      timer_flex_initial(100);    //for close the procedure
			if(KO_conf.Reference == 0)
			{
				strncpy(buffer_tx,"B5001500",17);
				CharToStr(KO_conf.GR,buffer);
				buffer_tx[2] = buffer[0];
				buffer_tx[3] = buffer[1];
				send_frame_pp_broad(buffer_tx,TRANS_DELAY);
        timer_flex_initial(3000);
				conf_3s = 1;
			}
			state.main_state = PNL_AD_CONFED_STEP6;
		}

		if(Time_delay.LPB.count > 10000)
		{
      key_result.short_pressed = 0;
			key_result.long_pressed = 0;

			if(KO_conf.Reference != 0)
				send_group_pnl_frame(SET,KO_conf.Reference,REF_TRANS);
			
			if(ee_flags.PnG_confed)
			{
				KO_conf.Reference = ee_variable.Reference;
				ee_KO_conf.Reference = ee_variable.Reference;
			}
			else
			{
				KO_conf.Reference = 0;
				ee_KO_conf.Reference = 0;
			}
			
			send_group_pnl_frame(SET,KO_conf.GR,GROUP_END_PNL);
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			send_group_pnl_frame(SET,KO_conf.GR,GROUP_ERASE);
			led_blinking(60,200);
      delay_ms(5000);
      state.main_state = NORMAL;
		}
	}

	if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x21))
	{
		if(KO_conf.Reference == 0)
		{
			KO_conf.Reference = g_asc_reception_buffer[1];
			ee_KO_conf.Reference = g_asc_reception_buffer[1];
		}
	}	
		
	if( state.main_state == PNL_AD_CONFED_STEP6)
	{
		if(conf_3s == 1)
		{
			if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x21))
			{
				conf_3s = 0;
				KO_conf.Reference = g_asc_reception_buffer[1];
				ee_KO_conf.Reference = KO_conf.Reference;
			}
		}

		if(Time_delay.timer_flex.time_out == 1)
		{
			state.main_state = PNL_AD_CONFED_STEP7;
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP7)
	{
		if(KO_conf.Reference != 0)
				send_group_pnl_frame(SET,KO_conf.Reference,REF_TRANS);
		
		strncpy(buffer_tx,"D20001428C22094F",17);
		CharToStr(KO_conf.GR,buffer);
		buffer_tx[10] = buffer[0];
		buffer_tx[11] = buffer[1];
		send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);

		send_frame_pp_broad("B000990F",TRANS_DELAY);

		led_blinking_disable(0);
		state.main_state = STATE_NORMAL;
	}

	if( state.main_state == PNL_AD_CONFED_STEP8 )
	{
		/////////////////////////////////////////////////
		///      for solve GR==0         ////////////////
		if( key_result.short_pressed )
		{
			state.main_state = PNL_AD_CONFED_STEP90;
		}
		/////////////////////////////////////////////////
		if( (g_asc_short_buffer[0] == 0xB8) && (g_asc_short_buffer[2] == 0x12))
		{
			ptop.A = g_short_buffer[2];
			ptop.PL = g_short_buffer[3];
			ptop.flag = 1;
			state.main_state = PNL_AD_CONFED_STEP81;			//ptop step 3
		}
		if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x41))
		{
			send_frame_pp_ext_broad("D20001428C000945",TRANS_DELAY);
			state.main_state = PNL_AD_CONFED_STEP9;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
			return 0;
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP81 )
	{
		if( key_result.long_pressed == 1 )
		{
			key_result.long_pressed = 0;

			KO_conf.Reference = StrToChar(&ptop.A);
			ee_KO_conf.Reference = KO_conf.Reference;
			
			strncpy(buffer_tx,"D20001428C00094F",17);
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
		}
		else if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x21))
		{
			//StrToChar();
			KO_conf.DesAdd = g_asc_reception_buffer[1];
			ee_KO_conf.DesAdd = KO_conf.DesAdd;
			send_frame_pp_ext_broad("D20001428C000945",TRANS_DELAY);
		}

		if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x06))
		{
			//StrToChar();
			KO_conf.DesAdd = g_asc_reception_buffer[1];
			ee_KO_conf.DesAdd = KO_conf.DesAdd;

			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = KO_conf.GR;
			
			CharToStr(KO_conf.GR,buffer);
			buffer_tx[10] = buffer[0];
			buffer_tx[11] = buffer[1];
			strncpy(buffer_tx,"D20001428C000940",17);
			
			state.main_state = PNL_AD_CONFED_STEP2;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
			return 0;
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP9 )
	{
		if( (g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x06))
		{
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = KO_conf.GR;
			strncpy(buffer_tx,"D20001428C000940",17);
			CharToStr(KO_conf.GR,buffer);
			buffer_tx[10] = buffer[0];
			buffer_tx[11] = buffer[1];
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			state.main_state = PNL_AD_CONFED_STEP90;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
			return 0;
		}
	}

	if( state.main_state == PNL_AD_CONFED_STEP90 )
	{
		if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			PnL_ad_end();
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
			return 0;
		}
	}
  return 0;
}

void scs_pnl_none_confed_master(void)
{
	if(state.main_state == STATE_NORMAL)
	{
		if(key_result.short_pressed == 1)
		{
			key_result.short_pressed = 0;
			state.main_state = PNL_NONE_CONFED_STEP1;
			led_blinking(1000,1000);
			timer_flex_initial(60000);
		}
	}

	if(state.main_state == PNL_NONE_CONFED_STEP1)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
			LLED_OFF;
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
		}
		
		if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			state.main_state = PNL_NONE_CONFED_STEP2;
			frame_send_disable_automatic_control();
			frame_send_start_pnl_none_group_confed();
			led_blinking(250,250);
			//timer_flex_initial(600000);
			led_blinking_stage2_initial(600000);
		}
    else if(Time_delay.LPB.count > 10000)	
    {
      factory_default();
      ee_flags.manual_initialize = 1;
			system_reset();
    }
	}

	if(state.main_state == PNL_NONE_CONFED_STEP2)
	{
		if(Time_delay.pnl_stage2.time_out == 1)
		{
			state.main_state = PNL_NONE_CONFED_STEP4;
		}
		
    if(g_asc_short_buffer[0] == 0xB8 && g_asc_short_buffer[2] == 0x12)
    {
			//KO_conf.DesAdd = g_asc_short_buffer[1];
			//ee_KO_conf.DesAdd = g_asc_short_buffer[1];
			temp_variable.DesAdd = g_asc_short_buffer[1];
			flags.pp_link = 1;
			//product_information.conf_type = ADVANCED;
			//ee_product_information.conf_type = ADVANCED;
    }

		if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			if(flags.pp_link)
			{
				flags.pp_link = 0;
				load_default_advance_parameter();
				KO_conf.DesAdd = temp_variable.DesAdd;
				ee_KO_conf.DesAdd = temp_variable.DesAdd;
				product_information.conf_type = ADVANCED;
				ee_product_information.conf_type = ADVANCED;
				KO_conf.AddressType = PP;
				ee_KO_conf.AddressType = PP;
			}
			state.main_state = PNL_NONE_CONFED_STEP4;
		}
		
    if(g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x21)
    {
      KO_conf.Reference = g_asc_reception_buffer[1];
			ee_KO_conf.Reference = g_asc_reception_buffer[1];
      frame_send_group_request();
      timer_flex_initial(3000);
      state.main_state = PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN;
    }

		////////////////////////////////////////////////////////////////////////
		//////////////  for none confed group sensor   /////////////////////////
		if(g_asc_reception_buffer[6] == 0x09 && (g_asc_reception_buffer[7] == 0x06 || g_asc_reception_buffer[7] == 0xF6))
		{
			load_default_advance_parameter();
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = g_asc_reception_buffer[5];
			KO_conf.AddressType = GROUP;
			ee_KO_conf.AddressType = GROUP;
			product_information.conf_type = ADVANCED;
      ee_product_information.conf_type = ADVANCED;
			send_group_pnl_frame(SET,KO_conf.GR,START_PNL);
			state.main_state = PNL_AD_CONFED_STEP2;
		}
		
		if(Time_delay.LPB.count > 3000)				// group initial
		{
			key_result.short_pressed = 0;
			key_result.long_pressed = 0;
			load_default_advance_parameter();
			KO_conf.DesAdd = temp_variable.DesAdd;
			ee_KO_conf.DesAdd = temp_variable.DesAdd;
			KO_conf.AddressType = PP;
			ee_KO_conf.AddressType = PP;
			product_information.conf_type = ADVANCED;
			ee_product_information.conf_type = ADVANCED;
			frame_send_end_pnl();
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			led_blinking_normal();
			state.main_state = STATE_NORMAL;
		}
	}

  if(state.main_state == PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN)
  {
		if(Time_delay.timer_flex2.time_out == 1)
		{
			state.main_state = PNL_NONE_CONFED_STEP4;
		}
		
    if(Time_delay.timer_flex.time_out == 1)
		{
      frame_send_enable_automatic_control();    //added by reyno
      frame_send_end_pnl(); //added by reyno
		  led_blinking_normal();
		  state.main_state = STATE_NORMAL;
		}

    if(flags.group_assigned)
    {
			load_default_advance_parameter();
      KO_conf.GR = g_asc_reception_buffer[5];
      ee_KO_conf.GR = g_asc_reception_buffer[5];
			KO_conf.AddressType = GROUP;
			ee_KO_conf.AddressType = GROUP;
      product_information.conf_type = ADVANCED;
      ee_product_information.conf_type = ADVANCED;
      frame_send_start_pnl_group_confed();
      key_result.short_pressed = 0;
      key_result.long_pressed = 0;
      state.main_state = PNL_AD_CONFED_STEP2;
      //state.main_state = PNL_NONE_CONFED_STEP4;
    }
  }

  if(state.main_state == PNL_NONE_CONFED_STEP4)
  {
		PnL_NONE_end();
  }

}

void scs_pnl_advance_slave(void)
{
	unsigned char buffer_tx[17] = "D20001348C000941";
	unsigned char buffer[3];
	
	if(state.main_state == NORMAL)
	{
		if(state.pnl_slave == START_PNL_GROUP_SENSOR)
		{
			if(key_result.short_pressed)
  	  {
  	    key_result.short_pressed = 0;
				if(flags.wait_GS_remove == 1)
				{
					flags.wait_GS_remove = 0;
					if(KO_conf.GS1 == temp_variable.GR) //remove
					{
						send_group_pnl_frame(ANSWER,KO_conf.GS1,GROUP_ERASE);
						KO_conf.GS1 = 0;
						ee_KO_conf.GS1 = 0;
					}
					else
					{
						send_group_pnl_frame(ANSWER,KO_conf.GS2,GROUP_ERASE);
						KO_conf.GS2 = 0;
						ee_KO_conf.GS2 = 0;
					}
					led_blinking_disable(0);
					state.main_state = NORMAL;
				}
				else
				{
					led_blinking(1000,1000);
					timer_flex_initial(60000);
					state.main_state = SENSOR_GROUP_STEP4;
				}
			}
  	}
		else if(state.pnl_slave == START_PNL_NONE_CONFED_GROUP_SENSOR)
		{
			if( key_result.short_pressed)
    	{
      	key_result.short_pressed = 0;
      	led_blinking(1000,1000);
				timer_flex_initial(60000);
				state.main_state = NONE_TO_AD_STEP1;
    	}
		}
	}
	
	if(state.main_state == SENSOR_GROUP_STEP4)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
		  led_blinking_normal();
		  state.main_state = STATE_NORMAL;
		}
		
		if(key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			if(KO_conf.GS1 == 0 || KO_conf.GS1 == temp_variable.GR)
			{
				KO_conf.GS1 = temp_variable.GR;
				ee_KO_conf.GS1 = temp_variable.GR;
				CharToStr(KO_conf.GS1,buffer);
				buffer_tx[10] = buffer[0];
				buffer_tx[11] = buffer[1];
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				led_blinking(250,250);
				state.main_state = ADD_THEN_REMOVE;
			}
			else if(KO_conf.GS2 == 0 || KO_conf.GS2 == temp_variable.GR)
			{
				KO_conf.GS2 = temp_variable.GR;
				ee_KO_conf.GS2 = temp_variable.GR;
				CharToStr(KO_conf.GS2,buffer);
				buffer_tx[10] = buffer[0];
				buffer_tx[11] = buffer[1];
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				led_blinking(250,250);
				state.main_state = ADD_THEN_REMOVE;
			}
			else
			{
				led_blinking(120,0);
				delay_ms(5000);
				led_blinking_disable(0);
				state.main_state = NORMAL;
			}
		}
	}
	
	if(state.main_state == ADD_THEN_REMOVE)
	{
		if(key_result.short_pressed)
    {
			key_result.short_pressed = 0;
      if(KO_conf.GS1 == temp_variable.GR) //remove
			{
				send_group_pnl_frame(ANSWER,KO_conf.GS1,GROUP_ERASE);
				KO_conf.GS1 = 0;
				ee_KO_conf.GS1 = 0;
			}
			else
			{
				send_group_pnl_frame(ANSWER,KO_conf.GS2,GROUP_ERASE);
				KO_conf.GS2 = 0;
				ee_KO_conf.GS2 = 0;
			}
			led_blinking_disable(0);
			state.main_state = NORMAL;
		}
	}
	
	if(state.main_state == NONE_TO_AD_STEP1)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			if(KO_conf.GS1 == 0 || KO_conf.GS1 == temp_variable.GR)
			{
				led_blinking(250,250);
				state.main_state = NONE_TO_AD_STEP2;
			}
			else if(KO_conf.GS2 == 0 || KO_conf.GS2 == temp_variable.GR)
			{
				led_blinking(250,250);
				state.main_state = NONE_TO_AD_STEP2;
			}
			else
			{
				led_blinking(120,0);
				delay_ms(5000);
				state.main_state = NORMAL;
				state.pnl_slave = NORMAL;
				flags.scs_pnl_group_sensor_starded = NORMAL;
				led_blinking_normal();
			}
		}
	}
	
	if(state.main_state == NONE_TO_AD_STEP2)
	{
		send_group_pnl_frame(ANSWER,0x00,GROUP_CONFIRM);
		send_group_pnl_frame(SET,0x00,GROUP_REQUEST);
		timer_flex2_initial(3000);
		state.main_state = NONE_TO_AD_STEP3;
	}
	
	if(state.main_state == NONE_TO_AD_STEP3)
	{
		if(Time_delay.timer_flex2.time_out == 1)
		{
			send_group_pnl_frame(SET,0x00,GROUP_END_PNL);
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			led_blinking_normal();
			state.pnl_slave = NORMAL;
	  	state.main_state = STATE_NORMAL;
		}
		else
		{
			if(g_asc_reception_buffer[3] == 0x42 && g_asc_reception_buffer[4] == 0x8C && g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x40)
			{
				if(KO_conf.GS1 == 0 || KO_conf.GS1 == g_asc_reception_buffer[5])
				{
					send_group_pnl_frame(ANSWER,KO_conf.GS1,GROUP_CONFIRM);
				}
				else if(KO_conf.GS2 == 0 || KO_conf.GS2 == g_asc_reception_buffer[5])
				{
					send_group_pnl_frame(ANSWER,KO_conf.GS2,GROUP_CONFIRM);
				}
				state.main_state = NONE_TO_AD_STEP4;
			}
		}
	}
	
	if(state.main_state == NONE_TO_AD_STEP4)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			send_group_pnl_frame(SET,0x00,GROUP_END_PNL);
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			led_blinking_normal();
			state.pnl_slave = NORMAL;
	  	state.main_state = STATE_NORMAL;
		}
	}
}

void scs_advance_from_none_confed(void)
{
	//for PnL confed sensor slave
	if( key_result.short_pressed)
  {
      key_result.short_pressed = 0;
      led_blinking(1000,1000);
			timer_flex_initial(60000);
			//state.pnl_slave_none_confed = AFTER_STEP1;
			state.main_state = NONE_TO_AD_STEP1;
    }
	
		if(state.pnl_slave == START_PNL_NONE_CONFED_GROUP_SENSOR)
		{
			if(KO_conf.GS1 == 0)
			{
			
			}
			else if(KO_conf.GS2 == 0)
			{
		
			}
			else
			{
				led_blinking(120,0);
				delay_ms(5000);
				state.main_state = NORMAL;
				state.pnl_slave = NORMAL;
				flags.scs_pnl_group_sensor_starded = NORMAL;
				led_blinking_normal();
			}
		}
}

unsigned char scs_pnl_none_confed_slave(void)
{
	if(state.main_state == NORMAL && state.pnl_slave == NORMAL)
	{
		if( key_result.short_pressed)
    {
     	key_result.short_pressed = 0;
     	led_blinking(1000,1000);
			timer_flex_initial(60000);
			state.main_state = AD_TO_NONE_STEP2;
    }
	}
	
	if(state.main_state == AD_TO_NONE_STEP2)
		{
			if(Time_delay.timer_flex.time_out == 1)
			{
		  	led_blinking_normal();
		  	state.main_state = NORMAL;
			}
		
			if( key_result.short_pressed)
    	{
     		key_result.short_pressed = 0;
				state.main_state = CONSTANT_LIGHT;
     		led_blinking(120,0);
				delay_ms(5000);
				state.main_state = NORMAL;
				led_blinking_normal();
    	}
		}
	
	if(state.pnl_slave == START_PNL_NONE_CONFED_GROUP_SENSOR)
	{
		if(state.main_state == NORMAL)
		{
			if( key_result.short_pressed)
    	{
      	key_result.short_pressed = 0;
      	led_blinking(1000,1000);
				timer_flex_initial(60000);
				state.main_state = SENSOR_NONE_CONFED_SUB_STEP3;
    	}
		}
	}
		
	if(state.main_state == SENSOR_NONE_CONFED_SUB_STEP3)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
		  led_blinking_normal();
		  state.main_state = STATE_NORMAL;
			state.pnl_slave = NORMAL;
		}
		
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			led_blinking(100,0);
			delay_ms(5000);
			state.main_state = NORMAL;
			state.pnl_slave = NORMAL;
			flags.scs_pnl_group_sensor_starded = NORMAL;
			led_blinking_normal();
			return 1;
		}
	}
	else if(state.main_state == SENSOR_NONE_CONFED_SUB_STEP31)
	{
		if(g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x40)
		{
			load_default_advance_parameter();
			KO_conf.GS1 = g_asc_reception_buffer[5];
			ee_KO_conf.GS1 = g_asc_reception_buffer[5];
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = g_asc_reception_buffer[5];
			send_group_pnl_frame(ANSWER,KO_conf.GS1,GROUP_CONFIRM);
			state.main_state = WAIT_END_PNL;
		}
	}
	else if(state.main_state == WAIT_END_PNL)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			product_information.conf_type = ADVANCED;
			ee_product_information.conf_type = ADVANCED;
			send_group_pnl_frame(SET,KO_conf.GS1,GROUP_END_PNL);
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			state.main_state = NORMAL;
			state.pnl_slave = NORMAL;
			flags.scs_pnl_group_sensor_starded = NORMAL;
			led_blinking_normal();
		}
	}
	return 0;
}

void scs_pnl_group_sensor_detector(void)
{

}

void key_time_clear(void)
{
	Time_delay.LPB.count = 0;
	Time_delay.LPB.enabled = 0;
}
/*
void led_blinking_double(unsigned long int on_ms, unsigned long int off_ms)
{
  Time_delay.led_double_on.count = 0;
	Time_delay.led_double_off.count = 0;
	Time_delay.led_double_on.stack_top = (unsigned long int)(on_ms);
	Time_delay.led_double_off.stack_top = (unsigned long int)(off_ms);
	Time_delay.led_double_on.enabled = 1;
	Time_delay.led_double_off.enabled = 1;
}
*/
void led_blinking_double_disable(void)
{
	LLED_OFF;
	DLED_OFF;
  Time_delay.led_double_on.enabled = 1;
	Time_delay.led_double_off.enabled = 1;
}

void led_blinking(unsigned long int on_ms, unsigned long int off_ms)
{
	Time_delay.led_on.count = 0;
	Time_delay.led_off.count = 0;
	Time_delay.led_on.stack_top = (unsigned long int)(on_ms);
	Time_delay.led_off.stack_top = (unsigned long int)(off_ms);
	Time_delay.led_on.enabled = 1;
	Time_delay.led_off.enabled = 0;
}

void led_blinking_ms(unsigned long int on_ms,unsigned long int off_ms, unsigned long int period)
{
	led_blinking(on_ms,off_ms);
	Time_delay.blinking_count.count = 0;
	Time_delay.blinking_count.stack_top = period;
	Time_delay.blinking_count.time_out = 0;
	Time_delay.blinking_count.enabled = 1;
}

void Dled_light_on_ms(unsigned long int on_ms)
{
	Time_delay.Dled.count = 0;
	Time_delay.Dled.stack_top = on_ms;
	Time_delay.Dled.time_out = 0;
	Time_delay.Dled.enabled = 1;
	LLED_ON;
}



void led_blinking_disable(unsigned char state)
{
	Time_delay.led_on.enabled = 0;
	Time_delay.led_off.enabled = 0;
	if(state == 1)
		LLED_ON;
	else if(state == 0)
		LLED_OFF;
}

void timer_flex_initial(unsigned long int ms)
{
	Time_delay.timer_flex.stack_top = ms;
	Time_delay.timer_flex.count = 0;
	Time_delay.timer_flex.time_out = 0;
	Time_delay.timer_flex.started = 1;
	Time_delay.timer_flex.enabled = 1;
}

void timer_flex2_initial(unsigned long int ms)
{
	Time_delay.timer_flex2.stack_top = ms;
	Time_delay.timer_flex2.count = 0;
	Time_delay.timer_flex2.time_out = 0;
	Time_delay.timer_flex2.started = 1;
	Time_delay.timer_flex2.enabled = 1;
}

void timer_dimmer_initial(unsigned long int ms)
{
  Time_delay.dimmer.stack_top = ms;
	Time_delay.dimmer.count = 0;
	Time_delay.dimmer.time_out = 0;
	Time_delay.dimmer.started = 1;
	Time_delay.dimmer.enabled = 1;
}

void all_reception_buffer_clear(void)
{
	unsigned char i;
	for(i=0;i<DEEP;i++)
	{
		if(scs_frame[i].finished != 0)
		{
			scs_frame[i].finished = 1;
		}

    scs_frame[i].byte[20] = 0;
	}
	reception_buffer_clear(0);
}

void manual_reception_buffer_clear(void)
{
  unsigned char i;
	for(i=0;i<DEEP;i++)
	{
		scs_frame[i].finished = 0;
    scs_frame[i].byte[20] = 0;
	}
}

void start_conf(void)
{
	unsigned char  buffer[3];
  volatile unsigned char ko_confed;
	unsigned char buffer_gateway[6];
	unsigned char i;
	
	#ifndef NO_CONFIGURATOR_HOUSING
  if(flags.id_confed)
  {
		while(power_up_configuration() != 0)
		{
			if(flags.diagnostic != 1)
			{
				led_blinking(200,1000);
				KO[0] = '0';
        KO[1] = '2';
        KO[2] = '0';
        KO[3] = '3';
				diagnostic_frame();
				flags.diagnostic = 1;
			}
		}
		
		if( ee_product_information.conf_type == 0 )
    	ee_configurators = Configurators;
  }
	#else

	#endif
  //configuration for gateway
	put_s("$09\r");
	for(i=0;i<200;i++)
  {
    if(is_gateway_busy() == 0x13)
    {
			break;
		}
		else
		{
      delay_ms(10);
		}
  }
	
	//put_s("$13\r");
	//delay_ms(2000);
	
  put_s("$270500\r");
  delay_ms(50);
  put_s("$021000\r");
  delay_ms(50);
	
	buffer_gateway[0] = '$';
	buffer_gateway[1] = '1';
	buffer_gateway[2] = '6';
	buffer_gateway[3] = '2';
	buffer_gateway[4] = '2';
	buffer_gateway[5] = 0x0D;
  put_s(buffer_gateway);
	
	/*
	put_s("$1600\r");
  delay_ms(50);
  */
  if(ee_flags.manual_initialize)
  {
    led_blinking_normal();
    while(get_key()) delay_ms(50);
    delay_ms(500);
    ee_flags.manual_initialize = 0;
  }
  //flags.manual_initialize = 0;

	if(ee_product_information.conf_type == BASIC_PHYSICAL || ee_product_information.conf_type == BASIC_VIRTUAL)
	{
    Configurators = ee_configurators;
		buffer[0] = Configurators.A;
		buffer[1] = Configurators.PL;
		KO_conf.DesAdd = StrToChar(buffer);
		ee_KO_conf.DesAdd = StrToChar(buffer);

    switch(Configurators.M)
    {
      case '0':
        #ifdef NONE_CONFED_203
          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '8';
          ee_product_information.cen_system = NOT_CEN;
        #endif
      break;

      case '1':
        #ifdef NONE_CONFED_203
          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '6';
          ee_product_information.cen_system = NOT_CEN;
        #endif
      break;

      case '2':
        #ifdef NONE_CONFED_203
          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = '8';
          ee_KO[3] = '0';
					ee_KO_conf.AddressType = PP;
          ee_product_information.cen_system = CEN;
          ee_product_information.local_A = Configurators.A;
          ee_product_information.local_PL = Configurators.PL;
        #endif
      break;

      case '3':
        #ifdef NONE_CONFED_203
          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '8';
          ee_product_information.cen_system = NOT_CEN;
        #endif
      break;

      case '4':
        #ifdef NONE_CONFED_203
          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '6';
          ee_product_information.cen_system = NOT_CEN;
          ee_KO_conf.Reference = ee_KO_conf.DesAdd;
        #endif
      break;

      default:break;
    }
	}
	else if(ee_product_information.conf_type == ADVANCED)
	{
		Configurators.A = '0';
		Configurators.PL = '0';
		Configurators.M = '0';
		Configurators.S = '0';
		Configurators.T = '0';	

    buffer[0] = ee_KO[2];
    buffer[1] = ee_KO[3];
    ko_confed = StrToChar(buffer);
#ifdef NONE_CONFED_203
   switch(ko_confed)
   {
    case 0xA8:
      ee_product_information.cen_system = NOT_CEN;
    break;

    case 0xA6:
      ee_product_information.cen_system = NOT_CEN;
      //ee_KO_conf.Reference = ee_KO_conf.DesAdd;
    break;

    case 0x77:
      ee_product_information.cen_system = NOT_CEN;
    break;

    case 0x80:
      ee_product_information.cen_system = CEN;
    break;

    case 0xA4:
      ee_product_information.cen_system = CEN;
    break;

    case 0xA5:
      ee_product_information.cen_system = CEN;
    break;

    default:break;
   }
#endif

#ifdef NONE_CONFED_204
   switch(ko_confed)
   {
    case 0xA6:
      ee_product_information.cen_system = NOT_CEN;
    break;

    case 0xA4:
      ee_product_information.cen_system = CEN;
    break;

    default:break;
   }
#endif

#ifdef NONE_CONFED_203
   switch(ko_confed)
   {
    case 0x77:
      ee_product_information.cen_system = NOT_CEN;
    break;

    case 0xA5:
      ee_product_information.cen_system = CEN;
    break;

    case 0x70:
      ee_product_information.cen_system = NOT_CEN;
    break;

    default:break;
   }
#endif
	}
	else
	{
    for(unsigned char i = 0;i<16;i++)
    {
      if(ee_scenario[i].confed)
      {
        flags.confed = 1;
        break;
      }
    }

    //if(flags.confed == 0)
		  //led_blinking(120,120);
		
		Configurators.A = '0';
		Configurators.PL = '0';
		Configurators.M = '0';
		Configurators.S = '0';
		Configurators.T = '0';	
	}

  if( ee_product_information.ID_factory_assigned )
    DLED_OFF;
  else
    DLED_ON;

  Time_delay.led_blink.count = 0;
	Time_delay.led_blink.stack_top = 999;
	Time_delay.led_blink.enabled = 1;
}

void factory_default(void)
{
	unsigned char i;
	unsigned char j;
	//load_default_parameter();
	//remember_parameter();				// with load default together
	
	//ID_setting("00050000");
	KO[0] = flash_KO[0];
  KO[1] = flash_KO[1];
  KO[2] = flash_KO[2];
  KO[3] = flash_KO[3];
	KO_parameter_initial_temp();
	ee_KO_conf = KO_conf;
	
  ee_KO[0] = flash_KO[0];
  ee_KO[1] = flash_KO[1];
  ee_KO[2] = flash_KO[2];
  ee_KO[3] = flash_KO[3];
  ee_product_information.cen_system = 0;
	ee_product_information.conf_type = 3;
	//ee_product_information.ID_confed = 0;

	ee_scenario_index = 0;
  g_ns_index = 0;
	for(i=0;i<16;i++)
	{
		ee_scenario[i].ns_number = 0x01;
		ee_scenario[i].reg_type = 0x01;
		for(j=0;j<3;j++)
		{
			ee_scenario[i].id[j] = 0;
		}
		ee_scenario[i].key_number = 0;
		ee_scenario[i].confed = 0;
	}

	ee_product_information.local_A = '0';
	ee_product_information.local_PL = '0';
	
	ee_configurators.A = '0';
	ee_configurators.PL = '0';
	ee_configurators.M = '0';
	ee_configurators.S = '0';
	ee_configurators.T = '0';
	
	ee_flags.PnG_confed = 0;
}

void configurator_to_KO(void)
{
	switch(ee_configurators.M)
	{
		case '0':
			ee_KO_conf.AddressType = 0;
			ee_KO_conf.FuncMod = 1;
			ee_KO_conf.LightReg = 0;
			ee_KO_conf.Retrigger = 0;
			ee_KO_conf.en_load = 1;
			ee_KO_conf.en_GS_main_group = 0;
			ee_KO_conf.TypeLoop = 0;
			ee_KO_conf.Retrigger = 0;
			//ee_KO_conf.PofL = 60;
#ifdef HARDWARE_PIR
			ee_KO_conf.InitOccu = 1;
			ee_KO_conf.MaintainOccu = 1;
#endif
			
#ifdef HARDWARE_US
			ee_KO_conf.InitOccu = 2;
			ee_KO_conf.MaintainOccu = 2;
#endif
			
#ifdef HAEDWARE_PIR_US
			ee_KO_conf.InitOccu = 3;
			ee_KO_conf.MaintainOccu = 4;
#endif
		break;
		
	case '1':
		
		break;
		
	case '2':
		break;
		
	case '3':
		ee_KO_conf.AddressType = 0;
		ee_KO_conf.FuncMod = 1;
		ee_KO_conf.LightReg = 1;
		ee_KO_conf.Retrigger = 0;
		ee_KO_conf.en_load = 1;
		ee_KO_conf.en_GS_main_group = 0;
		ee_KO_conf.TypeLoop = 0;
		ee_KO_conf.Retrigger = 0;
		//ee_KO_conf.PofL = 60;
#ifdef HARDWARE_PIR
		ee_KO_conf.InitOccu = 1;
		ee_KO_conf.MaintainOccu = 1;
#endif
		
#ifdef HARDWARE_US
		ee_KO_conf.InitOccu = 2;
		ee_KO_conf.MaintainOccu = 2;
#endif
		
#ifdef HAEDWARE_PIR_US
		ee_KO_conf.InitOccu = 3;
		ee_KO_conf.MaintainOccu = 4;
#endif
		break;
		
	case '4':
		break;
		
	default:break;
	}
				switch(ee_configurators.S)
				{
				case '0':
					ee_KO_conf.PirSens = 0;
					ee_KO_conf.USSens = 0;
					break;
					
				case '1':
					ee_KO_conf.PirSens = 1;
						ee_KO_conf.USSens = 1;
					break;
					
				case '2':
					ee_KO_conf.PirSens = 2;
						ee_KO_conf.USSens = 2;
					break;
					
				case '3':
					ee_KO_conf.PirSens = 3;
						ee_KO_conf.USSens = 3;
					break;
					
				default:break;
				}
	
	switch( Configurators.T )
	{
		case '0':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 10;
			ee_KO_conf.Seconds = 0;
		break;

		case '1':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 0;
			ee_KO_conf.Seconds = 30;
		break;

		case '2':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 1;
			ee_KO_conf.Seconds = 0;
		break;

		case '3':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 2;
			ee_KO_conf.Seconds = 0;
		break;

		case '4':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 5;
			ee_KO_conf.Seconds = 0;
		break;

		case '5':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 10;
			ee_KO_conf.Seconds = 0;
		break;

		case '6':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 15;
			ee_KO_conf.Seconds = 0;
		break;

		case '7':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 20;
			ee_KO_conf.Seconds = 0;
		break;

		case '8':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 30;
			ee_KO_conf.Seconds = 0;
		break;

		case '9':
			ee_KO_conf.Hours = 0;
			ee_KO_conf.Minutes = 40;
			ee_KO_conf.Seconds = 0;
		break;

		default: break;
	}
}

void service_main(void)
{
  switch (state.main_state)
  {
    case STATE_PRE_PROGRAMMING:
      if(get_key())
			{
        key_result.short_pressed = 0;
        key_result.long_pressed = 0;
        state.main_state = STATE_PROGRAMMING;
				diagnostic_frame();	
				flags.AA_received = 0;
				flags.parameter_setting_wrong = 0;
				flags.parameter_write_right = 0;
			}
    break;

    case STATE_PROGRAMMING:
			timer_flex_initial(660000);				//11 minutes time out
			led_blinking(1000,1000);
			state.main_state = STATE_PROGRAMMING_DURING;
    break;

    case STATE_PROGRAMMING_DURING:
			if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_normal();
        send_frame_pp_ext_broad("D20001348C0000FA",TRANS_DELAY);
				state.main_state = STATE_NORMAL;
			}
    break;

    case STATE_PRE_TEST:
      if(get_key())
			{
        state.main_state = STATE_PROGRAMMING;
				diagnostic_frame();	
			}
      else if(Time_delay.timer_flex.time_out == 1)
      {
        state.main_state = STATE_NORMAL;
      }
    break;

    case STATE_TEST:
			timer_flex_initial(660000);				//11 minutes time out
			led_blinking(1000,1000);
			state.main_state = STATE_TEST_DURING;
    break;

    case STATE_TEST_DURING:
      if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_normal();
				state.main_state = STATE_NORMAL;
			}
    break;

		case FACTORY_CALIBRATION:
			case FACTORY_CALIBRATION_STEP1:
				factory_calibration();
		break;
		
    default:break;
  }

		if(product_information.conf_type == ADVANCED)
		{
			if( state.main_state == STATE_NORMAL )
			{
				if(flags.app_disable == 0)
				{
					function_service();			// add by alan 20090424
				}
			}
		}
		else if(product_information.conf_type == BASIC_PHYSICAL || product_information.conf_type == BASIC_VIRTUAL)
		{
			if( state.main_state == STATE_NORMAL )
			{
				function_service();			// add by alan 20090424
			}
		}

		if(product_information.conf_type == NONE_CONFED || product_information.conf_type == ADVANCED)
		{
			ir_pnl();								//0218
	
    	if(product_information.conf_type == ADVANCED)
			{
				if(flags.scs_pnl_group_sensor_starded)
				{
					scs_pnl_advance_slave();
				}
				else
				{
					if(KO_conf.AddressType == GROUP)
						scs_pnl_advance_master();
					else if(KO_conf.AddressType == PP)
						scs_pnl_none_confed_master();		
				}				
			}

			if(product_information.conf_type == NONE_CONFED)
			{
				if(flags.scs_pnl_group_sensor_starded)
					scs_pnl_none_confed_slave();
				else
					scs_pnl_none_confed_master();							
			}
		}
	
		if(state.id_setting == 1)
		{
			if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_disable(0);
				state.id_setting = 0;
				send_frame_pp_ext_broad("D000010E00000000",TRANS_DELAY);
			}
		}
}

void led_status_recover(void)
{
  if(product_information.conf_type == 3)
  {
    led_blinking(120,120);
  }
  else
    led_blinking_disable(0);
}

void frame_send_disable_automatic_control(void)
{
	send_frame_pp_broad("B0009900",TRANS_DELAY);
}

void frame_send_enable_automatic_control(void)
{
  send_frame_pp_broad("B000990F",TRANS_DELAY);
}

void frame_send_start_pnl_none_group_confed(void)
{
	send_frame_pp_ext_broad("D20001428C000940",TRANS_DELAY);
}

void frame_send_start_pnl_group_confed(void)
{
  unsigned char buffer_tx[17] = "D20001428C000940";
  unsigned char buffer[3];

  CharToStr(KO_conf.GR,buffer);
  buffer_tx[10] = buffer[0];
  buffer_tx[11] = buffer[1];
  send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
}

void frame_send_end_pnl(void)
{
	send_frame_pp_ext_broad("D20001428C00094F",TRANS_DELAY);
}

void frame_send_group_request(void)
{
  send_frame_pp_ext_broad("D20001428C000945",TRANS_DELAY);
}

void led_blinking_normal(void)
{
	flags.confed = 0;
  for(unsigned char i = 0;i<16;i++)
  {
 		if(ee_scenario[i].confed)
		{
			flags.confed = 1;
			break;
		}
	}
		
	if(state.main_state == STATE_NORMAL)
	{
  	if(product_information.conf_type == NONE_CONFED && flags.confed == 0)
  	{
      led_blinking(120,120);
  	}
  	else
    	led_blinking_disable(0);
	}
}

void load_default_advance_parameter(void)
{
	KO[0] = '0';
	KO[1] = '0';
	KO[2] = 'A';
	KO[3] = '8';
				
	ee_KO[0] = '0';
  ee_KO[1] = '0';
  ee_KO[2] = 'A';
  ee_KO[3] = '8';
  //to avoid power up KO confdiguration
  ee_KO_last[0] = '0';
  ee_KO_last[1] = '0';
  ee_KO_last[2] = 'A';
  ee_KO_last[3] = '8';
  //ee_KO_conf = KO_conf;
  KO_parameter_initial();
  KO_conf = ee_KO_conf;
}

void led_blinking_stage2_initial(unsigned long int ms)
{
	Time_delay.pnl_stage2.stack_top = ms;
	Time_delay.pnl_stage2.count = 0;
	Time_delay.pnl_stage2.time_out = 0;
	Time_delay.pnl_stage2.started = 1;
	Time_delay.pnl_stage2.enabled = 1;
}

void PnL_ad_end(void)
{
	unsigned char buffer_tx[17];
	unsigned char buffer[3];
	
	if(KO_conf.Reference != 0)
				send_group_pnl_frame(SET,KO_conf.Reference,REF_TRANS);
			
	strncpy(buffer_tx,"D20001428C00094F",17);
	CharToStr(KO_conf.GR,buffer);
	buffer_tx[10] = buffer[0];
	buffer_tx[11] = buffer[1];
	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	send_frame_pp_broad("B000990F",TRANS_DELAY);
	led_blinking_disable(0);
	state.main_state = STATE_NORMAL;
}

void PnL_NONE_end(void)
{
	frame_send_end_pnl();
  frame_send_enable_automatic_control();
  led_blinking_normal();
	state.pnl_slave = NORMAL;
	state.main_state = STATE_NORMAL;
}

void regulation_timer_initial(void)
{
	Time_delay.regulation.stack_top = 200;
	Time_delay.regulation.count = 0;
	Time_delay.regulation.time_out = 0;
	Time_delay.regulation.started = 1;
	Time_delay.regulation.enabled = 1;
}

void relay_timer_initial(unsigned long int ms)
{
	Time_delay.relay.stack_top = ms;
	Time_delay.relay.count = 0;
	Time_delay.relay.time_out = 0;
	Time_delay.relay.started = 1;
	Time_delay.relay.enabled = 1;
}

void test_ID_assigned(void)
{
	if(ee_product_information.ID_factory_assigned == 0)
	{		
		ee_product_information.ID_factory_assigned = 1;	
		ee_product_information.ID_confed = 1;
		product_information.ID_confed = 1;
		flags.id_confed = 1;
	}
}