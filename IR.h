#ifndef _H_IR
#define _H_IR

#define IR_RX_BUFFER_NUMBER 14
#define DATA_UD1_EMPTY (1<<UDRE1)

struct SIR_reception
{         ///< Contient les octets de la trame n et n-1 ainsi que le nombre d'octet reçu
	unsigned char pipe[IR_RX_BUFFER_NUMBER];             //
	unsigned char begin_actual;            ///< Si Nbre_Octet = 0 : la trame est vide
	unsigned char info;						///< bit 0 : 1:trame complète
	unsigned char finished;
	unsigned char CRC_OK;
};

void init_USART1(unsigned long int baud_rate);
// USART Transmitter buffer
#define TX1_BUFFER_SIZE 14

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

#endif
