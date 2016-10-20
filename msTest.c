/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 370 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-10 16:12:43 +0200 (mer, 10 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/msTest.c $			
   *																																						
   ****************************************************************************************************************************************************

 */


#define	_TEST_C
 
#include "msPlatform.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
#include <p18f45k22.h>
#include <string.h>

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

#include "ConfigEasyPicV7.h"


// direct dependecies:

//	reverse dependecies: Timer, Glcd, Touch
#include "krTimerGlo.h"
#include "rs2Lcd.h"
#include "rs2Glcd.h"

//#include "rs2TouchGlo.h"
#include "rs2ButtonsGlo.h"


// ----------------------------------------------------------------------------

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - CONSTANT DEFINITION
// ------------------------12345678901234567890
#define  STR_VERSIONE_FW  "Test FW ver-E10-12-"

// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - VARIABLE DEFINITION

char Flag;
char Counter;

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

// void InitMicro (void)
// {
// 
//    // set RC0 and RC11 as digital output
//    ANSELC &= 0xCF;
//    TRISC  &= 0xCF;
// 
// }

#ifdef _CONFIG_EASY_PIC_V7_GRAPHIC_LCD
void TestInit (void)
{
   ram char str[21];
   
   // visualizza versione firmware
   strcpypgm2ram(str,(const far _ROM char *)STR_VERSIONE_FW);
   glcdStrXY(0,0,str);
}
#elif defined(_CONFIG_EASY_PIC_V7_LCD)
void TestInit (void)
{
   // ram char str[21];

   // strcpypgm2ram(str,(const far _ROM char *)STR_VERSIONE_FW);
   // LcdStrRC(1,0,str);
   LcdRomStrRC(1,0,STR_VERSIONE_FW);
   
//   LcdSetPosition(3,16);
//   LcdCh('1');
//   LcdCh('6');
//
//   LcdSetPosition(2,17);
//   LcdCh('1');
//   LcdCh('7');
//   
//   LcdSetPosition(4,18);
//   LcdCh('1');
//   LcdCh('2');
//   
//   LcdSetPosition(1,15);
//   LcdCh('1');
//   LcdCh('3');
   
}
#endif


void TestTmrSecond (void)
{
   Timer[TMR_SECOND] = 10;
   
//   if(Flag == 0)
//   {
//      Flag = 1;
//      LATC &= 0xCF;            
//   }
//   else
//   {
//      Flag = 0;
//      LATC |= 0x30;            
//   }
}


#if defined(_CONFIG_EASY_PIC_V7_TOUCH) && defined(_CONFIG_EASY_PIC_V7_GRAPHIC_LCD)
void TestTmrGLCD (void)
{
   char in_xy_nib_l;
   char in_xy_nib_h;
   
   
   Timer[TMR_TEST_GLCD] = 200;

   Counter++;
   Counter &= 0x0F;
   
   glcdChXY(Counter,2,'1');
   glcdChXY(Counter+1,2,'2');
   glcdChXY(Counter+2,2,'3');
   glcdChXY(Counter+3,2,'4');
   glcdChXY(Counter+4,2,'5');
   glcdChXY(Counter+5,2,'6');
   glcdChXY(Counter+6,2,'7');
   glcdChXY(Counter+7,2,'8');
   glcdChXY(Counter+8,2,'9');
   glcdChXY(Counter+9,2,'0');
   
   in_xy_nib_l = TouchX & 0x0F;
   in_xy_nib_h = (TouchX & 0xF0) >> 4;
   glcdChXY(8,7,'0'+in_xy_nib_h);
   glcdChXY(9,7,'0'+in_xy_nib_l);

   in_xy_nib_l = TouchY & 0x0F;
   in_xy_nib_h = (TouchY & 0xF0) >> 4;
   glcdChXY(12,7,'0'+in_xy_nib_h);
   glcdChXY(13,7,'0'+in_xy_nib_l);
  
}
#elif defined(_CONFIG_EASY_PIC_V7_LCD)
void TestTmrGLCD (void)
{
//    char centinaia, decine, unita;
//    
//    centinaia = Buttons.Codice/100;
//    decine = (Buttons.Codice - centinaia*100)/10;
//    unita = Buttons.Codice%10;
// 
//    Timer[TMR_TEST_GLCD] = 200;
// 
//    Counter++;
//    Counter &= 0x0F;
// 
//    LcdSetPosition(3,3);
//    LcdCh('0'+centinaia);
//    LcdCh('0'+decine);
//    LcdCh('0'+unita);
// 
//    LcdSetPosition(2,Counter+2);
//    LcdCh(' ');
//    LcdCh('7');
//    
//    LcdSetPosition(4,3);
//    LcdCh('0'+Buttons.Stato);
// //   LcdCh('2');
//    LcdCh(' ');
//    
// //   LcdSetPosition(1,Counter+1);
// //   LcdCh('1');
// //   LcdCh('5');
}
#endif
