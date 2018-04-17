#ifndef __APPL_MENU_H__
#define __APPL_MENU_H__

#if _DEBUG_ENABLE_==ON
#include <stdio.h>
#endif


/* #include "Appl_Types.h" */

#define NULL_PTR (0)


// - defines how many digits represent the menu name
#define APPLICATION_MAIN_MENU_HEADER_DIGITS (4)
// - defines how many digits represent the menue value
#define APPLICATION_MAIN_MENU_VALUE_DIGITS (4)

#ifdef _DEBUG_ENABLE_
#define DEBUG_PRINT_HEADER(a, b, c, d) printf("\n\r [ %c %c %c %c ]", a, b, c, d);fflush(stdout)
#define DEBUG_PRINT_STATE(a)           printf("\n\r\t\t State: %d", a);fflush(stdout);
#define DEBUG_PRINT_NEW_LINE()         printf("\n\n\n\r");fflush(stdout);
#else 
#define DEBUG_PRINT_HEADER(a, b, c, d) 
#define DEBUG_PRINT_STATE(a)
#define DEBUG_PRINT_NEW_LINE()
#endif


typedef enum 
{
	E_MENU_TYPE_STRING = 0,
	E_MENU_TYPE_INT,
	E_MENU_TYPE_FLOAT,
	E_MENU_TYPE_ENUM,
	E_MENU_TYPE_BOOL,
	E_MENU_SUB_MENU_ENTRY,
	E_MENU_SUB_MENU_EXIT
	
}T_MENU_TYPE;




// privilege level required to access / modify content
// 0 - all rights
// 1 - read only
// 2 - hidden - available only in security level Super User
// 3 - hidden - available only in security level Admin
typedef enum 
{
	E_MENU_SECURITY_ALL_RIGHTS = 0,
	E_MENU_SECURITY_RO,
	E_MENU_SECURITY_SU,
	E_MENU_SECURITY_ADMIN
	
}T_MENU_SECURITY;



typedef struct
{
	// index inside the enum array types
	unsigned char m_enum_idx;
	
	// current enum value ... index inside enum records
	unsigned char m_enum_value;
	
}T_ENUM_ELEMENT_INDEX;



typedef struct 
{
	T_MENU_TYPE m_menu_type;
	
	unsigned char m_menu_item_counts;
	
	unsigned char m_menu_header[APPLICATION_MAIN_MENU_HEADER_DIGITS];
	
	
	
	// -> in case of BOOL -> this shall point to an int variable
	// -> in case of INT  -> this shall point to a short variable
	// -> in case of STRING -> this shall point to a int[2] variable ... representing the index inside the display values collection
	//
	void* m_ptr_ram_data;
	
	
	// privilege level required to access / modify content
	T_MENU_SECURITY m_security_level;
	
}T_MENU_ELEMENT;





// Keeps all the string sub menu posibilities
//
//
typedef struct TAG_SUB_MENU_SRING_LIST
{
	unsigned char mMaxEntryIDs;
	
	/* unsigned char mStrList[APPLICATION_SUB_MENU_STRING_LIST_MAX_ENTRY][APPLICATION_MAIN_MENU_VALUE_DIGITS]; */
    unsigned char mStrList[7][7];
	
}T_SUB_MENU_STRING_LIST;




/*
 *  Exported API's
 */

void Appl_Menu_Init(void);

void Appl_Menu_ScrollDown(void);
void Appl_Menu_ScrollUp(void);
void Appl_Menu_ExitSubMenu(void);
void Appl_Menu_EnterSubMenu(void);

//void Appl_Menu_SetMenuDisplayLogo(void);
//void Appl_Menu_Refresh(void);

void Appl_Menu_MainFunction(void);


#endif
