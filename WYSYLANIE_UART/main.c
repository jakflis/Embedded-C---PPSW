#include "uart.h"
#include "timer_interrupts.h"
#include "conversion.h"
#include "string.h"
#include "command_decoder.h"

struct Watch sWatch;

int main(){
	
	char cTransmitString[TRANSMITER_SIZE];
	char cReceivedString[RECEIVER_SIZE];
	
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(500000, WatchUpdate);
	
	
	while(1){
		if(eReceiver_GetStatus() == READY){
			Receiver_GetStringCopy(cReceivedString);
			DecodeMsg(cReceivedString);
			Calc();
			}
					
		if(Transmiter_GetStatus() == FREE){
			if(sWatch.fSecondsValueChanged == 1){
				CopyString("sec ",cTransmitString);
				AppendUIntToString(sWatch.ucSeconds,cTransmitString);
				Transmiter_SendString(cTransmitString);
				sWatch.fSecondsValueChanged = 0;
			}
			else if(sWatch.fMinutesValueChanged == 1){
				CopyString("min ",cTransmitString);
				AppendUIntToString(sWatch.ucMinutes,cTransmitString);
				Transmiter_SendString(cTransmitString);
				sWatch.fMinutesValueChanged = 0;
			}
			else if(Calc_GetStatus() == 1){
				CopyString("calc ", cTransmitString);
				AppendUIntToString(Calc_Result(), cTransmitString);
				Transmiter_SendString(cTransmitString);
			}
		}
	}
}
