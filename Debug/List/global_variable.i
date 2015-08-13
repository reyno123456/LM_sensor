#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
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
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet re鐄
	unsigned char pipe[20];             //
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

/****************	add by alan end	**************************/
#line 2 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\IR.h"






struct SIR_reception
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet re鐄
	unsigned char pipe[14];             //
	unsigned char begin_actual;            ///< Si Nbre_Octet = 0 : la trame est vide
	unsigned char info;						///< bit 0 : 1:trame compl鑤e
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

#line 3 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
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

  // unsigned char    daylevelsenden;   // 用于modality2,每间隔5min发送一帧数据，或者光亮度变化超过3%时，立刻发送daylevel数据帧


   unsigned char    first_detect;
/********************************************************************/
// Add by alan for the daylight level set start
/********************************************************************/
  unsigned char   calc_OK_flag;         //20090302
  unsigned int    setpoint_H;           // 暂时保留


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
unsigned int factor_mulcalc(unsigned int x,unsigned int y);	//result = x*y	y是factor,xx.xx,小数点后两位
void frame_M2_answer( unsigned char type);
void Mode_frame_GR(char GG, char type);
void Mode_frame_P2P(char type,char cmd,char func0, char func1,char func2 ,char func3,char func4);
void regulation_timer_initial(void);

// add by alan 20090408 end


//		(un-corrected value * D.F - PfL*ratio) / D.F + PfL*ratio
//		un-corrected value + PfL(D.F - 1)

//		(un-corrected value * D.F - PfL) / D.F + PfL
//		un-corrected value - PfL / D.F + PfL
#line 4 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\PIR.h"
//PIR.h









/*  PIR信号检测限定 */
#line 18 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\PIR.h"


/* PIR灵敏度定义 */		






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





#line 5 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
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

#line 6 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

//unsigned char scs_frame[5][20];
unsigned char g_timer2_flag = 0;
unsigned char g_temp;
volatile struct struct_scs_frame scs_frame[10];
volatile unsigned char g_configurator[5];
volatile struct SConfigurators Configurators;
volatile struct SKO_Configuration KO_conf;
//__eeprom struct SKO_Configuration ee_PnG_KO_conf;
//struct SKO_Configuration temp_KO_conf;
volatile struct SState state;
volatile struct Sframe_extended_type frame_extended_type;
volatile unsigned char g_reception_buffer[17];
volatile unsigned char g_asc_reception_buffer[8];
volatile unsigned char g_short_buffer[8];
volatile unsigned char g_asc_short_buffer[4];
volatile unsigned char g_ir_reception[14];
volatile struct Sproduct_info product_info;
volatile struct SIR_reception IR_reception;
volatile struct Sflag_timer flag_timer;
volatile struct SDll DLL;
volatile struct STimeDelay Time_delay;
volatile struct PIR pir;
volatile unsigned int pir_total = 0;
volatile unsigned char us_result = 0;
volatile unsigned int us_total = 0;
volatile unsigned int motion_total = 0;
volatile unsigned char US_detection_en;
volatile unsigned long int modality0_delay_ms;
volatile unsigned char g_key_value = 0;
volatile unsigned char g_virtual_basci_configuration_flag = 0;
const int daylight_motion[] = {515,168,166,119,128,164,165};
const int daylight[] = {516,166,164};
const int motion[] = {511,119,165,122};
volatile struct Ukey_result key_result;
__eeprom unsigned char g_ns_index;
volatile struct s_flags flags;
__eeprom struct s_ee_flags ee_flags;
volatile unsigned char PIR_detection_en;   // add by alan 20090409

volatile char tx1_buffer[14];
volatile unsigned char tx1_wr_index,tx1_rd_index,tx1_counter;

struct S_product_information product_information;
struct S_product_information temp_product_information;
volatile unsigned char KO[4];
struct s_parameters parameters;
struct s_temp_variable temp_variable;
struct s_flags_muti_step flags_muti_step;

__eeprom struct s_ee_variable ee_variable;


  __eeprom unsigned char ee_KO_last[4] = {'0','2','0','3'};
  const unsigned char flash_KO[4] = {'0','2','0','3'};
  __eeprom unsigned char ee_KO[4] = {'0','2','0','3'};






	





	

	__eeprom struct s_parameter ee_parameter={'0','F','2','2','2','2',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};

	





	





	





/*	
#ifdef HARDWARE_PIR
	__eeprom struct s_parameter ee_parameter={'0','5','2','0','2','0',
																						'0','1','0','1','0','1',
																						'0','1','0','1','0','1'};
#endif
	
#ifdef HARDWARE_US
	__eeprom struct s_parameter ee_parameter={'0','5','2','0','2','1',
																						'0','1','0','1','0','1',
																						'0','1','0','1','0','1'};
#endif
	
#ifdef HARDWARE_PIR_US
  __eeprom struct s_parameter ee_parameter={'0','5','2','2','2','2',
																						'0','1','0','1','0','1',
																						'0','1','0','1','0','1'};
#endif
	
#ifdef DAYLIGHT_ONLY
	__eeprom struct s_parameter ee_parameter={'0','5','2','2','2','8',
																						'0','1','0','1','0','1',
																						'0','1','0','1','0','1'};
#endif
*/
#line 135 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
	__flash struct SKO_Configuration flash_KO_168=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	50,	0,	0,	//24
		100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0, 0				//34
	};


  __flash struct SKO_Configuration flash_KO_166=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	0,	0,	0,	0,	//14
		0,	0,	0,	0,	0,	//19
		0,	0,	0,	0,	0,	//24
		0,	0,	0,	0,	1,	//29	default daylight 88 * 10 = 880(ADC value)
		0,	0,	0,	0, 0				//34
	};

#line 170 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"
	__flash struct SKO_Configuration flash_KO_119=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	5,	0,	0,	//24
		100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0,  0				//34
	};


  __flash struct SKO_Configuration flash_KO_128=
  {
	  0,	0,	0,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	0,	30,	0,	0,	//14
		0,	0,	0,	0,	0,	//19
		1,	1,	4,	0,	0,	//24
		0,	0,	0,	0,	0,	//29	default daylight 88 * 10 = 880(ADC value)
		0,	0,	0,	0, 0				//34
	};

  __flash struct SKO_Configuration flash_KO_165=
  {
	  0,	0,	0,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	0,	30,	0,	0,	//14
		0,	0,	0,	0,	0,	//19
		1,	1,	4,	0,	0,	//24
		0,	0,	0,	0,	0,	//29	default daylight 88 * 10 = 880(ADC value)
		0,	0,	0,	0, 0				//34
	};
	
	__flash struct SKO_Configuration flash_KO_515=
  {
	  0,	0,	0,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	0,	0,	0,	0,	//14
		0,	0,	0,	0,	0,	//19
		0,	0,	0,	0,	0,	//24
		0,	0,	0,	0,	0,	//29	default daylight 88 * 10 = 880(ADC value)
		0,	0,	0,	0, 0				//34
	};


#line 223 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

#line 231 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

__eeprom struct SConfigurators ee_configurators=
{
  '0','0','0','0','0','0'
};

#line 249 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"


__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	2,	5,	0,	0,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	3,	4,	4,	0, 0		//34
};


#line 275 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

#line 288 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

#line 301 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

#line 314 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

#line 327 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.c"

__eeprom volatile unsigned char ee_ID[9] = {'0','0','0','5','5','4','F','E','0'};
__eeprom struct S_product_information ee_product_information =
{
  3,0,'0','0',0,0
};

__eeprom unsigned char ee_scenario_index = 0;

__eeprom struct s_scenario  ee_scenario[16] =
{
  1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,0,0,0,0,0
};

//************************** add by alan begin 	*****************************//

 	__eeprom unsigned int  eep_setpoint[4];
 	__eeprom unsigned int  eep_factor;	
	__eeprom unsigned char eep_M2_hour;	
 	__eeprom unsigned char eep_M2_min;	
 	__eeprom unsigned char eep_M2_sec;
 	__eeprom unsigned char eep_M2_sens;
 	unsigned long int   M2_timer;
	unsigned long int   M2_timer_count;
	unsigned char 	  	M2_type;
	unsigned char       motion_resutl;
	unsigned int        set_point;
	volatile unsigned long int Delay_Time_set;
	unsigned char 	during_on_cnt;
 	unsigned char 	during_off_cnt;
	unsigned char 	Walk_Through_flag;
 	unsigned char 	First_detection_enable;

	struct SSensor_mode Sensor_mode;
	struct SSCS_received SCS_received;


//************************** add by alan end	***************************//
	
void global_variable_initial()
{
	unsigned char i;
	unsigned char j;

	for(i=0;i<10;i++)
	{
		scs_frame[i].next = 0;
		scs_frame[i].finished = 0;
		scs_frame[i].decoded = 0;
		for(j = 0;j< 20;j++)
		{
			scs_frame[i].byte[j] = 0;
		}
	}

	state.programming = 0;
	state.test = 0;
	state.normal = 0;

	frame_extended_type.D0 = 0;
	frame_extended_type.D1 = 0;
	frame_extended_type.D2 = 0;
	frame_extended_type.D5 = 0;

	IR_reception.CRC_OK = 0;

	Time_delay.timer_20s.count = 0;
	Time_delay.timer_20s.time_out = 0;
	Time_delay.timer_20s.enabled = 0;
	Time_delay.timer_20s.started = 0;

	Time_delay.timer_5m.count = 0;
	Time_delay.timer_5m.time_out = 0;
	Time_delay.timer_5m.enabled = 0;
	Time_delay.timer_5m.started = 0;

	DLL.first_detect = 0;
	us_result = 0;

	Time_delay.LPB.count = 0;
	Time_delay.LPB.time_out = 0;
	Time_delay.LPB.enabled = 0;
	Time_delay.LPB.started = 0;

	key_result.short_pressed = 0;
	key_result.long_pressed = 0;

	state.programming = 0;
	state.test = 0;
	state.normal = 0;
	state.configuration_method = 0;
	state.main_state = 0;
	state.pnl_slave = 0;

	//g_ns_index = 0;

	flags.id_confed = 0;
	flags.id_ack = 0;
	flags.id_request_enabled = 1;
	flags.request_83 = 0;
	flags.virtul_configuration_right = 0;
  flags.KO_conf_right = 0;

  flags_muti_step.cen_system_step = 0;
	
	flags.parameter_write_right = 0;
	flags.KO_erase_all = 0;
	flags.KO_erase_main = 0;
	flags.KO_erase_scenario = 0;
	
	Time_delay.pir_wait_40s = 0;
	Time_delay.pir_warmup_ok = 0;
	
	DLL.calc_OK_flag = 0; //reyno 0610
	Time_delay.IR.time_out = 1;//reyno 0616
	Sensor_mode.flag_leader_group = 0;
	Sensor_mode.init_OK = 0;
	flags.scenario_scs_confed = 0;
}
