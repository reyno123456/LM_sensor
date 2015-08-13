#include <ioavr.h>
#include <inavr.h>
#include <stdio.h>
#include "usart.h"
#include "board.h"
#include "moudle_SCS.h"
#include "decode_scs.h"
#include "stdlib.h"
#include "global_variable.h"
#include "decode_scs_next.h"
#include "application.h"
#include <string.h>
#include "configuration.h"
#include "function_service.h"
#include "PIR.h"
#include "US.h"

void send_frame_pp(char *data, unsigned int ms)
{
	unsigned char i;
	unsigned char buffer[13];
	unsigned char temp;

	buffer[0] = '$';
	buffer[1] = '0';
	buffer[2] = '3';
	for(i=0;i<8;i++)
	{
		buffer[i+3] = *(data+i);
	}

	buffer[11] = 13;
	buffer[12] = 0;

	put_s(buffer);
	delay_ms(ms);
	
	for(i=0;i<125;i++)
  {
		temp = is_gateway_busy();
		if(temp == 0x07 || temp == 0x01)
		{
			put_s(buffer);
		}
		else if(temp == 0x02)
		{
			break;
		}
  }
}

void send_frame_pp_broad(char *data, unsigned int ms)
{
	unsigned char i;
	unsigned char buffer[13];
	unsigned char temp;

	buffer[0] = '$';
	buffer[1] = '0';
	buffer[2] = '4';
	for(i=0;i<8;i++)
	{
		buffer[i+3] = *(data+i);
	}

	buffer[11] = 13;
	buffer[12] = 0;

	put_s(buffer);
	delay_ms(ms);
	
	for(i=0;i<250;i++)
  {
		temp = is_gateway_busy();
		if(temp == 0x07 || temp == 0x01)
		{
			put_s(buffer);
		}
		else if(temp == 0x02)
		{
			break;
		}
  }
	
}

void send_frame_pp_ext(char *data, unsigned int ms)
{
	unsigned char i;
	unsigned char buffer[21];

	buffer[0] = '$';
	buffer[1] = '0';
	buffer[2] = '5';
	for(i=0;i<16;i++)
	{
		buffer[i+3] = *(data+i);
	}
	buffer[19] = 13;
	buffer[20] = 0;

	put_s(buffer);

	delay_ms(ms);
}

void send_frame_pp_ext_broad(char *data, unsigned int ms)
{
	unsigned char i;
	unsigned char buffer[21];
	unsigned char buffer_char[3];
	unsigned char temp = 0;

	buffer[0] = '$';
	buffer[1] = '0';
	buffer[2] = '6';
	for(i=0;i<16;i++)
	{
		buffer[i+3] = *(data+i);
	}
	buffer[19] = 13;

	//add by 2009 02 18
	if(product_information.conf_type == 3)
	{
		buffer[5] = '0';
		buffer[6] = '0';
	}
	else if( product_information.conf_type == 2 )
	{
		if(g_reception_buffer[7] == '3')
		{
			buffer[5] = '0';
			buffer[6] = '0';
		}
		else
		{
			CharToStr( ee_KO_conf.GR, buffer_char);
			buffer[5] = buffer_char[0];
			buffer[6] = buffer_char[1];
		}
	}
	else
	{
		if(g_reception_buffer[7] == '3')
		{
			buffer[5] = '0';
			buffer[6] = '0';
		}
		else
		{
			CharToStr( ee_KO_conf.DesAdd , buffer_char);
			buffer[5] = buffer_char[0];
			buffer[6] = buffer_char[1];
		}
	}

  if( product_information.cen_system == CEN )
  {
    buffer[5] = product_information.local_A;
    buffer[6] = product_information.local_PL;
  }
  else
  {
    buffer[5] = '0';
		buffer[6] = '0';
  }

	buffer[20] = 0;
	put_s(buffer);
  delay_ms(ms);
  /*
  if(is_gateway_busy() != 0x02)
  {
    put_s(buffer);
    delay_ms(ms);
  }
	delay_ms(ms);
  */

  for(i=0;i<250;i++)
  {
		temp = is_gateway_busy();
		if(temp == 0x07 || temp == 0x01)
		{
			put_s(buffer);
		}
		else if(temp == 0x02)
		{
			break;
		}
  }
}

void  org_ext_broad(char *data, unsigned int ms)
{
	unsigned char i;
	unsigned char buffer[21];
	unsigned char temp = 0;
	
	buffer[0] = '$';
	buffer[1] = '0';
	buffer[2] = '6';
	for(i=0;i<16;i++)
	{
		buffer[i+3] = *(data+i);
	}
	buffer[19] = 13;

	//add by 2009 02 18

	put_s(buffer);

	delay_ms(ms);

  for(i=0;i<250;i++)
  {
		temp = is_gateway_busy();
		if(temp == 0x07 || temp == 0x01)
		{
			put_s(buffer);
		}
		else if(temp == 0x02)
		{
			break;
		}
  }
}

void id_frame(void)
{
	unsigned char i;
	unsigned char buffer_tx[17];
	static unsigned char ID_buffer[9] = "00000000";

	strncpy(buffer_tx,"D000010400000000",17);
	buffer_tx[16] = 0;

	i = 8;
	buffer_tx[i++] = ee_ID[0];
	buffer_tx[i++] = ee_ID[1];
	buffer_tx[i++] = ee_ID[2];
	buffer_tx[i++] = ee_ID[3];
	buffer_tx[i++] = ee_ID[4];
	buffer_tx[i++] = ee_ID[5];
	buffer_tx[i++] = ee_ID[6];
	buffer_tx[i++] = ee_ID[7];

	switch(g_reception_buffer[7])
	{
		case '0':
			//reserved
		break;

		case '1':
			//reserved
		break;

		case '2':
			//if(product_information.ID_factory_assigned == 0)
			//{
				for(i=0;i<8;i++)
				{
					ID_buffer[i] = g_reception_buffer[i+8];
				}
				timer_flex_initial(10000);
				state.id_setting = 1;
			//}
		break;

		case '3':
			//ID request
			if(flags.id_ack == 0)
			{
				if(flags.id_request_enabled)
				{
					if(ee_product_information.ID_confed)
					{
						asm("nop");
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
					}
				}
			}
		break;

		case '5':
			//if(state.id_setting == 1 && product_information.ID_factory_assigned == 0)
			if(state.id_setting == 1)
			{	
				state.id_setting = 0;
				if((g_reception_buffer[8] == ID_buffer[0]) && (g_reception_buffer[9] == ID_buffer[1]) && (g_reception_buffer[10] == ID_buffer[2]) && (g_reception_buffer[11] == ID_buffer[3]) && (g_reception_buffer[12] == ID_buffer[4]) && (g_reception_buffer[13] == ID_buffer[5]) && (g_reception_buffer[14] == ID_buffer[6]) && (g_reception_buffer[15] == ID_buffer[7]))
				{
					ID_setting(ID_buffer);
					ee_product_information.ID_confed = 0x01;
					strncpy(buffer_tx,"D000010400000000",17);
					strncpy(&buffer_tx[8],ID_buffer,9);
					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
					flags.id_confed = 1;
					ee_product_information.ID_factory_assigned = 1;
					if( product_information.ID_factory_assigned == 0 ) system_reset();
				}
				else
				{
					buffer_tx[7] = 'E';
					strncpy(&buffer_tx[8],"00000000",9);
					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				}
			}
		break;

		case '6':
			if(ee_product_information.ID_confed)
			{
				if((g_reception_buffer[8] == ee_ID[0])
					&& (g_reception_buffer[9] == ee_ID[1])
					&& (g_reception_buffer[10] == ee_ID[2])
					&& (g_reception_buffer[11] == ee_ID[3])
				 	&& (g_reception_buffer[12] == ee_ID[4])
				 	&& (g_reception_buffer[13] == ee_ID[5])
				 	&& (g_reception_buffer[14] == ee_ID[6])
				 	&& (g_reception_buffer[15] == ee_ID[7]))
				{
					// ID configuration
					state.programming = 1;
					flags.png = 1;
					//send_frame_pp_ext_broad("D200013481040000",TRANS_DELAY);
          state.main_state = STATE_PROGRAMMING;
					//KO_SCENARIO_TRANS_DELAY = 80;
					diagnostic_frame();
					//KO_SCENARIO_TRANS_DELAY = 80;
					flags.AA_received = 0;
					flags.parameter_setting_wrong = 0;
					flags.parameter_write_right = 0;
					//png_dian
				}
			}
		break;

		case '7':
			if(ee_product_information.ID_confed)
			{
				if((g_reception_buffer[8] == ee_ID[0])
					&& (g_reception_buffer[9] == ee_ID[1])
					&& (g_reception_buffer[10] == ee_ID[2])
					&& (g_reception_buffer[11] == ee_ID[3])
				 	&& (g_reception_buffer[12] == ee_ID[4])
				 	&& (g_reception_buffer[13] == ee_ID[5])
				 	&& (g_reception_buffer[14] == ee_ID[6])
				 	&& (g_reception_buffer[15] == ee_ID[7]))
				{
					// ID configuration
					// only send diagnostic frame
					//TRANS_DELAY = 60;							//too big cause PnG timing error, too small cause interface chip lost frames
          state.main_state = STATE_TEST;
					diagnostic_frame();			//modified 2009 1 9
				}
			}
    break;

		case '8':
			//ID request not conf
			if(flags.id_ack == 0)
			{
				if(flags.id_request_enabled)
				{
					if(product_information.ID_confed)
					{
						if(product_information.conf_type == 3 )
						{
							asm("nop");
							send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
						}
					}
				}
			}
		break;

		case '9':
			//ID request conf
			if(flags.id_ack == 0)
			{
				if(flags.id_request_enabled)
				{
					if(product_information.ID_confed)
					{
						if(product_information.conf_type == 0 || product_information.conf_type == 1 || product_information.conf_type == 2)
						{
							asm("nop");
							send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
						}
					}
				}
			}
		break;

		case 'A':
			if(strcmp(&buffer_tx[8],&g_reception_buffer[8]) == 0)
				flags.id_ack = 1;
		break;

		case 'B':
		  flags.id_ack = 0;

			flags.id_request_enabled = 1;
			if( product_information.conf_type == 3 )
			{
				//send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			}
		break;
/*
		case 'C':
			if(g_asc_reception_buffer[4] == 0x00 && g_asc_reception_buffer[5] == 0x00 && g_asc_reception_buffer[6] == 0x00 && g_asc_reception_buffer[7] == 0x00)
			{
				product_information.ID_factory_assigned = 0; // for reassigned ID
			}
		break;
*/		
		default: break;
	}
}

void parameter_set(unsigned char data)
{
	switch(data)
	{
		//case 0x80:
			
	}
}

void diagnostic_frame(void)
{
	unsigned char i;
	unsigned char buffer_tx[17] = "D000010400059876";

  __disable_interrupt();
	flags.diagnostic = 1;
	//configuration_answer_frame(0x80);
	//send_frame_pp_ext_broad("D200013480052322",1);
	configuration_answer_frame(0x80);
	configuration_answer_frame(0x81);
	configuration_answer_frame(0x83);
	configuration_answer_frame(0x86);
	//id_frame('3',1);
  for(i=0;i<8;i++)
  {
    buffer_tx[8+i] = ee_ID[i];
  }
	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  ko_answer_all();
	configuration_answer_frame(0x8C);
	frame_buffer_clear();
  __enable_interrupt();
	flags.diagnostic = 0;
}

//unsigned char data[7];
void configuration_setting_frame(unsigned char value)
{
	unsigned char i;
	unsigned char buffer_tx[17];			// 20090216
	unsigned int write_parameter_resutl = 1;
  unsigned char flag_configurator;
	//unsigned char *p_KO = &KO_conf;
	//unsigned char *p_ee_KO = &ee_KO_conf;

	switch (value)
	{
		case 0x15:
			if(g_asc_reception_buffer[7] >= 0 && g_asc_reception_buffer[7] <= 3)
			{
				KO_conf.PirSens = g_asc_reception_buffer[7];
				ee_KO_conf.PirSens = g_asc_reception_buffer[7];
				KO_conf.USSens = g_asc_reception_buffer[7];
				ee_KO_conf.USSens = g_asc_reception_buffer[7];
				PIR_SENSE_SET();
				US_SENSE_SET();
				strncpy(buffer_tx,"D200013415000000",17);
				buffer_tx[14] = g_reception_buffer[14];
				buffer_tx[15] = g_reception_buffer[15];
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			}
		break;
		
		case 0x16:
			//#define INDEX_HOURS 10
			//#define INDEX_MINUTES 11
			//#define INDEX_SECONDS 12
			if(g_asc_reception_buffer[6] <= 0x3B && g_asc_reception_buffer[7] <= 0x3B)
			{
				write_KO(INDEX_HOURS,g_asc_reception_buffer[5]);
				write_ee_KO(INDEX_HOURS,g_asc_reception_buffer[5]);
				
				write_KO(INDEX_MINUTES,g_asc_reception_buffer[6]);
				write_ee_KO(INDEX_MINUTES,g_asc_reception_buffer[6]);
				
				write_KO(INDEX_SECONDS,g_asc_reception_buffer[7]);
				write_ee_KO(INDEX_SECONDS,g_asc_reception_buffer[7]);
				
				strncpy(buffer_tx,"D200013416000000",17);
				strncpy(&buffer_tx[10],&g_reception_buffer[10],7);

				Delay_Time_set =  KO_conf.Seconds + (unsigned long int)(KO_conf.Minutes*60) + (unsigned long int)(KO_conf.Hours)*3600;
				Time_delay.timer_delay_set.count = Delay_Time_set;
				
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			}
			
		break;
		
    case 0x80:
			if(product_information.ID_factory_assigned == 0)
			{
      	for(i=0;i<6;i++)
      	{
        	ee_parameter.device_modle[i] = g_reception_buffer[i+10];
      	}
			}
    break;

		case 0x81:
			if(product_information.ID_factory_assigned == 0)
			{
				for(i=0;i<6;i++)
      	{
					ee_parameter.software_version[i] = g_reception_buffer[i+10];
      	}
			}
		break;

		case 0x82:
			if(product_information.ID_factory_assigned == 0)
			{
				for(i=0;i<6;i++)
      	{
					ee_parameter.hardware_version[i] = g_reception_buffer[i+10];
      	}
      	configuration_answer_frame(0x82);
			}
		break;

		case 0x83:
			switch(state.main_state)
			{		
				case STATE_PROGRAMMING_DURING:
					strncpy(&temp_variable.configurators,&g_reception_buffer[10],7);
          //temp_variable.configurators[0] =
					flag_configurator = configuration_checking(&temp_variable.configurators);
					if(flag_configurator)
					{
						flags.virtul_configuration_right = 1;
						strncpy(buffer_tx,"D200013483000000",17);
						strncpy(&buffer_tx[10],&temp_variable.configurators,7);
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
						strncpy(buffer_tx,"D20001348C0000AA",17);
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
					}
					else
					{
						flags.virtul_configuration_right = 0;
						strncpy(buffer_tx,"D2000134830000EE",17);
						send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
					}
          manual_reception_buffer_clear();
				break;

				default:break;
			}
		break;
		
		case 0x8B:
      if(state.main_state == STATE_PROGRAMMING_DURING)
				KO_setting_procedure();
		break;
		
		case 0x8C:
			configuration_procedure();
		break;

		case 0x8D:
			if(state.main_state == STATE_PROGRAMMING_DURING)
			{
      	if(GetBit(g_asc_reception_buffer[7],7) == 0)
      	{
      	  //parameter writing
					if(g_asc_reception_buffer[CHANNEL] == 0x01)
					{
						if(product_information.conf_type == NONE_CONFED)
      	  	{
      	    	KO_answer_frame();
      	  	}
						else
						{
							write_parameter_resutl = write_KO(g_asc_reception_buffer[6],g_asc_reception_buffer[5]);
							if(write_parameter_resutl == OK)
							{
								flags.parameter_write_right = 1;
							}
							else
							{
								flags.parameter_setting_wrong = 1;
							}
							parameter_setting_error_answer(write_parameter_resutl);
						}
					}
					else if(g_asc_reception_buffer[CHANNEL] >= 0x02 && g_asc_reception_buffer[CHANNEL] <= 0x11)
					{
						if(ee_scenario[g_asc_reception_buffer[CHANNEL] - 2].confed == 0 && flags.scenario_scs_confed == 0)
						{
							KO_answer_frame();
						}
						else
						{
							write_parameter_resutl = write_parameter_scenario();
							parameter_setting_error_answer(write_parameter_resutl);
						}
					}
      	  else
      	  {
      	    parameter_setting_error_answer(write_parameter_resutl);
      	  }
				}
      	else
      	{
      	  //address writing
      	  if(g_asc_reception_buffer[CHANNEL] == 0x81)
      	  {
      	    if(product_information.conf_type != NONE_CONFED)
      	    {
							if( flags_muti_step.cen_system_step == 1 || product_information.cen_system )
							{
      	      	if(g_asc_reception_buffer[BYTE1] == 0x10)
      	      	{
      	        	if(g_asc_reception_buffer[BYTE2] >= 1 && g_asc_reception_buffer[BYTE2] <= 0xAF)
      	        	{
      	          	temp_product_information = product_information;
      	          	temp_product_information.conf_type = ADVANCED;
      	          	temp_product_information.cen_system = 1;
      	          	temp_product_information.local_A = g_reception_buffer[12];
      	          	temp_product_information.local_PL = g_reception_buffer[13];
      	          	flags_muti_step.cen_system_step = 2;
      	          	flags.KO_conf_right = 1;
      	        	}
      	        	else
      	        	{
      	          	address_setting_error_frame();
      	          	if(flags_muti_step.cen_system_step == 1)
      	            	flags_muti_step.cen_system_step = CONF_WRONG;
      	        	}
      	      	}
      	    	}
							else
							{
								address_setting_error_frame();
							}
						}
      	    else if(product_information.conf_type == NONE_CONFED)
      	    {
      	      address_setting_error_frame();
      	    }
      	  }
      	  else
      	  {
      	    address_setting_error_frame();
      	  }
      	
      	}
			}
		break;

		default:break;
	}
}

void configuration_answer_frame(unsigned char value)
{
	unsigned char buffer_tx[17] = "D200013480000000";
	unsigned char asc_buffer_tx[8];

	unsigned char i;
	unsigned char buffer[3];
	
	for(i=0;i<8;i++)
	{
		buffer[0] = buffer_tx[i * 2];
		buffer[1] = buffer_tx[i * 2 + 1];
		buffer[2] = 0;
		asc_buffer_tx[i] = StrToChar(buffer);
	}

	if(value == 0x10 && GetBit(g_asc_reception_buffer[5],4) == 0)
	{
		strncpy(buffer_tx,"D200013410100000",17);
		KO_conf.DayLightLevLux[0] = DLL.calc_level&0x00FF;		//  low byte
		KO_conf.DayLightLevLux[1] = DLL.calc_level>>8;				//  higt byte
		CharToStr(DLL.calc_level&0x00FF,buffer);
		buffer_tx[14] = buffer[0];
		buffer_tx[15] = buffer[1];
		CharToStr(DLL.calc_level>>8,buffer);
		buffer_tx[12] = buffer[0];
		buffer_tx[13] = buffer[1];
		send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x15)
	{
		strncpy(buffer_tx,"D200013415000000",17);
		CharToStr(KO_conf.PirSens,buffer);
		buffer_tx[14] = buffer[0];
		buffer_tx[15] = buffer[1];
		send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x16)
	{
		strncpy(buffer_tx,"D200013416000000",17);
		CharToStr(KO_conf.Hours,buffer);
		buffer_tx[10] = buffer[0];
		buffer_tx[11] = buffer[1];
		CharToStr(KO_conf.Minutes,buffer);
		buffer_tx[12] = buffer[0];
		buffer_tx[13] = buffer[1];
		CharToStr(KO_conf.Seconds,buffer);
		buffer_tx[14] = buffer[0];
		buffer_tx[15] = buffer[1];
		send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x80)
	{
			buffer_tx[9] = '0';
			for(i=0;i<6;i++)
      {
        buffer_tx[10+i] = ee_parameter.device_modle[i];
      }
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x81)
	{
			buffer_tx[9] = '1';
			for(i=0;i<6;i++)
      {
				buffer_tx[10+i] = ee_parameter.software_version[i];
      }
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x82)
	{
			buffer_tx[9] = '2';
			for(i=0;i<6;i++)
      {
				buffer_tx[10+i] = ee_parameter.hardware_version[i];
      }
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x83)
	{
      buffer_tx[9] = '3';
			buffer_tx[10] = Configurators.A;
			buffer_tx[11] = Configurators.PL;
			buffer_tx[12] = Configurators.M;
			buffer_tx[13] = Configurators.S;
			buffer_tx[14] = Configurators.T;
			buffer_tx[15] = '0';
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      //send_frame_pp_ext_broad("D200013483000000",TRANS_DELAY);
	}
	else if(value == 0x84)
	{
			strncpy(&buffer_tx[8],"FFFFFFFF",9);
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x85)
	{
		//strncpy(&buffer_tx[0],"$24\r",5);
		buffer_tx[0] = '$';
		buffer_tx[1] = '2';
		buffer_tx[2] = '4';
		buffer_tx[3] = 0x0D;
		buffer_tx[4] = 0;
		put_s(buffer_tx);
			//delay_ms(100);
			/*
			for(i=0;i<DEEP;i++)
			{
				if(scs_frame[i].finished == 1)
				{
					scs_frame[i].finished = 0;
					if((scs_frame[i].byte[1] == '2') && ((scs_frame[i].byte[2] == '5')))
					{
						strncpy(&buffer_tx[10],&scs_frame[i].byte[3],7);
						break;
					}
				}
			}
			buffer_tx[9] = '5';
			//strncpy(&buffer_tx[10],&g_reception_SCS.pipe[2],7);
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			*/
			
	}
	else if(value == 0x86)
	{
			SetBit(asc_buffer_tx[7],0);		//not busy
			SetBit(asc_buffer_tx[7],1);	  //hardware failure
			SetBit(asc_buffer_tx[7],2);		//wrong configuration
			SetBit(asc_buffer_tx[7],3);		//system failure
	
			SetBit(asc_buffer_tx[7],5);			//device not disabled
			SetBit(asc_buffer_tx[7],6);			//ID right
			
			if( product_information.conf_type == BASIC_PHYSICAL )
			{
        SetBit(asc_buffer_tx[7],4);
				SetBit(asc_buffer_tx[7],7);
			}
			else if(product_information.conf_type == BASIC_VIRTUAL)
			{
				ClrBit(asc_buffer_tx[7],4);
        SetBit(asc_buffer_tx[7],7);
			}
      else if(product_information.conf_type == ADVANCED)
      {
        ClrBit(asc_buffer_tx[7],4);
        ClrBit(asc_buffer_tx[7],7);
      }

			buffer_tx[9] = '6';
			buffer_tx[10] = 'F';
			buffer_tx[11] = 'F';
			buffer_tx[12] = 'F';
			buffer_tx[13] = 'F';
      CharToStr(asc_buffer_tx[7],buffer);
			buffer_tx[14] = buffer[0];
			buffer_tx[15] = buffer[1];
      asm("nop");

			//buffer_tx[15] = '1';		//manual		
			//buffer_tx[14] = '6';
			//buffer_tx[15] = 'F';	
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x88)
	{
			//strncpy(&buffer_tx[9],"8000000",8);
			//send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
  else if(value == 0x89)
  {
    SetBit(asc_buffer_tx[7],0);		//not busy
			SetBit(asc_buffer_tx[7],1);	  //hardware failure
			SetBit(asc_buffer_tx[7],2);		//wrong configuration
			SetBit(asc_buffer_tx[7],3);		//system failure
	
			SetBit(asc_buffer_tx[7],5);			//device not disabled
			SetBit(asc_buffer_tx[7],6);			//ID right
			
			if( product_information.conf_type == BASIC_PHYSICAL )
			{
        SetBit(asc_buffer_tx[7],4);
				SetBit(asc_buffer_tx[7],7);
			}
			else if(product_information.conf_type == BASIC_VIRTUAL)
			{
				ClrBit(asc_buffer_tx[7],4);
        SetBit(asc_buffer_tx[7],7);
			}
      else if(product_information.conf_type == ADVANCED)
      {
        ClrBit(asc_buffer_tx[7],4);
        ClrBit(asc_buffer_tx[7],7);
      }

			buffer_tx[9] = '9';
			buffer_tx[10] = 'F';
			buffer_tx[11] = 'F';
			buffer_tx[12] = 'F';
			buffer_tx[13] = 'F';
      CharToStr(asc_buffer_tx[7],buffer);
			buffer_tx[14] = buffer[0];
			buffer_tx[15] = buffer[1];
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }
	else if(value == 0x8B)
	{
    if(GetBit(g_asc_reception_buffer[5],1) == 0)    //every device
    {
		  KO_answer_frame();
    }
    else //device in programming/test state
    {
      if(state.main_state == STATE_PROGRAMMING_DURING || state.main_state == STATE_TEST_DURING)
      {
        KO_answer_frame();
      }
    }
	}
	else if(value == 0x8C)
	{
			strncpy(&buffer_tx[9],"C0000AA",8);
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	}
	else if(value == 0x8D)
	{
			if(GetBit(g_asc_reception_buffer[7],7)) //address answer
			{
        if(GetBit(g_asc_reception_buffer[5],1))
        {
          if(state.main_state == STATE_PROGRAMMING_DURING || state.main_state == STATE_TEST_DURING)
          {
            address_answer_frame();
          }
        }
        else
        {
          address_answer_frame();
        }
      }
			else //parameter request
			{
				parameter_answer_frame();
			}
	}
}

void configuration_receive_answer_frame(void)
{
	switch(g_asc_reception_buffer[4])
	{
		case 0x80:
      state.main_state = STATE_NORMAL;
			led_blinking_normal();
			if(state.main_state == STATE_TEST_DURING)
			{
				send_frame_pp_ext_broad("D20001348C0001FA",TRANS_DELAY);
			}
      else if(state.main_state == STATE_PROGRAMMING_DURING)
      {
        send_frame_pp_ext_broad("D20001348C0000FA",TRANS_DELAY);
      }
		break;
		
		case 0x0D:
		  if(((KO_conf.AddressType ==2)&&(KO_conf.Reference == g_asc_reception_buffer[1]))
					||((KO_conf.AddressType ==0)&&(KO_conf.DesAdd == g_asc_reception_buffer[1])))
			{
				//if(Time_delay.regulation.time_out == 1)
				//{
				//	Time_delay.regulation.time_out = 0;
				//	DLL.start_regulation = 0;
				//	ClrBit(KO_conf.status[0],Status_Regulationing);
				//}
				if((g_asc_reception_buffer[5] ==0x00)||(g_asc_reception_buffer[5] ==0x01))	
				{
						if(g_asc_reception_buffer[5] == 0x00)
						{
							Sensor_mode.power_on_flag = 1;
							KO_conf.status[1] = g_asc_reception_buffer[6];		//reyno 0616
						}
						else
						{
							Sensor_mode.power_on_flag = 0;
							KO_conf.status[1] = Status_OFF;		//reyno 0616
						}
						///////////////////////////////////////////////
				}
				if(g_asc_reception_buffer[5] == 0x0D)							
				{
					//reyno 0612/////////////////////////////////////
					Sensor_mode.power_on_flag = 1;
					KO_conf.status[1] = g_asc_reception_buffer[6];
					/////////////////////////////////////////////////
					SCS_received.P2P_dimmer_flag = 1;
					SCS_received.P2P_actuator_flag = 0;
				}
			}
		break;

		default:break;
	}
}

void KO_answer_frame(void)
{
  unsigned char i;
  unsigned char temp;
  volatile unsigned char buffer_tx[17];
  unsigned char buffer[3];
  unsigned char ko_channel = g_asc_reception_buffer[7];

  ClrBit(ko_channel,7);

	strncpy(buffer_tx,"D20001348B020381",17);
  if(ko_channel > NUM_KO_TOTAL)
  {
    buffer_tx[10] = 'F';
    buffer_tx[11] = 'F';
    buffer_tx[12] = '0';
    buffer_tx[13] = '4';
    temp = g_asc_reception_buffer[7];
    SetBit(temp,7);
    CharToStr(temp,buffer);
    buffer_tx[14] = buffer[0];
    buffer_tx[15] = buffer[1];
    send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }
  else
  {
    //if( GetBit(g_asc_reception_buffer[7],7) == 0 )
		//{
			if(ko_channel == 0x00)
			{
				strncpy(buffer_tx,"D20001348B020381",17);
        buffer_tx[10] = KO[0];
        buffer_tx[11] = KO[1];
        buffer_tx[12] = KO[2];
        buffer_tx[13] = KO[3];
				if( product_information.conf_type == 3 )
				{
					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				}
				else
				{
					strncpy(&buffer_tx[14],"01",3);
					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				}

				strncpy(buffer_tx,"D20001348B01AF02",17);
        temp = 0;
				for(i=0;i<16;i++)
				{
					temp = 0x02 + i;
					
					if( ee_scenario[i].confed == 0)             //
					{																																		//
						SetBit(temp,7);																										//
					}																																		//
					else																																/////////////////
					{																																		/////////////////
						ClrBit(temp,7);																										/////////////////
					}																																		
					
					CharToStr(temp,buffer);
					buffer_tx[14] = buffer[0];
					buffer_tx[15] = buffer[1];
/*
					/////////////////////////////////////////////////////////////////////////////////////
					//             For solve the bug that interface always lost the first frame        //
					if((temp == 0x02) || (temp == 0x82))																										/////////////////
					{																																		/////////////////
						if( ee_scenario[i].confed  == 0)						/////////////////
							send_frame_pp_ext_broad("D20001348B01AF82",KO_SCENARIO_TRANS_DELAY);				/////////////////
						else																															/////////////////
							send_frame_pp_ext_broad("D20001348B01AF02",KO_SCENARIO_TRANS_DELAY);				/////////////////
					}																																		/////////////////
					/////////////////////////////////////////////////////////////////////////////////////
*/

					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);	
          //frame_buffer_clear();
          manual_reception_buffer_clear();
				}
			}
			else
			{
				if(ko_channel == 0x01)
				{
					strncpy(buffer_tx,"D20001348B000000",17);
          buffer_tx[10] = KO[0];
          buffer_tx[11] = KO[1];
          buffer_tx[12] = KO[2];
          buffer_tx[13] = KO[3];
					if( product_information.conf_type == 3 )
					{
						buffer_tx[14] = '8';
            buffer_tx[15] = '1';
					}
					else
					{
						buffer_tx[14] = '0';
            buffer_tx[15] = '1';
					}
          send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				}
        else
        {
        if((ko_channel >= 2) && (ko_channel <= 17))
				{
					strncpy(buffer_tx,"D20001348B01AF02",17);
					temp = ko_channel - 2;
					if( ee_scenario[temp].confed  == 0)
					{						
						SetBit(temp,7);
					}
					else
					{
						ClrBit(temp,7);
					}
          temp += 2;
					CharToStr(temp,buffer);
					buffer_tx[14] = buffer[0];
					buffer_tx[15] = buffer[1];
					//if(i == 2)
					//{
						//send_frame_pp_ext_broad(buffer_tx,0);
					//}
					send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
				}
        else
        {
          buffer_tx[10] = 'F';
          buffer_tx[11] = 'F';
          buffer_tx[12] = '0';
          buffer_tx[13] = '4';
          temp = g_asc_reception_buffer[7];
          SetBit(temp,7);
          CharToStr(temp,buffer);
          buffer_tx[14] = buffer[0];
          buffer_tx[15] = buffer[1];
          send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
        }
        }
        //delay_ms(50);
        //manual_reception_buffer_clear();
        asm("nop");
			}
		//}
  }
}

void parameter_answer_frame(void)
{
	if(GetBit(g_asc_reception_buffer[5],1)) //ask for the programming or test state answer
	{
		if(state.main_state == STATE_TEST_DURING || state.main_state == STATE_PROGRAMMING_DURING)
		{
			if(g_asc_reception_buffer[7] == 0x00) //every key object
			{
	      parameter_all_answer();
	    }
			else if(g_asc_reception_buffer[7] <= NUM_KO_TOTAL)
			{
				parameter_specified_index_answer();
			}
		}
	}
	else
	{
		if(g_asc_reception_buffer[7] == 0x00) //every key object
		{
	    parameter_all_answer();
	  }
		else if(g_asc_reception_buffer[7] <= NUM_KO_TOTAL)
		{
			parameter_specified_index_answer();
		}
	}
}

void frame_buffer_clear(void)
{
  for(unsigned char i=0;i<DEEP;i++)
	{
		scs_frame[i].finished = 0;
    for(unsigned char j=0;j<NUMBER_BYTE_SCS;j++)
    {
      scs_frame[i].byte[j] = 0;
    }
	}
}

void parameter_request_error_frame(void)
{
	unsigned char buffer_tx[17] = "D20001348D000000";
		
		buffer_tx[10] = g_reception_buffer[12];
  	buffer_tx[11] = g_reception_buffer[13];
  	buffer_tx[12] = 'F';
  	buffer_tx[13] = 'F';
  	buffer_tx[14] = g_reception_buffer[14];
  	buffer_tx[15] = g_reception_buffer[15];
  	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);	
}

void not_allowed_response(unsigned char ko_channel)
{
	unsigned char buffer_tx[17] = "D20001348D000000";
  unsigned char buffer[3];
  unsigned char temp;
  	
  if(ko_channel == 0x01)
  {
  	buffer_tx[9] = 'B';
    buffer_tx[10] = KO[0];
    buffer_tx[11] = KO[1];
    buffer_tx[12] = KO[2];
    buffer_tx[13] = KO[3];
    buffer_tx[14] = '8';
    buffer_tx[15] = '1';
    send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }
  else if(ko_channel <= NUM_KO_TOTAL)
  {
		buffer_tx[9] = 'B';
  	buffer_tx[10] = '0';
  	buffer_tx[11] = '1';
  	buffer_tx[12] = 'A';
    buffer_tx[13] = 'F';
    temp = ko_channel;
    SetBit(temp,7);
    CharToStr(temp,buffer);
    buffer_tx[14] = buffer[0];
    buffer_tx[15] = buffer[1];
    send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }
}

void parameter_all_answer(void)
{
	unsigned char buffer_tx[17] = "D20001348D000000";
  unsigned char buffer[3];
	unsigned char i;

				if(GetBit(g_asc_reception_buffer[5],2))
	      {
	        if(g_asc_reception_buffer[6] == 0x00)
	        {
	          //every managered parameter answer      eg: D2 00 01 43 8D 04 00 00
	          if(product_information.conf_type == 0x03)
	          {
	          	not_allowed_response(0x01);	
	          }
	          else
	         	{
	          	for(i=1;i<35;i++)
	          	{
                if(read_KO(i) != 0xFFFF)
                {
	                CharToStr(read_KO(i),buffer);
	                buffer_tx[10] = buffer[0];
	                buffer_tx[11] = buffer[1];
	
	                CharToStr(i,buffer);
	                buffer_tx[12] = buffer[0];
	                buffer_tx[13] = buffer[1];
	
	                buffer_tx[14] = '0';
	                buffer_tx[15] = '1';
	                send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
									
									//if(++temp==3)
										//send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
                }
	          	}
              frame_buffer_clear();
	        	}	
	
	          for(i=0;i<16;i++)
	          {
	          	if(ee_scenario[i].confed)
	          	{
	                CharToStr(i+2,buffer);
	                buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
	
	                //parameter scenario number
	                CharToStr(ee_scenario[i].ns_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '0';
									buffer_tx[13] = '1';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter regutation type
									CharToStr(ee_scenario[i].reg_type,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '0';
									buffer_tx[13] = '3';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter ID1
									CharToStr(ee_scenario[i].id[0],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '4';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							    //parameter ID2
									CharToStr(ee_scenario[i].id[1],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '5';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter ID3
									CharToStr(ee_scenario[i].id[2]>>4,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '6';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter unit number
									CharToStr(ee_scenario[i].key_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '7';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							}
							else
							{
								not_allowed_response(i+2);	
							}
	          }

	          frame_buffer_clear();
	        }
	      }
	      else
	      {
	        if(g_asc_reception_buffer[6] <= 0xCF || (g_asc_reception_buffer[6] >= 0xF0 && g_asc_reception_buffer[6] <= 0xF9))
	        {
	          //every managered key object answer the specified parameter
	          //eg: D2 00 01 43 8D 00 01 00
	          if(product_information.conf_type == 0x03)
	          {
	          	not_allowed_response(0x01);	
	          }
	          else if(g_asc_reception_buffer[6] < 35 )
	          {
							if(read_KO(i) != 0xFFFF)
							{	
	            	CharToStr(read_KO(g_asc_reception_buffer[6]),buffer);
	            	buffer_tx[10] = buffer[0];
	            	buffer_tx[11] = buffer[1];
	
								CharToStr(i,buffer);
								buffer_tx[12] = buffer[0];
	            	buffer_tx[13] = buffer[1];
	            	//buffer_tx[12] = g_reception_buffer[12];
	            	//buffer_tx[13] = g_reception_buffer[13];
	
	            	buffer_tx[14] = '0';
	            	buffer_tx[15] = '1';
	            	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							}
	          }
	
	          for(i=0;i<16;i++)
	          {
	            if(ee_scenario[i].confed == 0x00)
	            {
	              not_allowed_response(i+2);	
	            }
	            else
	            {
	            switch(g_asc_reception_buffer[6])
	            {
	              case 1: //D2 00 01 43 8D 00 01 02
									CharToStr(ee_scenario[i].ns_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '0';
									buffer_tx[13] = '1';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
							  case 3:
									CharToStr(ee_scenario[i].reg_type,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '0';
									buffer_tx[13] = '3';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
							  case 20:
									CharToStr(ee_scenario[i].id[0],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '1';
									buffer_tx[13] = '4';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
	              case 21:
									CharToStr(ee_scenario[i].id[1],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '1';
									buffer_tx[13] = '5';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              case 22:
									CharToStr(ee_scenario[i].id[2],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '1';
									buffer_tx[13] = '6';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              case 23:
									CharToStr(ee_scenario[i].key_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = '1';
									buffer_tx[13] = '7';
	
	                CharToStr(i+2,buffer);
									buffer_tx[14] = buffer[0];
									buffer_tx[15] = buffer[1];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              default: break;
						  }
	            }
	          }
            frame_buffer_clear();
            manual_reception_buffer_clear();
	        }
	      }	
}

void parameter_specified_index_answer(void)
{
	unsigned char buffer_tx[17] = "D20001348D000000";
  unsigned char buffer[3];
  unsigned char temp;
	unsigned char i;
	
			if(GetBit(g_asc_reception_buffer[5],2) == 0)
	    {
	      if(g_asc_reception_buffer[6] <= 0xCF)
	      {
	        if(g_asc_reception_buffer[7] == 0x01)   // key object 1
	        {
	        	if(product_information.conf_type == 3)
	        	{
	        		buffer_tx[9] = 'B';
	        		buffer_tx[10] = KO[0];
	        		buffer_tx[11] = KO[1];
	        		buffer_tx[12] = KO[2];
	        		buffer_tx[13] = KO[3];
	        		buffer_tx[14] = '0';
	        		buffer_tx[15] = '1';
	        		send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	        	}
	        	else if(g_asc_reception_buffer[6] <= 34)
	          {
	            CharToStr(read_KO(g_asc_reception_buffer[6]),buffer);
	            buffer_tx[10] = buffer[0];
	            buffer_tx[11] = buffer[1];
	
	            buffer_tx[12] = g_reception_buffer[12];
	            buffer_tx[13] = g_reception_buffer[13];
	
	            buffer_tx[14] = '0';
	            buffer_tx[15] = '1';
	            send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	          }
	          else //answer 8D request error frame
	         	{
	         		parameter_request_error_frame();
	         	}
	        }
	        else
	        {
	          if(g_asc_reception_buffer[7] >= 2 && g_asc_reception_buffer[7] <= NUM_KO_TOTAL)
	          {
	          	if(ee_scenario[g_asc_reception_buffer[7] - 2].confed == 0)
	          	{
	          		buffer_tx[9] = 'B';
	        			buffer_tx[10] = '0';
	        			buffer_tx[11] = '1';
	        			buffer_tx[12] = 'A';
	        			buffer_tx[13] = 'F';
	        			temp = g_asc_reception_buffer[7];
	        			SetBit(temp,7);
	        			CharToStr(temp,buffer);
	        			buffer_tx[14] = buffer[0];
	        			buffer_tx[15] = buffer[1];
	        			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	          	}
	          	else
	          	{
	             	switch(g_asc_reception_buffer[6])
	            	{
	              case 1: //D2 00 01 43 8D 00 01 02
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].ns_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
							  case 3:
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].reg_type,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
							  case 20:
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[0],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							  break;
	
	              case 21:
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[1],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              case 22:
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[2]>>4,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              case 23:
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].key_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
	
									buffer_tx[12] = g_reception_buffer[12];
									buffer_tx[13] = g_reception_buffer[13];
	
									buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	              break;
	
	              default:
	              	not_allowed_response(g_asc_reception_buffer[7]);
	              break;
						  }
						}
	          }
	        }
	      }
	      else if(g_asc_reception_buffer[6] >= 0xFA && g_asc_reception_buffer[6] <= 0xF9) //for updated
	      {
	
	      }
	      else
	      {
	       	not_allowed_response(g_asc_reception_buffer[7]);
	      }
	    }
	    else //every managed parameter
	    {
	      if(g_asc_reception_buffer[6] == 0x00)   //every parameter accord to the specified key object number
	      {
	        if(g_asc_reception_buffer[7] == 0x01) //main key object   D2 00 01 43 8D 04 00 01
	        {
            if(product_information.conf_type == NONE_CONFED)
            {
              KO_answer_frame();
            }
            else
            {
							temp = 0;
	            for(i=1;i<35;i++)
	            {
                if(read_KO(i) != 0xFFFF)
                {
	                CharToStr(read_KO(i),buffer);
	                buffer_tx[10] = buffer[0];
	                buffer_tx[11] = buffer[1];

	                CharToStr(i,buffer);
	                buffer_tx[12] = buffer[0];
	                buffer_tx[13] = buffer[1];
	            		
	                buffer_tx[14] = '0';
	                buffer_tx[15] = '1';
	                send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
                }
	            }
            }
            frame_buffer_clear();
	        }
	        else if(g_asc_reception_buffer[7] >= 2 && g_asc_reception_buffer[7] <= NUM_KO_TOTAL) // 16 IR scenario answer Eg: D2 00 01 43 8D 04 00 02
	        {
            if(ee_scenario[g_asc_reception_buffer[7] - 2].confed == 0)
            {
              KO_answer_frame();
            }
            else
            {
	                buffer_tx[14] = g_reception_buffer[14];
									buffer_tx[15] = g_reception_buffer[15];
	
	                //parameter scenario number
	                CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].ns_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '0';
									buffer_tx[13] = '1';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter regutation type
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].reg_type,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '0';
									buffer_tx[13] = '3';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter ID1
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[0],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '4';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
							    //parameter ID2
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[1],buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '5';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter ID3
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].id[2]>>4,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '6';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	                //parameter unit number
									CharToStr(ee_scenario[g_asc_reception_buffer[7] - 2].key_number,buffer);
									buffer_tx[10] = buffer[0];
									buffer_tx[11] = buffer[1];
									buffer_tx[12] = '1';
									buffer_tx[13] = '7';
									send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
	
	                frame_buffer_clear();
            }
	        }
	      }
	      else // not allowed frame
	     	{
	     		not_allowed_response(g_asc_reception_buffer[7]);
	     	}
	    }	
}

void send_aux_frame(unsigned char argument,unsigned char ns,unsigned char scenario_index)
{
  unsigned char buffer_short[9] = "B1009300";
  unsigned char buffer[3];
  signed char temp;

  CharToStr(ns,buffer);
  buffer_short[2] = buffer[0];
  buffer_short[3] = buffer[1];

  switch(argument)
  {
    case ON:
      buffer_short[4] = '9';
      buffer_short[5] = '3';
      buffer_short[6] = '6';
      buffer_short[7] = '4';
      send_frame_pp_broad(buffer_short,TRANS_DELAY);
    break;

    case OFF:
      buffer_short[4] = '9';
      buffer_short[5] = '4';
      buffer_short[6] = '0';
      buffer_short[7] = '0';
      send_frame_pp_broad(buffer_short,TRANS_DELAY);
    break;

    case DIM_STEP:
      temp = IR_reception.pipe[6];
      if(temp > 0)
      {
        buffer_short[4] = '9';
        buffer_short[5] = '5';
        buffer_short[6] = dimmer_convert(temp);
				if(scenario_index == OUT_RANGE)
        	buffer_short[7] = '0';
				else
				{
					CharToStr(ee_scenario[scenario_index].reg_type,buffer);
					buffer_short[7] = buffer[1];
				}
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
      else if(temp < 0)
      {
        temp = 0 - temp;
        buffer_short[4] = '9';
        buffer_short[5] = '6';
        buffer_short[6] = dimmer_convert(temp);
        if(scenario_index == OUT_RANGE)
        	buffer_short[7] = '0';
				else
				{
					CharToStr(ee_scenario[scenario_index].reg_type,buffer);
					buffer_short[7] = buffer[1];
				}
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
    break;

    case GO_TO_LEVEL_TIME:
      if(IR_reception.pipe[6] == 0)
      {
        buffer_short[4] = '9';
        buffer_short[5] = '4';
        buffer_short[6] = '0';
        buffer_short[7] = '0';
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
      else if(IR_reception.pipe[6] <= 0x64)
      {
        buffer_short[4] = '9';
        buffer_short[5] = '3';
        CharToStr(IR_reception.pipe[6],buffer);
        buffer_short[6] = buffer[0];
        buffer_short[7] = buffer[1];
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
      else
      {
        buffer_short[4] = '9';
        buffer_short[5] = '3';
        buffer_short[6] = '6';
        buffer_short[7] = '4';
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
    break;

    case ACTION:
      buffer_short[4] = '9';
      buffer_short[5] = '3';
      buffer_short[6] = '0';
      buffer_short[7] = '0';
      send_frame_pp_broad(buffer_short,TRANS_DELAY);
    break;
		
		case DIMMER_STOP:
			buffer_short[4] = '9';
      buffer_short[5] = '7';
			send_frame_pp_broad(buffer_short,TRANS_DELAY);
		break;

  default:break;
  }
}

void send_group_pnl_frame(unsigned char send_type,unsigned char GR, unsigned char cmd)
{
	unsigned char buffer_tx[17] = "D20001428C000940";
	unsigned char buffer[3];
	
	if(send_type == REQUEST)
	{
		buffer_tx[6] = '4';
		buffer_tx[7] = '3';
	}
	else if(send_type == SET)
	{
		buffer_tx[6] = '4';
		buffer_tx[7] = '2';
	}
	else
	{
		buffer_tx[6] = '3';
		buffer_tx[7] = '4';
	}
	
	CharToStr(GR,buffer);
	buffer_tx[10] = buffer[0];
	buffer_tx[11] = buffer[1];
	
	buffer_tx[15] = cmd;
	
	send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
}

void ko_answer_all(void)
{
  unsigned char temp;
  temp = g_asc_reception_buffer[7];
  g_asc_reception_buffer[7] = 0x00;
  KO_answer_frame();
  g_asc_reception_buffer[7] = temp;
}

void address_answer_frame(void)
{
  unsigned char buffer_tx[17] = "D20001348DFEFE00";
  unsigned char i;
  unsigned char temp;
	unsigned char channel_scenario;
  //ko_answer_all();
  if(g_asc_reception_buffer[7] == 0x80)
  {
    if(product_information.conf_type == NONE_CONFED)
    {
      ko_answer_all();
    }
    else
    {
      if(product_information.cen_system)
      {
        buffer_tx[10] = '1';
        buffer_tx[11] = '0';
        buffer_tx[12] = product_information.local_A;
        buffer_tx[13] = product_information.local_PL;
        buffer_tx[14] = '8';
        buffer_tx[15] = '1';
        send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      }
      else
      {
        buffer_tx[14] = '8';
        buffer_tx[15] = '1';
        send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      }

      temp = g_asc_reception_buffer[CHANNEL];
      for(i=0x02;i<=0x11;i++)
      {
        g_asc_reception_buffer[CHANNEL] = i;
        KO_answer_frame();
      }
      g_asc_reception_buffer[CHANNEL] = temp;
      frame_buffer_clear();
    }
  }
  else if(g_asc_reception_buffer[7] == 0x81)
  {
    if(product_information.conf_type == NONE_CONFED)
    {
      KO_answer_frame();
    }
    else if(product_information.cen_system == 1)
    {
      //for CEN system
      buffer_tx[10] = '1';
      buffer_tx[11] = '0';
      buffer_tx[12] = product_information.local_A;
      buffer_tx[13] = product_information.local_PL;
      buffer_tx[14] = g_reception_buffer[14];
      buffer_tx[15] = g_reception_buffer[15];
      send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
    }
    else
    {
      buffer_tx[14] = '8';
      buffer_tx[15] = '1';
      send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
    }
  }
  else if(g_asc_reception_buffer[7] <= 0x91 && g_asc_reception_buffer[7] >= 0x82)
  {
		channel_scenario = g_asc_reception_buffer[CHANNEL];
		ClrBit(channel_scenario,7);
		channel_scenario -= 2;
		if(ee_scenario[channel_scenario].confed)
		{
			buffer_tx[14] = g_reception_buffer[14];
			buffer_tx[15] = g_reception_buffer[15];
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		}
		else
		{
    	KO_answer_frame();
		}
    //CharToStr(g_asc_reception_buffer[7], buffer);
    //buffer_tx[14] = buffer[0];
    //buffer_tx[15] = buffer[1];
    //send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }
}

void address_setting_error_frame(void)
{
  unsigned char buffer_tx[17] = "D20001348DFEFE80";
  unsigned char i;
  unsigned char buffer[3];
  unsigned char temp;
  //ko_answer_all();
  if(g_asc_reception_buffer[7] == 0x80)
  {
    if(product_information.conf_type == NONE_CONFED)
    {
      ko_answer_all();
    }
    else
    {
      for(i=0x81;i<=0x91;i++)
      {
        CharToStr(i,buffer);
        buffer_tx[14] = buffer[0];
        buffer_tx[15] = buffer[1];
        send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      }
      frame_buffer_clear();
    }
  }
  else if(g_asc_reception_buffer[7] == 0x81)
  {
    if(product_information.cen_system == 1)
    {
      //for CEN system

      if(product_information.conf_type == NONE_CONFED)
      {
        KO_answer_frame();
      }
      else
      {
        buffer_tx[10] = 'F';
        buffer_tx[11] = 'F';
        buffer_tx[12] = 'F';
        buffer_tx[13] = 'E';
        buffer_tx[14] = '8';
        buffer_tx[15] = '1';
        send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      }
    }
    else
    {
      if(product_information.conf_type == NONE_CONFED)
      {
        KO_answer_frame();
      }
			else
			{
				buffer_tx[15] = '1';
				send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);  //ADDRESS NOT ACCEPTED
			}
      /*
      buffer_tx[8] = '8';
      buffer_tx[9] = 'B';
      buffer_tx[10] = KO[0];
      buffer_tx[11] = KO[1];
      buffer_tx[12] = KO[2];
      buffer_tx[13] = KO[3];
      buffer_tx[14] = '8';
      buffer_tx[15] = '1';
      send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
      */
    }
  }
  else if(g_asc_reception_buffer[7] <= 0x91 && g_asc_reception_buffer[7] >= 0x82)
  {
		temp = g_asc_reception_buffer[7];
    ClrBit(temp,7);
    temp -= 2;
		
		if(ee_scenario[temp].confed)
		{
			buffer_tx[14] = g_reception_buffer[14];
			buffer_tx[15] = g_reception_buffer[15];
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		}
		else
		{
    	buffer_tx[8] = '8';
    	buffer_tx[9] = 'B';
    	buffer_tx[10] = '0';
    	buffer_tx[11] = '1';
    	buffer_tx[12] = 'A';
    	buffer_tx[13] = 'F';
    	buffer_tx[14] = g_reception_buffer[14];
			buffer_tx[15] = g_reception_buffer[15];
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		}
  }
	
	flags.KO_conf_right = 0; //reyno 0625
}

unsigned char dimmer_convert(unsigned char data)
{
        if(data == 1)
        {
          return '0';
        }
        else if(data == 2)
        {
          return '1';
        }
        else if(data == 3)
        {
          return '2';
        }
        else if(data == 4)
        {
          return '3';
        }
        else if(data == 5)
        {
          return '4';
        }
        else if(data == 6)
        {
          return '5';
        }
        else if(data == 7 || data == 8)
        {
          return '6';
        }
        else
        {
          return '7';
        }
}

void send_group_frame(unsigned char argument)
{
  unsigned char buffer_short[9] = "B5001200";
  unsigned char buffer_tx[17] = "D20001428C000944";
  unsigned char buffer[3];
  signed char temp;

  CharToStr(KO_conf.GR,buffer);
  buffer_short[2] = buffer[0];
  buffer_short[3] = buffer[1];

  buffer_tx[10] = buffer[0];
  buffer_tx[11] = buffer[1];

  switch(argument)
  {
    case ON:
    if(KO_conf.GR != 0)
      send_frame_pp_broad(buffer_short,TRANS_DELAY);
    break;

    case OFF:
      if(KO_conf.GR != 0)
      {
        buffer_short[7] = '1';
        send_frame_pp_broad(buffer_short,TRANS_DELAY);
      }
    break;

    case DIM_STEP:
      if(KO_conf.GR != 0)
      {
        temp = IR_reception.pipe[6];
        if(temp > 0)
        {
          buffer_short[7] = '3';
          send_frame_pp_broad(buffer_short,TRANS_DELAY);
        }
        else if(temp < 0)
        {
          buffer_short[7] = '4';
          send_frame_pp_broad(buffer_short,TRANS_DELAY);
        }
      }
    break;

    case ERASE:
      send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
    break;

    default:break;
  }
}

unsigned int write_parameter_scenario(void)
{
	unsigned char channel = g_asc_reception_buffer[CHANNEL];
	ClrBit(channel,7);
	channel -= 2;
	
	switch(g_asc_reception_buffer[PAR_N])
	{
		case 1: //D2 00 01 43 8D 00 01 02
			if(g_asc_reception_buffer[PAR_V] >= 1)
			{
				ee_scenario[channel].ns_number = g_asc_reception_buffer[PAR_V];
			}
			else
			{
				return PAR_OUT_OF_RANGE;
			}
		break;
		
		case 3:
			if(g_asc_reception_buffer[PAR_V] >= 0 && g_asc_reception_buffer[PAR_V] <= 0x03)
			{
				ee_scenario[channel].reg_type = g_asc_reception_buffer[PAR_V];
			}
			else
			{
				return PAR_OUT_OF_RANGE;
			}
		break;
		
		case 20:
			ee_scenario[channel].id[0] = g_asc_reception_buffer[PAR_V];
		break;
		
		case 21:
			ee_scenario[channel].id[1] = g_asc_reception_buffer[PAR_V];
		break;
		
		case 22:
			if(g_asc_reception_buffer[PAR_V] >= 0 && g_asc_reception_buffer[PAR_V] <= 0x0F)
			{
				ee_scenario[channel].id[2] = g_asc_reception_buffer[PAR_V];
			}
			else
			{
				return PAR_OUT_OF_RANGE;
			}
		break;
		
		case 23:
			if(g_asc_reception_buffer[PAR_V] >= 0 && g_asc_reception_buffer[PAR_V] <= 0x0F)
			{
				ee_scenario[channel].key_number = g_asc_reception_buffer[PAR_V];
			}
			else
			{
				return PAR_OUT_OF_RANGE;
			}
		break;
		
		default:
			return PAR_NOT_IMPLEMENTED;
	}
  return 0;
}

void parameter_setting_error_answer(unsigned int value)
{
	unsigned char buffer_tx[17] = "D20001348D000000";
	unsigned char buffer[3];
	unsigned char channel = g_asc_reception_buffer[CHANNEL];
	unsigned char temp;

	ClrBit(channel,7);
	temp = channel;

  if(channel > 0x11)
  {
    buffer_tx[8] = '8';
		buffer_tx[9] = 'B';
    buffer_tx[10] = 'F';
    buffer_tx[11] = 'F';
    buffer_tx[12] = '0';
    buffer_tx[13] = '4';
    SetBit(temp,7);
    CharToStr(temp,buffer);
    buffer_tx[14] = buffer[0];
    buffer_tx[15] = buffer[1];
    send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
  }

	switch(value)
	{
		case PAR_NOT_IMPLEMENTED:
			buffer_tx[10] = g_reception_buffer[12];
			buffer_tx[11] = g_reception_buffer[13];
			buffer_tx[12] = 'F';
			buffer_tx[13] = 'F';
      if(channel == 0x01)
      {
        if(product_information.conf_type == NONE_CONFED)
        {
          buffer_tx[14] = '8';
          buffer_tx[15] = '1';
        }
        else
        {
          buffer_tx[14] = '0';
          buffer_tx[15] = '1';
        }
      }
      else
      {
				if(ee_scenario[channel-2].confed)
				{
					ClrBit(temp,7);
				}
				else
				{
					SetBit(temp,7);
				}
				CharToStr(temp,buffer);
				buffer_tx[14] = buffer[0];
        buffer_tx[15] = buffer[1];
      }
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			//flags.KO_conf_right = 0;
			flags.parameter_setting_wrong = 1;
		break;

		case PAR_OUT_OF_RANGE:
			buffer_tx[10] = g_reception_buffer[12];
			buffer_tx[11] = g_reception_buffer[13];
			buffer_tx[12] = 'F';
			buffer_tx[13] = 'E';
			if(channel == 0x01)
      {
        if(product_information.conf_type == NONE_CONFED)
        {
          buffer_tx[14] = '8';
          buffer_tx[15] = '1';
        }
        else
        {
          buffer_tx[14] = '0';
          buffer_tx[15] = '1';
        }
      }
      else
      {
				if(ee_scenario[channel-2].confed)
				{
					ClrBit(temp,7);
				}
				else
				{
					SetBit(temp,7);
				}
				CharToStr(temp,buffer);
				buffer_tx[14] = buffer[0];
        buffer_tx[15] = buffer[1];
      }
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
			//flags.KO_conf_right = 0;
			flags.parameter_setting_wrong = 1;
		break;

		default:break;
	}

}

void KO_setting_procedure(void)
{
  if(GetBit(g_asc_reception_buffer[CHANNEL],7))
	{
		if( g_asc_reception_buffer[CHANNEL] == 0x80 )
		{
      flags.KO_erase_all = 1;
		}
    else if(g_asc_reception_buffer[CHANNEL] == 0x81)
    {
      flags.KO_erase_main = 1;
    }
    else if(g_asc_reception_buffer[CHANNEL] >= 0x82 && g_asc_reception_buffer[CHANNEL] <= 0x91)
    {
      temp_variable.erase_KO_scenario = g_asc_reception_buffer[CHANNEL];
      ClrBit(temp_variable.erase_KO_scenario,7);
      temp_variable.erase_KO_scenario -= 2;
      flags.KO_erase_scenario = 1;
    }
	}
	else
  {
    if(g_asc_reception_buffer[CHANNEL] == 0x01)
    {
#ifdef NONE_CONFED_203
        if(g_asc_reception_buffer[5] == 0x00)
        {
          if(g_asc_reception_buffer[6] == 0xA8 || g_asc_reception_buffer[6] == 0xA6 || g_asc_reception_buffer[6] == 0x77
              || g_asc_reception_buffer[6] == 0x80 || g_asc_reception_buffer[6] == 0xA4 || g_asc_reception_buffer[6] == 0xA5)
          {
						if((product_information.conf_type != NONE_CONFED && flags.KO_erase_all == 0 && flags.KO_erase_main == 0) && (KO[2] != g_reception_buffer[12] || KO[3] != g_reception_buffer[13]))
						{
							KO_setting_error_frame(ASSIGNED_AGAIN,1);
						}
						else
						{
            	KO[0] = g_reception_buffer[10];
            	KO[1] = g_reception_buffer[11];
            	KO[2] = g_reception_buffer[12];
            	KO[3] = g_reception_buffer[13];
            	product_information.conf_type = ADVANCED;    //modified now
							if(g_asc_reception_buffer[6] == 0xA8 || g_asc_reception_buffer[6] == 0xA6 || g_asc_reception_buffer[6] == 0x77)
            	{
              	product_information.cen_system = 0;
								temp_product_information.cen_system = 0;
            	}
            	else
            	{
              	product_information.cen_system = 1;
								temp_product_information.cen_system = 1;
              	flags_muti_step.cen_system_step = 1;
            	}
							KO_parameter_initial_temp();
							flags.KO_conf_right = 1;
							flags.parameter_setting_wrong = 0;
							//delay_ms(100); //avoid to 3 times transfier from interface
							//frame_buffer_clear();
						}
          }
					else
					{
						KO_setting_error_frame(NOT_IMPLEMENTED,1);
					}
        }
				else
				{
					KO_setting_error_frame(NOT_IMPLEMENTED,1);
				}
#endif

#ifdef NONE_CONFED_204
      if(g_asc_reception_buffer[5] == 0x00)
      {
        switch(g_asc_reception_buffer[6])
        {
        case 0xA6:
          KO[0] = g_reception_buffer[10];
          KO[1] = g_reception_buffer[11];
          KO[2] = g_reception_buffer[12];
          KO[3] = g_reception_buffer[13];
          product_information.conf_type = 2;    //modified now
          flags.KO_conf_right = 1;
          break;

        case 0xA4:
          KO[0] = g_reception_buffer[10];
          KO[1] = g_reception_buffer[11];
          KO[2] = g_reception_buffer[12];
          KO[3] = g_reception_buffer[13];
          product_information.conf_type = 2;    //modified now
          flags.KO_conf_right = 1;
          break;

        default:break;
        }
      }
#endif

#ifdef NONE_CONFED_1FF
      if(g_asc_reception_buffer[5] == 0x00)
      {
        switch(g_asc_reception_buffer[6])
        {
        case 0x77:
          KO[0] = g_reception_buffer[10];
          KO[1] = g_reception_buffer[11];
          KO[2] = g_reception_buffer[12];
          KO[3] = g_reception_buffer[13];
          product_information.conf_type = 2;    //modified now
          flags.KO_conf_right = 1;
          break;

        case 0xA5:
          KO[0] = g_reception_buffer[10];
          KO[1] = g_reception_buffer[11];
          KO[2] = g_reception_buffer[12];
          KO[3] = g_reception_buffer[13];
          product_information.conf_type = 2;    //modified now
          flags.KO_conf_right = 1;
          break;

        case 0x70:
          KO[0] = g_reception_buffer[10];
          KO[1] = g_reception_buffer[11];
          KO[2] = g_reception_buffer[12];
          KO[3] = g_reception_buffer[13];
          product_information.conf_type = 2;    //modified now
          flags.KO_conf_right = 1;
          break;
        default:break;
        }
      }
#endif
    }
    else if(g_asc_reception_buffer[CHANNEL] >= 0x02 && g_asc_reception_buffer[CHANNEL] <= 0x11)
    {
      if(g_asc_reception_buffer[5] == 0x01 && g_asc_reception_buffer[6] == 0xAF)
      {
        temp_variable.conf_KO_scenario = g_asc_reception_buffer[CHANNEL];
        temp_variable.conf_KO_scenario -= 2;
        flags.scenario_scs_confed = 1;
      }
			else
			{
				KO_setting_error_frame(NOT_IMPLEMENTED,g_asc_reception_buffer[CHANNEL]);
			}
    }
		else
		{
			KO_setting_error_frame(OUT_KO,g_asc_reception_buffer[CHANNEL]);
		}
  }
}

void configuration_procedure(void)
{
  unsigned char i;
	unsigned char buffer[3];
	unsigned char buffer_tx[17];			// 20090216
	//static unsigned char data[7];
  unsigned char conf_right = 0xFF;
  //unsigned char flag_avoid_twice_wrong = 0;
  unsigned char flag_reset = 0;

  switch(g_asc_reception_buffer[6])
			{
				case 0x00:  //configuration set frame
					switch(g_asc_reception_buffer[7])
					{
						case 0x00: //start configuration
                key_result.short_pressed = 0;
                key_result.long_pressed = 0;
								state.main_state = STATE_PRE_PROGRAMMING;
						break;

						case 0xAA: //stop sending frame
							if(state.main_state == STATE_PROGRAMMING_DURING)
              {
								flags.AA_received = 1;
                if(flags.KO_conf_right)
                {
                  //flags.KO_conf_right = 0;
                  conf_right = 1;
                }
              }

							if(flags_muti_step.cen_system_step == 2 || flags.KO_erase_all || flags.KO_erase_main || flags.KO_erase_scenario || flags.scenario_scs_confed)
              {
                conf_right = 1;
              }
							else if(flags.parameter_write_right)
							{
								conf_right = 1;
							}

							if(flags_muti_step.cen_system_step == CONF_WRONG || flags.parameter_setting_wrong == 1)
              {
                conf_right = 0;
              }
							
              if(conf_right == 1)
                send_frame_pp_ext_broad("D20001348C0000AB",TRANS_DELAY);
              else if(conf_right == 0)
                send_frame_pp_ext_broad("D20001348C0000EE",TRANS_DELAY);

							flags.parameter_setting_wrong = 0;
							flags.parameter_write_right = 0;
						break;

						case 0xF0: //reset EEP configuration
              if(state.main_state == STATE_PROGRAMMING_DURING)
              {
							  factory_default();
							  system_reset();
              }
						break;

						case 0xFA: //configuration aborted
              if(state.main_state == STATE_PROGRAMMING_DURING || state.main_state == STATE_TEST_DURING)
              {
							  state.main_state = STATE_NORMAL;
                led_blinking_normal();
              }
						break;

						case 0xFF: //end of configuration
              if(flags.KO_erase_main && flags.KO_conf_right == 0)
              {
                flags.KO_erase_main = 0;
								if(flags.AA_received)
								{	
                	//load_default_parameter();
	              	//remember_parameter();
                	ee_KO[0] = flash_KO[0];
                	ee_KO[1] = flash_KO[1];
                	ee_KO[2] = flash_KO[2];
                	ee_KO[3] = flash_KO[3];
                	KO[0] = flash_KO[0];
                	KO[1] = flash_KO[1];
                	KO[2] = flash_KO[2];
                	KO[3] = flash_KO[3];
                	ee_product_information.cen_system = 0;
	              	ee_product_information.conf_type = NONE_CONFED;
                	product_information.cen_system = 0;
	              	product_information.conf_type = NONE_CONFED;

	              	ee_configurators.A = '0';
	              	ee_configurators.PL = '0';
	              	ee_configurators.M = '0';
	              	ee_configurators.S = '0';
	              	ee_configurators.T = '0';

                	Configurators.A = '0';
	             		Configurators.PL = '0';
	              	Configurators.M = '0';
	              	Configurators.S = '0';
	              	Configurators.T = '0';
                	//flag_reset = 1;
								}
              }

              if(flags.KO_conf_right)
              {
								if(flags.AA_received )
								{
									if(product_information.cen_system == 0)
									{
										ee_KO[0] = KO[0];
										ee_KO[1] = KO[1];
										ee_KO[2] = KO[2];
										ee_KO[3] = KO[3];
										//to avoid power up KO confdiguration
										ee_KO_last[0] = KO[0];
										ee_KO_last[1] = KO[1];
										ee_KO_last[2] = KO[2];
										ee_KO_last[3] = KO[3];
										//ee_KO_conf = KO_conf;  //2009 04 17
										KO_parameter_initial();
										//KO_conf = ee_KO_conf;
										ee_KO_conf = KO_conf;
										//ee_PnG_KO_conf = KO_conf;
										ee_variable.GR = KO_conf.GR;
										ee_variable.Reference = KO_conf.Reference;
										ee_flags.PnG_confed = 1;
										
										if(KO_conf.AddressType == PP)
										{
											CharToStr(KO_conf.DesAdd,buffer);
											ee_configurators.A = buffer[0];
											ee_configurators.PL = buffer[1];
										}
										
										ee_product_information = product_information;
									}
									else if(product_information.cen_system == 1)
									{
									  buffer[0] = temp_product_information.local_A;
										buffer[1] = temp_product_information.local_PL;
										unsigned char address = StrToChar(buffer);
										if(address > 0 && address <= 0xAF)
										{
											ee_KO[0] = KO[0];
											ee_KO[1] = KO[1];
											ee_KO[2] = KO[2];
											ee_KO[3] = KO[3];
	
											ee_KO_last[0] = KO[0];
											ee_KO_last[1] = KO[1];
											ee_KO_last[2] = KO[2];
											ee_KO_last[3] = KO[3];
	
											KO_parameter_initial();
											ee_KO_conf = KO_conf;
											
											ee_flags.PnG_confed = 1;
											ee_product_information = product_information;
										}
									}
								}
								flag_reset = 1;
              }
							else if(flags.parameter_write_right)
							{
								ee_KO_conf = KO_conf;
								flags.parameter_write_right = 0;
							}

              if(flags.KO_erase_all && flags.KO_conf_right == 0)
              {
								if(flags.AA_received)
                	factory_default();
                flag_reset = 1;
              }

              if( flags.scenario_scs_confed )
              {
                ee_scenario[temp_variable.conf_KO_scenario].confed = 1;
                //flag_reset = 1;
              }

              if(flags.KO_erase_scenario)
              {
                scenario_remove(temp_variable.erase_KO_scenario);
              }

              if(flags_muti_step.cen_system_step == 2)
              {
                remember_parameter();
                ee_product_information = temp_product_information;
                flag_reset = 1;
              }

              if(state.main_state == STATE_PROGRAMMING_DURING)
              {
							  if(flags.virtul_configuration_right)
							  {
								  state.main_state = STATE_NORMAL;
								  flags.virtul_configuration_right = 0;
                  ee_configurators.A = temp_variable.configurators[0];
									ee_configurators.PL = temp_variable.configurators[1];
									ee_configurators.M = temp_variable.configurators[2];
									ee_configurators.S = temp_variable.configurators[3];
									ee_configurators.T = temp_variable.configurators[4];

                  if(temp_variable.configurators[2] == '0' || temp_variable.configurators[2] == '1' || temp_variable.configurators[2] == '3' || temp_variable.configurators[2] == '4')
                  {
                    ee_KO_conf.DesAdd = StrToChar(&temp_variable.configurators[0]);
                  }
                  else if(temp_variable.configurators[2] == '2')
                  {
                    ee_KO_conf.DesAdd = StrToChar(&temp_variable.configurators[0]);
                    ee_product_information.local_A = temp_variable.configurators[0];
                    ee_product_information.local_PL = temp_variable.configurators[1];
                  }

									ee_product_information.conf_type = 0x01;
									ee_KO_conf.AddressType = 0;
									flag_reset = 1;
							  }
                /*
                else
                {
                  state.main_state = STATE_NORMAL;
                  remember_parameter();
                  led_blinking_normal();
                }
                */
              }

              if(flag_reset)
              {
                system_reset();
              }
              else if(state.main_state == STATE_PROGRAMMING_DURING || state.main_state == STATE_TEST_DURING)
              {
                state.main_state = STATE_NORMAL;
                product_information = ee_product_information;
                KO[0] = ee_KO[0];
                KO[1] = ee_KO[1];
                KO[2] = ee_KO[2];
                KO[3] = ee_KO[3];
                led_blinking_normal();
              }
						break;

						default:break;
					}
				break;
				
				case 0x01:  //test frame
					switch(g_asc_reception_buffer[7])
					{
            case 0x00:
							  state.main_state = STATE_PRE_PROGRAMMING;
						break;
						
						case 0xFA:
              if(state.main_state == STATE_TEST_DURING)
              {
                state.main_state = STATE_NORMAL;
							  led_blinking_normal();
              }
						break;

						case 0xFF:
							if(state.main_state == STATE_TEST_DURING)
              {
                state.main_state = STATE_NORMAL;
							  led_blinking_normal();
              }
						break;

						default:break;
					}
				break;

				case 0x09:	//PnL group frame
					switch(g_asc_reception_buffer[7])
					{
            //////////////////////////////////////
            //same as group assigned
            case 0x06: //group assign
              if( state.main_state == PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN )
              {
                flags.group_assigned = 1;
              }
            break;

						case 0x09:
							if(KO_conf.GR == g_asc_reception_buffer[5])
								send_group_pnl_frame(ANSWER,KO_conf.GR,GROUP_USED_REQUEST);
						break;
						
						case 0xF9:
							if(KO_conf.GR == g_asc_reception_buffer[5])
								send_group_pnl_frame(ANSWER,KO_conf.GR,GROUP_USED_REQUEST);
						break;
						
						case 0xF3:
							if(product_information.conf_type == ADVANCED && KO_conf.AddressType == GROUP)
							{
								KO_conf.Reference = g_asc_reception_buffer[5];
								ee_KO_conf.Reference = g_asc_reception_buffer[5];
							}
						break;
						
            case 0xF6:
              if( state.main_state == PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN )
              {
                flags.group_assigned = 1;
              }
						break;

            case 0x46:
              if( state.main_state == PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN )
              {
                flags.group_assigned = 1;
              }
						break;
            //            over               /////
            //////////////////////////////////////
						
						case 0x40: //start PnL
						case 0x00:	
							key_result.short_pressed = 0;
							
							if(state.main_state == PNL_AD_CONFED_STEP2 && state.pnl_slave == NORMAL)
							{
								if(g_asc_reception_buffer[5] != 0 && g_asc_reception_buffer[5] != KO_conf.GR)
								{
									state.main_state = NORMAL;
									led_blinking_normal();
								}
							}
							
							temp_variable.GR = g_asc_reception_buffer[5];
							if( flags.scs_pnl_group_sensor_starded == 0 )
							{
								if(g_asc_reception_buffer[5] != 0)
								{	
									//advance started
									if(KO_conf.AddressType == GROUP)
									{
										state.pnl_slave = START_PNL_GROUP_SENSOR;
										if(KO_conf.GR == temp_variable.GR)
										{
											led_blinking_ms(250,250,600000);
											state.pnl_slave = GR_EQUAL;
										}
										else if(KO_conf.GS1 == temp_variable.GR || KO_conf.GS2 == temp_variable.GR)
										{
											led_blinking_ms(250,250,600000);
											flags.wait_GS_remove = 1;
										}
										else
										{
											flags.wait_GS_remove = 0;
										}
									}
									
								}
								else
								{
									state.pnl_slave = START_PNL_NONE_CONFED_GROUP_SENSOR;
								}
							}
							flags.scs_pnl_group_sensor_starded = 1;
						break;

						case 0x41: //group confirmation
						break;

						case 0x42: //group refusing
						break;

						case 0x43: //referent transmission
						break;

						case 0x44: //group ereasing
							if(KO_conf.GR == g_asc_reception_buffer[5])
							{
								KO_conf.GS1 = 0;
								ee_KO_conf.GS1 = 0;
								KO_conf.GS2 = 0;
								ee_KO_conf.GS2 = 0;
							}
							else if(KO_conf.GS1 == g_asc_reception_buffer[5])
							{
								KO_conf.GS1 = 0;
								ee_KO_conf.GS1 = 0;
							}
							else if(KO_conf.GS2 == g_asc_reception_buffer[5])
							{
								KO_conf.GS2 = 0;
								ee_KO_conf.GS2 = 0;
							}
						break;

						case 0x45: //group request
						break;

						case 0x47:
							if(KO_conf.GS1 == g_asc_reception_buffer[5])
							{
								KO_conf.GS1 = 0;
								ee_KO_conf.GS1 = 0;
							}
							else if(KO_conf.GS2 == g_asc_reception_buffer[5])
							{
								KO_conf.GS2 = 0;
								ee_KO_conf.GS2 = 0;
							}
						break;

						case 0x48:
						break;

						case 0x49:
						break;

						case 0x4A: //disable load control
						break;

						case 0x0F:
						case 0x4F: //end PnL
							key_result.short_pressed = 0;
							state.main_state = NORMAL;
							state.pnl_slave = NORMAL;
							flags.scs_pnl_group_sensor_starded = 0;
							led_blinking_normal();
						break;

						default:break;
					}
				break;

				case 0x0A:  //PnL scenario frame
					switch(g_asc_reception_buffer[7])
					{
						case 0x00:
						break;

						case 0x05:
						break;

						case 0x06:
						break;

						case 0x07:
						break;

						case 0x08:
						break;

						case 0x09:
							for(i=0;i<16;i++)
							{
								if(g_asc_reception_buffer[5] == ee_scenario[i].ns_number)
								{	
									i = 16;
									strncpy(buffer_tx,"D20001348C000A09",17);
									CharToStr(KO_conf.DesAdd,buffer);
									buffer_tx[2] = buffer[0];
									buffer_tx[3] = buffer[1];
									buffer_tx[10] = g_reception_buffer[10];
									buffer_tx[11] = g_reception_buffer[11];
									send_frame_pp_ext_broad(buffer_tx,0);
									timer_flex_initial(3000);
								}
							}	
						break;

						case 0x0F:
						break;

						default:break;
					}
				break;
				
				case 0x0B:  //PnL IR scenario frame
				break;

				default:break;
			}
}

void aux_procedure(void)
{
  unsigned char i;
  if(g_asc_reception_buffer[3] == 0x08)
  {
    if(g_reception_buffer[9] == '1')
    {
      if(g_asc_reception_buffer[7] == 0x66)
      {
        for(i=0;i<16;i++)
        {
          if(ee_scenario[i].confed)
          {
            if(ee_scenario[i].ns_number == g_asc_reception_buffer[5])
            {
              scenario_remove(i);
              break;
            }
          }
        }
      }
    }
  }
}

void scenario_remove(unsigned char number)
{
  ee_scenario_index = 0;
  ee_scenario[number].ns_number = 0x01;
	ee_scenario[number].reg_type = 0x01;
	for(unsigned char i=0;i<3;i++)
	{
	  ee_scenario[number].id[i] = 0;
  }
  ee_scenario[number].key_number = 0;
  ee_scenario[number].confed = 0;
}

void KO_setting_error_frame(unsigned char send_type,unsigned char channel)
{
	unsigned char buffer_tx[17] = "D20001348BFF0201";
	unsigned char buffer[3];
	
	CharToStr(channel,buffer);
	buffer_tx[14] = buffer[0];
	buffer_tx[15] = buffer[1];
	
	switch(send_type)
	{
		case NOT_IMPLEMENTED:
			SetBit(channel,7);
			CharToStr(channel,buffer);
			buffer_tx[14] = buffer[0];
			buffer_tx[15] = buffer[1];
			buffer_tx[12] = '0';
			buffer_tx[13] = '0';
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case BUSY:
			buffer_tx[12] = '0';
			buffer_tx[13] = '1';
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case ASSIGNED_AGAIN:
			buffer_tx[12] = '0';
			buffer_tx[13] = '2';
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		case OUT_KO:
			SetBit(channel,7);
			CharToStr(channel,buffer);
			buffer_tx[14] = buffer[0];
			buffer_tx[15] = buffer[1];
			buffer_tx[12] = '0';
			buffer_tx[13] = '4';
			send_frame_pp_ext_broad(buffer_tx,TRANS_DELAY);
		break;
		
		default:break;
	}
}