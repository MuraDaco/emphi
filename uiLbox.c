/*

   MODULE DESCRIPTION:  

   AUTHOR:  Marco Ing. Dau		 																									

   ****************************************************************************************************************************************************
   * SVN-keywords: fields managed by SVN - DO NOT MODIFY 
   *
   *	USER who run commit:    $Author: Administrator $																										
   *	REVISION NUMBER:        $Revision: 371 $																											
   *	LAST DATE REVISION:     $Date: 2016-08-11 19:27:06 +0200 (gio, 11 ago 2016) $															
   *	LOCATION FILE:          $HeadURL: file:///C:/Users/Administrator/Documents/SVN/Repository/fw2/15101-emphil/work/uiLbox.c $			
   *																																						
   ****************************************************************************************************************************************************

 */

#define _UI_LBOX_C

#include "msPlatform.h"

#include "krEventGlo.h"
#include "krEvent.h"

#include "uiBaseGlo.h"
#include "uiLboxGlo.h"

#include "krTimerGlo.h"
#include "rs2Lcd.h"




// unsigned char LboxRow;
// unsigned char LboxCol;
// 
// char LboxFatherId;
// char LboxListElementId;
// char LboxWindowId;
// char wdIdAbsolute;
// char wdIdRelative;
// char wdIdStates;
// 
// _ROM LboxElementoStruct        *PtrLboxIstanzaElemento;
// _ROM LboxListaElementiStruct   *PtrLboxListaElemento;
// _ROM BaseElementoStruct        *PtrLboxBaseElemento;

typedef struct {
   BaseCoordinateStruct             coordinate;
   _ROM LboxElementoStruct          *PtrIstanzaElemento;
   _ROM BaseElementoStruct          *PtrLboxBaseElemento;

   char                             LboxFatherId;
   char                             LboxListElementId;
   char                             LboxWindowId;
   char                             wdIdAbsolute;
   char                             wdIdRelative;
   char                             wdIdStates;
   _ROM LboxListaElementiStruct     *PtrLboxListaElemento;
} LboxIstanzaDynStruct;

LboxIstanzaDynStruct uiLboxIstanzaDyn;

// uiLboxIstanzaDyn.coordinate.o_row
// uiLboxIstanzaDyn.coordinate.o_col
// uiLboxIstanzaDyn.PtrIstanzaElemento
// uiLboxIstanzaDyn.PtrParBaseElemento

//uiLboxIstanzaDyn.LboxFatherId;
//uiLboxIstanzaDyn.LboxListElementId
//uiLboxIstanzaDyn.LboxWindowId
//uiLboxIstanzaDyn.wdIdAbsolute
//uiLboxIstanzaDyn.wdIdRelative
//uiLboxIstanzaDyn.wdIdStates
//uiLboxIstanzaDyn.PtrLboxListaElemento



void  fbwIncAbsolute               (void);
void  fbwIncRelative               (void);
void  fbwDisplayWindowFromBot      (void);
void  fbwSetAbsoluteToLast         (void);
void  fbwDecAbsolute               (void);
void  fbwDecRelative               (void);
void  fbwDisplayWindowFromTop      (void);
void  fbwSetAbsoluteToFirst        (void);



#define  _NOTHING                      (unsigned char) 0x00
#define  _INC_ABSOLUTE                 (unsigned char) 0x01
#define  _INC_RELATIVE                 (unsigned char) 0x02
#define  _DISPLAY_WINDOW_FROM_BOT      (unsigned char) 0x04
#define  _SET_ABSOLUTE_TO_LAST         (unsigned char) 0x08
#define  _DEC_ABSOLUTE                 (unsigned char) 0x10
#define  _DEC_RELATIVE                 (unsigned char) 0x20
#define  _DISPLAY_WINDOW_FROM_TOP      (unsigned char) 0x40
#define  _SET_ABSOLUTE_TO_FIRST        (unsigned char) 0x80

#define  _PRIMO      0
#define  _MEZZO      1
#define  _ULTIMO     2

#define  _UP         0
#define  _DOWN       1


_ROM unsigned char wdButtonsTaskFlags[9][2] =
{
// Tasto UP                                        Tasto Down                                               // | Relatvio   Assoluto 
// ---------------------------------------------------------------------------------------------------------// +---------------------
    {_SET_ABSOLUTE_TO_LAST|_DISPLAY_WINDOW_FROM_TOP ,_INC_ABSOLUTE|_INC_RELATIVE                       }    // | PRIMO    | PRIMO    |                                                   
   ,{_SET_ABSOLUTE_TO_LAST|_DEC_RELATIVE            ,_INC_ABSOLUTE|_INC_RELATIVE                       }    // | MEZZO    | PRIMO    | Situazione possibile se attivo il buffer circolare
   ,{_SET_ABSOLUTE_TO_LAST|_DEC_RELATIVE            ,_INC_ABSOLUTE|_DISPLAY_WINDOW_FROM_BOT            }    // | ULTIMO   | PRIMO    | Situazione possibile se attivo il buffer circolare
   ,{_DEC_ABSOLUTE|_DISPLAY_WINDOW_FROM_TOP         ,_INC_ABSOLUTE|_INC_RELATIVE                       }    // | PRIMO    | MEZZO    |
   ,{_DEC_ABSOLUTE|_DEC_RELATIVE                    ,_INC_ABSOLUTE|_INC_RELATIVE                       }    // | MEZZO    | MEZZO    |
   ,{_DEC_ABSOLUTE|_DEC_RELATIVE                    ,_INC_ABSOLUTE|_DISPLAY_WINDOW_FROM_BOT            }    // | ULTIMO   | MEZZO    |
   ,{_DEC_ABSOLUTE|_DISPLAY_WINDOW_FROM_TOP         ,_SET_ABSOLUTE_TO_FIRST|_DEC_RELATIVE              }    // | PRIMO    | ULTIMO   | Situazione possibile se attivo il buffer circolare
   ,{_DEC_ABSOLUTE|_DEC_RELATIVE                    ,_SET_ABSOLUTE_TO_FIRST|_DEC_RELATIVE              }    // | MEZZO    | ULTIMO   | Situazione possibile se attivo il buffer circolare
   ,{_DEC_ABSOLUTE|_DEC_RELATIVE                    ,_SET_ABSOLUTE_TO_FIRST|_DISPLAY_WINDOW_FROM_BOT   }    // | ULTIMO   | ULTIMO   |
};

_ROM EventTableDef wdButtonsTaskFunctions[8] =
{
    fbwIncAbsolute               // _INC_ABSOLUTE                 0x01
   ,fbwIncRelative               // _INC_RELATIVE                 0x02
   ,fbwDisplayWindowFromBot      // _DISPLAY_WINDOW_FROM_BOT      0x04
   ,fbwSetAbsoluteToLast         // _SET_ABSOLUTE_TO_LAST         0x08
   ,fbwDecAbsolute               // _DEC_ABSOLUTE                 0x10
   ,fbwDecRelative               // _DEC_RELATIVE                 0x20
   ,fbwDisplayWindowFromTop      // _DISPLAY_WINDOW_FROM_TOP      0x40
   ,fbwSetAbsoluteToFirst        // _SET_ABSOLUTE_TO_FIRST        0x80
};

void _lbox_elimina_elementi  (void)
{
   char i;
   _ROM LboxListaElementiStruct   *ptr_lbox_lista_elemento;
   _ROM BaseElementoStruct        *ptr_lbox_base_elemento;
   
   ptr_lbox_lista_elemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start + uiLboxIstanzaDyn.LboxListElementId - 1];
   for(i=0;i<uiLboxIstanzaDyn.PtrIstanzaElemento->row_number;i++)
   {
      // elimina
      ptr_lbox_base_elemento = BaseElemento + ptr_lbox_lista_elemento->tipo_elemento;
      ptr_lbox_base_elemento->Elimina();
    
      ptr_lbox_lista_elemento++;

   }
   
}

/*

id_elemento
id_elemento_relativo = id_relativo
id_finestra

incremento id_elemento
. incremento id_relativo
.. se id_relativo era alla fine della finestra allora
... incrementa finestra e
... lascia inalterato id_relativo
.. se id_relativo non era alla fine della finestra
... lascia l'incremento id_relativo

. Controlla id_elemento
.. id_elemento ?'ultimo
... inizializza ptr_elemento al primo elemento della lista
.. id_elemento non ?'ultimo
... controlla id_elemento
.... id_elemento ?'ultimo elemento
..... 

. visualizza finestra a partire dall'ultimo elemento
. elementi coinvolti
.. id_elemento (che ?'ultimo)
.. id_elemento relativo alla finestra
.. numero di righe da visualizzare
. situazioni
.. selezionato ultimo elemento della finestra
.. selezionato primo elemento della finestra
. uso del id_relativo
.. ottenere le coordinate dell'elemento

. incremento indice
.. prima
... controllare
.... se id_elemento ?'ultimo
..... id_elemento ?ltimo -> no fare niente
..... id_elemento NON ?ltimo
...... controllare
....... se id_realtivo ?ltimo
........ id_relativo ?ltimo
......... incrementa 

. flusso di programma
.. acquisire lo stato degli indici
.. esegui incremento

. stato del sistema
.. ?'unione degli stati dei due indici elemento quello assoluto e quello relativo
... elemento_assoluto
... elemento_relativo
.. i possibili valori dei due indici sono
... elemento PRIMO
... elemento MEZZO
... elemento ULTIMO
.. possibili coppie sono
Relatvio  Assoluto |                                            | Tasto UP        | Tasto Down
----------------------------------------------------------------------------------------------------
PRIMO   | PRIMO    | si                                         | non fare nulla; | F0001 -> F0010
MEZZO   | PRIMO    | possibile se implementata lista circolare  |                 |
ULTIMO  | PRIMO    | possibile se implementata lista circolare  |                 |
PRIMO   | MEZZO    | si                                         | F1001 -> F1100  | F0001 -> F0010
MEZZO   | MEZZO    | si                                         | F1001 -> F1010  | F0001 -> F0010
ULTIMO  | MEZZO    | si                                         | F1001 -> F1010  | F0001 -> F0100
PRIMO   | ULTIMO   | possibile se implementata lista circolare  |                 |
MEZZO   | ULTIMO   | possibile se implementata lista circolare  |                 |
ULTIMO  | ULTIMO   | si                                         | F1001 -> F1010  | non fare nulla;

F0000: non fare nulla
F0001: incrementa Assoluto
F0010: incrementa Relativo
F0100: visualizza la finestra partendo dal basso
F1001: decrementa Assoluto
F1010: decrementa Relativo
F1100: visualizza la finestra partendo dall'alto

void fbwNothing               (void)
{
   
}





void DisplayWindowFromTop  (void)
{
   _ROM LboxListaElementiStruct   *ptr_lbox_lista_elemento;
   _ROM BaseElementoStruct        *ptr_lbox_base_elemento;
   
   // 
   coordinate.o_row = LboxRow;
   coordinate.o_col = LboxCol;
   ptr_lbox_lista_elemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start + LboxListElementId];
   for(i=0;i<PtrLboxIstanzaElemento->row_number;i++)
   {
      //
      // imposta puntatori
      
      // visualizza
      ptr_lbox_base_elemento = BaseElemento + ptr_lbox_lista_elemento->tipo_elemento;
      ptr_lbox_base_elemento->Visualizza(ptr_lbox_lista_elemento->id_elemento,coordinate);
    
      coordinate.o_row++;
      ptr_lbox_lista_elemento++;
   }
      
}




void _tasto_up (void)
{
   
}


funzioni
. incrementa relativo
. incrementa assoluto
. rivisualizza finestra

Rivisualizza Finestra verso il basso
. l'indice assoluto corrisponde al primo elemento della finestra

Rivisualizza Finestra verso l'alto
. l'indice assoluto corrisponde all'ultimo elemento della finestra





*/

// Funzioni della tabella "wdButtonsTaskFunctions"
void fbwSetAbsoluteToLast     (void)
{
//   LboxListElementId    = PtrLboxIstanzaElemento->list_element_number - 1;
//   PtrLboxListaElemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start + LboxListElementId];
}

void fbwDecAbsolute           (void)
{
   // aggiorna id
   uiLboxIstanzaDyn.LboxListElementId--;

//   // aggiorna il puntatore alla lista
//   PtrLboxListaElemento--;
}

void fbwDecRelative           (void)
{
   uiLboxIstanzaDyn.LboxWindowId--;
}

void fbwDisplayWindowFromTop  (void)
{
   char i;
   BaseCoordinateStruct          coordinate;
   _ROM LboxListaElementiStruct   *ptr_lbox_lista_elemento;
   _ROM BaseElementoStruct        *ptr_lbox_base_elemento;

   _lbox_elimina_elementi();
   
   // Inizializza puntatori e coordinate dell'elemento -> InitPtrWindowElement(dir);
   coordinate.o_col = uiLboxIstanzaDyn.coordinate.o_col;
   coordinate.o_row = uiLboxIstanzaDyn.coordinate.o_row;
   ptr_lbox_lista_elemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start + uiLboxIstanzaDyn.LboxListElementId];
   for(i=0;i<uiLboxIstanzaDyn.PtrIstanzaElemento->row_number;i++)
   {
      // visualizza
      ptr_lbox_base_elemento = BaseElemento + ptr_lbox_lista_elemento->tipo_elemento;
      ptr_lbox_base_elemento->Visualizza(ptr_lbox_lista_elemento->id_elemento,coordinate);
    
      // Aggiorna puntatori e coordinate dell'elemento -> UpdatePtrWindowElement(dir);
      coordinate.o_row++;
      ptr_lbox_lista_elemento++;

//      // Il codice seguente viene eseguito se ?ttiva la gestione della lista circolare
//      // in particolare se sono attive le funzioni
//      // . fbwSetAbsoluteToFirst
//      // . fbwSetAbsoluteToLast
//      if((LboxListElementId+i) == (PtrLboxIstanzaElemento->list_element_number-1))
//      {
//         ptr_lbox_lista_elemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start];
//      }
   }
      
}

void fbwSetAbsoluteToFirst    (void)
{
//   LboxListElementId    = 0;
//   PtrLboxListaElemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start];   
}

void fbwIncAbsolute           (void)
{
   // aggiorna id
   uiLboxIstanzaDyn.LboxListElementId++;

//   // aggiorna il puntatore alla lista
//   PtrLboxListaElemento++;
}

void fbwIncRelative           (void)
{
   uiLboxIstanzaDyn.LboxWindowId++;
}

void fbwDisplayWindowFromBot  (void)
{
   char i;
   BaseCoordinateStruct          coordinate;
   _ROM LboxListaElementiStruct   *ptr_lbox_lista_elemento;
   _ROM BaseElementoStruct        *ptr_lbox_base_elemento;
   
   _lbox_elimina_elementi();
   
   // Inizializza puntatori e coordinate dell'elemento -> InitPtrWindowElement(dir);
   coordinate.o_col = uiLboxIstanzaDyn.coordinate.o_col;
   coordinate.o_row = uiLboxIstanzaDyn.coordinate.o_row + (uiLboxIstanzaDyn.PtrIstanzaElemento->row_number - 1);
   ptr_lbox_lista_elemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start + uiLboxIstanzaDyn.LboxListElementId];
   for(i=0;i<uiLboxIstanzaDyn.PtrIstanzaElemento->row_number;i++)
   {
      // visualizza
      ptr_lbox_base_elemento = BaseElemento + ptr_lbox_lista_elemento->tipo_elemento;
      ptr_lbox_base_elemento->Visualizza(ptr_lbox_lista_elemento->id_elemento,coordinate);
    
      // Aggiorna puntatori e coordinate dell'elemento -> UpdatePtrWindowElement(dir);
      coordinate.o_row--;
      ptr_lbox_lista_elemento--;
      
//      // Il codice seguente viene eseguito se ?ttiva la gestione della lista circolare
//      // in particolare se sono attive le funzioni
//      // . fbwSetAbsoluteToFirst
//      // . fbwSetAbsoluteToLast
//      if((LboxListElementId-i) == 0)
//      {
//         ptr_lbox_lista_elemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start + PtrLboxIstanzaElemento->list_element_number - 1];
//      }
   }

//   for(i=0;i<PtrLboxIstanzaElemento->row_number;i++)
//   {
//      // visualizza elemento lista
//      PtrLboxBaseElemento = BaseElemento + PtrLboxListaElemento->tipo_elemento;
//      PtrLboxBaseElemento->Visualizza(PtrLboxListaElemento->id_elemento, coordinate);
//
//      PtrLboxListaElemento++;
//      coordinate.o_row++;
//   }

   
}


// Funzioni per il controllo e aggiornamento dello stato degli indici della finestra
// queste funzioni sono chiamate dalle funzioni evento UP e DOWN
void wdSetIdState    (void)
{
   
   // inizializza il valore dello stato dell'indice assoluto
   uiLboxIstanzaDyn.wdIdAbsolute = _PRIMO;
   if(uiLboxIstanzaDyn.LboxListElementId)
   {
      uiLboxIstanzaDyn.wdIdAbsolute = _MEZZO;
      if(uiLboxIstanzaDyn.LboxListElementId == (uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_number-1))
      {
         uiLboxIstanzaDyn.wdIdAbsolute = _ULTIMO;
      }
   }

   // inizializza il valore dello stato dell'indice relativo
   uiLboxIstanzaDyn.wdIdRelative = _PRIMO;
   if(uiLboxIstanzaDyn.LboxWindowId)
   {
      uiLboxIstanzaDyn.wdIdRelative = _MEZZO;
      if(uiLboxIstanzaDyn.LboxWindowId == (uiLboxIstanzaDyn.PtrIstanzaElemento->row_number-1))
      {
         uiLboxIstanzaDyn.wdIdRelative = _ULTIMO;
      }
   }

   uiLboxIstanzaDyn.wdIdStates = uiLboxIstanzaDyn.wdIdRelative + 3*uiLboxIstanzaDyn.wdIdAbsolute;
}

char wdUpdate        (char tasto)
{
   char i;
   char flag, saved_flag;
   
   flag = wdButtonsTaskFlags[uiLboxIstanzaDyn.wdIdStates][tasto];
   saved_flag = flag;
   for(i=0;i<8;i++)
   {
      //
      if(flag&0x01)
      {
         // esegui funzione
         wdButtonsTaskFunctions[i]();
      }
      flag >>= 1;
   }
   
   // aggiorna puntatore alla lista elementi
   uiLboxIstanzaDyn.PtrLboxListaElemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start + uiLboxIstanzaDyn.LboxListElementId];
   
   return saved_flag;
}

void _cambia_selezione (char tasto)
{
   BaseCoordinateStruct coordinate;
   char flag_window, flag_select;
   char i;

   for(i=0;i<uiLboxIstanzaDyn.PtrIstanzaElemento->row_number;i++)
   {
      // deseleziona 
      uiLboxIstanzaDyn.PtrLboxBaseElemento->Deselect();
   
      // rileva lo stato degli indici e puntatori agli elementi
      wdSetIdState();
      
      // aggiorna lo stato della finestra e della lista degli elementi
      // lo stato della finestra ?aratterizzato da
      // - indice reltivo
      // - indice assoluto
      // - visualizzazione degli elementi
      // - puntatore all'elelmento della lista
      flag_window = wdUpdate(tasto);
      
      // seleziona elemento
      // aggiorna le coordinate dell'elemento selezionato
      coordinate.o_col = uiLboxIstanzaDyn.coordinate.o_col;
      coordinate.o_row = uiLboxIstanzaDyn.coordinate.o_row + uiLboxIstanzaDyn.LboxWindowId;
      // 2. Aggiorna i puntatori alle strutture per il nuovo elemento selezionato
      uiLboxIstanzaDyn.PtrLboxBaseElemento = BaseElemento + uiLboxIstanzaDyn.PtrLboxListaElemento->tipo_elemento;
      // 3. Chiama la funzione di selezione dell'elemento
      flag_select = uiLboxIstanzaDyn.PtrLboxBaseElemento->Select(uiLboxIstanzaDyn.PtrLboxListaElemento->id_elemento,coordinate);

      if(((((_DISPLAY_WINDOW_FROM_BOT|_DISPLAY_WINDOW_FROM_TOP) & flag_window) != 0) || (flag_select != 0)))
      {
         break;
      }
      
   }
   
}

// Funzioni eventi
void uiLboxEventButtonsUp      (void)
{
   _cambia_selezione(_UP);
   

}

void uiLboxEventButtonsDown    (void)
{

   _cambia_selezione(_DOWN);
   
   
}

void uiLboxEventButtonsEnter   (void)
{
//   // attiva la tabella eventi del elemento figlio
   uiLboxIstanzaDyn.PtrLboxBaseElemento->EventOn(EL_LBOX);   
}

void _esci     (void)
{
   // deseleziona elemento selezionato
   uiLboxIstanzaDyn.PtrLboxBaseElemento = BaseElemento + uiLboxIstanzaDyn.PtrLboxListaElemento->tipo_elemento;
   uiLboxIstanzaDyn.PtrLboxBaseElemento->Deselect();

   // riattiva la tabella eventi del elemento padre
   uiLboxIstanzaDyn.PtrLboxBaseElemento = BaseElemento + uiLboxIstanzaDyn.LboxFatherId;
   uiLboxIstanzaDyn.PtrLboxBaseElemento->EventOn(0xFF);   

   // visualizza nella prima posizione una 'x'
   LcdRomStrRC(uiLboxIstanzaDyn.coordinate.o_row,0,"x");
   
//   // riattiva la tabella eventi del elemento padre
//   PtrParBaseElemento->EventOn(0xFF);
//   
//   Timer[TMR_UI_PAR] = 200;
}

void uiLboxEventButtonsLeft    (void)
{
   _esci();
}

void uiLboxEventButtonsRight   (void)
{
   _esci();
}

_ROM EventTableDef uiLboxEvent[NUMBER_EVENT_BUTTONS] = {
    uiLboxEventButtonsRight         //    EVENT_BUTTONS_RIGHT     0
   ,uiLboxEventButtonsUp            //    EVENT_BUTTONS_UP        1
   ,uiLboxEventButtonsEnter         //    EVENT_BUTTONS_ENTER     2
   ,uiLboxEventButtonsDown          //    EVENT_BUTTONS_DOWN      3
   ,uiLboxEventButtonsLeft          //    EVENT_BUTTONS_LEFT      4
};                                  //    NUMBER_EVENT_BUTTONS    5

void uiLboxInitLight		(char element_id)
{
//   PtrLboxIstanzaElemento = LboxElemento + element_id;
//   LboxListElementId = 0;
   
}

void uiLboxInitCold				(void)
{
//   ButtonsEventMatrix[0].EventTable = uiLboxEvent;
   
//   uiLboxInitLight(0);
   // disattiva il timer di lampeggio dell'etichetta
   Timer[TMR_UI_LBOX] = 1;

}

void uiLboxDeselect		(void)
{
   // disattiva il lampeggio dell'elemento attivo
   LcdRomStrRC(uiLboxIstanzaDyn.coordinate.o_row,0," ");
}


void uiLboxEventOn	   (unsigned char father_id)
{
   BaseCoordinateStruct coordinate;
   
   // Attiva Tabella eventi
   ButtonsEventMatrix[0].EventTable = uiLboxEvent;      

   // controlla la tipologia del chiamante
   if(father_id != 0xFF)
   {
      // questa funzione ?tata chiamata dal padre, quindi ...
      // imposta i parametri
      
      // memorizza father_id
      uiLboxIstanzaDyn.LboxFatherId = father_id;
      
      // deselect lbox element
      uiLboxDeselect();
      
      // seleziona primo elemento della lista
      coordinate.o_row = uiLboxIstanzaDyn.coordinate.o_row + uiLboxIstanzaDyn.LboxWindowId;
      coordinate.o_col = uiLboxIstanzaDyn.coordinate.o_col;
      
      // aggiorna puntatore alla lista elementi
      uiLboxIstanzaDyn.PtrLboxListaElemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start + uiLboxIstanzaDyn.LboxListElementId];
      uiLboxIstanzaDyn.PtrLboxBaseElemento = BaseElemento + uiLboxIstanzaDyn.PtrLboxListaElemento->tipo_elemento;
      uiLboxIstanzaDyn.PtrLboxBaseElemento->Select(uiLboxIstanzaDyn.PtrLboxListaElemento->id_elemento,coordinate);
   }
      
}

//void uiLboxSelect		(char element_id, char o_row, char o_col, char n_row)
char uiLboxSelect		(char element_id, BaseCoordinateStruct coordinate)
{
//   // imposta il puntatore dell'istanza alla struttura del listbox selezionato
//   // l'elemento selezionato ?ornito dal element_id
//
//   // impostare il puntatore al parametro
//   PtrLboxIstanzaElemento = LboxElemento + element_id;
//   PtrLboxListaElemento = &LboxListaElementi[PtrLboxIstanzaElemento->list_element_id_start];
//                           
//   
//   PtrLboxBaseElemento = BaseElemento + PtrLboxListaElemento->tipo_elemento;
//   PtrLboxBaseElemento->Select(PtrLboxListaElemento->id_elemento,coordinate);
//   
//   // Seleziona primo elemento della lista elementi
   
//++   // 0. iniziailizzazione delle variabili globali circoscritte al modulo
//++   // 0.1. impostare il puntatore al parametro
//++   PtrParElemento = ParElemento + element_id;
//++   // 0.2. imposta le coordinate
//++   ParRow = coordinate.o_row;
//++   ParCol = coordinate.o_col;
//++   
//++   // attivare il timer di lampeggio dell'etichetta
//++   Timer[TMR_UI_PAR] = 200;

   // 0. iniziailizzazione delle variabili globali circoscritte al modulo
   // 0.1. impostare il puntatore al parametro
   uiLboxIstanzaDyn.PtrIstanzaElemento = LboxElemento + element_id;
   // 0.2. imposta le coordinate
   uiLboxIstanzaDyn.coordinate.o_row = coordinate.o_row;
   uiLboxIstanzaDyn.coordinate.o_col = coordinate.o_col;
//   // 0.3. imposta gli indici della lista elementi e 
//   LboxListElementId = 0;
//   LboxWindowId = 0;

   
   // visualizza nella prima posizione una 'x' ed impostare il timer del lampeggio
   LcdRomStrRC(uiLboxIstanzaDyn.coordinate.o_row,0,"x");
   

/*   

// impostate nella funzione di select
LboxListElementId = 0;
LboxWindowId = 0;

// viene impostata nella funzione EventOn, se si vuole la si potrebbe inserire anche nella funzione di select
char LboxFatherId;

// impostate nella funzione di select
unsigned char LboxRow;
unsigned char LboxCol;

// non serve settare queste variabili vengono calcolate al momento sulla base dei valori dei parametri
// LboxListElementId, LboxWindowId
char wdIdAbsolute = 0;
char uiLboxIstanzaDyn.wdIdRelative = 0;
char wdIdStates;
*/

   // ricaricare il timer
   // deselezionare l'elemento
   // incrementa l'indice
   // seleziona elemento
   
   return 1;
   
}

//void uiLboxVisualizza		(char element_id, char o_row, char o_col, char n_row)
void uiLboxVisualizza		(char element_id, BaseCoordinateStruct coordinate)
{
   char i;
   
   // visualizza la finestra
   // . id primo elemento della finestra
   // . numero di righe della finestra
   // . coordinate (riga e colonna) dell'angolo in alto a sinistra della finestra
   
   // impostare il puntatore al parametro
   uiLboxIstanzaDyn.PtrIstanzaElemento = LboxElemento + element_id;
   uiLboxIstanzaDyn.LboxListElementId = 0;
   uiLboxIstanzaDyn.LboxWindowId = 0;
  
   uiLboxIstanzaDyn.PtrLboxListaElemento = &LboxListaElementi[uiLboxIstanzaDyn.PtrIstanzaElemento->list_element_id_start];
   
   // Visualizza gli elementi della lista
   for(i=0;i<uiLboxIstanzaDyn.PtrIstanzaElemento->row_number;i++)
   {
      // visualizza elemento lista
      uiLboxIstanzaDyn.PtrLboxBaseElemento = BaseElemento + uiLboxIstanzaDyn.PtrLboxListaElemento->tipo_elemento;
      uiLboxIstanzaDyn.PtrLboxBaseElemento->Visualizza(uiLboxIstanzaDyn.PtrLboxListaElemento->id_elemento, coordinate);
      // xc8 link error - recursivwe call -- uiLboxIstanzaDyn.PtrLboxBaseElemento->Visualizza(uiLboxIstanzaDyn.PtrLboxListaElemento->id_elemento, coordinate);
      uiLboxIstanzaDyn.PtrLboxListaElemento++;

      coordinate.o_row++;
   }
   
   
}

void uiLboxTimer     (void)
{
   
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

