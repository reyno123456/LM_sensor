#ifndef _FONT_H
#define _FONT_H

typedef struct
{
	unsigned char width;
	unsigned char distance;
	unsigned char bytes;
}FONT_CHARINFO;

extern __flash const unsigned char ASC[][32];
extern __flash const FONT_CHARINFO FontTrebuchetMS16_CharInfo[192];


#endif
