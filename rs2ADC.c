/*
   adc.c
   
   Description / Descrizione:
   Driver to handle the ADC
   Driver per gestire l'ADC
	
   Documentation / Documentazione
	

   
   Author:
   Marco Dau

   Creation Date:
   Tuesday, 17 March 2015
   
   Update:
   
   
*/

/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2ADC.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#include <p18f45k22.h>

#include "msPlatform.h"


#include "rs2ADCGlo.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE

// SECTION END
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

// direct dependecies:

//	reverse dependecies:

// SECTION END
// ----------------------------------------------------------------------------

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - CONSTANT DEFINITION

// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - VARIABLE DEFINITION

// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - ARRAY DEFINITION

// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	****************************************************************************
// SECTION - CONTROL FUNCTION DEFINITION

// SECTION END
//	****************************************************************************

//	****************************************************************************
// SECTION - EVENT FUNCTION DEFINITION

// SECTION END
//	****************************************************************************


//	****************************************************************************
// SECTION - LIBRTARY FUNCTION DEFINITION

// SECTION END
//	****************************************************************************


#define	ADC_CHS_MASK_0	0x83
#define	ADC_CHS_MASK_1	0x7C
#define	ADC_CHS_AN0		0x00
#define	ADC_CHS_AN1		0x04
#define	ADC_CHS_AN7		0x1C



char adcCHSBuff [ADC_CH_NUMBER] = {
	ADC_CHS_AN0,	// CH_TOUCH_BOTTOM
	ADC_CHS_AN1,	// CH_TOUCH_LEFT
	ADC_CHS_AN7		// CH_LM35
};




void adcInit (void)
{
   // Configure Port
   // see the application
   
   // Configure ADC
   // 01 - Select ADC Conversion Clock
   // ADCS bits in ADCON2
   ADCON2 |= 0x01;
   
   // 02 - Configure Voltage Reference
   // PVCFG e NVCFG bitz in ADCON1
   
   
   // 03 - Select ADC Input Channel - see the read routine
   // CHS in ADCON0
   
   // 04 - Select result format
   //ADFM in ADCON2
   ADCON2bits.ADFM = 0;
   
   // 05 - Select acquisition delay: it's about the acqusition time; 
   //                                  see Fig 17-3 and 17-4 to best understanding its meaning
   // ACQT in ADCON2
   ADCON2 |= 0x30; 
   
   // 06 - Turn on ADC module
   // ADON in ADCON0
   ADCON0bits.ADON = 1;
   
   // Configure ADC Interrupt (Optional)
   
   // 01 - Clear ADC interrupt flag
   // ADIF in PIR1
   PIR1bits.ADIF = 0;
   
   // 02 - Enable ADC interrupot
   // ADIE in PIE1
   // PIE1bits.ADIE = 1
   
   // 03 - Enable peripheral interrupt
   // ADIP in IPR1
   // IPR1bits.ADIP = 0  // default = 0, istruzione non necessaria infatti il valore ?i default
   
   // 04 - Enable global interrupt
   // GIE in INTCON
   // valore impostato nella routine hwInit.c
}


unsigned char adcReadChannel (char channel)
{
 
   char adc_register;
   
   // select channel
   // 00 - read ADCON0
   adc_register = ADCON0;
   // 01 - clear bit
   adc_register &= ADC_CHS_MASK_0;
   // 02 - set bit
   adc_register |= adcCHSBuff[channel];
   // 03 - set ADCON register
   ADCON0 = adc_register;
   
   
   // Start adc
   ADCON0bits.GO = 1;   

   // adcWait()
   while(ADCON0bits.DONE){
        #asm
            nop
        #endasm
   }
   
   // read adc value
   return ADRESH;
   
   
}







