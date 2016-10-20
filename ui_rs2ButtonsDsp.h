/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 368 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-04 18:17:11 +0200 (gio, 04 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/ui_rs2ButtonsDsp.h $			
   *																																						
   ****************************************************************************************************************************************************

 */


#ifdef _UI_DEF_C
#define _EXTERN_UI_DEF
#else
#define _EXTERN_UI_DEF extern
#endif
 
// Nota bene:
// ID_STR_VAR_RS2_BUTTONS_TIMES_PRESSED deve essere definita nel file uiApplication.c

//																   Etichetta variabile di stato				   ,ptr_variabile						,sizeof()									,FLAG1		,FLAG2 		
#define	ROW_VAR_RS2_BUTTONS_TIMES_PRESSED		{	ID_STR_VAR_RS2_BUTTONS_TIMES_PRESSED		,&rs2ButtonsTimesPressed		,sizeof(rs2ButtonsTimesPressed)		,WORD			,DIGIT_3		}

_EXTERN_UI_DEF	char rs2ButtonsTimesPressed;

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

