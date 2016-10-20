/*
   glcd.c
   
   Description / Descrizione:
      Driver to handle the LCD graphic provided with the development board EasyPic V7
      Driver per gestire l'lcd grafico fornito con la scheda di sviluppo EasyPic V7 
  
   How do GLCD work:
      
   
  
   Documentation / Documentazione
      datasheet pdf file of MOdule no: WDGO151-TMI-V#N00 by http://www.winstar.com.tw
   
   Author:
      Marco Dau

   Creation Date:
      Tuesday, 17 March 2015
   
   Last Update:
   
   
*/

/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 363 $																											
   *	LAST DATE REVISION:     $Date: 2016-06-16 17:34:11 +0200 (gio, 16 giu 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2Glcd.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define  _GLCD_C

#include "msPlatform.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE
#include <p18f45k22.h>

// END SECTION
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

// direct dependecies:

//	reverse dependecies:

// END SECTION
// ----------------------------------------------------------------------------

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - CONSTANT DEFINITION

// *************************************************************************************
// Configuration PORTs
// *************************************************************************************
#define		GLCD_CMD_TRIS					TRISB
#define		GLCD_DATA_TRIS					TRISD
			
#define		GLCD_CMD_ANSEL					ANSELB
#define		GLCD_DATA_ANSEL				ANSELD
			
#define		GLCD_CMD_PORT					PORTB
#define		GLCD_DATA_PORT					PORTD

// *************************************************************************************
// "command pin port" define			
//		see EasyPic v7 Demoboard Schematic and "Interface Pin Function" Table of GLCD datasheet 
// *************************************************************************************
#define     GLCD_Pin_CS1  					PORTBbits.RB0
#define     GLCD_Pin_CS2  					PORTBbits.RB1
#define     GLCD_Pin_RS   					PORTBbits.RB2	// see "Display Control Instruction" 
#define     GLCD_Pin_D_I  					PORTBbits.RB2	// see "Interface Pin Function" Table, this pin is also named RS; see "Display Control Instruction" and RS pin
#define     GLCD_Pin_R_W  					PORTBbits.RB3
#define     GLCD_Pin_E    					PORTBbits.RB4
#define     GLCD_Pin_RST  					PORTBbits.RB5	// set to low to reset GLCD
					
// *************************************************************************************
// "data pin port" define			
//		see EasyPic v7 Demoboard Schematic
// *************************************************************************************
#define     GLCD_Pin_D0   					PORTDbits.RD0
#define     GLCD_Pin_D1   					PORTDbits.RD1
#define     GLCD_Pin_D2   					PORTDbits.RD2
#define     GLCD_Pin_D3   					PORTDbits.RD3
#define     GLCD_Pin_D4   					PORTDbits.RD4
#define     GLCD_Pin_D5   					PORTDbits.RD5
#define     GLCD_Pin_D6   					PORTDbits.RD6
#define     GLCD_Pin_D7   					PORTDbits.RD7

// *************************************************************************************
// "command bus" define
// 	defines below are been made seeing  "Display Control Instruction" table of GLCD datasheet
// *************************************************************************************
																
#define		GLCD_CDM_ADDR_ON_OFF_ALL_ON  	0x00	
#define		GLCD_CMD_STATUS_READ_ALL_ON  	0x08	// instruction "Status read"
#define		GLCD_CMD_DATA_WRITE_ALL_ON   	0x04	// instruction "Write display data"
#define		GLCD_CMD_DATA_READ_ALL_ON    	0x0C	// instruction "Read display data"

// following defines is the same of precedings plus CS2 pin high that means CS2 disable; CS1 and CS2 are in negative-logic
#define		GLCD_CDM_ADDR_ON_OFF_CS1_ON  	0x02  
#define		GLCD_CMD_STATUS_READ_CS1_ON  	0x0A  // instruction "Status read" with CS2 disable
#define		GLCD_CMD_DATA_WRITE_CS1_ON   	0x06  // instruction "Write display data" with CS2 disable
#define		GLCD_CMD_DATA_READ_CS1_ON    	0x0E  // instruction "Read display data" with CS2 disable

// following defines is the same of precedings plus CS1 pin high that means CS1 disable; CS1 and CS2 are in negative-logic
#define		GLCD_CDM_ADDR_ON_OFF_CS2_ON  	0x01  
#define		GLCD_CMD_STATUS_READ_CS2_ON  	0x09  // instruction "Status read" with CS1 disable
#define		GLCD_CMD_DATA_WRITE_CS2_ON   	0x05  // instruction "Write display data" with CS1 disable
#define		GLCD_CMD_DATA_READ_CS2_ON    	0x0D  // instruction "Read display data" with CS1 disable


// *************************************************************************************
// "data bus" define
// 	defines below have been made seeing  "Display Control Instruction" table of GLCD datasheet
// *************************************************************************************

#define		GLCD_DATA_CMD_ON_OFF    	0x3E	// instruction "Display on/off"
#define		GLCD_DATA_CMD_SET_ADD_Y 	0x40	// instruction "Set Address (Y address)"
#define		GLCD_DATA_CMD_SET_ADD_X 	0xB8	// instruction "Set Address (X address)"
#define		GLCD_DATA_CMD_SET_ADD_Z 	0xC0	// instruction "Set Address (Z address)"

#define		GLCD_ON      					0x01	// instruction "Display on/off"
#define		GLCD_OFF     					0x00	// instruction "Display on/off"


// *************************************************************************************
// GLCD Delay
// *************************************************************************************
#define		GLCD_DELAY_140ns      		1	// Warning! this value can't be greater than 255
#define		GLCD_DELAY_550ns      		1	// Warning! this value can't be greater than 255
#define		GLCD_DELAY_5us      			20	// Warning! this value can't be greater than 255


#define		GLCD_DELAY_NOP_140ns		asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
#define		GLCD_DELAY_NOP_450ns		asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 
#define		GLCD_DELAY_NOP_550ns		asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 


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

void glcdWriteCmd		(char pin_cs_rs_rw, char pin_data);

// SECTION END
//	****************************************************************************






typedef struct
{
	char	ch[5];
}	CharArray;

// Variable definition
char glcdX;
char glcdY;
char glcdCS_sel;

const _ROM char AsciiToCustom [0x80] = {
/* banco 0 di 16 caratteri 0x00 to 0x0F */ 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 
/* banco 1 di 16 caratteri 0x10 to 0x1F */ 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 
/* banco 2 di 16 caratteri 0x20 to 0x2F */ 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 
/* banco 3 di 16 caratteri 0x30 to 0x3F */ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
/* banco 4 di 16 caratteri 0x40 to 0x4F */ 0x3E, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 
/* banco 5 di 16 caratteri 0x50 to 0x5F */ 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E,
/* banco 6 di 16 caratteri 0x60 to 0x6F */ 0x3E, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
/* banco 7 di 16 caratteri 0x70 to 0x7F */ 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
};



//CharArray CharMatrix[] = {
const _ROM char CharMatrix[0x40][8] = {
   {0xC1, 0xAE, 0xB6, 0xBA, 0xC1, 0xFF, 0xFF, 0xFF},  //	0x00 Code for char '0'		
   {0xFF, 0xBD, 0x80, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF},  //	0x01 Code for char '1'		
   {0xBD, 0x9E, 0xAE, 0xB6, 0xB9, 0xFF, 0xFF, 0xFF},  //	0x02 Code for char '2'		
   {0xDE, 0xBE, 0xBA, 0xB4, 0xCE, 0xFF, 0xFF, 0xFF},  // 0x03 Code for char '3'
   {0xE7, 0xEB, 0xED, 0x80, 0xEF, 0xFF, 0xFF, 0xFF},  // 0x04 Code for char '4'
   {0xD8, 0xBA, 0xBA, 0xBA, 0xC6, 0xFF, 0xFF, 0xFF},  // 0x05 Code for char '5'
   {0xC3, 0xB5, 0xB6, 0xB6, 0xCE, 0xFF, 0xFF, 0xFF},  // 0x06 Code for char '6'
   {0xFE, 0xFE, 0x86, 0xFA, 0xFC, 0xFF, 0xFF, 0xFF},  // 0x07 Code for char '7'
   {0xC9, 0xB6, 0xB6, 0xB6, 0xC9, 0xFF, 0xFF, 0xFF},  // 0x08 Code for char '8'
   {0xF9, 0xB6, 0xB6, 0xD6, 0xE1, 0xFF, 0xFF, 0xFF},  // 0x09 Code for char '9'
   {0x83, 0xED, 0xEE, 0xED, 0x83, 0xFF, 0xFF, 0xFF},  //	0x0A Code for char 'A'		
   {0x80, 0xB6, 0xB6, 0xB6, 0xC9, 0xFF, 0xFF, 0xFF},  //	0x0B Code for char 'B'		
   {0xC1, 0xBE, 0xBE, 0xBE, 0xDD, 0xFF, 0xFF, 0xFF},  //	0x0C Code for char 'C'		
   {0x80, 0xBE, 0xBE, 0xDD, 0xE3, 0xFF, 0xFF, 0xFF},  // 0x0D Code for char 'D'
   {0x80, 0xB6, 0xB6, 0xBE, 0xBE, 0xFF, 0xFF, 0xFF},  // 0x0E Code for char 'E'
   {0x80, 0xF6, 0xF6, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF},  // 0x0F Code for char 'F'
   {0xC1, 0xBE, 0xAE, 0xAE, 0x8D, 0xFF, 0xFF, 0xFF},  // 0x10 Code for char 'G'
   {0x80, 0xF7, 0xF7, 0xF7, 0x80, 0xFF, 0xFF, 0xFF},  // 0x11 Code for char 'H'
   {0xFF, 0xBE, 0x80, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF},  // 0x12 Code for char 'I'
   {0xDF, 0xBF, 0xBE, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF},  // 0x13 Code for char 'J'
   {0x80, 0xF7, 0xEB, 0xDD, 0xBE, 0xFF, 0xFF, 0xFF},  // 0x14 Code for char 'K'
   {0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xFF, 0xFF, 0xFF},  // 0x15 Code for char 'L'
   {0x80, 0xFD, 0xF3, 0xFD, 0x80, 0xFF, 0xFF, 0xFF},  // 0x16 Code for char 'M'
   {0x80, 0xFB, 0xF7, 0xEF, 0x80, 0xFF, 0xFF, 0xFF},  // 0x17 Code for char 'N'
   {0xC1, 0xBE, 0xBE, 0xBE, 0xC1, 0xFF, 0xFF, 0xFF},  // 0x18 Code for char 'O'
   {0x80, 0xF6, 0xF6, 0xF6, 0xF9, 0xFF, 0xFF, 0xFF},  // 0x19 Code for char 'P'
   {0xC1, 0xBE, 0xAE, 0xDE, 0xA1, 0xFF, 0xFF, 0xFF},  // 0x1A Code for char 'Q'
   {0x80, 0xF6, 0xE6, 0xD6, 0xB9, 0xFF, 0xFF, 0xFF},  // 0x1B Code for char 'R'
   {0xD9, 0xB6, 0xB6, 0xAE, 0xDD, 0xFF, 0xFF, 0xFF},  // 0x1C Code for char 'S'
   {0xFE, 0xFE, 0x80, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF},  // 0x1D Code for char 'T'
   {0xC0, 0xBF, 0xBF, 0xBF, 0xC0, 0xFF, 0xFF, 0xFF},  // 0x1E Code for char 'U'
   {0xE0, 0xDF, 0xBF, 0xDF, 0xE0, 0xFF, 0xFF, 0xFF},  // 0x1F Code for char 'V'
   {0x80, 0xDF, 0xE7, 0xDF, 0x80, 0xFF, 0xFF, 0xFF},  // 0x20 Code for char 'W'
   {0x9C, 0xEB, 0xF7, 0xEB, 0x9C, 0xFF, 0xFF, 0xFF},  // 0x21 Code for char 'X'
   {0xFC, 0xBB, 0x87, 0xBB, 0xFC, 0xFF, 0xFF, 0xFF},  // 0x22 Code for char 'Y'
   {0x9C, 0xAE, 0xB6, 0xBA, 0x9C, 0xFF, 0xFF, 0xFF},  // 0x23 Code for char 'Z'   
   {0xDF, 0xAB, 0xAB, 0xAB, 0x87, 0xFF, 0xFF, 0xFF},  // 0x24 Code for char 'a'
   {0xC0, 0xB7, 0xBB, 0xBB, 0xC7, 0xFF, 0xFF, 0xFF},  // 0x25 Code for char 'b'
   {0xC7, 0xBB, 0xBB, 0xBB, 0xDF, 0xFF, 0xFF, 0xFF},  // 0x26 Code for char 'c'
   {0xC7, 0xBB, 0xBB, 0xB7, 0x80, 0xFF, 0xFF, 0xFF},  // 0x27 Code for char 'd'
   {0xC7, 0xAB, 0xAB, 0xAB, 0xF7, 0xFF, 0xFF, 0xFF},  // 0x28 Code for char 'e'
   {0xFF, 0xF7, 0x81, 0xF6, 0xFD, 0xFF, 0xFF, 0xFF},  // 0x29 Code for char 'f'
   {0xF7, 0xAB, 0xAB, 0xAB, 0xC3, 0xFF, 0xFF, 0xFF},  // 0x2A Code for char 'g'
   {0x80, 0xF7, 0xFB, 0xFB, 0x87, 0xFF, 0xFF, 0xFF},  // 0x2B Code for char 'h'
   {0xFF, 0xBB, 0x82, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF},  // 0x2C Code for char 'i'
   {0xDF, 0xBF, 0xBF, 0xC2, 0xFF, 0xFF, 0xFF, 0xFF},  // 0x2D Code for char 'j'
   {0xFF, 0x80, 0xEF, 0xD7, 0xB9, 0xFF, 0xFF, 0xFF},  // 0x2E Code for char 'k'
   {0xFF, 0xBE, 0x80, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF},  // 0x2F Code for char 'l'
   {0x83, 0xFB, 0x87, 0xFB, 0x87, 0xFF, 0xFF, 0xFF},  // 0x30 Code for char 'm'
   {0x83, 0xF7, 0xFB, 0xFB, 0x87, 0xFF, 0xFF, 0xFF},  // 0x31 Code for char 'n'
   {0xC7, 0xBB, 0xBB, 0xBB, 0xC7, 0xFF, 0xFF, 0xFF},  // 0x32 Code for char 'o'
   {0x83, 0xEB, 0xEB, 0xEB, 0xF7, 0xFF, 0xFF, 0xFF},  // 0x33 Code for char 'p'
   {0xF7, 0xEB, 0xEB, 0xEB, 0x83, 0xFF, 0xFF, 0xFF},  // 0x34 Code for char 'q'
   {0xFF, 0x83, 0xF7, 0xFB, 0xFB, 0xFF, 0xFF, 0xFF},  // 0x35 Code for char 'r'
   {0xB7, 0xAB, 0xAB, 0xAB, 0xDB, 0xFF, 0xFF, 0xFF},  // 0x36 Code for char 's'
   {0xFF, 0xFB, 0xC1, 0xBB, 0xDF, 0xFF, 0xFF, 0xFF},  // 0x37 Code for char 't'
   {0xC3, 0xBF, 0xBF, 0xDF, 0x83, 0xFF, 0xFF, 0xFF},  // 0x38 Code for char 'u'
   {0xE3, 0xDF, 0xBF, 0xDF, 0xE3, 0xFF, 0xFF, 0xFF},  // 0x39 Code for char 'v'
   {0xC3, 0xBF, 0xCF, 0xBF, 0xC3, 0xFF, 0xFF, 0xFF},  // 0x3A Code for char 'w'
   {0xBB, 0xDB, 0xC7, 0xB7, 0xBB, 0xFF, 0xFF, 0xFF},  // 0x3B Code for char 'x'
   {0xBB, 0xB7, 0xCF, 0xEF, 0xF3, 0xFF, 0xFF, 0xFF},  // 0x3C Code for char 'y'
   {0xBB, 0x9B, 0xAB, 0xB3, 0xBB, 0xFF, 0xFF, 0xFF},  // 0x3D Code for char 'z'
   {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // 0x3E Code for char ' '
   {0xF7, 0xF7, 0xC1, 0xF7, 0xF7, 0xFF, 0xFF, 0xFF},  // 0x3F Code for char '+'
};

/*
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char  
        0xFF, 0xFF, 0xA0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char !

        0xE3, 0xDD, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char (
        0xFF, 0xFF, 0xBE, 0xDD, 0xE3, 0xFF, 0xFF, 0xFF,  // Code for char )

        0xFF, 0x99, 0x99, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char :
        0xFF, 0xA9, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char ;
        0xFF, 0xF7, 0xEB, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char <
        0xFF, 0xEB, 0xEB, 0xEB, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char =
        0xFF, 0xDD, 0xEB, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char >
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ?
        0xCD, 0xB6, 0x86, 0xBE, 0xC1, 0xFF, 0xFF, 0xFF,  // Code for char @


        0xFF, 0xFF, 0xBE, 0xBE, 0x80, 0xFF, 0xFF, 0xFF,  // Code for char [
        0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0xFF, 0xFF, 0xFF,  // Code for char BackSlash
        0xFF, 0x80, 0xBE, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char ]
        0xFB, 0xFD, 0xFE, 0xFD, 0xFB, 0xFF, 0xFF, 0xFF,  // Code for char ^
        0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xFF, 0xFF, 0xFF,  // Code for char _
        0xFF, 0xFA, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char `

        0xF7, 0xC9, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char {
        0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // Code for char |
        0xFF, 0xFF, 0xBE, 0xC9, 0xF7, 0xFF, 0xFF, 0xFF,  // Code for char }
        0xF7, 0xFB, 0xF7, 0xEF, 0xF7, 0xFF, 0xFF, 0xFF,  // Code for char ~


*/



void GLcdSet (char pin_cs_rs_rw, char data)
{
   unsigned char i;
   // set low Enable pin  - Waiting Time Twh = 450/550 ns
   GLCD_Pin_E = 0; i=GLCD_DELAY_550ns; while(i>0){i--;}
   
   // set Instruction and Data pin - Waiting Time Tasu,Tdsu = 140 ns
   PORTB &= 0xF0; PORTB |= (pin_cs_rs_rw & 0x0F); PORTD = data; i=GLCD_DELAY_140ns; while(i>0){i--;}

   // set low Enable pin - Waiting Time Twh = 450/550 ns
   GLCD_Pin_E = 1; i=GLCD_DELAY_550ns; while(i>0){i--;}; GLCD_Pin_E = 0;
}


void glcdInitPorts (void)
{
   unsigned char i;
 
   // By default port are analog input, to read digital port it must set these port to digital port 
   // Di default le porte sono input analogici, per leggere le porte digitali si devono impostare queste porte come porte digitali
   GLCD_CMD_ANSEL    &= 0xC0;
   GLCD_DATA_ANSEL   = 0;

   // set OUT following ports
   GLCD_CMD_TRIS     &= 0xC0;    // PORT D <0.5> 
   GLCD_DATA_TRIS    = 0;        // PORT D <0.7> (all)
   
 
   // init ports value
   GLCD_CMD_PORT     &= 0xC0;
   GLCD_DATA_PORT    = 0;

   // ritardo iniziale
   i=GLCD_DELAY_5us; while(i>0){i--;}
   
   // set reset pin high
   GLCD_Pin_RST      = 1;   
   
   GLcdSet (GLCD_CDM_ADDR_ON_OFF_ALL_ON, GLCD_DATA_CMD_ON_OFF|GLCD_ON);
   
}

void glcdWriteCmd (char pin_cs_rs_rw, char pin_data)
{
   unsigned char i;
/*
   MPU Write Timing
   
                                 tC
                        |-------------------|
                            tWL       tWH
                        |---------|---------|
   Enable pin        ---|_________|---------|_________|----------
   R/W pin              ----|_________________|-------------------|
   CS1, CS2, RS pin     ====|=================|===================|
   Data pin             ====|=================|===================|
                            |_____|         |_|
                               |             |
                             tASU           tAH
                             tDSU           tDHW                
                              
*/   
   
   // set Enable pin low - Waiting Time tWL = 450/550 ns
//   GLCD_Pin_E = 0; i=GLCD_DELAY_550ns; while(i>0){i--;}; {_asm nop _endasm}
   GLCD_Pin_E = 0; GLCD_DELAY_NOP_450ns

   // set Instruction and Data pin - Waiting Time tASU, tDSU = 140 ns
//   GLCD_CMD_PORT &= 0xF0; GLCD_CMD_PORT |= (pin_cs_rs_rw & 0x0F); GLCD_DATA_PORT = pin_data; i=GLCD_DELAY_140ns; while(i>0){i--;}
   GLCD_CMD_PORT &= 0xF0; GLCD_CMD_PORT |= (pin_cs_rs_rw & 0x0F); GLCD_DATA_PORT = pin_data; GLCD_DELAY_NOP_140ns;

   // set Enable pin high - Waiting Time tWH = 450/550 ns - set Enable pin low 
//   GLCD_Pin_E = 1; i=GLCD_DELAY_550ns; while(i>0){i--;}; GLCD_Pin_E = 0;
   GLCD_Pin_E = 1; GLCD_DELAY_NOP_550ns; GLCD_Pin_E = 0;
}


void glcdUpdateX (void)
{
   char cs;
   char glcd_x;
   
   
   // update X coordinate
   glcdX++;

   // set global variable
   glcdX &= 0x0F;
   
   // setup X coordinate
   cs = glcdX & 0x08;
   glcd_x = (glcdX & 0x07)*8;

   if((glcdX == 0) || (glcdX == 0x08))
   {
      if(cs != 0)
      {
         glcdWriteCmd (GLCD_CDM_ADDR_ON_OFF_CS2_ON, GLCD_DATA_CMD_SET_ADD_Y|glcd_x);
         glcdWriteCmd (GLCD_CDM_ADDR_ON_OFF_CS2_ON, GLCD_DATA_CMD_SET_ADD_X|glcdY);
      }
      else
      {
         glcdWriteCmd (GLCD_CDM_ADDR_ON_OFF_CS1_ON, GLCD_DATA_CMD_SET_ADD_Y|glcd_x);
         glcdWriteCmd (GLCD_CDM_ADDR_ON_OFF_CS1_ON, GLCD_DATA_CMD_SET_ADD_X|glcdY);
      }
   }
   
   // analisys X coordinate
   (cs == 0) ? (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS1_ON) : (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS2_ON);
}

void glcdSetXY				(char x, char y)
{
   char cs;
   char glcd_x;
   
   // set global variable
   glcdX = x;
   glcdY = y & 0x07;
   
   // limit X coordinate
   glcdX &= 0x0F;
   
   // setup X coordinate
   cs = glcdX & 0x08;
   glcd_x = (glcdX & 0x07)*8;
   
   // analisys X coordinate to select the correct CS
   (cs == 0) ? (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS1_ON) : (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS2_ON);
         
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_Y|glcd_x);
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_X|y);
//   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_Z|0);   
}

void glcdChXY				(char x, char y, char ch)
{
   char i, valore, cs;
   char glcd_x;

   // set global variable
   glcdX = x;
   glcdY = y & 0x07;
   
   // limit X coordinate
   glcdX &= 0x0F;
   
   // setup X coordinate
   cs = glcdX & 0x08;
   glcd_x = (glcdX & 0x07)*8;
   
   // analisys X coordinate to select the correct CS
   (cs == 0) ? (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS1_ON) : (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS2_ON);
      
   // set coordinates
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_Y|glcd_x);
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_X|y);
   //glcdWriteCmd (glcdADDR_CS_sel, GLCD_DATA_CMD_SET_ADD_Z|0);
   
   valore = AsciiToCustom [ch];
   
   for(i=0;i<8;i++)
   {
      glcdWriteCmd (GLCD_CMD_DATA_WRITE_ALL_ON | glcdCS_sel, CharMatrix[valore][i]);      
   }
   
   // update X coordinate
   glcdUpdateX();
   
}

void glcdStrXY				(char x, char y, char *str)
{
   char i, valore, cs;
   char glcd_x;

   // set global variable
   glcdX = x;
   glcdY = y & 0x07;
   
   // limit X coordinate
   glcdX &= 0x0F;
   
   // setup X coordinate
   cs = glcdX & 0x08;
   glcd_x = (glcdX & 0x07)*8;
   
   // analisys X coordinate to select the correct CS
   (cs == 0) ? (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS1_ON) : (glcdCS_sel = GLCD_CDM_ADDR_ON_OFF_CS2_ON);
      
   // set coordinates
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_Y|glcd_x);
   glcdWriteCmd (glcdCS_sel, GLCD_DATA_CMD_SET_ADD_X|y);
   //glcdWriteCmd (glcdADDR_CS_sel, GLCD_DATA_CMD_SET_ADD_Z|0);
      
   // write string
   while (*str>0)
   {
      valore = AsciiToCustom [*str];
      str++;
      
      // write character
      for(i=0;i<8;i++)
      {
         glcdWriteCmd (GLCD_CMD_DATA_WRITE_ALL_ON | glcdCS_sel, CharMatrix[valore][i]);
      }
      
      // update X coordinate
      glcdUpdateX();   
   }   
}

void glcdCh				(char ch)
{
   char i, valore;
      
   valore = AsciiToCustom [ch];
   
   for(i=0;i<8;i++)
   {
//      glcdWriteCmd (GLCD_CMD_DATA_WRITE_CS1_ON, CharMatrix[ch].ch[i]);
      glcdWriteCmd (GLCD_CMD_DATA_WRITE_ALL_ON | glcdCS_sel, CharMatrix[valore][i]);
   }

   // update X coordinate
   glcdUpdateX();
}


void glcdStr				(char *str)
{
   char i, valore;
         
   while (*str>0)
   {
      valore = AsciiToCustom [*str];
      str++;
      
      for(i=0;i<8;i++)
      {
         glcdWriteCmd (GLCD_CMD_DATA_WRITE_ALL_ON | glcdCS_sel, CharMatrix[valore][i]);
      }
      
      // update X coordinate
      glcdUpdateX();
   }
   
}

