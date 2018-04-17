
#ifndef __MAX7219_H__
#define __MAX7219_H__

#ifndef _DEBUG_ENABLE_

#include "../bus/SPIDevice.h"

#endif

/*
 * exported interfaces ....
 */
/* using namespace exploringBB; */

void Max7219_Init(int nFileDescr);

void Max7219_Set_to_Display_Test(void);

void Max7219_Set_to_Display_Normal(void);


void Max7219_Display_String_4digit(const unsigned char *strString, unsigned char nOffset);


#endif // __MAX7219_H__
