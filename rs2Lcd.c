/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/rs2Lcd.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define _LCD_C

#include "msPlatform.h"

// ----------------------------------------------------------------------------
// SECTION - SYSTEM INCLUDE

#include <p18f45k22.h>


// SECTION END
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SECTION - PROJECT INCLUDE (Dependecies)

#include "krTimerGlo.h"


// SECTION END
// ----------------------------------------------------------------------------

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - CONSTANT DEFINITION

// attendi altri 39us circa (39000ns / 125ns) = 312 cicli di clock // esegui 312 cicli
#define     DELAY_37us        20
#define     DELAY_39us        40 // OK 200

#define     LCD_COLUMN     20
#define     LCD_ROW        4

#define		LCD_DELAY_NOP_50ns		asm("nop");
#define		LCD_DELAY_NOP_150ns		asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); 

// RAM e DISPLAY
// entry mode agisce quando si scrive nella ram
// il cursor_display_shift agisce al momento che viene dato il comando 
// RAM  rimane ferma si sposta il display

#define  LCD_INSTRUCTION_CLEAR_DISPLAY             0x01
#define  LCD_INSTRUCTION_RETURN_HOME               0x02
#define  LI_CLEAR_DISPLAY                                         LCD_INSTRUCTION_CLEAR_DISPLAY
#define  LI_RETURN_HOME                                           LCD_INSTRUCTION_RETURN_HOME

#define  LCD_INSTRUCTION_ENTRY_MODE                0x04
#define  _SHIFT_RIGHT                              0x02
#define  _SHIFT_LEFT                               0x00
#define  _DISPLAY_MOVED_AND_CURSOR_FIXED           0x01
#define  _DISPLAY_FIXED_AND_CURSOR_MOVED           0x00
#define  LI_DISPLAY_MOVED_RIGHT_AND_CURSOR_FIXED                  LCD_INSTRUCTION_ENTRY_MODE | _DISPLAY_MOVED_AND_CURSOR_FIXED | _SHIFT_RIGHT
#define  LI_DISPLAY_MOVED_LEFT_AND_CURSOR_FIXED                   LCD_INSTRUCTION_ENTRY_MODE | _DISPLAY_MOVED_AND_CURSOR_FIXED | _SHIFT_LEFT
#define  LI_DISPLAY_FIXED_AND_CURSOR_MOVED_RIGHT                  LCD_INSTRUCTION_ENTRY_MODE | _DISPLAY_FIXED_AND_CURSOR_MOVED | _SHIFT_RIGHT
#define  LI_DISPLAY_FIXED_AND_CURSOR_SHIFT_LEFT                   LCD_INSTRUCTION_ENTRY_MODE | _DISPLAY_FIXED_AND_CURSOR_MOVED | _SHIFT_LEFT
#define  LI_DEFAULT_ENTRY_MODE                     LI_DISPLAY_FIXED_AND_CURSOR_MOVED_RIGHT

#define  LCD_INSTRUCTION_ON_OFF_CONTROL            0x08
#define  _DISPLAY_ON                               0x04
#define  _DISPLAY_OFF                              ~_DISPLAY_ON
#define  _CURSOR_ON                                0x02
#define  _CURSOR_OFF                               ~_CURSOR_ON
#define  _BLINKING_ON                              0x01
#define  _BLINKING_OFF                             ~_BLINKING_ON
#define  LI_DISPLAY_ON_CURSOR_ON_BLINKING_ON                      LCD_INSTRUCTION_ON_OFF_CONTROL | _DISPLAY_ON | _CURSOR_ON | _BLINKING_ON
#define  LI_DISPLAY_ON_CURSOR_ON                                  LCD_INSTRUCTION_ON_OFF_CONTROL | _DISPLAY_ON | _CURSOR_ON
#define  LI_DISPLAY_ON_BLINKING_ON                                LCD_INSTRUCTION_ON_OFF_CONTROL | _DISPLAY_ON | _BLINKING_ON
#define  LI_DISPLAY_ON                                            LCD_INSTRUCTION_ON_OFF_CONTROL | _DISPLAY_ON
#define  LI_DEFAULT_ON_OFF_CONTROL                 LI_DISPLAY_ON

#define  LCD_INSTRUCTION_DISPLAY_CURSOR_SHIFT      0x10
#define  _DISPLAY_SHIFT                            0x08
#define  _CURSOR_SHIFT                             0x00
#define  _DIRECTION_RIGHT                          0x04
#define  _DIRECTION_LEFT                           0x00
#define  LI_DISPLAY_SHIFT_DIRECTION_RIGHT                         LCD_INSTRUCTION_DISPLAY_CURSOR_SHIFT | _DISPLAY_SHIFT | _DIRECTION_RIGHT
#define  LI_DISPLAY_SHIFT_DIRECTION_LEFT                          LCD_INSTRUCTION_DISPLAY_CURSOR_SHIFT | _DISPLAY_SHIFT | _DIRECTION_LEFT
#define  LI_CURSOR_SHIFT_DIRECTION_RIGHT                          LCD_INSTRUCTION_DISPLAY_CURSOR_SHIFT | _CURSOR_SHIFT  | _DIRECTION_RIGHT
#define  LI_CURSOR_SHIFT_DIRECTION_LEFT                           LCD_INSTRUCTION_DISPLAY_CURSOR_SHIFT | _CURSOR_SHIFT  | _DIRECTION_LEFT
#define  LI_DEFAULT_DISPLAY_CURSOR_SHIFT           LI_CURSOR_SHIFT_DIRECTION_RIGHT


#define  LCD_INSTRUCTION_FUNCTION_SET              0x20
#define  _DATA_8BIT                                0x10
#define  _DATA_4BIT                                0x00
#define  _2_LINE                                   0x08
#define  _1_LINE                                   0x00
#define  _5X11_FONT                                0x04
#define  _5X08_FONT                                0x00
#define  LI_DATA_8BIT_2_LINE_5X11_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_8BIT | _2_LINE | _5X11_FONT
#define  LI_DATA_8BIT_2_LINE_5X08_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_8BIT | _2_LINE | _5X08_FONT
#define  LI_DATA_8BIT_1_LINE_5X11_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_8BIT | _1_LINE | _5X11_FONT
#define  LI_DATA_8BIT_1_LINE_5X08_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_8BIT | _1_LINE | _5X08_FONT
#define  LI_DATA_4BIT_2_LINE_5X11_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_4BIT | _2_LINE | _5X11_FONT
#define  LI_DATA_4BIT_2_LINE_5X08_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_4BIT | _2_LINE | _5X08_FONT
#define  LI_DATA_4BIT_1_LINE_5X11_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_4BIT | _1_LINE | _5X11_FONT
#define  LI_DATA_4BIT_1_LINE_5X08_FONT                            LCD_INSTRUCTION_FUNCTION_SET | _DATA_4BIT | _1_LINE | _5X08_FONT
#define  LI_DEFAULT_FUNCTION_SET                   LI_DATA_4BIT_2_LINE_5X11_FONT

#define _PROVA_DEF  (unsigned char) (0xFF | 0xAA)


// SECTION END
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SECTION - VARIABLE DEFINITION

unsigned char lcdStato;
unsigned char lcdDisplayCursorShift;
unsigned char lcdEntryMode;

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

void LcdRegInit   (void)
{

// Display alfanumerico
   // deselezionare analogic input per le porte in uso per poterle leggere 
   ANSELB &= 0xC0;
   // impostare in OUT le seguenti porte
   // PORT B <0.5>
   TRISB &= 0xC0;
   // azzera tutte le porte coinvolte di dati e di comandi
   // Descrizione
   // Linea dati:    RB<0.3>
   // RB3 <-> D7
   // RB2 <-> D6
   // RB1 <-> D5
   // RB0 <-> D4
   // ----------
   // Linea comandi: RB<4.5>
   // RB4 <-> RS
   // RB5 <-> Enable
   LATB &= 0xC0;

   // stato iniziale del display
   // Display acceso
   // cursore spento
   // cursore non lampeggiante
   lcdStato                = LI_DEFAULT_ON_OFF_CONTROL;
//   lcdStato                = _PROVA_DEF;
   lcdDisplayCursorShift   = LI_DEFAULT_DISPLAY_CURSOR_SHIFT;
   lcdEntryMode            = LI_DEFAULT_ENTRY_MODE;
}

void LcdInit1 (char nib)
{
   LATBbits.LATB5 = 1;
   // tempo di attesa non specificato
   LATB &= 0xF0; // azzera tutti i bit dei dati
   // tempo di attesa = il max tra (t_DSW = 40 ns) e (t_PW = 140 ns) // esegui un solo ciclo
//   LATB |= nib;      i=1; while(i>0){i--;}
   LATB |= nib;      // LCD_DELAY_NOP_50ns;   
   // disattiva Enable // tempo di attesa = (t_C = 1200 ns) // esegui 10 cicli
//   LATBbits.LATB5 = 0; i=10;while(i>0){i--;}   
   LATBbits.LATB5 = 0; LCD_DELAY_NOP_150ns;
}

/*  Nuovo */
void LcdCmd (char data)
{
   char i;

   LcdInit1((data>>4) & 0x0F);
   LcdInit1(data & 0x0F);

   i=DELAY_39us;while(i>0){i--;}
   
}

void LcdCmdCh (char data)
{
   LcdInit1((data>>4) & 0x0F);
   LcdInit1(data & 0x0F);
}

void LcdInit (void)
{
   char i;

//   int count;
   
   // inizializzazione delle porte
   LcdRegInit();

   // inizializzazione del display
   // 01-Aspettare almeno 40ms, facciamo 100ms
   Timer[TMR_LCD_INIT] = 50; // 50;
   while (Timer[TMR_LCD_INIT] > 0){LCD_DELAY_NOP_50ns}
   
   // 02-imposta il primo comando
   LcdInit1(0x03);
   i=DELAY_39us;while(i>0){i--;}
      
   // 03-imposta il secondo comando: 
   // Data Length: 4 bit           -> DL (bit 4)= 0
   // Number Display Line: 2 line  -> N  (bit 3)= 1
   // Display Font Type: 5x11 dots -> F  (bit 2)= 1
//   LcdCmd(0x2C);
   LcdCmd(LI_DEFAULT_FUNCTION_SET);
//   i=DELAY_39us;while(i>0){i--;}
   
   // 04-imposta di nuovo il comando precedente come da procedura del datasheet
   // Data Length: 4 bit           -> DL (bit 4)= 0
   // Number Display Line: 2 line  -> N  (bit 3)= 1
   // Display Font Type: 5x11 dots -> F  (bit F)= 1
//   LcdCmd(0x2C);
   LcdCmd(LI_DEFAULT_FUNCTION_SET);
   
//   i=DELAY_37us;while(i>0){i--;}
   
   // 05-imposta il comando di on/off
   // Set Display         -> D (bit 2)= 1
   // Set Cursor          -> C (bit 1)= 1 
   // Set Cursor Blinking -> B (bit 0)= 1
//   LcdCmd(lcdStato);
   LcdCmd(LI_DEFAULT_ON_OFF_CONTROL);
//   i=DELAY_37us;while(i>0){i--;}
   
   // 06-imposta il comando di clear display
//   LcdCmd(0x01);
   LcdCmd(LI_CLEAR_DISPLAY);
//   i=DELAY_1600us;while(i>0){i--;}
   Timer[TMR_LCD_INIT] = 4;
   while (Timer[TMR_LCD_INIT] > 0){LCD_DELAY_NOP_50ns}
   
   // 07-imposta il comando di entry mode set
   // Cursor Moving direction     -> I/D (bit 1) = 1 (increment scrittura da sinistra a destra) / 0 (decrement scrittura da destra a sinistra)
   // Enable Shift Entire display -> SH  (bit 0) = 1 (Shift attivo, il cursore rimane fermo e la scrittura scorre a dx o sx in base a bit I/D 
   // considerare che ?l display che si sposta ogni volta che scrivo un
   // carattere quindi quando impostero un indirizzo del display questo sara spostato) / 0 (no shift)
//   LcdCmd(0x06);
   LcdCmd(LI_DEFAULT_ENTRY_MODE);
   
//   i=DELAY_39us;while(i>0){i--;}
   
}

void LcdSetPosition(unsigned char row, unsigned char column)
{
   char data;

   // gli indirizzi delle righe 1 e 3 sono rappresentati dagli indirizzi con nib + alto da 0x80 e 0x0A 
   // gli indirizzi delle righe 2 e 4 sono rappresentati dagli indirizzi con nib + alto da 0xC0 e 0x0E 
   // controlla i limiti
   (column > LCD_COLUMN)?(column = LCD_COLUMN):(0);
   (row    > LCD_ROW)?(row    = LCD_ROW):(0);

   // se la riga ?aggiore di 2 allora alla colonna si dovra aggiungere l'offset della riga che la precede
   (row>2)?(column+=LCD_COLUMN):(0);
   // se la riga ?ispari nib_high = 0x08, se ?ari nib_high = 0x0C
   ((row&0x01)==1)?(row=0x08):(row=0x0C);
   row += (column>>4);
   column &= 0x0F;

   data = (row<<4) & 0xF0;
   data += column;
   
   LcdCmd(data);
//   i=DELAY_39us;while(i>0){i--;}
}

void LcdCh(char carattere)
{
   char i;

   LATBbits.LATB4 = 1;
   LcdCmdCh(carattere);
   LATBbits.LATB4 = 0;
   i=DELAY_39us;while(i>0){i--;}
}
/* */

void LcdStrRC  (unsigned char row,unsigned char column,char *str)
{
   LcdSetPosition(row,column);
   
   // write string
   while (*str>0)
   {
      LcdCh(*str);
      str++;
   }   
   
}

void LcdRomStrRC  (unsigned char row,unsigned char column,const _ROM char *str)
{
   LcdSetPosition(row,column);
   
   // write string
   while (*str>0)
   {
      LcdCh(*str);
      str++;
   }   
   
}

void LcdNumberRC  (unsigned char row,unsigned char column,unsigned char par)
{
//   char par;
   unsigned char num[4];
   char i;
   
   LcdSetPosition(row,column);
   
//   par = *ptr_par;
   num[3] = 0;
   num[2] = par%10;
   num[1] = (par/10)%10;
   num[0] = par/100;
   
   
   // write string
   for(i=0;i<3;i++)
   {
      LcdCh('0'+num[i]);
   }   
   
}

void LcdDisplayReset (void)
{
   LcdCmd(LI_CLEAR_DISPLAY);
   Timer[TMR_LCD_INIT] = 4;
   while (Timer[TMR_LCD_INIT] > 0){LCD_DELAY_NOP_50ns}
}

void LcdDisplayOff (void)
{
   lcdStato &= _DISPLAY_OFF;
   LcdCmd(lcdStato);
}
void LcdDisplayOn (void)
{
   lcdStato |= _DISPLAY_ON;
   LcdCmd(lcdStato);
}

void LcdCursorOff (void)
{
   lcdStato &= _CURSOR_OFF;
   LcdCmd(lcdStato);
}
void LcdCursorOn (void)
{
   lcdStato |= _CURSOR_ON;
   LcdCmd(lcdStato);
}

void LcdBlinkingOff (void)
{
   lcdStato &= _BLINKING_OFF;
   LcdCmd(lcdStato);
}
void LcdBlinkingOn (void)
{
   lcdStato |= _BLINKING_ON;
   LcdCmd(lcdStato);
}

void LcdDisplayShift (void)
{
   lcdDisplayCursorShift |= _DISPLAY_SHIFT;
   LcdCmd(lcdDisplayCursorShift);
}
void LcdCursorShift (void)
{
   lcdDisplayCursorShift &= ~_DISPLAY_SHIFT;
   LcdCmd(lcdDisplayCursorShift);
}

void LcdRightShift (void)
{
   lcdDisplayCursorShift |= _DIRECTION_RIGHT;
   LcdCmd(lcdDisplayCursorShift);
}
void LcdLeftShift (void)
{
   lcdDisplayCursorShift &= ~_DIRECTION_RIGHT;
   LcdCmd(lcdDisplayCursorShift);
}

void LcdEntryModeRightShift (void)
{
   lcdEntryMode |= _SHIFT_RIGHT;
   LcdCmd(lcdEntryMode);
}
void LcdEntryModeLeftShift (void)
{
   lcdEntryMode &= ~_SHIFT_RIGHT;
   LcdCmd(lcdEntryMode);
}

void LcdEntryModeDisplay (void)
{
   lcdEntryMode |= _DISPLAY_MOVED_AND_CURSOR_FIXED;
   LcdCmd(lcdEntryMode);
}
void LcdEntryModeCursor (void)
{
   lcdEntryMode &= ~_DISPLAY_MOVED_AND_CURSOR_FIXED;
   LcdCmd(lcdEntryMode);
}
