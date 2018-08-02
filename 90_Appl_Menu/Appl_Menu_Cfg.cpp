#include "Appl_Menu.h"
#include "Appl_Menu_Cfg.h"

//
// Menu new concept
//

const T_MENU_ELEMENT MENU_DISPLAY_ELEMENTS[ APPLICATION_MAIN_MENU_COUNTS_TOTAL ] = 
{

	{
		E_MENU_TYPE_STRING,
		0,
		{'A', 'U', 'T', 'O'},
		NULL,
		E_MENU_SECURITY_ALL_RIGHTS
	},
	
	
	{
		E_MENU_TYPE_INT,
		0,
		{'P', 'A', 'R', '0'},
		NULL,
		E_MENU_SECURITY_ALL_RIGHTS
	},
	

	{
		E_MENU_TYPE_FLOAT,
		0,
		{'P', 'A', 'R', '1'},
		NULL,
		E_MENU_SECURITY_ALL_RIGHTS
	},
	
	// should contain 3 more elements
	//	
	{
		E_MENU_SUB_MENU_ENTRY,
		3,
		{'M', 'E', 'N', '0'},
		NULL,
		E_MENU_SECURITY_ALL_RIGHTS
	},

		{
			E_MENU_TYPE_INT,
			0,
			{'P', 'A', 'R', '2'},
			NULL,
			E_MENU_SECURITY_ALL_RIGHTS
		},

		{
			E_MENU_TYPE_INT,
			0,
			{'P', 'A', 'R', '3'},
			NULL,
			E_MENU_SECURITY_ALL_RIGHTS
		},
		
		{
			E_MENU_SUB_MENU_EXIT,
			2,
			{' ', 'U', 'P', ' '},
			NULL,
			E_MENU_SECURITY_ALL_RIGHTS
		}
		


};






//
//
//
//
/*
const T_SUB_MENU_STRING_LIST  SUB_MENU_STRING_LIST[APPLICATION_MENU_STRING_MAX_ENTRY] =
{
		
		{
			5, 
			
			{ {'S', 'T', 'R', '1'}, {'S', 'T', 'R', '2'}, {'S', 'T', 'R', '3'}, {'S', 'T', 'R', '4'}, {'S', 'T', 'R', '5'} }
		},
		{
			3,
			{ {'S', 'T', 'R', '6'}, {'S', 'T', 'R', '7'}, {'S', 'T', 'R', '8'}, {'S', 'T', 'R', '9'}, {'S', 'T', 'R', 'A'} }
		}

};
*/