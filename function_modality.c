#include <ioavr.h>
#include <inavr.h>
#include "global_variable.h"
#include "moudle_SCS.h"
#include "function_modality.h"
#include "application.h"
#include "board.h"
#include "function_service.h"

void modality_service(void)
{
	
	switch (Configurators.M)
	{
		case '0':
			modality_0_initial();
			//modality_0();
			//modality_0();
		break;

		default:break;
	}
	
}

void modality_0_initial(void)
{
	flags.modality0_initialed = 1;
}

void modality_0(void)
{
	
	if(Time_delay.LPB.count > 2000)
	{
		led_blinking_ms(250,250,5000);
		 delay_ms(5000);
	}
	
  //daylight_service();
	occupancy_detect();
}

void modality_1(void)
{

}

void modality_2(void)
{

}

void modality_3(void)
{

}

void modality_4(void)
{

}