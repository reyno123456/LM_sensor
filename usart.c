//usart.c

#include <ioavr.h>
#include <stdio.h>
#include <inavr.h>
#include "usart.h"
#include "board.h"
#include "moudle_SCS.h"
#include "global_variable.h"
#include "application.h"
#include "string.h"

char rx_buffer[RX_BUFFER_SIZE]; // 接收缓冲区，为char型变量组成的数组，该数组构成环形队列，个数为RX_BUFFER_SIZE 
unsigned char rx_wr_index,rx_rd_index,rx_counter;
// This flag is set on USART Receiver buffer overflow
char rx_buffer_overflow;   //接收缓冲区溢出标志

char tx_buffer[TX_BUFFER_SIZE];
unsigned char tx_wr_index,tx_rd_index,tx_counter;

#ifdef DEBUG
	unsigned char g_RxBuffer[RX_BUFFER_SIZE];
	unsigned char RxNumber;
	ISR(USART0_RX_vect)
	{
		g_RxBuffer[RxNumber] = UDR0;
		RxNumber++;
	}
#else

#pragma vector=USART0_RX_vect
__interrupt void usart0_rx_ser(void)
{
	unsigned char temp;
	unsigned char i;
	volatile unsigned char current = 0xFF;
  volatile unsigned char compared = 0;
	temp = UDR0;
	
	for(i=0;i<DEEP;i++)
	{
		if(scs_frame[i].finished == 0)
		{
			current = i;
			break;
		}
	}
  
  if(scs_frame[current].finished == 0)
	{

			if(temp == '$')
			{
				scs_frame[current].next = 0;
			}	
							
			scs_frame[current].byte[scs_frame[current].next++] = temp;

			if(temp == 0x0D)
			{
				if(current == 0)
				{
					scs_frame[current].finished = 1;
				}	
				else
				{
          for(i=0;i<current;i++)
          {
            if(strcmp(&scs_frame[current].byte[0], &scs_frame[i].byte[0]) == 0)
            {
              scs_frame[current].finished = 0;
              compared = 1;
              break;
            }
          }
          
          if(compared)
          {
            scs_frame[current].finished = 0;
          }
					else
					{
						scs_frame[current].finished = 1;
					}
				}

				//return;
			}
		}

}
#endif

#pragma vector=USART0_TX_vect
__interrupt void usart0_tx_ser(void)
{
    if (tx_counter)
    {
           --tx_counter;
           UDR0=tx_buffer[tx_rd_index];
           if (++tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
    }; 
}
/**//*发送单个字符*/
void put_c(unsigned char c)
{
    while (tx_counter == TX_BUFFER_SIZE);   //发送数据队列中还有数据没有发送完，等待

    __disable_interrupt();
    if (tx_counter || ((UCSR0A & DATA_REGISTER_EMPTY)==0))    //若发送数据队列有数据或者数据寄存器UDR非空时执行(因为队列先进先出的原因，所以，c要放进非空的发送数据队列里面)
    {
           tx_buffer[tx_wr_index]=c;
           if (++tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
           ++tx_counter;
       }
    else
           UDR0=c;
    __enable_interrupt();
		
}
/**//*发送字符串*/
void put_s(unsigned char *ptr)
{
	//reception_buffer_clear();
		//LLED_ON;
    while (*ptr)
    {
        put_c(*ptr++);
    }
    //put_c(0x0D);
		//LLED_OFF;
    //put_c(0x0A);  //结尾发送回车换行
}

/**//*USART 初始化*/
void init_USART0(void)
{
	// USART0 initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART0 Receiver: On
	// USART0 Transmitter: On
	// USART0 Mode: Asynchronous
	// USART0 Baud Rate: 38400
	
	UCSR0A=0x00;
	UCSR0B=0xD8;
	UCSR0C=0x06;
	UBRR0H=0x00;
	UBRR0L=0x0B;
	

//test only for transmiter
/*
	UCSR0A=0x00;
	UCSR0B=0x48;
	UCSR0C=0x06;
	UBRR0H=0x00;
	UBRR0L=0x0B;
*/
}
