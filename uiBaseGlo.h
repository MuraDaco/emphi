/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 370 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-10 16:12:43 +0200 (mer, 10 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/uiBaseGlo.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifdef _UI_DEF_C
#define _EXTERN_UI_DEF
#else
#define _EXTERN_UI_DEF extern
#endif

#include "msPlatform.h"


#ifndef _UI_BASE_GLO_H
#define _UI_BASE_GLO_H

typedef struct {
	char o_row;
	char o_col;
	char n_row;	
} BaseCoordinateStruct;
	
typedef struct {
	void (*InitCold)		(void);
	void (*InitLight)		(char element_id);
	void (*EventOn)		(unsigned char father_id);
	void (*Elimina)		(void);
	void (*Visualizza)	(char element_id, BaseCoordinateStruct coordinate);
	char (*Select)			(char element_id, BaseCoordinateStruct coordinate);
	void (*Deselect)		(void);
} BaseElementoStruct;




#ifndef _UI_BASE_C

extern _ROM BaseElementoStruct BaseElemento[];

#endif


#define	EL_PAGE				0
#define	EL_LBOX				1
#define	EL_PAR				2
#define	EL_VAR				3
#define	EL_STR				4
#define	EL_NUMBER			5


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

#endif		// _UI_BASE_GLO_H
