#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\ioavr.h"
/**************************************************************
 **             - IO_AVR.H -
 **
 **     I/O definitions for iccAVR
 **
 **     Used with iccAVR.
 **
 **     Copyright IAR Systems 2001. All rights reserved.
 **
 **     File version: $Revision: 1.33 $
 **
 **************************************************************/



#pragma system_include



#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"
/****************************************************************************
 **             - iom644p.h -
 **
 **     This file declares the internal register addresses for ATmega644P.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 2005. All rights reserved.
 **
 **     File version: $Revision: 1.4 $
 **
 ***************************************************************************/



#pragma system_include



#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"
/**************************************************************
 **             - iomacro.h -
 **
 **     This file defines the Special Function Register Macros
 **     for Atmel AT90S.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 1999 - 2005. All rights reserved.
 **
 **     File version: $Revision: 1.28 $
 **
 **************************************************************/



#pragma system_include












/* The assembler uses a special set of macros... */
#line 187 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 199 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 207 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 219 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 232 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 244 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 263 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 282 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 290 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 298 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 311 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 335 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 344 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 356 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



  
#line 376 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"
  
#line 393 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 411 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 429 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 447 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 464 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 491 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 518 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 546 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 574 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 601 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 626 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 653 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 677 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 705 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 746 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



#line 787 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 826 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"

#line 940 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"



/*
  SFR_B(SREG,   0x3F) Expands to:
  __io union {
              unsigned char   SREG;          // The sfrb as 1 byte
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_Bit0:1,
                                    SREG_Bit1:1,
                                    SREG_Bit2:1,
                                    SREG_Bit3:1,
                                    SREG_Bit4:1,
                                    SREG_Bit5:1,
                                    SREG_Bit6:1,
                                    SREG_Bit7:1;
                     };
             } @ 0x3F;
*/




/*
  SFR_B_N(0x3F,SREG,I,T,H,S,V,N,Z,C) Expands to:
  __io union {
              unsigned char   SREG;          // The sfrb as 1 byte
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_Bit0:1,
                                    SREG_Bit1:1,
                                    SREG_Bit2:1,
                                    SREG_Bit3:1,
                                    SREG_Bit4:1,
                                    SREG_Bit5:1,
                                    SREG_Bit6:1,
                                    SREG_Bit7:1;
                     };
              struct {                        // The sfrb as 8 bits
                      unsigned char SREG_C:1,
                                    SREG_Z:1,
                                    SREG_N:1,
                                    SREG_V:1,
                                    SREG_S:1,
                                    SREG_H:1,
                                    SREG_T:1,
                                    SREG_I:1;
                     };
             } @ 0x3F;
*/
#line 1015 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"








#line 1054 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 1087 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"




#line 1139 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iomacro.h"


#line 21 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"









/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */


#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

__io union { unsigned char UDR1; struct { unsigned char UDR1_Bit0:1, UDR1_Bit1:1, UDR1_Bit2:1, UDR1_Bit3:1, UDR1_Bit4:1, UDR1_Bit5:1, UDR1_Bit6:1, UDR1_Bit7:1; }; } @ 0xCE;
__io union { unsigned short UBRR1; struct { unsigned char UBRR1_Bit0:1, UBRR1_Bit1:1, UBRR1_Bit2:1, UBRR1_Bit3:1, UBRR1_Bit4:1, UBRR1_Bit5:1, UBRR1_Bit6:1, UBRR1_Bit7:1; unsigned char UBRR1_Bit8:1, UBRR1_Bit9:1, UBRR1_Bit10:1, UBRR1_Bit11:1, UBRR1_Bit12:1, UBRR1_Bit13:1, UBRR1_Bit14:1, UBRR1_Bit15:1; }; struct { unsigned char UBRR1L; unsigned char UBRR1H; }; struct { unsigned char UBRR1L_Bit0:1, UBRR1L_Bit1:1, UBRR1L_Bit2:1, UBRR1L_Bit3:1, UBRR1L_Bit4:1, UBRR1L_Bit5:1, UBRR1L_Bit6:1, UBRR1L_Bit7:1; unsigned char UBRR1H_Bit0:1, UBRR1H_Bit1:1, UBRR1H_Bit2:1, UBRR1H_Bit3:1, UBRR1H_Bit4:1, UBRR1H_Bit5:1, UBRR1H_Bit6:1, UBRR1H_Bit7:1; }; } @ 0xCC;
__io union { unsigned char UCSR1C; struct { unsigned char UCSR1C_Bit0:1, UCSR1C_Bit1:1, UCSR1C_Bit2:1, UCSR1C_Bit3:1, UCSR1C_Bit4:1, UCSR1C_Bit5:1, UCSR1C_Bit6:1, UCSR1C_Bit7:1; }; struct { unsigned char UCSR1C_UCPOL1:1, UCSR1C_UCSZ10:1, UCSR1C_UCSZ11:1, UCSR1C_USBS1:1, UCSR1C_UPM10:1, UCSR1C_UPM11:1, UCSR1C_UMSEL10:1, UCSR1C_UMSEL11:1; }; } @ 0xCA;
__io union { unsigned char UCSR1B; struct { unsigned char UCSR1B_Bit0:1, UCSR1B_Bit1:1, UCSR1B_Bit2:1, UCSR1B_Bit3:1, UCSR1B_Bit4:1, UCSR1B_Bit5:1, UCSR1B_Bit6:1, UCSR1B_Bit7:1; }; struct { unsigned char UCSR1B_TXB81:1, UCSR1B_RXB81:1, UCSR1B_UCSZ12:1, UCSR1B_TXEN1:1, UCSR1B_RXEN1:1, UCSR1B_UDRIE1:1, UCSR1B_TXCIE1:1, UCSR1B_RXCIE1:1; }; } @ 0xC9;
__io union { unsigned char UCSR1A; struct { unsigned char UCSR1A_Bit0:1, UCSR1A_Bit1:1, UCSR1A_Bit2:1, UCSR1A_Bit3:1, UCSR1A_Bit4:1, UCSR1A_Bit5:1, UCSR1A_Bit6:1, UCSR1A_Bit7:1; }; struct { unsigned char UCSR1A_MPCM1:1, UCSR1A_U2X1:1, UCSR1A_UPE1:1, UCSR1A_DOR1:1, UCSR1A_FE1:1, UCSR1A_UDRE1:1, UCSR1A_TXC1:1, UCSR1A_RXC1:1; }; } @ 0xC8;
__io union { unsigned char UDR0; struct { unsigned char UDR0_Bit0:1, UDR0_Bit1:1, UDR0_Bit2:1, UDR0_Bit3:1, UDR0_Bit4:1, UDR0_Bit5:1, UDR0_Bit6:1, UDR0_Bit7:1; }; } @ 0xC6;
__io union { unsigned short UBRR0; struct { unsigned char UBRR0_Bit0:1, UBRR0_Bit1:1, UBRR0_Bit2:1, UBRR0_Bit3:1, UBRR0_Bit4:1, UBRR0_Bit5:1, UBRR0_Bit6:1, UBRR0_Bit7:1; unsigned char UBRR0_Bit8:1, UBRR0_Bit9:1, UBRR0_Bit10:1, UBRR0_Bit11:1, UBRR0_Bit12:1, UBRR0_Bit13:1, UBRR0_Bit14:1, UBRR0_Bit15:1; }; struct { unsigned char UBRR0L; unsigned char UBRR0H; }; struct { unsigned char UBRR0L_Bit0:1, UBRR0L_Bit1:1, UBRR0L_Bit2:1, UBRR0L_Bit3:1, UBRR0L_Bit4:1, UBRR0L_Bit5:1, UBRR0L_Bit6:1, UBRR0L_Bit7:1; unsigned char UBRR0H_Bit0:1, UBRR0H_Bit1:1, UBRR0H_Bit2:1, UBRR0H_Bit3:1, UBRR0H_Bit4:1, UBRR0H_Bit5:1, UBRR0H_Bit6:1, UBRR0H_Bit7:1; }; } @ 0xC4;
__io union { unsigned char UCSR0C; struct { unsigned char UCSR0C_Bit0:1, UCSR0C_Bit1:1, UCSR0C_Bit2:1, UCSR0C_Bit3:1, UCSR0C_Bit4:1, UCSR0C_Bit5:1, UCSR0C_Bit6:1, UCSR0C_Bit7:1; }; struct { unsigned char UCSR0C_UCPOL0:1, UCSR0C_UCSZ00:1, UCSR0C_UCSZ01:1, UCSR0C_USBS0:1, UCSR0C_UPM00:1, UCSR0C_UPM01:1, UCSR0C_UMSEL00:1, UCSR0C_UMSEL01:1; }; } @ 0xC2;
__io union { unsigned char UCSR0B; struct { unsigned char UCSR0B_Bit0:1, UCSR0B_Bit1:1, UCSR0B_Bit2:1, UCSR0B_Bit3:1, UCSR0B_Bit4:1, UCSR0B_Bit5:1, UCSR0B_Bit6:1, UCSR0B_Bit7:1; }; struct { unsigned char UCSR0B_TXB80:1, UCSR0B_RXB80:1, UCSR0B_UCSZ02:1, UCSR0B_TXEN0:1, UCSR0B_RXEN0:1, UCSR0B_UDRIE0:1, UCSR0B_TXCIE0:1, UCSR0B_RXCIE0:1; }; } @ 0xC1;
__io union { unsigned char UCSR0A; struct { unsigned char UCSR0A_Bit0:1, UCSR0A_Bit1:1, UCSR0A_Bit2:1, UCSR0A_Bit3:1, UCSR0A_Bit4:1, UCSR0A_Bit5:1, UCSR0A_Bit6:1, UCSR0A_Bit7:1; }; struct { unsigned char UCSR0A_MPCM0:1, UCSR0A_U2X0:1, UCSR0A_UPE0:1, UCSR0A_DOR0:1, UCSR0A_FE0:1, UCSR0A_UDRE0:1, UCSR0A_TXC0:1, UCSR0A_RXC0:1; }; } @ 0xC0;
__io union { unsigned char TWAM; struct { unsigned char TWAM_Bit0:1, TWAM_Bit1:1, TWAM_Bit2:1, TWAM_Bit3:1, TWAM_Bit4:1, TWAM_Bit5:1, TWAM_Bit6:1, TWAM_Bit7:1; }; struct { unsigned char TWAM_Dummy0:1, TWAM_TWAM0:1, TWAM_TWAM1:1, TWAM_TWAM2:1, TWAM_TWAM3:1, TWAM_TWAM4:1, TWAM_TWAM5:1, TWAM_TWAM6:1; }; } @ 0xBD;
__io union { unsigned char TWCR; struct { unsigned char TWCR_Bit0:1, TWCR_Bit1:1, TWCR_Bit2:1, TWCR_Bit3:1, TWCR_Bit4:1, TWCR_Bit5:1, TWCR_Bit6:1, TWCR_Bit7:1; }; struct { unsigned char TWCR_TWIE:1, TWCR_Dummy1:1, TWCR_TWEN:1, TWCR_TWWC:1, TWCR_TWSTO:1, TWCR_TWSTA:1, TWCR_TWEA:1, TWCR_TWINT:1; }; } @ 0xBC;
__io union { unsigned char TWDR; struct { unsigned char TWDR_Bit0:1, TWDR_Bit1:1, TWDR_Bit2:1, TWDR_Bit3:1, TWDR_Bit4:1, TWDR_Bit5:1, TWDR_Bit6:1, TWDR_Bit7:1; }; } @ 0xBB;
__io union { unsigned char TWAR; struct { unsigned char TWAR_Bit0:1, TWAR_Bit1:1, TWAR_Bit2:1, TWAR_Bit3:1, TWAR_Bit4:1, TWAR_Bit5:1, TWAR_Bit6:1, TWAR_Bit7:1; }; struct { unsigned char TWAR_TWGCE:1, TWAR_TWA0:1, TWAR_TWA1:1, TWAR_TWA2:1, TWAR_TWA3:1, TWAR_TWA4:1, TWAR_TWA5:1, TWAR_TWA6:1; }; } @ 0xBA;
__io union { unsigned char TWSR; struct { unsigned char TWSR_Bit0:1, TWSR_Bit1:1, TWSR_Bit2:1, TWSR_Bit3:1, TWSR_Bit4:1, TWSR_Bit5:1, TWSR_Bit6:1, TWSR_Bit7:1; }; struct { unsigned char TWSR_TWPS0:1, TWSR_TWPS1:1, TWSR_Dummy2:1, TWSR_TWS3:1, TWSR_TWS4:1, TWSR_TWS5:1, TWSR_TWS6:1, TWSR_TWS7:1; }; } @ 0xB9;
__io union { unsigned char TWBR; struct { unsigned char TWBR_Bit0:1, TWBR_Bit1:1, TWBR_Bit2:1, TWBR_Bit3:1, TWBR_Bit4:1, TWBR_Bit5:1, TWBR_Bit6:1, TWBR_Bit7:1; }; } @ 0xB8;
__io union { unsigned char ASSR; struct { unsigned char ASSR_Bit0:1, ASSR_Bit1:1, ASSR_Bit2:1, ASSR_Bit3:1, ASSR_Bit4:1, ASSR_Bit5:1, ASSR_Bit6:1, ASSR_Bit7:1; }; struct { unsigned char ASSR_TCR2BUB:1, ASSR_TCR2AUB:1, ASSR_OCR2BUB:1, ASSR_OCR2AUB:1, ASSR_TCN2UB:1, ASSR_AS2:1, ASSR_EXCLK:1, ASSR_Dummy7:1; }; } @ 0xB6;
__io union { unsigned char OCR2B; struct { unsigned char OCR2B_Bit0:1, OCR2B_Bit1:1, OCR2B_Bit2:1, OCR2B_Bit3:1, OCR2B_Bit4:1, OCR2B_Bit5:1, OCR2B_Bit6:1, OCR2B_Bit7:1; }; } @ 0xB4;
__io union { unsigned char OCR2A; struct { unsigned char OCR2A_Bit0:1, OCR2A_Bit1:1, OCR2A_Bit2:1, OCR2A_Bit3:1, OCR2A_Bit4:1, OCR2A_Bit5:1, OCR2A_Bit6:1, OCR2A_Bit7:1; }; } @ 0xB3;
__io union { unsigned char TCNT2; struct { unsigned char TCNT2_Bit0:1, TCNT2_Bit1:1, TCNT2_Bit2:1, TCNT2_Bit3:1, TCNT2_Bit4:1, TCNT2_Bit5:1, TCNT2_Bit6:1, TCNT2_Bit7:1; }; } @ 0xB2;
__io union { unsigned char TCCR2B; struct { unsigned char TCCR2B_Bit0:1, TCCR2B_Bit1:1, TCCR2B_Bit2:1, TCCR2B_Bit3:1, TCCR2B_Bit4:1, TCCR2B_Bit5:1, TCCR2B_Bit6:1, TCCR2B_Bit7:1; }; struct { unsigned char TCCR2B_CS20:1, TCCR2B_CS21:1, TCCR2B_CS22:1, TCCR2B_WGM22:1, TCCR2B_Dummy4:1, TCCR2B_Dummy5:1, TCCR2B_FOC2B:1, TCCR2B_FOC2A:1; }; } @ 0xB1;
__io union { unsigned char TCCR2A; struct { unsigned char TCCR2A_Bit0:1, TCCR2A_Bit1:1, TCCR2A_Bit2:1, TCCR2A_Bit3:1, TCCR2A_Bit4:1, TCCR2A_Bit5:1, TCCR2A_Bit6:1, TCCR2A_Bit7:1; }; struct { unsigned char TCCR2A_WGM20:1, TCCR2A_WGM21:1, TCCR2A_Dummy2:1, TCCR2A_Dummy3:1, TCCR2A_COM2B0:1, TCCR2A_COM2B1:1, TCCR2A_COM2A0:1, TCCR2A_COM2A1:1; }; } @ 0xB0;
__io union { unsigned short OCR1B; struct { unsigned char OCR1B_Bit0:1, OCR1B_Bit1:1, OCR1B_Bit2:1, OCR1B_Bit3:1, OCR1B_Bit4:1, OCR1B_Bit5:1, OCR1B_Bit6:1, OCR1B_Bit7:1; unsigned char OCR1B_Bit8:1, OCR1B_Bit9:1, OCR1B_Bit10:1, OCR1B_Bit11:1, OCR1B_Bit12:1, OCR1B_Bit13:1, OCR1B_Bit14:1, OCR1B_Bit15:1; }; struct { unsigned char OCR1BL; unsigned char OCR1BH; }; struct { unsigned char OCR1BL_Bit0:1, OCR1BL_Bit1:1, OCR1BL_Bit2:1, OCR1BL_Bit3:1, OCR1BL_Bit4:1, OCR1BL_Bit5:1, OCR1BL_Bit6:1, OCR1BL_Bit7:1; unsigned char OCR1BH_Bit0:1, OCR1BH_Bit1:1, OCR1BH_Bit2:1, OCR1BH_Bit3:1, OCR1BH_Bit4:1, OCR1BH_Bit5:1, OCR1BH_Bit6:1, OCR1BH_Bit7:1; }; } @ 0x8A;
__io union { unsigned short OCR1A; struct { unsigned char OCR1A_Bit0:1, OCR1A_Bit1:1, OCR1A_Bit2:1, OCR1A_Bit3:1, OCR1A_Bit4:1, OCR1A_Bit5:1, OCR1A_Bit6:1, OCR1A_Bit7:1; unsigned char OCR1A_Bit8:1, OCR1A_Bit9:1, OCR1A_Bit10:1, OCR1A_Bit11:1, OCR1A_Bit12:1, OCR1A_Bit13:1, OCR1A_Bit14:1, OCR1A_Bit15:1; }; struct { unsigned char OCR1AL; unsigned char OCR1AH; }; struct { unsigned char OCR1AL_Bit0:1, OCR1AL_Bit1:1, OCR1AL_Bit2:1, OCR1AL_Bit3:1, OCR1AL_Bit4:1, OCR1AL_Bit5:1, OCR1AL_Bit6:1, OCR1AL_Bit7:1; unsigned char OCR1AH_Bit0:1, OCR1AH_Bit1:1, OCR1AH_Bit2:1, OCR1AH_Bit3:1, OCR1AH_Bit4:1, OCR1AH_Bit5:1, OCR1AH_Bit6:1, OCR1AH_Bit7:1; }; } @ 0x88;
__io union { unsigned short ICR1; struct { unsigned char ICR1_Bit0:1, ICR1_Bit1:1, ICR1_Bit2:1, ICR1_Bit3:1, ICR1_Bit4:1, ICR1_Bit5:1, ICR1_Bit6:1, ICR1_Bit7:1; unsigned char ICR1_Bit8:1, ICR1_Bit9:1, ICR1_Bit10:1, ICR1_Bit11:1, ICR1_Bit12:1, ICR1_Bit13:1, ICR1_Bit14:1, ICR1_Bit15:1; }; struct { unsigned char ICR1L; unsigned char ICR1H; }; struct { unsigned char ICR1L_Bit0:1, ICR1L_Bit1:1, ICR1L_Bit2:1, ICR1L_Bit3:1, ICR1L_Bit4:1, ICR1L_Bit5:1, ICR1L_Bit6:1, ICR1L_Bit7:1; unsigned char ICR1H_Bit0:1, ICR1H_Bit1:1, ICR1H_Bit2:1, ICR1H_Bit3:1, ICR1H_Bit4:1, ICR1H_Bit5:1, ICR1H_Bit6:1, ICR1H_Bit7:1; }; } @ 0x86;
__io union { unsigned short TCNT1; struct { unsigned char TCNT1_Bit0:1, TCNT1_Bit1:1, TCNT1_Bit2:1, TCNT1_Bit3:1, TCNT1_Bit4:1, TCNT1_Bit5:1, TCNT1_Bit6:1, TCNT1_Bit7:1; unsigned char TCNT1_Bit8:1, TCNT1_Bit9:1, TCNT1_Bit10:1, TCNT1_Bit11:1, TCNT1_Bit12:1, TCNT1_Bit13:1, TCNT1_Bit14:1, TCNT1_Bit15:1; }; struct { unsigned char TCNT1L; unsigned char TCNT1H; }; struct { unsigned char TCNT1L_Bit0:1, TCNT1L_Bit1:1, TCNT1L_Bit2:1, TCNT1L_Bit3:1, TCNT1L_Bit4:1, TCNT1L_Bit5:1, TCNT1L_Bit6:1, TCNT1L_Bit7:1; unsigned char TCNT1H_Bit0:1, TCNT1H_Bit1:1, TCNT1H_Bit2:1, TCNT1H_Bit3:1, TCNT1H_Bit4:1, TCNT1H_Bit5:1, TCNT1H_Bit6:1, TCNT1H_Bit7:1; }; } @ 0x84;
__io union { unsigned char TCCR1C; struct { unsigned char TCCR1C_Bit0:1, TCCR1C_Bit1:1, TCCR1C_Bit2:1, TCCR1C_Bit3:1, TCCR1C_Bit4:1, TCCR1C_Bit5:1, TCCR1C_Bit6:1, TCCR1C_Bit7:1; }; struct { unsigned char TCCR1C_Dummy0:1, TCCR1C_Dummy1:1, TCCR1C_Dummy2:1, TCCR1C_Dummy3:1, TCCR1C_Dummy4:1, TCCR1C_Dummy5:1, TCCR1C_FOC1B:1, TCCR1C_FOC1A:1; }; } @ 0x82;
__io union { unsigned char TCCR1B; struct { unsigned char TCCR1B_Bit0:1, TCCR1B_Bit1:1, TCCR1B_Bit2:1, TCCR1B_Bit3:1, TCCR1B_Bit4:1, TCCR1B_Bit5:1, TCCR1B_Bit6:1, TCCR1B_Bit7:1; }; struct { unsigned char TCCR1B_CS10:1, TCCR1B_CS11:1, TCCR1B_CS12:1, TCCR1B_WGM12:1, TCCR1B_WGM13:1, TCCR1B_Dummy5:1, TCCR1B_ICES1:1, TCCR1B_ICNC1:1; }; } @ 0x81;
__io union { unsigned char TCCR1A; struct { unsigned char TCCR1A_Bit0:1, TCCR1A_Bit1:1, TCCR1A_Bit2:1, TCCR1A_Bit3:1, TCCR1A_Bit4:1, TCCR1A_Bit5:1, TCCR1A_Bit6:1, TCCR1A_Bit7:1; }; struct { unsigned char TCCR1A_WGM10:1, TCCR1A_WGM11:1, TCCR1A_Dummy2:1, TCCR1A_Dummy3:1, TCCR1A_COM1B0:1, TCCR1A_COM1B1:1, TCCR1A_COM1A0:1, TCCR1A_COM1A1:1; }; } @ 0x80;
__io union { unsigned char DIDR1; struct { unsigned char DIDR1_Bit0:1, DIDR1_Bit1:1, DIDR1_Bit2:1, DIDR1_Bit3:1, DIDR1_Bit4:1, DIDR1_Bit5:1, DIDR1_Bit6:1, DIDR1_Bit7:1; }; struct { unsigned char DIDR1_AIN0D:1, DIDR1_AIN1D:1, DIDR1_Dummy2:1, DIDR1_Dummy3:1, DIDR1_Dummy4:1, DIDR1_Dummy5:1, DIDR1_Dummy6:1, DIDR1_Dummy7:1; }; } @ 0x7F;
__io union { unsigned char DIDR0; struct { unsigned char DIDR0_Bit0:1, DIDR0_Bit1:1, DIDR0_Bit2:1, DIDR0_Bit3:1, DIDR0_Bit4:1, DIDR0_Bit5:1, DIDR0_Bit6:1, DIDR0_Bit7:1; }; struct { unsigned char DIDR0_ADC0D:1, DIDR0_ADC1D:1, DIDR0_ADC2D:1, DIDR0_ADC3D:1, DIDR0_ADC4D:1, DIDR0_ADC5D:1, DIDR0_ADC6D:1, DIDR0_ADC7D:1; }; } @ 0x7E;
__io union { unsigned char ADMUX; struct { unsigned char ADMUX_Bit0:1, ADMUX_Bit1:1, ADMUX_Bit2:1, ADMUX_Bit3:1, ADMUX_Bit4:1, ADMUX_Bit5:1, ADMUX_Bit6:1, ADMUX_Bit7:1; }; struct { unsigned char ADMUX_MUX0:1, ADMUX_MUX1:1, ADMUX_MUX2:1, ADMUX_MUX3:1, ADMUX_MUX4:1, ADMUX_ADLAR:1, ADMUX_REFS0:1, ADMUX_REFS1:1; }; } @ 0x7C;
__io union { unsigned char ADCSRB; struct { unsigned char ADCSRB_Bit0:1, ADCSRB_Bit1:1, ADCSRB_Bit2:1, ADCSRB_Bit3:1, ADCSRB_Bit4:1, ADCSRB_Bit5:1, ADCSRB_Bit6:1, ADCSRB_Bit7:1; }; struct { unsigned char ADCSRB_ADTS0:1, ADCSRB_ADTS1:1, ADCSRB_ADTS2:1, ADCSRB_Dummy3:1, ADCSRB_Dummy4:1, ADCSRB_Dummy5:1, ADCSRB_ACME:1, ADCSRB_Dummy7:1; }; } @ 0x7B;
__io union { unsigned char ADCSRA; struct { unsigned char ADCSRA_Bit0:1, ADCSRA_Bit1:1, ADCSRA_Bit2:1, ADCSRA_Bit3:1, ADCSRA_Bit4:1, ADCSRA_Bit5:1, ADCSRA_Bit6:1, ADCSRA_Bit7:1; }; struct { unsigned char ADCSRA_ADPS0:1, ADCSRA_ADPS1:1, ADCSRA_ADPS2:1, ADCSRA_ADIE:1, ADCSRA_ADIF:1, ADCSRA_ADATE:1, ADCSRA_ADSC:1, ADCSRA_ADEN:1; }; } @ 0x7A;
__io union { unsigned short ADC; struct { unsigned char ADC_Bit0:1, ADC_Bit1:1, ADC_Bit2:1, ADC_Bit3:1, ADC_Bit4:1, ADC_Bit5:1, ADC_Bit6:1, ADC_Bit7:1; unsigned char ADC_Bit8:1, ADC_Bit9:1, ADC_Bit10:1, ADC_Bit11:1, ADC_Bit12:1, ADC_Bit13:1, ADC_Bit14:1, ADC_Bit15:1; }; struct { unsigned char ADCL; unsigned char ADCH; }; struct { unsigned char ADCL_Bit0:1, ADCL_Bit1:1, ADCL_Bit2:1, ADCL_Bit3:1, ADCL_Bit4:1, ADCL_Bit5:1, ADCL_Bit6:1, ADCL_Bit7:1; unsigned char ADCH_Bit0:1, ADCH_Bit1:1, ADCH_Bit2:1, ADCH_Bit3:1, ADCH_Bit4:1, ADCH_Bit5:1, ADCH_Bit6:1, ADCH_Bit7:1; }; } @ 0x78;
__io union { unsigned char PCMSK3; struct { unsigned char PCMSK3_Bit0:1, PCMSK3_Bit1:1, PCMSK3_Bit2:1, PCMSK3_Bit3:1, PCMSK3_Bit4:1, PCMSK3_Bit5:1, PCMSK3_Bit6:1, PCMSK3_Bit7:1; }; struct { unsigned char PCMSK3_PCINT24:1, PCMSK3_PCINT25:1, PCMSK3_PCINT26:1, PCMSK3_PCINT27:1, PCMSK3_PCINT28:1, PCMSK3_PCINT29:1, PCMSK3_PCINT30:1, PCMSK3_PCINT31:1; }; } @ 0x73;
__io union { unsigned char TIMSK2; struct { unsigned char TIMSK2_Bit0:1, TIMSK2_Bit1:1, TIMSK2_Bit2:1, TIMSK2_Bit3:1, TIMSK2_Bit4:1, TIMSK2_Bit5:1, TIMSK2_Bit6:1, TIMSK2_Bit7:1; }; struct { unsigned char TIMSK2_TOIE2:1, TIMSK2_OCIE2A:1, TIMSK2_OCIE2B:1, TIMSK2_Dummy3:1, TIMSK2_Dummy4:1, TIMSK2_Dummy5:1, TIMSK2_Dummy6:1, TIMSK2_Dummy7:1; }; } @ 0x70;
__io union { unsigned char TIMSK1; struct { unsigned char TIMSK1_Bit0:1, TIMSK1_Bit1:1, TIMSK1_Bit2:1, TIMSK1_Bit3:1, TIMSK1_Bit4:1, TIMSK1_Bit5:1, TIMSK1_Bit6:1, TIMSK1_Bit7:1; }; struct { unsigned char TIMSK1_TOIE1:1, TIMSK1_OCIE1A:1, TIMSK1_OCIE1B:1, TIMSK1_Dummy3:1, TIMSK1_Dummy4:1, TIMSK1_ICIE1:1, TIMSK1_Dummy6:1, TIMSK1_Dummy7:1; }; } @ 0x6F;
__io union { unsigned char TIMSK0; struct { unsigned char TIMSK0_Bit0:1, TIMSK0_Bit1:1, TIMSK0_Bit2:1, TIMSK0_Bit3:1, TIMSK0_Bit4:1, TIMSK0_Bit5:1, TIMSK0_Bit6:1, TIMSK0_Bit7:1; }; struct { unsigned char TIMSK0_TOIE0:1, TIMSK0_OCIE0A:1, TIMSK0_OCIE0B:1, TIMSK0_Dummy3:1, TIMSK0_Dummy4:1, TIMSK0_Dummy5:1, TIMSK0_Dummy6:1, TIMSK0_Dummy7:1; }; } @ 0x6E;
__io union { unsigned char PCMSK2; struct { unsigned char PCMSK2_Bit0:1, PCMSK2_Bit1:1, PCMSK2_Bit2:1, PCMSK2_Bit3:1, PCMSK2_Bit4:1, PCMSK2_Bit5:1, PCMSK2_Bit6:1, PCMSK2_Bit7:1; }; struct { unsigned char PCMSK2_PCINT16:1, PCMSK2_PCINT17:1, PCMSK2_PCINT18:1, PCMSK2_PCINT19:1, PCMSK2_PCINT20:1, PCMSK2_PCINT21:1, PCMSK2_PCINT22:1, PCMSK2_PCINT23:1; }; } @ 0x6D;
__io union { unsigned char PCMSK1; struct { unsigned char PCMSK1_Bit0:1, PCMSK1_Bit1:1, PCMSK1_Bit2:1, PCMSK1_Bit3:1, PCMSK1_Bit4:1, PCMSK1_Bit5:1, PCMSK1_Bit6:1, PCMSK1_Bit7:1; }; struct { unsigned char PCMSK1_PCINT8:1, PCMSK1_PCINT9:1, PCMSK1_PCINT10:1, PCMSK1_PCINT11:1, PCMSK1_PCINT12:1, PCMSK1_PCINT13:1, PCMSK1_PCINT14:1, PCMSK1_PCINT15:1; }; } @ 0x6C;
__io union { unsigned char PCMSK0; struct { unsigned char PCMSK0_Bit0:1, PCMSK0_Bit1:1, PCMSK0_Bit2:1, PCMSK0_Bit3:1, PCMSK0_Bit4:1, PCMSK0_Bit5:1, PCMSK0_Bit6:1, PCMSK0_Bit7:1; }; struct { unsigned char PCMSK0_PCINT0:1, PCMSK0_PCINT1:1, PCMSK0_PCINT2:1, PCMSK0_PCINT3:1, PCMSK0_PCINT4:1, PCMSK0_PCINT5:1, PCMSK0_PCINT6:1, PCMSK0_PCINT7:1; }; } @ 0x6B;
__io union { unsigned char EICRA; struct { unsigned char EICRA_Bit0:1, EICRA_Bit1:1, EICRA_Bit2:1, EICRA_Bit3:1, EICRA_Bit4:1, EICRA_Bit5:1, EICRA_Bit6:1, EICRA_Bit7:1; }; struct { unsigned char EICRA_ISC00:1, EICRA_ISC01:1, EICRA_ISC10:1, EICRA_ISC11:1, EICRA_ISC20:1, EICRA_ISC21:1, EICRA_Dummy6:1, EICRA_Dummy7:1; }; } @ 0x69;
__io union { unsigned char PCICR; struct { unsigned char PCICR_Bit0:1, PCICR_Bit1:1, PCICR_Bit2:1, PCICR_Bit3:1, PCICR_Bit4:1, PCICR_Bit5:1, PCICR_Bit6:1, PCICR_Bit7:1; }; struct { unsigned char PCICR_PCIE0:1, PCICR_PCIE1:1, PCICR_PCIE2:1, PCICR_PCIE3:1, PCICR_Dummy4:1, PCICR_Dummy5:1, PCICR_Dummy6:1, PCICR_Dummy7:1; }; } @ 0x68;
__io union { unsigned char OSCCAL; struct { unsigned char OSCCAL_Bit0:1, OSCCAL_Bit1:1, OSCCAL_Bit2:1, OSCCAL_Bit3:1, OSCCAL_Bit4:1, OSCCAL_Bit5:1, OSCCAL_Bit6:1, OSCCAL_Bit7:1; }; } @ 0x66;
__io union { unsigned char PRR; struct { unsigned char PRR_Bit0:1, PRR_Bit1:1, PRR_Bit2:1, PRR_Bit3:1, PRR_Bit4:1, PRR_Bit5:1, PRR_Bit6:1, PRR_Bit7:1; }; struct { unsigned char PRR_PRADC:1, PRR_PRUSART0:1, PRR_PRSPI:1, PRR_PRTIM1:1, PRR_Dummy4:1, PRR_PRTIM0:1, PRR_PRTIM2:1, PRR_PRTWI:1; }; } @ 0x64;
__io union { unsigned char CLKPR; struct { unsigned char CLKPR_Bit0:1, CLKPR_Bit1:1, CLKPR_Bit2:1, CLKPR_Bit3:1, CLKPR_Bit4:1, CLKPR_Bit5:1, CLKPR_Bit6:1, CLKPR_Bit7:1; }; struct { unsigned char CLKPR_CLKPS0:1, CLKPR_CLKPS1:1, CLKPR_CLKPS2:1, CLKPR_CLKPS3:1, CLKPR_Dummy4:1, CLKPR_Dummy5:1, CLKPR_Dummy6:1, CLKPR_CLKPCE:1; }; } @ 0x61;
__io union { unsigned char WDTCSR; struct { unsigned char WDTCSR_Bit0:1, WDTCSR_Bit1:1, WDTCSR_Bit2:1, WDTCSR_Bit3:1, WDTCSR_Bit4:1, WDTCSR_Bit5:1, WDTCSR_Bit6:1, WDTCSR_Bit7:1; }; struct { unsigned char WDTCSR_WDP0:1, WDTCSR_WDP1:1, WDTCSR_WDP2:1, WDTCSR_WDE:1, WDTCSR_WDCE:1, WDTCSR_WDP3:1, WDTCSR_WDIE:1, WDTCSR_WDIF:1; }; } @ 0x60;
__io union { unsigned char SREG; struct { unsigned char SREG_Bit0:1, SREG_Bit1:1, SREG_Bit2:1, SREG_Bit3:1, SREG_Bit4:1, SREG_Bit5:1, SREG_Bit6:1, SREG_Bit7:1; }; struct { unsigned char SREG_C:1, SREG_Z:1, SREG_N:1, SREG_V:1, SREG_S:1, SREG_H:1, SREG_T:1, SREG_I:1; }; } @ 0x3F;
__io union { unsigned short SP; struct { unsigned char SP_Bit0:1, SP_Bit1:1, SP_Bit2:1, SP_Bit3:1, SP_Bit4:1, SP_Bit5:1, SP_Bit6:1, SP_Bit7:1; unsigned char SP_Bit8:1, SP_Bit9:1, SP_Bit10:1, SP_Bit11:1, SP_Bit12:1, SP_Bit13:1, SP_Bit14:1, SP_Bit15:1; }; struct { unsigned char SP_SP0:1, SP_SP1:1, SP_SP2:1, SP_SP3:1, SP_SP4:1, SP_SP5:1, SP_SP6:1, SP_SP7:1; unsigned char SP_SP8:1, SP_SP9:1, SP_SP10:1, SP_SP11:1, SP_SP12:1, SP_SP13:1, SP_SP14:1, SP_SP15:1; }; struct { unsigned char SPL; unsigned char SPH; }; struct { unsigned char SPL_Bit0:1, SPL_Bit1:1, SPL_Bit2:1, SPL_Bit3:1, SPL_Bit4:1, SPL_Bit5:1, SPL_Bit6:1, SPL_Bit7:1; unsigned char SPH_Bit0:1, SPH_Bit1:1, SPH_Bit2:1, SPH_Bit3:1, SPH_Bit4:1, SPH_Bit5:1, SPH_Bit6:1, SPH_Bit7:1; }; struct { unsigned char SPL_SP0:1, SPL_SP1:1, SPL_SP2:1, SPL_SP3:1, SPL_SP4:1, SPL_SP5:1, SPL_SP6:1, SPL_SP7:1; unsigned char SPH_SP8:1, SPH_SP9:1, SPH_SP10:1, SPH_SP11:1, SPH_SP12:1, SPH_SP13:1, SPH_SP14:1, SPH_SP15:1; }; } @ 0x3D;
__io union { unsigned char SPMCSR; struct { unsigned char SPMCSR_Bit0:1, SPMCSR_Bit1:1, SPMCSR_Bit2:1, SPMCSR_Bit3:1, SPMCSR_Bit4:1, SPMCSR_Bit5:1, SPMCSR_Bit6:1, SPMCSR_Bit7:1; }; struct { unsigned char SPMCSR_SPMEN:1, SPMCSR_PGERS:1, SPMCSR_PGWRT:1, SPMCSR_BLBSET:1, SPMCSR_RWWSRE:1, SPMCSR_SIGRD:1, SPMCSR_RWWSB:1, SPMCSR_SPMIE:1; }; } @ 0x37;
__io union { unsigned char MCUCR; struct { unsigned char MCUCR_Bit0:1, MCUCR_Bit1:1, MCUCR_Bit2:1, MCUCR_Bit3:1, MCUCR_Bit4:1, MCUCR_Bit5:1, MCUCR_Bit6:1, MCUCR_Bit7:1; }; struct { unsigned char MCUCR_IVCE:1, MCUCR_IVSEL:1, MCUCR_Dummy2:1, MCUCR_Dummy3:1, MCUCR_PUD:1, MCUCR_Dummy5:1, MCUCR_Dummy6:1, MCUCR_JTD:1; }; } @ 0x35;
__io union { unsigned char MCUSR; struct { unsigned char MCUSR_Bit0:1, MCUSR_Bit1:1, MCUSR_Bit2:1, MCUSR_Bit3:1, MCUSR_Bit4:1, MCUSR_Bit5:1, MCUSR_Bit6:1, MCUSR_Bit7:1; }; struct { unsigned char MCUSR_PORF:1, MCUSR_EXTRF:1, MCUSR_BORF:1, MCUSR_WDRF:1, MCUSR_JTRF:1, MCUSR_Dummy5:1, MCUSR_Dummy6:1, MCUSR_Dummy7:1; }; } @ 0x34;
__io union { unsigned char SMCR; struct { unsigned char SMCR_Bit0:1, SMCR_Bit1:1, SMCR_Bit2:1, SMCR_Bit3:1, SMCR_Bit4:1, SMCR_Bit5:1, SMCR_Bit6:1, SMCR_Bit7:1; }; struct { unsigned char SMCR_SE:1, SMCR_SM0:1, SMCR_SM1:1, SMCR_SM2:1, SMCR_Dummy4:1, SMCR_Dummy5:1, SMCR_Dummy6:1, SMCR_Dummy7:1; }; } @ 0x33;
__io union { unsigned char OCDR; struct { unsigned char OCDR_Bit0:1, OCDR_Bit1:1, OCDR_Bit2:1, OCDR_Bit3:1, OCDR_Bit4:1, OCDR_Bit5:1, OCDR_Bit6:1, OCDR_Bit7:1; }; } @ 0x31;
__io union { unsigned char ACSR; struct { unsigned char ACSR_Bit0:1, ACSR_Bit1:1, ACSR_Bit2:1, ACSR_Bit3:1, ACSR_Bit4:1, ACSR_Bit5:1, ACSR_Bit6:1, ACSR_Bit7:1; }; struct { unsigned char ACSR_ACIS0:1, ACSR_ACIS1:1, ACSR_ACIC:1, ACSR_ACIE:1, ACSR_ACI:1, ACSR_ACO:1, ACSR_ACBG:1, ACSR_ACD:1; }; } @ 0x30;
__io union { unsigned char SPDR; struct { unsigned char SPDR_Bit0:1, SPDR_Bit1:1, SPDR_Bit2:1, SPDR_Bit3:1, SPDR_Bit4:1, SPDR_Bit5:1, SPDR_Bit6:1, SPDR_Bit7:1; }; } @ 0x2E;
__io union { unsigned char SPSR; struct { unsigned char SPSR_Bit0:1, SPSR_Bit1:1, SPSR_Bit2:1, SPSR_Bit3:1, SPSR_Bit4:1, SPSR_Bit5:1, SPSR_Bit6:1, SPSR_Bit7:1; }; struct { unsigned char SPSR_SPI2X0:1, SPSR_Dummy1:1, SPSR_Dummy2:1, SPSR_Dummy3:1, SPSR_Dummy4:1, SPSR_Dummy5:1, SPSR_WCOL0:1, SPSR_SPIF0:1; }; } @ 0x2D;
__io union { unsigned char SPCR; struct { unsigned char SPCR_Bit0:1, SPCR_Bit1:1, SPCR_Bit2:1, SPCR_Bit3:1, SPCR_Bit4:1, SPCR_Bit5:1, SPCR_Bit6:1, SPCR_Bit7:1; }; struct { unsigned char SPCR_SPR00:1, SPCR_SPR01:1, SPCR_CPHA0:1, SPCR_CPOL0:1, SPCR_MSTR0:1, SPCR_DORD0:1, SPCR_SPE0:1, SPCR_SPIE0:1; }; } @ 0x2C;
__io union { unsigned char GPIOR2; struct { unsigned char GPIOR2_Bit0:1, GPIOR2_Bit1:1, GPIOR2_Bit2:1, GPIOR2_Bit3:1, GPIOR2_Bit4:1, GPIOR2_Bit5:1, GPIOR2_Bit6:1, GPIOR2_Bit7:1; }; } @ 0x2B;
__io union { unsigned char GPIOR1; struct { unsigned char GPIOR1_Bit0:1, GPIOR1_Bit1:1, GPIOR1_Bit2:1, GPIOR1_Bit3:1, GPIOR1_Bit4:1, GPIOR1_Bit5:1, GPIOR1_Bit6:1, GPIOR1_Bit7:1; }; } @ 0x2A;
__io union { unsigned char OCR0B; struct { unsigned char OCR0B_Bit0:1, OCR0B_Bit1:1, OCR0B_Bit2:1, OCR0B_Bit3:1, OCR0B_Bit4:1, OCR0B_Bit5:1, OCR0B_Bit6:1, OCR0B_Bit7:1; }; } @ 0x28;
__io union { unsigned char OCR0A; struct { unsigned char OCR0A_Bit0:1, OCR0A_Bit1:1, OCR0A_Bit2:1, OCR0A_Bit3:1, OCR0A_Bit4:1, OCR0A_Bit5:1, OCR0A_Bit6:1, OCR0A_Bit7:1; }; } @ 0x27;
__io union { unsigned char TCNT0; struct { unsigned char TCNT0_Bit0:1, TCNT0_Bit1:1, TCNT0_Bit2:1, TCNT0_Bit3:1, TCNT0_Bit4:1, TCNT0_Bit5:1, TCNT0_Bit6:1, TCNT0_Bit7:1; }; } @ 0x26;
__io union { unsigned char TCCR0B; struct { unsigned char TCCR0B_Bit0:1, TCCR0B_Bit1:1, TCCR0B_Bit2:1, TCCR0B_Bit3:1, TCCR0B_Bit4:1, TCCR0B_Bit5:1, TCCR0B_Bit6:1, TCCR0B_Bit7:1; }; struct { unsigned char TCCR0B_CS00:1, TCCR0B_CS01:1, TCCR0B_CS02:1, TCCR0B_WGM02:1, TCCR0B_Dummy4:1, TCCR0B_Dummy5:1, TCCR0B_FOC0B:1, TCCR0B_FOC0A:1; }; } @ 0x25;
__io union { unsigned char TCCR0A; struct { unsigned char TCCR0A_Bit0:1, TCCR0A_Bit1:1, TCCR0A_Bit2:1, TCCR0A_Bit3:1, TCCR0A_Bit4:1, TCCR0A_Bit5:1, TCCR0A_Bit6:1, TCCR0A_Bit7:1; }; struct { unsigned char TCCR0A_WGM00:1, TCCR0A_WGM01:1, TCCR0A_Dummy2:1, TCCR0A_Dummy3:1, TCCR0A_COM0B0:1, TCCR0A_COM0B1:1, TCCR0A_COM0A0:1, TCCR0A_COM0A1:1; }; } @ 0x24;
__io union { unsigned char GTCCR; struct { unsigned char GTCCR_Bit0:1, GTCCR_Bit1:1, GTCCR_Bit2:1, GTCCR_Bit3:1, GTCCR_Bit4:1, GTCCR_Bit5:1, GTCCR_Bit6:1, GTCCR_Bit7:1; }; struct { unsigned char GTCCR_PSRSYNC:1, GTCCR_PSRASY:1, GTCCR_Dummy2:1, GTCCR_Dummy3:1, GTCCR_Dummy4:1, GTCCR_Dummy5:1, GTCCR_Dummy6:1, GTCCR_TSM:1; }; } @ 0x23;
__io union { unsigned short EEAR; struct { unsigned char EEAR_Bit0:1, EEAR_Bit1:1, EEAR_Bit2:1, EEAR_Bit3:1, EEAR_Bit4:1, EEAR_Bit5:1, EEAR_Bit6:1, EEAR_Bit7:1; unsigned char EEAR_Bit8:1, EEAR_Bit9:1, EEAR_Bit10:1, EEAR_Bit11:1, EEAR_Bit12:1, EEAR_Bit13:1, EEAR_Bit14:1, EEAR_Bit15:1; }; struct { unsigned char EEARL; unsigned char EEARH; }; struct { unsigned char EEARL_Bit0:1, EEARL_Bit1:1, EEARL_Bit2:1, EEARL_Bit3:1, EEARL_Bit4:1, EEARL_Bit5:1, EEARL_Bit6:1, EEARL_Bit7:1; unsigned char EEARH_Bit0:1, EEARH_Bit1:1, EEARH_Bit2:1, EEARH_Bit3:1, EEARH_Bit4:1, EEARH_Bit5:1, EEARH_Bit6:1, EEARH_Bit7:1; }; } @ 0x21;
__io union { unsigned char EEDR; struct { unsigned char EEDR_Bit0:1, EEDR_Bit1:1, EEDR_Bit2:1, EEDR_Bit3:1, EEDR_Bit4:1, EEDR_Bit5:1, EEDR_Bit6:1, EEDR_Bit7:1; }; } @ 0x20;
__io union { unsigned char EECR; struct { unsigned char EECR_Bit0:1, EECR_Bit1:1, EECR_Bit2:1, EECR_Bit3:1, EECR_Bit4:1, EECR_Bit5:1, EECR_Bit6:1, EECR_Bit7:1; }; struct { unsigned char EECR_EERE:1, EECR_EEPE:1, EECR_EEMPE:1, EECR_EERIE:1, EECR_EEPM0:1, EECR_EEPM1:1, EECR_Dummy6:1, EECR_Dummy7:1; }; } @ 0x1F;
__io union { unsigned char GPIOR0; struct { unsigned char GPIOR0_Bit0:1, GPIOR0_Bit1:1, GPIOR0_Bit2:1, GPIOR0_Bit3:1, GPIOR0_Bit4:1, GPIOR0_Bit5:1, GPIOR0_Bit6:1, GPIOR0_Bit7:1; }; } @ 0x1E;
__io union { unsigned char EIMSK; struct { unsigned char EIMSK_Bit0:1, EIMSK_Bit1:1, EIMSK_Bit2:1, EIMSK_Bit3:1, EIMSK_Bit4:1, EIMSK_Bit5:1, EIMSK_Bit6:1, EIMSK_Bit7:1; }; struct { unsigned char EIMSK_INT0:1, EIMSK_INT1:1, EIMSK_INT2:1, EIMSK_Dummy3:1, EIMSK_Dummy4:1, EIMSK_Dummy5:1, EIMSK_Dummy6:1, EIMSK_Dummy7:1; }; } @ 0x1D;
__io union { unsigned char EIFR; struct { unsigned char EIFR_Bit0:1, EIFR_Bit1:1, EIFR_Bit2:1, EIFR_Bit3:1, EIFR_Bit4:1, EIFR_Bit5:1, EIFR_Bit6:1, EIFR_Bit7:1; }; struct { unsigned char EIFR_INTF0:1, EIFR_INTF1:1, EIFR_INTF2:1, EIFR_Dummy3:1, EIFR_Dummy4:1, EIFR_Dummy5:1, EIFR_Dummy6:1, EIFR_Dummy7:1; }; } @ 0x1C;
__io union { unsigned char PCIFR; struct { unsigned char PCIFR_Bit0:1, PCIFR_Bit1:1, PCIFR_Bit2:1, PCIFR_Bit3:1, PCIFR_Bit4:1, PCIFR_Bit5:1, PCIFR_Bit6:1, PCIFR_Bit7:1; }; struct { unsigned char PCIFR_PCIF0:1, PCIFR_PCIF1:1, PCIFR_PCIF2:1, PCIFR_PCIF3:1, PCIFR_Dummy4:1, PCIFR_Dummy5:1, PCIFR_Dummy6:1, PCIFR_Dummy7:1; }; } @ 0x1B;
__io union { unsigned char TIFR2; struct { unsigned char TIFR2_Bit0:1, TIFR2_Bit1:1, TIFR2_Bit2:1, TIFR2_Bit3:1, TIFR2_Bit4:1, TIFR2_Bit5:1, TIFR2_Bit6:1, TIFR2_Bit7:1; }; struct { unsigned char TIFR2_TOV2:1, TIFR2_OCF2A:1, TIFR2_OCF2b:1, TIFR2_Dummy3:1, TIFR2_Dummy4:1, TIFR2_Dummy5:1, TIFR2_Dummy6:1, TIFR2_Dummy7:1; }; } @ 0x17;
__io union { unsigned char TIFR1; struct { unsigned char TIFR1_Bit0:1, TIFR1_Bit1:1, TIFR1_Bit2:1, TIFR1_Bit3:1, TIFR1_Bit4:1, TIFR1_Bit5:1, TIFR1_Bit6:1, TIFR1_Bit7:1; }; struct { unsigned char TIFR1_TOV1:1, TIFR1_OCF1A:1, TIFR1_OCF1B:1, TIFR1_Dummy3:1, TIFR1_Dummy4:1, TIFR1_ICF1:1, TIFR1_Dummy6:1, TIFR1_Dummy7:1; }; } @ 0x16;
__io union { unsigned char TIFR0; struct { unsigned char TIFR0_Bit0:1, TIFR0_Bit1:1, TIFR0_Bit2:1, TIFR0_Bit3:1, TIFR0_Bit4:1, TIFR0_Bit5:1, TIFR0_Bit6:1, TIFR0_Bit7:1; }; struct { unsigned char TIFR0_TOV0:1, TIFR0_OCF0A:1, TIFR0_OCF0B:1, TIFR0_Dummy3:1, TIFR0_Dummy4:1, TIFR0_Dummy5:1, TIFR0_Dummy6:1, TIFR0_Dummy7:1; }; } @ 0x15;
__io union { unsigned char PORTD; struct { unsigned char PORTD_Bit0:1, PORTD_Bit1:1, PORTD_Bit2:1, PORTD_Bit3:1, PORTD_Bit4:1, PORTD_Bit5:1, PORTD_Bit6:1, PORTD_Bit7:1; }; struct { unsigned char PORTD_PORTD0:1, PORTD_PORTD1:1, PORTD_PORTD2:1, PORTD_PORTD3:1, PORTD_PORTD4:1, PORTD_PORTD5:1, PORTD_PORTD6:1, PORTD_PORTD7:1; }; } @ 0x0B;
__io union { unsigned char DDRD; struct { unsigned char DDRD_Bit0:1, DDRD_Bit1:1, DDRD_Bit2:1, DDRD_Bit3:1, DDRD_Bit4:1, DDRD_Bit5:1, DDRD_Bit6:1, DDRD_Bit7:1; }; struct { unsigned char DDRD_DDD0:1, DDRD_DDD1:1, DDRD_DDD2:1, DDRD_DDD3:1, DDRD_DDD4:1, DDRD_DDD5:1, DDRD_DDD6:1, DDRD_DDD7:1; }; } @ 0x0A;
__io union { unsigned char PIND; struct { unsigned char PIND_Bit0:1, PIND_Bit1:1, PIND_Bit2:1, PIND_Bit3:1, PIND_Bit4:1, PIND_Bit5:1, PIND_Bit6:1, PIND_Bit7:1; }; struct { unsigned char PIND_PIND0:1, PIND_PIND1:1, PIND_PIND2:1, PIND_PIND3:1, PIND_PIND4:1, PIND_PIND5:1, PIND_PIND6:1, PIND_PIND7:1; }; } @ 0x09;
__io union { unsigned char PORTC; struct { unsigned char PORTC_Bit0:1, PORTC_Bit1:1, PORTC_Bit2:1, PORTC_Bit3:1, PORTC_Bit4:1, PORTC_Bit5:1, PORTC_Bit6:1, PORTC_Bit7:1; }; struct { unsigned char PORTC_PORTC0:1, PORTC_PORTC1:1, PORTC_PORTC2:1, PORTC_PORTC3:1, PORTC_PORTC4:1, PORTC_PORTC5:1, PORTC_PORTC6:1, PORTC_PORTC7:1; }; } @ 0x08;
__io union { unsigned char DDRC; struct { unsigned char DDRC_Bit0:1, DDRC_Bit1:1, DDRC_Bit2:1, DDRC_Bit3:1, DDRC_Bit4:1, DDRC_Bit5:1, DDRC_Bit6:1, DDRC_Bit7:1; }; struct { unsigned char DDRC_DDC0:1, DDRC_DDC1:1, DDRC_DDC2:1, DDRC_DDC3:1, DDRC_DDC4:1, DDRC_DDC5:1, DDRC_DDC6:1, DDRC_DDC7:1; }; } @ 0x07;
__io union { unsigned char PINC; struct { unsigned char PINC_Bit0:1, PINC_Bit1:1, PINC_Bit2:1, PINC_Bit3:1, PINC_Bit4:1, PINC_Bit5:1, PINC_Bit6:1, PINC_Bit7:1; }; struct { unsigned char PINC_PINC0:1, PINC_PINC1:1, PINC_PINC2:1, PINC_PINC3:1, PINC_PINC4:1, PINC_PINC5:1, PINC_PINC6:1, PINC_PINC7:1; }; } @ 0x06;
__io union { unsigned char PORTB; struct { unsigned char PORTB_Bit0:1, PORTB_Bit1:1, PORTB_Bit2:1, PORTB_Bit3:1, PORTB_Bit4:1, PORTB_Bit5:1, PORTB_Bit6:1, PORTB_Bit7:1; }; struct { unsigned char PORTB_PORTB0:1, PORTB_PORTB1:1, PORTB_PORTB2:1, PORTB_PORTB3:1, PORTB_PORTB4:1, PORTB_PORTB5:1, PORTB_PORTB6:1, PORTB_PORTB7:1; }; } @ 0x05;
__io union { unsigned char DDRB; struct { unsigned char DDRB_Bit0:1, DDRB_Bit1:1, DDRB_Bit2:1, DDRB_Bit3:1, DDRB_Bit4:1, DDRB_Bit5:1, DDRB_Bit6:1, DDRB_Bit7:1; }; struct { unsigned char DDRB_DDB0:1, DDRB_DDB1:1, DDRB_DDB2:1, DDRB_DDB3:1, DDRB_DDB4:1, DDRB_DDB5:1, DDRB_DDB6:1, DDRB_DDB7:1; }; } @ 0x04;
__io union { unsigned char PINB; struct { unsigned char PINB_Bit0:1, PINB_Bit1:1, PINB_Bit2:1, PINB_Bit3:1, PINB_Bit4:1, PINB_Bit5:1, PINB_Bit6:1, PINB_Bit7:1; }; struct { unsigned char PINB_PINB0:1, PINB_PINB1:1, PINB_PINB2:1, PINB_PINB3:1, PINB_PINB4:1, PINB_PINB5:1, PINB_PINB6:1, PINB_PINB7:1; }; } @ 0x03;
__io union { unsigned char PORTA; struct { unsigned char PORTA_Bit0:1, PORTA_Bit1:1, PORTA_Bit2:1, PORTA_Bit3:1, PORTA_Bit4:1, PORTA_Bit5:1, PORTA_Bit6:1, PORTA_Bit7:1; }; struct { unsigned char PORTA_PORTA0:1, PORTA_PORTA1:1, PORTA_PORTA2:1, PORTA_PORTA3:1, PORTA_PORTA4:1, PORTA_PORTA5:1, PORTA_PORTA6:1, PORTA_PORTA7:1; }; } @ 0x02;
__io union { unsigned char DDRA; struct { unsigned char DDRA_Bit0:1, DDRA_Bit1:1, DDRA_Bit2:1, DDRA_Bit3:1, DDRA_Bit4:1, DDRA_Bit5:1, DDRA_Bit6:1, DDRA_Bit7:1; }; struct { unsigned char DDRA_DDA0:1, DDRA_DDA1:1, DDRA_DDA2:1, DDRA_DDA3:1, DDRA_DDA4:1, DDRA_DDA5:1, DDRA_DDA6:1, DDRA_DDA7:1; }; } @ 0x01;
__io union { unsigned char PINA; struct { unsigned char PINA_Bit0:1, PINA_Bit1:1, PINA_Bit2:1, PINA_Bit3:1, PINA_Bit4:1, PINA_Bit5:1, PINA_Bit6:1, PINA_Bit7:1; }; struct { unsigned char PINA_PINA0:1, PINA_PINA1:1, PINA_PINA2:1, PINA_PINA3:1, PINA_PINA4:1, PINA_PINA5:1, PINA_PINA6:1, PINA_PINA7:1; }; } @ 0x00;





/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#line 239 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"










/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/

  /* UCSR1C */
#line 262 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

  /* UCSR1B */
#line 272 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

  /* UCSR1A */
#line 282 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0C */
#line 292 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0B */
#line 302 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* UCSR0A */
#line 312 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWAM */
#line 321 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWCR */
#line 330 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWAR */
#line 340 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TWSR */
#line 349 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ASSR */
#line 358 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR2B */
#line 366 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR2A */
#line 374 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR1C */



/* TCCR1B */
#line 387 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR1A */
#line 395 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DIDR1 */



/* DIDR0 */
#line 409 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ADMUX */
#line 419 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* ADCSRB */





/* ADCSRA */
#line 435 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK3 */
#line 445 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TIMSK2 */




/* TIMSK1 */





/* TIMSK0 */




/* PCMSK2 */
#line 471 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK1 */
#line 481 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCMSK0 */
#line 491 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* EICRA */
#line 499 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PCICR */





/* PRR */
#line 514 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* CLKPR */






/* WDTCSR */
#line 531 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SREG */
/*
#define I 7
#define T 6
#define H 5
#define S 4
#define V 3
#define N 2
#define Z 1
#define C 0
*/

  /* SP */
#line 561 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SPMCSR */
#line 571 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* MCUCR */





/* MCUSR */






/* SMCR */





/* ACSR */
#line 600 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* SPSR */




/* SPCR */
#line 615 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR0B */
#line 623 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* TCCR0A */
#line 631 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* GTCCR */




  /* EECR */
#line 644 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"


/* EIMSK */




/* EIFR */




/* PCIFR */





/* TIFR2 */




/* TIFR1 */





/* TIFR0 */




/* PORTD */
#line 687 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PD */
#line 697 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRD */
#line 707 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PIND */
#line 717 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTC */
#line 727 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PC */
#line 737 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRC */
#line 747 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINC */
#line 757 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTB */
#line 767 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PB */
#line 777 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRB */
#line 787 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINB */
#line 797 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PORTA */
#line 807 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PA */
#line 817 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* DDRA */
#line 827 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* PINA */
#line 837 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"



/* Pointer definition */
#line 847 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\iom644p.h"

/* Constants */





#line 172 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\ioavr.h"
#line 2 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdio.h"
/*                      - STDIO.H -

   Subset of ANSI standard I/O function declarations.

   $Revision: 1.1 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include


#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdarg.h"
/*                      - STDARG.H -
   The ANSI macros for reading variable argument lists (...).

   $Revision: 2093 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include


#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"
/*                      - SYSMAC.H -

   Defines system macros to maintain source compatibility
   with different IAR compilers.

   $Revision: 2095 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include










































#line 65 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"

#line 73 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"

#line 84 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\sysmac.h"








/* Macro for frmwri and frmrd */


/* Typedefs put here to appear only once */
typedef unsigned int    size_t;
typedef signed int ptrdiff_t;

#line 17 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdarg.h"




typedef void *va_list[1];

__intrinsic void __va_start(va_list);




/*=====================================*/
/*  These targets has char pushed as   */
/*  word on stack.                     */
/*  Stack grows in negativ direction.  */
/*  (New type of code-generators)      */
/* - - - - - - - - - - - - - - - - - - */
/*     ICC78000 version 4.xx           */
/*     M32C version 3.xx               */
/*=====================================*/
#line 46 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdarg.h"

#line 54 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdarg.h"



#line 18 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdio.h"













 int  puts(const char *);
 int  putchar(int);
 int  getchar(void);
 int  sprintf(char *,const char *,...);
 int  vsprintf(char *,const char *,va_list);
 int  printf(const char *,...);
 int  vprintf(const char *,va_list);
 int  scanf(const char *,...);
 int  sscanf(const char *, const char *,...);
 char *gets(char *);






#line 3 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\usart.h"
//usart.h

//常量定义

//#define F_CPU            4000000  //晶振频率4.0MHz




//#define UPE 2    //M128





//宏定义


//#define PARITY_ERROR (1<<UPE)    //M128




// USART Receiver buffer
// 全局变量,会在中断服务程序中被修改，须加volatile限定，不要就会出错啦






// USART Transmitter buffer


// 函数声明
char get_c(void);
void put_c(unsigned char c);
void put_s(unsigned char *ptr);
void init_USART0(void);
#line 4 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
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

#line 5 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
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
#line 6 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.h"



unsigned char decode_id(void);
unsigned char decode_SCS(void);
void reception_buffer_clear(unsigned char temp);
unsigned char is_gateway_busy(void);
void application_decode_short(void);    // add by alan 20090401
void application_decode_long(void);
void calibration_decode(void);
void scs_calibration(void);
#line 7 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\stdlib.h"
/*                      - STDLIB.H -

   The ANSI-defined 'standard' functions.

   $Revision: 2093 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include








typedef struct
{
  int   quot;
  int   rem;
} div_t;

typedef struct
{
  long int      quot;
  long int      rem;
} ldiv_t;























__intrinsic  void *malloc(size_t);

__intrinsic  void free(void *);

__intrinsic  void exit(int);

__intrinsic  void *calloc(size_t, size_t);

__intrinsic  void *realloc(void *, size_t);

__intrinsic  int  atoi(const char *);

__intrinsic  long atol(const char *);

__intrinsic  double atof(const char *);

__intrinsic  double strtod(const char *, char **);

__intrinsic  long int strtol(const char *, char **, int);

__intrinsic  unsigned long int strtoul(const char *, char **,
                                                       int);

__intrinsic  int rand(void);

__intrinsic  void srand(unsigned int);

__intrinsic  void abort(void);

__intrinsic  int abs(int);

__intrinsic  div_t div(int, int);

__intrinsic  long int labs(long int);

__intrinsic  ldiv_t ldiv(long int, long int);

__intrinsic  void *bsearch(const void *, const void *,
                                           size_t, size_t,
                                           int (*)(const void *,const void *));

__intrinsic  void qsort(void *, size_t, size_t,
                                        int (*)(const void *, const void *));







#line 8 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.h"
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

#line 5 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\global_variable.h"
// main
extern unsigned char g_timer2_flag;
extern unsigned char g_temp;
extern volatile void global_variable_initial();
extern volatile unsigned char g_configurator[5];

extern volatile struct struct_scs_frame scs_frame[10];
extern __eeprom struct SKO_Configuration ee_KO_conf;
//extern __eeprom struct SKO_Configuration ee_PnG_KO_conf;
extern volatile struct SConfigurators Configurators;
extern volatile struct SKO_Configuration KO_conf;
//extern struct SKO_Configuration temp_KO_conf;
extern __eeprom volatile unsigned char ee_ID[9];
extern __eeprom unsigned char ee_pre_ID[4];
extern volatile struct SState state;
extern volatile struct Sframe_extended_type frame_extended_type;
extern __eeprom struct SConfigurators ee_configurators;
extern volatile unsigned char g_reception_buffer[17];
extern volatile unsigned char g_asc_reception_buffer[8];
extern volatile unsigned char g_short_buffer[8];
extern volatile unsigned char g_asc_short_buffer[4];
extern volatile struct Sproduct_info product_info;
extern volatile struct SIR_reception IR_reception;
extern volatile struct Sflag_timer flag_timer;
extern volatile struct SDll DLL;
extern volatile struct STimeDelay Time_delay;
extern volatile struct PIR pir;
extern volatile unsigned int pir_total;
extern volatile unsigned char us_result;
extern volatile unsigned char us_total;
extern volatile unsigned int motion_total;
extern volatile unsigned char US_detection_en;
extern volatile unsigned long int modality0_delay_ms;
extern volatile unsigned char g_key_value;
extern volatile unsigned char g_virtual_basci_configuration_flag;
extern __eeprom struct S_product_information ee_product_information;
extern const int daylight_motion[];
extern const int daylight[];
extern const int motion[];
extern volatile struct Ukey_result key_result;
extern __eeprom unsigned char g_ns_index;
extern volatile unsigned char g_ir_reception[];
extern volatile struct s_flags flags;
extern volatile unsigned char PIR_detection_en;   // add by alan 20090409

extern __flash struct SKO_Configuration flash_KO_168;
extern __flash struct SKO_Configuration flash_KO_166;
extern __flash struct SKO_Configuration flash_KO_119;
extern __flash struct SKO_Configuration flash_KO_128;
extern __flash struct SKO_Configuration flash_KO_165;
extern __flash struct SKO_Configuration flash_KO_515;

extern volatile char tx1_buffer[14];
extern volatile unsigned char tx1_wr_index,tx1_rd_index,tx1_counter;

extern struct S_product_information product_information;
extern struct S_product_information temp_product_information;
extern volatile unsigned char KO[];
extern struct s_parameters parameters;

extern const unsigned char flash_KO[];

extern struct s_temp_variable temp_variable;
extern struct s_flags_muti_step flags_muti_step;

extern __eeprom struct s_ee_flags ee_flags;
extern __eeprom unsigned char ee_KO_last[];
extern __eeprom unsigned char ee_KO[];
extern __eeprom struct s_parameter ee_parameter;


extern __eeprom unsigned char ee_scenario_index;
//extern struct S_ir_scenario ir_scenario __attribute__((section(".eeprom")));
//extern struct s_ns ee_ns __attribute__((section(".eeprom")));
extern __eeprom struct S_test only_test;

extern __eeprom struct s_scenario  ee_scenario[16];
extern __eeprom struct S_product_information ee_product_information;
extern __eeprom struct s_ee_variable ee_variable;

// add by alan begin

extern __eeprom unsigned int eep_setpoint[4];
extern __eeprom unsigned int eep_factor;
extern __eeprom unsigned char eep_M2_hour;	
extern __eeprom unsigned char eep_M2_min;	
extern __eeprom unsigned char eep_M2_sec;
extern __eeprom unsigned char eep_M2_sens;
extern  unsigned long int   M2_timer;
extern  unsigned long int   M2_timer_count;
extern  unsigned char M2_type;
extern 	unsigned char  motion_resutl;
volatile  	extern unsigned long int Delay_Time_set;
extern 	unsigned int  set_point;
extern 	unsigned char during_on_cnt;
extern 	unsigned char during_off_cnt;
extern 	unsigned char Walk_Through_flag;
extern 	unsigned char First_detection_enable;
extern	struct	SSCS_received SCS_received;
extern	struct 	SSensor_mode Sensor_mode;

// add by alan end
#line 9 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
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
#line 10 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs_next.h"


void send_frame_pp(char *data, unsigned int ms);
void send_frame_pp_broad(char *data, unsigned int ms);
void send_frame_pp_ext(char *data, unsigned int ms);
void send_frame_pp_ext_broad(char *data, unsigned int ms);
void org_ext_broad(char *data, unsigned int ms);
void ext_ans_frame(unsigned char value);
void parameter_set(unsigned char data);
void id_frame(void);
void KO_answer_frame(void);
void diagnostic_frame(void);
void configuration_answer_frame(unsigned char value);
void configuration_receive_answer_frame(void);
void png_diagnostic(void);
void configuration_setting_frame(unsigned char value);
void KO_answer_frame(void);
void parameter_answer_frame(void);
void frame_buffer_clear(void);
void parameter_request_error_frame(void);
void not_allowed_response(unsigned char ko_channel);
void parameter_all_answer(void);
void parameter_specified_index_answer(void);
void send_aux_frame(unsigned char argument,unsigned char ns,unsigned char scenario_index);
void send_group_pnl_frame(unsigned char send_type,unsigned char GR, unsigned char cmd);
void ko_answer_all(void);
void address_answer_frame(void);
void address_setting_error_frame(void);
unsigned char dimmer_convert(unsigned char data);
void send_group_frame(unsigned char argument);
unsigned int write_parameter_scenario(void);
void parameter_setting_error_answer(unsigned int value);
void KO_setting_procedure(void);
void configuration_procedure(void);
void aux_procedure(void);
void scenario_remove(unsigned char number);
void KO_setting_error_frame(unsigned char send_type,unsigned char channel);
#line 11 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "C:\\Program Files\\IAR Systems\\Embedded Workbench 5.0 Evaluation\\avr\\INC\\CLIB\\string.h"
/*                       - STRING.H -

   The ANSI 'string' function declarations.

   $Revision: 2093 $

   Copyright 1986 - 1999 IAR Systems. All rights reserved.
*/





  #pragma system_include


















__intrinsic  void *memcpy(void *, const void *, size_t);

__intrinsic  void *memmove(void *, const void *, size_t);

__intrinsic  void *memchr(const void *, int, size_t);

__intrinsic  void *memset(void *, int, size_t);

__intrinsic  int memcmp(const void *, const void *, size_t);

__intrinsic  char *strchr(const char *, int);

__intrinsic  int strcmp(const char *, const char *);

__intrinsic  int strncmp(const char *, const char *, size_t);

__intrinsic  int strcoll(const char *, const char *);

__intrinsic  size_t strlen(const char *);

__intrinsic  size_t strcspn(const char *, const char *);

__intrinsic  size_t strspn(const char *, const char *);

__intrinsic  char *strpbrk(const char *, const char *);

__intrinsic  char *strrchr(const char *, int);

__intrinsic  char *strstr(const char *, const char *);

__intrinsic  char *strcat(char *, const char *);

__intrinsic  char *strncat(char *, const char *, size_t);

__intrinsic  char *strcpy(char *, const char *);

__intrinsic  char *strncpy(char *, const char *, size_t);

__intrinsic  char *strerror(int);

__intrinsic  char *strtok(char *, const char *);

__intrinsic  size_t strxfrm(char *, const char *, size_t);







#line 14 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\configuration.h"



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
#line 15 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
#line 1 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"




// set point level




// function state define





// detection scheme





// timeout warning mode define





// function mode define






// time delay define
#line 42 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"




// define the configurators.T
#line 57 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"

// define the sensor status
#line 69 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\function_service.h"
 /*
SetBit(KO_conf.status[3],Status_Retrigger);
SetBit(KO_conf.status[3],Status_Walk_through);
SetBit(KO_conf.status[3],Status_Maintain);
SetBit(KO_conf.status[3],Status_Detection);
ClrBit(KO_conf.status[3],Status_Retrigger);
ClrBit(KO_conf.status[3],Status_Walk_through);
ClrBit(KO_conf.status[3],Status_Maintain);
ClrBit(KO_conf.status[3],Status_Detection);

KO_conf.status[2] = Status_ON;
KO_conf.status[2] = Status_OFF;
KO_conf.status[2] = Status_OFF;
KO_conf.status[2] = Status_ON;
 */

/*
 ************************************************************************************************************
 ************************************************************************************************************
 */


//void _modality_0(void);
//void _modality_1(void);
//void _modality_2(void);
//void _modality_3(void);
//void _modality_4(void);
//void daylight_service(void);
//void regulation_diming(void);
//void frame_M2_answer( unsigned char type);
//unsigned char decode_frame_SCS(void);
void frame_presence(unsigned char arg);
void frame_dimming(char type,char cmd,char func0, char func1,char func2 ,char func3,char func4);
void check_modality_frame(void);
void Delay_Alert(void);
void Stop_allTimer(void);
void Start_Time_Delay(void);
void Call_detect_delay(void);
void WT_20s_detect(void);
void Check_SCS_received(void);
void Check_frame_received(void);
void GS_presence_send(void);
void frame_ON_send(void);
void frame_OFF_send(void);
void framesend_takeline(void);
void frame_on_off( unsigned char command );
void occupancy_detect(void);
void _Initial_state(void);
void _Maintain_state(void);
void _ReTrigger_State(void);
void _Standby_state(void);
void Function_LM_GR(void);
void Function_KO119(char addrestype);
void Function_KO128(void);
void Function_KO166(char addrestype, char detectype, char LightReg);
void Function_KO168(char addrestype, char FuncMod, char LightReg);
void function_service_init(void);
void function_service(void);

#line 16 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"

void reception_buffer_clear(unsigned char temp)
{


	unsigned char i;
		
	for(i=0;i<8;i++)
	{
		g_short_buffer[i] = 0;
	}

	for(i=0;i<4;i++)
	{
		g_asc_short_buffer[i] = 0;
	}

	for(i=0;i<8;i++)
	{
		g_asc_reception_buffer[i] = 0;
	}

	for(i=0;i<17;i++)
	{
		g_reception_buffer[i] = 0;
	}
	
#line 54 "D:\\avr\\Uart_Interrupt\\LM_Universal\\LM_IAR_V5.0\\Alan\\decode_scs.c"
}

unsigned char decode_id(void)
{
	unsigned char i;
	unsigned char buffer[3];

	//static unsigned char ID_buffer[8];
	volatile unsigned char current = 0xFF;

	for(i=0;i<10;i++)
	{
		if(scs_frame[i].finished)
		{
			current = i;
			break;
		}
	}

	if(scs_frame[current].finished && current != 0xFF)
	{
		switch(StrToChar(&scs_frame[current].byte[1]))
		{
			case 0x18:
				for(i=0;i<16;i++)
				{
					g_reception_buffer[i] = scs_frame[current].byte[i+3];
				}
				for(i=0;i<8;i++)
				{
					buffer[0] = g_reception_buffer[i * 2];
					buffer[1] = g_reception_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_reception_buffer[i] = StrToChar(buffer);
				}

				switch(g_asc_reception_buffer[0])
				{
					case 0xD0:
            if(g_reception_buffer[6] == '0' || g_reception_buffer[6] == 'F')
						  id_frame();
					break;

					default:break;
				}
			break;

			default:
				scs_frame[current].finished = 0;	
        if(state.id_setting == 1)
	      {
		      if( Time_delay.timer_flex.time_out == 1 )
		      {
			      state.id_setting = 0;
			      send_frame_pp_ext_broad("D000010E00000000",50);
			      asm("nop");
		      }
	      }
			return 1;
		}
	}
	scs_frame[current].finished = 0;
	return 0;
}

unsigned char decode_SCS(void)
{
	volatile unsigned char current = 0xFF;
	unsigned char i;
	unsigned char buffer[3];
	char buffer_tx[17];			// 20090216
	//unsigned char current;

	for(i=0;i<10;i++)
	{
		if(scs_frame[i].finished)
		{
			current = i;
			break;
		}
	}

	if(scs_frame[current].finished && current != 0xFF)
	{
		switch(StrToChar(&scs_frame[current].byte[1]))
		{
    	case 0x00:
      break;

    	case 0x01:
      break;

    	case 0x07:
      break;

			case 0x17:
				for(i=0;i<8;i++)
				{
					g_short_buffer[i] = scs_frame[current].byte[i+3];
				}
				
				for(i=0;i<4;i++)
				{	
					buffer[0] = g_short_buffer[i * 2];
					buffer[1] = g_short_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_short_buffer[i] = StrToChar(buffer);
				}

				application_decode_short();         //add by alan 20090412
				
				switch(g_asc_short_buffer[0])
				{
					case 0xB0:
						if(g_short_buffer[4] == '9')
						{
							if(g_short_buffer[7] == '0')
							{
								flags.app_disable = 1;
							}
							else if(g_short_buffer[7] == 'F')
							{
								flags.app_disable = 0;
							}
						}
					break;
					
					case 0xB1:
						if(g_short_buffer[4] == '9')
						{
							if(g_asc_short_buffer[1] != 0)
							{
								state.main_state = 0;
							}
						}
					break;
					
					case 0xB2:
					break;
					
					case 0xB4:
					break;
					
					default:break;
				}
				
        if(g_short_buffer[4] == '9')  //Auxiliary system
        {
          if(g_short_buffer[0] == 'B')
          {
            switch(g_short_buffer[5])
            {
              case '0':  //start of programming
              break;

              case '1':  //end of proframming
              break;

              case '2':  //begin scenario modification
              break;

            case '3':  //activation of a scenario
              break;

            case '4':  // turn off all managing scenario
              break;

            case '5':  //increase
              break;

            case '6':  //decrease
              break;

            case '7':  //stop increase/decrease
              break;

            default:break;
            }
          }
        }
			break;

			case 0x18:
				for(i=0;i<16;i++)
				{
					g_reception_buffer[i] = scs_frame[current].byte[i+3];
				}

				for(i=0;i<8;i++)
				{
					buffer[0] = g_reception_buffer[i * 2];
					buffer[1] = g_reception_buffer[i * 2 + 1];
					buffer[2] = 0;
					g_asc_reception_buffer[i] = StrToChar(buffer);
				}
				
				application_decode_long();
				
				if(g_reception_buffer[5] == '1')
				{
					switch(g_asc_reception_buffer[0])
					{
						case 0xD0:
        	    if(g_reception_buffer[6] == '0' || g_reception_buffer[6] == 'F')
							{
							  	id_frame();
							}
						break;
        	
						case 0xD1:
							scs_calibration();
							if((KO_conf.AddressType != 0) || (KO_conf.DesAdd != g_asc_reception_buffer[1]))
							{
								//asm("nop");							
								//reception_buffer_clear(0);
							}
							else
							{
								switch (g_reception_buffer[7])
								{
									case '2':
										configuration_setting_frame(g_asc_reception_buffer[4]);
									break;
        	
									case '3':
										configuration_answer_frame(g_asc_reception_buffer[4]);
									break;
        	
									default:break;
								}
							}
						break;
        	
						case 0xD2:
							
							// add by alan 0415 begin
							if(g_reception_buffer[7] == '4')		//answer	D2 A|Pl 0|1 3|4 0|D 0|X 0|0 0|0
							{
								if(g_asc_reception_buffer[4] == 0x0D)
								{
									if(((KO_conf.AddressType ==2)&&(KO_conf.Reference == g_asc_reception_buffer[1]))
										 	||((KO_conf.AddressType ==0)&&(KO_conf.DesAdd == g_asc_reception_buffer[1])))
									{
										//reyno 0622
										if(Time_delay.regulation.time_out == 1)
										{
											DLL.start_regulation = 0;
											(KO_conf . status[0]&=(~(1<<6)));
										}
									  if((g_asc_reception_buffer[5] ==0x00)||(g_asc_reception_buffer[5] ==0x01))	
										{
										  	//SCS_received.P2P_actuator_flag = 1; //reyno
												//SCS_received.P2P_dimmer_flag = 0;
												//reyno 0612////////////////////////////////////
												if(g_asc_reception_buffer[5] == 0x00)
												{
													Sensor_mode.power_on_flag = 1;
													KO_conf.status[1] = 100;		//reyno 0616
												}
												else
												{
													Sensor_mode.power_on_flag = 0;
													KO_conf.status[1] = 0;		//reyno 0616
												}
												///////////////////////////////////////////////
										}
										if(g_asc_reception_buffer[5] == 0x0D)							
										{
											//reyno 0612/////////////////////////////////////
											Sensor_mode.power_on_flag = 1;
											//KO_conf.status[1] = Status_ON;		//reyno 0616
											KO_conf.status[1] = g_asc_reception_buffer[6];
											/////////////////////////////////////////////////
										  SCS_received.P2P_dimmer_flag = 1;
											SCS_received.P2P_actuator_flag = 0;
											//if(g_asc_reception_buffer[6] == 0x01)	
											//		SCS_received.P2P_dimmer_zero = 1;	// dimmer value is zero
											//if(g_asc_reception_buffer[6] == 0x64)	
											//		SCS_received.P2P_dimmer_full = 1;	// dimmer value is full
										}
									}
								}
							}
							// add by alan 0415 end	
							
							switch (g_reception_buffer[7])
							{
							  case '2':
									scs_calibration();
								  configuration_setting_frame(g_asc_reception_buffer[4]);
							  break;
        	
							  case '3':
								  configuration_answer_frame(g_asc_reception_buffer[4]);
							  break;
							
							  case '4':
								  configuration_receive_answer_frame();
							  break;
        	
							  default:break;
							}
						break;
        	
						case 0xD5:
							switch(g_reception_buffer[4])
							{
								case '0':			//group
									if((KO_conf.GR != g_asc_reception_buffer[1]) || ((KO_conf.AddressType != 2)))
									{
										//reception_buffer_clear(0);
									}
									else
									{
										switch (g_reception_buffer[7])
										{
											case '2':
												configuration_setting_frame(g_asc_reception_buffer[4]);
											break;
        	
											case '3':
												configuration_answer_frame(g_asc_reception_buffer[4]);
											break;
        							
											case '4':
												// add by alan begin
												if((g_asc_reception_buffer[4] ==0x10)&&(KO_conf.TypeLoop ==1))      // in OPEN loop       // D5 GR 01 34 10 0X XX XX		
												{																																		// lux answer send by GS daylight sensor
													if(g_asc_reception_buffer[1] == KO_conf.GR)
													{
														DLL.open_lightlux =  g_asc_reception_buffer[5]&0x0F;
														DLL.open_lightlux = DLL.open_lightlux<<8;
														DLL.open_lightlux +=  g_asc_reception_buffer[6];
														DLL.open_lightlux = DLL.open_lightlux<<8;
														DLL.open_lightlux +=  g_asc_reception_buffer[7];
														SCS_received.Daylight_lux = 1;
													}
												}
												// add by alan end
											break;
											
											default:break;
										}
									}
									
									// Add by alan begin used for modality setting
                  if((g_reception_buffer[7] == '2')||((g_reception_buffer[7] == '3')))    //  set or request
									{
										if(g_asc_reception_buffer[4] == 0x10)       	// D5 LOC 01 43 10 0X XX XX
								 		{
								 			M2_type = '0';								//used in modality for sending frame to answer the daylight level
											frame_M2_answer('0');
                      if((g_asc_reception_buffer[1] ==0x00)&&(g_asc_reception_buffer[2] ==0xEE))	// in frame request, A|PL != 0x00	这个帧用于校验光亮度 debug for calibration 20090408
											{
                          if((g_asc_reception_buffer[6] ==0x22)&&(g_asc_reception_buffer[7] ==0x22))   SCS_received.setpoint_low    = 1;    	// D1 00 EE x3 10 0x 22 22
                          if((g_asc_reception_buffer[6] ==0x33)&&(g_asc_reception_buffer[7] ==0x33))   SCS_received.setpoint_medium = 1; 		// D1 00 EE x3 10 0x 33 33
                          if((g_asc_reception_buffer[6] ==0x44)&&(g_asc_reception_buffer[7] ==0x44))   SCS_received.setpoint_high   = 1;   	// D1 00 EE x3 10 0x 44 44
											}
								 		}
								 		if(g_asc_reception_buffer[4] == 0x15)       	// D5 LOC 01 43 15 XX XX XX
								 		{
								  			eep_M2_sens = g_asc_reception_buffer[7];
											M2_type = '5';//frame_M2_answer('5');		//to answer the senstivity setting
								 		}
								 		if(g_asc_reception_buffer[4] == 0x16)       	// D5 LOC 01 43 16 XX XX XX
								 		{
								 			if((g_asc_reception_buffer[6] <=0x3C)&&(g_asc_reception_buffer[7] <=0x3C)&&(g_reception_buffer[7] == '2'))
                      {
                        unsigned long int hour_count = g_asc_reception_buffer[5];
							 					M2_timer = ( hour_count*3600 + g_asc_reception_buffer[6]*60 + g_asc_reception_buffer[7] );
                        eep_M2_hour = g_asc_reception_buffer[5];
                        eep_M2_min  = g_asc_reception_buffer[6];
                        eep_M2_sec  = g_asc_reception_buffer[7];
                       }
                       M2_type = '6';//frame_M2_answer('6');		//to answer the timer setting
								 		}
									}
									// Add by alan end //should replaced by reyno
								break;
        	
								case '1':			//area
									if((g_reception_buffer[2] != 0) || (KO_conf.DesAdd != g_asc_reception_buffer[1]) || ((KO_conf.AddressType != 1)))
									{
										//reception_buffer_clear(0);
									}
									else
									{
										switch (g_reception_buffer[7])
										{
											case '2':
												configuration_setting_frame(g_asc_reception_buffer[4]);
											break;
        	
											case '3':
												configuration_answer_frame(g_asc_reception_buffer[4]);
											break;
        	
											default:break;
										}
									}
								break;
        	
								case '2':
									if(g_asc_reception_buffer[1] == 0x00)
									{
										switch (g_reception_buffer[7])
										{
											case '2':
												configuration_setting_frame(g_asc_reception_buffer[4]);
											break;
        	
											case '3':
												configuration_answer_frame(g_asc_reception_buffer[4]);
											break;
        	
											default:break;
										}
									}
								break;
        	
								case '3':
									if(g_reception_buffer[2] == '0')
									{
										if(KO_conf.DesAdd == g_asc_reception_buffer[1])
										{
											switch (g_reception_buffer[7])
											{
												case '2':
													configuration_setting_frame(g_asc_reception_buffer[4]);
												break;
        	
												case '3':
													configuration_answer_frame(g_asc_reception_buffer[4]);
												break;
        	
												default:break;
											}
										}
									}
								break;
							}
						break;
        	
						default:break;
					}
				}
				else if(g_reception_buffer[5] == '9')
				{
					if( g_asc_reception_buffer[0] == 0xD2 )
						aux_procedure();
					else if( g_asc_reception_buffer[0] == 0xD0 )
					{
						if(g_reception_buffer[6] == '0' || g_reception_buffer[6] == 'F')
						{
							 id_frame();
						}
					}
				}
			break;
				
			case 0x25:
				strncpy(buffer_tx,"D200013485000000",17);
				strncpy(&buffer_tx[10],&scs_frame[current].byte[3],7);
				buffer_tx[16] = 0;
				send_frame_pp_ext_broad(buffer_tx,50);
			break;

			case 0x26:
				if(flags.request_83)
				{
					flags.request_83 = 0;
					strncpy(buffer_tx,"D200013483000000",17);
					buffer_tx[16] = 0;
					strncpy(&buffer_tx[10],&scs_frame[current].byte[4],6);
					buffer_tx[15] = '0';
					send_frame_pp_ext_broad(buffer_tx,50);
				}
			break;

			default:
				scs_frame[current].finished = 0;		
				return 1;
		}
	}
	scs_frame[current].finished = 0;
	return 0;
}

unsigned char is_gateway_busy(void)
{
	unsigned char i;
	//unsigned char current;

	for(i=0;i<10;i++)
	{
		if(scs_frame[i].finished)
		{
      scs_frame[i].finished = 0;
      switch(StrToChar(&scs_frame[i].byte[1]))
		  {
        case 0x00:
          //scs_frame[current].finished = 0;
          return 0x02;

        case 0x01:
         return 0x01;

        case 0x07:
          return 0x07;

        case 0x08:
          if(StrToChar(&scs_frame[i].byte[3]) == 2 || StrToChar(&scs_frame[i].byte[3]) == 3)
            return 1;
        break;

				case 0x13:
					return 0x13;
				
        case 0x22:
          return 1;

			  default: break;
		  }
		}
	}
  return 0;
}

//SCS_received.presence GR presence
//SCS_received.GS_presence GS presence
void application_decode_short(void)
{	
	if(KO_conf.AddressType == 2)
	{
		if((g_asc_short_buffer[0] ==KO_conf.Reference)&&(KO_conf.FuncMod ==5))		//APL\00\12\00
		{
			if((g_asc_short_buffer[1] ==0x00)&&(g_asc_short_buffer[2] ==0x12)&&(g_asc_short_buffer[3] ==0x00))
				SCS_received.GR_ON = 1;
		}
		if(g_asc_short_buffer[0] == 0xB5)
		{
			if(g_asc_short_buffer[1] == KO_conf.GR)
			{
				if(g_asc_short_buffer[2] == 0x1D)
				{
					if(g_asc_short_buffer[3] == 0x00)	
						SCS_received.presence = 1;	// B|5 G|G 1|D 0|0  "presence"
					else if(g_asc_short_buffer[3] == 0x01)	
						SCS_received.no_presence = 1;	// B|5 G|G 1|D 0|1 "no presence"
				}
				
				if(g_asc_short_buffer[2] == 0x12)
				{
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.GR_ON = 1;		//B|5 G|G 1|2 0|0   "Group frame ON"
					
					if(g_asc_short_buffer[3] == 0x01)	
						SCS_received.GR_OFF = 1;	// B|5 G|G 1|2 0|1  "group frame OFF"
					
					if(g_short_buffer[7] == 'D')			// dimmer	0526
					{
						if(g_short_buffer[6] == '0')
							SCS_received.GR_OFF = 1;	
						else if(g_short_buffer[6] <= '9')
							SCS_received.GR_ON = 1;
					}
				}							
			}
				
			if(((KO_conf.GS1 != 0)||(KO_conf.GS2 != 0)) && (g_asc_short_buffer[1] != 0))
			{
				if((g_asc_short_buffer[1] == KO_conf.GS1)||(g_asc_short_buffer[1] == KO_conf.GS2))				
				{
					if(g_asc_short_buffer[2] == 0x1D)
					{
						if(g_asc_short_buffer[3] == 0)	 SCS_received.GS_presence = 1;									
						// B|5 G|S 1|D 0|0  "presence" send by GS
					}
				}		
			}
		}	
	}
	
	if(((KO_conf.AddressType == 2)&&(KO_conf.Reference == g_asc_short_buffer[1]))||((KO_conf.AddressType == 0)&&(KO_conf.DesAdd == g_asc_short_buffer[1])))
	{		
		if(g_asc_short_buffer[0] == 0xB8)	// frame B8						// B|8 G|G 1|2 0|1
		{
			if(g_asc_short_buffer[2] == 0x12)
			{
				if(Time_delay.regulation.time_out == 1)
				{
					DLL.start_regulation = 0;
					(KO_conf . status[0]&=(~(1<<6)));
				}

				switch(g_short_buffer[7])
				{
					case '0':
						Sensor_mode.power_on_flag = 1;
						KO_conf.status[1] = 100;		//reyno 0616
						SCS_received.update_state_ON = 1;
						break;
					case '1':
						Sensor_mode.power_on_flag = 0;
						KO_conf.status[1] = 0;		//reyno 0616
						SCS_received.update_state_OFF = 1;
						break;
					case 'D':
						Sensor_mode.power_on_flag = 1;
						SCS_received.update_state_LEVEL = 1;
						SCS_received.P2P_dimmer_flag = 1;			// dimmer,used for regulation
						SCS_received.P2P_actuator_flag = 0;
						
						switch (g_short_buffer[6])
						{
							case '1':
							KO_conf.status[1]=1;
							break;
							
							case '2':
							KO_conf.status[1]=10;
							break;
							
							case '3':
							KO_conf.status[1]=20;
							break;
							
							case '4':
							KO_conf.status[1]=30;
							break;
							
							case '5':
							KO_conf.status[1]=40;
							break;
							
							case '6':
							KO_conf.status[1]=50;
							break;
							
							case '7':
							KO_conf.status[1]=60;
							break;
							
							case '8':
								KO_conf.status[1]=75;
							break;
							
							case '9':
								KO_conf.status[1]=100;
							break;
							
							default:break;
						}
						break;
						default:	break;	
					}
			}
			
			if(g_asc_short_buffer[2] == 0x1D)
			{
				if(KO_conf.AddressType == 0)
				{
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.presence = 1;
					else if(g_asc_short_buffer[3] == 0x01)
						SCS_received.no_presence = 1;
				}
			}
		}
		
		if(KO_conf.AddressType == 0)
		{
			switch(g_asc_short_buffer[2])
			{
				case 0x12:
					/*
					if(KO_conf.LightReg == 1)
					{	
						DLL.start_regulation = 1;
						SetBit(KO_conf.status[0],Status_Regulationing);
						regulation_timer_initial();
					}
					*/
					if(g_asc_short_buffer[3] == 0x00)
						SCS_received.GR_ON = 1;         // 0714 alan in order to compatible with GR, P2P and GR use the same flag SCS_received.GR_ON
					else if(g_asc_short_buffer[3] == 0x01)
						SCS_received.GR_OFF = 1;
				break;
				default:break;
			}
		}	
	}
	
	//receive APL XX 12 00
	if(g_asc_short_buffer[0] == KO_conf.DesAdd)
	{
		switch(g_asc_short_buffer[2])
		{
			case 0x12:
				if(KO_conf.LightReg == 1)
				{	
					DLL.start_regulation = 1;
					(KO_conf . status[0]|=(1<<6));
					regulation_timer_initial();
				}
				
				if(g_asc_short_buffer[3] == 0x00)
					SCS_received.GR_ON = 1;         // 0714 alan in order to compatible with GR, P2P and GR use the same flag SCS_received.GR_ON
				else if(g_asc_short_buffer[3] == 0x01)
					SCS_received.GR_OFF = 1;
			break;
			default:break;
		}
	}
	
}

void application_decode_long(void)
{
	if((g_asc_reception_buffer[1] == KO_conf.DesAdd && KO_conf.AddressType == 0) || (g_asc_reception_buffer[1] == KO_conf.Reference && KO_conf.AddressType == 2))
	{
		if(g_asc_reception_buffer[5] == 0x0D)
		{
			SCS_received.P2P_dimmer_flag = 1;			// dimmer,used for regulation
			SCS_received.P2P_actuator_flag = 0;
		}
	}
}

void calibration_decode(void)
{
	// add 0519
	// Enter calibration waiting mode	D1 01 01 42 14 00 00 00
	// Exit calibration waiting mode	D1 01 01 42 14 00 00 FF
	// Sent calibration lux				D1 01 01 42 10 0X XX XX
	// change by reyno May30
	if(g_asc_reception_buffer[3] == 0x42)       	// D5 LOC 01 42 14 XX XX XX 0519
	{
		if(g_asc_reception_buffer[4] == 0x14 )
		{
			if(g_asc_reception_buffer[7] ==0x00)
			{
				SCS_received.calib_wait = 1;    	// D1 LOC 01 42 14 XX XX 00
		  	led_blinking(250,250);
				state.main_state = 0x9033;
			}
			else if(g_asc_reception_buffer[7] == 0xFF)
			{
				SCS_received.calib_wait = 0; 		//SCS_received.calib_exit = 1; 		// D1 LOC 01 42 14 XX XX FF
		 		led_blinking_disable(0);
				state.main_state = 0;
			}
		}
		
		if(g_asc_reception_buffer[4] == 0x10)
		{
			if(SCS_received.calib_wait == 1)
			{
				unsigned long int temp_lux;
				temp_lux = g_asc_reception_buffer[5]&0x0F;
				temp_lux <<= 8;
				temp_lux += g_asc_reception_buffer[6];
				temp_lux <<= 8;
				temp_lux += g_asc_reception_buffer[7];
			
				DLL.setpoint_M = temp_lux*10/DLL.day_level;
				eep_setpoint[2] = DLL.setpoint_M;
				daylight_set_init();
				buzzer_ms(500);	
			}
		}
	}
}

//reyno 0602
void scs_calibration(void)
{								
	if(g_asc_reception_buffer[3] == 0x42)       	// D5 LOC 01 42 14 XX XX XX 0519
	{
		if(g_asc_reception_buffer[4] == 0x14 )
		{
			if(g_asc_reception_buffer[7] ==0x00)
			{
				SCS_received.calib_wait = 1;    	// D1 LOC 01 42 14 XX XX 00
		  	led_blinking(250,250);
				state.main_state = 0x9033;
			}
			else if(g_asc_reception_buffer[7] == 0xFF)
			{
				SCS_received.calib_wait = 0; 		//SCS_received.calib_exit = 1; 		// D1 LOC 01 42 14 XX XX FF
		 		led_blinking_disable(0);
				state.main_state = 0;
			}
		}
		
		if(g_asc_reception_buffer[4] == 0x10)
		{
			if(SCS_received.calib_wait == 1)
			{
				unsigned long int temp = 0;				// add by alan
				float f_temp;
				temp = g_asc_reception_buffer[5];
				temp = temp<<8;
				temp += g_asc_reception_buffer[6];
				temp = temp<<8;
				temp += g_asc_reception_buffer[7];
				temp &= 0xFFFFF;
				KO_conf.DF = temp*10/ DLL.calc_level;			//0526
				f_temp = (float)temp*10/ (float)DLL.calc_level;
				if((f_temp - KO_conf.DF >= 0.5) && (KO_conf.DF != 255))
					KO_conf.DF++;
				write_KO(22,KO_conf.DF); //reyno 0602
				write_ee_KO(22,KO_conf.DF);										// 0529 write_ee_KO(unsigned char index,unsigned char data);
				buzzer_ms(500);
			}
		}
	}
}
