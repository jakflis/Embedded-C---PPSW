#define RECEIVER_SIZE 20
#define TERMINATOR '\r'
void UART_InitWithInt(unsigned int uiBaudRate);
extern char cOdebranyZnak;
enum eReceiverStatus {EMPTY, READY, OVERFLOW};
struct ReceiverBuffer{
	char cData[RECEIVER_SIZE];
	unsigned char ucCharCtr;
	enum eReceiverStatus eStatus;
};
void Receiver_PutCharacterToBuffer(char cCharacter);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char *ucDestination);
extern struct ReceiverBuffer sRxBuffer;
extern char cCharCtr;
