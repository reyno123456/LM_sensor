//usart.h

//��������
#define BAUDRATE        9600    //������
//#define F_CPU            4000000  //����Ƶ��4.0MHz

#define RXB8 1
#define TXB8 0
#define PE 2    //M16
//#define UPE 2    //M128
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

//�궨��
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<PE)    //M16
//#define PARITY_ERROR (1<<UPE)    //M128
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART Receiver buffer
// ȫ�ֱ���,�����жϷ�������б��޸ģ����volatile�޶�����Ҫ�ͻ������
#ifdef DEBUG
	#define RX_BUFFER_SIZE 16         // ���ջ�������С���ɸ�����Ҫ�޸�
#else
	#define RX_BUFFER_SIZE 200
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE 16

// ��������
char get_c(void);
void put_c(unsigned char c);
void put_s(unsigned char *ptr);
void init_USART0(void);
