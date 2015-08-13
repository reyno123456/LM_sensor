#include <ioavr.h>
#include "board.h"
#include <inavr.h>
#include "global_variable.h"
#include "moudle_SCS.h"
#include "application.h"

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_ser(void)       			// 100us alan
{
	TCNT0 = 0x8D;			//1ms

	if(Time_delay.timer_20s.enabled == 1)
	{
		if(++Time_delay.timer_20s.count >= SEC_20)
		{
			Time_delay.timer_20s.time_out = 1;
			Time_delay.timer_20s.enabled = 0;
		}
	}

	if(Time_delay.modality0.enabled == 1)
	{
		if(++Time_delay.modality0.count >= modality0_delay_ms)
		{
			Time_delay.modality0.time_out = 1;
			Time_delay.modality0.enabled = 0;
		}
	}

	if(Time_delay.motion.enabled == 1)
	{
		if(++Time_delay.motion.count >= 400)
		{
			//US_detection_en = 0;
			//PIR_detection_en = 0;     // add by alan 20090413
			// 以上针对PIR&US情况，在1s内US和PIR有探测才认为是有效，超过1S，不认为是同时探测到信号
			 //DLED_OFF;
			motion_total = 0;
      //motion_resutl = 0;
			Time_delay.motion.time_out = 1;
			Time_delay.motion.count = 0;
			//Time_delay.timer_1s.enabled = 0;
		}
	}

	if(Time_delay.LPB.enabled == 1)
	{
		Time_delay.LPB.count++;
	}
  /*
	if(Time_delay.led_double_on.enabled)
	{
		if((++Time_delay.led_double_on.count >= Time_delay.led_double_on.stack_top + Time_delay.led_double_off.stack_top) && (flags.led_on_double == 0))
		{
		  LLED_ON;
			DLED_ON;
			Time_delay.led_double_on.count = 0;
			flags.led_on_double = 1;
		}
		else if(++Time_delay.led_double_on.count >= Time_delay.led_double_on.stack_top)
		{
			LLED_OFF;
			DLED_OFF;
			flags.led_on_double = 0;
		}
	}
	*/
	
	if(Time_delay.led_on.enabled == 1)
	{
		LLED_ON;
		Time_delay.led_on.count++;
		if(Time_delay.led_on.count >= Time_delay.led_on.stack_top)
		{
			Time_delay.led_on.time_out = 1;
			Time_delay.led_on.enabled = 0;
			Time_delay.led_off.enabled = 1;
			Time_delay.led_off.count = 0;
		}
	}
	
	if(Time_delay.led_off.enabled == 1)
	{
		LLED_OFF;
		Time_delay.led_off.count++;
		if(Time_delay.led_off.count >= Time_delay.led_off.stack_top)
		{
			Time_delay.led_off.time_out = 1;
			Time_delay.led_off.enabled = 0;
			Time_delay.led_on.enabled = 1;
			Time_delay.led_on.count = 0;
		}
	}

	if(Time_delay.blinking_count.enabled == 1)
	{
		Time_delay.blinking_count.count++;
		if(Time_delay.blinking_count.count >= Time_delay.blinking_count.stack_top)
		{
			Time_delay.blinking_count.time_out = 1;
			Time_delay.blinking_count.enabled = 0;
			led_blinking_disable(0);
		}
	}
	
	if(Time_delay.Dled.enabled == 1)
	{
		Time_delay.Dled.count++;
		if(Time_delay.Dled.count >= Time_delay.Dled.stack_top)
		{
			Time_delay.Dled.time_out = 1;
			Time_delay.Dled.enabled = 0;
			LLED_OFF;
		}
	}
	
	if(Time_delay.IR.enabled == 1)
	{
		if(++Time_delay.IR.count >= Time_delay.IR.stack_top)
		{
			Time_delay.IR.time_out = 1;
			Time_delay.IR.enabled = 0;
		}
	}
	
	if(Time_delay.timer_flex.enabled == 1)
	{
		if(++Time_delay.timer_flex.count >= Time_delay.timer_flex.stack_top)
		{
			Time_delay.timer_flex.time_out = 1;
			Time_delay.timer_flex.enabled = 0;
		}
	}

	if(Time_delay.timer_flex2.enabled == 1)
	{
		if(++Time_delay.timer_flex2.count >= Time_delay.timer_flex2.stack_top)
		{
			Time_delay.timer_flex2.time_out = 1;
			Time_delay.timer_flex2.enabled = 0;
		}
	}
	
	if(Time_delay.dimmer.enabled == 1)
	{
		if(++Time_delay.dimmer.count >= Time_delay.dimmer.stack_top)
		{
			Time_delay.dimmer.time_out = 1;
			Time_delay.dimmer.enabled = 0;
		}
	}
	
	if(Time_delay.relay.enabled == 1)
	{
		if(++Time_delay.relay.count >= Time_delay.relay.stack_top)
		{
			Time_delay.relay.time_out = 1;
			Time_delay.relay.enabled = 0;
		}
	}
	
	if(Time_delay.pnl_stage2.enabled == 1)
	{
		if(++Time_delay.pnl_stage2.count >= Time_delay.pnl_stage2.stack_top)
		{
			Time_delay.pnl_stage2.time_out = 1;
			Time_delay.pnl_stage2.enabled = 0;
			if(state.main_state >= PNL_AD_CONFED_STEP2 && state.main_state <= PNL_AD_CONFED_STEP90)
			{
				PnL_ad_end();
			}
			else if(state.main_state > PNL_NONE_CONFED_STEP2 && state.main_state <= PNL_NONE_CONFED_STEP6)
			{
				PnL_NONE_end();
			}
		}
	}
		
  if(Time_delay.buzzer.enabled == 1)
	{
		//not_bit(&PORTD,7);
		if(++Time_delay.buzzer.count >= Time_delay.buzzer.stack_top)
		{
      //TCCR1B = (0<<CS12)|(0<<CS11)|(0<<CS10);	// CLOCK = 0	
		  //OCR1B = 0;
			Time_delay.buzzer.time_out = 1;
			Time_delay.buzzer.enabled = 0;
			//SetBit(PORTD,7);
		}
	}

	//Reyno 20091125
	/*
  if(Time_delay.led_blink.enabled == 1)
	{
		if(++Time_delay.led_blink.count >= Time_delay.led_blink.stack_top)
		{
			Time_delay.led_blink.count = 0;
			if((state.main_state == STATE_NORMAL || state.main_state ==STATE_PRE_PROGRAMMING) && state.pnl_slave == NORMAL)
			{
      	if(product_information.conf_type == NONE_CONFED)
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

          if(flags.confed == 0)
            led_blinking(120,120);
					else
						led_blinking_disable(0);
      	}
				else
				{
					led_blinking_disable(0);
				}
			}
		}
	}
	*/ 

	//reyno 0622
	if(Time_delay.regulation.enabled == 1)
	{
		if(++Time_delay.regulation.count >= Time_delay.regulation.stack_top)
		{
			Time_delay.regulation.time_out = 1;
			Time_delay.regulation.enabled = 0;
		}
	}
	
	if(Time_delay.sample_interval.enabled == 1)
	{
		if(++Time_delay.sample_interval.count >= Time_delay.sample_interval.stack_top)
		{
			Time_delay.sample_interval.time_out = 1;
			Time_delay.sample_interval.enabled = 0;
		}
	}
	
	if(Time_delay.timer_5m.enabled == 1)
	{
		if(++Time_delay.timer_5m.count >= Time_delay.timer_5m.stack_top)
		{
			Time_delay.timer_5m.time_out = 1;
			Time_delay.timer_5m.enabled = 0;
		}
	}
		// *******************add by alan begin*************************************************************
/******************	count the timer level Lower or Higher than the setpoint	***************/
	
	if(Time_delay.Dim_inc_enable == 1)			Time_delay.Dim_inc_count++;
	
	if(Time_delay.Dim_dec_enable == 1)			Time_delay.Dim_dec_count++;
	
	if(Time_delay.detect_waitting > 0)							// disable the motion detection 2s after send "OFF" 	0527
	{
			Time_delay.detect_waitting--;
			motion_total = 0;
      US_detection_en = 0;
      PIR_detection_en = 0;
      SCS_received.motion_detect = 0;
	}
	
/*********************		delay 5s for end detection		************************/
   if(DLL.Dim_T06s > 0)            		DLL.Dim_T06s--;         		//  send frame DIM--
   if(DLL.Dim_T200ms > 0)         		DLL.Dim_T200ms--;       		//  send frame DIM++
/**********************	delay 200ms for frame presence and ON	*************************/	
	if(Time_delay.frame_200ms.enabled == 1)							// 用于计算两个帧之间的间隔是否小于200ms
	{	
		if(++Time_delay.frame_200ms.count >= 300)
		{
			Time_delay.frame_200ms.time_out = 1;
			Time_delay.frame_200ms.enabled = 0;
			Time_delay.frame_200ms.started = 0;
			SCS_received.presence_2_ON = 0;									// 时间间隔超过200ms认为收到单个的ON帧	
		}	
	}	
/*********************	delay for frame send taking line		************************/
	if(Time_delay.timer_takeline.enabled == 1)
	{
		if(++Time_delay.timer_takeline.count >= Time_delay.random_time)
		{
			Time_delay.timer_takeline.time_out = 1;
			Time_delay.timer_takeline.enabled = 0;
		//	Time_delay.timer_takeline.started = 0;
		}
	}

	if(Time_delay.GS_200ms.enabled == 1)
	{
		if(++Time_delay.GS_200ms.count >= Time_delay.GS_200ms.stack_top)
		{
			Time_delay.GS_200ms.time_out = 1;
			Time_delay.GS_200ms.enabled = 0;
		}
	}
	
	if((Sensor_mode.presence_send ==1)&&(Sensor_mode.presence_20sinterval > 0))
	{
		Sensor_mode.presen_timeout = 0;
		if(--Sensor_mode.presence_20sinterval == 0)
		{
			Sensor_mode.presence_send = 0;
			Sensor_mode.presen_timeout = 1;
		}
	}
	
/**********************	delay for the load_timeout set by user Seconds	******************/	
	if(++Time_delay.second_OK >= 1000 )	// 1 second
	{
		Time_delay.second_OK = 0;
		if(Time_delay.GS_wait_22s > 0)		Time_delay.GS_wait_22s--;		//  0716

		if(Time_delay.pir_warmup_ok == 0)
		{
	  		if(++Time_delay.pir_wait_40s >= 5)		// 10s should change to 40s
				{
					Time_delay.pir_warmup_ok = 1;
				}
		}
		
		if(Time_delay.timer_delay_set.enabled == 1)
		{
			if(--Time_delay.timer_delay_set.count == 0)
			{
				Time_delay.timer_delay_set.time_out = 1;
				Time_delay.timer_delay_set.enabled = 0;
			}
		}
			
		if(Time_delay.Re_Trigger_senconds > 0)      Time_delay.Re_Trigger_senconds--;
	
		if(Time_delay.Walk_Through_Timeout > 0)     Time_delay.Walk_Through_Timeout--;
	
		if(Time_delay.DLL_low_20s_enable ==1)				Time_delay.DLL_low_20s_count++;
	
		if(Time_delay.DLL_high_10min_enable ==1)		Time_delay.DLL_high_10min_count++;	
	
		if(M2_timer_count > 0)          		M2_timer_count--;       				//  for modality 2

    if(DLL.lightness_load > 0)      		DLL.lightness_load--;					//  to calibrate the load provision
	
		if(Time_delay.second.enabled == 1)
		{
			if(++Time_delay.second.count >= Time_delay.second.stack_top)
			{
				Time_delay.second.time_out = 1;
				Time_delay.second.enabled = 0;
			}
		}
	}
// **************************add by alan end**********************************************	
}

#pragma vector=TIMER2_OVF_vect
__interrupt void timer2_ovf_ser(void)
{
	//Time_delay.timer0_compa_flag = 1;
	
	g_timer2_flag =~ g_timer2_flag;
	if(g_timer2_flag)
		SetBit(PORTB,3);
	else
		ClrBit(PORTB,3);
	
	//not_bit(&PORTB,0);
	TCNT2 = 0xBF;
}

void IO_Initial()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;

	//ClrBit(PORTB,0);
	//SetBit(PORTB,0);

	ClrBit(DDRB,4);			//push button
	SetBit(PORTB,4);

	//ClrBit(DDRB,0);
	//SetBit(PORTB,0);

	//SCS port
	//RX set high
	ClrBit(DDRD,0);
	SetBit(PORTD,0);
	ClrBit(DDRD,1);
	SetBit(PORTD,1);
	
	ClrBit(DDRB,6); //Get Value from Touch
	ClrBit(DDRD,5); //interrupt of Touch
	ClrBit(DDRD,4); //Busy
	SetBit(PORTB,6);
	SetBit(PORTD,5);
	SetBit(PORTD,4);
	
	SetBit(PORTC,1);
	
	ClrBit(DDRD,2);
	SetBit(PORTD,2);
}

void delay_ms(unsigned int ms)
{
  unsigned int i;
  for(i=0;i<ms;i++)
	  __delay_cycles(7372);
}

void delay_us(unsigned int us)
{
  unsigned int i;
  for(i=0;i<us;i++)
    __delay_cycles(73);
}

void delay_ms_1(void)
{
  unsigned char i;
  for(i=0;i<10;i++)
    __delay_cycles(7372);
}

void buzzer(unsigned int data)
{
/*
	unsigned int i;
	for(i=0;i<data;i++)
	{
		SET_BUZZER;
		delay_ms(1);
		CLR_BUZZER;
		delay_ms(1);
	}
*/
}

void not_bit(unsigned char *data, unsigned bit)
{
	if(GetBit(*data,bit))
		ClrBit(*data,bit);
	else
		SetBit(*data,bit);
}

unsigned char StrToChar(unsigned char *data)
{
	unsigned char temp;
	if((*data >= 'A') && (*data <= 'F'))
	{
		temp = (*data - 'A' + 10) * 16;
	}
	else if((*data >= '0') && (*data <= '9'))
	{
		temp = (*data - '0') * 16;
	}

	if((*(data+1) >= 'A') && (*(data+1) <= 'F'))
	{
		temp = temp + *(data+1) - 'A' + 10;
	}
	else if((*(data+1) >= '0') && (*(data+1) <= '9'))
	{
		temp = temp + *(data+1) - '0';
	}

	return temp;
}

unsigned char *CharToStr(unsigned char data,unsigned char *buffer)
{

	unsigned char buffer_temp[2];
	//itoa(data,buffer_temp,16);
  buffer_temp[0] = (data & 0xF0) >> 4;
  if(buffer_temp[0] <= 9)
  {
    buffer_temp[0] += 0x30;
  }
  else
  {
    buffer_temp[0] += 0x41 - 10;
  }

  buffer_temp[1] = data & 0x0F;
  if(buffer_temp[1] <= 9)
  {
    buffer_temp[1] += 0x30;
  }
  else
  {
    buffer_temp[1] += 0x41 - 10;
  }

  *buffer = buffer_temp[0];
	buffer++;
	*buffer = buffer_temp[1];

  return 0;
  /*
	if(buffer_temp[1] == 0)
	{
		buffer_temp[1] = buffer_temp[0];
		buffer_temp[0] = '0';
	}
	if((buffer_temp[0] >= 'a') && (buffer_temp[0] <= 'z'))
		buffer_temp[0] -= 32;
	if((buffer_temp[1] >= 'a') && (buffer_temp[1] <= 'z'))
		buffer_temp[1] -= 32;

	*buffer = buffer_temp[0];
	buffer++;
	*buffer = buffer_temp[1];
  */

  /*
  unsigned char temp[3];

  temp[0] = (temp[0] & 0xF0) >> 4;
  if((temp[0] >= 0) && (temp[0] <= 9))
  {
    temp[0] += 0x30;
  }
  else
  {
    temp[0] += 0x41;
  }

  temp[1] = temp[1] & 0x0F;
  if((temp[1] >= 0) && (temp[1] <= 9))
  {
    temp[1] += 0x30;
  }
  else
  {
    temp[1] += 0x41;
  }

  temp[2] = 0;

  *buffer = buffer_temp[0];
	buffer++;
	*buffer = buffer_temp[1];
  */
}

void buzzer_ms(unsigned int ms)
{
	/*
  Time_delay.buzzer.stack_top = ms;
	Time_delay.buzzer.count = 0;
	Time_delay.buzzer.time_out = 0;
	Time_delay.buzzer.started = 1;
	Time_delay.buzzer.enabled = 1;
	*/
}

unsigned char get_key()
{
	if(GetBit(PINB,4) == 0)
		return 1;
	else
		return 0;
}

#pragma vector=TIMER1_OVF_vect
__interrupt void timer1_ovf_ser(void)
{
	//TCNT1H = 228;				// 1s
	//TCNT1L = 224;					// 1s
}

unsigned char get_PIR_trigger(unsigned char level)
{
	switch(level)
	{
		case '0':
			// add your code here
			return 0;
		case '1':
			// add your code here
			// return your get level
			return 0;
		case '2':
			// add your code here
			// return your get level
			return 0;
		case '3':
			// add your code here
			// return your get level
			return 0;
		default:
			break;
	}
	return 1;
}

unsigned char get_US_trigger(unsigned char level)
{
	switch(level)
	{
		case '0':
			// add your code here
			return 0;
		case '1':
			// add your code here
			// return your get level
			return 0;
		case '2':
			// add your code here
			// return your get level
			return 0;
		case '3':
			// add your code here
			// return your get level
			return 0;
		default:
			break;
	}
	return 1;
}

void timer1_initial(void)
{
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 7.200 kHz
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x05;
TCNT1H=228;					// 1s
TCNT1L=224;					// 1s
ICR1H=0x00;					
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ClrBit(PRR,PRTIM1);
}

void adc_initial()
{
// ADC initialization
// ADC Clock frequency: 921.600 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: None
// Digital input buffers on ADC0: Off, ADC1: Off, ADC2: On, ADC3: Off
// ADC4: Off, ADC5: Off, ADC6: Off, ADC7: Off
DIDR0=0xFB;
ADMUX=ADC_VREF_TYPE;
ADCSRA=0x80;
ADCSRA |= 0x05;
}

unsigned int read_adc10bit(unsigned char adc_input)
{
	ADMUX = adc_input | ADC_VREF_TYPE;
	g_temp = ADMUX;
	// Delay needed for the stabilization of the ADC input voltage
	delay_us(10);
	// Start the AD conversion
	ADCSRA|=0x40;
	// Wait for the AD conversion to complete
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;
	return ADC;
}

unsigned char read_adc8bit(unsigned char adc_input)
{
  ADMUX = adc_input | ADC_VREF_TYPE | 0x20;
  // Delay needed for the stabilization of the ADC input voltage
  delay_us(10);
  // Start the AD conversion
  ADCSRA|=0x40;
  // Wait for the AD conversion to complete
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  return ADCH;
}

void system_reset(void)
{
	WDTCSR = 0x18;
	WDTCSR = 0x08;
}

void WDT_off(void)
{
	MCUSR &= ~(1<<WDRF);
	WDTCSR |= (1<<WDCE) | (1<<WDE);
	WDTCSR = 0x00;
}
