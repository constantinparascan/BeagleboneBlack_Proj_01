#ifndef _STRING_PROC_H_
#define _STRING_PROC_H_

#include <string>

class String_processor
{
private:

public:
	String_processor(){};

	bool GetMark(std::string strInput,
			     std::string strTokenStart,
				 std::string strTokenEnd,
				 std::string* strOutput);

};

#endif
