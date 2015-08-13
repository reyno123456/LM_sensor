#include <ioavr.h>
#include <stdio.h>
#include "usart.h"
#include "board.h"
#include "moudle_SCS.h"
#include "decode_scs.h"
#include "stdlib.h"
#include "global_variable.h"
#include "application.h"
#include "decode_scs_next.h"
#include "moudle_scs.h"
#include "application.h"
#include "string.h"
#include "configuration.h"
#include "function_service.h"

void reception_buffer_clear(unsigned char temp)
{
#ifndef DEBUG

	unsigned char i;
		for(i=0;i<8;i++)
		{
			g_short_buffer[i] = 0;
		}
	
		for(i=0;i<4;i++)
		{
			g_asc_short_buffer[i] = 0;
		}
	

		for(i=0;i<8;i++)
		{
			g_asc_reception_buffer[i] = 0;
		}
	
		for(i=0;i<16;i++)
		{
			g_reception_buffer[i] = 0;
		}
#else
	extern unsigned char g_RxBuffer[];
	extern unsigned char RxNumber;
		
	for(i=0;i<RX_BUFFER_SIZE;i++)
	{
		g_RxBuffer[i] = 0;
	}
	RxNumber = 0;

#endif
}

unsigned char decode_id(void)
{
	unsigned char i;
	unsigned char buffer[3];

	//static unsigned char ID_buffer[8];
	volatile unsigned char current = 0xFF;

	for(i=0;i<DEEP;i++)
	{
		if(scs_frame[i].finished)
		{
			current = i;
			break;
		}
	}

	if(scs_frame[current].finished && current != 0xFF)
	{
		switch(StrToChar(&scs_frame[current].byte[1]))
		{
			case 0x18:
				for(i=0;i<16;i++)
				{
					g_reception_buffer[i] = scs_frame[current].byte[i+3];
				}
				for(i=0;i<8;i++)
				{
					buffer[0] = g_reception_buffer[i * 2];
					buffer[1] = g_reception_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_reception_buffer[i] = StrToChar(buffer);
				}

				switch(g_asc_reception_buffer[0])
				{
					case 0xD0:
            if(g_reception_buffer[6] == '0' || g_reception_buffer[6] == 'F')
						  id_frame();
					break;

					default:break;
				}
			break;

			default:
				scs_frame[current].finished = 0;	
        if(state.id_setting == 1)
	      {
		      if( Time_delay.timer_flex.time_out == 1 )
		      {
			      state.id_setting = 0;
			      send_frame_pp_ext_broad("D000010E00000000",TRANS_DELAY);
			      asm("nop");
		      }
	      }
			return 1;
		}
	}
	scs_frame[current].finished = 0;
	return 0;
}

unsigned char decode_SCS(void)
{
	volatile unsigned char current = 0xFF;
	unsigned char i;
	unsigned char buffer[3];
	//unsigned char current;

	for(i=0;i<DEEP;i++)
	{
		if(scs_frame[i].finished)
		{
			current = i;
			break;
		}
	}

	if(scs_frame[current].finished && current != 0xFF)
	{
		switch(StrToChar(&scs_frame[current].byte[1]))
		{
    	case 0x00:
      break;

    	case 0x01:
      break;

    	case 0x07:
      break;

			case 0x17:
				for(i=0;i<8;i++)
				{
					g_short_buffer[i] = scs_frame[current].byte[i+3];
				}
				
				for(i=0;i<4;i++)
				{	
					buffer[0] = g_short_buffer[i * 2];
					buffer[1] = g_short_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_short_buffer[i] = StrToChar(buffer);
				}
			break;

			case 0x18:
				for(i=0;i<16;i++)
				{
					g_reception_buffer[i] = scs_frame[current].byte[i+3];
				}

				for(i=0;i<8;i++)
				{
					buffer[0] = g_reception_buffer[i * 2];
					buffer[1] = g_reception_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_reception_buffer[i] = StrToChar(buffer);
				}
			break;

			default:
				scs_frame[current].finished = 0;		
			return 1;
		}
	}
	scs_frame[current].finished = 0;
	return 0;
}

unsigned char is_gateway_busy(void)
{
	unsigned char i;
	//unsigned char current;

	for(i=0;i<DEEP;i++)
	{
		if(scs_frame[i].finished)
		{
      scs_frame[i].finished = 0;
      switch(StrToChar(&scs_frame[i].byte[1]))
		  {
        case 0x00:
          //scs_frame[current].finished = 0;
          return 0x02;

        case 0x01:
         return 0x01;

        case 0x07:
          return 0x07;

        case 0x08:
          if(StrToChar(&scs_frame[i].byte[3]) == 2 || StrToChar(&scs_frame[i].byte[3]) == 3)
            return 1;
        break;

				case 0x13:
					return 0x13;
				
        case 0x22:
          return 1;

			  default: break;
		  }
		}
	}
  return 0;
}

//SCS_received.presence GR presence
//SCS_received.GS_presence GS presence
void application_decode_short(void)
{	
	if(KO_conf.AddressType == GROUP)
	{
		if(g_asc_short_buffer[0] == KO_conf.Reference)		//APL\00\12\00
		{
			if(g_asc_short_buffer[2] == 0x12 && g_asc_short_buffer[3] == 0x00 )
				SCS_received.GR_ON = 1;
		}
		
		if(g_asc_short_buffer[0] == 0xB5)
		{
			if(g_asc_short_buffer[1] == KO_conf.GR)
			{
				if(g_asc_short_buffer[2] == 0x1D)
				{
					if(g_asc_short_buffer[3] == 0x00)	
						SCS_received.presence = 1;	// B|5 G|G 1|D 0|0  "presence"
					else if(g_asc_short_buffer[3] == 0x01)	
						SCS_received.no_presence = 1;	// B|5 G|G 1|D 0|1 "no presence"
				}
				
				if(g_asc_short_buffer[2] == 0x12)
				{
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.GR_ON = 1;		//B|5 G|G 1|2 0|0   "Group frame ON"
					
					if(g_asc_short_buffer[3] == 0x01)	
						SCS_received.GR_OFF = 1;	// B|5 G|G 1|2 0|1  "group frame OFF"
					
					if(g_short_buffer[7] == 'D')			// dimmer	0526
					{
						if(g_short_buffer[6] == '0')
							SCS_received.GR_OFF = 1;	
						else if(g_short_buffer[6] <= '9')
							SCS_received.GR_ON = 1;
					}
				}							
			}
				
			if(((KO_conf.GS1 != 0)||(KO_conf.GS2 != 0)) && (g_asc_short_buffer[1] != 0))
			{
				if((g_asc_short_buffer[1] == KO_conf.GS1)||(g_asc_short_buffer[1] == KO_conf.GS2))				
				{
					if(g_asc_short_buffer[2] == 0x1D)
					{
						if(g_asc_short_buffer[3] == 0)	
						{
							if(Time_delay.GS_wait_22s ==0)
									SCS_received.GS_presence = 1;									
						}
						// B|5 G|S 1|D 0|0  "presence" send by GS
					}
				}		
			}
		}	
	}
	
	if(((KO_conf.AddressType == GROUP)&&(KO_conf.Reference == g_asc_short_buffer[1]))||((KO_conf.AddressType == PP)&&(KO_conf.DesAdd == g_asc_short_buffer[1])))
	{		
		if(g_asc_short_buffer[0] == 0xB8)	// frame B8						// B|8 G|G 1|2 0|1
		{
			if(g_asc_short_buffer[2] == 0x12)
			{
				if(Time_delay.regulation.time_out == 0)			// received a single update frame,200ms after received a ON before
				{			
					DLL.start_regulation = 1;				// ALAN 0729, Start to regulation when received update ON of its own GR
					SetBit(KO_conf.status[0],Status_Regulationing);
				}
				else
				{
					//DLL.start_regulation = 0;				
					//ClrBit(KO_conf.status[0],Status_Regulationing);
					DLL.start_regulation = 0;				// ALAN 0729, Start to regulation when received update ON of its own GR
					ClrBit(KO_conf.status[0],Status_Regulationing);
				}

				switch(g_short_buffer[7])
				{
					case '0':
						Sensor_mode.power_on_flag = 1;
						KO_conf.status[1] = Status_ON;		//reyno 0616
						SCS_received.update_state_ON = 1;
						break;
					case '1':
						Sensor_mode.power_on_flag = 0;
						KO_conf.status[1] = Status_OFF;		//reyno 0616
						SCS_received.update_state_OFF = 1;
						break;
					case 'D':
						Sensor_mode.power_on_flag = 1;
						SCS_received.update_state_LEVEL = 1;
						SCS_received.P2P_dimmer_flag = 1;			// dimmer,used for regulation
						SCS_received.P2P_actuator_flag = 0;
						
						switch (g_short_buffer[6])
						{
							case '1':
							KO_conf.status[1]=1;
							break;
							
							case '2':
							KO_conf.status[1]=10;
							break;
							
							case '3':
							KO_conf.status[1]=20;
							break;
							
							case '4':
							KO_conf.status[1]=30;
							break;
							
							case '5':
							KO_conf.status[1]=40;
							break;
							
							case '6':
							KO_conf.status[1]=50;
							break;
							
							case '7':
							KO_conf.status[1]=60;
							break;
							
							case '8':
								KO_conf.status[1]=75;
							break;
							
							case '9':
								KO_conf.status[1]=Status_ON;
							break;
							
							default:break;
						}
						break;
						default:	break;	
					}
			}
			
			if(g_asc_short_buffer[2] == 0x1D)
			{
				if(KO_conf.AddressType == PP)
				{
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.presence = 1;
					else if(g_asc_short_buffer[3] == 0x01)
						SCS_received.no_presence = 1;
				}
			}
		}
		
		if(KO_conf.AddressType == PP)
		{
			switch(g_asc_short_buffer[2])
			{
				case 0x12:
					/*
					if(KO_conf.LightReg == 1)
					{	
						DLL.start_regulation = 1;
						SetBit(KO_conf.status[0],Status_Regulationing);
						regulation_timer_initial();
					}
					*/
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.GR_ON = 1;         // 0714 alan in order to compatible with GR, P2P and GR use the same flag SCS_received.GR_ON
					else if(g_asc_short_buffer[3] == 0x01)
						SCS_received.GR_OFF = 1;
				break;
				default:break;
			}
		}	
	}
	
	//receive APL XX 12 00
	if(g_asc_short_buffer[0] == KO_conf.DesAdd)
	{
		switch(g_asc_short_buffer[2])
		{
			case 0x12:
				if(g_asc_short_buffer[3] == 0x00)
				{
					SCS_received.GR_ON = 1;         // 0714 alan in order to compatible with GR, P2P and GR use the same flag SCS_received.GR_ON
					if(KO_conf.LightReg == 1)
					{	
						DLL.start_regulation = 1;
						SetBit(KO_conf.status[0],Status_Regulationing);
						regulation_timer_initial();
					}
				}
				else if(g_asc_short_buffer[3] == 0x01)
					SCS_received.GR_OFF = 1;
			break;
			default:break;
		}
	}
	
}

void application_decode_long(void)
{
	if((g_asc_reception_buffer[1] == KO_conf.DesAdd && KO_conf.AddressType == PP) || (g_asc_reception_buffer[1] == KO_conf.Reference && KO_conf.AddressType == GROUP) || (g_asc_reception_buffer[1] == KO_conf.GR && KO_conf.AddressType == GROUP))
	{
		if(g_asc_reception_buffer[5] == 0x0D)
		{
			SCS_received.P2P_dimmer_flag = 1;			// dimmer,used for regulation
			SCS_received.P2P_actuator_flag = 0;
			
			KO_conf.status[1] = g_asc_reception_buffer[5];
		}
		
		//D2 A|Pl 0|1 3|4 0|D X|X X|X X|X		Extended state update frame
		if((g_asc_reception_buffer[0]==0xD2)&&(g_asc_reception_buffer[3]==0x34)&&(g_asc_reception_buffer[4]==0x0D))//&&(g_reception_buffer[11]=='0'||g_reception_buffer[11]=='D'))
		{
			if(Time_delay.regulation.time_out == 0)			// received a single update frame,200ms after received a ON before
			{			
				DLL.start_regulation = 1;									// ALAN 0729, Start to regulation when received update ON of its own GR
				SetBit(KO_conf.status[0],Status_Regulationing);
				//DLL.start_regulation = 0;				
				//ClrBit(KO_conf.status[0],Status_Regulationing);
			}
			else
			{
				DLL.start_regulation = 0;				
				ClrBit(KO_conf.status[0],Status_Regulationing);
				//DLL.start_regulation = 1;									// ALAN 0729, Start to regulation when received update ON of its own GR
				//SetBit(KO_conf.status[0],Status_Regulationing);
			}
		}
	}
}

void calibration_decode(void)
{
	// add 0519
	// Enter calibration waiting mode	D1 01 01 42 14 00 00 00
	// Exit calibration waiting mode	D1 01 01 42 14 00 00 FF
	// Sent calibration lux				D1 01 01 42 10 0X XX XX
	// change by reyno May30
	if(g_asc_reception_buffer[3] == 0x42)       	// D5 LOC 01 42 14 XX XX XX 0519
	{
		if(g_asc_reception_buffer[4] == 0x14 )
		{
			if(g_asc_reception_buffer[7] ==0x00)
			{
				SCS_received.calib_wait = 1;    	// D1 LOC 01 42 14 XX XX 00
		  	led_blinking(250,250);
				state.main_state = CALIBRATION;
			}
			else if(g_asc_reception_buffer[7] == 0xFF)
			{
				SCS_received.calib_wait = 0; 		//SCS_received.calib_exit = 1; 		// D1 LOC 01 42 14 XX XX FF
		 		led_blinking_disable(0);
				state.main_state = NORMAL;
			}
		}
		
		if(g_asc_reception_buffer[4] == 0x10)
		{
			if(SCS_received.calib_wait == 1)
			{
				unsigned long int temp_lux;
				temp_lux = g_asc_reception_buffer[5]&0x0F;
				temp_lux <<= 8;
				temp_lux += g_asc_reception_buffer[6];
				temp_lux <<= 8;
				temp_lux += g_asc_reception_buffer[7];
			
				DLL.setpoint_M = temp_lux*10/DLL.day_level;
				eep_setpoint[2] = DLL.setpoint_M;
				daylight_set_init();
				buzzer_ms(500);	
			}
		}
	}
}

//reyno 0602
void scs_calibration(void)
{								
	if(g_asc_reception_buffer[3] == 0x42)       	// D5 LOC 01 42 14 XX XX XX 0519
	{
		if(g_asc_reception_buffer[4] == 0x14 )
		{
			if(g_asc_reception_buffer[7] ==0x00)
			{
				SCS_received.calib_wait = 1;    	// D1 LOC 01 42 14 XX XX 00
		  	led_blinking(250,250);
				state.main_state = CALIBRATION;
			}
			else if(g_asc_reception_buffer[7] ==0x01)
			{
				state.main_state = FACTORY_CALIBRATION;
				buzzer_ms(500);
				led_blinking_disable(0);
			}
			else if(g_asc_reception_buffer[7] == 0xFF)
			{
				SCS_received.calib_wait = 0; 		//SCS_received.calib_exit = 1; 		// D1 LOC 01 42 14 XX XX FF
		 		led_blinking_disable(0);
				state.main_state = NORMAL;
				if(ee_main_state == FACTORY_CALIBRATION_STEP1)
					ee_main_state = NORMAL;
			}
		}
		
		if(g_asc_reception_buffer[4] == 0x10)
		{
			if(SCS_received.calib_wait == 1)
			{
				unsigned long int temp = 0;				// add by alan
				float f_temp;
				temp = g_asc_reception_buffer[5];
				temp = temp<<8;
				temp += g_asc_reception_buffer[6];
				temp = temp<<8;
				temp += g_asc_reception_buffer[7];
				temp &= 0xFFFFF;
				if(Sensor_mode.power_on_flag)
				{	
					KO_conf.DF = temp*10/ DLL.calc_level;			//0526
					f_temp = (float)temp*10/ (float)DLL.calc_level;
					if((f_temp - KO_conf.DF >= 0.5) && (KO_conf.DF != 255))
						KO_conf.DF++;
					write_KO(22,KO_conf.DF); //reyno 0602
					write_ee_KO(22,KO_conf.DF);
				}
				else
				{
					KO_conf.NF = temp*10/ DLL.calc_level;			//0526
					f_temp = (float)temp*10/ (float)DLL.calc_level;
					if((f_temp - KO_conf.NF >= 0.5) && (KO_conf.NF != 255))
						KO_conf.NF++;
					write_KO(24,KO_conf.NF); //reyno 0602
					write_ee_KO(24,KO_conf.NF);
				}
				buzzer_ms(500);
			}
		}
	}
}