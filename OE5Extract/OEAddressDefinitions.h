#ifndef	OEADDRESSDEFINITION_H
#define	OEADDRESSDEFINITION_H

//
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "OE5ExtractDefinitions.h"

/*
 *		Structures
 */
struct	structHeader1
{
	unsigned long			lAddress;
};

struct	structHeader2
{
	unsigned long			lLengthAllocated;
};

struct	structHeader3
{
	unsigned long			lLengthUsed;
	unsigned long			lNextAddress;
};

struct	structHeader4
{
	unsigned long			lPrevAddress;
};

struct	structInformation
{
	int						iAttachementType;
	int						iAttachementCount;
	unsigned long			lPosition;
	char					szSortDate [ LEN_FILENAME ];
	char					szDate [ LEN_FILENAME ];
	char					szSubject [ LEN_PATHNAME ];
	char					szAuthor [ LEN_FILENAME ];
	char					szEmail [ LEN_FILENAME ];
	unsigned long			lSize;
};

#endif