#ifndef UART_H
#define UART_H

#define RECEIVER_SIZE 20
#define TERMINATOR '\r'

#define TRANSMITER_SIZE 20

extern char cOdebranyZnak;
enum eReceiverStatus {EMPTY, READY, OVERFLOW};
struct ReceiverBuffer{
	char cData[RECEIVER_SIZE];
	unsigned char ucCharCtr;
	enum eReceiverStatus eStatus;
};
extern struct ReceiverBuffer sRxBuffer;
extern char cCharCtr;

enum eTransmiterStatus {FREE, BUSY};
struct TransmiterBuffer{
	char cTransmiterData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char ucCharCtr;
};
extern struct TransmiterBuffer sTxBuffer;

void UART_InitWithInt(unsigned int uiBaudRate);

void Receiver_PutCharacterToBuffer(char cCharacter);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *ucDestination);

char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);

#endif
