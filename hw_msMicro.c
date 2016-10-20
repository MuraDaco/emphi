/*

   MODULE DESCRIPTION:  manage micro general register

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/hw_msMicro.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE

#include <p18f45k22.h>

#include "msPlatform.h"

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

// direct dependecies:

//	reverse dependecies:

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



void InitMicro (void)
{

// sette segmenti
   // selezionare i primi 4 bit dello switch 4 SW4<0.3>, servono per comandare i comuni dei ttl Qx (vedere lo schema elettrico)
   // impostare in OUT le seguenti porte
   // PORT A <0.3> (le prime 4)
   TRISA &= 0xF0;
   // PORT D <0.7> (tutte)
   TRISD = 0;
   // impostare il registro analog input a 0 per poter leggere il registro PORTD
   // di default pord ?mpostato come ingrsso analogico
   ANSELD = 0;
   // Inizizializzazione display
   // 01-Spegni tutti i comuni
   PORTA &= 0xF0;
   PORTD = 0;
   PORTD = 0xCC;

//   // set RC0 and RC11 as digital output
//   ANSELC &= 0xCF;
//   TRISC  &= 0xCF;

}

