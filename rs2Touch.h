/*
   touch.h
   
   Description / Descrizione:
   Driver to handle the resistive touch screen with 4 wire
   Driver per gestire il touch ecreen resistivo a 4 fili
	
   Documentation / Documentazione
	

   
   Author:
   Marco Dau

   Creation Date:
   Tuesday, 17 March 2015
   
   Update:
   
	**** Notes on Friday the 26 June 2015 ****
	
	01 - Reading coordinates
		. set Drive ?
		. read and print adc buffer value
		.. read mean copy adc buffer value in X coordinate global variable
		
	02 - the reading has to be put in the loop but there has to be syncronasing with set drive
	
	. acquisition
	.. set drive
	.. read adc value
	
	. check situation
	.. no touch
	... like before
	.... don't anything
	... different from before, that means screen was pressed
	.... clear value on screen
	.. screen has been pressed
	... print value
	
	there would has to be a syncronasing between check touch and adc reading
	i would make a parallel computing to have modulare code or to avoid spaghetti code
	
	to do this there is need of a data structure to share between vary application module like temperature sensor or resitive touch screen
	
	how to share the resorse between application module
	. resource is adc
	. apps module is
	.. touch screen
	.. sensor temperature
	
	to do this we need of a reading state variable
	. adcAppStateReading = 1 means that there is a new reading
	
	how to manage this state variable:
	. it sets to 1 from adc
	. it sets to 0 from App Module
	
	A question: is it sufficent to use one only state variable for all n-app module or it has to use tante state variable quante are App module?
	
	A possible answer: it is possible to use only one state variable if its use is sequential
	Another possible answer: it can use a semaphore variable specific for resource module and one state variable for the App Mudule
	. adcAppStateReading
	. adcAppSemaphore
	. touch_adc_state

	How to manage these variable
	. adcAppStateReading
	... it sets to 1 from adc
	... it sets to 0 from App Module
	. adcAppSemaphore
	... it sets to 1 and/or 0 from App Module
	. touch_adcState
	... it permit to know at next loop if the adc resource is been to use by me 
	
	at the end this state variable is a semaphore between concurrent process
	
	the reading is valid only for specifc situation 
	
	Possible scenario
	1. Sequential
	....a) set drive A
	....a.1) wait
	....b) select adc channel
	....b.1) start adc
	....c) wait for adc
	
	....a) set drive B
	....a.1) wait
	....b) select adc channel
	....b.1) start adc
	....c) wait for adc
	
	2. Parallel
	....a) adc Process
	....a.1) there are two possibility
	....a.1.1) app module set channel
	....a.1.2) app module don't set channel so every cycle loop there is a new channel to acquire
	....b) touch Process
	....b.1) First cycle loop
	....b.1.1) set drive
	....b.1.2) set adc channel if possible
	....b.1.3) clear adcAppStateReading
	....b.2) Second cycle loop
	....b.2.1) if set channel
	....b.2.1.1) check adcAppStateReading, 
	....b.2.1.1.1) 1 means new value, in this case it is possible release adc resource clearing adcAppSemaphore
	....b.2.1.1.2) 0 means old value in this case it has to wait another cycle loop
	....b.2.2) if no set channel
	....b.2.1.1) in this case it has to wait NUMBER_ADC_CHANNEL cycle loop but it is best to check the adc update cycle
	....b.2.1.1.1) in this case it has to add another adc state variable to know if the channel of interest has been acquire 	
	
	. UNDERSTAND WELL the adc interrupt function modality
	... the adc interrupt is activated onfly after the go_done bit is set to 1?
	..... Verify this situation
	
	
	....c) sensor Temperature Process
	
   
*/

/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 357 $																											
   *	LAST DATE REVISION:     $Date: 2016-05-05 19:38:30 +0200 (gio, 05 mag 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2Touch.h $			
   *																																						
   ****************************************************************************************************************************************************

 */

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



#ifndef _TOUCH_H
#define _TOUCH_H


// char touchX, touchY;
#ifdef _MAIN_C
void touchInit (void);
#endif

#ifdef _PROCESS_TABLE_C
char ControlloTouch0 (char);
#endif

#ifdef _TIMER_TABLE_C
void TouchTimer 		(void);
#endif

// void touchCheckLoopParallel (void)

#endif	// _TOUCH_H