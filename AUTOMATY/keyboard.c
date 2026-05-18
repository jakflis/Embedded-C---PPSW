#include <LPC21xx.H>
#include "keyboard.h"

#define S0_bm (1<<4) 
#define S1_bm (1<<6) 
#define S2_bm (1<<5) 
#define S3_bm (1<<7) 

void KeyboardInit(){
	
	IO0DIR = IO0DIR & (~(S0_bm|S1_bm|S2_bm|S3_bm));
}

enum eKeyboardState eKeyboardRead(){
	
	if ((S0_bm & IO0PIN) == 0){
			return BUTTON_0;
	}
	else if((S1_bm & IO0PIN) == 0){
			return BUTTON_1;
	}
	else if((S2_bm & IO0PIN) == 0){
			return BUTTON_2;
	}
	else if((S3_bm & IO0PIN) == 0){
			return BUTTON_3;
	}
	else{
			return RELEASED;
	}
}
