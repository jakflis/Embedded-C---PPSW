#include <LPC21xx.H>
#include "timer_interrupts.h"

#define mCOUNTER_ENABLE (1<<0)
#define mCOUNTER_RESET (1<<1)

#define mINTERRUPT_ON_MR0 (1<<0)
#define mRESET_ON_MR0 (1<<1)
#define mMR0_INTERRUPT (1<<0)

#define VIC_TIMER0_CHANNEL_NR 4

#define mIRQ_SLOT_ENABLE (1<<5)

void (*ptrTimer0InterruptFunction)(void);

__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	
	ptrTimer0InterruptFunction();
	VICVectAddr=0x00;
}

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void)){

  ptrTimer0InterruptFunction = ptrInterruptFunction;

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);           
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  
	VICVectAddr0  =(unsigned long)Timer0IRQHandler; 	 

	T0MR0 = 15 * uiPeriod;                 	     
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);

	T0TCR |=  mCOUNTER_ENABLE;

}

struct Watch sWatch;

void WatchUpdate(void){
	sWatch.ucSeconds++;
	sWatch.fSecondsValueChanged = 1;
	if(sWatch.ucSeconds == 60){
		sWatch.ucSeconds = 0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged = 1;
		if(sWatch.ucMinutes == 60){
			sWatch.ucMinutes = 0;
		}
	}
}
