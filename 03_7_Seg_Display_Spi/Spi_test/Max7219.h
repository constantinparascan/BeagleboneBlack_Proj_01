
#ifndef __MAX7219_H__
#define __MAX7219_H__

/* #include "../bus/SPIDevice.h" */

/*
 * exported interfaces ....
 */


#define NULL_PTR (0)

void Max7219_Init(int nFileDescr);

void Max7219_Set_to_Display_Test(int nFileDescr);

void Max7219_Set_to_Display_Normal(int nFileDescr);

void Max7219_Set_Intensity(int nFileDescr, unsigned char nIntensity);

void Max7219_Set_to_Opperation_Sleep(int nFileDescr);

void Max7219_Set_to_Opperation_Normal(int nFileDescr);

void Max7219_Display_String_8digit(int nFileDescr, char *strString);


#endif // __MAX7219_H__
