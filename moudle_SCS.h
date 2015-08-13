#ifndef _MOUDLE_SCS_H
#define _MOUDLE_SCS_H
#define TRANS_DELAY 50							//too big cause PnG timing error, too small cause interface chip lost frames
//#define KO_SCENARIO_TRANS_DELAY 20
#define SCENARIO_NUMBER 16
#define NUM_KO_TOTAL 17
#define NUMBER_BYTE_SCS 20
#define FRAME_COMPLETE 1

#define PARAMETER_NUMBER 35
#define KO_NONE_CONF 515
//#define KOH			0									//key object
//#define KOL			168								//key object

#define PIPE_LINE_DEEP 1

#ifdef FINAL_VERSION2
	#define DEEP 10
#else
	#define DEEP 45
#endif

#define GROUP 2
#define PP  0

#define INDEX_MODE	0
#define INDEX_ADDRESSING_TYPE	1
#define INDEX_DES	2
#define INDEX_INSTALLATION_LEVEL 3
#define INDEX_DESTINATION_LEVEL 4
#define INDEX_REFERENCE 5
#define INDEX_HOURS 10
#define INDEX_MINUTES 11
#define INDEX_SECONDS 12
#define INDEX_PIR_SENSITIVITY 20
#define INDEX_US_SENSITIVITY 21
#define INDEX_DAY_LIGHT_SENSOR_ENABLE 23
#define INDEX_MOTION_SENSOR_ENABLE 24
#define INDEX_DAY_LIGHT_SET_POINT 25
//#define INDEX_PROVISION_OF_LIGHT 26;
#define INDEX_DAYLIGHT_LEVEL 27
#define INDEX_LIGHTING_REGULATION 28
#define INDEX_FUNCTIONAL_MODE 29
#define INDEX_INITIAL_OCCUPANCY 30
#define INDEX_MANTAIN_OCCYPANCY 31
//#define INDEX_RETRIGGER 32;
#define INDEX_RETRIGGER_DURATION 33
#define INDEX_VISUAL_ALERT 34
#define INDEX_ACUSTIC_ALERT 35
#define INDEX_AUTOMATIC_TRANSMISSION 36

// 86 Frame byte3
#define unavailable 0
#define HW_failure 1
#define WrongConf 2
#define SystemWiringFailure 3
#define PYH_conf 4
#define DeviceDisabled 5
#define ID_code 6
#define BasicAdvanceConf 7

//define normal
#define OK 0
//Key word defined
#define SYS 5
#define LEV 6
#define ARG 9

#define BASIC_PHYSICAL 0
#define BASIC_VIRTUAL 1
#define ADVANCED 2
#define NONE_CONFED 3

#define CONF_WRONG 4

#define NORMAL 0
#define STATE_NORMAL 0x0000
#define STATE_PRE_PROGRAMMING 0x1000
#define STATE_PROGRAMMING 0x2000
#define STATE_PROGRAMMING_DURING 0x2100
#define STATE_TEST 0x2001
#define STATE_TEST_DURING 0x2002
#define STATE_PRE_TEST 0x2003
#define PNL_NONE_CONFED_STEP1 0x9001
#define PNL_NONE_CONFED_STEP2 0x9002
#define PNL_NONE_CONFED_WAIT_FOR_GROUP_ASSIGN 0x9003
#define PNL_NONE_CONFED_STEP4 0x9004
#define PNL_NONE_CONFED_STEP5 0x9005
#define PNL_NONE_CONFED_STEP6 0x9006

#define PNL_AD_CONFED_STEP1 0x9007
#define PNL_AD_CONFED_STEP2 0x9008
#define PNL_AD_CONFED_STEP3 0x9009
#define PNL_AD_CONFED_STEP4 0x900A
#define PNL_AD_CONFED_STEP5 0x900B
#define PNL_AD_CONFED_STEP6 0x900C
#define PNL_AD_CONFED_STEP7 0x900D
#define PNL_AD_CONFED_STEP8 0x900E
#define PNL_AD_CONFED_STEP81 0x900F
#define PNL_AD_CONFED_STEP9 0x9010
#define PNL_AD_CONFED_STEP90 0x9011
//#define PNL_IR_SCENARIO_STEP1 0x9012
#define PNL_IR_SCENARIO_STEP2 0x9013
#define PNL_IR_SCENARIO_STEP21 0x9014
#define PNL_IR_SCENARIO_STEP3 0x9015
#define PNL_IR_SCENARIO_STEP4 0x9016
#define PNL_IR_SCENARIO_STEP7 0x9017
#define PNL_IR_SCENARIO_STEP8 0x9018
//for PNL group sensor
#define SENSOR_GROUP_STEP4 0x9019

#define NONE_TO_AD_STEP1 0x9020
#define NONE_TO_AD_STEP2 0x9021
#define NONE_TO_AD_STEP3 0x9022
#define NONE_TO_AD_STEP4 0x9023

#define SENSOR_NONE_CONFED_STEP3 0x9024
//none confed slave
#define SLAVE_STARTED 0x9025
#define ADD 0x9026
#define REMOVE 0x9027
#define ADD_THEN_REMOVE 0x9030
#define CONSTANT_LIGHT 0x9031
#define AD_TO_NONE_STEP2 0x9032

#define CALIBRATION 0x9033
#define FACTORY_CALIBRATION 0x9044
#define FACTORY_CALIBRATION_STEP1 0x9045
#define FACTORY_CALIBRATION_STEP2 0x9046

#define AFTER_REQUEST_ID 0x9047
#define FINAL_STEP1 0x9048
#define FINAL_STEP2 0x9049
#define FINAL_STEP3 0x904A
#define FINAL_STEP4 0x904B
#define FINAL_STEP5 0x904C

#define FINAL_STEP6 0x904D

#define FINAL_ID_STEP1 0x904E
#define FINAL_ID_STEP2 0x904F
#define FINAL_ID_STEP3 0x9050
#define FINAL_ID_STEP4 0x9051
#define FINAL_ID_STEP5 0x9052
#define FINAL_ID_STEP6 0x9053
#define FINAL_ID_STEP7 0x9054
#define FINAL_ID_STEP8 0x9055
#define FINAL_ID_STEP9 0x9056
#define FINAL_ID_STEP10 0x9057

#define AFTER_SETTING_ID 0x9058

#define INPUT_MODEL 0
#define INPUT_YEAR 1
#define INPUT_WEEK 2
#define INPUT_SOFTWARE_VERSION 3
#define INPUT_HARDWARE_VERSION 4

#define SENSOR_NONE_CONFED_SUB_STEP3 3
#define SENSOR_NONE_CONFED_SUB_STEP31 4
#define WAIT_END_PNL 5
#define AFTER_STEP1 6

#define STRUCT_SENSOR_LENGTH_BYTE 42

//PNL Group Started Status////////////////////////
#define START_PNL_GROUP_SENSOR 1
#define START_PNL_NONE_CONFED_GROUP_SENSOR 2
#define GR_EQUAL 3
/////////////////////////////////////////////////

#define CEN 1
#define NOT_CEN 0

//for Aux and Group frame
#define ON 1
#define OFF 2
#define DIM_STEP 3
#define GO_TO_LEVEL_TIME 4
#define ACTION 7
#define ERASE 8
#define DIMMER_STOP 9
#define DIM_UP 10
#define DIM_DOWN 11
#define LEVEL 12
//for group pnl
#define ANSWER '4'
#define REQUEST '3'
#define SET '2'
#define START_PNL '0'
#define GROUP_CONFIRM '1'
#define GROUP_REFUSE '2'
#define REF_TRANS '3'
#define GROUP_ERASE '4'
#define GROUP_REQUEST '5'
#define GROUP_ASSIGNATION '6'
#define GROUP_RELEASE '7'
#define NO_GROUP_AVAILABEL '8'
#define GROUP_USED_REQUEST '9'
#define DISABLE_LOAD_CONTROL 'A'
#define GROUP_END_PNL 'F'

#define UP 0
#define DOWN 1

//for ir group
#define IR_GROUP 2


//scs define
#define PAR_N 6
#define PAR_V 5
#define CHANNEL 7
#define BYTE1 5
#define BYTE2 6
#define BYTE3 7
//parameter answer define
#define PAR_NOT_IMPLEMENTED 0xFF00
#define PAR_OUT_OF_RANGE 0xFF01
//key object error define
#define NOT_IMPLEMENTED 0
#define BUSY 1
#define ASSIGNED_AGAIN 2
#define OUT_KO 4
//for IR scenario
#define OUT_RANGE 0xFF

struct struct_scs_frame
{
	unsigned char byte[21];
	unsigned char next;
	unsigned char finished;
	unsigned char decoded;
};

struct Spile_reception_SCS
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet re鐄
	unsigned char pipe[NUMBER_BYTE_SCS];             //
	unsigned char begin_actual;            ///< Si Nbre_Octet = 0 : la trame est vide
	unsigned char info;						///< bit 0 : 1:trame compl鑤e
};

struct sensor_information
{
	unsigned area:4;
	unsigned point_light:4;
	unsigned mode:4;
	unsigned :0;
};

struct SShortFrame
{
	unsigned char des[2];
	unsigned char loc[2];
	unsigned char cmd[2];
	unsigned char arg[2];
};

struct SExtendedFrame
{
	unsigned char Dx[2];

	unsigned char d1_d0[2];

	unsigned char d2_SYS[2];

	unsigned char lev_cmd[2];

	unsigned char type[2];
	unsigned char par_v[2];
	unsigned char par_n[2];
	unsigned char byte3[2];
};

struct SConfigurators
{
	unsigned char reserved;
	unsigned char A;					//  1~9  (0~A)0x
	unsigned char PL;					// 1~9   (0~F)0x
	unsigned char M;					//0~4	
	unsigned char S;					//0~3
	unsigned char T;					//0~9
};

struct SConf
{
	unsigned IDConfigurated :1;       //if the ID has beed configurated    o:no  1:yes.
	unsigned ConfMethod :1;   	    //basic or advanced       1:basic    0:advanced	
	unsigned ConfigurateEn :1;       //after receiving a frame of starting configuration,enable the configuration (advanced conf)	
	unsigned StandCen :1;		    			// 1 if standby  0 if centralize
	unsigned KOCodeChange :1;       // 1 if the kocode need to be changed or assigned
	unsigned Confed :1;		            // 0 if nonconfed 1 if configuration is done
	unsigned :2;
};

struct SKO_Configuration
{
	unsigned char reserved_0;
	unsigned char AddressType;
	unsigned char DesAdd;
	unsigned char reserved_3;
	unsigned char reserved_4;

	unsigned char Reference;
	unsigned char GR;
	unsigned char GS1;
	unsigned char GS2;
	unsigned char reserved_9;


	unsigned char Hours;
	unsigned char Minutes;
	unsigned char Seconds;
	unsigned char en_load;
	unsigned char en_GS_main_group;

	unsigned char reserved_15;
	unsigned char reserved_16;
	unsigned char reserved_17;
	unsigned char reserved_18;
	unsigned char reserved_19;

	unsigned char PirSens;
	unsigned char USSens;
	unsigned char DF;
	unsigned char TypeLoop;
	unsigned char NF;

	unsigned char DaylightSetp;
	unsigned char PofL;
	unsigned char DaylightLev;
	unsigned char LightReg;
	unsigned char FuncMod;

	unsigned char InitOccu;
	unsigned char MaintainOccu;
	unsigned char Retrigger;
	unsigned char reserved_33;
	unsigned char Alert;
	
	unsigned char DayLightLevLux[2];
	unsigned char Type[2];
	unsigned char ID1[2];
	unsigned char ID2[2];
	unsigned char FW_Version[2];
	unsigned char status[2];
	unsigned int KO_number;
	unsigned char flag_PofL_Forced:1; //reyno 0622
};

struct s_ns
{
	unsigned char id[3];
};

struct SState
{
	unsigned programming : 1;
	unsigned test : 1;
	unsigned normal : 1;
	unsigned configuration_method:2;
						//0 physical
						//1 physical virtual
						//2 advanced
	unsigned :1;
	unsigned test_configuration:1;
	unsigned id_setting:1;
	unsigned int main_state;
	unsigned char pnl_slave;
	unsigned IR_Trans:1;
};

struct Sframe_extended_type
{
	unsigned D0 : 1;
	unsigned D1 : 1;
	unsigned D2 : 1;
	unsigned D5 : 1;
	unsigned :4;
};

struct Skey_conf
{
	unsigned StandCen : 1;
	unsigned MotionEn : 1;
	unsigned DayLightEn :1;
	unsigned : 5;
};

struct Sproduct_info
{
	unsigned IDConfigurated :1;       //if the ID has beed configurated    o:no  1:yes.
	unsigned ConfMethod :1;   	    //basic or advanced       1:basic    0:advanced	
	unsigned ConfigurateEn :1;       //after receiving a frame of starting configuration,enable the configuration (advanced conf)	
	unsigned StandCen :1;		    			// 1 if standby  0 if centralize
	unsigned KOCodeChange :1;       // 1 if the kocode need to be changed or assigned
	unsigned Confed :1;		            // 0 if nonconfed 1 if configuration is done
	unsigned load_on_off : 1;				//load status
	unsigned :1;

	//unsigned int NonConfCode;
	//unsigned char A;
	//unsigned char PL;
	//unsigned char D2;
	//unsigned char channel;
};

struct Sflag_timer
{
	unsigned int timer0_rool;
	unsigned int timer0_top;
};

struct S_product_information
{
	//unsigned char confed;
	unsigned char conf_type;
								//0 physical
								//1 physical virtual
								//2 advanced
                //3 none_confed
	unsigned char ID_confed;
  unsigned char local_A;
  unsigned char local_PL;
  unsigned char cen_system;

  unsigned ID_factory_assigned:1;
	unsigned factory_calibrated:1;
};

struct Ukey_result
{
	unsigned char short_pressed;
	unsigned char long_pressed;
};

struct S_test
{
	unsigned char array_test[4];
};

struct s_flags
{
	unsigned id_confed:1;
	unsigned id_ack:1;
	unsigned id_request_enabled:1;
	unsigned request_83:1;
	unsigned diagnostic:1;
	unsigned png:1;
	unsigned virtul_configuration_right:1;
  unsigned load_status:1;

  //for IR diagnostic
  unsigned reserved1:1;
  unsigned dimmer_mode:1;
  unsigned detection:1;
  unsigned time_delay_during:1;
  unsigned walk_through_en:1;
  unsigned re_triger_en:1;
  unsigned exemption_en:1;
  unsigned regulation_en:1;

  //for pnl group
  unsigned group_assigned :1;
  //for davance configuration
  unsigned KO_conf_right:1;
  unsigned KO_erase_all:1;
  unsigned KO_erase_main:1;
  unsigned KO_erase_scenario:1;
  unsigned confed:1;
  unsigned scenario_scs_confed:1;
  unsigned parameter_write_right:1;
	//for group sensor
	unsigned scs_pnl_group_sensor_starded:1;
	unsigned wait_GS_remove:1;
	unsigned pp_link:1;
	
	unsigned conflict:1;
	unsigned ir_buzzer:1;
	unsigned app_disable:1;
	unsigned AA_received:1;
	unsigned scenario_last_assigned:1;
	
	unsigned modality0_initialed:1;
	unsigned parameter_setting_wrong:1;
	
	//for application
	unsigned pp_off_received;
	unsigned factory_calibration_started:1;
	unsigned motion_detected:1;
	unsigned timer_started:1;
	unsigned led_on_double;
	unsigned dimmer_started:1;
	unsigned M2_step2_started:1;
	unsigned one_procedure_started:1;
	unsigned dimmer_ON_sended:1;
	unsigned KO_128_first_sampel_ready:1;
};

struct s_parameters
{
	unsigned char dimmer_value;
};

struct s_scenario
{
	unsigned char ns_number;
	unsigned char reg_type;
	unsigned char id[3];
	unsigned char key_number;
  unsigned char confed;
};

struct s_parameter
{
  unsigned char device_modle[6];
	unsigned char software_version[6];
	unsigned char hardware_version[6];
};

struct s_temp_variable
{
  unsigned long int scenario_id;
  unsigned char scenario_ns;
  unsigned char erase_KO_scenario;
  unsigned char conf_KO_scenario;
  unsigned char configurators[7];
	unsigned char GR;
	unsigned long int ID;
	unsigned char DesAdd;
};

struct s_ee_flags
{
  unsigned manual_initialize:1;
	unsigned PnG_confed:1;
	unsigned ID_confed:1;
};

struct s_flags_muti_step
{
  unsigned char cen_system_step;
};

struct s_ee_variable
{
	unsigned char GR;
	unsigned char Reference;
};

struct s_factory_variable
{
	unsigned int adc_1;
	unsigned int adc_2;
	unsigned int lux_1;
	unsigned int lux_2;
};

/****************	add by alan begin	**************************/
struct SSCS_received
{
	unsigned char presence:1;			//B|5 G|G 1|D 0|0
	unsigned char no_presence:1;			//B|5 G|G 1|D 0|1
	unsigned char GS_presence:1;
	unsigned char GR_ON:1;				//B|5 G|G 1|2 0|0
	unsigned char GR_OFF:1;				//B|5 G|G 1|2 0|1
	unsigned char GR_DIM:1;				//B|5 G|G 1|2 0|1
	unsigned char P2P_ON:1;				//D1 A|Pl 0|1 4|2 0|D 0|0 0|0 0|0 			
	unsigned char update_state_ON:1;		//B|8 A|Pl 1|2 0|0
	unsigned char update_state_OFF:1;		//B|8 A|Pl 1|2 0|1
	unsigned char update_state_LEVEL:1;		//B|8 A|Pl 1|2 D|4
	unsigned char  update_on_wait:2;		//0519
	unsigned char  update_off_wait:2;		//0519
	
	unsigned char presence_2_ON:1;
	unsigned char nopresence_2_OFF:1;
	volatile unsigned char P2P_actuator_flag:1;
	volatile unsigned char P2P_dimmer_flag:1;
	unsigned char P2P_dimmer_full:1;
	unsigned char P2P_dimmer_zero:1;

	unsigned char Manual_ON:1;
	unsigned char Manual_OFF:1;
	unsigned char motion_detect:1;
		
	
	// 以下数据帧用于modality
	unsigned char modality_time_set:1; 			// D1 00 01 42 16 XX XX XX
	unsigned char modality_time_request:1; 		// D2 00 01 43 16 00 00 00
	unsigned char modality_lux_request:1; 		// D1 APL 01 43 10 00 00 00
	unsigned char modality_sensitivity_set:1; 	// D1 00 01 42 15 00 00 xx
	unsigned char modality_sensitivity_request:1; 	// D1 00 01 42 15 00 00 00

	unsigned char	setpoint_low:1;
	unsigned char	setpoint_high:1;
      unsigned char	setpoint_medium:1;
	unsigned char 	Daylight_lux:1;	
	unsigned char  calib_wait:1;		//0519
	//unsigned char  calib_exit:1;		//0519
	
};			// the flag for frame that have received


struct SSensor_mode
{
 	unsigned char 		mode_state;
  unsigned char 		modality_state;
  unsigned char 		detect_scheme;
  unsigned int  		presence_20sinterval;

 	unsigned char 		regulation_EN:1;
 	unsigned char 		flag_leader_group:1;
 		
 	unsigned char			presence_send:1;
	unsigned char			presen_timeout:1;
	unsigned char   	end_dection:1;			// 标志位表明已经处理过end detection程序
 	unsigned char   	no_prence_off_send:1;

 	unsigned char			manual_on_need:1;
	unsigned char   	random_takeline; //reyno 0609
	unsigned char   	ON_takeline_waitsend:1;
	unsigned char   	OFF_takeline_waitsend:1;
	unsigned char   	motion_initial_detect:2;
	unsigned char 		maintain_pre:1;
	unsigned char   	power_on_flag:1;
	unsigned char			LightReg_flag:1;
	unsigned char			init_OK:1;
	unsigned int temp0;		// debug 0527
		
};	

struct S_sensor_info
{
	unsigned char start[2];
	unsigned char date[5]; //"0950";
	unsigned char id[9]; //"00050000";
	unsigned char device_model[4]; //"020";
	unsigned char brand[3]; //"2";
	unsigned char hardware_version[3];//"01";
	unsigned char software_version[7];//"010600";
	unsigned char gateway_version[7];// "040523";
	unsigned char end[2];
};
/****************	add by alan end	**************************/
struct S_usb_command
{
	unsigned char start;
	unsigned char pipe[8];
	unsigned char next;
	unsigned char decoded;
};
#endif
