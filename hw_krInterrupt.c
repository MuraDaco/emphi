/*

   MODULE DESCRIPTION:  manage interrupt: timer, adc, sci, etc
   
   AUTHOR:  Marco Ing. Dau		 																									
   
   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/hw_krInterrupt.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

 
#define	_HW_INTERRUPT_C 

#include "msPlatform.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
#include <p18f45k22.h>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Application and Dependecies)

// applications
#include "krTimer.h"

// ----------------------------------------------------------------------------


//	****************************************************************************
//	****************************************************************************
void interrupt high_priority high_isr (void)
{
   // check flag Timer 0
   if(INTCONbits.TMR0IF)
   {
      // clear flag Timer 0 for next interrupt
      INTCONbits.TMR0IF = 0;
      
      // register reload for next interrupt
      TMR0H = 0xC1;  // it MUST write the high byte first
      TMR0L = 0x80;  // writing low byte automatically update the high byte (see the pic datasheet)

      UpdateTimer();
   }
}

//	****************************************************************************
//	****************************************************************************
void interrupt low_priority low_isr (void)
{
  /* ... */
}


//	****************************************************************************
//	****************************************************************************
void InitInterruptTimer (void)
{

   // Interrupt
   // switch-off all interrupt
   
   // Timer 0

   // register timer setup for a period of 2ms correspondent to 16000 Tcy
   // so the register have to have the following value 65536-16000 = 49536 = 0xC180
   TMR0H = 0xC1;  // it MUST write the high byte first
   TMR0L = 0x80;  // writing low byte automatically update the high byte (see the pic datasheet)
   
   // set timer 0 to 16bit
   T0CONbits.T08BIT = 0; // by default is 1
   
   // disable the prescaler 
   T0CONbits.PSA  = 1;   // by default is 1, you may omit this instruction
   T0CONbits.T0PS = 0;   // set minimum prescaler value
   
   // enable timer 0 ----------------------------- T0CONbits.TMR0ON = 1;      // by default is 1

   // select source timer 0
   T0CONbits.T0CS   = 0;   // by default is 1
   
   // set timer0 priority (by default is high) --- INTCON2bits.TMR0IP = 1;    // by default is 1
   
   // clear interrupt flag to enable interrupt - INTCONbits.TMR0IF = 0;     // by default is 0
   
   // enable interrupt 
   INTCONbits.TMR0IE = 1; // by default is 0
   
   
   // disable priority level interrupt ----------- RCONbits.IPEN 0;           // by default is 0

   // enable all non-maskered interrupt
   INTCONbits.GIE = 1; // di default ? 0
  
}

