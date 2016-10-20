/*

   glcd.c
   
   Description / Descrizione:
   Driver to handle the LCD graphic provided with the development board EasyPic V7
   Driver per gestire l'lcd grafico fornito con la scheda di sviluppo EasyPic V7 
   
   Documentation / Documentazione
   datasheet pdf file of MOdule no: WDG0151-TMI-V#N00 by http://www.winstar.com.tw
	to download datasheet
	http://www.mikroe.com/support/index.php?/Knowledgebase/Article/View/803/121/winstar-wdg0151-tmi-vn00-128x64-glcd-display
   
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
   *	REVISION NUMBER:        $Revision: 306 $																											
   *	LAST DATE REVISION:     $Date: 2015-12-07 19:35:58 +0100 (lun, 07 dic 2015) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2Glcd.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifndef _GLCD_H
#define _GLCD_H

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE

// SECTION END
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

// direct dependecies:	------------------

//	reverse dependecies: main

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

#ifdef _MAIN_C
void glcdInitPorts	(void);
#endif

#ifdef _PROCESS_TABLE_C
void glcdInitPorts	(void);
#endif

void glcdStr			(char *str);
void glcdStrXY			(char x, char y, char *str);
void glcdCh				(char ch);
void glcdChXY			(char x, char y, char ch);
void glcdSetXY			(char x, char y);

// SECTION END
//	****************************************************************************

// Function Definition

#endif