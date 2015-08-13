#include "moudle_SCS.h"
#include "IR.h"
#include "application.h"
#include "PIR.h"
#include "board.h"

//unsigned char scs_frame[5][20];
unsigned char g_soft[] = "000000";
unsigned char g_hard[] = "00";
unsigned char g_year[] = "00";
unsigned char g_week[] = "00";
unsigned char g_model[] = "000000";

__eeprom unsigned char ee_soft[] = "010600";
__eeprom unsigned char ee_hard[] = "01";
__eeprom unsigned char ee_year[] = "09";
__eeprom unsigned char ee_week[] = "50";
__eeprom unsigned char ee_model[] = "062020";
__eeprom unsigned char ee_printed_id[] = "00050000";

__flash const unsigned char error_109[] = "  Error: 109 ";
__flash const unsigned char error_110[] = "  Flash Full ";
__flash const unsigned char error_111[] = "  ID Write Error";
__flash const unsigned char error_112[] = "  Wrong Software";
__flash const unsigned char error_113[] = "Hard or Date error";

__flash const unsigned char error_114[] = "PnG Setting error";

__flash const unsigned char right_100[] = "PnG Successful";
__flash const unsigned char right_101[] = "Already Confed";
//__flash const unsigned char blank[] = "                  ";
  __flash const unsigned char blank[] = "  Configing...    ";

struct S_sensor_info stru_sensor = {
"S",
"0950",
"00050000",
"020",
"02",
"01",
"010600",
"AAAAAA",
"N",
};

__eeprom unsigned int ee_page = 0;
__eeprom unsigned int ee_page_address = 0;

volatile unsigned int g_dataflash_page_address = 0;
struct S_usb_command usb_command;

unsigned char g_lux[5];
unsigned char g_timer2_flag = 0;
unsigned char g_temp;
volatile struct struct_scs_frame scs_frame[DEEP];
volatile unsigned char g_configurator[5];
volatile struct SConfigurators Configurators;
volatile struct SKO_Configuration KO_conf;
//__eeprom struct SKO_Configuration ee_PnG_KO_conf;
//struct SKO_Configuration temp_KO_conf;
volatile struct SState state;
//volatile struct Sframe_extended_type frame_extended_type;
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

volatile char tx1_buffer[TX1_BUFFER_SIZE];
volatile unsigned char tx1_wr_index,tx1_rd_index,tx1_counter;

volatile unsigned char eventflag2_g=0;
unsigned int  cell_W,cell_H, vx,vy,avg_x,avg_y,xmin,ymin,xmax,ymax;
float	  x_para,y_para;
char	  Menu_status;	//alan
struct S_product_information product_information;
struct S_product_information temp_product_information;
volatile unsigned char KO[4];
struct s_parameters parameters;
struct s_temp_variable temp_variable;
struct s_flags_muti_step flags_muti_step;

__eeprom struct s_ee_variable ee_variable;

#ifdef NONE_CONFED_203
  __eeprom unsigned char ee_KO_last[4] = {'0','2','0','3'};
  const unsigned char flash_KO[4] = {'0','2','0','3'};
  __eeprom unsigned char ee_KO[4] = {'0','2','0','3'};

#ifdef LM018
	__eeprom struct s_parameter ee_parameter={'0','F','2','0','2','0',
																						'0','1','0','0','0','0',		//software version
																						'0','1','0','9','2','8'};		//hardware version
#endif
	
#ifdef LM056
	__eeprom struct s_parameter ee_parameter={'0','F','2','0','2','1',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};
#endif
	
#ifdef LM057
	__eeprom struct s_parameter ee_parameter={'0','F','2','2','2','2',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};
#endif
	
#ifdef LM076
	__eeprom struct s_parameter ee_parameter={'0','F','2','0','2','4',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};
#endif
	
#ifdef LM077
	__eeprom struct s_parameter ee_parameter={'0','F','2','0','2','3',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};
#endif
	
#ifdef LM020
	__eeprom struct s_parameter ee_parameter={'0','F','2','0','2','9',
																						'0','1','0','0','0','0',
																						'0','1','0','9','2','8'};
#endif
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
#ifdef WALLCORNER
  __flash struct SKO_Configuration flash_KO_168=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	10,	0,	10,	//24
		60,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0, 0				//34
	};
#else
	__flash struct SKO_Configuration flash_KO_168=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	50,	0,	10,	//24
		100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0, 0				//34
	};
#endif

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

#ifdef WALLCORNER
  __flash struct SKO_Configuration flash_KO_119=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	1,	0,	10,	//24
		60,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0,  0				//34
	};
#else
	__flash struct SKO_Configuration flash_KO_119=
  {
	  0,	0,	1,	0,	0,	//4
		0,	0,	0,	0,	0,	//9
		0,	15,	0,	1,	0,	//14
		0,	0,	0,	0,	0,	//19
		3,	2,	5,	0,	10,	//24
		100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
		3,	4,	4,	0,  0				//34
	};
#endif

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
#endif

 #ifdef NONE_CONFED_204
  const unsigned char flash_KO[4] = {'0','2','0','4'};
   __eeprom unsigned char ee_KO[4] = {'0','2','0','4'};
   __eeprom struct s_parameter ee_parameter={'0','5','2','0','2','0',
																							'0','1','0','1','0','1',
																							'0','1','0','1','0','1'};
 #endif

#ifdef NONE_CONFED_1FF
   const unsigned char flash_KO[4] = {'0','1','F','F'};
   __eeprom unsigned char ee_KO[4] = {'0','1','F','F'};
   __eeprom struct s_parameter ee_parameter={'0','5','2','0','2','1',
																							'0','1','0','1','0','1',
																							'0','1','0','1','0','1'};
#endif

__eeprom struct SConfigurators ee_configurators=
{
  '0','0','0','0','0','0'
};

#ifdef LM018
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	0,	5,	0,	10,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	1,	1,	1,	0, 0		//34
};
#endif

#ifdef LM057
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	2,	5,	0,	10,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	3,	4,	4,	0, 0		//34
};
#endif

#ifdef LM056
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	2,	5,	0,	10,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	2,	2,	2,	0, 0		//34
};
#endif

#ifdef LM077
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	2,	1,	0,	10,	//24
	60,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	3,	4,	4,	0, 0		//34
};
#endif

#ifdef LM076
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	2,	1,	0,	10,	//24
	60,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	1,	1,	1,	0, 0		//34
};
#endif

#ifdef LM020
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	0,	5,	0,	10,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	1,	1,	1,	0, 0		//34
};
#endif

#ifdef LM028
__eeprom struct SKO_Configuration ee_KO_conf=
{
  0,	0,	0,	0,	0,	//4
	0,	0,	0,	0,	0,	//9
	0,	15,	0,	0,	0,	//14
	0,	0,	0,	0,	0,	//19
	3,	0,	5,	0,	10,	//24
	100,	255,	0,	0,	2,	//29	default daylight 88 * 10 = 880(ADC value)
	1,	1,	1,	0, 0		//34
};
#endif

__eeprom volatile unsigned char ee_ID[9] = {'0','0','0','5','5','4','F','E','0'};
__eeprom struct S_product_information ee_product_information =
{
  2,0,'0','0',0,0
};

__eeprom unsigned char ee_scenario_index = 0;

__eeprom struct s_scenario  ee_scenario[SCENARIO_NUMBER] =
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

__eeprom struct s_factory_variable ee_factory_variable = {0,0,0,0};

__eeprom unsigned int ee_main_state = 0;
double g_slope;
__eeprom double ee_slope = 1;

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

	for(i=0;i<DEEP;i++)
	{
		scs_frame[i].next = 0;
		scs_frame[i].finished = 0;
		scs_frame[i].decoded = 0;
		for(j = 0;j< NUMBER_BYTE_SCS;j++)
		{
			scs_frame[i].byte[j] = 0;
		}
	}

	state.programming = 0;
	state.test = 0;
	state.normal = 0;

	//frame_extended_type.D0 = 0;
	//frame_extended_type.D1 = 0;
	//frame_extended_type.D2 = 0;
	//frame_extended_type.D5 = 0;

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
	state.main_state = NORMAL;
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
	Time_delay.relay.time_out = 1;
	
	flags.id_confed = ee_product_information.ID_factory_assigned;
	
	ee_soft[6] = 0;
	ee_hard[2] = 0;
	ee_year[2] = 0;
	ee_week[2] = 0;
	ee_model[6] = 0;
	ee_printed_id[8] = 0;
}
                                      		