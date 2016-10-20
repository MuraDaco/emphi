/*
   adc.h
   
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
   *	REVISION NUMBER:        $Revision: 261 $																											
   *	LAST DATE REVISION:     $Date: 2015-10-19 19:58:07 +0200 (lun, 19 ott 2015) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2ADC.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifndef _ADC_H
#define _ADC_H


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



// adc routine
void adcInit (void);
unsigned char adcReadChannel (char channel);


#endif