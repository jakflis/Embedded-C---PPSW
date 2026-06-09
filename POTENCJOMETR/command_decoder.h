#ifndef TOKENS_H
#define TOKENS_H

#include "string.h"
#include "conversion.h"

#undef NULL
#define NULL '\0'
#define MAX_TOKEN_NR 3 
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define DELIMITER_CHARACTER ' '

enum TokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {CL, GT, CA}; 

struct Keyword {
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
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

extern struct Keyword asKeywordList[MAX_KEYWORD_NR];
extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);

#endif
