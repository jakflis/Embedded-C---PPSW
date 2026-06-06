#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"

char cString[RECEIVER_SIZE];
int main(){
	UART_InitWithInt(9600);
	ServoInit(50); 
	
	while(1){
		if(eReceiver_GetStatus() == READY){
			Receiver_GetStringCopy(cString);
		  DecodeMsg(cString);
			if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
					switch (asToken[0].uValue.eKeyword){
					  case CL:
							ServoCallib();
							break;
						case GT:
							ServoGoTo(asToken[1].uValue.uiValue);
							break;
						default:
							break;
					}
			}
		}
	}
}
