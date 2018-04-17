#include <iostream>
#include <stdio.h>
#include <string>
#include "../library/string_processor/string_proc.h"
#include "../library/network/SocketServer.h"

using namespace std;

int main()
{
	String_processor procText;
	std::string stroutput;

	if( procText.GetMark("Hello Barney -Hello [World] this... is a simple []text","[","]", &stroutput) )
		cout << endl << "|>" << stroutput << "<|" << endl;
	else
		cout << "ERROR" << endl;

	return 0;
}
