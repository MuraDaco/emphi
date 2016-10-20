/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/uiPage.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define _UI_PAGE_C

#include "msPlatform.h"


#include "krEventGlo.h"
#include "krEvent.h"

#include "uiBaseGlo.h"
#include "uiPageGlo.h"

#include "rs2Lcd.h"

//unsigned char TestChar;
char TestChar;
// Puntatore alla lista delle istanze del modulo corrente
_ROM PageElementoStruct        *PtrPageIstanzaElemento;
// Puntatore alla lista degli elementi
_ROM PageListaElementiStruct   *PtrPageListaElemento;
// Puntatore alla lista dei tipi di elementi: forse non necessario
_ROM BaseElementoStruct        *PtrPageBaseElemento;
// Questa variabile va in parallelo al puntatore alla lista degli elementi 'PtrPageListaElemento'
// ?tato introdotto per poter discriminare la situazione di 'nessun elemento selezionato'
char PageListElementId;


void uiPageSelect (char a, char b, char c, char d)
{
   
}

void uiPageEventNull (void)
{
//   TestChar++;
//
//   LcdCh('0'+(TestChar&0x07));   
//   LcdNumberRC(3,15,TestChar);
   
}

void _page_elimina_elementi		(void)
{

   BaseElemento[EL_VAR].Elimina();

//   char i;
//
//   // 1.1. Loop degli elementi della lista
//   for(i=0;i<PtrPageIstanzaElemento->list_element_number;i++)
//   {
//      // 1.1.1. imposta il tipo di elemento
//      PtrPageBaseElemento = BaseElemento + PageListaElementi[PtrPageIstanzaElemento->list_element_id_start + i].tipo_elemento;
//      // 1.1.2. esegui la funzione Elimina 
//      PtrPageBaseElemento->Elimina();
//   }
}

void uiPageInitLight		(char element_id)
{
   char i;
   _ROM PageListaElementiStruct   *ptr_page_lista_elemento;
//   _ROM BaseElementoStruct        *ptr_base_elemento;

   // 0.1. Inizializza il puntatore dell'istanza della pagina corrente
   PtrPageIstanzaElemento = PageElemento + element_id;   
   // 0.2. inizializza l'id alla lista elementi in modo che non figuri nessun elemento selezionato
   PageListElementId = 0;
   
   // 1. visualizza tutti gli elementi
   // 1.0. Inizializza il puntatore alla lista degli elementi
   ptr_page_lista_elemento =  &PageListaElementi[PtrPageIstanzaElemento->list_element_id_start];
   // 1.1. Loop degli elementi della lista
   for(i=0;i<PtrPageIstanzaElemento->list_element_number;i++)
   {
      // 1.1.1. imposta il tipo di elemento
      PtrPageBaseElemento = BaseElemento + ptr_page_lista_elemento->tipo_elemento;
      // 1.1.2. esegui la funzione Visualizza 
      // 1.1.2.1. relativa al tipo di elemento selezionato 
      // 1.1.2.2. indicando l'id e 
      // 1.1.2.3. le sue coordinate
      PtrPageBaseElemento->Visualizza(ptr_page_lista_elemento->id_elemento, ptr_page_lista_elemento->coordinate);
      // 1.1.3. aggiorna il puntatore alla lista degli elementi
      ptr_page_lista_elemento++;
   }

   
//    LcdNumberRC(4, 0,PtrPageIstanzaElemento->list_element_number);
//    LcdNumberRC(4, 5,PtrPageIstanzaElemento->list_element_id_start);
//    LcdNumberRC(4,10,ptr_page_lista_elemento->tipo_elemento);
//    LcdNumberRC(4,15,ptr_page_lista_elemento->id_elemento);
//    
//    LcdNumberRC(3,0,ptr_page_lista_elemento->coordinate.o_row);
//    LcdNumberRC(3,5,ptr_page_lista_elemento->coordinate.o_col);
//    
//    
//       PtrPageBaseElemento = BaseElemento + ptr_page_lista_elemento->tipo_elemento;
//       PtrPageBaseElemento->Visualizza(ptr_page_lista_elemento->id_elemento, ptr_page_lista_elemento->coordinate);
// //      ptr_base_elemento   = BaseElemento + ptr_page_lista_elemento->tipo_elemento;
// //      PtrPageBaseElemento = &BaseElemento[ptr_page_lista_elemento->tipo_elemento];
// //      PtrPageBaseElemento->Deselect();
// //      BaseElemento[ptr_page_lista_elemento->tipo_elemento].Visualizza(ptr_page_lista_elemento->id_elemento, 2,0,0);
// //      (BaseElemento[0].Visualizza)(ptr_page_lista_elemento->id_elemento, 2,0,0);
// //      (BaseElemento[0].EventOn)(0);
// //      (BaseElemento[0].Deselect)();
// //      (BaseElemento[0].Deselect)();
// //      (BaseElemento[0].Deselect)();
// //      (BaseElemento[0].Deselect)();
// //      (BaseElemento[0].Deselect)();
// //      (BaseElemento[0].Select)(0,0,0,0);
//       uiPageSelect(0,0,0,0);
}


void uiPageEventButtonsDown      (void)
{
   // 1.1. Situazione: nessuna selezione
   // 1.1.1. Impostare PtrPageListaElemento al primo elemento
   // 1.1.2. Impostare PtrPageBaseElemento
   // 1.1.3. Incrementa PageListElementId   
   // 1.2. Situazione: selezionato uno degli elementi eccetto l'ultimo
   // 1.2.1. Deseleziona elemento corrente
   // 1.2.2. Incrementare PtrPageListaElemento
   // 1.2.3. Impostare PtrPageBaseElemento
   // 1.2.4. Incrementa PageListElementId   
   // 1.3. Situazione: selezionato l'ultimo elemento
   // 1.3.1. Deseleziona elemento corrente
   // 1.3.2. Imposta PageListElementId = 0
   
   // 1. Controlla situazione
   if(PageListElementId == 0)
   {
      // 1.1.0. Situazione: nessuna selezione
      // 1.1.1. Inizializza il puntatore della lista al primo elemento
      PtrPageListaElemento =  &PageListaElementi[PtrPageIstanzaElemento->list_element_id_start];
   }
   else
   {
      // 1.2.0. Situazione: selezionato uno degli elementi
      // 1.2.1. Deseleziona l'elemento selezionato
      PtrPageBaseElemento->Deselect();
      // 1.2.2. Controlla situazione
      if(PageListElementId == PtrPageIstanzaElemento->list_element_number)
      {
         // 1.2.2.1. Situazione: selezionato l'ultimo elemento
         // 1.2.2.2. Azzera l'id della lista, questo siginifica che non sar?elezionato nessun elemento
         PageListElementId = 0;
         return;
      }
      else
      {
         // 1.2.2.3. Situazione: selezionato un elemento eccetto l'ultimo
         // 1.2.3.4. Aggiorna il puntatore alla lista degli elementi
         PtrPageListaElemento++;
      }
   }
   
   // 2. Aggiorna i puntatori alle strutture per il nuovo elemento selezionato
   PtrPageBaseElemento = BaseElemento + PtrPageListaElemento->tipo_elemento;
   // 3. Chiama la funzione di selezione dell'elemento
   PtrPageBaseElemento->Select(PtrPageListaElemento->id_elemento,PtrPageListaElemento->coordinate);
   // 4. Aggiorna l'id della lista 
   PageListElementId++;
      
}

void uiPageEventButtonsUp    (void)
{
   // 1.1. Situazione: nessuna selezione
   // 1.1.1. Impostare PtrPageListaElemento all'ultimo elemento
   // 1.1.2. Impostare PtrPageBaseElemento
   // 1.1.2. Impostare PageListElementId = indice ultimo elemento
   // 1.2. Situazione: selezionato uno degli elementi eccetto il primo
   // 1.2.1. Deseleziona elemento corrente
   // 1.2.2. Decrementa PageListElementId   
   // 1.2.4. Decrementa PtrPageListaElemento
   // 1.2.4. Impostare PtrPageBaseElemento
   // 1.3. Situazione: selezionato il primo elemento
   // 1.3.1. Deseleziona elemento corrente
   // 1.3.2. Decrementa PageListElementId   
   
   // 1. Controlla situazione
   if(PageListElementId == 0)
   {
      // 1.1.0. Situazione: nessuna selezione
      // 1.1.1. Inizializza il puntatore della lista all'ultimo elemento
      PtrPageListaElemento =  &PageListaElementi[PtrPageIstanzaElemento->list_element_id_start + PtrPageIstanzaElemento->list_element_number - 1];
      // 1.1.2. Aggiorna l'id della lista in modo che figuri l'ultimo elemento
      PageListElementId = PtrPageIstanzaElemento->list_element_number;
   }
   else
   {
      // 1.2.0. Situazione: selezionato uno degli elementi
      // 1.2.1. Deseleziona l'elemento selezionato
      PtrPageBaseElemento->Deselect();
      // 1.2.2. Aggiorna l'id della lista
      PageListElementId--;
      // 1.2.3. Controlla situazione
      if(PageListElementId == 0)
      {
         // 1.2.3.1. Situazione: selezionato il primo elemento
         // non fare niente, esci
         // N.B.: il puntatore alla lista degli elementi verr?mpostata al prossimo evento
         return;
      }
      else
      {
         // 1.2.3.2. Situazione: selezionato un elemento eccetto il primo
         // 1.2.3.3. Aggiorna il puntatore alla lista elementi
         PtrPageListaElemento--;
      }
   }
   
   // 2. Aggiorna i puntatori alle strutture per il nuovo elemento selezionato
   PtrPageBaseElemento = BaseElemento + PtrPageListaElemento->tipo_elemento;
   // 3. Chiama la funzione di selezione dell'elemento
   PtrPageBaseElemento->Select(PtrPageListaElemento->id_elemento,PtrPageListaElemento->coordinate);
      
}

void uiPageEventButtonsEnter   (void)
{
   // controlla se qualche elemento ?tato selezionato
   if(PageListElementId > 0)
   {
      // attiva la tabella eventi dell'elemento selezionato
      (PtrPageBaseElemento->EventOn)(EL_PAGE);
   }
}

void uiPageEventButtonsRight   (void)
{
   _page_elimina_elementi();
   // cambia pagina
   uiPageInitLight(PtrPageIstanzaElemento->page_next_id);
}

void uiPageEventButtonsLeft    (void)
{
   _page_elimina_elementi();
   // cambia pagina
   uiPageInitLight(PtrPageIstanzaElemento->page_prev_id);
}


_ROM EventTableDef uiPageEvent[NUMBER_EVENT_BUTTONS] = {
    uiPageEventButtonsRight      //    EVENT_BUTTONS_RIGHT     0
   ,uiPageEventButtonsUp         //    EVENT_BUTTONS_UP        1
   ,uiPageEventButtonsEnter      //    EVENT_BUTTONS_ENTER     2
   ,uiPageEventButtonsDown       //    EVENT_BUTTONS_DOWN      3
   ,uiPageEventButtonsLeft       //    EVENT_BUTTONS_LEFT      4
};                               //    NUMBER_EVENT_BUTTONS    5


void uiPageInitCold				(void)
{   
   // imposta tabella eventi
   ButtonsEventMatrix[0].EventTable = uiPageEvent;   
}

void uiPageEventOn	      (unsigned char father_id)
{
   ButtonsEventMatrix[0].EventTable = uiPageEvent;
}




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

/* Variabili per Test Funzioni LCD
char TestChar;

char Display;
char Cursor;
char Blinking;

unsigned char DisplayShift;
unsigned char DirectionShift;
unsigned char EntryModeShift;
unsigned char EntryModeDisplay;
*/

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


// gestire la tabella delle transizioni tra pagine
// gestire le tabelle evento e le eventuali relative istanze
// gestire gli elementi contenuti nella pagina

/* Test Funzioni LCD

ram char strEntryModeDisplay[2][5] = {
//  12345678901234567890   
   "EMCu",
   "EMDi"
};

ram char strEntryModeDirection[2][5] = {
//  12345678901234567890   
   "EMLf",
   "EMRg"
};

ram char strDispCurShift[2][3] = {
//  1234 5678901234567890   
   "Cu",
   "Di"
};

ram char strDispCurDir[2][3] = {
//  12345678901234567890   
   "Lf",
   "Rg"
};


void VisualizzaStato (void)
{
   LcdDisplayReset();
   
   (EntryModeDisplay > 1)?(EntryModeDisplay = 1):(EntryModeDisplay = EntryModeDisplay);
   (EntryModeShift > 1)?(EntryModeShift = 1):(EntryModeShift = EntryModeShift);
   (DisplayShift > 1)?(DisplayShift = 1):(DisplayShift = DisplayShift);   
   (DirectionShift > 1)?(DirectionShift = 1):(DirectionShift = DirectionShift);    

   (EntryModeDisplay == 0)?(LcdEntryModeCursor()):(LcdEntryModeDisplay());
   (EntryModeShift == 0)?(LcdEntryModeLeftShift()):(LcdEntryModeRightShift());
//   (DisplayShift == 0)?(LcdCursorShift()):(LcdDisplayShift());
//   (DirectionShift == 0)?(LcdLeftShift()):(LcdRightShift());
   
   LcdStrRC(1, 8,strEntryModeDisplay    [EntryModeDisplay]);
   LcdStrRC(2, 8,strEntryModeDirection  [EntryModeShift]);
   LcdStrRC(3, 8,strDispCurShift        [DisplayShift]);
   LcdStrRC(3,10,strDispCurDir          [DirectionShift]);
   
   LcdSetPosition(4,9);
   LcdCh('9');
   
}

//void uiPageInit1(void)
//{
//   // reset del display
//   LcdDisplayReset();
//}

void EventoRight0  (void)
{

   (Display == 0)?(Display=1):(Display=0);      
   (Display == 0)?(LcdDisplayOff()):(LcdDisplayOn());
   
} 

void EventoUp0     (void)
{
//   LcdSetPosition(4,10);
//   LcdCh('0');
//   LcdCh('U');   
   
   TestChar++;
   TestChar &= 0x07;

   LcdCh('0'+TestChar);
   
   
} 

void EventoEnter0   (void)
{
   // reset del display
   
  
   // imposta la pagina successiva (TabellaTransizioniPage)
   ProcessTable[PROCESS_BUTTONS].EventTable = EventPage1;

   // inizializza pagina successiva
//   uiPageInit1();
   LcdDisplayReset();
     
   VisualizzaStato();
} 

void EventoDown0   (void)
{
   LcdSetPosition(4,10);
   LcdCh('0');
   LcdCh('D');   
   
   (Cursor == 0)?(Cursor=1):(Cursor=0);      
   (Cursor == 0)?(LcdCursorOff()):(LcdCursorOn());

} 

void EventoLeft0   (void)
{
   LcdSetPosition(4,10);
   LcdCh('0');
   LcdCh('L');   
   
   (Blinking == 0)?(Blinking=1):(Blinking=0);      
   (Blinking == 0)?(LcdBlinkingOff()):(LcdBlinkingOn());
   
} 

// *****************************************************************************


void EventoRight1  (void)
{
//   ram char str[21];

//   LcdSetPosition(4,10);
//   LcdCh('1');
//   LcdCh('R');   
   
   (DisplayShift == 0)?(DisplayShift=1):(DisplayShift=0);      
   (DisplayShift == 0)?(LcdCursorShift()):(LcdDisplayShift());
//   VisualizzaStato();
   

} 

void EventoUp1     (void)
{
//   LcdSetPosition(4,10);
//   LcdCh('1');
//   LcdCh('U');   
   
   TestChar++;
   TestChar &= 0x07;

   LcdCh('0'+TestChar);
   
} 

void EventoEnter1   (void)
{
   // imposta la pagina successiva
   // TabellaTransizioniPage
   ProcessTable[PROCESS_BUTTONS].EventTable = EventPage0;
  
   // inizializza pagina successiva
   LcdDisplayReset();

   
   (EntryModeDisplay == 0)?(EntryModeDisplay=1):(EntryModeDisplay=0);      

   VisualizzaStato();
   
   
} 

void EventoDown1   (void)
{
//   LcdSetPosition(4,10);
//   LcdCh('1');
//   LcdCh('D');   

   (DirectionShift == 0)?(DirectionShift=1):(DirectionShift=0);      
   (DirectionShift == 0)?(LcdLeftShift()):(LcdRightShift());
//   VisualizzaStato();
   
} 

void EventoLeft1   (void)
{
//   LcdSetPosition(4,10);
//   LcdCh('1');
//   LcdCh('L');
   
   (EntryModeShift == 0)?(EntryModeShift=1):(EntryModeShift=0);      
   VisualizzaStato();
   
   
} 

*/


