/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 366 $																											
   *	LAST DATE REVISION:     $Date: 2016-07-27 18:13:43 +0200 (mer, 27 lug 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/krTimerTbl.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define _TIMER_TABLE_C

#include "msPlatform.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE


// SECTION END
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

// definizione della tabella evento
#include "krEventGlo.h"

// definizione Evento Nullo
#include "krEvent.h"

// si apprende il numero dei timers
#include "krTimerGlo.h"

// Moduli che usano timer (dipendenze indirette)
#include "krTimer.h"
#include "rs2Touch.h"
#include "rs2Buttons.h"
#include "uiPar.h"
#include "uiVar.h"
#include "uiLbox.h"
#include "msTest.h"

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


_ROM EventTableDef EventTimer[TMR_NUMBER] = {
                                 TestTmrSecond,    // TMR_SECOND		0  //  modulo Test      
                                 TestTmrGLCD,      // TMR_TEST_GLCD	1  //  modulo Test      
                                 EventNull,        // TMR_TOUCH		2  //  modulo Touch     
                                 EventNull,        // TMR_LCD_INIT	3  //  non fare niente   
                                 ButtonsTimer,     // TMR_BUTTONS		4  //  modulo Buttons   
                                 uiParTimer,       // TMR_UI_PAR		5  //  modulo Parameter 
                                 uiLboxTimer,      // TMR_UI_LBOX		6  //  modulo ListBox   
                                 uiVarTimer        // TMR_UI_VAR     7  //  modulo Variable
};                                                 // TMR_NUMBER		8

