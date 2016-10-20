/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 363 $																											
   *	LAST DATE REVISION:     $Date: 2016-06-16 17:34:11 +0200 (gio, 16 giu 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/krEventGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#include "msPlatform.h"

#ifndef _EVENT_GLO_H
#define _EVENT_GLO_H
 
// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

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

#define  EVENT_BUTTONS_RIGHT     		0
#define  EVENT_BUTTONS_UP        		1
#define  EVENT_BUTTONS_ENTER     		2
#define  EVENT_BUTTONS_DOWN      		3
#define  EVENT_BUTTONS_LEFT      		4
#define  NUMBER_EVENT_BUTTONS    		5

typedef void (*EventTableDef)(void);

typedef struct
{
   _ROM EventTableDef *EventTable;
} EventPtrTableDef;		// EventStructX;                     	// EventPtrTableDef

// extern EventStructX	EventTimerMatrix[];   
// extern EventStructX	ButtonsEventMatrix[];  

extern EventPtrTableDef		EventTimerMatrix[];   
extern EventPtrTableDef		ButtonsEventMatrix[];  


#endif	// _EVENT_GLO_H

