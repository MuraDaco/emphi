/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 370 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-10 16:12:43 +0200 (mer, 10 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/uiApplication.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define _UI_APPLICATION_C

#include "msPlatform.h"

// definizione delle costanti presenti nella definizione dei paramteri
#include "uiParDisplayGlo.h"

// definizione dei parametri modificabili
#include "ui_GeneralEdt.h"
#include "ui_fnThermostatEdt.h"

// definizione delle variabili visualizzabili
#include "ui_rs2ButtonsDsp.h"
#include "ui_fnThermostatDsp.h"


// definizione delle strutture e costanti dei componenti grafici
#include "uiPageGlo.h"
#include "uiLboxGlo.h"
#include "uiParGlo.h"
#include "uiVarGlo.h"
#include "uiStrGlo.h"







// SEZIONE - TABELLE MODULI

// MODULO STR

#define  ID_STR_WEB_SITE				                    0x00
#define  ID_STR_E_MAIL					                    0x01
#define  ID_STR_PHONE					                    0x02
#define  ID_STR_PAGE_HOME       	                       0x03
#define  ID_STR_PAGE_SETTINGS_A 	                       0x04
#define  ID_STR_PAGE_SETTINGS_B 	                       0x05
#define  ID_STR_PAGE_INFO    	                          0x06
#define  ID_STR_PAR_TERMOSTATO_SETPOINT			        0x07
#define  ID_STR_PAR_TERMOSTATO_SETPOINT_MIN	           0x08
#define  ID_STR_PAR_TERMOSTATO_SETPOINT_MAX	           0x09
#define  ID_STR_PAR_TERMOSTATO_DELTA				        0x0A
#define  ID_STR_PAR_TERMOSTATO_TEMPO_MINUTI	           0x0B
#define  ID_STR_PAR_TERMOSTATO_TEMPO_SECONDI	           0x0C
#define  ID_STR_PAR_GENERAL_LANGUAGE                    0x0D
#define  ID_STR_VAR_TERMOSTATO_TEMPERATURA	           0x0E
#define  ID_STR_VAR_TERMOSTATO_UMIDITA				        0x0F
#define  ID_STR_VAR_RS2_BUTTONS_TIMES_PRESSED			  0x10
#define  NUMERO_STR_ELEMENTI        				        0x11

_ROM StringTipoItem StrElemento[NUMERO_STR_ELEMENTI] = {
//   English                 Italiano
//    123456789012345        123456789012345
    {"www.emphil.com "     ,"www.emphil.com "}        // ID_STR_WEB_SITE				                    0x00    
   ,{"info@emphil.com"     ,"info@emphil.com"}        // ID_STR_E_MAIL					                    0x01    
   ,{"  xxx-aa.bb.cc "     ,"  xxx-aa.bb.cc "}        // ID_STR_PHONE					                    0x02    
   ,{"Home           "     ,"Principale     "}        // ID_STR_PAGE_HOME       	                       0x03    
   ,{"Settings A     "     ,"Parmetri A     "}        // ID_STR_PAGE_SETTINGS_A 	                       0x04    
   ,{"Settings B     "     ,"Parmetri B     "}        // ID_STR_PAGE_SETTINGS_B 	                       0x05    
   ,{"Info           "     ,"Info           "}        // ID_STR_PAGE_INFO    	                          0x06    
   ,{"Setpoin:       "     ,"Setpoint       "}        // ID_STR_PAR_TERMOSTATO_SETPOINT			        0x07    
   ,{"Setpoint min:  "     ,"Setpoint min:  "}        // ID_STR_PAR_TERMOSTATO_SETPOINT_MIN	           0x08    
   ,{"Setpoint max:  "     ,"Setpoint max:  "}        // ID_STR_PAR_TERMOSTATO_SETPOINT_MAX	           0x09    
   ,{"Delta:         "     ,"Delta:         "}        // ID_STR_PAR_TERMOSTATO_DELTA				        0x0A    
   ,{"Time minutes:  "     ,"Tempo Minuti:  "}        // ID_STR_PAR_TERMOSTATO_TEMPO_MINUTI	           0x0B    
   ,{"Time seconds:  "     ,"Tempo Secondi: "}        // ID_STR_PAR_TERMOSTATO_TEMPO_SECONDI	           0x0C    
   ,{"Language       "     ,"Lingua         "}        // ID_STR_PAR_GENERAL_LANGUAGE				        0x0D    
   ,{"Temperature:   "     ,"Temperatura    "}        // ID_STR_VAR_TERMOSTATO_TEMPERATURA	           0x0E    
   ,{"Humidity       "     ,"Umidita        "}        // ID_STR_VAR_TERMOSTATO_UMIDITA				        0x0F    
   ,{"TimesPressed   "     ,"Volte premuto  "}        // ID_STR_VAR_RS2_BUTTONS_TIMES_PRESSED			  0x10    
};

// MODULO VAR

// Definizione identificativi delle variabili di stato
#define  ID_VAR_TERMOSTATO_TEMPERATURA	   	      0
#define  ID_VAR_TERMOSTATO_UMIDITA				      1
#define  ID_VAR_RS2_BUTTONS_TIMES_PRESSED				2
#define  NUMERO_VAR_ELEMENTI                       3

// Definizione tabella
_ROM VarElementoStruct VarElemento[NUMERO_VAR_ELEMENTI] = {
    ROW_VAR_TERMOSTATO_TEMPERATURA     // ID_VAR_TERMOSTATO_TEMPERATURA             0   
   ,ROW_VAR_TERMOSTATO_UMIDITA         // ID_VAR_TERMOSTATO_UMIDITA                 1   
   ,ROW_VAR_RS2_BUTTONS_TIMES_PRESSED  // ID_VAR_RS2_BUTTONS_TIMES_PRESSED				2
};   

// MODULO PAR

// Definizione identificativi dei parametri
#define  ID_PAR_TERMOSTATO_SETPOINT		            0
#define  ID_PAR_TERMOSTATO_SETPOINT_MIN	         1
#define  ID_PAR_TERMOSTATO_SETPOINT_MAX	         2
#define  ID_PAR_TERMOSTATO_DELTA			            3
#define  ID_PAR_TERMOSTATO_TEMPO_MINUTI            4
#define  ID_PAR_TERMOSTATO_TEMPO_SECONDI           5
#define  ID_PAR_GENERAL_LANGUAGE                   6
#define  NUMERO_PAR_ELEMENTI                       7

// Definizione tabella
_ROM ParElementoStruct ParElemento[NUMERO_PAR_ELEMENTI] = {
    ROW_PAR_TERMOSTATO_SETPOINT		   // ID_PAR_TERMOSTATO_SETPOINT		         0      
   ,ROW_PAR_TERMOSTATO_SETPOINT_MIN	   // ID_PAR_TERMOSTATO_SETPOINT_MIN	      1      
   ,ROW_PAR_TERMOSTATO_SETPOINT_MAX	   // ID_PAR_TERMOSTATO_SETPOINT_MAX	      2      
   ,ROW_PAR_TERMOSTATO_DELTA			   // ID_PAR_TERMOSTATO_DELTA			         3      
   ,ROW_PAR_TERMOSTATO_TEMPO_MINUTI    // ID_PAR_TERMOSTATO_TEMPO_MINUTI         4      	
   ,ROW_PAR_TERMOSTATO_TEMPO_SECONDI   // ID_PAR_TERMOSTATO_TEMPO_SECONDI        5      	
   ,ROW_PAR_GENERAL_LANGUAGE	         // ID_PAR_GENERAL_LANGUAGE                6      
};   


// MODULO LBOX

// Definizione identificativi degli elementi presenti negli "lbox"
#define  ID_LBOX_ELEMENT_0                          0
#define  ID_LBOX_ELEMENT_1                          1
#define  ID_LBOX_ELEMENT_2                          2
#define  ID_LBOX_ELEMENT_3                          3
#define  ID_LBOX_ELEMENT_4                          4
#define  ID_LBOX_ELEMENT_5                          5
#define  ID_LBOX_ELEMENT_6                          6
#define  ID_LBOX_ELEMENT_7                          7
#define  ID_LBOX_ELEMENT_8                          8
#define  NUMERO_LBOX_LISTA_ELEMENTI                 9
// -------------------------------------------------                                                   

// Definizione identificativi dei list box
#define	ID_LBOX_TST_1						0
#define	ID_LBOX_TST_2						1
#define	ID_LBOX_TST_3				      2
#define	ID_LBOX_TST_4				      3
#define  NUMERO_LBOX_ELEMENTI          4

// Definizione tabella
_ROM LboxElementoStruct LboxElemento[NUMERO_LBOX_ELEMENTI] = {
//	   dimensione (numero righe)	,Id_Start_lista_elementi	,numero_elementi
    {	2							      ,ID_LBOX_ELEMENT_2	      ,4	               }  //	ID_LBOX_TST_1						0	 
   ,{	1							      ,ID_LBOX_ELEMENT_1	      ,3	               }  //	ID_LBOX_TST_2						1	 	
   ,{	3							      ,ID_LBOX_ELEMENT_0      	,6	               }  //	ID_LBOX_TST_3	   	   		2	 	
   ,{	2							      ,ID_LBOX_ELEMENT_3         ,3	               }  //	ID_LBOX_TST_4  	   			3	 	
};


// MODULO PAGE

// -------------------------------------------------------------------------

// Definizione identificativi degli elementi presenti nelle "pagine"
#define  ID_PAGE_ELEMENT_0_HOME                     0	
#define  ID_PAGE_ELEMENT_1_HOME                     1	
#define  ID_PAGE_ELEMENT_2_SETT_A                   2	
#define  ID_PAGE_ELEMENT_3_SETT_A                   3	
#define  ID_PAGE_ELEMENT_4_SETT_B                   4	
#define  ID_PAGE_ELEMENT_5_INFO                     5
#define  ID_PAGE_ELEMENT_6_INFO                     6
#define  ID_PAGE_ELEMENT_7_INFO                     7
#define  NUMERO_PAGE_LISTA_ELEMENTI                 8
  
// Definizione identificativi delle pagine         
#define  ID_PAGE_HOME			         0
#define  ID_PAGE_SETTINGS_A	         1
#define  ID_PAGE_SETTINGS_B	         2
#define  ID_PAGE_INFO			         3
#define  NUNERO_PAGE_ELEMENTI          4


// Definizione tabella
_ROM PageElementoStruct	PageElemento[NUNERO_PAGE_ELEMENTI] = {
//	   Titolo		   	      ,Id_Start_lista_elementi   ,numero_elementi  ,IdPrevNext             ,IdPageNext
    {	ID_STR_PAGE_HOME       	,ID_PAGE_ELEMENT_0_HOME    ,2       		   ,ID_PAGE_SETTINGS_A     ,ID_PAGE_SETTINGS_A  }	//	ID_PAGE_HOME				0	
   ,{	ID_STR_PAGE_SETTINGS_A 	,ID_PAGE_ELEMENT_2_SETT_A  ,2       		   ,ID_PAGE_HOME           ,ID_PAGE_HOME        }	//	ID_PAGE_SETTINGS_A		1	
   ,{	ID_STR_PAGE_SETTINGS_B 	,ID_PAGE_ELEMENT_4_SETT_B  ,1       		   ,ID_PAGE_SETTINGS_A     ,ID_PAGE_INFO        }	//	ID_PAGE_SETTINGS_B		2			
   ,{	ID_STR_PAGE_INFO    	   ,ID_PAGE_ELEMENT_5_INFO	   ,3       		   ,ID_PAGE_SETTINGS_B     ,ID_PAGE_HOME        }	//	ID_PAGE_INFO				3				
};


// SEZIONE - TABELLE DELLE LISTE ELEMENTI DEI MODULI PAGE E LBOX

// 
_ROM LboxListaElementiStruct LboxListaElementi[NUMERO_LBOX_LISTA_ELEMENTI] = {
//    IdParametro				               ,TipoElemento (Label, EditBox)
// ---------------------------------------------------------------------------------------------   
	 {	ID_PAR_TERMOSTATO_SETPOINT	   		,EL_PAR  }     // ID_LBOX_ELEMENT_0                0  
	,{	ID_PAR_TERMOSTATO_SETPOINT_MIN		,EL_PAR  }     // ID_LBOX_ELEMENT_1                1  
	,{	ID_PAR_TERMOSTATO_SETPOINT_MAX		,EL_PAR  }     // ID_LBOX_ELEMENT_2                2  
	,{	ID_PAR_TERMOSTATO_DELTA     			,EL_PAR  }     // ID_LBOX_ELEMENT_3                3  
	,{	ID_PAR_TERMOSTATO_TEMPO_MINUTI		,EL_PAR  }     // ID_LBOX_ELEMENT_4                4  
	,{	ID_PAR_TERMOSTATO_TEMPO_SECONDI		,EL_PAR  }     // ID_LBOX_ELEMENT_5                5  
// ---------------------------------------------------------------------------------------------   
// ---------------------------------------------------------------------------------------------   
	,{	ID_VAR_TERMOSTATO_TEMPERATURA	   	,EL_VAR  }     // ID_LBOX_ELEMENT_6                6  
	,{	ID_VAR_TERMOSTATO_UMIDITA				,EL_VAR  }     // ID_LBOX_ELEMENT_7                7  
	,{	ID_PAR_GENERAL_LANGUAGE 				,EL_PAR  }     // ID_LBOX_ELEMENT_8                8  
// ---------------------------------------------------------------------------------------------   
};


// 
_ROM PageListaElementiStruct	PageListaElementi[NUMERO_PAGE_LISTA_ELEMENTI] = {
//    IdElemento     					   ,TipoElemento	,Pos:Row			,Pos:Column		Dim:Width		
// -------------------------------------------------------------------------------------------------------------------------      
    {	ID_PAR_TERMOSTATO_SETPOINT_MIN	,EL_PAR			,{1			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_0_HOME   
   ,{	ID_LBOX_TST_3     				   ,EL_LBOX			,{2			   ,1		         ,0}	}     // ID_PAGE_ELEMENT_1_HOME   
// -------------------------------------------------------------------------------------------------------------------------      
// -------------------------------------------------------------------------------------------------------------------------      
   ,{	ID_VAR_RS2_BUTTONS_TIMES_PRESSED ,EL_VAR			,{1			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_2_SETT_A   
//   ,{	ID_PAR_TERMOSTATO_DELTA          ,EL_PAR			,{1			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_0_HOME   
   ,{	ID_LBOX_TST_4     				   ,EL_LBOX			,{2			   ,1		         ,0}	}     // ID_PAGE_ELEMENT_3_SETT_A 
// -------------------------------------------------------------------------------------------------------------------------      
// -------------------------------------------------------------------------------------------------------------------------      
   ,{	ID_LBOX_TST_3     				   ,EL_LBOX			,{2			   ,1		         ,0}	}     // ID_PAGE_ELEMENT_4_SETT_B 
// -------------------------------------------------------------------------------------------------------------------------      
// -------------------------------------------------------------------------------------------------------------------------      
   ,{	ID_STR_WEB_SITE					   ,EL_STR			,{2			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_5_INFO   
   ,{	ID_STR_E_MAIL						   ,EL_STR			,{3			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_6_INFO   
   ,{	ID_STR_PHONE						   ,EL_STR			,{4			   ,0		         ,0}	}     // ID_PAGE_ELEMENT_7_INFO   
// -------------------------------------------------------------------------------------------------------------------------      
};


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

