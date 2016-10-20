/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 366 $																											
   *	LAST DATE REVISION:     $Date: 2016-07-27 18:13:43 +0200 (mer, 27 lug 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/krTimerGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifdef _DEF_C
#define _EXTERN_DEF
#else
#define _EXTERN_DEF extern
#endif



#include "msPlatform.h"

// definizione della funzione evento
#include "krEventGlo.h"



// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)


// ----------------------------------------------------------------------------

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - CONSTANT DEFINITION

#define	TMR_SECOND		0  //  modulo Test  
#define	TMR_TEST_GLCD	1  //  modulo Test 
#define	TMR_TOUCH		2  //  modulo Touch
#define	TMR_LCD_INIT	3  //  non fare niente
#define	TMR_BUTTONS		4  //  modulo Buttons
#define	TMR_UI_PAR		5  //  modulo Parameter
#define	TMR_UI_LBOX		6  //  modulo ListBox
#define	TMR_UI_VAR		7  //  modulo Variable
#define  TMR_NUMBER		8


// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - VARIABLE DEFINITION

#if defined(_DEF_C) || defined(_TIMER_C) || defined(_TEST_C) || defined(_TOUCH_C) || defined(_LCD_C) || defined(_BUTTONS_C) || defined(_UI_PAR_C) || defined(_UI_VAR_C) || defined(_UI_LBOX_C)
_EXTERN_DEF	int TmrSecond;
_EXTERN_DEF	int TmrError;
_EXTERN_DEF	int TmrTouch;
_EXTERN_DEF	int Timer[TMR_NUMBER];
#endif


extern _ROM EventTableDef EventTimer[];

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

