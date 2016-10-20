/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 350 $																											
   *	LAST DATE REVISION:     $Date: 2016-03-09 18:54:40 +0100 (mer, 09 mar 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2ButtonsGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifdef _DEF_C
#define _EXTERN_DEF
#else
#define _EXTERN_DEF extern
#endif


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

#define	BUTTONS_STATE_NO_PRESSED					0
#define	BUTTONS_STATE_WAIT							1
#define	BUTTONS_STATE_PRESSED						2
#define	BUTTONS_STATE_PRESSED_EXECUTED			3
#define	BUTTONS_STATE_NUMBER							4

#define	BUTTONS_EVENT_NOTHING						0
#define	BUTTONS_EVENT_PRESS							1
#define	BUTTONS_EVENT_RELEASE						2
#define	BUTTONS_EVENT_NUMBER							3

#define	BUTTONS_MODALITA_RIPETUTA_OFF		0
#define	BUTTONS_MODALITA_RIPETUTA_ON		1

#define  CODE_BUTTONS_RIGHT     0x01
#define  CODE_BUTTONS_UP        0x02
#define  CODE_BUTTONS_ENTER     0x04
#define  CODE_BUTTONS_LEFT      0x08
#define  CODE_BUTTONS_DOWN      0x10



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

typedef struct
{
   char Stato;
   char Codice;
   char CodiceOld;
   char Modalita;
} ButtonsStruct;

_EXTERN_DEF ButtonsStruct Buttons;
