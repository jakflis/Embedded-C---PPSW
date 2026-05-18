#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

#define S0_bm 0x00000010
#define S1_bm 0x00000040
#define S2_bm 0x00000020
#define S3_bm 0x00000080

enum eKeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum eDirections {RIGHT, LEFT};

void Delay(int iDelayInMs){

    int iLoopCounter;

    iDelayInMs = iDelayInMs*2400;
    for(iLoopCounter = 0; iLoopCounter< iDelayInMs ; iLoopCounter++){}

}

void LedInit(){

    IO1DIR = IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
    IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
    IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	
    IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;

 switch(ucLedIndeks){

  case(0):
			IO1SET = LED0_bm;
			break;
  case(1):
			IO1SET = LED1_bm;
			break;
  case(2):
			IO1SET = LED2_bm;
			break;
  case(3):
			IO1SET = LED3_bm;
			break;
  default:
			break;
 }
}

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

void LedStep(enum eDirections eStepDirection){
	
	static unsigned int uiCurrentLed=0;
	
	if(eStepDirection == RIGHT){
		uiCurrentLed++;
	}
	else{
		uiCurrentLed--;
	}
	
	LedOn(uiCurrentLed%4);
}

void LedStepLeft(void){
	
	LedStep(LEFT);
}

void LedStepRight(void){
	
	LedStep(RIGHT);
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
