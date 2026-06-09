struct Watch{
	unsigned char ucMinutes;
	unsigned char ucSeconds;
	unsigned char fSecondsValueChanged;
	unsigned char fMinutesValueChanged;
};
extern struct Watch sWatch;

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));
void WatchUpdate(void);
