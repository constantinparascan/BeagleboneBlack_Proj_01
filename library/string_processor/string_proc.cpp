#include "string_proc.h"




bool String_processor::GetMark(std::string strInput,
			     	 	 	   std::string strTokenStart,
							   std::string strTokenEnd,
							   std::string* strOutput)
{
	bool bFoundMarks = false;
	int nFirstTokenPosition = -1;
	int nSecondTokenPosition = -1;

	if( strInput.find(strTokenStart) != std::string::npos )
	{
		nFirstTokenPosition = strInput.find(strTokenStart);

		if( strInput.find(strTokenEnd) != std::string::npos )
		{
			nSecondTokenPosition = strInput.find(strTokenEnd);

			bFoundMarks = true;
		}
	}


	if( ( bFoundMarks ) && ( nSecondTokenPosition > nFirstTokenPosition ) )
	{
		*strOutput = strInput.substr(nFirstTokenPosition + 1,
				                     (nSecondTokenPosition - nFirstTokenPosition - 1) );
	}

	return bFoundMarks;

}
