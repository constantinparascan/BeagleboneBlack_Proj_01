//
// Max7219.c       - keyboard driver
//
//
// C. Parascan 
//  
// v0.1 - 19.02.2013 - first implementation


#include "Max7219.h"
#include "Hal_Spi.h"

typedef enum 
{
	IDDLE        = 0,
	DIGIT_0      = 1,
	DIGIT_1      = 2,
	DIGIT_2      = 3,
	DIGIT_3      = 4,
	DIGIT_4      = 5,
	DIGIT_5      = 6,
	DIGIT_6      = 7,
	DIGIT_7      = 8,
	DECODE_MODE  = 9,
	INTENSITY    = 10,
	SCAN_LIMIT   = 11,
	SHUTDOWN     = 12,
	DISPLAY_TEST = 15
	
} T_Max7219Registry;




/////////////////////////////////////////////////
//                                             //
//                  Dictionary                 //
//                                             //
/////////////////////////////////////////////////


#define N_MAX_SUPPORTED_SYMBOLS (51)


unsigned char const arrAlphabet[N_MAX_SUPPORTED_SYMBOLS] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'l', 'L', 'n', 'N', 'm', 'M', 'o', 'O', 'p', 'P', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', ' ', '-','_' };
unsigned char const arrDecoded [N_MAX_SUPPORTED_SYMBOLS] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x77,0x1F,0x1F,0x0D,0x4E,0x3C,0x3C,0x4F,0x4F,0x47,0x47,0x73,0x73,0x37,0x37,0x06,0x06,0x38,0x38,0x0E,0x0E,0x15,0x15,0x76,0x76,0x1D,0x1D,0x67,0x67,0x05,0x05,0x5B,0x5B,0x0F,0x0F,0x3E,0x3E,0x00,0x01,0x08 };

unsigned char const arrInteger[10]        = {0,   1,   2,   3,   4,   5,   6,   7,   8,   9    };
unsigned char const arrDecodedInteger[10] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B };

unsigned char const arrFloat[20]        = {0,   1,   2,   3,   4,   5,   6,   7,   8,   9   ,0,   1,   2,   3,   4,   5,   6,   7,   8,   9     };
unsigned char const arrDecodedFloat[20] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0xFE,0xB0,0xED,0xF9,0xB3,0xDB,0xDF,0xF0,0xFF,0xFB  };




// C. Parascan - v0.1
// 
//  - first implementation
//
void Max7219_Init(void)
{
	unsigned short nTransmissionData = 0x0000;
	
	// send SPI command for no decode
	// DECODE_MODE, data = 0x00
	nTransmissionData = ((unsigned short)DECODE_MODE) << 8;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
	
	
	// send SPI command for intensity
	// INTENSITY, data = 0x0F ... maximum
	nTransmissionData = ((unsigned short)INTENSITY) << 8 | (unsigned short)0x000F;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
		
	
	// send SPI command for scan limit
	// SCAN_LIMIT, data = 0x07 ..... 0 .. 7
	nTransmissionData = ((unsigned short)SCAN_LIMIT) << 8 | (unsigned short)0x0007;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
	
	
	
	// send SPI command for SHUTDOWN
	// SHUTDOWN, data = 0x01 = normal opp
	nTransmissionData = ((unsigned short)SHUTDOWN) << 8 | (unsigned short)0x000F;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
	
	
	
}// end function Max7219_Init




// C.Parascan - v0.1
//
//  - first implementation
//
void Max7219_Set_to_Display_Test(void)
{
	unsigned short nTransmissionData = 0x0000;

    // send SPI command for test mode
	// DISPLAY_TEST, data = 0x01
	nTransmissionData = ((unsigned short)DISPLAY_TEST) << 8 | (unsigned short)0x000F;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
	
}// end function Max7219_Set_to_Display_Test




// C.Parascan - v0.1
//
//  - first implementation
//
void Max7219_Set_to_Display_Normal(void)
{

	unsigned short nTransmissionData = 0x0000;

    // send SPI command for normal mode
	// DISPLAY_TEST, data = 0x00
	nTransmissionData = ((unsigned short)DISPLAY_TEST) << 8;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);
	

}// end function Max7219_Set_to_Display_Normal




// C.Parascan - v0.1
//
//  - first implementation
//
void Max7219_Set_Intensity(unsigned char nIntensity)
{

	unsigned short nTransmissionData = 0x0000;

    // send SPI command for normal mode
	// INTENSITY, data = nIntensity
	nTransmissionData = ((unsigned short)INTENSITY) << 8 | ((unsigned short)0x000F & (unsigned short)nIntensity);
	Hal_Add_Tx_QueueElement_C(nTransmissionData);

}// end function Max7219_Set_Intensity



// C.Parascan - v0.1
//
//  - first implementation
//
void Max7219_Set_to_Opperation_Sleep(void)
{

	unsigned short nTransmissionData = 0x0000;


	// send SPI command for SHUTDOWN
	// SHUTDOWN, data = 0x00 = sleep opperation
	nTransmissionData = ((unsigned short)SHUTDOWN) << 8;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);


}// end function Max7219_Set_to_Opperation_Sleep



// C.Parascan - v0.1
//
//  - first implementation
//
void Max7219_Set_to_Opperation_Normal(void)
{

	unsigned short nTransmissionData = 0x0000;


	// send SPI command for SHUTDOWN
	// SHUTDOWN, data = 0x01 = normal opp
	nTransmissionData = ((unsigned short)SHUTDOWN) << 8 | (unsigned short)0x000F;
	Hal_Add_Tx_QueueElement_C(nTransmissionData);



}// end function Max7219_Set_to_Opperation_Normal




// C.Parascan - v0.1
//
//  - first implementation
//
unsigned char Util_Get_Code_From_Char(unsigned char chrCharacter)
{
	unsigned char nSearchIndex;
	unsigned char nReturnValue = 0x00;
	
	// search inside supported character vector for a match ...
	//
	for (nSearchIndex = 0; nSearchIndex < N_MAX_SUPPORTED_SYMBOLS; nSearchIndex++)
	{
	
		// search the caracter inside the supported char list ...
		//
		if(arrAlphabet[nSearchIndex] == chrCharacter)
		{
			nReturnValue = arrDecoded[nSearchIndex];
			break;
			
		}// end if
		
	}// end for
	
	return nReturnValue;
	
}// end function  Util_Get_Code_From_Char





// C.Parascan - v0.1
//
//  - first implementation
//
//
// [Restriction] - not less than 8 chars !!!
//
void Max7219_Display_String_8digit(char *strString)
{
	unsigned char nDispIndex;
	unsigned char nCharCode;
	unsigned short nCommandByte = 0x0000;
	
	// NULL string ???
	if(strString != 0)
	{
		
		// for each character in the string ... 0 ... 7
		//
		for (nDispIndex = 0; nDispIndex < 8; nDispIndex ++)
		{
		
			// the string has ended unexpected ?
			//
			if(*(strString + nDispIndex) == '\0')
				break;
			
			
			// get current character code
			nCharCode = Util_Get_Code_From_Char((unsigned char)(*(strString + nDispIndex)));
			
			
			
			// format command ... and send on SPI
			nCommandByte = ((unsigned short)(8 - nDispIndex)) << 8 | (unsigned short)nCharCode;
			Hal_Add_Tx_QueueElement_C(nCommandByte);

			
		}// end for
	
	}
	
}// end function Max7219_Display_String_8digit





// C.Parascan - v0.1
//
//  - first implementation
//
//
//
//
// Digit order of the display :    0x08 [D7]   |    0x07 [D6]   |    0x06 [D5]    |     0x05 [D4] 
//                                 0x04 [D3]   |    0x03 [D2]   |    0x02 [D1]    |     0x01 [D0]
//
//
//  if offset == 0   -> digits displayed  7, 6 ,5 ,4
//     offset == 1   -> digits displayed  6, 5, 4, 3 
//     offset == 2   -> digits displayed  5, 4, 3, 2
//     offset == 3   -> digits displayed  4, 3, 2, 1
//     offset == 4   -> digits displayed  3, 2, 1, 0
//
//
void Max7219_Display_String_4digit(char *strString, unsigned char nOffset)
{
	unsigned char nDispIndex;
	unsigned char nCharCode;
	unsigned short nCommandByte;
	
	
	// limit the offset variable to "4"
	//
	if(nOffset > 4)
		nOffset = 4;
	
	
	// ... decode characters in the string ...
	//
	for (nDispIndex = 0; nDispIndex < 4; nDispIndex ++)
	{
	
		// the string has ended unexpected ?
		//
		if(*(strString + nDispIndex) == '\0')
			break;
	
		
		// get current character code
		nCharCode = Util_Get_Code_From_Char((unsigned char)(*(strString + nDispIndex)));
		
		// format command ... and send on SPI
		nCommandByte = ((unsigned short)(8 - nDispIndex - nOffset)) << 8 | (unsigned short)nCharCode;
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		Hal_SendDSPI_Locked_C(nCommandByte);
		
	}// end for
	
}// end function Max7219_Display_String_4digit






// C.Parascan - v0.1
//
//  - first implementation
//
//
//
//
// Digit order of the display :    0x08 [D7]   |    0x07 [D6]   |    0x06 [D5]    |     0x05 [D4] 
//                                 0x04 [D3]   |    0x03 [D2]   |    0x02 [D1]    |     0x01 [D0]
//
//
//  if offset == 0   -> digits displayed  7, 6 ,5 ,4
//     offset == 1   -> digits displayed  6, 5, 4, 3 
//     offset == 2   -> digits displayed  5, 4, 3, 2
//     offset == 3   -> digits displayed  4, 3, 2, 1
//     offset == 4   -> digits displayed  3, 2, 1, 0
//
//

void Max7219_Display_Number_4digit_v0(short nValue, unsigned char nOffset)
{
	unsigned char  nDispIndex = 0;
	unsigned short nCharCode = 0;
	unsigned short nCommandByte = 0;
	unsigned char  nDataByte = 0;
	
	unsigned char nValueNonZeroExist = 0;
	
	
	// check to see if value in range ...
	if(nValue > 9999)
		nValue = 9999;
		
	if(nValue < -999)
		nValue = -999;
	
	
    // limit the offset variable to "4"
	//
	if(nOffset > 4)
		nOffset = 4;

	
	// Display '0' ???
	//
	if(nValue == 0)
	{
		nCharCode = (unsigned short)arrDecodedInteger[0];
		nCommandByte = (unsigned short)(8 - 3 - nOffset) << 8 | nCharCode;
		
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		Hal_SendDSPI_Locked_C(nCommandByte);

	}
	//
	// this must be a numeric value != 0 ... with several digits ...
	//
	else
	{
		
		// for each numer ... decode and display ...
		//
		for (nDispIndex = 0; nDispIndex < 4; nDispIndex ++)
		{
		
			// fist digit is to be displayed ...
			//
			if( nDispIndex == 0 )
			{
			
				// if a negative number is to be displayed
				//
				if( nValue < 0 )
				{
				
					// first digit is '-'
					//
					nCharCode = (unsigned short)Util_Get_Code_From_Char('-');
					
					// convert to positive
					nValue = -nValue;
					
				}
				else
				// positive number ...
				{
					// positive number ... decode high digit
					//
					nCharCode =  (unsigned short)(nValue / (unsigned short)1000);
					
					// remove high nibble
					nValue = nValue - (short)(nCharCode * 1000);
					
					
					// if the high nibbles are '0' ... do not display them
					if(nCharCode > 0)
					{
						nCharCode = (unsigned short)arrDecodedInteger[nCharCode];
						
						nValueNonZeroExist ++;
					}
					else
					{
						// ... do not display anything
						nCharCode = (unsigned short)Util_Get_Code_From_Char(' ');
						
					}
					
					
				}// end if ( nValue < 0 )
				
							
			}// end if( nDispIndex == 0 )
			//
			// decode consecutive digit ...
			//
			else
			{
				nCharCode =  (unsigned short)(nValue / (short)(10 ^ (3 - nDispIndex)));
				
				// remove high nibble
				nValue = nValue - (short)(nCharCode * (unsigned short)(10 ^ (3 - nDispIndex)));
				
				
				// if the high nibbles are '0' ... do not display them
				if(nCharCode > 0)
				{
					nCharCode = (unsigned short)arrDecodedInteger[nCharCode];
					
					nValueNonZeroExist ++;
				}
				else
				{
					if(nValueNonZeroExist)
					{
						nCharCode = (unsigned short)arrDecodedInteger[0];
					}
					else
					{
						// ... do not display anything
						nCharCode = (unsigned short)Util_Get_Code_From_Char(' ');
					}
					
				}// end if else if(nCharCode > 0)
					
			}// end else if( nDispIndex == 0 )
			
			
			
			// display ...			
			nCommandByte = ((unsigned short)(8 - nDispIndex - nOffset)) << 8 | nCharCode;
			//Hal_Add_Tx_QueueElement_C(nCommandByte);
			Hal_SendDSPI_Locked_C(nCommandByte);
			
		}// end for
	
	
	}// end if (nValue == 0)
	
	
}// end function Max7219_Display_Number_4digit


void Max7219_Display_Number_4digit(short nValue)
{
	
	unsigned char  nSignExtracted = 0;
	unsigned char  nDone          = 0;
	unsigned char  nDispIndex     = 0;
	unsigned short nValueTemp     = 0;
	
	/*                                   '  '   '  '  '  '  '  '    */
	unsigned char arrDecodedNumber[4] = {0x00, 0x00, 0x00, 0x00};
	
	
	// check to see if value in range ...
	if(nValue > 9999)
		nValue = 9999;
		
	if(nValue < -999)
		nValue = -999;
	
	

	
	// Display '0' ???
	//
	if(nValue == 0)
	{
		arrDecodedNumber[3] = arrDecodedInteger[0];
		
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		//Hal_SendDSPI_Locked_C(nCommandByte);

	}
	//
	// this must be a numeric value != 0 ... with several digits ...
	//
	else
	{
		if(nValue < 0)
		{
			/*                    '-'
			*/
			arrDecodedNumber[0] = 0x01;
			
			nSignExtracted = 1;
			nValue = -nValue;
		}
		
		
		/*
		 *   Decode digit '3' 
		 */
		 
		nValueTemp = nValue % 10;
		
		if(nValueTemp != 0)
		{
			arrDecodedNumber[3] = arrDecodedInteger[nValueTemp];
			nValue = nValue / 10;
		}
		else
		{
			nDone = 1;	
		}
	
		
	
		
		/*
		 *   Decode digit '2' 
		 */
		if(nDone == 0)
		{
			
			nValueTemp = nValue % 10;
			
			if(nValueTemp != 0)
			{
				arrDecodedNumber[2] = arrDecodedInteger[nValueTemp];
				nValue = nValue / 10;
			}
			else
			{
				nDone = 1;
			}
		}
		
		
		
		/*
		 *   Decode digit '1' 
		 */
		if(nDone == 0)
		{
			
			nValueTemp = nValue % 10;
			
			if(nValueTemp != 0)
			{
				arrDecodedNumber[1] = arrDecodedInteger[nValueTemp];
				
				nValue = nValue / 10;
			}
			else
			{
				nDone = 1;	
			}
		

		
		}

		/*
		 *   Decode digit '0' and sign
		 */
		if( (nDone == 0) && (nSignExtracted == 0) )
		{
			
			nValueTemp = nValue % 10;
			
			if(nValueTemp != 0)
			{
				arrDecodedNumber[0] = arrDecodedInteger[nValueTemp];
				
			}
			else
			{
				nDone = 1;	
			}
		

		
		}/* end decode digit '0' */
		
	
	
	}// end if (nValue == 0)
	

	// for each numer ... display ...
	//
	for (nDispIndex = 0; nDispIndex < 4; nDispIndex ++)
	{
	
		// display ...			
		nValueTemp = ((unsigned short)(4 - nDispIndex)) << 8 | arrDecodedNumber[nDispIndex];
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		Hal_SendDSPI_Locked_C(nValueTemp);
		
	}// end for

	
	
}// end function Max7219_Display_Number_4digit





// C.Parascan - v0.1
//
//  - first implementation
//
//
//
//
// Digit order of the display :    0x08 [D7]   |    0x07 [D6]   |    0x06 [D5]    |     0x05 [D4] 
//                                 0x04 [D3]   |    0x03 [D2]   |    0x02 [D1]    |     0x01 [D0]
//
//
//  if offset == 0   -> digit displayed  7, 6 ,5 ,4
//     offset == 1   -> digit displayed  6, 5, 4, 3 
//     offset == 2   -> digit displayed  5, 4, 3, 2
//     offset == 3   -> digit displayed  4, 3, 2, 1
//     offset == 4   -> digit displayed  3, 2, 1, 0
//
//
void Max7219_Display_Bool_4digit(int nBoolValue, unsigned char nOffset)
{
	unsigned char  nDispIndex;
	unsigned char  nCharCode;
	unsigned short nCommandByte;
	
	unsigned char arrBool_On [4] = " On ";
	unsigned char arrBool_Off[4] = " OFF";
	unsigned char *ptrStrDisp;
	
	// limit the offset variable to "4"
	//
	if(nOffset > 4)
		nOffset = 4;
	
	
	// check to see what to display
	//
	if(nBoolValue > 0)
	{
		ptrStrDisp = arrBool_On;
	}
	else
	{
		ptrStrDisp = arrBool_Off;
	}
	
	
	
	// ... decode characters in the string ...
	//
	for (nDispIndex = 0; nDispIndex < 4; nDispIndex ++)
	{
	

		
		// get current character code
		nCharCode = Util_Get_Code_From_Char((unsigned char)(*(ptrStrDisp + nDispIndex)));
		
		//
		// format command ... and send on SPI
		//
		nCommandByte = ((unsigned short)(8 - nDispIndex - nOffset)) << 8 | (unsigned short)nCharCode;
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		Hal_SendDSPI_Locked_C(nCommandByte);
		
		
	}// end for
	
}// end function Max7219_Display_Bool_4digit



// C.Parascan - v0.1
//
//  - first implementation
//
//
//
//
// Digit order of the display :    0x08 [D7]   |    0x07 [D6]   |    0x06 [D5]    |     0x05 [D4] 
//                                 0x04 [D3]   |    0x03 [D2]   |    0x02 [D1]    |     0x01 [D0]
//
//
//  if offset == 0   -> digit displayed  7, 6 ,5 ,4
//     offset == 1   -> digit displayed  6, 5, 4, 3 
//     offset == 2   -> digit displayed  5, 4, 3, 2
//     offset == 3   -> digit displayed  4, 3, 2, 1
//     offset == 4   -> digit displayed  3, 2, 1, 0
//
//

void Max7219_Display_Float_4digit(short nValue, unsigned char nDivider, unsigned char nOffset)
{
	unsigned char  nDispIndex = 0;
	unsigned short nCharCode = 0;
	unsigned short nCommandByte = 0;
	unsigned char  nDataByte = 0;
	
	unsigned char nValueNonZeroExist = 0;
	
	
	// check to see if value in range ...
	if(nValue > 9999)
		nValue = 9999;
		
	if(nValue < -999)
		nValue = -999;
	
	
    // limit the offset variable to "4"
	//
	if(nOffset > 4)
		nOffset = 4;

	
	// Display '0' ???
	//
	if(nValue == 0)
	{
		// add also the decimal point if required
		//
		if(nDivider == 0)
		{
			nCharCode = (unsigned short)arrDecodedFloat[0];	
		}
		else
		{
			nCharCode = (unsigned short)arrDecodedFloat[10];
		}
		
		nCommandByte = (unsigned short)(8 - 3 - nOffset) << 8 | nCharCode;
		
		//Hal_Add_Tx_QueueElement_C(nCommandByte);
		Hal_SendDSPI_Locked_C(nCommandByte);

	}
	//
	// this must be a numeric value != 0 ... with several digits ...
	//
	else
	{
		
		// for each numer ... decode and display ...
		//
		for (nDispIndex = 0; nDispIndex < 4; nDispIndex ++)
		{
		
			// fist digit is to be displayed ...
			//
			if( nDispIndex == 0 )
			{
			
				// if a negative number is to be displayed
				//
				if( nValue < 0 )
				{
				
					// first digit is '-'
					//
					nCharCode = (unsigned short)Util_Get_Code_From_Char('-');
					
					// convert to positive
					nValue = -nValue;
					
				}
				else
				// positive number ...
				{
					// positive number ... decode high digit
					//
					nCharCode =  (unsigned short)(nValue / (unsigned short)1000);
					
					// remove high nibble
					nValue = nValue - (short)(nCharCode * 1000);
					
					
					// if the high nibbles are '0' ... do not display them
					if(nCharCode > 0)
					{
						nCharCode = (unsigned short)arrDecodedInteger[nCharCode];
						
						nValueNonZeroExist ++;
					}
					else
					{
						// ... do not display anything
						nCharCode = (unsigned short)Util_Get_Code_From_Char(' ');
						
					}
					
					
				}// end if ( nValue < 0 )
				
							
			}// end if( nDispIndex == 0 )
			//
			// decode consecutive digit ...
			//
			else
			{
				nCharCode =  (unsigned short)(nValue / (short)(10 ^ (3 - nDispIndex)));
				
				// remove high nibble
				nValue = nValue - (short)(nCharCode * (unsigned short)(10 ^ (3 - nDispIndex)));
				
				
				// if the high nibbles are '0' ... do not display them
				if(nCharCode > 0)
				{
					nCharCode = (unsigned short)arrDecodedInteger[nCharCode];
					
					nValueNonZeroExist ++;
				}
				else
				{
					if(nValueNonZeroExist)
					{
						nCharCode = (unsigned short)arrDecodedInteger[0];
					}
					else
					{
						// ... do not display anything
						nCharCode = (unsigned short)Util_Get_Code_From_Char(' ');
					}
					
				}// end if else if(nCharCode > 0)
					
			}// end else if( nDispIndex == 0 )
			
			
			
			// display ...			
			nCommandByte = ((unsigned short)(8 - nDispIndex - nOffset)) << 8 | nCharCode;
			//Hal_Add_Tx_QueueElement_C(nCommandByte);
			Hal_SendDSPI_Locked_C(nCommandByte);
			
		}// end for
	
	
	}// end if (nValue == 0)
	
	
}// end function Max7219_Display_Float_4digit
