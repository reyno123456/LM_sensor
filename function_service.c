// Function_KO168.c

#include <ioavr.h>
#include <inavr.h>
#include "IR.h"
#include "PIR.h"
#include "US.h"
#include "usart.h"
#include "board.h"
#include "moudle_SCS.h"
#include "application.h"
#include "configuration.h"
#include "decode_scs.h"
#include "decode_scs_next.h"
#include "global_variable.h"
#include "function_service.h"

//******************************************************************************
// 	send frame presence
//******************************************************************************
//Mode_frame_GR(KO_conf.GR,nopre);
//GS_presence_send();
//frame_presence('1') pp mode

void frame_presence(unsigned char arg)
{
		// B8 APL 1D 00
		unsigned char TX_buffer[8];
    unsigned char buffer[3];
		
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
		TX_buffer[7] = arg;
		send_frame_pp_broad(TX_buffer, TRANS_DELAY);

}

//******************************************************************************
// 	send frame no presence + OFF
//******************************************************************************
void frame_pp_on_off( unsigned char command )
{
	if(KO_conf.en_load == 1)
  {
		// APL  LOC 12 00 "ON"
		// APL  LOC 12 01 "OFF"
		unsigned char buffer[2];
		unsigned char TX_buffer[8];
	
		if(command == '0')
		{
			Sensor_mode.power_on_flag =  1;
			//KO_conf.status[1] = Status_ON; //reyno 0616
			//DLL.lightness_load = T_5min5s;					// 5s
			//DLL.calc_OK_flag = 0; //reyno 0616
		}
		else if(command == '1')
		{
			Sensor_mode.power_on_flag = 0; //reyno 0616
			//KO_conf.status[1] = Status_OFF;
			Time_delay.detect_waitting = OFF_delay_2s;	// 0527,after send "OFF",the new detect will be enable 2s later
		}
		
		if(KO_conf.AddressType == 0)	
		{
			CharToStr(KO_conf.DesAdd,buffer);
			TX_buffer[0] = buffer[0];
			TX_buffer[1] = buffer[1];
		}
		else if(KO_conf.AddressType == 2)							// 0526
		{
			CharToStr(KO_conf.Reference, buffer);						// KO_conf.DesAdd
			TX_buffer[0] = buffer[0];
			TX_buffer[1] = buffer[1];
			//CharToStr(KO_conf.GR, buffer);						// KO_conf.DesAdd
			//TX_buffer[2] = buffer[0];
			//TX_buffer[3] = buffer[1];
		}
		TX_buffer[2] = '0';
		TX_buffer[3] = '0';		
		TX_buffer[4] = '1';
		TX_buffer[5] = '2';
		TX_buffer[6] = '0';
		TX_buffer[7] = command;
		send_frame_pp_broad(TX_buffer, TRANS_DELAY);				// 0707
	}	
}

//******************************************************************************
// 	start time delay for load
//******************************************************************************
void Start_Time_Delay(void)
{
	Time_delay.Walk_Through_Timeout = 0;	
	Time_delay.timer_delay_set.count = Delay_Time_set;	// start time count from Delay_Time_set--
	Time_delay.timer_delay_set.time_out = 0;
	Time_delay.timer_delay_set.enabled = 1;
	Time_delay.timer_delay_set.started = 1;
}

//******************************************************************************
// 	stop time delay for load
//******************************************************************************
void Stop_allTimer(void)
{
	Time_delay.Re_Trigger_senconds = 0;
	Time_delay.Walk_Through_Timeout = 0;
	Time_delay.timer_takeline.enabled = 0;
	Time_delay.timer_delay_set.enabled = 0;
	if(KO_conf.LightReg == 1)			// alan 0729
	{
			DLL.start_regulation = 0;
			ClrBit(KO_conf.status[0],Status_Regulationing);
	}
}

//******************************************************************************
// 	update the time dalay base on Automatic or walkthrough
//******************************************************************************
void Call_detect_delay(void)
{
  if(KO_conf.FuncMod == Auto_Walk_thru)		// 在Auto_Walk_thru模式时
	{
		if(Delay_Time_set > Walkthru_delay)		
			Time_delay.Walk_Through_Timeout = Walkthru_delay;
		else									
			Time_delay.Walk_Through_Timeout = Delay_Time_set;
	  	
		Walk_Through_flag = 1;
		First_detection_enable = 1;
	}
	else
	{
		Start_Time_Delay();	
		Walk_Through_flag = 0;
	}
}

//*****************************************************************************************
// 	to check the time delay between the detection and the first detection > 20s
//*****************************************************************************************
void WT_20s_detect(void)               					// to judge if the time between the detection and the first detection is longer than 20s
{
    if(Walk_Through_flag == 1)									// in walk_through mode
		{
				if( ((Time_delay.Walk_Through_Timeout < 160)&&(Delay_Time_set >= Walkthru_delay))
					 ||((Time_delay.Walk_Through_Timeout < Delay_Time_set-20)&&(Delay_Time_set < Walkthru_delay)))	
				{																				//(Walkthru_delay – T_20s))
					Walk_Through_flag = 0;
					Time_delay.Walk_Through_Timeout = 0;	// detection is occur after 20s since first detection, use the set time delay
					Start_Time_Delay();										// when detection is occur after 20s, use the set time delay instead of Walk_Through_Timeout
				}
				else																		// update time delay
				{
					if(Delay_Time_set > Walkthru_delay)		
			  		Time_delay.Walk_Through_Timeout = Walkthru_delay;
					else							
			 	 		Time_delay.Walk_Through_Timeout = Delay_Time_set;
				}
		}
		else
		{
				Start_Time_Delay();											// update the delay time after received the GS presence
		}
}

//******************************************************************************
// 	send the frame presence for the GS
//******************************************************************************
void GS_presence_send(void)
{
        if(KO_conf.en_GS_main_group ==1)
        {
	      //Mode_frame_GR(KO_conf.GR,pre);													// send GR frame presence;	B5 GG 1D 00
	      if(KO_conf.GS1 != 0)	Mode_frame_GR(KO_conf.GS1, Gs1);		// send frame "presence detection" to the GS1;
	      if(KO_conf.GS2 != 0)	Mode_frame_GR(KO_conf.GS2, Gs2);		// send frame "presence detection" to the GS2;
        }
}

//******************************************************************************
// 					send the frame ON
//			in Partial_ON mode, 	APL LOC 12 00
//			in other mode,				B5  GR  12 00
//******************************************************************************
void frame_ON_send(void)
{
     if(KO_conf.en_load == 1)				//0618
     {
			 flags.dimmer_ON_sended = 0;
       	if( KO_conf.FuncMod == Partial_ON || KO_conf.AddressType ==0)   // Parital ON or P2P
				{
						//if( KO_conf.Reference != 0 )	Mode_frame_P2P('1','2','0','0','0','0','0');		
						frame_pp_on_off('0');             		// send frame ON	    0526    	
				}
				else																	// GR on
				{
						if(KO_conf.GR !=0)		Mode_frame_GR(KO_conf.GR,ON);		
				}
				//KO_conf.status[1] = Status_ON;				//0515
				if(KO_conf.LightReg == 1)			// alan 0729
				{
						DLL.start_regulation = 1;
						SetBit(KO_conf.status[0],Status_Regulationing);
						regulation_timer_initial();
				}
     }
}

//******************************************************************************
// 				send the frame OFF
//******************************************************************************
void frame_OFF_send(void)
{
     if(KO_conf.en_load == 1)			//0618
     {
			 if( KO_conf.LightReg == 1 && SCS_received.P2P_dimmer_flag == 1 && DLL.start_regulation == 1)
			 {
				 dimmer_command(OFF,0);
			 }
			 else
			 {
          if(KO_conf.AddressType == 2 && KO_conf.GR != 0)		//GR
					{
			 				Mode_frame_GR(KO_conf.GR,nopre);		// send Group "no presence detection"	B5 GG 1D 01
          		Mode_frame_GR(KO_conf.GR,OFF);			// send Group "OFF" frame	B5 GG 12 01
					}
					else if(KO_conf.AddressType == 0)				//P2P
					{
						frame_presence('1'); //0709
						frame_pp_on_off('1');             		// send frame OFF    0618
					}
			 }
			
			 DLL.start_regulation = 0;							// alan 0729 stop regulation when time delay over
			 ClrBit(KO_conf.status[0],Status_Regulationing);
     }
}

//*******************************************************************************
// 			used for the Alert when the time dalay equal to 1min or 30s ir 10s
//*******************************************************************************
void Delay_Alert(void)
{
	
  	if((Time_delay.Walk_Through_Timeout==60)||(Time_delay.Walk_Through_Timeout==30)
	   ||(Time_delay.Walk_Through_Timeout==10)||(Time_delay.timer_delay_set.count==60)
		 ||(Time_delay.timer_delay_set.count==30)||(Time_delay.timer_delay_set.count==10))
	  {		
			switch(KO_conf.Alert)
			{
				case Disabled:
					// do nothing
					break;
				case Visual:
	
					break;
				case Acustic:
					buzzer_ms(500);
		
					break;
				case Visual_Acustic:
					buzzer_ms(500);
					break;	
			
				default: break;			
			}
	  }	

}
	
//*******************************************************************************
// 	used for takeline when the sensor want to send the frame  presence + ON
//*******************************************************************************
void ON_takeline(void)
{		
	if(Time_delay.timer_takeline.time_out == 1)					// when time is out, send the frames
	{													
		Mode_frame_GR(KO_conf.GR,pre);										// send Group "presence detection"	B5 GG 1D 00
		frame_ON_send();

		Time_delay.timer_takeline.time_out = 0;
		Time_delay.timer_takeline.started = 0;
		Sensor_mode.ON_takeline_waitsend = 0;							// to indicate this frame had been sent
		Sensor_mode.flag_leader_group = 1;
		Sensor_mode.mode_state = Maintain_state;

		Call_detect_delay();
		Sensor_mode.maintain_pre = 1;											//0518
		Sensor_mode.presence_20sinterval = presence_20s;		//0518
	}
}

//******************************************************************************
// 	used for takeline when the sensor want to send the frame  no presence + OFF
//******************************************************************************
void OFF_takeline(void)
{					
	if(Time_delay.timer_takeline.time_out == 1)
	{		
		frame_OFF_send();
		Sensor_mode.no_prence_off_send = 1;								// to  indicate this frame had been sent
		Sensor_mode.OFF_takeline_waitsend = 0;
		Sensor_mode.flag_leader_group = 1;
		Time_delay.timer_takeline.started = 0;
	}
}

//******************************************************************************
// 	Check the frame received on SCS	when manual is enabled
//******************************************************************************
void function_check_status(void)
{	

//******************************************************************************
// 	if received update ON/OFF/LEVEL
//******************************************************************************
  if((SCS_received.update_state_ON == 1)||(SCS_received.update_state_OFF == 1)||(SCS_received.update_state_LEVEL == 1))
	{
      if(SCS_received.update_state_ON == 1)				// 0519
			{
				SCS_received.update_state_ON = 0;
				SCS_received.update_on_wait = 0;
			}
	  		if(SCS_received.update_state_OFF == 1)  	// 0519
			{
				SCS_received.update_state_OFF = 0;
				SCS_received.update_off_wait = 0;
			}
		  	
			SCS_received.update_state_LEVEL = 0;
			
			if(Sensor_mode.mode_state == Initial_state)		//0520
			{
				Stop_allTimer();
			}
			if(Sensor_mode.mode_state == Re_Trigger_State)
			{
				if ( (Time_delay.Re_Trigger_senconds <=4 && KO_conf.FuncMod != ManualON_Auto_OFF)
				   ||(Time_delay.Re_Trigger_senconds <= Re_Trigger_30s - 1 && KO_conf.FuncMod == ManualON_Auto_OFF))
				{
			  		Sensor_mode.mode_state = Maintain_state;
						Call_detect_delay();
				}
			}
	}
	
	if(KO_conf.FuncMod == ManualON_Auto_OFF)//((KO_conf.FuncMod == ManualON_Manual_OFF)||(KO_conf.FuncMod == ManualON_Auto_OFF))// 在manual mode，sensor不接收任何来自SCS总线上的帧
	{
		if(SCS_received.GS_presence == 1)
		{
				SCS_received.GS_presence = 0;
				Time_delay.GS_200ms.stack_top = 200;
				Time_delay.GS_200ms.count = 0;
				Time_delay.GS_200ms.time_out = 0;
				Time_delay.GS_200ms.started = 1;
				Time_delay.GS_200ms.enabled = 1;
		}
		
		if(Time_delay.GS_200ms.time_out)
		{
			Time_delay.GS_200ms.time_out = 0;
		  Mode_frame_GR(KO_conf.GR,pre);	
			Start_Time_Delay();	
		}
		//Sensor_mode.mode_state = Maintain_state; //0520
		if(SCS_received.presence == 1)		//in manual, upadate timedelay more 20s,配合其他的auto mode的sensor
		{
				SCS_received.presence = 0;
				Start_Time_Delay();
				//Time_delay.timer_delay_set.count +=  presence_20s;
		}
		if(SCS_received.GR_ON == 1)
		{
				SCS_received.GR_ON = 0;
				Sensor_mode.presen_timeout = 0;			// 0603
				// STOP TIME DALAY 0601
				Time_delay.timer_delay_set.enabled = 0;				// stop time set delay
				Time_delay.timer_delay_set.time_out = 0;
				if((KO_conf.FuncMod == ManualON_Auto_OFF)&&(Sensor_mode.flag_leader_group ==1))
				{
					Sensor_mode.mode_state = Maintain_state;			// 0601
					Walk_Through_flag = 0;			//reyno 0608
				}
		}
	}
	else
	{	
		 	Check_SCS_received();
	}
}


//******************************************************************************
// 	Check the frame received on SCS	without manual mode
//******************************************************************************
void Check_SCS_received(void)					
{
		
//******************************************************************************
// 	if received GS "ON"
//******************************************************************************	
	if(SCS_received.GS_presence == 1)				// the frame sent by extern sensor of GS
	{
		SCS_received.GS_presence = 0;
		Time_delay.GS_200ms.stack_top = 200;
		Time_delay.GS_200ms.count = 0;
		Time_delay.GS_200ms.time_out = 0;
		Time_delay.GS_200ms.started = 1;
		Time_delay.GS_200ms.enabled = 1;
	}
	
	if(Time_delay.GS_200ms.time_out)
	{
		Time_delay.GS_200ms.time_out = 0;
		if(Sensor_mode.presence_20sinterval == 0)		//0716
		{
			Mode_frame_GR(KO_conf.GR,pre);			// send GR frame presence;	// B5 GG 1D 00	for this frame, presence maybe doesn't needed
			Sensor_mode.presence_20sinterval = presence_20s;			// add 0605
			Time_delay.GS_wait_22s = 22;			// TO Ingore the 20s presence sent by GS when end detection
		}
		switch(Sensor_mode.mode_state)
		{
			case Initial_state:		
				if(DLL.current_level < set_point)			
				{
					//reyno 0622
					if(KO_conf.LightReg == 1)
					{
						DLL.start_regulation = 1;
						SetBit(KO_conf.status[0],Status_Regulationing);
					}
					Sensor_mode.flag_leader_group = 1;
					Sensor_mode.mode_state = Maintain_state;					
					frame_ON_send();	
					Call_detect_delay();
				}
				else
				{
					Start_Time_Delay();					//if still in the initial state
				}	
				break;
			
			case Maintain_state:
      case Standby_state:
			        WT_20s_detect();			
				break;
			
			case Re_Trigger_State:	
				Sensor_mode.mode_state = Maintain_state;
				Time_delay.Re_Trigger_senconds = 0;            // clear the retrigger time delay when leave the retrogger state		
                        frame_ON_send();	
				Start_Time_Delay();														// in the walk_through won't go into the rerigger	
				break;
				
			default:  break;				
		}
	}
//******************************************************************************
// 	if received GR "ON"
//******************************************************************************
	if(SCS_received.GR_ON == 1)
	{
		//reyno 0622
		if(KO_conf.LightReg == 1)
		{	
			DLL.start_regulation = 1;
			SetBit(KO_conf.status[0],Status_Regulationing);
			regulation_timer_initial();
		}		
	       // SCS_received.presence_2_ON = 1;		// debug
		SCS_received.GR_ON = 0;
	        //Time_delay.frame_200ms.time_out = 0;  // 避免在误执行单独接收presence的程序
		Time_delay.timer_takeline.enabled = 0;
		Time_delay.timer_takeline.started = 0;
		Time_delay.frame_200ms.enabled = 0;
		Time_delay.frame_200ms.started = 0;
		//Sensor_mode.flag_leader_group = 0;					// debug 20090423
		
		switch(Sensor_mode.mode_state)
		{
			/*case Initial_state:	
				if(SCS_received.presence_2_ON == 1)		
				{
					SCS_received.presence_2_ON = 0;
					Sensor_mode.mode_state = Standby_state;
					Sensor_mode.flag_leader_group = 0;	
					Call_detect_delay();
				}
			    break;
       */
			
			case Maintain_state:
           if(SCS_received.presence_2_ON != 1)
							Walk_Through_flag = 0;    								//  received signal ON frame
      //break;
			
      case Initial_state:
				if(SCS_received.presence_2_ON == 1)							//received presence and ON frame
				{
					SCS_received.presence_2_ON = 0;	
         	Sensor_mode.flag_leader_group = 0;
					Sensor_mode.mode_state = Standby_state;
					Sensor_mode.presence_send = 1; //Reyno 0623
					Sensor_mode.presence_20sinterval = presence_20s;				// 0717
					Call_detect_delay();
				}
				//else if((KO_conf.FuncMod == ManualON_Auto_OFF)&&(Sensor_mode.flag_leader_group ==1))
				//{
				//	Sensor_mode.mode_state = Maintain_state;			// 注释，放到前面去处理 0601
					//Call_detect_delay();
				//}
				else
				{
					// STOP TIME DALAY 0601
						Time_delay.timer_delay_set.enabled = 0;				// stop time set delay
						Time_delay.timer_delay_set.time_out = 0;
				}
			    break;
			
			case Re_Trigger_State:	

				Sensor_mode.mode_state = Maintain_state;				//Standby_state;
				Time_delay.Re_Trigger_senconds = 0;		
				Start_Time_Delay();
			    break;
			
			case Standby_state:
			
				if(SCS_received.presence_2_ON == 1)							//received presence and ON frame
				{
					SCS_received.presence_2_ON = 0;
					Time_delay.Re_Trigger_senconds = 0;
					Time_delay.Walk_Through_Timeout = 0;

					if(Walk_Through_flag == 1)	
						Time_delay.Walk_Through_Timeout = Walkthru_delay;	
					else
						Start_Time_Delay();
				}
				// start light regulation if received signal ON frame
			    break;
				
			default:  break;				
		}	
	}
	
	
//******************************************************************************
// 	if received GR "presence" frame
//******************************************************************************
	if(SCS_received.presence == 1)					
	{
		SCS_received.presence = 0;
		if(Time_delay.frame_200ms.started == 0) // delay 200ms start
		{
			Time_delay.frame_200ms.count = 0;
			Time_delay.frame_200ms.time_out = 0;
			Time_delay.frame_200ms.enabled = 1;
			Time_delay.frame_200ms.started = 1;
			SCS_received.presence_2_ON = 1;		 // 在200ms内，标志位置一，收到ON帧时可以据此判断接收到的是ON,还是presence+ON
		}
	}
	if((Time_delay.frame_200ms.time_out == 1)&&(SCS_received.GR_ON == 0))	// 接收到presence200ms后，还没有接收到ON，就认为是单独的一个presence帧
	{
		// 做在200ms结束后第一次执行到此，并且恰在此时接收到SCS_received.GR_ON==1；就会出现多执行一次presence的bug（很少发生）
		Time_delay.frame_200ms.time_out = 0;
		switch(Sensor_mode.mode_state)
		{
			case Initial_state:	
				if(DLL.current_level < set_point)
				{
          if(KO_conf.LightReg == 1)
					{
						DLL.start_regulation = 1;  //reyno 0622
						SetBit(KO_conf.status[0],Status_Regulationing);
					}
						Call_detect_delay();				
						if(Sensor_mode.flag_leader_group == 1)
						{
								Sensor_mode.mode_state = Maintain_state;		
								if(Walk_Through_flag != 1)
								{
									Sensor_mode.maintain_pre = 1;											//0518
									Sensor_mode.presence_20sinterval = presence_20s;		//0518
								}
								Mode_frame_GR(KO_conf.GR,pre);											// send GR frame presence;	// B5 GG 1D 00
								frame_ON_send();
						}
						else
						{
								Sensor_mode.mode_state = Initial_state;
								Sensor_mode.ON_takeline_waitsend = 1;								//	ON_takeline();	//WITH Special TAKING LINE to send presence+ON							
						}						
				}
				else
				{
						Start_Time_Delay();																			// start time dalay if still in initial state
				}
				break;
			
			case Maintain_state:
	        case Standby_state:
				WT_20s_detect();
        Sensor_mode.presence_20sinterval = presence_20s;
				Sensor_mode.maintain_pre = 1;
				Sensor_mode.presence_send = 1; //Reyno 0623
				//Mode_frame_GR(KO_conf.GR,pre);			// I don't think the sensor should resend the presence frame after it received a presence frame
				// Mode_frame_GR('5','1','D','0','B');		// B5 GG 1D 00  for debug
				break;
				
			case Re_Trigger_State:	
			
				Sensor_mode.mode_state = Maintain_state;
				Time_delay.Re_Trigger_senconds = 0; 		
				Start_Time_Delay();
				Mode_frame_GR(KO_conf.GR,pre);				// send GR frame presence;
				frame_ON_send();
				break;
			
			default: break;				
		}		
		
	}
	
//******************************************************************************
// 	if received GR "NO presence" or "OFF"
//******************************************************************************
	if(SCS_received.no_presence == 1)
	{
		SCS_received.no_presence = 0;
		SCS_received.nopresence_2_OFF = 1;				//  received no presence frame
	}
	
	if(KO_conf.AddressType == PP)
	{
		switch(Sensor_mode.mode_state)
		{
			case Initial_state:	
			break;
				
			case Maintain_state:
				if(SCS_received.nopresence_2_OFF == 1)
				{
				  SCS_received.nopresence_2_OFF = 0;			
					Sensor_mode.flag_leader_group = 0;	
					Time_delay.timer_takeline.enabled = 0;		// after received the frame no presence and OFF, stop the taking line
					Time_delay.timer_takeline.time_out = 0;			
					Sensor_mode.mode_state = Standby_state;

					if(KO_conf.FuncMod != ManualON_Auto_OFF)	
					  Time_delay.Re_Trigger_senconds = Re_Trigger_5s;
					else						
					  Time_delay.Re_Trigger_senconds = Re_Trigger_30s;
				}
			break;
			
			case Re_Trigger_State:
			break;
			
			case Standby_state:
			break;
			
			default:break;
		}
	}
	
	if(SCS_received.GR_OFF == 1)
	{
		SCS_received.GR_OFF = 0;

		switch(Sensor_mode.mode_state)
		{
			case Initial_state:	
				if(SCS_received.nopresence_2_OFF == 1)			//received no presence and OFF frame
				{
					SCS_received.nopresence_2_OFF = 0;
					Sensor_mode.flag_leader_group = 0;	
					Time_delay.timer_takeline.enabled = 0;		// after received the frame no presence and OFF, stop the taking line
					Time_delay.timer_takeline.time_out = 0;
					Stop_allTimer();		//0520
				}
				else		
				{
                                        // signal frame OFF
				}
			     break;
				
			 case Maintain_state:
				
				if(SCS_received.nopresence_2_OFF == 1)			//received no presence and OFF frame
				{
					SCS_received.nopresence_2_OFF = 0;			
					Sensor_mode.flag_leader_group = 0;	
					Time_delay.timer_takeline.enabled = 0;		// after received the frame no presence and OFF, stop the taking line
					Time_delay.timer_takeline.time_out = 0;			
					Sensor_mode.mode_state = Standby_state;
					if(KO_conf.FuncMod != ManualON_Auto_OFF)	
					  Time_delay.Re_Trigger_senconds = Re_Trigger_5s;
					else						
					  Time_delay.Re_Trigger_senconds = Re_Trigger_30s;	
				}
				else				// signal frame OFF
				{
					if(Delay_Time_set > Walkthru_delay)		
						Time_delay.Walk_Through_Timeout = Walkthru_delay;
					else									
						Time_delay.Walk_Through_Timeout = Delay_Time_set;
					
					Walk_Through_flag = 1;
					Time_delay.detect_waitting = 20000;		// 0601 detection is disabled 20s
					if(KO_conf.FuncMod == Auto_Walk_thru)
						First_detection_enable = 0;
				}
			      break;
				
			  case Re_Trigger_State:	
					Walk_Through_flag = 1;
					if(Delay_Time_set > Walkthru_delay)		
						Time_delay.Walk_Through_Timeout = Walkthru_delay;
					else									
						Time_delay.Walk_Through_Timeout = Delay_Time_set;	
					
					Sensor_mode.mode_state = Maintain_state;
					Time_delay.Re_Trigger_senconds = 0;
					Time_delay.detect_waitting = 20000;		// 0601 detection is disabled 20s
			      break;
				
			  case Standby_state:
				if(SCS_received.nopresence_2_OFF == 1)			// received no presence and OFF
				{
					SCS_received.nopresence_2_OFF = 0;
					Sensor_mode.flag_leader_group = 0;				// this is no need, because Sensor_mode.flag_leader_group = 0

					Time_delay.timer_takeline.enabled = 0;		// after received the frame no presence and OFF, stop the taking line
					Time_delay.timer_takeline.time_out = 0;
					Time_delay.timer_delay_set.enabled = 0;		// stop time set delay
					Time_delay.timer_delay_set.time_out = 0;
					Time_delay.Walk_Through_Timeout = 0;			// stop walk_through delay	
						
					if(Walk_Through_flag == 1)
					{
						Sensor_mode.mode_state = Initial_state;	
						Time_delay.timer_delay_set.time_out = 0;
						Sensor_mode.no_prence_off_send = 0;			// allow to send no presence and OFF frame
						Time_delay.Re_Trigger_senconds = 0;
					}
					else
					{
						Time_delay.Re_Trigger_senconds = Re_Trigger_5s;	
						Sensor_mode.mode_state = Standby_state;		
					}
				}
				else										// single OFF frame
				{
					Walk_Through_flag = 1;
					if(Delay_Time_set > Walkthru_delay)		
						Time_delay.Walk_Through_Timeout = Walkthru_delay;
					else									
						Time_delay.Walk_Through_Timeout = Delay_Time_set;
					
					Time_delay.detect_waitting = 20000;		// 0601 detection is disabled 20s
				}
			      break;
			
			  default:  break;				
		}
	}
	
//******************************************************************************
// 	if received GR "lux" request
//******************************************************************************	

	if(SCS_received.modality_lux_request == 1)
	{
		SCS_received.modality_lux_request = 0;
		frame_M2_answer('0');
		
	}
	if(SCS_received.setpoint_high ==1)
	{
	 	SCS_received.setpoint_high = 0;
                DLL_setpoint(3);//(High);
	}
    if(SCS_received.setpoint_medium ==1)
	{
	 	SCS_received.setpoint_medium = 0;
                DLL_setpoint(2);//(Medium);
	}
	if(SCS_received.setpoint_low ==1)
	{
		 SCS_received.setpoint_low = 0;
		 DLL_setpoint(1);//(Low);
	}
}


//******************************************************************************
// check the detection of Pir or US
// Pir warmup time should be at least 30s
// 6ms every cycle for Pir, 200us every cycle for US
//******************************************************************************
void occupancy_detect(void)
{
    //if((++Time_delay.timer0_compa_cnt >= 2)&&(Time_delay.pir_warmup_ok == 1))			// every 6ms
		if(Time_delay.pir_warmup_ok == 1)
		{
			Time_delay.timer0_compa_cnt = 0;
			motion_resutl = 0;
			if(product_information.cen_system)
			{
				Sensor_mode.detect_scheme = KO_conf.DF;
			}
			motion_resutl = motion_detect(Sensor_mode.detect_scheme);   							// set in the files function mode.c
			motion_total = motion_total + motion_resutl;
			if(motion_total)
				asm("nop");
			if((motion_total)&&(SCS_received.calib_wait != 1)&&(Time_delay.pir_warmup_ok == 1)&&(Time_delay.detect_waitting ==0))			// in the calibration waitting mode, motion detection is disabled
			{
				//DLED_ON;
				motion_total = 0;
				Dled_light_on_ms(1000);
				//Time_delay.timer_1s.count = 0;							//start count 1 second	
				US_detection_en = 0;
				PIR_detection_en = 0;
				SCS_received.motion_detect = 1;
				flags.motion_detected = 1;
				SetBit(KO_conf.status[0],Status_Detection);				//0515
			}
		}
}


//******************************************************************************
// function LM GR  machine states	begin	
//******************************************************************************
void _Initial_state(void)
{			
	
	if(SCS_received.motion_detect == 1 && Sensor_mode.presence_20sinterval == 0)				// 0520	
	{
      Mode_frame_GR(KO_conf.GR,pre);			                 // send frame GR presence  B5 GG 1D 00
			Sensor_mode.presence_send = 1;
			
			if((KO_conf.KO_number == 119)||(KO_conf.KO_number == 168)&&(DLL.loadoff_level < set_point)&&(KO_conf.FuncMod != ManualON_Auto_OFF))
			{
				//reyno 0622
				if(KO_conf.LightReg == 1)
				{
					DLL.start_regulation = 1;
					SetBit(KO_conf.status[0],Status_Regulationing);
				}
				
				Sensor_mode.mode_state = Maintain_state;
				Sensor_mode.motion_initial_detect = 1;			//保证第一次动initial进入到maintain时程序能正常的设定延迟时间		
				//SCS_received.motion_detect = 1;						//debug 0520
				Sensor_mode.flag_leader_group = 1;				
				frame_ON_send();
     	 	Call_detect_delay();
			}
			else
			{				
				Start_Time_Delay();
			}	
			GS_presence_send();	
		
			//	if(KO_conf.FuncMod == Auto_Walk_thru)			//0521
			//		Sensor_mode.motion_initial_detect = 2;	
			//	else
			Sensor_mode.presence_20sinterval = presence_20s;
		
	}

	SCS_received.motion_detect = 0;
		
	if(Time_delay.timer_delay_set.time_out == 1)//&&(Sensor_mode.no_prence_off_send == 0))	//make sure send one no presence and OFF frame in initial state
	{
		Time_delay.timer_delay_set.started = 0;
		Time_delay.timer_delay_set.time_out = 0;
		
		//if(KO_conf.AddressType == PP)         //reyno 0709
			//Mode_frame_GR(KO_conf.GR,nopre);
		
		if(Sensor_mode.flag_leader_group == 1)
		{						
				//	Mode_frame_GR(KO_conf.GR,pre);
				frame_OFF_send();
				Sensor_mode.no_prence_off_send = 1;					
		}
		else		//  WITH Special TAKING LINE : after send no presence+OFF帧后不再进入到这一步程序
		{
			Sensor_mode.OFF_takeline_waitsend = 1;						//	OFF_takeline();									
		}		
	}
	
	if ((Sensor_mode.ON_takeline_waitsend == 1)||(Sensor_mode.OFF_takeline_waitsend == 1))
	{
		if(Time_delay.timer_takeline.started == 0)						// start the timer_takeline
		{
			Time_delay.timer_takeline.count = 0;
		//	Time_delay.timer_takeline.time_out = 0;
			Time_delay.timer_takeline.enabled = 1;
			Time_delay.timer_takeline.started = 1;
			Time_delay.random_time	= Sensor_mode.random_takeline*400;	// random time delay for the frame send	
		}
		if(Sensor_mode.ON_takeline_waitsend == 1) 		ON_takeline();
		if(Sensor_mode.OFF_takeline_waitsend == 1)		OFF_takeline();		
	}	
}



void _Maintain_state(void)
{			
	if(Sensor_mode.presence_20sinterval == 0)
	{
		if(Sensor_mode.presen_timeout ==1)			// end detection
		{
				Sensor_mode.presen_timeout = 0;
				SCS_received.motion_detect = 0;			//Ignore detection
				if(Walk_Through_flag != 1)
				{
						Mode_frame_GR(KO_conf.GR,pre);
						Start_Time_Delay();
				}
		}
		
		if((SCS_received.motion_detect == 1)||(Sensor_mode.motion_initial_detect != 0)||(Sensor_mode.maintain_pre == 1))		
		{
			Sensor_mode.maintain_pre = 0;
			if(Sensor_mode.motion_initial_detect ==0 && SCS_received.motion_detect != 1)					// detection in the maintain state
			{
				WT_20s_detect();
				Mode_frame_GR(KO_conf.GR,pre);
			}
			else if(Sensor_mode.motion_initial_detect == 1)			// automatic just from initial to maintain
			{
			//	Sensor_mode.motion_initial_detect = 0;
			//	SCS_received.motion_detect =0;
			//	Mode_frame_GR(KO_conf.GR,pre);	
			}
			else if(Sensor_mode.motion_initial_detect == 2)			// W_T just from initial to maintain
			{
				//Sensor_mode.motion_initial_detect =0;
				//SCS_received.motion_detect =0;
			}
			
			if(SCS_received.motion_detect == 1)
			{
				Sensor_mode.presence_20sinterval = presence_20s; 	
				SCS_received.motion_detect = 0;	
				Mode_frame_GR(KO_conf.GR,pre);
				GS_presence_send();	
				WT_20s_detect();
			}
		}
	}
	// end of load Time_dalay_count
	if((Time_delay.timer_delay_set.time_out == 1)&&(Walk_Through_flag != 1))	//sensor will then go into Re_Trigger_State
	{	
		Sensor_mode.end_dection = 0;						
		Sensor_mode.mode_state = Re_Trigger_State;
		Time_delay.Re_Trigger_senconds = Re_Trigger_5s;

		if(KO_conf.FuncMod == ManualON_Auto_OFF)//((KO_conf.FuncMod == ManualON_Auto_OFF)||(KO_conf.FuncMod == ManualON_Manual_OFF))
		{
			Time_delay.Re_Trigger_senconds = Re_Trigger_30s;
		}
		frame_OFF_send();
		Sensor_mode.no_prence_off_send = 1;		//reyno 0619
	}
	
	// end of Walk_Through_Timeout_count
	if((Time_delay.Walk_Through_Timeout ==0)&&(Walk_Through_flag == 1))	        // 处于	Walk_Through mode
	{
		Sensor_mode.end_dection = 0;						
		Sensor_mode.mode_state = Initial_state;				// if in Walk_Through mode, the sensor won't go to Retrigger state
		Time_delay.timer_delay_set.time_out = 0;
		Sensor_mode.no_prence_off_send = 0;					// allow to send no presence and OFF frame again in initial state
		Stop_allTimer();
		if(First_detection_enable == 1)
		{
			First_detection_enable = 0;	
			frame_OFF_send();
			Sensor_mode.no_prence_off_send = 1;		//reyno 0619
    }
	}
	
	Delay_Alert();										
}


void _ReTrigger_State(void)
{
	//reyno 0609
	//if(Time_delay.Re_Trigger_senconds >0 && Sensor_mode.detect_scheme != 0)					// Re_Trigger_time out is not over        0714
	if(Time_delay.Re_Trigger_senconds >0 )					// Re_Trigger_time out is not over
	{	
		if(SCS_received.motion_detect == 1)
		{
			SCS_received.motion_detect = 0;			
			Sensor_mode.mode_state = Maintain_state;
			Time_delay.Re_Trigger_senconds = 0;				
			Start_Time_Delay();													// 回到maintain前，要重新开始计时延迟			
			Mode_frame_GR(KO_conf.GR,pre);	        		// send GR frame presence;			
			frame_ON_send();			
			GS_presence_send();		
			Sensor_mode.presence_20sinterval = presence_20s; 	 //  0514
		}	
	}
	else			// retrigger timeout
	{	
		Sensor_mode.mode_state = Initial_state;
		Sensor_mode.no_prence_off_send = 0;					// allow to send no presence and OFF frame again in initial state
		Time_delay.timer_delay_set.time_out = 0;
		if(KO_conf.FuncMod == ManualON_Auto_OFF)	Sensor_mode.manual_on_need = 1;	//在manual mode,retriggertimeout后，必需手动才能打开负载	
		Stop_allTimer();
	}
}


void _Standby_state(void)
{			
	
	if(Sensor_mode.presen_timeout ==1)			// end detection
		{
				Sensor_mode.presen_timeout = 0;
				//Mode_frame_GR(KO_conf.GR,pre);
				SCS_received.motion_detect = 0;			//Ignore detection
				Start_Time_Delay();
		}
	
	if(Sensor_mode.presence_20sinterval == 0)					
	{		
		if(SCS_received.motion_detect == 1)				
		{
			SCS_received.motion_detect = 0;
     	Sensor_mode.presence_20sinterval = presence_20s; 		
			WT_20s_detect();
			Mode_frame_GR(KO_conf.GR,pre);						// send GR frame presence;
			GS_presence_send();	
		}
	}
	
	if((Time_delay.timer_delay_set.time_out ==1)||(Time_delay.Re_Trigger_senconds ==1)||(Time_delay.Walk_Through_Timeout ==1))	
	{		
		Sensor_mode.mode_state = Initial_state;
		Time_delay.timer_delay_set.time_out = 0;
		Sensor_mode.no_prence_off_send = 0;			        	// allow to send no presence and OFF frame again in initial state
		Stop_allTimer();																	// stop all timer
	}
	// end of Regulation_Timeout_count
}


//******************************************************************************
// function for LM GR with addressed type==2
//******************************************************************************
void Function_LM_GR(void)
{
		function_check_status();             					//respond the frames according to its own state

		if(1)//(Sensor_mode.manual_on_need !=1)					//((Sensor_mode.manual_on_need !=1)&&(KO_conf.FuncMod != ManualON_Manual_OFF))	
		{														// 在manual mode,retrigger timeout后，必需手动才能打开负载
			if(++Sensor_mode.random_takeline > 10)	
			  	Sensor_mode.random_takeline = 1;				// used for random taking line
			if(Walk_Through_flag == 1)	
			  	SetBit(KO_conf.status[0],Status_Walk_through);
      switch(Sensor_mode.mode_state)
			{	
				case Initial_state:	
          Sensor_mode.detect_scheme = KO_conf.InitOccu;
					KO_conf.status[0] &= 0xF8;
					_Initial_state();
					break;
				case Maintain_state:
          Sensor_mode.detect_scheme = KO_conf.MaintainOccu;
					SetBit(KO_conf.status[0],Status_Maintain);
					ClrBit(KO_conf.status[0],Status_Retrigger);
					_Maintain_state();
					break;
				case Re_Trigger_State:
          Sensor_mode.detect_scheme = KO_conf.Retrigger;
					ClrBit(KO_conf.status[0],Status_Maintain);
					SetBit(KO_conf.status[0],Status_Retrigger);
					_ReTrigger_State();
					break;
				case Standby_state:
					_Standby_state();
					break;
				default: break;				
			}
		}
		//if(Sensor_mode.flag_leader_group == 1)		
		//LLED_ON ;
		//else							
		//LLED_OFF ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////		LM GR  machine states	end		/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
// function for KO119
//******************************************************************************
void Function_KO119(void)	// Stand-alone motion sensor
{
	set_point = 0xFFFF;
	DLL.current_level = 0;
	DLL.calc_level = 0;
	
	occupancy_detect();
	Function_LM_GR();	// Function_LM_GR(168);
	Light_regulation();
}

//******************************************************************************
// function for KO128
//******************************************************************************
void Function_KO128(void)								// Daylight and motion sensor for centralized LM system
{
	//daylight_service();
	//get_dl_level();
	unsigned long int temp_lux = 0;
	unsigned char i;
	
	if( Time_delay.sample_interval.time_out )
	{
		timer_interval_initial(1000);
		DLL.day_level = read_adc10bit ( daylight_channel );		// ADC value
#ifdef SMT
	DLL.read_lux = exp10(5 * (double)(DLL.day_level)/1024 * 100000 / RES_VALUE);
	DLL.calc_level = (unsigned int)DLL.read_lux ;
#else
	//DLL.calc_level = (CONST_DAYLIGHT * (unsigned long)DLL.day_level)/100;									// calculate the daylight level (LUX)around the sensor
	DLL.calc_level = (unsigned int)(g_slope * (double)DLL.day_level);
#endif
		DLL.lux_array[DLL.daylight_SampleCount++] = DLL.calc_level;
		
		if(DLL.daylight_SampleCount >= SAMPLE_COUNT)
		{
			DLL.daylight_SampleCount = 0;
			flags.KO_128_first_sampel_ready = 1;
		}
		
		if(flags.KO_128_first_sampel_ready)
		{
			#ifdef DEMOBOARD
					ClrBit(PORTB,0);
			#endif
					
			for(i=0;i<SAMPLE_COUNT;i++)
			{
				temp_lux += DLL.lux_array[i];
			}
			temp_lux /= SAMPLE_COUNT;
			if(DLL.calc_level > temp_lux * 1.03 || DLL.calc_level < temp_lux * 0.97)
			{
				configuration_answer_frame(0x10);
				for(i=0;i<SAMPLE_COUNT;i++)
				{
					DLL.lux_array[i] = DLL.calc_level;
				}
				timer_5m_initial(MIN_5);
			}
			temp_lux = 0;
			
			#ifdef DEMOBOARD
				SetBit(PORTB,0);
			#endif
		}
		
		if( Time_delay.timer_5m.time_out )
		{
			timer_5m_initial(MIN_5);
		  configuration_answer_frame(0x10);
		}
	}

	if(Time_delay.relay.time_out)
  	occupancy_detect();
	
	if(flags.motion_detected && (flags.timer_started == 0 || Time_delay.timer_delay_set.time_out))
	{
		flags.motion_detected = 0;
		frame_presence('0');
		relay_timer_initial(2000);
		Start_Time_Delay();
		flags.timer_started = 1;
	}
	
	if(Time_delay.timer_delay_set.time_out && flags.M2_step2_started == 0)
	{
		//Time_delay.timer_delay_set.time_out = 0;
		//flags.timer_started = 0;
		flags.M2_step2_started = 1;
		if(flags.motion_detected)
		{
			frame_presence('0');
			relay_timer_initial(2000);
			Start_Time_Delay();
		}
	}
}

//******************************************************************************
// function for KO166
//******************************************************************************
void Function_KO166(char addrestype, char detectype, char LightReg)
{
	
}

void Function_KO164(void)
{
	get_dl_level();
#ifdef SMT
	DLL.read_lux = exp10(5 * (double)(DLL.day_level)/1024 * 100000 / RES_VALUE);
	DLL.calc_level = (unsigned int)DLL.read_lux ;
#else
	//DLL.calc_level = (CONST_DAYLIGHT * (unsigned long)DLL.day_level)/100;									// calculate the daylight level (LUX)around the sensor
	DLL.calc_level = (unsigned int)(g_slope * (double)DLL.day_level);
#endif
}

void Function_KO165(void)
{
  	occupancy_detect();
		
		if(flags.motion_detected && flags.timer_started == 0)
		{
			flags.motion_detected = 0;
			frame_presence('0');
			Start_Time_Delay();
			flags.timer_started = 1;
		}
		
		if(Time_delay.timer_delay_set.time_out)
		{
			if(flags.motion_detected)
			{
				frame_presence('0');
			}
		}
}
//******************************************************************************
// function for KO168
//******************************************************************************
void Function_KO168(char addrestype, char FuncMod, char LightReg)
{
  	daylight_service();
  	occupancy_detect();
		Function_LM_GR();	// Function_LM_GR(168);		
		Light_regulation();
}
//******************************************************************************
// function mode for LM group end
//******************************************************************************



void function_service_init(void)
{
		timer0_enable();                      			// enable timer for sensor detection add 20090408 by alan
		ultWarmUpEvents();                    			// init the US detector
		daylight_set_init();
		Sensor_mode.detect_scheme = KO_conf.InitOccu;
		Time_delay.motion.count = 0;
		Time_delay.motion.time_out = 0;
		Time_delay.motion.enabled = 1;
		Time_delay.motion.started = 1;
		Delay_Time_set =  KO_conf.Seconds + (unsigned long int)KO_conf.Minutes*60 + (unsigned long int) KO_conf.Hours*3600;		//calculate the time set by user
	
  	set_point = KO_conf.DaylightSetp*5;   	
		if(set_point == 0)	
			set_point = 1500;		// for debug alan
	
		if(KO_conf.KO_number == 128)
    {
     		M2_timer = (eep_M2_hour*3600 + eep_M2_min*60 + eep_M2_sec);			
				Start_Time_Delay();											//call Start_Time_Delay() to send the dll frame every 5min
      	if(M2_timer == 0)		M2_timer = 5;   		// for debug //default presence frame interval time
    }
		
		
		 switch(KO_conf.KO_number)
		{
			case 119:
			case 168:
				// sensitivity of the sensor is set in the files PIR.c and US.c
				Sensor_mode.mode_state = 1;	
				if(KO_conf.FuncMod == ManualON_Auto_OFF)	
					Sensor_mode.manual_on_need = 1;     // in manualon mode
				if (KO_conf.LightReg)
					Sensor_mode.flag_leader_group = 1;
			break;
			
			case 128:
				timer_interval_initial(1000);
				timer_5m_initial(MIN_5);
				DLL.daylight_SampleCount = 0;
				flags.KO_128_first_sampel_ready = 0;
			break;
			
			case 165:
			break;
			
			default:break;	
		}
	/*
		KO_conf.KO_number = 168;	//debug
		KO_conf.en_load = 1;
		KO_conf.GR = 2;	
		KO_conf.Reference = 2;
		KO_conf.AddressType = 2;
		Delay_Time_set =  30;
		KO_conf.FuncMod = ManualON_Auto_OFF;
	*/

}

//#pragma optimize=none
void function_service(void)
{

  if(Sensor_mode.init_OK == 0)			// if not initialed
	{
			Sensor_mode.init_OK = 1;
			KO_conf.KO_number = StrToChar(KO);				
			KO_conf.KO_number = KO_conf.KO_number<<8;
			KO_conf.KO_number += StrToChar(&KO[2]);
	  	function_service_init();
			SCS_received.P2P_actuator_flag = 1;
			SCS_received.P2P_dimmer_flag = 0;
	}

	//set_point = KO_conf.DaylightSetp*5;
	
  switch(KO_conf.KO_number)
	{
		case 112:
		
		  	break;
		case 119:
		  	Function_KO119();
		 	break;
		case 128:
		  	Function_KO128();  				//_modality_2();
		  	break;
		case 164:
		
		  	break;
		case 165:
		  	Function_KO165();
		  	break;
		case 166:
		  	// Function_KO166(2,x,x); 		// Group
		  	// Function_KO166(0,1,0);  		//_modality_1();
		  	// Function_KO166(0,3,1);  		//_modality_4();
		  	// void Function_KO166(char addrestype, char detectype, char LightReg);
				Function_KO166(KO_conf.AddressType, KO_conf.FuncMod, KO_conf.LightReg);
		  	break;
		case 168:
		  	// Function_KO168(2,x,x);  		// Group
		  	// Function_KO168(0,1,0);  		//_modality_0();	
		  	// Function_KO168(0,1,1);  		//_modality_3();	
		  	// void Function_KO168(char addrestype, char FuncMod, char LightReg);
		  	Function_KO168(KO_conf.AddressType, KO_conf.FuncMod, KO_conf.LightReg); 	
				//Function_KO168(2,1,1);
		  	break;
		case 0x203:
			/*
		  if(Configurators.M == '0')		
				Function_KO168(0,1,0);  	//_modality_0();	
			else if(Configurators.M == '2')	
				Function_KO128(); 			//_modality_2();
			else if(Configurators.M == '3')	    Function_KO168(0,1,1);  	//_modality_3();	
			*/
		  	break;
		case 0x204:
		  /*
		  if(Configurators.M == '1')			
				Function_KO166(0,1,0);  									//_modality_1();
			else if(Configurators.M == '4')		Function_KO166(0,3,1);  	//_modality_4();
		  */
		  	break;
		case 0x1FF:
		
		  	break;
		default:
		  	break;	
	}
}

void check_frame_received_maintain(void)
{
	
}

void timer_interval_initial(unsigned long int ms)
{
	Time_delay.sample_interval.stack_top = ms;
	Time_delay.sample_interval.count = 0;
	Time_delay.sample_interval.time_out = 0;
	Time_delay.sample_interval.enabled = 1;
	Time_delay.sample_interval.started = 1;
}

void timer_5m_initial(unsigned long int ms)
{
	Time_delay.timer_5m.stack_top = ms;
	Time_delay.timer_5m.count = 0;
	Time_delay.timer_5m.time_out = 0;
	Time_delay.timer_5m.enabled = 1;
	Time_delay.timer_5m.started = 1;
}