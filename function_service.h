#ifndef _FUNCTION_SERVICE_H
#define _FUNCTION_SERVICE_H


// set point level
#define		Low								1
#define		Medium						2
#define		High        			3

// function state define
#define 	Initial_state			1
#define 	Maintain_state		2
#define 	Re_Trigger_State	3
#define 	Standby_state			4

// detection scheme
#define     PIR_only        1
#define     US_only         2
#define     PIR_US          3
#define     PIR_OR_US       4

// timeout warning mode define
#define		Disabled 					0
#define		Visual						1
#define		Acustic						2
#define		Visual_Acustic		3

// function mode define
#define	Auto_ONOFF						1
#define	Auto_Walk_thru				2
#define	ManualON_Auto_OFF			3		
#define	ManualON_Manual_OFF		4
#define	Partial_ON						5

// time delay define
#define  	Re_Trigger_5s			5
#define  	presence_20s			20000			//10
#define  	Re_Trigger_30s		30
#define		Walkthru_delay		180			// 3min
#define		OFF_delay_2s			2000		//2000ms after send "OFF", motion sensor will enable 2 second later	0527
#define		OFF_delay_20s			20000	

#define 	Maunal_ON         1
#define 	Maunal_OFF        2

// define the configurators.T
#define     T_10S         	10
#define     T_30S         	30
#define     T_1min        	60
#define     T_2min        	120
#define     T_5min        	300
#define     T_10min       	600
#define     T_15min       	900
#define     T_20min       	1200
#define     T_30min       	1800
#define     T_40min       	2400

// define the sensor status
#define 	Status_Retrigger		0	//	SetBit(KO_conf.status[1],Status_Retrigger);
#define 	Status_Walk_through	1	//	SetBit(KO_conf.status[1],Status_Walk_through);
#define 	Status_Maintain			2	//	SetBit(KO_conf.status[1],Status_Maintain);
#define 	Status_Detection		3	//	SetBit(KO_conf.status[1],Status_Detection);
#define 	Status_Derogation		4	//	SetBit(KO_conf.status[1],Status_Derogation);
#define 	Status_Regulation		5	//	SetBit(KO_conf.status[1],Status_Regulation);
#define		Status_Regulationing 6
#define 	Status_ON					100	//	KO_conf.status[0] = Status_ON;
#define 	Status_OFF					0	//	KO_conf.status[0] = Status_OFF;
#define 	Status_DIM					0	//	KO_conf.status[0] = status[2]&Status_OFF;

#define SAMPLE_COUNT 80
#define MIN_5 300000
 /*
SetBit(KO_conf.status[3],Status_Retrigger);
SetBit(KO_conf.status[3],Status_Walk_through);
SetBit(KO_conf.status[3],Status_Maintain);
SetBit(KO_conf.status[3],Status_Detection);
ClrBit(KO_conf.status[3],Status_Retrigger);
ClrBit(KO_conf.status[3],Status_Walk_through);
ClrBit(KO_conf.status[3],Status_Maintain);
ClrBit(KO_conf.status[3],Status_Detection);

KO_conf.status[2] = Status_ON;
KO_conf.status[2] = Status_OFF;
KO_conf.status[2] = Status_OFF;
KO_conf.status[2] = Status_ON;
 */

/*
 ************************************************************************************************************
 ************************************************************************************************************
 */


//void _modality_0(void);
//void _modality_1(void);
//void _modality_2(void);
//void _modality_3(void);
//void _modality_4(void);
//void daylight_service(void);
//void regulation_diming(void);
//void frame_M2_answer( unsigned char type);
//unsigned char decode_frame_SCS(void);
void frame_presence(unsigned char arg);
void frame_dimming(char type,char cmd,char func0, char func1,char func2 ,char func3,char func4);
void Delay_Alert(void);
void Stop_allTimer(void);
void Start_Time_Delay(void);
void Call_detect_delay(void);
void WT_20s_detect(void);
void Check_SCS_received(void);
void function_check_status(void);
void GS_presence_send(void);
void frame_ON_send(void);
void frame_OFF_send(void);
void framesend_takeline(void);
void frame_pp_on_off( unsigned char command );
void occupancy_detect(void);
void _Initial_state(void);
void _Maintain_state(void);
void _ReTrigger_State(void);
void _Standby_state(void);
void Function_LM_GR(void);
void Function_KO119(void);
void Function_KO128(void);
void Function_KO164(void);
void Function_KO165(void);
void Function_KO166(char addrestype, char detectype, char LightReg);
void Function_KO168(char addrestype, char FuncMod, char LightReg);
void function_service_init(void);
void function_service(void);
void timer_interval_initial(unsigned long int ms);
void timer_5m_initial(unsigned long int ms);

#endif