#include "command_decoder.h"
#include "string.h"
#include "conversion.h"
/*
#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 2
#define DELIMITER_CHARACTER ' '

enum TokenType {KEYWORD, NUMBER, STRING};

enum KeywordCode {CL, GT}; 

struct Keyword {
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
	{CL,"callib"},
	{GT, "goto" }
};

union TokenValue {
	enum KeywordCode eKeyword; 
	unsigned int uiValue; 
	char* pcString;
};

struct Token {
	enum TokenType eType; 
	union TokenValue uValue;
};
*/

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
	{CL,"callib"},
	{GT, "goto" }
};

enum State {TOKEN, DELIMITER};

unsigned char ucFindTokensInString(char *pcString) {

  enum State eCurrentState = DELIMITER;
  unsigned char ucCharacterCounter;
  unsigned char ucCurrentCharacter;
  unsigned char ucTokenNumber = 0;

  for(ucCharacterCounter = 0; ; ucCharacterCounter++) {
		ucCurrentCharacter = pcString[ucCharacterCounter];
		switch(eCurrentState) {
			case DELIMITER:
			if(NULL == ucCurrentCharacter) {
				return ucTokenNumber;
			}
			else if(DELIMITER_CHARACTER == ucCurrentCharacter) {}
			else {
				eCurrentState = TOKEN;
				asToken[ucTokenNumber].uValue.pcString = (pcString + ucCharacterCounter);
				ucTokenNumber++;
			}
			break;
			case TOKEN:
			if(MAX_TOKEN_NR <= ucTokenNumber) {
				return ucTokenNumber;
			}
			else if(NULL == ucCurrentCharacter) {
				return ucTokenNumber;
			}
			else if(DELIMITER_CHARACTER == ucCurrentCharacter) {
				eCurrentState = DELIMITER;
			}
			else {
				eCurrentState = TOKEN;
			}
			break;
		}
  }
}


enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode) { 
	unsigned char ucKeywordCounter;
	for(ucKeywordCounter=0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) { 
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)) {
			*peKeywordCode= asKeywordList[ucKeywordCounter].eCode; 
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void){

  unsigned char ucTokenCounter;
  struct Token * psCurrentToken;
	
  for(ucTokenCounter = 0; ucTokenNr > ucTokenCounter; ucTokenCounter++) {
     psCurrentToken = &asToken[ucTokenCounter];
	if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &psCurrentToken->uValue.eKeyword)) {
	   psCurrentToken->eType = KEYWORD;
	}
	else if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &psCurrentToken->uValue.uiValue)) {
	   psCurrentToken->eType = NUMBER;
	}
	else {
	   psCurrentToken->eType = STRING;
	}
  }
}

void DecodeMsg(char *pcString) {
	ucTokenNr= ucFindTokensInString(pcString); 
	ReplaceCharactersInString(pcString, DELIMITER_CHARACTER, NULL); 
	DecodeTokens();
}
