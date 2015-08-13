#include "usb_command.h"
#include "global_variable.h"
#include "moudle_SCS.h"
#include "dataflash.h"
#include <ioavr.h>
#include <inavr.h>
#include "printer.h"
#include "board.h"

void usb_decode(void)
{
	if(usb_command.decoded == 0)
	{
		if(usb_command.pipe[0] == '0' && usb_command.pipe[1] == '1') 
		{
			if(usb_command.pipe[2] == '0' && usb_command.pipe[3] == '1')
			{
				asm("nop");
				delay_ms(50);
				upload_information();
				asm("nop");
			}
			else if(usb_command.pipe[2] == '0' && usb_command.pipe[3] == '2')
			{
				//dataflash_chip_erease();
				chip_erease_one_command();
			}
			else if(usb_command.pipe[2] == '8' && usb_command.pipe[3] == '0')
			{
				write_full_item();
			}
		}
		else if(usb_command.pipe[0] == '0' && usb_command.pipe[1] == '3')
		{
			if(usb_command.pipe[2] == '0' && usb_command.pipe[3] == '1')
			{
				send_items();
			}
		}
		
		usb_command.decoded = 1;
	}
}

__flash unsigned char label_usb_1[] = "$02010000";
unsigned char upload_information(void)
{
	volatile unsigned int i = 0;
	volatile unsigned int j = 0;
	volatile unsigned char temp = 0xFF;	
	unsigned char delay_flag = 0;
	
	DF_SPI_init();
	
	Cont_Flash_Read_Enable (0 ,0);
	
	while(j <= ee_page && j != TOP_PAGE)
	{
		//Page_To_Buffer (j, 2);
		
		for (i=0;i<264;i++)
		{
			temp = DF_SPI_RW(0x00);
			if(temp != 0xFF)
			{
				while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
				UDR1 = temp;
			}
			/*
			if(GetBit(temp,0) || GetBit(temp,1))
				LLED_ON;
			else
				LLED_OFF;
			*/
			if(temp == 0x00 && delay_flag == 1)
			{
				//not_bit(&PORTD,6);
        //NotBit(PORTD,6);
        PORTD_Bit6 = ~PORTD_Bit6;
          
				delay_ms(25);
				delay_flag = 0;
			}
			
			if(temp == 'N')
			{
				delay_flag = 1;
			}
		}
		j++;
	}
	
	/*
	Cont_Flash_Read_Enable (0, 0);
	while(j <= ee_page)
	{
		for (i=0;i<264;i++)
		{
			temp = DF_SPI_RW(0x00);
			if(temp != 0xFF)
			{
				while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
				UDR1 = temp;
			}
		}
		j++;
		delay_ms(100);
	}
	*/
	print_out_flash(label_usb_1);
	
	DF_CS_inactive;  
	DF_SPI_disable();
	LLED_OFF;
	return 0;
}

void send_items(void)
{
	unsigned char buffer_tx[] = "02040000";
	unsigned int item;
	unsigned char buffer[2];
	
	item = ee_page * 6 + g_dataflash_page_address / 42;
	CharToStr(item>>8,buffer);
	buffer_tx[4] = buffer[0];
	buffer_tx[5] = buffer[1];
	CharToStr(item & 0x00FF,buffer);
	buffer_tx[6] = buffer[0];
	buffer_tx[7] = buffer[1];
	
	print_out("$");
	print_out(buffer_tx);
}