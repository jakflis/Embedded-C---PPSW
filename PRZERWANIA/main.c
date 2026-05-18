#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"


void Automat(void){
	
	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT};
	static enum LedState eLedState = LED_STOP;

	switch (eLedState){
			
		case LED_STOP:
				if(eKeyboardRead() == BUTTON_0){
					eLedState = LED_LEFT;
				}
				else if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_RIGHT;
				}
				else{
					eLedState = LED_STOP;
				}
				break;		
		case LED_RIGHT:
				LedStepRight();
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_RIGHT;
				}
				break;	
		case LED_LEFT:
				LedStepLeft();
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_LEFT;
					}
		default:
				break;
	
		}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(100000, &Automat);

	while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
