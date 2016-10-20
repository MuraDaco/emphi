/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 363 $																											
   *	LAST DATE REVISION:     $Date: 2016-06-16 17:34:11 +0200 (gio, 16 giu 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/uiParGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */


#include "msPlatform.h"

typedef struct {
   char id_label;
   char *ptr_par;
   char default_par;
	char min_par;
	unsigned char max_par;
	char sizeof_par;
	char flag1;
	char flag2;
} ParElementoStruct;

#if defined(_UI_BASE_C) || defined(_UI_PAR_C)

extern _ROM ParElementoStruct ParElemento[];

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

