/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 302 $																											
   *	LAST DATE REVISION:     $Date: 2015-12-07 15:16:33 +0100 (lun, 07 dic 2015) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/krEventGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */


#ifndef _PROCESS_GLO_H
#define _PROCESS_GLO_H

#include "msPlatform.h"

#include "krEventGlo.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
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

		
#define	PROCESS_TIMER						0
#define	PROCESS_BUTTONS					1
#define	NUMBER_PROCESS						2


typedef struct
{
   unsigned char (*Controllo)(char);			
   EventPtrTableDef *EventMatrix;				
   char NumeroRipetizioniControllo;
} ProcessStruct;


extern _ROM ProcessStruct ProcessTable[];
extern _ROM EventTableDef ProcessInitTable[];


#endif	// _PROCESS_GLO_H

