/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// Configurators C1|C2 C3|C4 C5|C6
//							 0 |A  PL|M  S | T
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


#include <ioavr.h>
#include <inavr.h>
#include "moudle_SCS.h"
#include "global_variable.h"
#include "board.h"
#include "configuration.h"
#include "decode_scs_next.h"
#include "application.h"
#include "IR.h"
#include "usart.h"
#include "decode_SCS.h"

unsigned char configuration_read(void)
{
	unsigned char i;
#ifndef NO_CONFIGURATOR_HOUSING
		unsigned char current;
#endif
	manual_reception_buffer_clear();
	for(i=0;i<5;i++)
		g_configurator[i] = 0;		

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

	put_s("$2603\r");				//require configurators setting
	delay_ms(200);

	#ifdef NO_CONFIGURATOR_HOUSING											//have house
		for(i=0;i<5;i++)
		{
			g_configurator[i] = '0';
		}
		state.configuration_method = 1;
		ee_product_information.conf_type = 1;		//virtual configuration
		return 0;
	#else																								//no house
		for(i=0;i<DEEP;i++)
		{
			if((scs_frame[i].byte[1] == '2') && (scs_frame[i].byte[2] == '6'))
			{
				current = i;
				break;
			}
		}

		if(scs_frame[current].finished == 1)
		{
			if(scs_frame[current].byte[1] == '2' && scs_frame[current].byte[2] == '6')
			{
				for(i=0;i<5;i++)
				{
					g_configurator[i] = scs_frame[current].byte[i+4];
				}

				if(g_configurator[0] == g_configurator[1] == g_configurator[2] == g_configurator[3] == g_configurator[4] == '0')
        {
          ee_product_information.conf_type = 1;
        }
					//eeprom_write_byte_me (&ee_product_information.conf_type,1);		//virtual configuration

				state.configuration_method = 0;
				return 0;
			}
			state.configuration_method = 0;
			return 1;
		}
    return 1;
	#endif
}

unsigned char power_up_configuration(void)
{
	unsigned char buffer[3];
	unsigned char des_add;
	if( configuration_read() == 0 )
	{
		Configurators.A = g_configurator[0];
		Configurators.PL = g_configurator[1];
		Configurators.M = g_configurator[2];
		Configurators.S = g_configurator[3];
		Configurators.T = g_configurator[4];
		//load_default_parameter(&KO_conf);
		//load_parameter();
    buffer[0] = Configurators.A;
		buffer[1] = Configurators.PL;
		buffer[2] = 0;
		des_add = StrToChar(buffer);
		
		if((Configurators.A == '0') && (Configurators.PL == '0') && (Configurators.M == '0') && (Configurators.S == '0') && (Configurators.T == '0'))
		{
			if(ee_product_information.conf_type == 0)
			{
				ee_product_information.conf_type = 3;
			}
			return 0;
		}	
		else if( (Configurators.M >= '0') && (Configurators.M <= '4') )
		{
			if(Configurators.M == '0')
			{
				if((des_add >= 1 && des_add <= 0xAF) && (Configurators.S >= '0') && (Configurators.S <= '3') && (Configurators.T >= '0') && (Configurators.T <= '9'))
				{
					ee_product_information.conf_type = 0;		//basic PHY configuration
					ee_KO_conf.AddressType = 0;
					KO_conf.AddressType = 0;
					//load_default_parameter(&KO_conf);
					return 0;
				}
				else
					return 1;
			}
			else if(Configurators.M == '1')
			{
				if((des_add >= 1 && des_add <= 0xAF) && (Configurators.S == '0') && (Configurators.T == '0'))
				{
					ee_product_information.conf_type = 0;		//basic PHY configuration
					ee_KO_conf.AddressType = 0;
					KO_conf.AddressType = 0;
					return 0;
				}
				else
					return 1;
			}
			else if(Configurators.M == '2')
			{
				if((des_add >= 1 && des_add <= 0xAF) && ((Configurators.S >= '0') && (Configurators.S <= '3')) && ((Configurators.T >= '0') && (Configurators.T <= '9')))
				{
					ee_product_information.conf_type = 0;		//basic PHY configuration
					ee_KO_conf.AddressType = 0;
					KO_conf.AddressType = 0;
					return 0;
				}
				else
					return 1;
			}
			else if(Configurators.M == '3')
			{
				if((des_add >= 1 && des_add <= 0xAF) && (Configurators.S >= '0') && (Configurators.S <= '3') && (Configurators.T >= '0') && (Configurators.T <= '9'))
				{
					ee_product_information.conf_type = 0;		//basic PHY configuration
					ee_KO_conf.AddressType = 0;
					KO_conf.AddressType = 0;
					return 0;
				}
				else
					return 1;
			}
			else if(Configurators.M == '4')
			{
				if((des_add >= 1 && des_add <= 0xAF) && (Configurators.S == '0') && (Configurators.T  == '0'))
				{
					ee_product_information.conf_type = 0;		//basic PHY configuration
					ee_KO_conf.AddressType = 0;
					KO_conf.AddressType = 0;
					return 0;
				}
				else
					return 1;
			}
		}
		else
			return 1;
	}
	else
		return 1;

  return 0;
}


//extern struct SKO_Configuration ee_KO_conf __attribute__((section(".eeprom")));
void remember_parameter()
{
	unsigned char i;
	for(i=0;i<35;i++)
	{
		write_KO(i,read_KO(i));
	}
  ee_KO[0] = KO[0];
  ee_KO[1] = KO[1];
  ee_KO[2] = KO[2];
  ee_KO[3] = KO[3];
  ee_KO_conf = KO_conf;
  ee_configurators = Configurators;
  ee_product_information = product_information;
}

void load_parameter()
{
  unsigned char buffer[3];
  KO[0] = ee_KO[0];
  KO[1] = ee_KO[1];
  KO[2] = ee_KO[2];
  KO[3] = ee_KO[3];

  if(ee_KO[0] != ee_KO_last[0] || ee_KO[1] != ee_KO_last[1] || ee_KO[2] != ee_KO_last[2] || ee_KO[3] != ee_KO_last[3])
  {
    KO_parameter_initial();
    if(ee_product_information.conf_type == BASIC_PHYSICAL || ee_product_information.conf_type == BASIC_VIRTUAL)
    {
      	buffer[0] = ee_configurators.A;
      	buffer[1] = ee_configurators.PL;
      	buffer[2] = 0;
      	ee_KO_conf.DesAdd = StrToChar(&buffer);
      	ee_KO_conf.Reference = ee_KO_conf.DesAdd;
				configurator_to_KO();
    }
		
		ee_KO_last[0] = KO[0];
  	ee_KO_last[1] = KO[1];
  	ee_KO_last[2] = KO[2];
  	ee_KO_last[3] = KO[3];
  }
	else if(ee_product_information.conf_type == BASIC_PHYSICAL || ee_product_information.conf_type == BASIC_VIRTUAL)
	{
		buffer[0] = ee_configurators.A;
    buffer[1] = ee_configurators.PL;
    buffer[2] = 0;
    ee_KO_conf.DesAdd = StrToChar(&buffer);
		configurator_to_KO();
	}

  KO_conf = ee_KO_conf;
  product_information = ee_product_information;
	/*
	if(product_information.cen_system)
	{
		KO_conf.DF = 4;
		ee_KO_conf.DF = 4;
	}
	*/
  flags.id_confed = ee_product_information.ID_confed;
#ifdef CELIING
		DLL.setpoint_M = 20;
#else
		DLL.setpoint_M = 40; //Reyno 0604
#endif
		
	state.main_state = ee_main_state;
	g_slope = ee_slope;
	if(state.main_state == FACTORY_CALIBRATION_STEP1)
	{
		//led_blinking(60,60);
		buzzer_ms(500);
	}
	
	g_dataflash_page_address = ee_page_address;
}

void ID_setting(unsigned char *data)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
		ee_ID[i] = *(data+i);
  }
}

unsigned char configuration_checking(unsigned char *data)
{
  volatile struct SConfigurators confi;
	unsigned char result = 0;
	unsigned char buffer[3];
	unsigned char des_add;
	
	confi.A = *(data++);
	confi.PL = *(data++);
	confi.M = *(data++);
	confi.S = *(data++);
	confi.T = *(data++);
	
	buffer[0] = confi.A;
	buffer[1] = confi.PL;
	
	des_add = StrToChar(buffer);
	
	if( (confi.M >= '0') && (confi.M <= '4') )
	{
		if(confi.M == '0')
		{
			if((des_add >= 1 && des_add <= 0xAF) && (confi.S >= '0') && (confi.S <= '3') && (confi.T >= '0') && (confi.T <= '9'))
			{
				result = '0';
			}
		}
		else if(confi.M == '1')
		{
			if((des_add >= 1 && des_add <= 0xAF) && (confi.S == '0') && (confi.T == '0'))
			{
				result = '1';
			}
		}
		else if(confi.M == '2')
		{
			if((des_add <= 0xAF) && ((confi.S >= '0') && (confi.S <= '3')) && ((confi.T >= '0') && (confi.T <= '9')))
			{
				result = '2';
			}
		}
		else if(confi.M == '3')
		{
			if((des_add >= 1 && des_add <= 0xAF) && (confi.S >= '0') && (confi.S <= '3') && (confi.T >= '0') && (confi.T <= '9'))
			{
				result = '3';
			}
		}
		else if(confi.M == '4')
		{
			if((des_add >= 1 && des_add <= 0xAF) && (confi.S == '0') && (confi.T == '0'))
			{
				result = '4';
			}
		}
	}

	return result;
}

unsigned int write_KO(unsigned char index,unsigned char data)
{
#ifdef NONE_CONFED_203
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '8')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				KO_conf.GR = data;
  	  break;
  	
  	  case 7:
				KO_conf.GS1 = data;
  	  break;
  	
  	  case 8:
				KO_conf.GS2 = data;
  	  break;
  	
  	  case 10:
				KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 13:
				if(data == 0 || data == 1)
					KO_conf.en_load = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 14:
				if(data == 0 || data == 1)
					KO_conf.en_GS_main_group = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
			
#ifdef HARDWARE_PIR_US  	
  	  case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
			case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
#ifdef HARDWARE_US
			case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 22:
				KO_conf.DF = data;
  	  break;
  	
  	  case 23:
				if(data == 0 || data == 1)
					KO_conf.TypeLoop = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
	  case 24:
				KO_conf.NF = data;
  	  break;
  	
  	  case 25:
				KO_conf.DaylightSetp = data;
  	  break;
  	
  	  case 26:
				KO_conf.PofL = data;
				if(data == 0)
				{
					KO_conf.PofL = 0xFF;
					KO_conf.flag_PofL_Forced = 0;
				}
				else
				{
					KO_conf.flag_PofL_Forced = 1;
					DLL.load_provision = data * 5;
				}
  	  break;
  	
  	  case 27:
				KO_conf.DaylightLev = data;
  	  break;
  	
  	  case 28:
				if(data == 0 || data == 1)
					KO_conf.LightReg = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 29:
				if(data == 1 || data == 2 || data == 3 || data == 5)
					KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 30:
#ifdef HARDWARE_PIR
				if(data == 1)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 2)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 31:
#ifdef HARDWARE_PIR
				if(data == 1)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef  HARDWARE_US
				if(data == 2)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 32:
#ifdef HARDWARE_PIR
				if(data == 0 || data == 1)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 0 || data == 2)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data <= 4)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 34:
				if(data <= 3)
					KO_conf.Alert = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				KO_conf.GR = data;
  	  break;
  	
		case 22:
				KO_conf.DF = data;
  	  break;
			
			case 24:
				KO_conf.NF = data;
  	  break;
  	  case 25:
				KO_conf.DaylightSetp = data;
  	  break;
  	
  	  case 26:
				KO_conf.PofL = data;
				if(data == 0)
				{
					KO_conf.PofL = 0xFF;
					KO_conf.flag_PofL_Forced = 0;
				}
				else
				{
					KO_conf.flag_PofL_Forced = 1;
					DLL.load_provision = data * 5;
				}
  	  break;
  	
  	  case 27:
				KO_conf.DaylightLev = data;
  	  break;
  	
  	  case 28:
				if(data == 0 || data == 1)
					KO_conf.LightReg = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 29:
				if(data >= 1 && data <= 4)
					KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				KO_conf.GR = data;
  	  break;
  	
  	  case 7:
				KO_conf.GS1 = data;
  	  break;
  	
  	  case 8:
				KO_conf.GS2 = data;
  	  break;
  	
  	  case 10:
				KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 13:
				if(data == 0 || data == 1)
					KO_conf.en_load = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 14:
				if(data == 0 || data == 1)
					KO_conf.en_GS_main_group = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
#ifdef HARDWARE_PIR_US  	
  	  case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
			case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
#ifdef HARDWARE_US
			case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 29:
				if(data >= 1 && data <= 4)
					KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 30:
#ifdef HARDWARE_PIR
				if(data == 1)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 2)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 31:
#ifdef HARDWARE_PIR
				if(data == 1)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 2)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 32:
#ifdef HARDWARE_PIR
				if(data == 0 || data == 1)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 0 || data == 2)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data <= 4)
					KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 34:
				if(data <= 3)
					KO_conf.Alert = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '8' && KO[3] == '0')
	{
  	switch(index)
  	{
  	  case 10:
				KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
#ifdef HARDWARE_PIR_US  	
  	  case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
			case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
#ifdef HARDWARE_US
			case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 22:
				if(data >= 1 && data <= 4)
					KO_conf.DF = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
  	switch(index)
  	{
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	switch(index)
  	{
  	  case 10:
				KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;

  	  #ifdef HARDWARE_PIR_US  	
  	  case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif

#ifdef HARDWARE_PIR
			case 20:
				if(data <= 3)
					KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif			

#ifdef HARDWARE_US
			case 21:
				if(data <= 3)
					KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
				case 22:
				if(data >= 1 && data <= 4)
					KO_conf.DF = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	

  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
#endif

  return 0;
}

unsigned int write_ee_KO(unsigned char index,unsigned char data)
{
#ifdef NONE_CONFED_203
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '8')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					ee_KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(ee_KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(ee_KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					ee_KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				ee_KO_conf.GR = data;
  	  break;
  	
  	  case 7:
				ee_KO_conf.GS1 = data;
  	  break;
  	
  	  case 8:
				ee_KO_conf.GS2 = data;
  	  break;
  	
  	  case 10:
				ee_KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					ee_KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					ee_KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 13:
				if(data == 0 || data == 1)
					ee_KO_conf.en_load = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 14:
				if(data == 0 || data == 1)
					ee_KO_conf.en_GS_main_group = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_US
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
  	  case 22:
				ee_KO_conf.DF = data;
  	  break;
  	
  	  case 23:
				if(data == 0 || data == 1)
					ee_KO_conf.TypeLoop = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
		case 24:
				ee_KO_conf.NF = data;
  	  break;
  	  case 25:
				ee_KO_conf.DaylightSetp = data;
  	  break;
  	
  	  case 26:
				ee_KO_conf.PofL = data;
				if(data == 0)
				{
					ee_KO_conf.PofL = 0xFF;
					ee_KO_conf.flag_PofL_Forced = 0;
				}
				else
					ee_KO_conf.flag_PofL_Forced = 1;
  	  break;
  	
  	  case 27:
				ee_KO_conf.DaylightLev = data;
  	  break;
  	
  	  case 28:
				if(data == 0 || data == 1)
					ee_KO_conf.LightReg = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 29:
				if(data == 1 || data == 2 || data == 3 || data == 5)
					ee_KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 30:
#ifdef HARDWARE_PIR
				if(data == 1)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 2)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 31:
#ifdef HARDWARE_PIR
				if(data == 1)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 2)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 32:
#ifdef HARDWARE_PIR
				if(data == 0 || data == 1)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_US
				if(data == 0 || data == 2)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
				
#ifdef HARDWARE_PIR_US
				if(data <= 4)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 34:
				if(data <= 3)
					ee_KO_conf.Alert = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					ee_KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(ee_KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(ee_KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					ee_KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				ee_KO_conf.GR = data;
  	  break;
  	
		case 22:
				ee_KO_conf.DF = data;
  	  break;
			
			case 24:
				ee_KO_conf.NF = data;
  	  break;
  	  case 25:
				ee_KO_conf.DaylightSetp = data;
  	  break;
  	
  	  case 26:
				ee_KO_conf.PofL = data;
				if(data == 0)
				{
					ee_KO_conf.PofL = 0xFF;
					ee_KO_conf.flag_PofL_Forced = 0;
				}
				else
					ee_KO_conf.flag_PofL_Forced = 1;
  	  break;
  	
  	  case 27:
				ee_KO_conf.DaylightLev = data;
  	  break;
  	
  	  case 28:
				if(data == 0 || data == 1)
					ee_KO_conf.LightReg = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 29:
				if(data >= 1 && data <= 4)
					ee_KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	switch(index)
  	{
  	  case 1:
				if(data == 0 || data == 2)
					ee_KO_conf.AddressType = data;
				else
					return PAR_OUT_OF_RANGE;
			break;
  	
  	  case 2:
				if(ee_KO_conf.AddressType == 0)
				{
					if(data >= 0x01 && data <= 0xAF)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
				else if(ee_KO_conf.AddressType == 2)
				{
					if(data >= 0x00 && data <= 0x0A)
						ee_KO_conf.DesAdd = data;
					else
						return PAR_OUT_OF_RANGE;
				}
  	  break;
  	
  	  case 5:
				if(data <= 0xAF)
					ee_KO_conf.Reference = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 6:
				ee_KO_conf.GR = data;
  	  break;
  	
  	  case 7:
				ee_KO_conf.GS1 = data;
  	  break;
  	
  	  case 8:
				ee_KO_conf.GS2 = data;
  	  break;
  	
  	  case 10:
				ee_KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					ee_KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					ee_KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 13:
				if(data == 0 || data == 1)
					ee_KO_conf.en_load = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 14:
				if(data == 0 || data == 1)
					ee_KO_conf.en_GS_main_group = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_US
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 29:
				if(data >= 1 && data <= 4)
					ee_KO_conf.FuncMod = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 30:
#ifdef HARDWARE_PIR
				if(data == 1)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_US
				if(data == 2)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					ee_KO_conf.InitOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 31:
#ifdef HARDWARE_PIR
				if(data == 1)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_US
				if(data == 2)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_PIR_US
				if(data >= 1 && data <= 4)
					ee_KO_conf.MaintainOccu = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 32:
#ifdef HARDWARE_PIR
				if(data == 0 || data == 1)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_US
				if(data == 0 || data == 2)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
#ifdef HARDWARE_PIR_US
				if(data <= 4)
					ee_KO_conf.Retrigger = data;
				else
					return PAR_OUT_OF_RANGE;
#endif
  	  break;
  	
  	  case 34:
				if(data <= 3)
					ee_KO_conf.Alert = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '8' && KO[3] == '0')
	{
  	switch(index)
  	{
  	  case 10:
				ee_KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					ee_KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					ee_KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_US
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 22:
				ee_KO_conf.DF = data;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
  	switch(index)
  	{
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	switch(index)
  	{
  	  case 10:
				ee_KO_conf.Hours = data;
  	  break;
  	
  	  case 11:
				if(data <= 59)
					ee_KO_conf.Minutes = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 12:
				if(data <= 59)
					ee_KO_conf.Seconds = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;

#ifdef HARDWARE_PIR_US
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
  	
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_PIR
  	  case 20:
				if(data <= 3)
					ee_KO_conf.PirSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
			
#ifdef HARDWARE_US
  	  case 21:
				if(data <= 3)
					ee_KO_conf.USSens = data;
				else
					return PAR_OUT_OF_RANGE;
  	  break;
#endif
  	
  	  case 22:
				ee_KO_conf.DF = data;
  	  break;
  	
  	  default:
				return PAR_NOT_IMPLEMENTED;
  	}
	}
#endif

  return 0;
}

unsigned char read_KO_none_confed(unsigned char index)
{
		switch(index)
  	{
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
				
  	  case 5:
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return KO_conf.GS1;
  	
  	  case 8:
				return KO_conf.GS2;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return KO_conf.en_load;
  	
  	  case 14:
				return KO_conf.en_GS_main_group;

#ifdef HARDWARE_PIR_US
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
#endif
				
#ifdef HARDWARE_PIR
  	  case 20:
				return KO_conf.PirSens;
#endif
				
#ifdef HARDWARE_US
  	  case 21:
				return KO_conf.USSens;
#endif
				
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return KO_conf.TypeLoop;
		case 24:
				return KO_conf.NF;
  	
  	  case 25:
				return KO_conf.DaylightSetp;
  	
  	  case 26:
				return KO_conf.PofL;
  	
  	  case 27:
				return KO_conf.DaylightLev;
  	
  	  case 28:
				return KO_conf.LightReg;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return KO_conf.InitOccu;
  	
  	  case 31:
				return KO_conf.MaintainOccu;
  	
  	  case 32:
				return KO_conf.Retrigger;
  	
  	  case 34:
				return KO_conf.Alert;
  	
  	  default:
  	    return 0;
  	}
}

unsigned int read_KO(unsigned char index)
{
#ifdef NONE_CONFED_203
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '8')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				asm("nop");
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return KO_conf.GS1;
  	
  	  case 8:
				return KO_conf.GS2;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return KO_conf.en_load;
  	
  	  case 14:
				return KO_conf.en_GS_main_group;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;

#ifdef HARDWARE_PIR_US
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
#endif
				
#ifdef HARDWARE_PIR
  	  case 20:
				return KO_conf.PirSens;
#endif
				
#ifdef HARDWARE_US
  	  case 21:
				return KO_conf.USSens;
#endif
				
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return KO_conf.TypeLoop;
  	
  	  case 24:
				return KO_conf.NF;
  	
  	  case 25:
				return KO_conf.DaylightSetp;
  	
  	  case 26:
				return KO_conf.PofL;
  	
  	  case 27:
				return KO_conf.DaylightLev;
  	
  	  case 28:
				return KO_conf.LightReg;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return KO_conf.InitOccu;
  	
  	  case 31:
				return KO_conf.MaintainOccu;
  	
  	  case 32:
				return KO_conf.Retrigger;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return KO_conf.Alert;
  	
  	  default:
  	    return 0xFFFF;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return 0xFFFF;
  	
  	  case 8:
				return 0xFFFF;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return 0xFFFF;
  	
  	  case 11:
				return 0xFFFF;
  	
  	  case 12:
				return 0xFFFF;
  	
  	  case 13:
				return 0xFFFF;
  	
  	  case 14:
				return 0xFFFF;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
  	  case 20:
				return 0xFFFF;
  	
  	  case 21:
				return 0xFFFF;
  	
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return KO_conf.NF;
  	
  	  case 25:
				return KO_conf.DaylightSetp;
  	
  	  case 26:
				return KO_conf.PofL;
  	
  	  case 27:
				return KO_conf.DaylightLev;
  	
  	  case 28:
				return KO_conf.LightReg;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return 0xFFFF;
  	
  	  case 31:
				return 0xFFFF;
  	
  	  case 32:
				return 0xFFFF;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return 0xFFFF;
  	
  	  default:
  	    return 0xFFFF;
  	}
	}
  else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return KO_conf.GS1;
  	
  	  case 8:
				return KO_conf.GS2;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return KO_conf.en_load;
  	
  	  case 14:
				return KO_conf.en_GS_main_group;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
#endif
				
#ifdef HARDWARE_PIR
  	  case 20:
				return KO_conf.PirSens;
#endif
				
#ifdef HARDWARE_US
  	  case 21:
				return KO_conf.USSens;
#endif
  	
  	  case 22:
				return 0xFFFF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return 0xFFFF;
  	
  	  case 25:
				return 0xFFFF;
  	
  	  case 26:
				return 0xFFFF;
  	
  	  case 27:
				return 0xFFFF;
  	
  	  case 28:
				return 0xFFFF;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return KO_conf.InitOccu;
  	
  	  case 31:
				return KO_conf.MaintainOccu;
  	
  	  case 32:
				return KO_conf.Retrigger;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return KO_conf.Alert;
  	
  	  default:
  	    return 0xFFFF;
  	}
  }
  if(KO[0] == '0' && KO[1] == '0' && KO[2] == '8' && KO[3] == '0')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return 0xFFFF;
  	
  	  case 2:
				return 0xFFFF;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return 0xFFFF;
  	
  	  case 6:
				return 0xFFFF;
  	
  	  case 7:
				return 0xFFFF;
  	
  	  case 8:
				return 0xFFFF;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return 0xFFFF;
  	
  	  case 14:
				return 0xFFFF;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
#endif
				
#ifdef HARDWARE_PIR
  	  case 20:
				return KO_conf.PirSens;
#endif
				
#ifdef HARDWARE_US
  	  case 21:
				return KO_conf.USSens;
#endif
  	
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return 0xFFFF;
  	
  	  case 25:
				return 0xFFFF;
  	
  	  case 26:
				return 0xFFFF;
  	
  	  case 27:
				return 0xFFFF;
  	
  	  case 28:
				return 0xFFFF;
  	
  	  case 29:
				return 0xFFFF;
  	
  	  case 30:
				return 0xFFFF;
  	
  	  case 31:
				return 0xFFFF;
  	
  	  case 32:
				return 0xFFFF;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return 0xFFFF;
  	
  	  default:
  	    return 0xFFFF;
  	}
	}
  else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
  	switch(index)
  	{
  	  default:
        return 0xFFFF;
  	}
	}
  else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return 0xFFFF;
  	
  	  case 2:
				return 0xFFFF;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return 0xFFFF;
  	
  	  case 6:
				return 0xFFFF;
  	
  	  case 7:
				return 0xFFFF;
  	
  	  case 8:
				return 0xFFFF;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return 0xFFFF;
  	
  	  case 14:
				return 0xFFFF;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
#ifdef HARDWARE_PIR_US
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
#endif
				
#ifdef HARDWARE_PIR
  	  case 20:
				return KO_conf.PirSens;
#endif
				
#ifdef HARDWARE_US
  	  case 21:
				return KO_conf.USSens;
#endif
  	
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return 0xFFFF;
  	
  	  case 25:
				return 0xFFFF;
  	
  	  case 26:
				return 0xFFFF;
  	
  	  case 27:
				return 0xFFFF;
  	
  	  case 28:
				return 0xFFFF;
  	
  	  case 29:
				return 0xFFFF;
  	
  	  case 30:
				return 0xFFFF;
  	
  	  case 31:
				return 0xFFFF;
  	
  	  case 32:
				return 0xFFFF;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return 0xFFFF;
  	
  	  default:
  	    return 0xFFFF;
  	}
	}
#endif

#ifdef NONE_CONFED_204
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return 0xFFFF;
  	
  	  case 8:
				return 0xFFFF;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return 0xFFFF;
  	
  	  case 11:
				return 0xFFFF;
  	
  	  case 12:
				return 0xFFFF;
  	
  	  case 13:
				return 0xFFFF;
  	
  	  case 14:
				return 0xFFFF;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
  	  case 20:
				return 0xFFFF;
  	
  	  case 21:
				return 0xFFFF;
  	
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return KO_conf.NF;
  	
  	  case 25:
				return KO_conf.DaylightSetp;
  	
  	  case 26:
				return KO_conf.PofL;
  	
  	  case 27:
				return KO_conf.DaylightLev;
  	
  	  case 28:
				return KO_conf.LightReg;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return 0xFFFF;
  	
  	  case 31:
				return 0xFFFF;
  	
  	  case 32:
				return 0xFFFF;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return 0xFFFF;
  	
  	  default:
  	    return 0xFFFF;
  	}
  }
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
  	switch(index)
  	{
  	  default:
        return 0xFFFF;
  	}
	}
#endif

#ifdef NONE_CONFED_1FF
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return KO_conf.AddressType;
  	
  	  case 2:
				return KO_conf.DesAdd;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return KO_conf.Reference;
  	
  	  case 6:
				return KO_conf.GR;
  	
  	  case 7:
				return KO_conf.GS1;
  	
  	  case 8:
				return KO_conf.GS2;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return KO_conf.en_load;
  	
  	  case 14:
				return KO_conf.en_GS_main_group;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
  	
  	  case 22:
				return 0xFFFF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return 0xFFFF;
  	
  	  case 25:
				return 0xFFFF;
  	
  	  case 26:
				return 0xFFFF;
  	
  	  case 27:
				return 0xFFFF;
  	
  	  case 28:
				return 0xFFFF;
  	
  	  case 29:
				return KO_conf.FuncMod;
  	
  	  case 30:
				return KO_conf.InitOccu;
  	
  	  case 31:
				return KO_conf.MaintainOccu;
  	
  	  case 32:
				return KO_conf.Retrigger;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return KO_conf.Alert;
  	
  	  default:
  	    return 0xFFFF;
  	}
  }
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	switch(index)
  	{
  	  case 0:
  	    return 0xFFFF;
  	
  	  case 1:
  	    return 0xFFFF;
  	
  	  case 2:
				return 0xFFFF;
  	
  	  case 3:
			  return 0xFFFF;
  	
  	  case 4:
  	    return 0xFFFF;
  	
  	  case 5:
				return 0xFFFF;
  	
  	  case 6:
				return 0xFFFF;
  	
  	  case 7:
				return 0xFFFF;
  	
  	  case 8:
				return 0xFFFF;
  	
  	  case 9:
  	    return 0xFFFF;
  	
  	  case 10:
				return KO_conf.Hours;
  	
  	  case 11:
				return KO_conf.Minutes;
  	
  	  case 12:
				return KO_conf.Seconds;
  	
  	  case 13:
				return 0xFFFF;
  	
  	  case 14:
				return 0xFFFF;
  	
  	  case 15:
  	    return 0xFFFF;
  	
  	  case 16:
  	    return 0xFFFF;
  	
  	  case 17:
  	    return 0xFFFF;
  	
  	  case 18:
  	    return 0xFFFF;
  	
  	  case 19:
  	    return 0xFFFF;
  	
  	  case 20:
				return KO_conf.PirSens;
  	
  	  case 21:
				return KO_conf.USSens;
  	
  	  case 22:
				return KO_conf.DF;
  	
  	  case 23:
				return 0xFFFF;
  	
  	  case 24:
				return 0xFFFF;
  	
  	  case 25:
				return 0xFFFF;
  	
  	  case 26:
				return 0xFFFF;
  	
  	  case 27:
				return 0xFFFF;
  	
  	  case 28:
				return 0xFFFF;
  	
  	  case 29:
				return 0xFFFF;
  	
  	  case 30:
				return 0xFFFF;
  	
  	  case 31:
				return 0xFFFF;
  	
  	  case 32:
				return 0xFFFF;
  	
  	  case 33:
  	    return 0xFFFF;
  	
  	  case 34:
				return 0xFFFF;
  	
  	  default:
  	    return 0xFFFF;
  	}
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '0')
	{
  	switch(index)
  	{
  	  default:
        return 0xFFFF;
  	}
	}
#endif
  return 0xFFFE;
}

void KO_parameter_initial(void)
{
  if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '8')
	{
  	ee_KO_conf = flash_KO_168;
		write_moudle_parameter();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	ee_KO_conf = flash_KO_166;
		write_moudle_parameter();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	ee_KO_conf = flash_KO_119;
		write_moudle_parameter();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '8' && KO[3] == '0')
	{
  	ee_KO_conf = flash_KO_128;
		write_moudle_parameter();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
    ee_KO_conf = flash_KO_128;
		write_moudle_parameter();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	ee_KO_conf = flash_KO_165;
		write_moudle_parameter();
	}
}

void KO_parameter_initial_temp(void)
{
	if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '8')
	{
  	KO_conf = flash_KO_168;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '6')
	{
  	KO_conf = flash_KO_166;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '7' && KO[3] == '7')
	{
  	KO_conf = flash_KO_119;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == '8' && KO[3] == '0')
	{
  	KO_conf = flash_KO_128;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '4')
	{
    KO_conf = flash_KO_128;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '0' && KO[2] == 'A' && KO[3] == '5')
	{
  	KO_conf = flash_KO_165;
		write_moudle_parameter_temp();
	}
	else if(KO[0] == '0' && KO[1] == '2' && KO[2] == '0' && KO[3] == '3')
	{
		KO_conf = flash_KO_515;
		write_moudle_parameter_temp();
	}
}

void write_moudle_parameter(void)
{
#ifdef HARDWARE_PIR
			ee_KO_conf.Reference = 0;

			ee_KO_conf.Hours = 0;

			ee_KO_conf.Minutes = 15;

			ee_KO_conf.Seconds = 0;

			ee_KO_conf.PirSens = 3;
			
#ifdef CELIING
			ee_KO_conf.DF = 35;
#else
			ee_KO_conf.DF = 10;
#endif
			
			if(ee_product_information.cen_system)
			{
				ee_KO_conf.DF = 1;
			}	
  		
			ee_KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			ee_KO_conf.DaylightSetp = 100;
#else
			ee_KO_conf.DaylightSetp = 60;
#endif
			
			ee_KO_conf.PofL = 255;

			ee_KO_conf.LightReg = 0;

			ee_KO_conf.FuncMod = 2;

			ee_KO_conf.InitOccu = 1;

			ee_KO_conf.MaintainOccu = 1;

			ee_KO_conf.Retrigger = 1;

			ee_KO_conf.Alert = 0;
#endif
			
#ifdef HARDWARE_US
			ee_KO_conf.Reference = 0;

			ee_KO_conf.Hours = 0;

			ee_KO_conf.Minutes = 15;

			ee_KO_conf.Seconds = 0;

			ee_KO_conf.USSens = 2;
			
#ifdef CELIING
			ee_KO_conf.DF = 35;
#else
			ee_KO_conf.DF = 10;
#endif
  		if(ee_product_information.cen_system)
			{
				ee_KO_conf.DF = 2;
			}	
			
			ee_KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			ee_KO_conf.DaylightSetp = 100;
#else
			ee_KO_conf.DaylightSetp = 60;
#endif
			
			ee_KO_conf.PofL = 255;

			ee_KO_conf.LightReg = 0;

			ee_KO_conf.FuncMod = 2;

			ee_KO_conf.InitOccu = 2;

			ee_KO_conf.MaintainOccu = 2;

			ee_KO_conf.Retrigger = 2;

			ee_KO_conf.Alert = 0;
#endif
			
#ifdef HARDWARE_PIR_US
			ee_KO_conf.Reference = 0;

			ee_KO_conf.Hours = 0;

			ee_KO_conf.Minutes = 15;

			ee_KO_conf.Seconds = 0;
  		
			ee_KO_conf.PirSens = 3;
			
			ee_KO_conf.USSens = 2;
			
#ifdef CELIING
			ee_KO_conf.DF = 35;
#else
			ee_KO_conf.DF = 10;
#endif
  		
			if(ee_product_information.cen_system)
			{
				ee_KO_conf.DF = 4;
			}	
			
			ee_KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			ee_KO_conf.DaylightSetp = 100;
#else
			ee_KO_conf.DaylightSetp = 60;
#endif
			
			ee_KO_conf.PofL = 255;

			ee_KO_conf.LightReg = 0;

			ee_KO_conf.FuncMod = 2;

			ee_KO_conf.InitOccu = 3;

			ee_KO_conf.MaintainOccu = 4;

			ee_KO_conf.Retrigger = 4;

			ee_KO_conf.Alert = 0;
#endif
}

void write_moudle_parameter_temp(void)
{
#ifdef HARDWARE_PIR
			KO_conf.Reference = 0;

			KO_conf.Hours = 0;

			KO_conf.Minutes = 15;

			KO_conf.Seconds = 0;

			KO_conf.PirSens = 3;
			
#ifdef CELIING
			KO_conf.DF = 35;
#else
			KO_conf.DF = 10;
#endif
  		
			if(temp_product_information.cen_system)
			{
				KO_conf.DF = 1;
			}	
			
			KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			KO_conf.DaylightSetp = 100;
#else
			KO_conf.DaylightSetp = 60;
#endif
			
			KO_conf.PofL = 255;

			KO_conf.LightReg = 0;

			KO_conf.FuncMod = 2;

			KO_conf.InitOccu = 1;

			KO_conf.MaintainOccu = 1;

			KO_conf.Retrigger = 1;

			KO_conf.Alert = 0;
#endif

#ifdef HARDWARE_US
			KO_conf.Reference = 0;

			KO_conf.Hours = 0;

			KO_conf.Minutes = 15;

			KO_conf.Seconds = 0;

			KO_conf.USSens = 2;
			
#ifdef CELIING
			KO_conf.DF = 35;
#else
			KO_conf.DF = 10;
#endif
  		
			if(temp_product_information.cen_system)
			{
				KO_conf.DF = 2;
			}	
			
			KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			KO_conf.DaylightSetp = 100;
#else
			KO_conf.DaylightSetp = 60;
#endif
			
			KO_conf.PofL = 255;

			KO_conf.LightReg = 0;

			KO_conf.FuncMod = 2;

			KO_conf.InitOccu = 2;

			KO_conf.MaintainOccu = 2;

			KO_conf.Retrigger = 2;

			KO_conf.Alert = 0;
#endif

#ifdef HARDWARE_PIR_US
			KO_conf.Reference = 0;

			KO_conf.Hours = 0;

			KO_conf.Minutes = 15;

			KO_conf.Seconds = 0;
  		
			KO_conf.PirSens = 3;
			
			KO_conf.USSens = 2;
			
#ifdef CELIING
			KO_conf.DF = 35;
#else
			KO_conf.DF = 10;
#endif
  		
			if(temp_product_information.cen_system)
			{
				KO_conf.DF = 4;
			}	
			
			KO_conf.TypeLoop = 0;
			
#ifdef CELIING
			KO_conf.DaylightSetp = 100;
#else
			KO_conf.DaylightSetp = 60;
#endif
			
			KO_conf.PofL = 255;

			KO_conf.LightReg = 0;

			KO_conf.FuncMod = 2;

			KO_conf.InitOccu = 3;

			KO_conf.MaintainOccu = 4;

			KO_conf.Retrigger = 4;

			KO_conf.Alert = 0;
#endif
}