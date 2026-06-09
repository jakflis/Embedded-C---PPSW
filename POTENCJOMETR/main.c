#include "adc.h"
#include "servo.h"

int main(){
	
	ADC_Init();
	ServoInit(50);
	
	while(1){
		ServoGoTo(ADC_Read());
	}
}
