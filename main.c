//2008 12 12 finish buzzer function
//add IR setting parameter
//2008 12 31 finish modality0 test
//2008 12 31 add extended frame for turn on/off acturator
//2008 12 31 add first time Provision of Light detect
//2009 1 2 add IR Communication Tool communication
//2009 1 2 save the KO parameter into eeprom
//2009 1 2 complete PIR sensitivity test
//2009 1 3 finish IR frame, need test
//2009 1 4 test the IR P&L, forward to SCS bus
//2009 1 4 go on test the PIR & US functions
//2009 1 4 add push button diagnostic frame
//2009 1 5 add LM018
//2009 1 7 find an conflict in software of acturator with the document "ID request the 4 byte parameter must set to zero"
//2009 1 7 update IR ID request frame
//2009 1 7 add room controler ID request frame
//2009 1 8 add ID confirm, setting frame
//2009 1 8 research the master slave setting for acturator
//2009 1 8 could not find the RC's handshake frame
//2009 1 8 dont know ID 07 arguments means
//2009 1 8 improoved the dianostic frame change 00~0F to 80~8F
//2009 1 9 remove the ID 07 dianostic frame
//2009 1 9 test D|x x|x x|Sys x|2 8|C 0|0 0|8 F|0
//2009 1 9 change back ID 07 dianostic frame answer
//2009 1 12 want to solve the timing sequence problem with the RC
//2009 1 12 first send D2 00 01 42 8B 01 90 02
//										 D2 00 01 42 8D 09 00 02
//										 D2 00 01 42 8D 02 01 02
//										 D2 00 01 42 8D 02 02 02
//2009 1 12 add product moudle select
//2009 1 12 find there have error at 8B answer frame
//2009 1 13 updated the RC's fireware
//2009 1 13 achieve P&G function with the RC use SCS monitor
//2009 1 13 solve the trafic in load status update function
//2009 1 13 add KO erease frame
//2009 1 13 complete using point to setting the key object number, passed the test
//2009 1 14 modified the configurators setting sequance
//2009 1 14 it have only way send D0 get into programming state
//2009 1 14 sample of LM056 default A PL 00 00, user can use basic virtual configuration to change it's address
//2009 1 16 write the development progress about the SCS sensor
//2009 1 20 improve the SCS reception buffer
//2009 1 20 improve RC communication frame
//2009 1 23 test the ethernet scs gateway
//2009 1 23 study the scenarios command, most in feasibility book
//2009 2 1 sensor detection LED change delay ON during 1s
//         If sensor received a new detection during this 1s delay, LED stayed in state ON for another 1s.
//2009 2 1 first send D0 0B frame, then device could answer, add 0A 0B frame
//2009 2 1 LEV == 1 do nothing
//2009 2 1 read the PVL document
//2009 2 2 tested pass the group creation
//2009 2 4 add the short or long pressed button function
//2009 2 4 add LED blinking status function
//2009 2 4 add push and learn break
//2009 2 5 complete P&L sensor transmission group creation
//2009 2 6 change step 2 time out value from 10s to 60s
//2009 2 6 test OK the group add remove
//2009 2 6 find 2 conflicts in the Push and Learn sensor_22.doc
//2009 2 9 finish point-to-point sensor actuator(without LPB)
//2009 2 10 finish all the SCS push and learn function, need test
//2009 2 12 complete Plug and Go function
//2009 2 12 finish push and learn IR scenario remove independently

//2009 2 17 find a bug when use IR scenario remove, tha actuator remove all the scenario
//2009 2 17 finish push and learn IR remove all
//2009 2 19 improve diagnostic frame

//2009 2 22 finish basic virtual configuration
//2009 2 22 add system reset

//2009 3 3 configurator reading need a interface reset

////////////////////////////////////////////////////////////////////////////////////////////////////
//                      Bug about the Actuator on Room Controler
//1. the LED can't indicator the load at the same time
//
////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
//                        Room Controler Power On Frame                                           //
//1.	D0 00 01 0B 00 00 00 00               ID enable requeset
//2.  D0 00 01 08 00 00 00 00               ID request to not configured device
//3.  D0 00 01 04 00 03 00 28								ID transmission
//4.  D0 00 01 0B 00 00 00 00               ID enable requeset
//5.  D0 00 01 09 00 00 00 00               ID to configured device
//6.  D0 01 01 04 98 76 54 32								ID transmission     from acturator
//7.  D0 00 01 07 00 03 00 28               Start test configuration
//8.  D2 00 01 34 00 00 00 00					

//                        Push and Learn group frame
//D | x	d1 | d0	d2 | 1	42 / 34	8 | C	GG	0 | 9	Dev|Cmd
//
//Dev is the device type:
//-	0: Light command
//-	1: Shutter command
//-	2: Light actuator
//-	3: Shutter actuator
//-	4: Sensor
//-	F: Generic command device
//Cmd is the command:
//-	0: Start PnL
//-	1: Group confirmation
//-	2: Group refusing
//-	3: Referent transmission
//-	4: Group erasing
//-	5: Group request
//-	6: Group assignation
//-	7: Group release
//-	8: No group available
//-	9: "Group used" request
//-	F: End PnL
//GG is the number of group.

//                        Push and Learn scenario frame
//D | x	d1 | d0	d2 | 1	42 / 34	8 | C	NS	0 | A	Cmd

//Cmd is the command:
//-	0x00: Start PnL scenario
//-	0x05: Scenario request
//-	0x06: Scenario assignation
//-	0x07: Scenario release
//-	0x08: No scenario available
//-	0x09: "Scenario used" request (only for command devices)
//-	0x0F: End PnL scenario
//NS is the number of the scenario

//                     Push and Learn frame for IR tool
//D | 2	d1 | d0	d2 | 1	42	8 | C	00	0B	Cmd
//Cmd is the command:
//-	0x01: Next actuator
//-	0x02: Include
//-	0x03: Exclude
//-	0x04: Set ON
//-	0x05: Set OFF
//-	0x06: Set DIMMING UP
//-	0x07: SET DIMMING DOWN
//-	0x08: RESET GROUP

//仅能设置一个Actuator
//LM028 only send PP frame

//NSS | MyHome SubSystem
//----|--------------------------------
//  1 | Lighting-Automation
//  2 | Electrical system supervision
//  3 | Thermo-regulation
//  4 | Anti-intrusion
//  5 | Luminous signaling
//  6 | Videodoorentrysystem
//  7 | Access control
//  8 | Multimedia
//  9 | Auxiliary
//  F | Integration devices


//|------------------------------------+------------------------------------|
//| Product State                    | LLED state |
//|------------------------------------+------------------------------------|
//| No configured                    | 120ms ON , 120ms OFF |
//|------------------------------------+------------------------------------|
//| Auto configuration               | 60ms ON, 1s OFF |
//|------------------------------------+------------------------------------|
//| Distant Configuration in process | 1s ON, 1s OFF |
//|------------------------------------+------------------------------------|
//| Preselection Leader or Actor     | 1s ON, 1s OFF |
//|------------------------------------+------------------------------------|
//| Leader or actor learning         | 250ms ON , 250ms OFF |
//|------------------------------------+------------------------------------|
//| Erasing                          | 60ms ON , 200ms OFF during 5s |
//|------------------------------------+------------------------------------|
//| Error                            (memory full or | ON during 5s | incompatibility ) | |
//|------------------------------------+------------------------------------|


//how to handling the "not allowed" frame

//2009 03 23 updated all PnL group functions

//test modified test90
//device doesn't implement the current key object

//announce ID66
//open learning
//stop learning

//their have two conflit with NiToo 70 36 command, one said set_dimmer_up, another factory default

//updated 2009 04 07
//for PnL scenario Blinking(250,250)

//2009 4 20 updated PnL for group sensor
//2009 4 20 updated IR scenario
//2009 4 20 fixed the problem about parameter lost after PnG
//2009 4 20 improve KO_temp

//2009 4 21 fixed scenario full indicator

//2009 4 27 updated PnL Group sensors
//2009 4 28 great updated for gateway settting

//2009 5 4 updating key object setting and error response frame
//start advance 008 92B test
//2009 5 6 updated PnL Group remove, keep the reference if after PnG
//2009 5 8 finished self test for advance configuration
//2009 5 29 fix daylight level calibration and D.F via IR in close loop
//2009 6 1 detection is disabled in maintain, retrigger and standby for 20s if received "OFF" (derogation)

//2009 6 4 updated different device moudle for initial parameter

// updated version1 software for Limoges test
// updated version2 software for local test
// prepare software for label printer
// discuss the daylight parts with French

// improve the software
// finish the point to point test
// go on with the group function test
// prepare samples for Limoges
// define the lable for every product

// start to make a production equipment for final production
// updated software to version 1.1
// finished certralized system
// make some test for new test document from French
// define the new schematic for new modification

// pass all the latest test document
// prepare a equipment for final production
// check the initial parameter for modality 2
// read document used on final production

// add timer interval check for modality2
// check the final test schematic and PCB board
// prepare software for final delivery test

// the font is 6x10 pix

#include <ioavr.h>
#include <inavr.h>
#include "board.h"
#include "usart.h"
#include "decode_scs.h"
#include "stdlib.h"
#include "moudle_SCS.h"
#include "PIR.h"
#include "configuration.h"
#include "global_variable.h"
#include "IR.h"
#include "application.h"
#include "decode_scs_next.h"
#include "moudle_scs.h"
#include "string.h"
#include <intrinsics.h>
#include "function_service.h"
#include "font.h"
#include "DRI_TOUCH.h"
#include "printer.h"
#include "DRI_LCD.H"
#include "dataflash.h"
#include "usb_command.h"

//unsigned char buffer_test[3];
enum e_state{sun,mon,tue,wed,thu,fri,sat}state2;
//enum e_state state2;
struct s_blink
{
  unsigned char (*initial)();
  unsigned char (*disable)(unsigned char);
}blink;

void main(void)
{
  unsigned char (*pStateFunc)();
  pStateFunc = scs_pnl_none_confed_slave;
  blink.initial = scs_pnl_none_confed_slave;
  blink.initial();
   //blink.initial = 1;
  //blink.initial = scs_pnl_none_confed_slave();
  pStateFunc();
	state2 = mon;
	//unsigned char (*pStateFunc)(char);
	
  __watchdog_reset();
	WDT_off();
	IO_Initial();

	led_blinking_disable(0);
	
	global_variable_initial();
	init_USART0();
	init_USART1(115200);
	
	timer0_enable();
	timer2_enable();

	external_interrupt_initial();

  test_ID_assigned();

	start_conf();
	load_parameter();
  delay_ms(1000);
  __enable_interrupt();

	LCD_init();

	key_parameter_initial();
	
	menu_00();			
	
	//chip_erease_one_command();
	/*
	for(i = 0; i<TOP_PAGE*6;i++)
	{
		CharToStr(i>>8,buffer);
		stru_sensor.id[4] = buffer[0];
		stru_sensor.id[5] = buffer[1];
		CharToStr(i & 0x00FF,buffer);
		stru_sensor.id[6] = buffer[0];
		stru_sensor.id[7] = buffer[1];
		write_flash(0,stru_sensor);	
	}
	*/
	
	while(1)
	{
#ifdef FINAL_VERSION2
		usb_decode();
#endif
		if(IS_PEN == 0)
		{
			TOUCH_getdata();		//获取当前触摸屏按键的坐标(0,0)~(160,160)
			
			switch(get_touch_menu_00())
			{
				case 0:
					LCD_Clr();
					menu_01();		// set Lux
				break;

//#ifdef FINAL_VERSION2
				case 1:
					input_screen("product model",g_model,INPUT_MODEL);
					input_screen("release year",g_year,INPUT_YEAR);
					input_screen("release week", g_week,INPUT_WEEK);
					input_screen("software version",g_soft,INPUT_SOFTWARE_VERSION);
					input_screen("hardware version",g_hard,INPUT_HARDWARE_VERSION);
					menu_02();			// set ID
				break;
//#endif
				
				case 2:
					test_screen_all("functionality test",g_model);
				break;
				
			default:break;
			}
		}
		
		light_adj();
	}
}
