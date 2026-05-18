#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs){

    int iLoopCounter;

    iDelayInMs = iDelayInMs*2400;
    for(iLoopCounter = 0; iLoopCounter< iDelayInMs ; iLoopCounter++){}

}

int main(){

	LedInit();
	KeyboardInit();
	
	while(1){
		
		Delay(500);
		switch (eKeyboardRead()){
			
			case (BUTTON_1):
					LedStepRight();
					break;		
			case (BUTTON_2):
					LedStepLeft();
					break;	
			default:
					break;
	
			}
	}
}
