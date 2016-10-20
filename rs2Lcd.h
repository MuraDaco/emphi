/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 344 $																											
   *	LAST DATE REVISION:     $Date: 2016-03-01 17:27:34 +0100 (mar, 01 mar 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2Lcd.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifndef _LCD_H
#define _LCD_H


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

#ifdef _MAIN_C
void LcdInit (void);
#endif
#ifdef _PROCESS_TABLE_C
void LcdInit (void);
#endif

void LcdSetPosition				(unsigned char row, unsigned char column);
void LcdCh							(char carattere);
void LcdSetDisplayShiftLeft	(void);
void LcdSetDisplayShiftRight  (void);
void LcdSetCursorShiftLeft		(void);
void LcdSetCursorShiftRigh		(void);
void LcdStrRC  					(unsigned char row,unsigned char column,char *str);
void LcdRomStrRC  				(unsigned char row,unsigned char column,const _ROM char *str);
void LcdNumberRC					(unsigned char row,unsigned char column,unsigned char par);
void LcdDisplayReset 			(void);

void LcdDisplayOff 				(void);
void LcdDisplayOn 				(void);
void LcdCursorOff 				(void);
void LcdCursorOn 					(void);
void LcdBlinkingOff 				(void);
void LcdBlinkingOn 				(void);

void LcdDisplayShift 			(void);
void LcdCursorShift 				(void);
void LcdRightShift 				(void);
void LcdLeftShift 				(void);

void LcdEntryModeRightShift	(void);
void LcdEntryModeLeftShift		(void);
void LcdEntryModeDisplay		(void);
void LcdEntryModeCursor			(void);



#endif	// _LCD_H

