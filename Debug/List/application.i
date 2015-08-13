#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.h"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"



//#define KO_SCENARIO_TRANS_DELAY 20







//#define KOH			0									//key object
//#define KOL			168								//key object







#line 35 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"
//#define INDEX_PROVISION_OF_LIGHT 26;





//#define INDEX_RETRIGGER 32;





// 86 Frame byte3
#line 56 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"

//define normal

//Key word defined











#line 85 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"

#line 97 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"
//#define PNL_IR_SCENARIO_STEP1 0x9012
#line 104 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"
//for PNL group sensor








//none confed slave
#line 120 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"








//PNL Group Started Status////////////////////////



/////////////////////////////////////////////////




//for Aux and Group frame
#line 144 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"
//for group pnl
#line 160 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"




//for ir group



//scs define
#line 175 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\moudle_SCS.h"
//parameter answer define


//key object error define




//for IR scenario


struct struct_scs_frame
{
	unsigned char byte[21];
	unsigned char next;
	unsigned char finished;
	unsigned char decoded;
};

struct Spile_reception_SCS
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet re�u
	unsigned char pipe[20];             //
	unsigned char begin_actual;            ///< Si Nbre_Octet = 0 : la trame est vide
	unsigned char info;						///< bit 0 : 1:trame compl�te
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
	unsigned char reserved_24;

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
		
	
	// ��������֡����modality
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
	unsigned char   	end_dection:1;			// ��־λ�����Ѿ������end detection����
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

/****************	add by alan end	**************************/
#line 4 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.h"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\IR.h"






struct SIR_reception
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet re�u
	unsigned char pipe[14];             //
	unsigned char begin_actual;            ///< Si Nbre_Octet = 0 : la trame est vide
	unsigned char info;						///< bit 0 : 1:trame compl�te
	unsigned char finished;
	unsigned char CRC_OK;
};

void init_USART1();
// USART Transmitter buffer


unsigned char _calculate_crc(unsigned char data, unsigned char crc);
void put_s1(unsigned char *ptr, unsigned char end_pipe);
void timer_IR_initial(unsigned long int ms);
void decode_IR();
void ir_buffer_clear(void);
unsigned char ir_pnl(void);
void IR_36kHz(void);
void close_IR_36kHz(void);
void setting_diagnostic_ir(unsigned char *data);
unsigned char get_current_scenario_number(void);
unsigned char is_scenario_full(void);

#line 5 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.h"
// main
extern unsigned char g_timer2_flag;
extern unsigned char g_temp;
extern volatile void global_variable_initial();
extern volatile unsigned char g_configurator[5];

extern volatile struct struct_scs_frame scs_frame[10];
extern __eeprom struct SKO_Configuration ee_KO_conf;
//extern __eeprom struct SKO_Configuration ee_PnG_KO_conf;
extern volatile struct SConfigurators Configurators;
extern volatile struct SKO_Configuration KO_conf;
//extern struct SKO_Configuration temp_KO_conf;
extern __eeprom volatile unsigned char ee_ID[9];
extern __eeprom unsigned char ee_pre_ID[4];
extern volatile struct SState state;
extern volatile struct Sframe_extended_type frame_extended_type;
extern __eeprom struct SConfigurators ee_configurators;
extern volatile unsigned char g_reception_buffer[17];
extern volatile unsigned char g_asc_reception_buffer[8];
extern volatile unsigned char g_short_buffer[8];
extern volatile unsigned char g_asc_short_buffer[4];
extern volatile struct Sproduct_info product_info;
extern volatile struct SIR_reception IR_reception;
extern volatile struct Sflag_timer flag_timer;
extern volatile struct SDll DLL;
extern volatile struct STimeDelay Time_delay;
extern volatile struct PIR pir;
extern volatile unsigned int pir_total;
extern volatile unsigned char us_result;
extern volatile unsigned char us_total;
extern volatile unsigned int motion_total;
extern volatile unsigned char US_detection_en;
extern volatile unsigned long int modality0_delay_ms;
extern volatile unsigned char g_key_value;
extern volatile unsigned char g_virtual_basci_configuration_flag;
extern __eeprom struct S_product_information ee_product_information;
extern const int daylight_motion[];
extern const int daylight[];
extern const int motion[];
extern volatile struct Ukey_result key_result;
extern __eeprom unsigned char g_ns_index;
extern volatile unsigned char g_ir_reception[];
extern volatile struct s_flags flags;
extern volatile unsigned char PIR_detection_en;   // add by alan 20090409

extern __flash struct SKO_Configuration flash_KO_168;
extern __flash struct SKO_Configuration flash_KO_166;
extern __flash struct SKO_Configuration flash_KO_119;
extern __flash struct SKO_Configuration flash_KO_128;
extern __flash struct SKO_Configuration flash_KO_165;
extern __flash struct SKO_Configuration flash_KO_515;

extern volatile char tx1_buffer[14];
extern volatile unsigned char tx1_wr_index,tx1_rd_index,tx1_counter;

extern struct S_product_information product_information;
extern struct S_product_information temp_product_information;
extern volatile unsigned char KO[];
extern struct s_parameters parameters;

extern const unsigned char flash_KO[];

extern struct s_temp_variable temp_variable;
extern struct s_flags_muti_step flags_muti_step;

extern __eeprom struct s_ee_flags ee_flags;
extern __eeprom unsigned char ee_KO_last[];
extern __eeprom unsigned char ee_KO[];
extern __eeprom struct s_parameter ee_parameter;


extern __eeprom unsigned char ee_scenario_index;
//extern struct S_ir_scenario ir_scenario __attribute__((section(".eeprom")));
//extern struct s_ns ee_ns __attribute__((section(".eeprom")));
extern __eeprom struct S_test only_test;

extern __eeprom struct s_scenario  ee_scenario[16];
extern __eeprom struct S_product_information ee_product_information;
extern __eeprom struct s_ee_variable ee_variable;

// add by alan begin

extern __eeprom unsigned int eep_setpoint[4];
extern __eeprom unsigned int eep_factor;
extern __eeprom unsigned char eep_M2_hour;	
extern __eeprom unsigned char eep_M2_min;	
extern __eeprom unsigned char eep_M2_sec;
extern __eeprom unsigned char eep_M2_sens;
extern  unsigned long int   M2_timer;
extern  unsigned long int   M2_timer_count;
extern  unsigned char M2_type;
extern 	unsigned char  motion_resutl;
volatile  	extern unsigned long int Delay_Time_set;
extern 	unsigned int  set_point;
extern 	unsigned char during_on_cnt;
extern 	unsigned char during_off_cnt;
extern 	unsigned char Walk_Through_flag;
extern 	unsigned char First_detection_enable;
extern	struct	SSCS_received SCS_received;
extern	struct 	SSensor_mode Sensor_mode;

// add by alan end
#line 2 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.h"





struct SDll
{
   unsigned char  getlevel_finish;
   unsigned char  daylight_SampleCount;          //  Individual Sample Counter

   unsigned int   daylight_SampleValue;          //  Add Sensor Sample Value (to be averaged once desired sample have been taken)
   //unsigned int  Daylight_SampleVales[Daylight_HISAVESAMP_BUF];
   volatile unsigned int  read_daylightSample;

   unsigned int   day_level;
   unsigned int   last_day_level;
   unsigned int   loadoff_level;
   unsigned int   loadon_level;
   unsigned int   load_provision;
   unsigned int   current_level;
   unsigned int   calc_level;
   unsigned int   setpoint_OFF;         // used for actuaotr regulation 0715

  // unsigned char    daylevelsenden;   // ����modality2,ÿ���5min����һ֡���ݣ����߹����ȱ仯����3%ʱ�����̷���daylevel����֡


   unsigned char    first_detect;
/********************************************************************/
// Add by alan for the daylight level set start
/********************************************************************/
  unsigned char   calc_OK_flag;         //20090302
  unsigned int    setpoint_H;           // ��ʱ����


  unsigned int    setpoint_L;
  unsigned int    setpoint_M;



  unsigned int    DF;

  volatile unsigned long int open_lightlux;
  unsigned  int   open_lightlevel;
  unsigned  int   open_actualevel;
  unsigned  char  open_offset;

  unsigned char   Dim_T200ms;
  unsigned int    Dim_T06s;
  unsigned int    lightness_load;
  unsigned int    PLv_5s;
  unsigned int    PLv_5min;
  double          read_lux;







/********************************************************************/
// Add by alan for the daylight level set end
/********************************************************************/
  unsigned char start_regulation:1;
};

struct STimerPoint
{
	unsigned long int count;
	unsigned long int stack_top;
	unsigned char time_out;
	unsigned char enabled;
	unsigned char started;
	//unsigned : 5;
};

struct STimeDelay
{	
	unsigned char    Re_Trigger_senconds;
	unsigned int  	Walk_Through_Timeout;
	unsigned char    Regulation_Timeout;
	unsigned int    random_time;
	
	unsigned char   Time_Delay_over:1;
	unsigned char   Re_Trigger_over:1;
	unsigned char   Walk_Through_over:1;
	unsigned char   Regulation_Timeout_over:1;	

// add by alan begin
  unsigned char		Dim_inc_enable:1;
  unsigned char		Dim_dec_enable:1;
  unsigned char 	DLL_low_20s_enable:1;
  unsigned char 	DLL_high_10min_enable:1;
	unsigned char 	pir_warmup_ok:1;
		
	unsigned int  	pir_wait_40s;
	unsigned char		GS_wait_22s;
	unsigned int  	detect_waitting;
	unsigned int		Dim_inc_count;
	unsigned int		Dim_dec_count;
	unsigned int  	DLL_low_20s_count;
	unsigned long int  DLL_high_10min_count;

  unsigned char   timer0_compa_flag;
  unsigned int    timer0_compa_cnt;

	struct STimerPoint timer_delay_set;
	struct STimerPoint timer_takeline;
	struct STimerPoint frame_200ms;
	unsigned int	second_OK;
	
// add by alan end
	
	//unsigned char time_out_06s;
	//unsigned int  time_out_20s;
	struct STimerPoint timer_1s;
	struct STimerPoint timer_5m;
	struct STimerPoint timer_20s;
	struct STimerPoint modality0;

	//used for 10s time out
	struct STimerPoint timer_10s;
	struct STimerPoint LPB;

	//used for LED blinking
	struct STimerPoint led_on;
	struct STimerPoint led_off;

	struct STimerPoint timer_flex;
  struct STimerPoint led_blink;
  struct STimerPoint buzzer;
	struct STimerPoint blinking_count;
	struct STimerPoint pnl_stage2;
	struct STimerPoint timer_flex2;
	struct STimerPoint Dled;
	struct STimerPoint IR;
	//reyno 0622
	struct STimerPoint regulation;
	struct STimerPoint GS_200ms;
};


void load_default_parameter(void);
void remember_parameter();
void ID_setting(unsigned char *data);
void diagnostic_frame(void);
//void send_frame_pp_ext_broad(unsigned char *data, unsigned int ms);
//void send_frame_pp_broad(unsigned char *data, unsigned int ms);
//void send_frame_pp(struct SExtendedFrame *data, unsigned int ms);
void us_detection(void);
void ultWarmUpEvents( void );
void get_dl_level(void);
void daylight_initial(void);
void service_daylight(void);
void timer2_enable(void);
unsigned char get_us(void);
unsigned char motion_detect(unsigned char mode);
void load_update(unsigned char status);
unsigned char scs_pnl_advance_master(void);
void scs_pnl_none_confed_master(void);
void scs_pnl_advance_slave(void);
void scs_advance_from_none_confed(void);
unsigned char scs_pnl_none_confed_slave(void);
void button_press_detect(void);
void button_release_detect(void);
void key_time_clear(void);
void led_blinking(unsigned long int on_ms, unsigned long int off_ms);
void led_blinking_ms(unsigned long int on_ms,unsigned long int off_ms, unsigned long int period);
void Dled_light_on_ms(unsigned long int on_ms);
void led_blinking_disable(unsigned char state);
void configuration_answer_frame(unsigned char value);
void timer_flex_initial(unsigned long int ms);
void timer_flex2_initial(unsigned long int ms);
void all_reception_buffer_clear(void);
void manual_reception_buffer_clear(void);
void start_conf(void);
void factory_default(void);
void configurator_to_KO(void);
void service_main(void);
void led_status_recover(void);
void frame_send_disable_automatic_control(void);
void frame_send_enable_automatic_control(void);
void frame_send_start_pnl_none_group_confed(void);
void frame_send_start_pnl_group_confed(void);
void frame_send_end_pnl(void);
void frame_send_group_request(void);
void led_blinking_normal(void);
void load_default_advance_parameter(void);
void led_blinking_stage2_initial(unsigned long int ms);
void PnL_ad_end(void);
void PnL_NONE_end(void);

// add by alan 20090408 start

#line 200 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.h"

#line 209 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.h"

void timer0_enable(void);
void daylight_set_init(void);
void Dimmer_dec(void);
void Dimmer_regulation(void);
void Actuator_regulation(void);
void Light_regulation(void);
void real_daylight_calc(void);
void PofL_calc(void);
void daylight_service(void);
void DLL_setpoint(unsigned char point);
unsigned int factor_divcalc(unsigned int x,unsigned int y);
unsigned int factor_mulcalc(unsigned int x,unsigned int y);	//result = x*y	y��factor,xx.xx,С�������λ
void frame_M2_answer( unsigned char type);
void Mode_frame_GR(char GG, char type);
void Mode_frame_P2P(char type,char cmd,char func0, char func1,char func2 ,char func3,char func4);
void regulation_timer_initial(void);

// add by alan 20090408 end


//		(un-corrected value * D.F - PfL*ratio) / D.F + PfL*ratio
//		un-corrected value + PfL(D.F - 1)

//		(un-corrected value * D.F - PfL) / D.F + PfL
//		un-corrected value - PfL / D.F + PfL
#line 3 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\ioavr.h"
/**************************************************************
 **             - IO_AVR.H -
 **
 **     I/O definitions for iccAVR
 **
 **     Used with iccAVR.
 **
 **     Copyright IAR Systems 2001. All rights reserved.
 **
 **     File version: $Revision: 1.33 $
 **
 **************************************************************/



#pragma system_include



#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"
/****************************************************************************
 **             - iom644p.h -
 **
 **     This file declares the internal register addresses for ATmega644P.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 2005. All rights reserved.
 **
 **     File version: $Revision: 1.4 $
 **
 ***************************************************************************/



#pragma system_include



#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"
/**************************************************************
 **             - iomacro.h -
 **
 **     This file defines the Special Function Register Macros
 **     for Atmel AT90S.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 1999 - 2005. All rights reserved.
 **
 **     File version: $Revision: 1.28 $
 **
 **************************************************************/



#pragma system_include












/* The assembler uses a special set of macros... */
#line 187 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 199 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 207 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 219 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 232 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 244 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 263 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 282 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 290 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 298 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 311 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 335 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 344 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 356 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



  
#line 376 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"
  
#line 393 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 411 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 429 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 447 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 464 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 491 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 518 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 546 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 574 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 601 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 626 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 653 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 677 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 705 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 746 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 787 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 826 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 940 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



/*
  SFR_B(SREG,   0x3F) Expands to:
  __io union {
              unsigned char   SREG;          // The sfrb as 1 byte
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_Bit0:1,
                                    SREG_Bit1:1,
                                    SREG_Bit2:1,
                                    SREG_Bit3:1,
                                    SREG_Bit4:1,
                                    SREG_Bit5:1,
                                    SREG_Bit6:1,
                                    SREG_Bit7:1;
                     };
             } @ 0x3F;
*/




/*
  SFR_B_N(0x3F,SREG,I,T,H,S,V,N,Z,C) Expands to:
  __io union {
              unsigned char   SREG;          // The sfrb as 1 byte
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_Bit0:1,
                                    SREG_Bit1:1,
                                    SREG_Bit2:1,
                                    SREG_Bit3:1,
                                    SREG_Bit4:1,
                                    SREG_Bit5:1,
                                    SREG_Bit6:1,
                                    SREG_Bit7:1;
                     };
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_C:1,
                                    SREG_Z:1,
                                    SREG_N:1,
                                    SREG_V:1,
                                    SREG_S:1,
                                    SREG_H:1,
                                    SREG_T:1,
                                    SREG_I:1;
                     };
             } @ 0x3F;
*/
#line 1015 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"








#line 1054 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 1087 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"




#line 1139 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 21 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"









/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */


#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

__io union { unsigned char UDR1; struct { unsigned char UDR1_Bit0:1, UDR1_Bit1:1, UDR1_Bit2:1, UDR1_Bit3:1, UDR1_Bit4:1, UDR1_Bit5:1, UDR1_Bit6:1, UDR1_Bit7:1; }; } @ 0xCE;
__io union { unsigned short UBRR1; struct { unsigned char UBRR1_Bit0:1, UBRR1_Bit1:1, UBRR1_Bit2:1, UBRR1_Bit3:1, UBRR1_Bit4:1, UBRR1_Bit5:1, UBRR1_Bit6:1, UBRR1_Bit7:1; unsigned char UBRR1_Bit8:1, UBRR1_Bit9:1, UBRR1_Bit10:1, UBRR1_Bit11:1, UBRR1_Bit12:1, UBRR1_Bit13:1, UBRR1_Bit14:1, UBRR1_Bit15:1; }; struct { unsigned char UBRR1L; unsigned char UBRR1H; }; struct { unsigned char UBRR1L_Bit0:1, UBRR1L_Bit1:1, UBRR1L_Bit2:1, UBRR1L_Bit3:1, UBRR1L_Bit4:1, UBRR1L_Bit5:1, UBRR1L_Bit6:1, UBRR1L_Bit7:1; unsigned char UBRR1H_Bit0:1, UBRR1H_Bit1:1, UBRR1H_Bit2:1, UBRR1H_Bit3:1, UBRR1H_Bit4:1, UBRR1H_Bit5:1, UBRR1H_Bit6:1, UBRR1H_Bit7:1; }; } @ 0xCC;
__io union { unsigned char UCSR1C; struct { unsigned char UCSR1C_Bit0:1, UCSR1C_Bit1:1, UCSR1C_Bit2:1, UCSR1C_Bit3:1, UCSR1C_Bit4:1, UCSR1C_Bit5:1, UCSR1C_Bit6:1, UCSR1C_Bit7:1; }; struct { unsigned char UCSR1C_UCPOL1:1, UCSR1C_UCSZ10:1, UCSR1C_UCSZ11:1, UCSR1C_USBS1:1, UCSR1C_UPM10:1, UCSR1C_UPM11:1, UCSR1C_UMSEL10:1, UCSR1C_UMSEL11:1; }; } @ 0xCA;
__io union { unsigned char UCSR1B; struct { unsigned char UCSR1B_Bit0:1, UCSR1B_Bit1:1, UCSR1B_Bit2:1, UCSR1B_Bit3:1, UCSR1B_Bit4:1, UCSR1B_Bit5:1, UCSR1B_Bit6:1, UCSR1B_Bit7:1; }; struct { unsigned char UCSR1B_TXB81:1, UCSR1B_RXB81:1, UCSR1B_UCSZ12:1, UCSR1B_TXEN1:1, UCSR1B_RXEN1:1, UCSR1B_UDRIE1:1, UCSR1B_TXCIE1:1, UCSR1B_RXCIE1:1; }; } @ 0xC9;
__io union { unsigned char UCSR1A; struct { unsigned char UCSR1A_Bit0:1, UCSR1A_Bit1:1, UCSR1A_Bit2:1, UCSR1A_Bit3:1, UCSR1A_Bit4:1, UCSR1A_Bit5:1, UCSR1A_Bit6:1, UCSR1A_Bit7:1; }; struct { unsigned char UCSR1A_MPCM1:1, UCSR1A_U2X1:1, UCSR1A_UPE1:1, UCSR1A_DOR1:1, UCSR1A_FE1:1, UCSR1A_UDRE1:1, UCSR1A_TXC1:1, UCSR1A_RXC1:1; }; } @ 0xC8;
__io union { unsigned char UDR0; struct { unsigned char UDR0_Bit0:1, UDR0_Bit1:1, UDR0_Bit2:1, UDR0_Bit3:1, UDR0_Bit4:1, UDR0_Bit5:1, UDR0_Bit6:1, UDR0_Bit7:1; }; } @ 0xC6;
__io union { unsigned short UBRR0; struct { unsigned char UBRR0_Bit0:1, UBRR0_Bit1:1, UBRR0_Bit2:1, UBRR0_Bit3:1, UBRR0_Bit4:1, UBRR0_Bit5:1, UBRR0_Bit6:1, UBRR0_Bit7:1; unsigned char UBRR0_Bit8:1, UBRR0_Bit9:1, UBRR0_Bit10:1, UBRR0_Bit11:1, UBRR0_Bit12:1, UBRR0_Bit13:1, UBRR0_Bit14:1, UBRR0_Bit15:1; }; struct { unsigned char UBRR0L; unsigned char UBRR0H; }; struct { unsigned char UBRR0L_Bit0:1, UBRR0L_Bit1:1, UBRR0L_Bit2:1, UBRR0L_Bit3:1, UBRR0L_Bit4:1, UBRR0L_Bit5:1, UBRR0L_Bit6:1, UBRR0L_Bit7:1; unsigned char UBRR0H_Bit0:1, UBRR0H_Bit1:1, UBRR0H_Bit2:1, UBRR0H_Bit3:1, UBRR0H_Bit4:1, UBRR0H_Bit5:1, UBRR0H_Bit6:1, UBRR0H_Bit7:1; }; } @ 0xC4;
__io union { unsigned char UCSR0C; struct { unsigned char UCSR0C_Bit0:1, UCSR0C_Bit1:1, UCSR0C_Bit2:1, UCSR0C_Bit3:1, UCSR0C_Bit4:1, UCSR0C_Bit5:1, UCSR0C_Bit6:1, UCSR0C_Bit7:1; }; struct { unsigned char UCSR0C_UCPOL0:1, UCSR0C_UCSZ00:1, UCSR0C_UCSZ01:1, UCSR0C_USBS0:1, UCSR0C_UPM00:1, UCSR0C_UPM01:1, UCSR0C_UMSEL00:1, UCSR0C_UMSEL01:1; }; } @ 0xC2;
__io union { unsigned char UCSR0B; struct { unsigned char UCSR0B_Bit0:1, UCSR0B_Bit1:1, UCSR0B_Bit2:1, UCSR0B_Bit3:1, UCSR0B_Bit4:1, UCSR0B_Bit5:1, UCSR0B_Bit6:1, UCSR0B_Bit7:1; }; struct { unsigned char UCSR0B_TXB80:1, UCSR0B_RXB80:1, UCSR0B_UCSZ02:1, UCSR0B_TXEN0:1, UCSR0B_RXEN0:1, UCSR0B_UDRIE0:1, UCSR0B_TXCIE0:1, UCSR0B_RXCIE0:1; }; } @ 0xC1;
__io union { unsigned char UCSR0A; struct { unsigned char UCSR0A_Bit0:1, UCSR0A_Bit1:1, UCSR0A_Bit2:1, UCSR0A_Bit3:1, UCSR0A_Bit4:1, UCSR0A_Bit5:1, UCSR0A_Bit6:1, UCSR0A_Bit7:1; }; struct { unsigned char UCSR0A_MPCM0:1, UCSR0A_U2X0:1, UCSR0A_UPE0:1, UCSR0A_DOR0:1, UCSR0A_FE0:1, UCSR0A_UDRE0:1, UCSR0A_TXC0:1, UCSR0A_RXC0:1; }; } @ 0xC0;
__io union { unsigned char TWAM; struct { unsigned char TWAM_Bit0:1, TWAM_Bit1:1, TWAM_Bit2:1, TWAM_Bit3:1, TWAM_Bit4:1, TWAM_Bit5:1, TWAM_Bit6:1, TWAM_Bit7:1; }; struct { unsigned char TWAM_Dummy0:1, TWAM_TWAM0:1, TWAM_TWAM1:1, TWAM_TWAM2:1, TWAM_TWAM3:1, TWAM_TWAM4:1, TWAM_TWAM5:1, TWAM_TWAM6:1; }; } @ 0xBD;
__io union { unsigned char TWCR; struct { unsigned char TWCR_Bit0:1, TWCR_Bit1:1, TWCR_Bit2:1, TWCR_Bit3:1, TWCR_Bit4:1, TWCR_Bit5:1, TWCR_Bit6:1, TWCR_Bit7:1; }; struct { unsigned char TWCR_TWIE:1, TWCR_Dummy1:1, TWCR_TWEN:1, TWCR_TWWC:1, TWCR_TWSTO:1, TWCR_TWSTA:1, TWCR_TWEA:1, TWCR_TWINT:1; }; } @ 0xBC;
__io union { unsigned char TWDR; struct { unsigned char TWDR_Bit0:1, TWDR_Bit1:1, TWDR_Bit2:1, TWDR_Bit3:1, TWDR_Bit4:1, TWDR_Bit5:1, TWDR_Bit6:1, TWDR_Bit7:1; }; } @ 0xBB;
__io union { unsigned char TWAR; struct { unsigned char TWAR_Bit0:1, TWAR_Bit1:1, TWAR_Bit2:1, TWAR_Bit3:1, TWAR_Bit4:1, TWAR_Bit5:1, TWAR_Bit6:1, TWAR_Bit7:1; }; struct { unsigned char TWAR_TWGCE:1, TWAR_TWA0:1, TWAR_TWA1:1, TWAR_TWA2:1, TWAR_TWA3:1, TWAR_TWA4:1, TWAR_TWA5:1, TWAR_TWA6:1; }; } @ 0xBA;
__io union { unsigned char TWSR; struct { unsigned char TWSR_Bit0:1, TWSR_Bit1:1, TWSR_Bit2:1, TWSR_Bit3:1, TWSR_Bit4:1, TWSR_Bit5:1, TWSR_Bit6:1, TWSR_Bit7:1; }; struct { unsigned char TWSR_TWPS0:1, TWSR_TWPS1:1, TWSR_Dummy2:1, TWSR_TWS3:1, TWSR_TWS4:1, TWSR_TWS5:1, TWSR_TWS6:1, TWSR_TWS7:1; }; } @ 0xB9;
__io union { unsigned char TWBR; struct { unsigned char TWBR_Bit0:1, TWBR_Bit1:1, TWBR_Bit2:1, TWBR_Bit3:1, TWBR_Bit4:1, TWBR_Bit5:1, TWBR_Bit6:1, TWBR_Bit7:1; }; } @ 0xB8;
__io union { unsigned char ASSR; struct { unsigned char ASSR_Bit0:1, ASSR_Bit1:1, ASSR_Bit2:1, ASSR_Bit3:1, ASSR_Bit4:1, ASSR_Bit5:1, ASSR_Bit6:1, ASSR_Bit7:1; }; struct { unsigned char ASSR_TCR2BUB:1, ASSR_TCR2AUB:1, ASSR_OCR2BUB:1, ASSR_OCR2AUB:1, ASSR_TCN2UB:1, ASSR_AS2:1, ASSR_EXCLK:1, ASSR_Dummy7:1; }; } @ 0xB6;
__io union { unsigned char OCR2B; struct { unsigned char OCR2B_Bit0:1, OCR2B_Bit1:1, OCR2B_Bit2:1, OCR2B_Bit3:1, OCR2B_Bit4:1, OCR2B_Bit5:1, OCR2B_Bit6:1, OCR2B_Bit7:1; }; } @ 0xB4;
__io union { unsigned char OCR2A; struct { unsigned char OCR2A_Bit0:1, OCR2A_Bit1:1, OCR2A_Bit2:1, OCR2A_Bit3:1, OCR2A_Bit4:1, OCR2A_Bit5:1, OCR2A_Bit6:1, OCR2A_Bit7:1; }; } @ 0xB3;
__io union { unsigned char TCNT2; struct { unsigned char TCNT2_Bit0:1, TCNT2_Bit1:1, TCNT2_Bit2:1, TCNT2_Bit3:1, TCNT2_Bit4:1, TCNT2_Bit5:1, TCNT2_Bit6:1, TCNT2_Bit7:1; }; } @ 0xB2;
__io union { unsigned char TCCR2B; struct { unsigned char TCCR2B_Bit0:1, TCCR2B_Bit1:1, TCCR2B_Bit2:1, TCCR2B_Bit3:1, TCCR2B_Bit4:1, TCCR2B_Bit5:1, TCCR2B_Bit6:1, TCCR2B_Bit7:1; }; struct { unsigned char TCCR2B_CS20:1, TCCR2B_CS21:1, TCCR2B_CS22:1, TCCR2B_WGM22:1, TCCR2B_Dummy4:1, TCCR2B_Dummy5:1, TCCR2B_FOC2B:1, TCCR2B_FOC2A:1; }; } @ 0xB1;
__io union { unsigned char TCCR2A; struct { unsigned char TCCR2A_Bit0:1, TCCR2A_Bit1:1, TCCR2A_Bit2:1, TCCR2A_Bit3:1, TCCR2A_Bit4:1, TCCR2A_Bit5:1, TCCR2A_Bit6:1, TCCR2A_Bit7:1; }; struct { unsigned char TCCR2A_WGM20:1, TCCR2A_WGM21:1, TCCR2A_Dummy2:1, TCCR2A_Dummy3:1, TCCR2A_COM2B0:1, TCCR2A_COM2B1:1, TCCR2A_COM2A0:1, TCCR2A_COM2A1:1; }; } @ 0xB0;
__io union { unsigned short OCR1B; struct { unsigned char OCR1B_Bit0:1, OCR1B_Bit1:1, OCR1B_Bit2:1, OCR1B_Bit3:1, OCR1B_Bit4:1, OCR1B_Bit5:1, OCR1B_Bit6:1, OCR1B_Bit7:1; unsigned char OCR1B_Bit8:1, OCR1B_Bit9:1, OCR1B_Bit10:1, OCR1B_Bit11:1, OCR1B_Bit12:1, OCR1B_Bit13:1, OCR1B_Bit14:1, OCR1B_Bit15:1; }; struct { unsigned char OCR1BL; unsigned char OCR1BH; }; struct { unsigned char OCR1BL_Bit0:1, OCR1BL_Bit1:1, OCR1BL_Bit2:1, OCR1BL_Bit3:1, OCR1BL_Bit4:1, OCR1BL_Bit5:1, OCR1BL_Bit6:1, OCR1BL_Bit7:1; unsigned char OCR1BH_Bit0:1, OCR1BH_Bit1:1, OCR1BH_Bit2:1, OCR1BH_Bit3:1, OCR1BH_Bit4:1, OCR1BH_Bit5:1, OCR1BH_Bit6:1, OCR1BH_Bit7:1; }; } @ 0x8A;
__io union { unsigned short OCR1A; struct { unsigned char OCR1A_Bit0:1, OCR1A_Bit1:1, OCR1A_Bit2:1, OCR1A_Bit3:1, OCR1A_Bit4:1, OCR1A_Bit5:1, OCR1A_Bit6:1, OCR1A_Bit7:1; unsigned char OCR1A_Bit8:1, OCR1A_Bit9:1, OCR1A_Bit10:1, OCR1A_Bit11:1, OCR1A_Bit12:1, OCR1A_Bit13:1, OCR1A_Bit14:1, OCR1A_Bit15:1; }; struct { unsigned char OCR1AL; unsigned char OCR1AH; }; struct { unsigned char OCR1AL_Bit0:1, OCR1AL_Bit1:1, OCR1AL_Bit2:1, OCR1AL_Bit3:1, OCR1AL_Bit4:1, OCR1AL_Bit5:1, OCR1AL_Bit6:1, OCR1AL_Bit7:1; unsigned char OCR1AH_Bit0:1, OCR1AH_Bit1:1, OCR1AH_Bit2:1, OCR1AH_Bit3:1, OCR1AH_Bit4:1, OCR1AH_Bit5:1, OCR1AH_Bit6:1, OCR1AH_Bit7:1; }; } @ 0x88;
__io union { unsigned short ICR1; struct { unsigned char ICR1_Bit0:1, ICR1_Bit1:1, ICR1_Bit2:1, ICR1_Bit3:1, ICR1_Bit4:1, ICR1_Bit5:1, ICR1_Bit6:1, ICR1_Bit7:1; unsigned char ICR1_Bit8:1, ICR1_Bit9:1, ICR1_Bit10:1, ICR1_Bit11:1, ICR1_Bit12:1, ICR1_Bit13:1, ICR1_Bit14:1, ICR1_Bit15:1; }; struct { unsigned char ICR1L; unsigned char ICR1H; }; struct { unsigned char ICR1L_Bit0:1, ICR1L_Bit1:1, ICR1L_Bit2:1, ICR1L_Bit3:1, ICR1L_Bit4:1, ICR1L_Bit5:1, ICR1L_Bit6:1, ICR1L_Bit7:1; unsigned char ICR1H_Bit0:1, ICR1H_Bit1:1, ICR1H_Bit2:1, ICR1H_Bit3:1, ICR1H_Bit4:1, ICR1H_Bit5:1, ICR1H_Bit6:1, ICR1H_Bit7:1; }; } @ 0x86;
__io union { unsigned short TCNT1; struct { unsigned char TCNT1_Bit0:1, TCNT1_Bit1:1, TCNT1_Bit2:1, TCNT1_Bit3:1, TCNT1_Bit4:1, TCNT1_Bit5:1, TCNT1_Bit6:1, TCNT1_Bit7:1; unsigned char TCNT1_Bit8:1, TCNT1_Bit9:1, TCNT1_Bit10:1, TCNT1_Bit11:1, TCNT1_Bit12:1, TCNT1_Bit13:1, TCNT1_Bit14:1, TCNT1_Bit15:1; }; struct { unsigned char TCNT1L; unsigned char TCNT1H; }; struct { unsigned char TCNT1L_Bit0:1, TCNT1L_Bit1:1, TCNT1L_Bit2:1, TCNT1L_Bit3:1, TCNT1L_Bit4:1, TCNT1L_Bit5:1, TCNT1L_Bit6:1, TCNT1L_Bit7:1; unsigned char TCNT1H_Bit0:1, TCNT1H_Bit1:1, TCNT1H_Bit2:1, TCNT1H_Bit3:1, TCNT1H_Bit4:1, TCNT1H_Bit5:1, TCNT1H_Bit6:1, TCNT1H_Bit7:1; }; } @ 0x84;
__io union { unsigned char TCCR1C; struct { unsigned char TCCR1C_Bit0:1, TCCR1C_Bit1:1, TCCR1C_Bit2:1, TCCR1C_Bit3:1, TCCR1C_Bit4:1, TCCR1C_Bit5:1, TCCR1C_Bit6:1, TCCR1C_Bit7:1; }; struct { unsigned char TCCR1C_Dummy0:1, TCCR1C_Dummy1:1, TCCR1C_Dummy2:1, TCCR1C_Dummy3:1, TCCR1C_Dummy4:1, TCCR1C_Dummy5:1, TCCR1C_FOC1B:1, TCCR1C_FOC1A:1; }; } @ 0x82;
__io union { unsigned char TCCR1B; struct { unsigned char TCCR1B_Bit0:1, TCCR1B_Bit1:1, TCCR1B_Bit2:1, TCCR1B_Bit3:1, TCCR1B_Bit4:1, TCCR1B_Bit5:1, TCCR1B_Bit6:1, TCCR1B_Bit7:1; }; struct { unsigned char TCCR1B_CS10:1, TCCR1B_CS11:1, TCCR1B_CS12:1, TCCR1B_WGM12:1, TCCR1B_WGM13:1, TCCR1B_Dummy5:1, TCCR1B_ICES1:1, TCCR1B_ICNC1:1; }; } @ 0x81;
__io union { unsigned char TCCR1A; struct { unsigned char TCCR1A_Bit0:1, TCCR1A_Bit1:1, TCCR1A_Bit2:1, TCCR1A_Bit3:1, TCCR1A_Bit4:1, TCCR1A_Bit5:1, TCCR1A_Bit6:1, TCCR1A_Bit7:1; }; struct { unsigned char TCCR1A_WGM10:1, TCCR1A_WGM11:1, TCCR1A_Dummy2:1, TCCR1A_Dummy3:1, TCCR1A_COM1B0:1, TCCR1A_COM1B1:1, TCCR1A_COM1A0:1, TCCR1A_COM1A1:1; }; } @ 0x80;
__io union { unsigned char DIDR1; struct { unsigned char DIDR1_Bit0:1, DIDR1_Bit1:1, DIDR1_Bit2:1, DIDR1_Bit3:1, DIDR1_Bit4:1, DIDR1_Bit5:1, DIDR1_Bit6:1, DIDR1_Bit7:1; }; struct { unsigned char DIDR1_AIN0D:1, DIDR1_AIN1D:1, DIDR1_Dummy2:1, DIDR1_Dummy3:1, DIDR1_Dummy4:1, DIDR1_Dummy5:1, DIDR1_Dummy6:1, DIDR1_Dummy7:1; }; } @ 0x7F;
__io union { unsigned char DIDR0; struct { unsigned char DIDR0_Bit0:1, DIDR0_Bit1:1, DIDR0_Bit2:1, DIDR0_Bit3:1, DIDR0_Bit4:1, DIDR0_Bit5:1, DIDR0_Bit6:1, DIDR0_Bit7:1; }; struct { unsigned char DIDR0_ADC0D:1, DIDR0_ADC1D:1, DIDR0_ADC2D:1, DIDR0_ADC3D:1, DIDR0_ADC4D:1, DIDR0_ADC5D:1, DIDR0_ADC6D:1, DIDR0_ADC7D:1; }; } @ 0x7E;
__io union { unsigned char ADMUX; struct { unsigned char ADMUX_Bit0:1, ADMUX_Bit1:1, ADMUX_Bit2:1, ADMUX_Bit3:1, ADMUX_Bit4:1, ADMUX_Bit5:1, ADMUX_Bit6:1, ADMUX_Bit7:1; }; struct { unsigned char ADMUX_MUX0:1, ADMUX_MUX1:1, ADMUX_MUX2:1, ADMUX_MUX3:1, ADMUX_MUX4:1, ADMUX_ADLAR:1, ADMUX_REFS0:1, ADMUX_REFS1:1; }; } @ 0x7C;
__io union { unsigned char ADCSRB; struct { unsigned char ADCSRB_Bit0:1, ADCSRB_Bit1:1, ADCSRB_Bit2:1, ADCSRB_Bit3:1, ADCSRB_Bit4:1, ADCSRB_Bit5:1, ADCSRB_Bit6:1, ADCSRB_Bit7:1; }; struct { unsigned char ADCSRB_ADTS0:1, ADCSRB_ADTS1:1, ADCSRB_ADTS2:1, ADCSRB_Dummy3:1, ADCSRB_Dummy4:1, ADCSRB_Dummy5:1, ADCSRB_ACME:1, ADCSRB_Dummy7:1; }; } @ 0x7B;
__io union { unsigned char ADCSRA; struct { unsigned char ADCSRA_Bit0:1, ADCSRA_Bit1:1, ADCSRA_Bit2:1, ADCSRA_Bit3:1, ADCSRA_Bit4:1, ADCSRA_Bit5:1, ADCSRA_Bit6:1, ADCSRA_Bit7:1; }; struct { unsigned char ADCSRA_ADPS0:1, ADCSRA_ADPS1:1, ADCSRA_ADPS2:1, ADCSRA_ADIE:1, ADCSRA_ADIF:1, ADCSRA_ADATE:1, ADCSRA_ADSC:1, ADCSRA_ADEN:1; }; } @ 0x7A;
__io union { unsigned short ADC; struct { unsigned char ADC_Bit0:1, ADC_Bit1:1, ADC_Bit2:1, ADC_Bit3:1, ADC_Bit4:1, ADC_Bit5:1, ADC_Bit6:1, ADC_Bit7:1; unsigned char ADC_Bit8:1, ADC_Bit9:1, ADC_Bit10:1, ADC_Bit11:1, ADC_Bit12:1, ADC_Bit13:1, ADC_Bit14:1, ADC_Bit15:1; }; struct { unsigned char ADCL; unsigned char ADCH; }; struct { unsigned char ADCL_Bit0:1, ADCL_Bit1:1, ADCL_Bit2:1, ADCL_Bit3:1, ADCL_Bit4:1, ADCL_Bit5:1, ADCL_Bit6:1, ADCL_Bit7:1; unsigned char ADCH_Bit0:1, ADCH_Bit1:1, ADCH_Bit2:1, ADCH_Bit3:1, ADCH_Bit4:1, ADCH_Bit5:1, ADCH_Bit6:1, ADCH_Bit7:1; }; } @ 0x78;
__io union { unsigned char PCMSK3; struct { unsigned char PCMSK3_Bit0:1, PCMSK3_Bit1:1, PCMSK3_Bit2:1, PCMSK3_Bit3:1, PCMSK3_Bit4:1, PCMSK3_Bit5:1, PCMSK3_Bit6:1, PCMSK3_Bit7:1; }; struct { unsigned char PCMSK3_PCINT24:1, PCMSK3_PCINT25:1, PCMSK3_PCINT26:1, PCMSK3_PCINT27:1, PCMSK3_PCINT28:1, PCMSK3_PCINT29:1, PCMSK3_PCINT30:1, PCMSK3_PCINT31:1; }; } @ 0x73;
__io union { unsigned char TIMSK2; struct { unsigned char TIMSK2_Bit0:1, TIMSK2_Bit1:1, TIMSK2_Bit2:1, TIMSK2_Bit3:1, TIMSK2_Bit4:1, TIMSK2_Bit5:1, TIMSK2_Bit6:1, TIMSK2_Bit7:1; }; struct { unsigned char TIMSK2_TOIE2:1, TIMSK2_OCIE2A:1, TIMSK2_OCIE2B:1, TIMSK2_Dummy3:1, TIMSK2_Dummy4:1, TIMSK2_Dummy5:1, TIMSK2_Dummy6:1, TIMSK2_Dummy7:1; }; } @ 0x70;
__io union { unsigned char TIMSK1; struct { unsigned char TIMSK1_Bit0:1, TIMSK1_Bit1:1, TIMSK1_Bit2:1, TIMSK1_Bit3:1, TIMSK1_Bit4:1, TIMSK1_Bit5:1, TIMSK1_Bit6:1, TIMSK1_Bit7:1; }; struct { unsigned char TIMSK1_TOIE1:1, TIMSK1_OCIE1A:1, TIMSK1_OCIE1B:1, TIMSK1_Dummy3:1, TIMSK1_Dummy4:1, TIMSK1_ICIE1:1, TIMSK1_Dummy6:1, TIMSK1_Dummy7:1; }; } @ 0x6F;
__io union { unsigned char TIMSK0; struct { unsigned char TIMSK0_Bit0:1, TIMSK0_Bit1:1, TIMSK0_Bit2:1, TIMSK0_Bit3:1, TIMSK0_Bit4:1, TIMSK0_Bit5:1, TIMSK0_Bit6:1, TIMSK0_Bit7:1; }; struct { unsigned char TIMSK0_TOIE0:1, TIMSK0_OCIE0A:1, TIMSK0_OCIE0B:1, TIMSK0_Dummy3:1, TIMSK0_Dummy4:1, TIMSK0_Dummy5:1, TIMSK0_Dummy6:1, TIMSK0_Dummy7:1; }; } @ 0x6E;
__io union { unsigned char PCMSK2; struct { unsigned char PCMSK2_Bit0:1, PCMSK2_Bit1:1, PCMSK2_Bit2:1, PCMSK2_Bit3:1, PCMSK2_Bit4:1, PCMSK2_Bit5:1, PCMSK2_Bit6:1, PCMSK2_Bit7:1; }; struct { unsigned char PCMSK2_PCINT16:1, PCMSK2_PCINT17:1, PCMSK2_PCINT18:1, PCMSK2_PCINT19:1, PCMSK2_PCINT20:1, PCMSK2_PCINT21:1, PCMSK2_PCINT22:1, PCMSK2_PCINT23:1; }; } @ 0x6D;
__io union { unsigned char PCMSK1; struct { unsigned char PCMSK1_Bit0:1, PCMSK1_Bit1:1, PCMSK1_Bit2:1, PCMSK1_Bit3:1, PCMSK1_Bit4:1, PCMSK1_Bit5:1, PCMSK1_Bit6:1, PCMSK1_Bit7:1; }; struct { unsigned char PCMSK1_PCINT8:1, PCMSK1_PCINT9:1, PCMSK1_PCINT10:1, PCMSK1_PCINT11:1, PCMSK1_PCINT12:1, PCMSK1_PCINT13:1, PCMSK1_PCINT14:1, PCMSK1_PCINT15:1; }; } @ 0x6C;
__io union { unsigned char PCMSK0; struct { unsigned char PCMSK0_Bit0:1, PCMSK0_Bit1:1, PCMSK0_Bit2:1, PCMSK0_Bit3:1, PCMSK0_Bit4:1, PCMSK0_Bit5:1, PCMSK0_Bit6:1, PCMSK0_Bit7:1; }; struct { unsigned char PCMSK0_PCINT0:1, PCMSK0_PCINT1:1, PCMSK0_PCINT2:1, PCMSK0_PCINT3:1, PCMSK0_PCINT4:1, PCMSK0_PCINT5:1, PCMSK0_PCINT6:1, PCMSK0_PCINT7:1; }; } @ 0x6B;
__io union { unsigned char EICRA; struct { unsigned char EICRA_Bit0:1, EICRA_Bit1:1, EICRA_Bit2:1, EICRA_Bit3:1, EICRA_Bit4:1, EICRA_Bit5:1, EICRA_Bit6:1, EICRA_Bit7:1; }; struct { unsigned char EICRA_ISC00:1, EICRA_ISC01:1, EICRA_ISC10:1, EICRA_ISC11:1, EICRA_ISC20:1, EICRA_ISC21:1, EICRA_Dummy6:1, EICRA_Dummy7:1; }; } @ 0x69;
__io union { unsigned char PCICR; struct { unsigned char PCICR_Bit0:1, PCICR_Bit1:1, PCICR_Bit2:1, PCICR_Bit3:1, PCICR_Bit4:1, PCICR_Bit5:1, PCICR_Bit6:1, PCICR_Bit7:1; }; struct { unsigned char PCICR_PCIE0:1, PCICR_PCIE1:1, PCICR_PCIE2:1, PCICR_PCIE3:1, PCICR_Dummy4:1, PCICR_Dummy5:1, PCICR_Dummy6:1, PCICR_Dummy7:1; }; } @ 0x68;
__io union { unsigned char OSCCAL; struct { unsigned char OSCCAL_Bit0:1, OSCCAL_Bit1:1, OSCCAL_Bit2:1, OSCCAL_Bit3:1, OSCCAL_Bit4:1, OSCCAL_Bit5:1, OSCCAL_Bit6:1, OSCCAL_Bit7:1; }; } @ 0x66;
__io union { unsigned char PRR; struct { unsigned char PRR_Bit0:1, PRR_Bit1:1, PRR_Bit2:1, PRR_Bit3:1, PRR_Bit4:1, PRR_Bit5:1, PRR_Bit6:1, PRR_Bit7:1; }; struct { unsigned char PRR_PRADC:1, PRR_PRUSART0:1, PRR_PRSPI:1, PRR_PRTIM1:1, PRR_Dummy4:1, PRR_PRTIM0:1, PRR_PRTIM2:1, PRR_PRTWI:1; }; } @ 0x64;
__io union { unsigned char CLKPR; struct { unsigned char CLKPR_Bit0:1, CLKPR_Bit1:1, CLKPR_Bit2:1, CLKPR_Bit3:1, CLKPR_Bit4:1, CLKPR_Bit5:1, CLKPR_Bit6:1, CLKPR_Bit7:1; }; struct { unsigned char CLKPR_CLKPS0:1, CLKPR_CLKPS1:1, CLKPR_CLKPS2:1, CLKPR_CLKPS3:1, CLKPR_Dummy4:1, CLKPR_Dummy5:1, CLKPR_Dummy6:1, CLKPR_CLKPCE:1; }; } @ 0x61;
__io union { unsigned char WDTCSR; struct { unsigned char WDTCSR_Bit0:1, WDTCSR_Bit1:1, WDTCSR_Bit2:1, WDTCSR_Bit3:1, WDTCSR_Bit4:1, WDTCSR_Bit5:1, WDTCSR_Bit6:1, WDTCSR_Bit7:1; }; struct { unsigned char WDTCSR_WDP0:1, WDTCSR_WDP1:1, WDTCSR_WDP2:1, WDTCSR_WDE:1, WDTCSR_WDCE:1, WDTCSR_WDP3:1, WDTCSR_WDIE:1, WDTCSR_WDIF:1; }; } @ 0x60;
__io union { unsigned char SREG; struct { unsigned char SREG_Bit0:1, SREG_Bit1:1, SREG_Bit2:1, SREG_Bit3:1, SREG_Bit4:1, SREG_Bit5:1, SREG_Bit6:1, SREG_Bit7:1; }; struct { unsigned char SREG_C:1, SREG_Z:1, SREG_N:1, SREG_V:1, SREG_S:1, SREG_H:1, SREG_T:1, SREG_I:1; }; } @ 0x3F;
__io union { unsigned short SP; struct { unsigned char SP_Bit0:1, SP_Bit1:1, SP_Bit2:1, SP_Bit3:1, SP_Bit4:1, SP_Bit5:1, SP_Bit6:1, SP_Bit7:1; unsigned char SP_Bit8:1, SP_Bit9:1, SP_Bit10:1, SP_Bit11:1, SP_Bit12:1, SP_Bit13:1, SP_Bit14:1, SP_Bit15:1; }; struct { unsigned char SP_SP0:1, SP_SP1:1, SP_SP2:1, SP_SP3:1, SP_SP4:1, SP_SP5:1, SP_SP6:1, SP_SP7:1; unsigned char SP_SP8:1, SP_SP9:1, SP_SP10:1, SP_SP11:1, SP_SP12:1, SP_SP13:1, SP_SP14:1, SP_SP15:1; }; struct { unsigned char SPL; unsigned char SPH; }; struct { unsigned char SPL_Bit0:1, SPL_Bit1:1, SPL_Bit2:1, SPL_Bit3:1, SPL_Bit4:1, SPL_Bit5:1, SPL_Bit6:1, SPL_Bit7:1; unsigned char SPH_Bit0:1, SPH_Bit1:1, SPH_Bit2:1, SPH_Bit3:1, SPH_Bit4:1, SPH_Bit5:1, SPH_Bit6:1, SPH_Bit7:1; }; struct { unsigned char SPL_SP0:1, SPL_SP1:1, SPL_SP2:1, SPL_SP3:1, SPL_SP4:1, SPL_SP5:1, SPL_SP6:1, SPL_SP7:1; unsigned char SPH_SP8:1, SPH_SP9:1, SPH_SP10:1, SPH_SP11:1, SPH_SP12:1, SPH_SP13:1, SPH_SP14:1, SPH_SP15:1; }; } @ 0x3D;
__io union { unsigned char SPMCSR; struct { unsigned char SPMCSR_Bit0:1, SPMCSR_Bit1:1, SPMCSR_Bit2:1, SPMCSR_Bit3:1, SPMCSR_Bit4:1, SPMCSR_Bit5:1, SPMCSR_Bit6:1, SPMCSR_Bit7:1; }; struct { unsigned char SPMCSR_SPMEN:1, SPMCSR_PGERS:1, SPMCSR_PGWRT:1, SPMCSR_BLBSET:1, SPMCSR_RWWSRE:1, SPMCSR_SIGRD:1, SPMCSR_RWWSB:1, SPMCSR_SPMIE:1; }; } @ 0x37;
__io union { unsigned char MCUCR; struct { unsigned char MCUCR_Bit0:1, MCUCR_Bit1:1, MCUCR_Bit2:1, MCUCR_Bit3:1, MCUCR_Bit4:1, MCUCR_Bit5:1, MCUCR_Bit6:1, MCUCR_Bit7:1; }; struct { unsigned char MCUCR_IVCE:1, MCUCR_IVSEL:1, MCUCR_Dummy2:1, MCUCR_Dummy3:1, MCUCR_PUD:1, MCUCR_Dummy5:1, MCUCR_Dummy6:1, MCUCR_JTD:1; }; } @ 0x35;
__io union { unsigned char MCUSR; struct { unsigned char MCUSR_Bit0:1, MCUSR_Bit1:1, MCUSR_Bit2:1, MCUSR_Bit3:1, MCUSR_Bit4:1, MCUSR_Bit5:1, MCUSR_Bit6:1, MCUSR_Bit7:1; }; struct { unsigned char MCUSR_PORF:1, MCUSR_EXTRF:1, MCUSR_BORF:1, MCUSR_WDRF:1, MCUSR_JTRF:1, MCUSR_Dummy5:1, MCUSR_Dummy6:1, MCUSR_Dummy7:1; }; } @ 0x34;
__io union { unsigned char SMCR; struct { unsigned char SMCR_Bit0:1, SMCR_Bit1:1, SMCR_Bit2:1, SMCR_Bit3:1, SMCR_Bit4:1, SMCR_Bit5:1, SMCR_Bit6:1, SMCR_Bit7:1; }; struct { unsigned char SMCR_SE:1, SMCR_SM0:1, SMCR_SM1:1, SMCR_SM2:1, SMCR_Dummy4:1, SMCR_Dummy5:1, SMCR_Dummy6:1, SMCR_Dummy7:1; }; } @ 0x33;
__io union { unsigned char OCDR; struct { unsigned char OCDR_Bit0:1, OCDR_Bit1:1, OCDR_Bit2:1, OCDR_Bit3:1, OCDR_Bit4:1, OCDR_Bit5:1, OCDR_Bit6:1, OCDR_Bit7:1; }; } @ 0x31;
__io union { unsigned char ACSR; struct { unsigned char ACSR_Bit0:1, ACSR_Bit1:1, ACSR_Bit2:1, ACSR_Bit3:1, ACSR_Bit4:1, ACSR_Bit5:1, ACSR_Bit6:1, ACSR_Bit7:1; }; struct { unsigned char ACSR_ACIS0:1, ACSR_ACIS1:1, ACSR_ACIC:1, ACSR_ACIE:1, ACSR_ACI:1, ACSR_ACO:1, ACSR_ACBG:1, ACSR_ACD:1; }; } @ 0x30;
__io union { unsigned char SPDR; struct { unsigned char SPDR_Bit0:1, SPDR_Bit1:1, SPDR_Bit2:1, SPDR_Bit3:1, SPDR_Bit4:1, SPDR_Bit5:1, SPDR_Bit6:1, SPDR_Bit7:1; }; } @ 0x2E;
__io union { unsigned char SPSR; struct { unsigned char SPSR_Bit0:1, SPSR_Bit1:1, SPSR_Bit2:1, SPSR_Bit3:1, SPSR_Bit4:1, SPSR_Bit5:1, SPSR_Bit6:1, SPSR_Bit7:1; }; struct { unsigned char SPSR_SPI2X0:1, SPSR_Dummy1:1, SPSR_Dummy2:1, SPSR_Dummy3:1, SPSR_Dummy4:1, SPSR_Dummy5:1, SPSR_WCOL0:1, SPSR_SPIF0:1; }; } @ 0x2D;
__io union { unsigned char SPCR; struct { unsigned char SPCR_Bit0:1, SPCR_Bit1:1, SPCR_Bit2:1, SPCR_Bit3:1, SPCR_Bit4:1, SPCR_Bit5:1, SPCR_Bit6:1, SPCR_Bit7:1; }; struct { unsigned char SPCR_SPR00:1, SPCR_SPR01:1, SPCR_CPHA0:1, SPCR_CPOL0:1, SPCR_MSTR0:1, SPCR_DORD0:1, SPCR_SPE0:1, SPCR_SPIE0:1; }; } @ 0x2C;
__io union { unsigned char GPIOR2; struct { unsigned char GPIOR2_Bit0:1, GPIOR2_Bit1:1, GPIOR2_Bit2:1, GPIOR2_Bit3:1, GPIOR2_Bit4:1, GPIOR2_Bit5:1, GPIOR2_Bit6:1, GPIOR2_Bit7:1; }; } @ 0x2B;
__io union { unsigned char GPIOR1; struct { unsigned char GPIOR1_Bit0:1, GPIOR1_Bit1:1, GPIOR1_Bit2:1, GPIOR1_Bit3:1, GPIOR1_Bit4:1, GPIOR1_Bit5:1, GPIOR1_Bit6:1, GPIOR1_Bit7:1; }; } @ 0x2A;
__io union { unsigned char OCR0B; struct { unsigned char OCR0B_Bit0:1, OCR0B_Bit1:1, OCR0B_Bit2:1, OCR0B_Bit3:1, OCR0B_Bit4:1, OCR0B_Bit5:1, OCR0B_Bit6:1, OCR0B_Bit7:1; }; } @ 0x28;
__io union { unsigned char OCR0A; struct { unsigned char OCR0A_Bit0:1, OCR0A_Bit1:1, OCR0A_Bit2:1, OCR0A_Bit3:1, OCR0A_Bit4:1, OCR0A_Bit5:1, OCR0A_Bit6:1, OCR0A_Bit7:1; }; } @ 0x27;
__io union { unsigned char TCNT0; struct { unsigned char TCNT0_Bit0:1, TCNT0_Bit1:1, TCNT0_Bit2:1, TCNT0_Bit3:1, TCNT0_Bit4:1, TCNT0_Bit5:1, TCNT0_Bit6:1, TCNT0_Bit7:1; }; } @ 0x26;
__io union { unsigned char TCCR0B; struct { unsigned char TCCR0B_Bit0:1, TCCR0B_Bit1:1, TCCR0B_Bit2:1, TCCR0B_Bit3:1, TCCR0B_Bit4:1, TCCR0B_Bit5:1, TCCR0B_Bit6:1, TCCR0B_Bit7:1; }; struct { unsigned char TCCR0B_CS00:1, TCCR0B_CS01:1, TCCR0B_CS02:1, TCCR0B_WGM02:1, TCCR0B_Dummy4:1, TCCR0B_Dummy5:1, TCCR0B_FOC0B:1, TCCR0B_FOC0A:1; }; } @ 0x25;
__io union { unsigned char TCCR0A; struct { unsigned char TCCR0A_Bit0:1, TCCR0A_Bit1:1, TCCR0A_Bit2:1, TCCR0A_Bit3:1, TCCR0A_Bit4:1, TCCR0A_Bit5:1, TCCR0A_Bit6:1, TCCR0A_Bit7:1; }; struct { unsigned char TCCR0A_WGM00:1, TCCR0A_WGM01:1, TCCR0A_Dummy2:1, TCCR0A_Dummy3:1, TCCR0A_COM0B0:1, TCCR0A_COM0B1:1, TCCR0A_COM0A0:1, TCCR0A_COM0A1:1; }; } @ 0x24;
__io union { unsigned char GTCCR; struct { unsigned char GTCCR_Bit0:1, GTCCR_Bit1:1, GTCCR_Bit2:1, GTCCR_Bit3:1, GTCCR_Bit4:1, GTCCR_Bit5:1, GTCCR_Bit6:1, GTCCR_Bit7:1; }; struct { unsigned char GTCCR_PSRSYNC:1, GTCCR_PSRASY:1, GTCCR_Dummy2:1, GTCCR_Dummy3:1, GTCCR_Dummy4:1, GTCCR_Dummy5:1, GTCCR_Dummy6:1, GTCCR_TSM:1; }; } @ 0x23;
__io union { unsigned short EEAR; struct { unsigned char EEAR_Bit0:1, EEAR_Bit1:1, EEAR_Bit2:1, EEAR_Bit3:1, EEAR_Bit4:1, EEAR_Bit5:1, EEAR_Bit6:1, EEAR_Bit7:1; unsigned char EEAR_Bit8:1, EEAR_Bit9:1, EEAR_Bit10:1, EEAR_Bit11:1, EEAR_Bit12:1, EEAR_Bit13:1, EEAR_Bit14:1, EEAR_Bit15:1; }; struct { unsigned char EEARL; unsigned char EEARH; }; struct { unsigned char EEARL_Bit0:1, EEARL_Bit1:1, EEARL_Bit2:1, EEARL_Bit3:1, EEARL_Bit4:1, EEARL_Bit5:1, EEARL_Bit6:1, EEARL_Bit7:1; unsigned char EEARH_Bit0:1, EEARH_Bit1:1, EEARH_Bit2:1, EEARH_Bit3:1, EEARH_Bit4:1, EEARH_Bit5:1, EEARH_Bit6:1, EEARH_Bit7:1; }; } @ 0x21;
__io union { unsigned char EEDR; struct { unsigned char EEDR_Bit0:1, EEDR_Bit1:1, EEDR_Bit2:1, EEDR_Bit3:1, EEDR_Bit4:1, EEDR_Bit5:1, EEDR_Bit6:1, EEDR_Bit7:1; }; } @ 0x20;
__io union { unsigned char EECR; struct { unsigned char EECR_Bit0:1, EECR_Bit1:1, EECR_Bit2:1, EECR_Bit3:1, EECR_Bit4:1, EECR_Bit5:1, EECR_Bit6:1, EECR_Bit7:1; }; struct { unsigned char EECR_EERE:1, EECR_EEPE:1, EECR_EEMPE:1, EECR_EERIE:1, EECR_EEPM0:1, EECR_EEPM1:1, EECR_Dummy6:1, EECR_Dummy7:1; }; } @ 0x1F;
__io union { unsigned char GPIOR0; struct { unsigned char GPIOR0_Bit0:1, GPIOR0_Bit1:1, GPIOR0_Bit2:1, GPIOR0_Bit3:1, GPIOR0_Bit4:1, GPIOR0_Bit5:1, GPIOR0_Bit6:1, GPIOR0_Bit7:1; }; } @ 0x1E;
__io union { unsigned char EIMSK; struct { unsigned char EIMSK_Bit0:1, EIMSK_Bit1:1, EIMSK_Bit2:1, EIMSK_Bit3:1, EIMSK_Bit4:1, EIMSK_Bit5:1, EIMSK_Bit6:1, EIMSK_Bit7:1; }; struct { unsigned char EIMSK_INT0:1, EIMSK_INT1:1, EIMSK_INT2:1, EIMSK_Dummy3:1, EIMSK_Dummy4:1, EIMSK_Dummy5:1, EIMSK_Dummy6:1, EIMSK_Dummy7:1; }; } @ 0x1D;
__io union { unsigned char EIFR; struct { unsigned char EIFR_Bit0:1, EIFR_Bit1:1, EIFR_Bit2:1, EIFR_Bit3:1, EIFR_Bit4:1, EIFR_Bit5:1, EIFR_Bit6:1, EIFR_Bit7:1; }; struct { unsigned char EIFR_INTF0:1, EIFR_INTF1:1, EIFR_INTF2:1, EIFR_Dummy3:1, EIFR_Dummy4:1, EIFR_Dummy5:1, EIFR_Dummy6:1, EIFR_Dummy7:1; }; } @ 0x1C;
__io union { unsigned char PCIFR; struct { unsigned char PCIFR_Bit0:1, PCIFR_Bit1:1, PCIFR_Bit2:1, PCIFR_Bit3:1, PCIFR_Bit4:1, PCIFR_Bit5:1, PCIFR_Bit6:1, PCIFR_Bit7:1; }; struct { unsigned char PCIFR_PCIF0:1, PCIFR_PCIF1:1, PCIFR_PCIF2:1, PCIFR_PCIF3:1, PCIFR_Dummy4:1, PCIFR_Dummy5:1, PCIFR_Dummy6:1, PCIFR_Dummy7:1; }; } @ 0x1B;
__io union { unsigned char TIFR2; struct { unsigned char TIFR2_Bit0:1, TIFR2_Bit1:1, TIFR2_Bit2:1, TIFR2_Bit3:1, TIFR2_Bit4:1, TIFR2_Bit5:1, TIFR2_Bit6:1, TIFR2_Bit7:1; }; struct { unsigned char TIFR2_TOV2:1, TIFR2_OCF2A:1, TIFR2_OCF2b:1, TIFR2_Dummy3:1, TIFR2_Dummy4:1, TIFR2_Dummy5:1, TIFR2_Dummy6:1, TIFR2_Dummy7:1; }; } @ 0x17;
__io union { unsigned char TIFR1; struct { unsigned char TIFR1_Bit0:1, TIFR1_Bit1:1, TIFR1_Bit2:1, TIFR1_Bit3:1, TIFR1_Bit4:1, TIFR1_Bit5:1, TIFR1_Bit6:1, TIFR1_Bit7:1; }; struct { unsigned char TIFR1_TOV1:1, TIFR1_OCF1A:1, TIFR1_OCF1B:1, TIFR1_Dummy3:1, TIFR1_Dummy4:1, TIFR1_ICF1:1, TIFR1_Dummy6:1, TIFR1_Dummy7:1; }; } @ 0x16;
__io union { unsigned char TIFR0; struct { unsigned char TIFR0_Bit0:1, TIFR0_Bit1:1, TIFR0_Bit2:1, TIFR0_Bit3:1, TIFR0_Bit4:1, TIFR0_Bit5:1, TIFR0_Bit6:1, TIFR0_Bit7:1; }; struct { unsigned char TIFR0_TOV0:1, TIFR0_OCF0A:1, TIFR0_OCF0B:1, TIFR0_Dummy3:1, TIFR0_Dummy4:1, TIFR0_Dummy5:1, TIFR0_Dummy6:1, TIFR0_Dummy7:1; }; } @ 0x15;
__io union { unsigned char PORTD; struct { unsigned char PORTD_Bit0:1, PORTD_Bit1:1, PORTD_Bit2:1, PORTD_Bit3:1, PORTD_Bit4:1, PORTD_Bit5:1, PORTD_Bit6:1, PORTD_Bit7:1; }; struct { unsigned char PORTD_PORTD0:1, PORTD_PORTD1:1, PORTD_PORTD2:1, PORTD_PORTD3:1, PORTD_PORTD4:1, PORTD_PORTD5:1, PORTD_PORTD6:1, PORTD_PORTD7:1; }; } @ 0x0B;
__io union { unsigned char DDRD; struct { unsigned char DDRD_Bit0:1, DDRD_Bit1:1, DDRD_Bit2:1, DDRD_Bit3:1, DDRD_Bit4:1, DDRD_Bit5:1, DDRD_Bit6:1, DDRD_Bit7:1; }; struct { unsigned char DDRD_DDD0:1, DDRD_DDD1:1, DDRD_DDD2:1, DDRD_DDD3:1, DDRD_DDD4:1, DDRD_DDD5:1, DDRD_DDD6:1, DDRD_DDD7:1; }; } @ 0x0A;
__io union { unsigned char PIND; struct { unsigned char PIND_Bit0:1, PIND_Bit1:1, PIND_Bit2:1, PIND_Bit3:1, PIND_Bit4:1, PIND_Bit5:1, PIND_Bit6:1, PIND_Bit7:1; }; struct { unsigned char PIND_PIND0:1, PIND_PIND1:1, PIND_PIND2:1, PIND_PIND3:1, PIND_PIND4:1, PIND_PIND5:1, PIND_PIND6:1, PIND_PIND7:1; }; } @ 0x09;
__io union { unsigned char PORTC; struct { unsigned char PORTC_Bit0:1, PORTC_Bit1:1, PORTC_Bit2:1, PORTC_Bit3:1, PORTC_Bit4:1, PORTC_Bit5:1, PORTC_Bit6:1, PORTC_Bit7:1; }; struct { unsigned char PORTC_PORTC0:1, PORTC_PORTC1:1, PORTC_PORTC2:1, PORTC_PORTC3:1, PORTC_PORTC4:1, PORTC_PORTC5:1, PORTC_PORTC6:1, PORTC_PORTC7:1; }; } @ 0x08;
__io union { unsigned char DDRC; struct { unsigned char DDRC_Bit0:1, DDRC_Bit1:1, DDRC_Bit2:1, DDRC_Bit3:1, DDRC_Bit4:1, DDRC_Bit5:1, DDRC_Bit6:1, DDRC_Bit7:1; }; struct { unsigned char DDRC_DDC0:1, DDRC_DDC1:1, DDRC_DDC2:1, DDRC_DDC3:1, DDRC_DDC4:1, DDRC_DDC5:1, DDRC_DDC6:1, DDRC_DDC7:1; }; } @ 0x07;
__io union { unsigned char PINC; struct { unsigned char PINC_Bit0:1, PINC_Bit1:1, PINC_Bit2:1, PINC_Bit3:1, PINC_Bit4:1, PINC_Bit5:1, PINC_Bit6:1, PINC_Bit7:1; }; struct { unsigned char PINC_PINC0:1, PINC_PINC1:1, PINC_PINC2:1, PINC_PINC3:1, PINC_PINC4:1, PINC_PINC5:1, PINC_PINC6:1, PINC_PINC7:1; }; } @ 0x06;
__io union { unsigned char PORTB; struct { unsigned char PORTB_Bit0:1, PORTB_Bit1:1, PORTB_Bit2:1, PORTB_Bit3:1, PORTB_Bit4:1, PORTB_Bit5:1, PORTB_Bit6:1, PORTB_Bit7:1; }; struct { unsigned char PORTB_PORTB0:1, PORTB_PORTB1:1, PORTB_PORTB2:1, PORTB_PORTB3:1, PORTB_PORTB4:1, PORTB_PORTB5:1, PORTB_PORTB6:1, PORTB_PORTB7:1; }; } @ 0x05;
__io union { unsigned char DDRB; struct { unsigned char DDRB_Bit0:1, DDRB_Bit1:1, DDRB_Bit2:1, DDRB_Bit3:1, DDRB_Bit4:1, DDRB_Bit5:1, DDRB_Bit6:1, DDRB_Bit7:1; }; struct { unsigned char DDRB_DDB0:1, DDRB_DDB1:1, DDRB_DDB2:1, DDRB_DDB3:1, DDRB_DDB4:1, DDRB_DDB5:1, DDRB_DDB6:1, DDRB_DDB7:1; }; } @ 0x04;
__io union { unsigned char PINB; struct { unsigned char PINB_Bit0:1, PINB_Bit1:1, PINB_Bit2:1, PINB_Bit3:1, PINB_Bit4:1, PINB_Bit5:1, PINB_Bit6:1, PINB_Bit7:1; }; struct { unsigned char PINB_PINB0:1, PINB_PINB1:1, PINB_PINB2:1, PINB_PINB3:1, PINB_PINB4:1, PINB_PINB5:1, PINB_PINB6:1, PINB_PINB7:1; }; } @ 0x03;
__io union { unsigned char PORTA; struct { unsigned char PORTA_Bit0:1, PORTA_Bit1:1, PORTA_Bit2:1, PORTA_Bit3:1, PORTA_Bit4:1, PORTA_Bit5:1, PORTA_Bit6:1, PORTA_Bit7:1; }; struct { unsigned char PORTA_PORTA0:1, PORTA_PORTA1:1, PORTA_PORTA2:1, PORTA_PORTA3:1, PORTA_PORTA4:1, PORTA_PORTA5:1, PORTA_PORTA6:1, PORTA_PORTA7:1; }; } @ 0x02;
__io union { unsigned char DDRA; struct { unsigned char DDRA_Bit0:1, DDRA_Bit1:1, DDRA_Bit2:1, DDRA_Bit3:1, DDRA_Bit4:1, DDRA_Bit5:1, DDRA_Bit6:1, DDRA_Bit7:1; }; struct { unsigned char DDRA_DDA0:1, DDRA_DDA1:1, DDRA_DDA2:1, DDRA_DDA3:1, DDRA_DDA4:1, DDRA_DDA5:1, DDRA_DDA6:1, DDRA_DDA7:1; }; } @ 0x01;
__io union { unsigned char PINA; struct { unsigned char PINA_Bit0:1, PINA_Bit1:1, PINA_Bit2:1, PINA_Bit3:1, PINA_Bit4:1, PINA_Bit5:1, PINA_Bit6:1, PINA_Bit7:1; }; struct { unsigned char PINA_PINA0:1, PINA_PINA1:1, PINA_PINA2:1, PINA_PINA3:1, PINA_PINA4:1, PINA_PINA5:1, PINA_PINA6:1, PINA_PINA7:1; }; } @ 0x00;





/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#line 239 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"










/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/

  /* UCSR1C */
#line 262 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

  /* UCSR1B */
#line 272 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

  /* UCSR1A */
#line 282 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0C */
#line 292 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0B */
#line 302 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0A */
#line 312 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWAM */
#line 321 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWCR */
#line 330 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWAR */
#line 340 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWSR */
#line 349 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ASSR */
#line 358 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR2B */
#line 366 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR2A */
#line 374 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR1C */



/* TCCR1B */
#line 387 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR1A */
#line 395 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DIDR1 */



/* DIDR0 */
#line 409 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ADMUX */
#line 419 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ADCSRB */





/* ADCSRA */
#line 435 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK3 */
#line 445 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TIMSK2 */




/* TIMSK1 */





/* TIMSK0 */




/* PCMSK2 */
#line 471 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK1 */
#line 481 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK0 */
#line 491 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* EICRA */
#line 499 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCICR */





/* PRR */
#line 514 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* CLKPR */






/* WDTCSR */
#line 531 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SREG */
/*
#define I 7
#define T 6
#define H 5
#define S 4
#define V 3
#define N 2
#define Z 1
#define C 0
*/

  /* SP */
#line 561 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SPMCSR */
#line 571 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* MCUCR */





/* MCUSR */






/* SMCR */





/* ACSR */
#line 600 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SPSR */




/* SPCR */
#line 615 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR0B */
#line 623 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR0A */
#line 631 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* GTCCR */




  /* EECR */
#line 644 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"


/* EIMSK */




/* EIFR */




/* PCIFR */





/* TIFR2 */




/* TIFR1 */





/* TIFR0 */




/* PORTD */
#line 687 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PD */
#line 697 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRD */
#line 707 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PIND */
#line 717 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTC */
#line 727 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PC */
#line 737 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRC */
#line 747 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINC */
#line 757 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTB */
#line 767 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PB */
#line 777 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRB */
#line 787 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINB */
#line 797 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTA */
#line 807 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PA */
#line 817 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRA */
#line 827 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINA */
#line 837 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"



/* Pointer definition */
#line 847 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* Constants */





#line 172 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\ioavr.h"
#line 5 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\board.h"




//#define NONE_CONFED_204
//#define NONE_CONFED_1FF

//#define DEBUG

//#define DEMOBOARD

//#define LM018
//#define LM056
//#define LM057
//#define LM076
//#define LM077
//#define LM020
//#define LM028

//#ifdef SMT











































































#line 109 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\board.h"



void buzzer_ms(unsigned int ms);
void IO_Initial();
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);		// alan 0604
void not_bit(unsigned char *data, unsigned bit);
unsigned char StrToChar(unsigned char *data);
unsigned char *CharToStr(unsigned char data,unsigned char *buffer);
unsigned char get_key();



unsigned char get_PIR_trigger(unsigned char level);
unsigned char get_US_trigger(unsigned char level);
void timer1_initial(void);
void adc_initial();
unsigned int read_adc10bit(unsigned char adc_input);
unsigned char read_adc8bit(unsigned char adc_input);
void system_reset(void);
void WDT_off(void);
void delay_ms_1(void);

#line 6 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\PIR.h"
//PIR.h









/*  PIR�źż���޶� */
#line 18 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\PIR.h"


/* PIR�����ȶ��� */		






typedef enum DTFLAG_STATUS { DISABLED,
                             ENABLED } DTFLAG_STATUS;

struct PIR
{
	unsigned char center;
	unsigned char window;
	unsigned	fPIROCCDetected:1;
	unsigned	fPIRdetectionEnable:1;		
};

void PIR_SENSE_SET(void);

unsigned char PIR_detect(void);





#line 7 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\string.h"
/*                       - STRING.H -

   The ANSI 'string' function declarations.

   $Revision: 2093 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include


#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"
/*                      - SYSMAC.H -

   Defines system macros to maintain source compatibility
   with different IAR compilers.

   $Revision: 2095 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include










































#line 65 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"

#line 73 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"

#line 84 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"








/* Macro for frmwri and frmrd */


/* Typedefs put here to appear only once */
typedef unsigned int    size_t;
typedef signed int ptrdiff_t;

#line 18 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\string.h"















__intrinsic  void *memcpy(void *, const void *, size_t);

__intrinsic  void *memmove(void *, const void *, size_t);

__intrinsic  void *memchr(const void *, int, size_t);

__intrinsic  void *memset(void *, int, size_t);

__intrinsic  int memcmp(const void *, const void *, size_t);

__intrinsic  char *strchr(const char *, int);

__intrinsic  int strcmp(const char *, const char *);

__intrinsic  int strncmp(const char *, const char *, size_t);

__intrinsic  int strcoll(const char *, const char *);

__intrinsic  size_t strlen(const char *);

__intrinsic  size_t strcspn(const char *, const char *);

__intrinsic  size_t strspn(const char *, const char *);

__intrinsic  char *strpbrk(const char *, const char *);

__intrinsic  char *strrchr(const char *, int);

__intrinsic  char *strstr(const char *, const char *);

__intrinsic  char *strcat(char *, const char *);

__intrinsic  char *strncat(char *, const char *, size_t);

__intrinsic  char *strcpy(char *, const char *);

__intrinsic  char *strncpy(char *, const char *, size_t);

__intrinsic  char *strerror(int);

__intrinsic  char *strtok(char *, const char *);

__intrinsic  size_t strxfrm(char *, const char *, size_t);







#line 8 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.h"



unsigned char decode_id(void);
unsigned char decode_SCS(void);
void reception_buffer_clear(unsigned char temp);
unsigned char is_gateway_busy(void);
void application_decode_short(void);    // add by alan 20090401
void application_decode_long(void);
void calibration_decode(void);
void scs_calibration(void);
#line 9 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs_next.h"


void send_frame_pp(char *data, unsigned int ms);
void send_frame_pp_broad(char *data, unsigned int ms);
void send_frame_pp_ext(char *data, unsigned int ms);
void send_frame_pp_ext_broad(char *data, unsigned int ms);
void org_ext_broad(char *data, unsigned int ms);
void ext_ans_frame(unsigned char value);
void parameter_set(unsigned char data);
void id_frame(void);
void KO_answer_frame(void);
void diagnostic_frame(void);
void configuration_answer_frame(unsigned char value);
void configuration_receive_answer_frame(void);
void png_diagnostic(void);
void configuration_setting_frame(unsigned char value);
void KO_answer_frame(void);
void parameter_answer_frame(void);
void frame_buffer_clear(void);
void parameter_request_error_frame(void);
void not_allowed_response(unsigned char ko_channel);
void parameter_all_answer(void);
void parameter_specified_index_answer(void);
void send_aux_frame(unsigned char argument,unsigned char ns,unsigned char scenario_index);
void send_group_pnl_frame(unsigned char send_type,unsigned char GR, unsigned char cmd);
void ko_answer_all(void);
void address_answer_frame(void);
void address_setting_error_frame(void);
unsigned char dimmer_convert(unsigned char data);
void send_group_frame(unsigned char argument);
unsigned int write_parameter_scenario(void);
void parameter_setting_error_answer(unsigned int value);
void KO_setting_procedure(void);
void configuration_procedure(void);
void aux_procedure(void);
void scenario_remove(unsigned char number);
void KO_setting_error_frame(unsigned char send_type,unsigned char channel);
#line 11 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\configuration.h"



unsigned char configuration_read(void);
unsigned char power_up_configuration(void);

void ID_setting(unsigned char *data);
unsigned char configuration_checking(unsigned char *data);
void load_parameter();
unsigned int write_KO(unsigned char index,unsigned char data);
unsigned int write_ee_KO(unsigned char index,unsigned char data);
unsigned int read_KO(unsigned char index);
unsigned char read_KO_none_confed(unsigned char index);
void KO_parameter_initial(void);
void KO_parameter_initial_temp(void);
void write_moudle_parameter(void);
void write_moudle_parameter_temp(void);
#line 12 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\usart.h"
//usart.h

//��������

//#define F_CPU            4000000  //����Ƶ��4.0MHz




//#define UPE 2    //M128





//�궨��


//#define PARITY_ERROR (1<<UPE)    //M128




// USART Receiver buffer
// ȫ�ֱ���,�����жϷ�������б��޸ģ����volatile�޶�����Ҫ�ͻ������






// USART Transmitter buffer


// ��������
char get_c(void);
void put_c(unsigned char c);
void put_s(unsigned char *ptr);
void init_USART0(void);
#line 13 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"




// set point level




// function state define





// detection scheme





// timeout warning mode define





// function mode define






// time delay define
#line 42 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"




// define the configurators.T
#line 57 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"

// define the sensor status
#line 69 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"
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
void check_modality_frame(void);
void Delay_Alert(void);
void Stop_allTimer(void);
void Start_Time_Delay(void);
void Call_detect_delay(void);
void WT_20s_detect(void);
void Check_SCS_received(void);
void Check_frame_received(void);
void GS_presence_send(void);
void frame_ON_send(void);
void frame_OFF_send(void);
void framesend_takeline(void);
void frame_on_off( unsigned char command );
void occupancy_detect(void);
void _Initial_state(void);
void _Maintain_state(void);
void _ReTrigger_State(void);
void _Standby_state(void);
void Function_LM_GR(void);
void Function_KO119(char addrestype);
void Function_KO128(void);
void Function_KO166(char addrestype, char detectype, char LightReg);
void Function_KO168(char addrestype, char FuncMod, char LightReg);
void function_service_init(void);
void function_service(void);

#line 14 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\iccext.h"
/*                     - ICCEXT.H -

   Some extra declarations for non-ANSI functions used by the C library.

   $Revision: 2093 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/








  #pragma system_include












__intrinsic  double exp10(double);









#line 15 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"

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
	
	if(KO_conf.AddressType == 2)		// GR
	{
    CharToStr(GG ,buffer);
		TX_buffer[2] = buffer[0];
		TX_buffer[3] = buffer[1];

		switch(type)
		{
			case 3:
			case 5:
			case 6:
					TX_buffer[5] = 'D';
					TX_buffer[7] = '0';
			break;
			case 1:
					TX_buffer[5] = '2';
					TX_buffer[7] = '0';
					Sensor_mode.power_on_flag = 1;		// ON FRAME
					//KO_conf.status[1] = Status_ON;		//reyno 0616
					//DLL.lightness_load = T_5min5s;		// start timer 5min5s, start to calibrate the load provision
					//DLL.calc_OK_flag = 0; //reyno 0616
			 break;
			case 2:
					TX_buffer[5] = '2';
					TX_buffer[7] = '1';
					Sensor_mode.power_on_flag = 0;		// OFF FRAME
					KO_conf.status[1] = 0;		//reyno 0616
			break;
			case 4:
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
	else if(KO_conf.AddressType == 0 && type==3)	//P2P
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
	
	send_frame_pp_broad(TX_buffer, 50);
	
	if(type == 2)		// frame "OFF"
	{
			Time_delay.detect_waitting = 2000;
	}
	if(type == 3)
	{
		Sensor_mode.presence_send =1;
	}
	
}


//******************************************************************************
// 			send the frame P2P
//******************************************************************************
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
		KO_conf.status[1] = 0;		//reyno 0616
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
	org_ext_broad(TX_buffer, 50);
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

		send_frame_pp_ext_broad(TX_buffer, 50);
      	M2_type = 0;            			// ֡������Ϻ������־λ�����modality

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
//				result = x*y	y��factor,xx.xx,С�������λ
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
			if(Time_delay.DLL_low_20s_count > 20)
			{
				Time_delay.DLL_low_20s_count = 0;
				Time_delay.DLL_low_20s_enable = 0;
				//if(Configurators.M == '1')	
				//if(KO_conf.LightReg == 1)
					//frame_on_off('0');           				// send frame ON
				//else					
				Mode_frame_P2P('1','2','0','0','0','0','0');			// send P2P ON frame light on the load	
				regulation_timer_initial();
			}
		}
		else if((DLL.current_level > DLL.setpoint_OFF)&&(Sensor_mode.power_on_flag ==1)&&(DLL.calc_OK_flag == 1))
		{
			Time_delay.DLL_high_10min_enable = 1;
			Time_delay.DLL_low_20s_enable = 0;
			if(Time_delay.DLL_high_10min_count > 600)						// 10min may be too long 	
			{
				Time_delay.DLL_high_10min_count = 0;
				Time_delay.DLL_high_10min_enable = 0;
				//if(Configurators.M == '1')	
				//	frame_on_off('1');           				// send frame Off
				//else					
				Mode_frame_P2P('1','2','1','0','0','0','0');			// send P2P OFF frame light on the load	
				regulation_timer_initial();
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
	unsigned char buffer[2];
  if( DLL.start_regulation == 1 )
	{
			if(KO_conf.TypeLoop == 0)           								// in close loop
			{
				if(DLL.current_level < set_point)														// < setpoint		dim++ every 200ms
				{
					Time_delay.Dim_inc_enable = 1;
					if(Time_delay.Dim_inc_count > 400)
					{
						Time_delay.Dim_inc_count = 0;
						Time_delay.Dim_inc_enable = 0;
						//if(SCS_received.P2P_dimmer_full != 1)
						if(KO_conf.status[1] != 0x64)
						{
							Mode_frame_P2P('1','2','3','0','2','F','F');					// DIM++ 	step==2
							regulation_timer_initial();
							//SCS_received.P2P_dimmer_zero = 0;											// if DIM++ frame is sent, the flag SCS_received.P2P_dimmer_zero should be cleared
						}
					}
				}
				else if (DLL.current_level > (set_point + set_point/2))			// > setpoint(1+40%)	dim-- every 40s
				{
						Time_delay.Dim_dec_enable = 1;
						//if(Time_delay.Dim_dec_count > Regulation_600ms)
						if(Time_delay.Dim_dec_count > 20000)
						{
							Time_delay.Dim_dec_count = 0;
							Time_delay.Dim_dec_enable = 0;
							if (KO_conf.status[1] == 1)
							{
								Mode_frame_P2P('1','2','1','0','0','0','0'); //  OFF
								regulation_timer_initial();
							}
							else
							{
								if( KO_conf.status[1] != 0 ) //Reyno 0626
								{
									Mode_frame_P2P('1','2','4','0','1','F','F'); // DIM-- step==1
									regulation_timer_initial();
								}
							}
						}
				}
				else if(DLL.current_level > (set_point + set_point/5))			// > setpoint(1+20%)	dim-- every 20s
				{
						Time_delay.Dim_dec_enable = 1;
						//if(Time_delay.Dim_dec_count > Regulation_200ms)
						if(Time_delay.Dim_dec_count > 60000)
						{
							Time_delay.Dim_dec_count = 0;
							Time_delay.Dim_dec_enable = 0;
							if (KO_conf.status[1] > 1)
							{
								Mode_frame_P2P('1','2','4','0','1','F','F'); // DIM-- step==1
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
				if((KO_conf.DF ==0)&&(DLL.DF ==0))												//����һ�δ�close loopת��open loopʱ����������DF
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
						Mode_frame_P2P('1','2','1','0','0','0','0');					//  frame OFF
					}
					else
					{
						DLL.open_offset = factor_divcalc((set_point - DLL.open_actualevel*5), DLL.load_provision*5);
						CharToStr(DLL.open_offset ,buffer);
						Mode_frame_P2P('1','2','D',buffer[0],buffer[1],'F','F');// Set level for dimmer
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
		Mode_frame_P2P('1','2','4','0','1','F','F');				// DIM--	step==1
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
// DLL.current_level�Ǽ����Ӧ����ʵ�ʹ�����
// DLL.day_level�Ǵ�������ڲ���sensor��ȡ���Ĺ����ȵ�ֵ
//DLL.setpoint_M���ⲿ������ֵLUX��ADC�ı���ֵ�ٳ�10
//DLL.day_level�Ǵ�ADC��ȡ����ֵ
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
					DLL.lightness_load = 305;					// 5s
					DLL.PLv_5min = DLL.calc_level;
					DLL.calc_OK_flag = 0;
      }
     	else  if(DLL.calc_OK_flag != 1 && KO_conf.status[1] != 0)							// if the load is light on and load provision have not calibrated yet
      {																						// the provision of load is constant, no need to cablibrate every light on
				if(KO_conf.flag_PofL_Forced == 0)
				{
					//if(DLL.lightness_load > T_5mins && DLL.lightness_load < T_5mins + 2)					// load turn on less than 5 senconds
					if(DLL.lightness_load > 300 && DLL.lightness_load)
					{
						if( DLL.lightness_load < 300 + 2)
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
		DLL.calc_OK_flag = 1;																// ����close loop
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
	DLL.read_daylightSample = read_adc10bit ( 3 );
	DLL.daylight_SampleValue = DLL.daylight_SampleValue + (unsigned int) DLL.read_daylightSample;
	DLL.daylight_SampleCount++;
	if(DLL.daylight_SampleCount >= 10)				
	{

		not_bit(&PORTB,0);

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




	DLL.calc_level = (2143 * (unsigned long)DLL.day_level)/100;									// calculate the daylight level (LUX)around the sensor

//     DLL.calc_level = (DLL.setpoint_M * DLL.day_level)/10;									// calculate the daylight level (LUX)around the sensor
	
//		DLL.current_level = DLL.calc_level;
	if((KO_conf.TypeLoop == 0)&&(KO_conf.DF !=0))														// default :KO_conf.DF=5(ceiling sensor),KO_conf.DF=1(wall sensor)
	{
		if((Sensor_mode.power_on_flag == 1)&&(DLL.calc_OK_flag == 1))					// 0609
		//if(DLL.calc_OK_flag == 1)					// 0609
		{
			//DLL.current_level = DLL.calc_level + (unsigned long)(DLL.load_provision*(KO_conf.DF - 10))/KO_conf.DF;
			if(KO_conf.DF >= 10)
				DLL.current_level = DLL.calc_level + (((((unsigned long)DLL.load_provision)*KO_conf.status[1])/100)*(KO_conf.DF - 10))/KO_conf.DF; //Reyno 0623
			else
				//DLL.current_level = DLL.calc_level - (((((unsigned long)DLL.load_provision)*KO_conf.status[1])/100)*(10 - KO_conf.DF))/KO_conf.DF; //Reyno 0623
				//DLL.current_level = DLL.calc_level - (((((unsigned long)DLL.load_provision)*KO_conf.status[1])/100)*(10 - KO_conf.DF))/10; //Reyno 0623
				DLL.current_level = DLL.calc_level;	//DLL.current_level*KO_conf.DF/10;
		}
		else
		{
			DLL.current_level = DLL.calc_level;	//DLL.current_level*KO_conf.DF/10;
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
	(TIMSK0|=(1<<0));
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
	
	TCCR2A=0x33;
	TCCR2B = 0x19;
	//TCNT2=0x50;
	OCR2A=0xB8;
	OCR2B = 0x5C;
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
			(PORTC|=(1<<1));;
			temp = PIR_detect();
			//PIR_detect();
			asm("nop");
			if(temp)
				asm("nop");
			return temp;
			
		case 2:				//US only
			(PORTC&=(~(1<<1)));;
			get_us();
			return US_detection_en;

		case 3:				//PIR and US
			(PORTC&=(~(1<<1)));;
			temp = PIR_detect();
			//PIR_detect();
			get_us();
			if(US_detection_en && temp)
				return 1;

		case 4:				//PIR or US
			(PORTC&=(~(1<<1)));;
			get_us();
			PIR_detect();
			if(US_detection_en || PIR_detect())
				return 1;

		default:
			return 0;				
	}
}


/******************************************************************************
*	�����US��̽��ͣ��ʱ�䲻��̫��������Ӱ��IR tools�Ĳ�����ȡ		// alan 0604
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
				send_frame_pp_broad(buffer_short,50); //0707

        CharToStr(status,buffer);
        buffer_tx[10] = buffer[0];
        buffer_tx[11] = buffer[1];
				send_frame_pp_ext(buffer_tx,50);
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
			send_frame_pp_broad(buffer_short,50); //0707
    break;

    case 0x02://group
      buffer_short[0] = 'B';
		  buffer_short[1] = '5';
		  CharToStr(KO_conf.GR,buffer);
		  buffer_short[2] = buffer[0];
		  buffer_short[3] = buffer[1];
		  send_frame_pp_broad(buffer_short,50);
    break;

    case 0x03://general
      buffer_short[0] = 'B';
			buffer_short[1] = '1';
      CharToStr(status,buffer);
      buffer_short[6] = buffer[0];
      buffer_short[7] = buffer[1];
			send_frame_pp_broad(buffer_short,50); //0707
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
	if( state.main_state == 0x0000 )
	{
		if(key_result.short_pressed == 1)
		{
			key_result.short_pressed = 0;
			state.main_state = 0x9007;
			led_blinking(1000,1000);
      timer_flex_initial(60000);
		}
	}

	if( state.main_state == 0x9007 )
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = 0x0000;
			return 0;
		}
		else if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			state.main_state = 0x9008;
			timer_flex_initial(600000);
			led_blinking_stage2_initial(600000);
			led_blinking(250,250);
			send_frame_pp_broad("B0009900",50);

			if(KO_conf.GR != 0)
			{
				CharToStr(KO_conf.GR,buffer);
				buffer_tx[10] = buffer[0];
				buffer_tx[11] = buffer[1];
				send_frame_pp_ext_broad(buffer_tx,50);
			}
			else
			{
				state.main_state = 0x900E;
				send_frame_pp_ext_broad("D20001428C000940",50);
			}
		}			
		else if(Time_delay.LPB.count > 10000)				// group initial
		{
      Time_delay.LPB.count = 0;
      ee_flags.manual_initialize = 1;
			send_group_pnl_frame('2',KO_conf.GR,'7');
      factory_default();
			system_reset();
		}
	}

	if( state.main_state == 0x9008 )      //group remove
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
				send_frame_pp_broad(buffer_tx,50);
        timer_flex_initial(3000);
				conf_3s = 1;
			}
			state.main_state = 0x900C;
		}

		if(Time_delay.LPB.count > 10000)
		{
      key_result.short_pressed = 0;
			key_result.long_pressed = 0;

			if(KO_conf.Reference != 0)
				send_group_pnl_frame('2',KO_conf.Reference,'3');
			
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
			
			send_group_pnl_frame('2',KO_conf.GR,'F');
			send_frame_pp_broad("B000990F",50);
			send_group_pnl_frame('2',KO_conf.GR,'4');
			led_blinking(60,200);
      delay_ms(5000);
      state.main_state = 0;
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
		
	if( state.main_state == 0x900C)
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
			state.main_state = 0x900D;
		}
	}

	if( state.main_state == 0x900D)
	{
		if(KO_conf.Reference != 0)
				send_group_pnl_frame('2',KO_conf.Reference,'3');
		
		strncpy(buffer_tx,"D20001428C22094F",17);
		CharToStr(KO_conf.GR,buffer);
		buffer_tx[10] = buffer[0];
		buffer_tx[11] = buffer[1];
		send_frame_pp_ext_broad(buffer_tx,50);

		send_frame_pp_broad("B000990F",50);

		led_blinking_disable(0);
		state.main_state = 0x0000;
	}

	if( state.main_state == 0x900E )
	{
		/////////////////////////////////////////////////
		///      for solve GR==0         ////////////////
		if( key_result.short_pressed )
		{
			state.main_state = 0x9011;
		}
		/////////////////////////////////////////////////
		if( (g_asc_short_buffer[0] == 0xB8) && (g_asc_short_buffer[2] == 0x12))
		{
			ptop.A = g_short_buffer[2];
			ptop.PL = g_short_buffer[3];
			ptop.flag = 1;
			state.main_state = 0x900F;			//ptop step 3
		}
		if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x41))
		{
			send_frame_pp_ext_broad("D20001428C000945",50);
			state.main_state = 0x9010;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = 0x0000;
			return 0;
		}
	}

	if( state.main_state == 0x900F )
	{
		if( key_result.long_pressed == 1 )
		{
			key_result.long_pressed = 0;

			KO_conf.Reference = StrToChar(&ptop.A);
			ee_KO_conf.Reference = KO_conf.Reference;
			
			strncpy(buffer_tx,"D20001428C00094F",17);
			send_frame_pp_ext_broad(buffer_tx,50);
			led_blinking_disable(0);
			state.main_state = 0x0000;
		}
		else if((g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x21))
		{
			//StrToChar();
			KO_conf.DesAdd = g_asc_reception_buffer[1];
			ee_KO_conf.DesAdd = KO_conf.DesAdd;
			send_frame_pp_ext_broad("D20001428C000945",50);
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
			
			state.main_state = 0x9008;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = 0x0000;
			return 0;
		}
	}

	if( state.main_state == 0x9010 )
	{
		if( (g_asc_reception_buffer[6] == 0x09) && (g_asc_reception_buffer[7] == 0x06))
		{
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = KO_conf.GR;
			strncpy(buffer_tx,"D20001428C000940",17);
			CharToStr(KO_conf.GR,buffer);
			buffer_tx[10] = buffer[0];
			buffer_tx[11] = buffer[1];
			send_frame_pp_ext_broad(buffer_tx,50);
			state.main_state = 0x9011;
		}

		//add timeout
		if(Time_delay.timer_flex.time_out == 1)
		{
			led_blinking_disable(0);
			state.main_state = 0x0000;
			return 0;
		}
	}

	if( state.main_state == 0x9011 )
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
			state.main_state = 0x0000;
			return 0;
		}
	}
  return 0;
}

void scs_pnl_none_confed_master(void)
{
	if(state.main_state == 0x0000)
	{
		if(key_result.short_pressed == 1)
		{
			key_result.short_pressed = 0;
			state.main_state = 0x9001;
			led_blinking(1000,1000);
			timer_flex_initial(60000);
		}
	}

	if(state.main_state == 0x9001)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
			(PORTC|=(1<<7));
			led_blinking_disable(0);
			state.main_state = 0x0000;
		}
		
		if( key_result.short_pressed == 1 )
		{
			key_result.short_pressed = 0;
			state.main_state = 0x9002;
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

	if(state.main_state == 0x9002)
	{
		if(Time_delay.pnl_stage2.time_out == 1)
		{
			state.main_state = 0x9004;
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
				product_information.conf_type = 2;
				ee_product_information.conf_type = 2;
				KO_conf.AddressType = 0;
				ee_KO_conf.AddressType = 0;
			}
			state.main_state = 0x9004;
		}
		
    if(g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x21)
    {
      KO_conf.Reference = g_asc_reception_buffer[1];
			ee_KO_conf.Reference = g_asc_reception_buffer[1];
      frame_send_group_request();
      timer_flex_initial(3000);
      state.main_state = 0x9003;
    }

		////////////////////////////////////////////////////////////////////////
		//////////////  for none confed group sensor   /////////////////////////
		if(g_asc_reception_buffer[6] == 0x09 && (g_asc_reception_buffer[7] == 0x06 || g_asc_reception_buffer[7] == 0xF6))
		{
			load_default_advance_parameter();
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = g_asc_reception_buffer[5];
			KO_conf.AddressType = 2;
			ee_KO_conf.AddressType = 2;
			product_information.conf_type = 2;
      ee_product_information.conf_type = 2;
			send_group_pnl_frame('2',KO_conf.GR,'0');
			state.main_state = 0x9008;
		}
		
		if(Time_delay.LPB.count > 3000)				// group initial
		{
			key_result.short_pressed = 0;
			key_result.long_pressed = 0;
			load_default_advance_parameter();
			KO_conf.DesAdd = temp_variable.DesAdd;
			ee_KO_conf.DesAdd = temp_variable.DesAdd;
			KO_conf.AddressType = 0;
			ee_KO_conf.AddressType = 0;
			product_information.conf_type = 2;
			ee_product_information.conf_type = 2;
			frame_send_end_pnl();
			send_frame_pp_broad("B000990F",50);
			led_blinking_normal();
			state.main_state = 0x0000;
		}
	}

  if(state.main_state == 0x9003)
  {
		if(Time_delay.timer_flex2.time_out == 1)
		{
			state.main_state = 0x9004;
		}
		
    if(Time_delay.timer_flex.time_out == 1)
		{
      frame_send_enable_automatic_control();    //added by reyno
      frame_send_end_pnl(); //added by reyno
		  led_blinking_normal();
		  state.main_state = 0x0000;
		}

    if(flags.group_assigned)
    {
			load_default_advance_parameter();
      KO_conf.GR = g_asc_reception_buffer[5];
      ee_KO_conf.GR = g_asc_reception_buffer[5];
			KO_conf.AddressType = 2;
			ee_KO_conf.AddressType = 2;
      product_information.conf_type = 2;
      ee_product_information.conf_type = 2;
      frame_send_start_pnl_group_confed();
      key_result.short_pressed = 0;
      key_result.long_pressed = 0;
      state.main_state = 0x9008;
      //state.main_state = PNL_NONE_CONFED_STEP4;
    }
  }

  if(state.main_state == 0x9004)
  {
		PnL_NONE_end();
  }

}

void scs_pnl_advance_slave(void)
{
	unsigned char buffer_tx[17] = "D20001348C000941";
	unsigned char buffer[3];
	
	if(state.main_state == 0)
	{
		if(state.pnl_slave == 1)
		{
			if(key_result.short_pressed)
  	  {
  	    key_result.short_pressed = 0;
				if(flags.wait_GS_remove == 1)
				{
					flags.wait_GS_remove = 0;
					if(KO_conf.GS1 == temp_variable.GR) //remove
					{
						send_group_pnl_frame('4',KO_conf.GS1,'4');
						KO_conf.GS1 = 0;
						ee_KO_conf.GS1 = 0;
					}
					else
					{
						send_group_pnl_frame('4',KO_conf.GS2,'4');
						KO_conf.GS2 = 0;
						ee_KO_conf.GS2 = 0;
					}
					led_blinking_disable(0);
					state.main_state = 0;
				}
				else
				{
					led_blinking(1000,1000);
					timer_flex_initial(60000);
					state.main_state = 0x9019;
				}
			}
  	}
		else if(state.pnl_slave == 2)
		{
			if( key_result.short_pressed)
    	{
      	key_result.short_pressed = 0;
      	led_blinking(1000,1000);
				timer_flex_initial(60000);
				state.main_state = 0x9020;
    	}
		}
	}
	
	if(state.main_state == 0x9019)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
		  led_blinking_normal();
		  state.main_state = 0x0000;
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
				send_frame_pp_ext_broad(buffer_tx,50);
				led_blinking(250,250);
				state.main_state = 0x9030;
			}
			else if(KO_conf.GS2 == 0 || KO_conf.GS2 == temp_variable.GR)
			{
				KO_conf.GS2 = temp_variable.GR;
				ee_KO_conf.GS2 = temp_variable.GR;
				CharToStr(KO_conf.GS2,buffer);
				buffer_tx[10] = buffer[0];
				buffer_tx[11] = buffer[1];
				send_frame_pp_ext_broad(buffer_tx,50);
				led_blinking(250,250);
				state.main_state = 0x9030;
			}
			else
			{
				led_blinking(120,0);
				delay_ms(5000);
				led_blinking_disable(0);
				state.main_state = 0;
			}
		}
	}
	
	if(state.main_state == 0x9030)
	{
		if(key_result.short_pressed)
    {
			key_result.short_pressed = 0;
      if(KO_conf.GS1 == temp_variable.GR) //remove
			{
				send_group_pnl_frame('4',KO_conf.GS1,'4');
				KO_conf.GS1 = 0;
				ee_KO_conf.GS1 = 0;
			}
			else
			{
				send_group_pnl_frame('4',KO_conf.GS2,'4');
				KO_conf.GS2 = 0;
				ee_KO_conf.GS2 = 0;
			}
			led_blinking_disable(0);
			state.main_state = 0;
		}
	}
	
	if(state.main_state == 0x9020)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			if(KO_conf.GS1 == 0 || KO_conf.GS1 == temp_variable.GR)
			{
				led_blinking(250,250);
				state.main_state = 0x9021;
			}
			else if(KO_conf.GS2 == 0 || KO_conf.GS2 == temp_variable.GR)
			{
				led_blinking(250,250);
				state.main_state = 0x9021;
			}
			else
			{
				led_blinking(120,0);
				delay_ms(5000);
				state.main_state = 0;
				state.pnl_slave = 0;
				flags.scs_pnl_group_sensor_starded = 0;
				led_blinking_normal();
			}
		}
	}
	
	if(state.main_state == 0x9021)
	{
		send_group_pnl_frame('4',0x00,'1');
		send_group_pnl_frame('2',0x00,'5');
		timer_flex2_initial(3000);
		state.main_state = 0x9022;
	}
	
	if(state.main_state == 0x9022)
	{
		if(Time_delay.timer_flex2.time_out == 1)
		{
			send_group_pnl_frame('2',0x00,'F');
			send_frame_pp_broad("B000990F",50);
			led_blinking_normal();
			state.pnl_slave = 0;
	  	state.main_state = 0x0000;
		}
		else
		{
			if(g_asc_reception_buffer[3] == 0x42 && g_asc_reception_buffer[4] == 0x8C && g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x40)
			{
				if(KO_conf.GS1 == 0 || KO_conf.GS1 == g_asc_reception_buffer[5])
				{
					send_group_pnl_frame('4',KO_conf.GS1,'1');
				}
				else if(KO_conf.GS2 == 0 || KO_conf.GS2 == g_asc_reception_buffer[5])
				{
					send_group_pnl_frame('4',KO_conf.GS2,'1');
				}
				state.main_state = 0x9023;
			}
		}
	}
	
	if(state.main_state == 0x9023)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			send_group_pnl_frame('2',0x00,'F');
			send_frame_pp_broad("B000990F",50);
			led_blinking_normal();
			state.pnl_slave = 0;
	  	state.main_state = 0x0000;
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
			state.main_state = 0x9020;
    }
	
		if(state.pnl_slave == 2)
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
				state.main_state = 0;
				state.pnl_slave = 0;
				flags.scs_pnl_group_sensor_starded = 0;
				led_blinking_normal();
			}
		}
}

unsigned char scs_pnl_none_confed_slave(void)
{
	if(state.main_state == 0 && state.pnl_slave == 0)
	{
		if( key_result.short_pressed)
    {
     	key_result.short_pressed = 0;
     	led_blinking(1000,1000);
			timer_flex_initial(60000);
			state.main_state = 0x9032;
    }
	}
	
	if(state.main_state == 0x9032)
		{
			if(Time_delay.timer_flex.time_out == 1)
			{
		  	led_blinking_normal();
		  	state.main_state = 0;
			}
		
			if( key_result.short_pressed)
    	{
     		key_result.short_pressed = 0;
				state.main_state = 0x9031;
     		led_blinking(120,0);
				delay_ms(5000);
				state.main_state = 0;
				led_blinking_normal();
    	}
		}
	
	if(state.pnl_slave == 2)
	{
		if(state.main_state == 0)
		{
			if( key_result.short_pressed)
    	{
      	key_result.short_pressed = 0;
      	led_blinking(1000,1000);
				timer_flex_initial(60000);
				state.main_state = 3;
    	}
		}
	}
		
	if(state.main_state == 3)
	{
		if(Time_delay.timer_flex.time_out == 1)
		{
		  led_blinking_normal();
		  state.main_state = 0x0000;
			state.pnl_slave = 0;
		}
		
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			led_blinking(100,0);
			delay_ms(5000);
			state.main_state = 0;
			state.pnl_slave = 0;
			flags.scs_pnl_group_sensor_starded = 0;
			led_blinking_normal();
			return 1;
		}
	}
	else if(state.main_state == 4)
	{
		if(g_asc_reception_buffer[6] == 0x09 && g_asc_reception_buffer[7] == 0x40)
		{
			load_default_advance_parameter();
			KO_conf.GS1 = g_asc_reception_buffer[5];
			ee_KO_conf.GS1 = g_asc_reception_buffer[5];
			KO_conf.GR = g_asc_reception_buffer[5];
			ee_KO_conf.GR = g_asc_reception_buffer[5];
			send_group_pnl_frame('4',KO_conf.GS1,'1');
			state.main_state = 5;
		}
	}
	else if(state.main_state == 5)
	{
		if( key_result.short_pressed)
		{
			key_result.short_pressed = 0;
			product_information.conf_type = 2;
			ee_product_information.conf_type = 2;
			send_group_pnl_frame('2',KO_conf.GS1,'F');
			send_frame_pp_broad("B000990F",50);
			state.main_state = 0;
			state.pnl_slave = 0;
			flags.scs_pnl_group_sensor_starded = 0;
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
	(PORTC&=(~(1<<6)));
}

void led_blinking_disable(unsigned char state)
{
	Time_delay.led_on.enabled = 0;
	Time_delay.led_off.enabled = 0;
	if(state == 1)
		(PORTC&=(~(1<<7)));
	else if(state == 0)
		(PORTC|=(1<<7));
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

void all_reception_buffer_clear(void)
{
	unsigned char i;
	for(i=0;i<10;i++)
	{
		if(scs_frame[i].finished != 0)
		{
			scs_frame[i].finished = 1;
		}

    scs_frame[i].byte[20] = 0;
	}
	reception_buffer_clear(0);
	ir_buffer_clear();
}

void manual_reception_buffer_clear(void)
{
  unsigned char i;
	for(i=0;i<10;i++)
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
	
#line 1903 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"


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
	buffer_gateway[3] = ee_ID[6];
	buffer_gateway[4] = ee_ID[7];
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

	if(ee_product_information.conf_type == 0 || ee_product_information.conf_type == 1)
	{
    Configurators = ee_configurators;
		buffer[0] = Configurators.A;
		buffer[1] = Configurators.PL;
		KO_conf.DesAdd = StrToChar(buffer);
		ee_KO_conf.DesAdd = StrToChar(buffer);

    switch(Configurators.M)
    {
      case '0':

          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '8';
          ee_product_information.cen_system = 0;

      break;

      case '1':

          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '6';
          ee_product_information.cen_system = 0;

      break;

      case '2':

          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = '8';
          ee_KO[3] = '0';
          ee_product_information.cen_system = 1;
          ee_product_information.local_A = Configurators.A;
          ee_product_information.local_PL = Configurators.PL;

      break;

      case '3':

          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '8';
          ee_product_information.cen_system = 0;

      break;

      case '4':

          ee_KO[0] = '0';
          ee_KO[1] = '0';
          ee_KO[2] = 'A';
          ee_KO[3] = '6';
          ee_product_information.cen_system = 0;
          ee_KO_conf.Reference = ee_KO_conf.DesAdd;

      break;

      default:break;
    }
	}
	else if(ee_product_information.conf_type == 2)
	{
		Configurators.A = '0';
		Configurators.PL = '0';
		Configurators.M = '0';
		Configurators.S = '0';
		Configurators.T = '0';	

    buffer[0] = ee_KO[2];
    buffer[1] = ee_KO[3];
    ko_confed = StrToChar(buffer);

   switch(ko_confed)
   {
    case 0xA8:
      ee_product_information.cen_system = 0;
    break;

    case 0xA6:
      ee_product_information.cen_system = 0;
      //ee_KO_conf.Reference = ee_KO_conf.DesAdd;
    break;

    case 0x77:
      ee_product_information.cen_system = 0;
    break;

    case 0x80:
      ee_product_information.cen_system = 1;
    break;

    case 0xA4:
      ee_product_information.cen_system = 1;
    break;

    case 0xA5:
      ee_product_information.cen_system = 1;
    break;

    default:break;
   }


#line 2071 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\application.c"


   switch(ko_confed)
   {
    case 0x77:
      ee_product_information.cen_system = 0;
    break;

    case 0xA5:
      ee_product_information.cen_system = 1;
    break;

    case 0x70:
      ee_product_information.cen_system = 0;
    break;

    default:break;
   }

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

    if(flags.confed == 0)
		  led_blinking(120,120);

		Configurators.A = '0';
		Configurators.PL = '0';
		Configurators.M = '0';
		Configurators.S = '0';
		Configurators.T = '0';	
	}

  if( ee_product_information.ID_factory_assigned )
    (PORTC|=(1<<6));
  else
    (PORTC&=(~(1<<6)));

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
    case 0x1000:
      if(get_key())
			{
        key_result.short_pressed = 0;
        key_result.long_pressed = 0;
        state.main_state = 0x2000;
				diagnostic_frame();	
				flags.AA_received = 0;
				flags.parameter_setting_wrong = 0;
				flags.parameter_write_right = 0;
			}
    break;

    case 0x2000:
			timer_flex_initial(660000);				//11 minutes time out
			led_blinking(1000,1000);
			state.main_state = 0x2100;
    break;

    case 0x2100:
			if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_normal();
        send_frame_pp_ext_broad("D20001348C0000FA",50);
				state.main_state = 0x0000;
			}
    break;

    case 0x2003:
      if(get_key())
			{
        state.main_state = 0x2000;
				diagnostic_frame();	
			}
      else if(Time_delay.timer_flex.time_out == 1)
      {
        state.main_state = 0x0000;
      }
    break;

    case 0x2001:
			timer_flex_initial(660000);				//11 minutes time out
			led_blinking(1000,1000);
			state.main_state = 0x2002;
    break;

    case 0x2002:
      if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_normal();
				state.main_state = 0x0000;
			}
    break;

    default:break;
  }

		if(product_information.conf_type == 2)
		{
			if( state.main_state == 0x0000 )
			{
				if(flags.app_disable == 0)
				{
					function_service();			// add by alan 20090424
				}
			}
		}
		else if(product_information.conf_type == 0 || product_information.conf_type == 1)
		{
			if( state.main_state == 0x0000 )
			{
				function_service();			// add by alan 20090424
			}
		}

		if(product_information.conf_type == 3 || product_information.conf_type == 2)
		{
			ir_pnl();								//0218
	
    	if(product_information.conf_type == 2)
			{
				if(flags.scs_pnl_group_sensor_starded)
				{
					scs_pnl_advance_slave();
				}
				else
				{
					if(KO_conf.AddressType == 2)
						scs_pnl_advance_master();
					else if(KO_conf.AddressType == 0)
						scs_pnl_none_confed_master();		
				}				
			}

			if(product_information.conf_type == 3)
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
				send_frame_pp_ext_broad("D000010E00000000",50);
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
	send_frame_pp_broad("B0009900",50);
}

void frame_send_enable_automatic_control(void)
{
  send_frame_pp_broad("B000990F",50);
}

void frame_send_start_pnl_none_group_confed(void)
{
	send_frame_pp_ext_broad("D20001428C000940",50);
}

void frame_send_start_pnl_group_confed(void)
{
  unsigned char buffer_tx[17] = "D20001428C000940";
  unsigned char buffer[3];

  CharToStr(KO_conf.GR,buffer);
  buffer_tx[10] = buffer[0];
  buffer_tx[11] = buffer[1];
  send_frame_pp_ext_broad(buffer_tx,50);
}

void frame_send_end_pnl(void)
{
	send_frame_pp_ext_broad("D20001428C00094F",50);
}

void frame_send_group_request(void)
{
  send_frame_pp_ext_broad("D20001428C000945",50);
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
		
	if(state.main_state == 0x0000)
	{
  	if(product_information.conf_type == 3 && flags.confed == 0)
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
				send_group_pnl_frame('2',KO_conf.Reference,'3');
			
	strncpy(buffer_tx,"D20001428C00094F",17);
	CharToStr(KO_conf.GR,buffer);
	buffer_tx[10] = buffer[0];
	buffer_tx[11] = buffer[1];
	send_frame_pp_ext_broad(buffer_tx,50);
	send_frame_pp_broad("B000990F",50);
	led_blinking_disable(0);
	state.main_state = 0x0000;
}

void PnL_NONE_end(void)
{
	frame_send_end_pnl();
  frame_send_enable_automatic_control();
  led_blinking_normal();
	state.pnl_slave = 0;
	state.main_state = 0x0000;
}

void regulation_timer_initial(void)
{
	Time_delay.regulation.stack_top = 200;
	Time_delay.regulation.count = 0;
	Time_delay.regulation.time_out = 0;
	Time_delay.regulation.started = 1;
	Time_delay.regulation.enabled = 1;
}
