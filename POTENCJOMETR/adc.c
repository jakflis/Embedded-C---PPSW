#include <LPC21xx.H>

#include "adc.h"

#define mAIN0_PINSEL_MASK 0x00C00000
#define mAIN0_PINSEL_SET 0x00400000

#define mADCR_CH0 0x00000001
#define mADCR_CLKDIV 0x00000400
#define mADCR_PDN 0x00200000
#define mADCR_START 0x01000000
#define mADCR_STOP 0x07000000

#define mADDR_DONE 0x80000000

void ADC_Init(void){
	PINSEL1 &= ~mAIN0_PINSEL_MASK;
	PINSEL1 |= mAIN0_PINSEL_SET;
	
	ADCR = mADCR_CH0 | mADCR_CLKDIV | mADCR_PDN;
}

unsigned int ADC_Read(void){
	
    unsigned int uiResult;
    
    ADCR |= mADCR_START;
   
    while ((ADDR & mADDR_DONE) == 0) {}
    uiResult = (ADDR >> 6) & 0x03FF;
		uiResult = ((uiResult * 48) / 1023);
    ADCR &= ~mADCR_STOP;
		
    return uiResult;
}
