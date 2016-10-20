/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 361 $																											
   *	LAST DATE REVISION:     $Date: 2016-06-14 18:23:07 +0200 (mar, 14 giu 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/ui_GeneralEdt.h $			
   *																																						
   ****************************************************************************************************************************************************

 */


#ifdef _UI_DEF_C
#define _EXTERN_UI_DEF
#else
#define _EXTERN_UI_DEF extern
#endif
 
 

// Definizione dei parametri generali del sistema
#define  PAR_MIN_GENERAL_LANGUAGE      0
#define  PAR_MAX_GENERAL_LANGUAGE      1
#define  PAR_DEF_GENERAL_LANGUAGE      0
#define  PAR_GENERAL_LANGUAGE_NUMBER   PAR_MAX_GENERAL_LANGUAGE + 1
#define	ROW_PAR_GENERAL_LANGUAGE		{	ID_STR_PAR_GENERAL_LANGUAGE		,&Language		,PAR_DEF_GENERAL_LANGUAGE			,PAR_MIN_GENERAL_LANGUAGE		,PAR_MAX_GENERAL_LANGUAGE		,sizeof(Language)		,BYTE			,DIGIT_1		}

_EXTERN_UI_DEF	char Language;

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

