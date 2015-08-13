#ifndef _H_CONFIGURATION
#define _H_CONFIGURATION

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
#endif
