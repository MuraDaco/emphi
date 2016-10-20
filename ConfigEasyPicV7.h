/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 324 $																											
   *	LAST DATE REVISION:     $Date: 2016-01-18 18:50:40 +0100 (lun, 18 gen 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/ConfigEasyPicV7.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

#ifndef _CONFIG_EASY_PIC_V7_H
#define _CONFIG_EASY_PIC_V7_H

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

// Per attivare la define _CONFIG_EASY_PIC_V7_LCD 
// Configurazione switch della scheda di sviluppo 
// switch1: 0x00
// switch2: 0x00
// switch3: 0x00
// switch4: 0x30 - sw4.5, sw4.6 (la numerazione va da 1 a 8)
#define	_CONFIG_EASY_PIC_V7_LCD
//#undef	_CONFIG_EASY_PIC_V7_LCD

// Per attivare la define _CONFIG_EASY_PIC_V7_GRAPHIC_LCD 
// Configurazione switch della scheda di sviluppo 
// switch1: 0x00
// switch2: 0x00
// switch3: 0x00
// switch4: 0x30 - sw4.5, sw4.6 (la numerazione va da 1 a 8)
//#define	_CONFIG_EASY_PIC_V7_GRAPHIC_LCD
#undef	_CONFIG_EASY_PIC_V7_GRAPHIC_LCD

// Per attivare la define _CONFIG_EASY_PIC_V7_TOUCH 
// Configurazione switch della scheda di sviluppo 
// switch1: 0x00
// switch2: 0x00
// switch3: 0xF0 - da sw3.5 a sw3.8
// switch4: 0x00
//#define	_CONFIG_EASY_PIC_V7_TOUCH
#undef	_CONFIG_EASY_PIC_V7_TOUCH

// impostazione costanti dipendenti dalla configurazione
#if defined(_CONFIG_EASY_PIC_V7_GRAPHIC_LCD)
	#if defined(_CONFIG_EASY_PIC_V7_TOUCH)
	// #define	NUMERO_EVENTI_INIT 6
	#undef	NUMERO_EVENTI_INIT
	#else
	// #define	NUMERO_EVENTI_INIT 5
	#undef	NUMERO_EVENTI_INIT
	#endif
#elif defined(_CONFIG_EASY_PIC_V7_LCD)
#define	NUMERO_EVENTI_INIT 7
#endif


// controllo conflitti tra le configurazioni
#if defined(_CONFIG_EASY_PIC_V7_LCD) && defined(_CONFIG_EASY_PIC_V7_GRAPHIC_LCD)
#error "--- Non possono coesistere le definizione di LCD e GRAPHIC_LCD ---"
#elif defined(_CONFIG_EASY_PIC_V7_LCD) && defined(_CONFIG_EASY_PIC_V7_TOUCH)
#error "--- Non possono coesistere le definizione di LCD e TOUCH ---"
#elif !defined(_CONFIG_EASY_PIC_V7_GRAPHIC_LCD) && defined(_CONFIG_EASY_PIC_V7_TOUCH)
#error "--- Non può essere definito TOUCH senza definire anche GRAPHIC_LCD ---"
#endif

 
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

#endif		//		_CONFIG_EASY_PIC_V7_H
