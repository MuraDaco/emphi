/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 310 $																											
   *	LAST DATE REVISION:     $Date: 2015-12-08 17:39:10 +0100 (mar, 08 dic 2015) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/Def.c $			
   *																																						
   ****************************************************************************************************************************************************

 */


// #define _PIC_OLD_COMPILER

#ifndef _PLATFORM_H
#define _PLATFORM_H


#ifdef _PIC_OLD_COMPILER
    #define _ROM rom
#else
    #define _ROM const
#endif

#define _CONST const

#endif		// _PLATFORM_H
