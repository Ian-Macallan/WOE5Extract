#ifndef	TEXTROUTINES_H
#define	TEXTROUTINES_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *		Prototypes.
 */
static void BuildCharSet ( );

extern bool IsDigit ( char cByte );
extern bool IsNumber ( char cByte );
extern bool IsSignedNumber ( char cByte );
extern bool IsUpper ( char cByte );
extern bool IsLower ( char cByte );
extern bool IsLetter ( char cByte );
extern bool CapitalizeName ( char *pString );
extern bool CapitalizeFullName ( char *pString );
extern bool LowerName ( char *pString );
extern bool UpperName ( char *pString );
extern int	CompareStringU ( unsigned char *pOne, unsigned char *pTwo );
extern int CompareString ( char *pOne, char *pTwo );
extern int CompareNStringU ( unsigned char *pOne, unsigned char *pTwo, size_t iLen );
extern int CompareNString ( char *pOne, char *pTwo, size_t iLen );
extern char *SearchString ( char *pString, char *pSearched );
extern bool RemoveString ( char *pString, char *pRemove );
extern void ReplaceCharacter ( char *pString, char cRemove, char cInsert );
extern bool ReplaceString ( char *pString, char *pRemove, char *pInsert );
extern void RemoveNumbers ( char *pString );
extern void RemoveOther ( char *pString );
extern void RemoveLeadingChars ( char *pString, const char cByte );
extern void RemoveLeadingSpaces ( char *pString );
extern void RemoveLeadingUnderscore ( char *pString );
extern void RemoveTrailingSpaces ( char *pString );
extern void FilterWithCharSetU ( unsigned char *pString );
extern void FilterWithCharSet ( char *pString );
extern void RemoveMultipleDot ( char *pString );
extern void ReplaceSpaceDot ( char *pString );
extern void RemoveMultipleUnderscore ( char *pString );
extern void LeaveOneDot ( char *pString );
extern bool Collapse ( char *pFilename );
extern unsigned char *StringSearchU ( unsigned char *pString, unsigned char *pSearched );
extern char *StringSearch ( char *pString, char *pSearched );
extern unsigned char *StringSearchMatchU ( unsigned char *pString, unsigned char *pSearched );
extern char *StringSearchMatch ( char *pString, char *pSearched );
extern unsigned char *StringMatchU ( unsigned char *pOne, unsigned char *pTwo );
extern char *StringMatch ( char *pOne, char *pTwo );
extern void ReplaceTabAndSo ( char *pString );

#endif