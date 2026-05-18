#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs){

    int iLoopCounter;

    iDelayInMs = iDelayInMs*2400;
    for(iLoopCounter = 0; iLoopCounter< iDelayInMs ; iLoopCounter++){}

}

int main(){

	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT};
	enum LedState eLedState = LED_STOP;
	LedInit();
	KeyboardInit();
	
	while(1){
		
		Delay(100);
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
}
