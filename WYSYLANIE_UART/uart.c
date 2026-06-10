#include <LPC210X.H>
#include "uart.h"
#include "string.h"
#include "command_decoder.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

////////////// Zmienne globalne ////////////
char cOdebranyZnak;
char cCharCtr=0;
struct ReceiverBuffer sRxBuffer;
struct TransmiterBuffer sTxBuffer;
char cWyslanyZnak;
unsigned char fCalcReady = 0;
unsigned int uiCalcResult;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR;
		  Receiver_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
			cWyslanyZnak = Transmiter_GetCharacterFromBuffer();
				
			if(cWyslanyZnak != NULL){
					U0THR = cWyslanyZnak;
			}
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | 0x04 | 0x01;                                     // ustawic pina na odbiornik i nadajnik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_ENABLE;               // ustawiamy wlaczenie przerwania po odebraniu slowa

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

void Receiver_PutCharacterToBuffer(char cCharacter){
	
	if(cCharCtr >= RECEIVER_SIZE){
		sRxBuffer.eStatus = OVERFLOW;
		cCharCtr =0;
		return;
	}
	if(cCharacter == TERMINATOR){
		sRxBuffer.cData[cCharCtr] = '\0';
	  sRxBuffer.eStatus = READY;
		cCharCtr = 0;
	}
	else{
		sRxBuffer.cData[cCharCtr] = cCharacter;
		cCharCtr++;
	}	
}

enum eReceiverStatus eReceiver_GetStatus(void){
	
	return sRxBuffer.eStatus;
}

void Receiver_GetStringCopy(char *ucDestination){
	
	CopyString(sRxBuffer.cData, ucDestination);
	sRxBuffer.eStatus = EMPTY;
}

char Transmiter_GetCharacterFromBuffer(void){
	
	if(sTxBuffer.fLastCharacter == 1){
		sTxBuffer.eStatus = FREE;
		sTxBuffer.fLastCharacter = 0;
		sTxBuffer.ucCharCtr = 0;
		return NULL;
	}
	
	if(sTxBuffer.cTransmiterData[sTxBuffer.ucCharCtr] == NULL){
		sTxBuffer.fLastCharacter = 1;
		return TERMINATOR;
	}
	else{
		return sTxBuffer.cTransmiterData[sTxBuffer.ucCharCtr++];
	}
}
		
void Transmiter_SendString(char cString[]){
	
	CopyString(cString, sTxBuffer.cTransmiterData);
	sTxBuffer.eStatus = BUSY;
	sTxBuffer.fLastCharacter = 0;
	sTxBuffer.ucCharCtr = 0;
	U0THR = Transmiter_GetCharacterFromBuffer();
	
}
	
enum eTransmiterStatus Transmiter_GetStatus(void){
	
	return sTxBuffer.eStatus;
}

void Calc(void){
	if(asToken[0].eType == KEYWORD && asToken[0].uValue.eKeyword == CA){
	  if(asToken[1].eType == NUMBER){
		  uiCalcResult = (asToken[1].uValue.uiValue)*2;
			  fCalcReady = 1;
	  }
  }
}

unsigned char Calc_GetStatus(void){
	return fCalcReady;
}

unsigned int Calc_Result(void){
	fCalcReady = 0;
	return uiCalcResult;
}
