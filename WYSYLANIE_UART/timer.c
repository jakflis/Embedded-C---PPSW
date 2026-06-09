#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE_BM (1<<0)
#define COUNTER_RESET_BM (1<<1)

#define RESET_ON_MR0_BM (1<<1)
#define INTERRUPT_ON_MR0_BM (1<<0)
#define INTERRUPT_FLAG_MR0_BM (1<<0)

void InitTimer0(void){
	T0TCR = COUNTER_ENABLE_BM;
}

void WaitOnTimer0(unsigned int uiTimeInUs){
	T0TCR = T0TCR|COUNTER_RESET_BM;
	T0TCR = T0TCR&(~COUNTER_RESET_BM);
	while(T0TC <= ((uiTimeInUs)*15)){
	}
}

void InitTimer0Match0(unsigned int uiDelayInUs){
	T0MR0 = uiDelayInUs*15; 
	T0MCR |= (RESET_ON_MR0_BM|INTERRUPT_ON_MR0_BM);
	T0TCR |= COUNTER_RESET_BM;
	T0TCR &= ~COUNTER_RESET_BM; 
	T0TCR |= COUNTER_ENABLE_BM;
}

void WaitOnTimer0Match0(){
	while((T0IR & INTERRUPT_FLAG_MR0_BM) == 0){}
		T0IR = INTERRUPT_FLAG_MR0_BM; 
}
