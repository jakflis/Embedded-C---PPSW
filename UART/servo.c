#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(){
	
	IO0DIR &= ~(DETECTOR_bm);
}

enum DetectorState eReadDetector(){
	
	if(0 == (IO0PIN & DETECTOR_bm)){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

struct Servo sServo;

void Automat(){
	
	switch (sServo.eState){
			case CALLIB:
				if (eReadDetector() == ACTIVE){
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				}
				else{
					LedStepLeft();
					sServo.eState = CALLIB;
				}
				break;
			
			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
				}
				break;
			case IN_PROGRESS:
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					LedStepRight();
					sServo.uiCurrentPosition++;
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					LedStepLeft();
					sServo.uiCurrentPosition--;
				}
				else if (sServo.uiCurrentPosition == sServo.uiDesiredPosition){
					sServo.eState = IDLE;
				}
				else{
					sServo.eState = IN_PROGRESS;
				}
				break;
		
			default:
				break;
		}
}

void ServoInit(unsigned int uiServoFrequency){
	
	unsigned int uiTime;
	
	sServo.eState = CALLIB;
	LedInit();
	
	uiTime = (1000000/uiServoFrequency);
	Timer0Interrupts_Init(uiTime, &Automat);
}
	
void ServoCallib(){
	
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	
	sServo.uiDesiredPosition = uiPosition;
}
