#include "uart.h"
#include "servo.h"

int main(){
	
	unsigned int uiPosition = 0;
	UART_InitWithInt(9600);
	ServoInit(50); 
	
	while(1){
		switch(cOdebranyZnak){
			case '1':
				uiPosition = uiPosition + 12;
				ServoGoTo(uiPosition);
				cOdebranyZnak = 0;
				break;
			case 'c':
				ServoCallib();
				uiPosition = 0;
				cOdebranyZnak = 0;
				break;
			default:
				break;
		}
	}
}
