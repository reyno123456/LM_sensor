
//                                                                                                                     PL   Ex
//Start Group PnL	Used to start PnL procedure	                                                                        0x70	0x2C						
//NEXT_ACTUATOR	Used to move to the next actuator	                                                                    0x70	0x2D						
//INCLUDE	                                                                                                            0x70	0x2E						
//EXCLUDE		                                                                                                          0x70	0x2F						
//END_GROUP_PnL	Used to stop PnL procedure	                                                                          0x70	0x34						
//ERASE_GROUP_PNL	Used to reset PnL GROUP	                                                                            0x70	0x35						
//ADD_PERIPHERAL	Used to execute a self configuration (Plug&Go) by Room Control. (It's not a complete reset ROOM).	  0x70	0x36						



#include <ioavr.h>
#include <inavr.h>
#include "usart.h"
#include "board.h"
#include "moudle_SCS.h"
#include "global_variable.h"
#include "IR.h"
#include "application.h"
#include "string.h"
#include "decode_scs_next.h"
#include "configuration.h"
#include "function_service.h"

//ISR(USART1_RX_vect)
/*
#pragma vector=USART1_RX_vect
__interrupt void usart1_rx_ser(void)
{
	unsigned char temp;
  temp = UDR1;

	if (temp == 0xAA && IR_reception.begin_actual == 0)
	{
		IR_reception.info = 0;
		IR_reception.begin_actual = 0;
		IR_reception.finished = 0;
		IR_reception.pipe[0] = temp;
		IR_reception.CRC_OK = 0;
	}
	else
	{
		IR_reception.pipe[++IR_reception.begin_actual] = temp;	

    if(IR_reception.begin_actual >= 14)
      IR_reception.begin_actual = 0;

		if(IR_reception.begin_actual == 5)//&&(g_reception_IR.pipe[5] == 0x12))
		{		
			switch(IR_reception.pipe[5]&0xC0)
			{
				case 0x00:
					IR_reception.info = 6;			//只剩一帧CRC没有接收到，该数据帧共有0~6共7bytes
					break;
				case 0x40:
					IR_reception.info = 7;			//该数据帧共有0~7共8bytes
					break;
				case 0x80:
					IR_reception.info = 9;			//该数据帧共有0~9共10bytes
					break;
				case 0xC0:
					IR_reception.info = 13;			//该数据帧共有0~13共14bytes
					break;
				default:
          IR_reception.info = 20;     //for solve the IR receive question
          break;			
			}
		}

		if(IR_reception.begin_actual == IR_reception.info)
		{
      IR_reception.begin_actual = 0;
			IR_reception.finished = 1;
		}
	}
}
*/

#pragma vector=USART1_RX_vect
__interrupt void usart1_rx_ser(void)
{
	unsigned char temp;
  temp = UDR1;
	
	if(temp == '$')
	{
		usb_command.start = temp;
		usb_command.next = 0;
	}
	else if(usb_command.start)
	{
		usb_command.pipe[usb_command.next] = temp;
		usb_command.next++;
	}
	
	if(usb_command.next >= 8)
	{
		usb_command.next = 0;
		usb_command.start = 0;
		usb_command.decoded = 0;
	}
}

//ISR(USART1_TX_vect)
#pragma vector=USART1_TX_vect
__interrupt void usart_tx_ser(void)
{
    if (tx1_counter)
    {
           --tx1_counter;
		
           UDR1 = tx1_buffer[tx1_rd_index];
		
           if (++tx1_rd_index == TX1_BUFFER_SIZE) tx1_rd_index=0;
    };
}

/*USART1发送单个字符*/
void put_c1(char c)
{
    while (tx1_counter == TX1_BUFFER_SIZE);   //发送数据队列中还有数据没有发送完，等待

    __disable_interrupt();
    if (tx1_counter || ((UCSR1A & DATA_UD1_EMPTY)==0))    //若发送数据队列有数据或者数据寄存器UDR非空时执行(因为队列先进先出的原因，所以，c要放进非空的发送数据队列里面)
		{
           tx1_buffer[tx1_wr_index]=c;
           if (++tx1_wr_index == TX1_BUFFER_SIZE) tx1_wr_index=0;
           ++tx1_counter;
       }
    else
           UDR1=c;
    __enable_interrupt();
		
}

//0xAA,0x86,0x50,0x55,0x15,0x07
void put_s1(unsigned char *ptr, unsigned char end_pipe)
{	
	unsigned char i;
	unsigned char crc;
	//IR_36kHz();				//发送IR数据前先使能36KHZ的载波输出	
	//crc = 0x51
	crc = 0;
	for (i=1; i<end_pipe; i++)		//对数据帧的<HEADER>, <FIRST ADDRESS>, <PAYLOAD>位进行CRC校验
	{
		crc = _calculate_crc(*(ptr+i),crc);
	}

	delay_ms(10);	
 	for(i=0;i<end_pipe;i++)
	{
		put_c1(*ptr++);
	}
	put_c1(crc);
	delay_ms(70);
	//buzzer_ms(10);
	flags.ir_buzzer = 1;
	//delay_ms(6);
	
	//close_IR_36kHz();	//发送数据结束后，把36KHZ载波输出关闭
}

void init_USART1(unsigned long int baud_rate)
{
	if(baud_rate == 9600)
	{
		// USART1 initialization
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: Off
		// USART1 Transmitter: On
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 9600
		UCSR1A=0x00;
		//UCSR1B=0x08; //without interrupt
		UCSR1B=0x98; //interrupt
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0x2F;
	}
	else if(baud_rate == 115200)
	{
		// USART1 initialization
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: On
		// USART1 Transmitter: On
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 115200
		UCSR1A=0x00;
		UCSR1B=0x98;
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0x03;
	}
	else if(baud_rate == 2400)
	{
		/*
		UCSR1A=(1<<RXC1)|(1<<TXC1);
		UCSR1B=(1<<RXCIE1)|(1<<TXCIE1)|(1<<RXEN1)|(1<<TXEN1);		//0xD8
		UCSR1C=(1<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10);				//0x06;
		UBRR1H=0x00;
		UBRR1L=191;		//2400=191, 4800=95
		*/
	
		// USART1 initialization
		// Communication Parameters: 8 Data, 1 Stop, No Parity
		// USART1 Receiver: On
		// USART1 Transmitter: Off
		// USART1 Mode: Asynchronous
		// USART1 Baud Rate: 2400
		UCSR1A=0x00;
		UCSR1B=0x90;
		UCSR1C=0x06;
		UBRR1H=0x00;
		UBRR1L=0xBF;
	}
}

unsigned char _calculate_crc(unsigned char data, unsigned char crc)
{
  unsigned char i;
	crc = crc ^ data;
	for (i = 0; i < 8; i++)
	{
		if (crc & 0x01)
			crc = (crc >> 1) ^ 0x8C;
		else
			crc >>= 1;
	}
	return crc;
}

void PWM_output_init(void)
{
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
	TCCR1B = (1<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10);	// CLOCK/1	
}

void IR_36kHz(void)
{
	PWM_output_init();	
	ICR1 = 102;		// 36K
	OCR1A = 31;		//30%
	OCR1B = 0;		//0%
}

void close_IR_36kHz(void)
{
	TCCR1B = (0<<CS12)|(0<<CS11)|(0<<CS10);	// CLOCK = 0	
	OCR1A = 0;
	TCCR1A = 0;
	//TCCR1B = 0;
}

void timer_IR_initial(unsigned long int ms)
{
	Time_delay.IR.stack_top = ms;
	Time_delay.IR.count = 0;
	Time_delay.IR.time_out = 0;
	Time_delay.IR.started = 1;
	Time_delay.IR.enabled = 1;
}

void decode_IR()
{
	unsigned int par_num;
	//unsigned int par_val;
	unsigned char i;
	unsigned char crc;
	//unsigned char *p_ee = &ee_KO_conf;
	volatile unsigned char buffer_ir[13];
	unsigned char buffer_scs[17];
	unsigned char buffer_char[3];
	//unsigned char *p_IR = &IR_reception.pipe[0];
	unsigned char old_ns_index = 0;
  unsigned char ns;
  volatile unsigned long int current_id = 0;
  unsigned char temp;
  unsigned char available_command = 0;
  unsigned char group_flag = 0;
	unsigned char ns_sended[16];
	unsigned char j;
	unsigned char avoid_twice = 0;
	unsigned char temp_ns;
	unsigned char current_scenario = OUT_RANGE;
	static unsigned char ns_400ms;
	//CRC checking
	if(IR_reception.finished == 1)
	{
		crc = 0;
		for (i=1; i<IR_reception.info; i++)		//对数据帧的<HEADER>, <FIRST ADDRESS>, <PAYLOAD>位进行CRC校验
		{
			crc = _calculate_crc(IR_reception.pipe[i],crc);
		}

		if(crc == IR_reception.pipe[IR_reception.info])
			IR_reception.CRC_OK = 1;
		else
			IR_reception.CRC_OK = 0;
	}

	//if((IR_reception.CRC_OK == 1) || (IR_reception.CRC_OK == 0))
	if((IR_reception.CRC_OK == 1) )
	{
		timer_IR_initial(2000);
		state.IR_Trans = 1;
		flags.ir_buzzer = 0;
		//IR_reception.finished = 0;
		//IR_reception.CRC_OK = 0;
		//buzzer_ms(100);
    ns = IR_reception.pipe[4] & 0x0F;
    current_id = IR_reception.pipe[2];
    current_id = current_id << 8;
    current_id = current_id + IR_reception.pipe[3];
		current_id = current_id << 4;
    temp = IR_reception.pipe[4];
    temp = temp >> 4;
    temp = temp & 0x0F;
    current_id = current_id + temp;

    if(current_id == 0xFFFFF)
    {
      if(ns == 0)
      {
        available_command = 0;
        group_flag = 1;
      }
      else if(ns < 16)
        available_command = 1;
      else
        available_command = 0;
    }
    else
    {
      for(i=15;i!=0xFF;i--)
		  {
			  if( (IR_reception.pipe[2] == ee_scenario[i].id[0]) && (IR_reception.pipe[3] == ee_scenario[i].id[1]) && (IR_reception.pipe[4] == ee_scenario[i].id[2]))
			  {
          ns = ee_scenario[i].ns_number;
				  available_command = 1;
					current_scenario = i;
				  break;
			  }
			}
    }

		for(i=0;i<14;i++)
		{
			g_ir_reception[i] = IR_reception.pipe[i];
		}

		switch(IR_reception.info)
		{
			case 6:
				//IR_reception.info = 6;			//只剩一帧CRC没有接收到，该数据帧共有0~6共7bytes
        switch(IR_reception.pipe[5])
        {
          case 0x01:    //ON
            //load_update(0);
            if(available_command)
            {
              send_aux_frame(ON,ns,current_scenario);
            }
            else if(group_flag)
            {
              if(product_information.conf_type == NONE_CONFED)
              {
              }
              else
              {
								//SCS_received.Manual_ON = 1;     // add by alan on 20090404   //0715
								frame_ON_send();
								/*
                if(KO_conf.AddressType == GROUP)	
									send_group_frame(ON);
								else if(KO_conf.AddressType == PP)
									frame_pp_on_off('0');
								*/
								SCS_received.GR_ON = 1;
              }
            }
          break;

          case 0x02:    //OFF
						//load_update(1);
            if(available_command)
            {
                send_aux_frame(OFF,ns,current_scenario);
            }
            else if(group_flag)
            {
              if(product_information.conf_type == NONE_CONFED)
              {
              }
              else
              {
								/*
								if(KO_conf.AddressType == GROUP)
									send_group_frame(OFF);
								else if(KO_conf.AddressType == PP)
									frame_pp_on_off('1');
								*/
								frame_OFF_send();
								SCS_received.GR_OFF = 1;
								SCS_received.P2P_actuator_flag = 0;
								SCS_received.P2P_dimmer_flag = 0;
              }
            }
          break;

          case 0x07:
            if(current_id != 0xFFFFF)
            {
              for(i=15;i!=0xFF;i--)
					    {
						    if( (IR_reception.pipe[2] == ee_scenario[i].id[0]) && (IR_reception.pipe[3] == ee_scenario[i].id[1]) && (IR_reception.pipe[4] == ee_scenario[i].id[2]))
						    {
							    strncpy(buffer_scs,"B1009300",9);
							    CharToStr(ee_scenario[i].ns_number,buffer_char);
							    buffer_scs[2] = buffer_char[0];
							    buffer_scs[3] = buffer_char[1];
							    send_frame_pp_broad(buffer_scs,0);
							    break;
						    }
					    }
            }
            else
            {
              if(ns < 16)
              {
                send_aux_frame(ACTION,ns,current_scenario);
              }
            }
          break;

          default:break;
        }
			break;
			
			case 7:
				//IR_reception.info = 7;			//该数据帧共有0~7共8bytes
				if(IR_reception.pipe[5] == 0x70)
				{
					switch(IR_reception.pipe[6])
					{
						case 0x00:  //announce ID
							//led_blinking(1000,1000);
							//state.main_state = PNL_IR_SCENARIO_STEP1;
							//timer_flex_initial(60000);
						break;

						case 0x0E:  //erase_ID address_erase
							if( (IR_reception.pipe[4] & 0x0F) == 0)
							{
								for(i=0;i<16;i++)
								{
									ns_sended[i] = 0;
								}
                strncpy(buffer_scs,"D200090811000066",17);
                for(i=0;i<16;i++)
                {
									avoid_twice = 0;
									//&& (ee_scenario[i].id[2] & 0xF0 == IR_reception.pipe[4] & 0xF0)
									if((ee_scenario[i].id[0] == IR_reception.pipe[2] )&& (ee_scenario[i].id[1] == IR_reception.pipe[3]))
									{
										if((ee_scenario[i].id[2] & 0xF0) == (IR_reception.pipe[4] & 0xF0))
										{
											CharToStr(ee_scenario[i].ns_number,buffer_char);
                    	buffer_scs[10] = buffer_char[0];
                    	buffer_scs[11] = buffer_char[1];
											temp_ns = i;
											
											if(ee_scenario[i].confed)
											{
												for(j=0;j<i;j++)
												{
													if(ns_sended[j] == ee_scenario[i].ns_number)
													{
														avoid_twice = 1;
														break;
													}
												}
											}
										
											if(avoid_twice == 0)
											{
                    		send_frame_pp_ext_broad(buffer_scs,TRANS_DELAY);
												ns_sended[temp_ns] = ee_scenario[temp_ns].ns_number;
											}
										
											ee_scenario[temp_ns].ns_number = 0x01;
											ee_scenario[temp_ns].id[0] = 0;
											ee_scenario[temp_ns].id[1] = 0;
											ee_scenario[temp_ns].id[2] = 0;
											ee_scenario[temp_ns].key_number = 0;
											ee_scenario[temp_ns].confed = 0;
											
											g_ns_index = temp_ns;
										}
									}
									/*
                  if(ee_scenario[i].confed)
                  {
                    CharToStr(ee_scenario[i].ns_number,buffer_char);
                    buffer_scs[10] = buffer_char[0];
                    buffer_scs[11] = buffer_char[1];
                    send_frame_pp_ext_broad(buffer_scs,TRANS_DELAY);
                  }
									*/
                }
                /*
								for(i=0;i<16;i++)
								{
									ee_scenario[i].ns_number = 0x01;
									ee_scenario[i].id[0] = 0;
									ee_scenario[i].id[1] = 0;
									ee_scenario[i].id[2] = 0;
									ee_scenario[i].key_number = 0;
									ee_scenario[i].confed = 0;
								}
								*/
							}
							else
							{
								for(i=0;i<16;i++)
								{
									if( (IR_reception.pipe[2] == ee_scenario[i].id[0]) && (IR_reception.pipe[3] == ee_scenario[i].id[1]) && (IR_reception.pipe[4] == ee_scenario[i].id[2]))
									{
										strncpy(buffer_scs,"D200090811000066",17);
										CharToStr(ee_scenario[i].ns_number,buffer_char);
										buffer_scs[10] = buffer_char[0];
										buffer_scs[11] = buffer_char[1];
										send_frame_pp_ext_broad(buffer_scs,0);

										ee_scenario[i].ns_number =0x01;
										ee_scenario[i].id[0] = 0;
										ee_scenario[i].id[1] = 0;
										ee_scenario[i].id[2] = 0;
										ee_scenario[i].key_number = 0;
										ee_scenario[i].confed = 0;
									}
								}
							}
							
							led_blinking(60,250);
							timer_flex_initial(5000);
							state.main_state = PNL_IR_SCENARIO_STEP8;

						break;

						case 0x07: //close learning
							//strlcpy(buffer_ID,&IR_reception.pipe[2],4);
              if(state.main_state > PNL_IR_SCENARIO_STEP3 && state.main_state < PNL_IR_SCENARIO_STEP7)
							{
								if(current_id == temp_variable.ID)
								{
									temp_variable.ID = 0;
									state.pnl_slave = NORMAL;
							  	state.main_state = PNL_IR_SCENARIO_STEP7;
								}
							}
						break;

						case 0x2C:	//START_GROUP_PNL
              if(state.main_state == STATE_NORMAL)
              {
                if(product_information.conf_type == NONE_CONFED)
                {
							    state.main_state = PNL_NONE_CONFED_STEP1;
                  key_result.short_pressed = 1;
                }
                else if(product_information.conf_type == ADVANCED)
                {
                  state.main_state = PNL_AD_CONFED_STEP1;
                  key_result.short_pressed = 1;
                }
              }
						break;
							
						case 0x2D: //NEXT_ACTUATOR
							send_frame_pp_ext_broad("D20001428C000B01",TRANS_DELAY);
						break;

						case 0x2E: //INCLUDE
							send_frame_pp_ext_broad("D20001428C000B02",TRANS_DELAY);
						break;

						case 0x2F: //EXCLUDE
							send_frame_pp_ext_broad("D20001428C000B03",TRANS_DELAY);
						break;

						case 0x30:    //SET_ON
							//SCS_received.Manual_ON = 1;    // add by alan on 20090404  //0715
              send_frame_pp_ext_broad("D20001428C000B04",TRANS_DELAY);
						break;
						
						case 0x31:    //SET_OFF
							//SCS_received.Manual_OFF = 1;    // add by alan on 20090404  //0715
              send_frame_pp_ext_broad("D20001428C000B05",TRANS_DELAY);
						break;

            case 0x32:    //SET_DIMMING_UP
              send_frame_pp_ext_broad("D20001428C000B06",TRANS_DELAY);
            break;

            case 0x33:    //SET_DIMMING_DOWN
              send_frame_pp_ext_broad("D20001428C000B07",TRANS_DELAY);
            break;

						case 0x34:  //END_GROUP_PNL
              if(state.main_state != STATE_NORMAL)
              {
                if(product_information.conf_type == NONE_CONFED)
                {
							    state.main_state = PNL_NONE_CONFED_STEP4;
                  //key_result.short_pressed = 1;
                }
                else if(product_information.conf_type == ADVANCED)
                {
                  state.main_state = PNL_AD_CONFED_STEP90;
                  key_result.short_pressed = 1;
                }
              }
						break;

						case 0x35: //ERASE_GROUP_PNL
							//send_frame_pp_ext_broad("D20001428CGG0944",TRANS_DELAY);
              if(available_command)
              {
								if(KO_conf.Reference != 0)
									send_group_pnl_frame(SET,KO_conf.Reference,REF_TRANS);
			
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

                send_frame_pp_ext_broad("D20001428C000B05",TRANS_DELAY);
                led_blinking_normal();
              }
              else if(group_flag)
              {
                if(product_information.conf_type == NONE_CONFED)
                {
                }
                else
                {
									send_group_frame(ERASE);
                  if(available_command)
              		{
										if(KO_conf.Reference != 0)
											send_group_pnl_frame(SET,KO_conf.Reference,REF_TRANS);
			
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
                  	led_blinking_normal();
                	}
              	}
							}
						break;

						case 0x36: //ADD_PERIPHERAL
							send_frame_pp_ext_broad("D20001428C000802",TRANS_DELAY);
						break;

						case 0x37:			// return to factory default
              if(product_information.conf_type == ADVANCED)
              {
                if(KO_conf.GR != 0)
                {
                  CharToStr(KO_conf.GR,buffer_char);
                  strncpy(buffer_scs,"D20001428C000947",17);
                  buffer_scs[10] = buffer_char[0];
                  buffer_scs[11] = buffer_char[1];
                  send_frame_pp_ext_broad(buffer_scs,TRANS_DELAY);
                }
              }
              factory_default();
              system_reset();
						break;
	
						case 0x38:			//reset room controler
							send_frame_pp_ext_broad("D20001428C0008F0",TRANS_DELAY);
						break;
						default:break;
					}	
				}
			break;
			
			case 9:
				//IR_reception.info = 9;			//该数据帧共有0~9共10bytes
        if(IR_reception.pipe[5] == 0x83)  //dimmer step
        {
          if(available_command)
          {
							send_aux_frame(DIM_STEP,ns,current_scenario);
							timer_dimmer_initial(400);
							flags.dimmer_started = 1;
							ns_400ms = ns;
          }
          else if(group_flag)
          {
            if(product_information.conf_type != NONE_CONFED)
						{
              send_group_frame(DIM_STEP);
							timer_dimmer_initial(400);
							flags.dimmer_started = 1;
							ns_400ms = ns;
						}
          }
        }

        if(IR_reception.pipe[5] == 0x84)  //go to level time
        {
          if(available_command)
          {
              send_aux_frame(GO_TO_LEVEL_TIME,ns,current_scenario);
          }
        }

				if(IR_reception.pipe[5] == 0xB1)
				{
					if(IR_reception.pipe[6] == 0x04)			//Parameter read
					{
						buffer_ir[0] = 0xAA;
						buffer_ir[1] = 0x80;
						buffer_ir[2] = 0xFF;
						buffer_ir[3] = 0xFF;
						buffer_ir[4] = 0xF0;
						buffer_ir[5] = 0xF1;
						buffer_ir[6] = 0x05;
						buffer_ir[7] = IR_reception.pipe[7];		//20090515
						buffer_ir[8] = IR_reception.pipe[8];		//20090515
						buffer_ir[10] = 0x00;
						buffer_ir[11] = 0x00;
						buffer_ir[12] = 0x00;
						par_num = (unsigned int)(IR_reception.pipe[8] << 8) + IR_reception.pipe[7];
						if(par_num <= PARAMETER_NUMBER)
						{
							if(par_num == 27)
							{
								buffer_ir[7] = IR_reception.pipe[7];
								buffer_ir[8] = IR_reception.pipe[8];
								buffer_ir[9] = KO_conf.DayLightLevLux[0];
								buffer_ir[10] = KO_conf.DayLightLevLux[1];
							}
							else
							{
								buffer_ir[7] = IR_reception.pipe[7];
								buffer_ir[8] = IR_reception.pipe[8];
								//if(product_information.conf_type == NONE_CONFED)
									//buffer_ir[9] = read_KO_none_confed(IR_reception.pipe[7]);
								//else
								buffer_ir[9] = read_KO(IR_reception.pipe[7]);
								if(product_information.conf_type == NONE_CONFED)
								{
									break;
									//buffer_ir[10] = 0xFF;
								}
							}
						}
						else if(par_num == 256)
						{
							buffer_ir[7] = IR_reception.pipe[7];
							buffer_ir[8] = IR_reception.pipe[8];
							

							#ifdef HARDWARE_PIR
								buffer_ir[9] = 0x12; 			//need improve
							#endif

							#ifdef HARDWARE_US
								buffer_ir[9] = 0x22; 			//need improve
							#endif
								
							#ifdef HARDWARE_PIR_US
								buffer_ir[9] = 0x32; 			//need improve
							#endif
						}
						else if(par_num == 257)		// low byte of ID
						{
							//buffer_ir[9] = 0x76;
							//buffer_ir[10] = 0x98;
							buffer_ir[7] = IR_reception.pipe[7];			//add 20090213
							buffer_ir[8] = IR_reception.pipe[8];			//add 20090213

							buffer_char[0] = ee_ID[4];
							buffer_char[1] = ee_ID[5];
							buffer_ir[10] = StrToChar(buffer_char);
							buffer_char[0] = ee_ID[6];
							buffer_char[1] = ee_ID[7];
							buffer_ir[9] = StrToChar(buffer_char);
						}
						else if(par_num == 258)		// high byte of ID
						{
							//buffer_ir[9] = 0x05;
							//buffer_ir[10] = 0x00;
              buffer_char[0] = ee_ID[2];
							buffer_char[1] = ee_ID[3];
							buffer_ir[9] = StrToChar(buffer_char);
							buffer_char[0] = ee_ID[0];
							buffer_char[1] = ee_ID[1];
							buffer_ir[10] = StrToChar(buffer_char);
						}
            else if(par_num == 259)
            {
              //version = ee_parameter.software_version[0];
              buffer_ir[9] = ee_parameter.software_version[0] - 0x30;
              buffer_ir[10] = ee_parameter.software_version[1] - 0x30;
            }
            else if(par_num == 260)
            {
							//setting_diagnostic_ir(&buffer_ir[9]);
							buffer_ir[9] = KO_conf.status[0];
							buffer_ir[10] = KO_conf.status[1];
							
							ClrBit(KO_conf.status[0],Status_Derogation);
							ClrBit(KO_conf.status[0],Status_Regulation);
							ClrBit(KO_conf.status[0],Status_Detection);	
            }
						put_s1(buffer_ir,13);
					}
				}

				if(IR_reception.pipe[5] == 0xB0)
				{
					if(IR_reception.pipe[6] == 0x06)    //open learning
					{
						//if(state.main_state == STATE_NORMAL)
						//{
							temp_variable.ID = current_id;
							
							if(is_scenario_full() == 0)
							{
								send_frame_pp_broad("B0009900",TRANS_DELAY);
              	temp_variable.scenario_id = current_id;
              	temp_variable.scenario_ns = ns;
								strncpy(buffer_scs,"D20001428C000A05",17);

								for(i=0;i<16;i++)
								{
									if( (g_ir_reception[2] == ee_scenario[i].id[0]) && (g_ir_reception[3] == ee_scenario[i].id[1]) && (g_ir_reception[4] == ee_scenario[i].id[2]) )
									{
										old_ns_index = i;
										break;
									}
								}
							
								if(i>=16)
								{
									buffer_char[0] = '0';
									buffer_char[1] = '1';
								}
								else
								{
									CharToStr(ee_scenario[old_ns_index].ns_number,buffer_char);
								}
								buffer_scs[10] = buffer_char[0];
								buffer_scs[11] = buffer_char[1];
								send_frame_pp_ext_broad(buffer_scs,TRANS_DELAY);

								timer_flex_initial(3000);
								state.main_state = PNL_IR_SCENARIO_STEP2;
							}
							else
							{
								led_blinking(120,0);
								timer_flex_initial(5000);
								state.main_state = PNL_IR_SCENARIO_STEP2;
							}
						//}
					}
				}
			break;

			case 13:
				//IR_reception.info = 13;			//该数据帧共有0~13共14bytes
				if(IR_reception.pipe[5] == 0xF1) 		
				{
					if(IR_reception.pipe[6] == 0x03) 			//Parameter set
					{
            par_num = (unsigned int)(IR_reception.pipe[8] << 8) + IR_reception.pipe[7];
						if(IR_reception.pipe[8] == 0)				//Low 256 par number
						{
							if(par_num <= PARAMETER_NUMBER && par_num != 0x05)
							{
                //if(par_num == 26 && IR_reception.pipe[9] == 0)
                //{
                //  write_KO(IR_reception.pipe[7],0xFF);
                //}
								if(par_num == 27)
								{
									//reyno 0602
									unsigned int temp0;				// add by alan
									volatile float f_temp;
									temp0 = IR_reception.pipe[9];																// temp0 = lux/5
									temp0 += (IR_reception.pipe[10]<<8);
									if(Sensor_mode.power_on_flag)
									{
										KO_conf.DF = temp0*10*5/ DLL.calc_level;			//0526
										f_temp = (float)temp0*10*5/ (float)DLL.calc_level;
										if((f_temp - KO_conf.DF >= 0.5) && (KO_conf.DF != 255))
											KO_conf.DF++;
										write_KO(22,KO_conf.DF); //reyno 0602
										write_ee_KO(22,KO_conf.DF);										// 0529 write_ee_KO(unsigned char index,unsigned char data);
									}
									else
									{
										KO_conf.NF = temp0*10*5/ DLL.calc_level;			//0526
										f_temp = (float)temp0*10*5/ (float)DLL.calc_level;
										if((f_temp - KO_conf.NF >= 0.5) && (KO_conf.NF != 255))
											KO_conf.NF++;
										write_KO(24,KO_conf.NF); //reyno 0602
										write_ee_KO(24,KO_conf.NF);										// 0529 write_ee_KO(unsigned char index,unsigned char data);
									}
								}
								else
								{
                	//write_result = write_KO(IR_reception.pipe[7],IR_reception.pipe[9]);
                	//if(write_result != PAR_OUT_OF_RANGE && write_result != PAR_NOT_IMPLEMENTED)
                	//{
                  	//ee_KO_conf = KO_conf;
                	//}
									write_KO(IR_reception.pipe[7],IR_reception.pipe[9]);
									write_ee_KO(IR_reception.pipe[7],IR_reception.pipe[9]);
								}
								if((par_num == 10)||(par_num == 11)||(par_num == 12))		// add by alan
								{
										unsigned long int hour_count = KO_conf.Hours;
								  	Delay_Time_set = KO_conf.Seconds + KO_conf.Minutes*60 + hour_count*3600;	//calculate the time set by user
								}
								if(par_num == 23)	// alan when the type loop changed, the D.F should clear and re_set the D.F again
								{
										//KO_conf.DF = 0;
										//DLL.DF = 0;		
								}
								if(par_num == 25)	// alan when the type loop changed, the D.F should clear and re_set the D.F again
								{
									set_point = KO_conf.DaylightSetp*5;
								}
							}
							else
								ERROR;	
						}
					}
				}
				break;
			default: break;			
		}

		//IR_reception.finished = 0;
		//IR_reception.CRC_OK = 0;
		//put_s1(buffer_test,13);
		
		if(flags.ir_buzzer == 0)
			buzzer_ms(50);       //2009-3-20
		//send_frame_pp_ext("D200014281040000",1000);
		//send_frame_pp_ext("B300120000000000",1000); //test SCS interface frame
	}
	
	if(Time_delay.dimmer.time_out == 1 && flags.dimmer_started == 1)
	{
		Time_delay.dimmer.time_out = 0;
		flags.dimmer_started = 0;
		send_aux_frame(DIMMER_STOP,ns_400ms,current_scenario);
	}
}

void ir_buffer_clear(void)
{
	unsigned char i;
	if( IR_reception.CRC_OK == 1 )
	{
		for(i=0;i<13;i++)
		{
			IR_reception.pipe[i] = 0;
		}
		IR_reception.finished = 0;
		IR_reception.CRC_OK = 0;
	}
}

volatile unsigned char temp_ns;
unsigned char ir_pnl(void)
{
	unsigned char buffer_tx[17];
	unsigned char buffer[3];
	static unsigned char id_compare_flag;
	unsigned char i;
	
	if(g_asc_reception_buffer[7] == 0x09)
	{
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP2)
	{
		if(is_scenario_full() == 0)
		{
			if( Time_delay.timer_flex.time_out == 1 )
			{
    	  //not assigned NS by RC
				
					id_compare_flag = 0;
					for(i=0;i<16;i++)
					{
						if( (g_ir_reception[2] == ee_scenario[i].id[0]) && (g_ir_reception[3] == ee_scenario[i].id[1]) && (g_ir_reception[4] == ee_scenario[i].id[2]))
						{
							ee_scenario[i].id[0] = g_ir_reception[2];
							ee_scenario[i].id[1] = g_ir_reception[3];
							ee_scenario[i].id[2] = g_ir_reception[4];
							//ee_scenario[i].ns_number = g_asc_reception_buffer[5];
							ee_scenario[i].key_number = g_ir_reception[4] & 0x0F;
							ee_scenario[i].confed = 0x01;
							id_compare_flag = 1;
							g_ns_index = i;
							break;
						}
					}
    	
					if(id_compare_flag == 0)
					{
						for(i=0;i<16;i++)
						{
							if(ee_scenario[i].confed == 0)
							{
								g_ns_index = i;
								break;
							}
						}
					
						ee_scenario[g_ns_index].id[0] = g_ir_reception[2];
						ee_scenario[g_ns_index].id[1] = g_ir_reception[3];
						ee_scenario[g_ns_index].id[2] = g_ir_reception[4];
						//ee_scenario[g_ns_index].ns_number = g_asc_reception_buffer[5];
						ee_scenario[g_ns_index].key_number = g_ir_reception[4] & 0x0F;
						ee_scenario[g_ns_index].confed = 0x01;
						g_ns_index++;
						flags.scenario_last_assigned = 1;
					}
    	
    	  	led_blinking(250,250);
					state.main_state = PNL_IR_SCENARIO_STEP3;
			}
    	
			if( (g_asc_reception_buffer[6] == 0x0A) && (g_asc_reception_buffer[7] == 0x08))
			{
				led_blinking(120,120);
    	  timer_flex_initial(5000);
				state.main_state = PNL_IR_SCENARIO_STEP21;
			}
    	
			if( (g_asc_reception_buffer[6] == 0x0A) && (g_asc_reception_buffer[7] == 0x06))
			{
				id_compare_flag = 0;
				for(i=0;i<16;i++)
				{
					if( (g_ir_reception[2] == ee_scenario[i].id[0]) && (g_ir_reception[3] == ee_scenario[i].id[1]) && (g_ir_reception[4] == ee_scenario[i].id[2]))
					{
						ee_scenario[i].id[0] = g_ir_reception[2];
						ee_scenario[i].id[1] = g_ir_reception[3];
						ee_scenario[i].id[2] = g_ir_reception[4];
						ee_scenario[i].ns_number = g_asc_reception_buffer[5];
    	      ee_scenario[i].key_number = g_ir_reception[4] & 0x0F;
						ee_scenario[i].confed = 0x01;
						id_compare_flag = 1;
						g_ns_index = i;
						break;
					}
				}
    	
				if(id_compare_flag == 0)
				{
					for(i=0;i<16;i++)
					{
						if(ee_scenario[i].confed == 0)
						{
							g_ns_index = i;
							break;
						}
					}
					
					ee_scenario[g_ns_index].id[0] = g_ir_reception[2];
					ee_scenario[g_ns_index].id[1] = g_ir_reception[3];
					ee_scenario[g_ns_index].id[2] = g_ir_reception[4];
					ee_scenario[g_ns_index].ns_number = g_asc_reception_buffer[5];
    	    ee_scenario[g_ns_index].key_number = g_ir_reception[4] & 0x0F;
					ee_scenario[g_ns_index].confed = 0x01;
					g_ns_index++;
					flags.scenario_last_assigned = 1;
				}
    	
    	  led_blinking(250,250);
				state.main_state = PNL_IR_SCENARIO_STEP3;
			}
		}
		else
		{
			if( Time_delay.timer_flex.time_out == 1 )
			{
				led_blinking_disable(0);
				timer_flex_initial(600000);
				state.main_state = PNL_IR_SCENARIO_STEP4;
			}
		}
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP21)
	{
		if( Time_delay.timer_flex.time_out == 1 )
		{
			led_blinking_disable(0);
			state.main_state = PNL_IR_SCENARIO_STEP7;
		}
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP3)
	{
		strncpy(buffer_tx,"B1009300",9);
		
		if(id_compare_flag == 0)
		{
			g_ns_index--;
			if(g_ns_index == 0xFF)
				g_ns_index = 15;
		}
		
    temp_ns = ee_scenario[g_ns_index].ns_number;
		CharToStr(ee_scenario[g_ns_index].ns_number,buffer);

		if(id_compare_flag == 0)
		{
			g_ns_index++;
			//if(g_ns_index >= 16)
				//g_ns_index = 0;
		}

		buffer_tx[2] = buffer[0];
		buffer_tx[3] = buffer[1];
		send_frame_pp_broad(buffer_tx,TRANS_DELAY);

		buffer_tx[5] = '0';
		send_frame_pp_broad(buffer_tx,TRANS_DELAY);

		timer_flex_initial(600000);

		state.main_state = PNL_IR_SCENARIO_STEP4;
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP4)
	{
		if( Time_delay.timer_flex.time_out == 1 )
		{
			state.main_state = PNL_IR_SCENARIO_STEP7;
		}
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP7)
	{
		if(is_scenario_full()==0 || flags.scenario_last_assigned)
		{
			flags.scenario_last_assigned = 0;
			strncpy(buffer_tx,"B1009100",9);
		
			if(id_compare_flag == 0)
			{
				g_ns_index--;
				if(g_ns_index == 0xFF)
					g_ns_index = 15;
			}

			CharToStr(ee_scenario[g_ns_index].ns_number,buffer);
		
			if(id_compare_flag == 0)
			{
				g_ns_index++;
				//if(g_ns_index >= 16)
					//g_ns_index = 0;
			}

			buffer_tx[2] = buffer[0];
			buffer_tx[3] = buffer[1];
			send_frame_pp_broad(buffer_tx,TRANS_DELAY);
			send_frame_pp_broad("B000990F",TRANS_DELAY);
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
		}
		else
		{
			//send_frame_pp_broad("B000990F",TRANS_DELAY);
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
		}
	}

	if(state.main_state == PNL_IR_SCENARIO_STEP8)
	{
		if( Time_delay.timer_flex.time_out == 1 )
		{
			led_blinking_disable(0);
			state.main_state = STATE_NORMAL;
		}
	}
	
	return 0;
}

void setting_diagnostic_ir(unsigned char *data)
{
	if( flags.dimmer_mode == 0)
	{
		if(flags.load_status == 0)
			*data = 0x00;
		else
			*data = 0x64;
	}
	else
	{
		*data = parameters.dimmer_value;
	}

	if(flags.detection)
		SetBit(*(data+1),3);
	else
		ClrBit(*(data+1),3);

	if(flags.time_delay_during)
		SetBit(*(data+1),2);
	else
		ClrBit(*(data+1),2);

	if(flags.walk_through_en)
		SetBit(*(data+1),1);
	else
		ClrBit(*(data+1),1);

	if(flags.re_triger_en)
		SetBit(*(data+1),0);
	else
		ClrBit(*(data+1),0);

	if(flags.exemption_en)
		SetBit(*(data+1),4);
	else
		ClrBit(*(data+1),4);

	if(flags.regulation_en)
		SetBit(*(data+1),5);
	else
		ClrBit(*(data+1),5);
}

unsigned char get_current_scenario_number(void)
{
  unsigned char i = 16;

	for(i=0;i<16;i++)
	{
		if( (g_ir_reception[2] == ee_scenario[i].id[0]) && (g_ir_reception[3] == ee_scenario[i].id[1]) && (g_ir_reception[4] == ee_scenario[i].id[2]))
		{
			return i;
		}
	}

  if(i == 16)
    i = 0;

  return i;
}

unsigned char is_scenario_full(void)
{
	for(unsigned char i=0;i<16;i++)
	{
		if(ee_scenario[i].confed == 0)
		{
			return 0;
		}
	}
	
	return 1;
}