#ifndef CONVERSION_H
#define CONVERSION_H

#define NULL '\0'
void UIntToHexStr(unsigned int uiValue, char pcStr[]);
enum Result {OK, ERROR};
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);

#endif
