//usart.h

//常量定义
#define BAUDRATE        9600    //波特率
//#define F_CPU            4000000  //晶振频率4.0MHz

#define RXB8 1
#define TXB8 0
#define PE 2    //M16
//#define UPE 2    //M128
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

//宏定义
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<PE)    //M16
//#define PARITY_ERROR (1<<UPE)    //M128
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART Receiver buffer
// 全局变量,会在中断服务程序中被修改，须加volatile限定，不要就会出错啦
#ifdef DEBUG
	#define RX_BUFFER_SIZE 16         // 接收缓冲区大小，可根据需要修改
#else
	#define RX_BUFFER_SIZE 200
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE 16

// 函数声明
char get_c(void);
void put_c(unsigned char c);
void put_s(unsigned char *ptr);
void init_USART0(void);
