#include "Appl_Menu_Cfg.h"
#include "Max7219.h"


// 0 - no blinking
// 1 - blinking state - on display
// 2 - blinking state - off display
//
// represent the status of the value menu ....
//
unsigned char nApplMenu_CurrentMenuBlinkState;
unsigned char nApplMenu_BlinkingCounter;

//
// ... current display menu index ...
//
unsigned int nApplMenuCurrentDisplayIndex;

// current depth level of the menu display ...
unsigned int nApplMenuCurrentDepthLevel;
// index used to return from the current sub-menu ...
unsigned int nApplMenuDepthIndexReturn[APPL_MENU_DEPTH_LEVELS];


unsigned int nEnterEnergySave_L1_Timer;
unsigned int nEnterEnergySave_L2_Timer;
unsigned int nEnterPowerUpTest_Timer;


unsigned char nApplMenuState;

// used to indicate any anomalies in the functionality of the module
// ... logging of the errors ...
unsigned char nApplMenuErrors;


/*
 * 
 *  Local API's
 * 
 */
void Appl_Menu_SetMenuDisplayLogo(void);

//
// Display intesity states
//
#define APPL_MENU_INTENSITY_NORMAL       (5)
#define APPL_MENU_INTENSITY_L1           (2)
#define APPL_MENU_INTENSITY_L2           (1)


//
// Blinking states
//
//
#define APPL_MENU_BLINK_STATE_NO_BLINKING  (0)
#define APPL_MENU_BLINK_STATE_ON_MESSAGE   (1)
#define APPL_MENU_BLINK_STATE_OFF_MESSAGE  (2)




//
//  Menu States
//
//
// high power 
#define APPL_MENU_STATE_IDDLE_HIGH_POWER_ENTER       (0)
#define APPL_MENU_STATE_IDDLE_HIGH_POWER             (1)
#define APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1_ENTER   (2)
#define APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1         (3)
#define APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2_ENTER   (4)
#define APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2         (5)




#define APPL_MENU_STATE_ACTION_REFRESH_ENTER   (30)
#define APPL_MENU_STATE_ACTION_REFRESH         (31)


#define APPL_MENU_STATE_POWER_UP_TEST_ENTER    (101)
#define APPL_MENU_STATE_POWER_UP_TEST          (102)

#define APPL_MENU_STATE_LOGO                   (110)






// C. Parascan - v0.2
//
//
void Appl_Menu_Init(void)
{
    unsigned char nIndex = 0;
    
	// during the power up all display segments shall be displayed in order to check for 
	// burned segments
	nApplMenuState = APPL_MENU_STATE_POWER_UP_TEST_ENTER;
	

	// ... all the energy states saving  counters are reset
	//
	nEnterEnergySave_L1_Timer = 0;
    nEnterEnergySave_L2_Timer = 0;
    nEnterPowerUpTest_Timer   = 0;
    
    // first menu index that shall be displayed after power on test
    nApplMenuCurrentDisplayIndex = 0;
    
    
    // current depth level of the menu display ...
    nApplMenuCurrentDepthLevel = 0;
    
    // index used to return from the current sub-menu ...
    for(nIndex = 0; nIndex < APPL_MENU_DEPTH_LEVELS; nIndex ++)
    {
        nApplMenuDepthIndexReturn[ nIndex ] = 0;
    }
    
    
    
    // no blinking ...
    nApplMenu_CurrentMenuBlinkState = APPL_MENU_BLINK_STATE_OFF_MESSAGE;

    //
    // [ ToDo ]
    //
    //nApplMenu_CurrentMenuBlinkState = 0,0,0,0,0
    nApplMenu_BlinkingCounter = 0;
    
}// end function Appl_Menu_Init








//
//   ???? when you go down ... and meet an exit point >>>> search for a start point above .... cyclic menu display
//
//        when you go down and no exit point >>>> ++
//
//        when you go down .... and current is an entry point   >>>> search for an exit point down + 1 ... next menu in case of sub-menu detection
//
//




// C. Parascan - v0.2
//
// Select the next menu for display ...
//
//
void Appl_Menu_ScrollDown(void)
{
	
	//
	// [To Do] ... check that the menu contains at least 2 elements .... otherwise the index 1 is out of range
	//
	//
	//   >>>> this can be done inside the .h file ... as #if ( < 2 ) #error ....
	//
	
    
	//
	// Search possible end-up situations
	//
	if( nApplMenuCurrentDisplayIndex < ( APPLICATION_MAIN_MENU_COUNTS_TOTAL - 1 ) )
	{
	
		//
		//
		// Case 1 - "Sub-Menu" -> check if we are located on an sub-menu entry ... 
        //      than we have to go over all the sub menu entry points
		//
		//
		if( MENU_DISPLAY_ELEMENTS[ nApplMenuCurrentDisplayIndex ].m_menu_type == E_MENU_SUB_MENU_ENTRY )
		{
		
		
			//
			// we need to go over the current entry
			//
			nApplMenuCurrentDisplayIndex += MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts;

	

			//
			// make sure index does not goes outside array bounds
			//
			if(nApplMenuCurrentDisplayIndex >= (APPLICATION_MAIN_MENU_COUNTS_TOTAL - 1))
			{
				// ... go below the Logo menu entry ... who is always on position ... 0 ...
				//
				nApplMenuCurrentDisplayIndex = 1;
			}
			
			
		}// end if ... Case 1		
		else            
        {
              
            //
            //
            // Case 2 - "Sub-Menu" -> check if we are located on an sub-menu exit ... 
            //      than we have to go over to the start point
            //
            //
            if( MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_type == E_MENU_SUB_MENU_EXIT )
            {
            
            
                //
                // make sure index does not goes outside array bounds
                //                
                if( nApplMenuCurrentDisplayIndex > MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts )
                {
                    //
                    // we need to go over the current entry
                    //
                    nApplMenuCurrentDisplayIndex -= MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts;

                }
                else
                {
                    // ... go below the Logo menu entry ... who is always on position ... 0 ...
                    //
                    nApplMenuCurrentDisplayIndex = 1;
                }

                
            }// end if ... Case 2
            else
            {
            
                //
                // Case 3 - normal scroll
                //
                nApplMenuCurrentDisplayIndex ++;            		
		
            }// end else ... Case 3
            
        }// end else case 1

		
				
	}// end if(nApplMenuCurrentDisplayIndex < APPLICATION_MAIN_MENU_COUNTS - 1)
	//
	// ... the menu is at it's end ... no place to go ... but the beginning
	//
	else
	{
	
		//
		// nApplMenuCurrentDisplayIndex == 0 ... is the logo ...
		//
	
		nApplMenuCurrentDisplayIndex = 1;	
		
	}
	
	
	// trigger a menu refresh
	//
	nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
	
}// end function Appl_Menu_ScrollDown




// C. Parascan - v0.2
//
// Select the previous menu for display ...
//
//

void Appl_Menu_ScrollUp(void)
{

	//
	// [To Do] ... check that the menu contains at least 2 elements .... otherwise the index 1 is out of range
	//
	//
	//   >>>> this can be done inside the .h file ... as #if ( < 2 ) #error ....
	//


	//
	// nApplMenuCurrentDisplayIndex == 0 ... is the logo ...
	//
	
	if(nApplMenuCurrentDisplayIndex > 1)
	{
	

		//
		// Case 1 - "Exit Point" -> if we have ended on an "exit point" ... 
        //          this can only mean that we have to search and display
		//          it's entry point
		//
		if( MENU_DISPLAY_ELEMENTS[ nApplMenuCurrentDisplayIndex ].m_menu_type == E_MENU_SUB_MENU_EXIT )
		{
            if(nApplMenuCurrentDisplayIndex > MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts )
            {
            
                nApplMenuCurrentDisplayIndex -= MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts;
                
            }
            else
            {
                nApplMenuCurrentDisplayIndex = 1;
            }
            

		}// end if - Case 1
		else
        {
            

            //
            //
            // Case 2 - "Sub-Menu" -> check if we are located on an sub-menu entry point ... 
            //     than we have roll back to it's exit point 
            //     - we have to pay attention for all the sub-menues 
            //       that can be included in the current menu ... which also have
            //       entry / exit points
            //

            if( MENU_DISPLAY_ELEMENTS[ nApplMenuCurrentDisplayIndex ].m_menu_type == E_MENU_SUB_MENU_ENTRY )
            {
            
                nApplMenuCurrentDisplayIndex += MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_item_counts;
                
                if( nApplMenuCurrentDisplayIndex > APPLICATION_MAIN_MENU_COUNTS_TOTAL )
                {
                    nApplMenuCurrentDisplayIndex = 1;
                }
                
            }// end - Case 2
            else
            {

                //
                // Case 3 - normal scroll
                //
                nApplMenuCurrentDisplayIndex --;
            }
        }

			
	}
	

	// trigger a menu refresh
	//
	nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
	
	
}// end function Appl_Menu_ScrollUp





// C. Parascan - v0.2
//
// Exits the current sub-menu selection into the parent menu ...
//
//
void Appl_Menu_ExitSubMenu(void)
{
	
	if( ( nApplMenuCurrentDisplayIndex >= 1 ) && 
        ( nApplMenuCurrentDisplayIndex < APPLICATION_MAIN_MENU_COUNTS_TOTAL ) && 
        ( nApplMenuCurrentDepthLevel > 0) )
	{
	
        nApplMenuCurrentDisplayIndex = nApplMenuDepthIndexReturn[ nApplMenuCurrentDepthLevel ];
        nApplMenuCurrentDepthLevel --;
	
	}// end if

    // trigger a menu refresh
    //
    nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
	
	
}// end function Appl_Menu_ExitSubMenu_v2





// C. Parascan - v0.2
//
// Enters the current sub-menu selection ...
//
//

void Appl_Menu_EnterSubMenu(void)
{
    
	if( ( nApplMenuCurrentDisplayIndex >= 1 ) && 
        ( nApplMenuCurrentDisplayIndex < APPLICATION_MAIN_MENU_COUNTS_TOTAL ) )
	{
		
        //
        //
        // Case 1 - enter an sub-menu 
        //
        //
		if( MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_type == E_MENU_SUB_MENU_ENTRY )
		{

            if( nApplMenuCurrentDepthLevel < (APPL_MENU_DEPTH_LEVELS - 1) )
                nApplMenuCurrentDepthLevel ++;
            
            nApplMenuDepthIndexReturn[ nApplMenuCurrentDepthLevel ] = nApplMenuCurrentDisplayIndex;
            
			nApplMenuCurrentDisplayIndex ++;
		}
		else
        {
        
            //
            //
            // Case 2 - exit an sub-menu
            //
            //
            if( MENU_DISPLAY_ELEMENTS[ nApplMenuCurrentDisplayIndex ].m_menu_type == E_MENU_SUB_MENU_EXIT )
            {
                
                nApplMenuCurrentDisplayIndex = nApplMenuDepthIndexReturn[ nApplMenuCurrentDepthLevel ];
                
                if( nApplMenuCurrentDepthLevel > 0 )
                    nApplMenuCurrentDepthLevel --;
                
            }
            else
            {
                //
                //               
                // Case 3 - enter a normal option !!!
                //
                //
                
                //
                //
                // [ ToDo ]
                //
                //
            }		
        
        }
        
        
        nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
		
	}
	
	
}// end function Appl_Menu_EnterSubMenu





// C. Parascan - v0.1
//
// set the string display position to LOGO
//
void Appl_Menu_SetMenuDisplayLogo(void)
{

	// goto entry "0"
	nApplMenuCurrentDisplayIndex = 0;
	
	// trigger a menu refresh
	//
	nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
	
}// end function ApplMenu_SetMenuDisplayLogo





// C.Parascan 
//
// v0.1 - first implementation
//
// - explicitely triggers a menu refresh
//
//
#if(APPLICATION_MAIN_MENU_HEADER_DIGITS + APPLICATION_MAIN_MENU_VALUE_DIGITS != 8)
	#error This Driver version has been created for only 8 display digits !!!
#endif
//
//
void Appl_Menu_Refresh(void)
{
	

	unsigned char arrMenuValues_OFF_DisplayValue[APPLICATION_MAIN_MENU_VALUE_DIGITS] = { ' ', ' ', ' ', ' ' };

	unsigned char localStringMenuIndex;
	unsigned char localStrinSelectionIndex;
	

	//
	//
	// Display primary menu
	//
	//
	Max7219_Display_String_4digit(MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_header, 0);


	DEBUG_PRINT_HEADER(MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_header[0], 
                       MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_header[1],
                       MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_header[2],
                       MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_header[3]);
    
	DEBUG_PRINT_NEW_LINE();
    
	//
	// in case blinking is activated for the second menu 
	//
	// [ToDO - use macros]
	//
	//

	//
	// check to see if the current character should be turned OFF
	if(nApplMenu_CurrentMenuBlinkState == APPL_MENU_BLINK_STATE_OFF_MESSAGE)
	{
		//
		// send to display ... empty string ... in order to turn off the display
		//
		Max7219_Display_String_4digit(arrMenuValues_OFF_DisplayValue, 4);
	}
	else
	{
	
		//
		// prepare to refresh the second part of the menu
		//
		switch(MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_menu_type)
		{
			
			// -> BOOL <-
			//
			case E_MENU_TYPE_BOOL:
			{
				if(MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data != NULL_PTR)
				{
					
                    /*
					Max7219_Display_Bool_4digit( ( *(int *)MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data ), 4);
					*/
				}
				
				break;
				
			}// end case E_MENU_TYPE_BOOL
			
			
			
			// -> INT <-
			//
			case E_MENU_TYPE_INT:
			{
			
				if( MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data != NULL_PTR )
				{
					/*
					Max7219_Display_Number_4digit( ( *(short *)MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data ), 4);
					*/
				}
				
				break;
				
			}// end case E_MENU_TYPE_INT
			
			
			
			// -> STRING <-
			//
			case E_MENU_TYPE_STRING:
			{
				if( MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data != NULL_PTR )
				{
					
					// get string class index ...
					localStringMenuIndex = ( * (int *)MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data );
					
					// get string offset ...
					localStrinSelectionIndex = ( * ( ( (int *)MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data) + 1 ) );
					
					
				   /*	Max7219_Display_String_4digit(SUB_MENU_STRING_LIST[localStringMenuIndex].mStrList[localStrinSelectionIndex], 4);
                    */
				}
				
				break;
				
			}// end case E_MENU_TYPE_STRING
			
			
			
			// -> value == 4
			//
			case E_MENU_TYPE_FLOAT:
			{
				break;
				
			}// end case E_MENU_TYPE_FLOAT
			
			
			
			// -> ?? unknown or type "none"
			default:
			{
				
				// display default string ...
				//
				//Max7219_Display_String_4digit(MENU_DISPLAY_ELEMENTS[nApplMenuCurrentDisplayIndex].m_ptr_ram_data, 4);
				
			}// end default
			
			
		}// end switch MENU_DISPLAY_CONST[nApplMenuCurrentDisplayIndex].mParamType
	
		
		
	}// end if nApplMenu_CurrentMenuBlinkState == APPL_MENU_BLINK_STATE_OFF_MESSAGE
		

	
}// end function Appl_Menu_Refresh








// C.Parascan
// 
// v0.1 - first implementation
// v0.2 - bugfix
//
void Appl_Menu_MainFunction(void)
{

	//
	// blinking management is done in here
	//
	if(nApplMenu_CurrentMenuBlinkState != APPL_MENU_BLINK_STATE_OFF_MESSAGE)
	{
	
		//
		// check to see if the blinking counter has expired
		//
		if(	nApplMenu_BlinkingCounter > 0)
		{
			nApplMenu_BlinkingCounter --;
		}
		else
		{
			//
			// the counter has expired indicating that a blink stage has been finished
			//
		
			//
			// change the blink state
			//
			if(nApplMenu_CurrentMenuBlinkState == APPL_MENU_BLINK_STATE_ON_MESSAGE)
			{
				nApplMenu_CurrentMenuBlinkState = APPL_MENU_BLINK_STATE_OFF_MESSAGE;
			}
			else
			{
				nApplMenu_CurrentMenuBlinkState = APPL_MENU_BLINK_STATE_ON_MESSAGE;
			}
			
		
			// restart counter
			//
			nApplMenu_BlinkingCounter = APPL_MENU_MAX_BLINKING_DELAY;
			
			
			// trigger a menu refresh
			//
			nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
			
		}// end if
		
	}// end if

	
	
	
	//
	// depending on the state of the menu ... execute actions
	// 
	switch(nApplMenuState)
	{
	
	
		//
		//
		// Power UP SELF TEST
		//
		//
		
	
		//
		// - state in which all the displays are turned on - for the user to see if any burned
		//

		case APPL_MENU_STATE_POWER_UP_TEST_ENTER:
		{
			
			//
			// To Do ... display all segments to ON ...
			//

            DEBUG_PRINT_HEADER('8','8','8','8');
            DEBUG_PRINT_HEADER('8','8','8','8');
            DEBUG_PRINT_NEW_LINE();
            
            
			/* Max7219_Set_to_Display_Test();  ----------------------- add message to queue --------- */
			
			
            
            
			nApplMenuState = APPL_MENU_STATE_POWER_UP_TEST;
			
			nEnterPowerUpTest_Timer = APPLICATION_TIMER_POWER_UP_TEST;
            
            DEBUG_PRINT_STATE(APPLICATION_TIMER_POWER_UP_TEST);
		
			break;
			
		}// end case APPL_MENU_STATE_POWER_UP_TEST_ENTER
		
		
		
		//
		// - state in which all the displays are turned on - for the user to see if any burned
		//
		case APPL_MENU_STATE_POWER_UP_TEST:
		{
			
				if(nEnterPowerUpTest_Timer > 0)
				{
						
					nEnterPowerUpTest_Timer --;
				}
				else
				{
					/* Max7219_Set_to_Display_Normal(); ----------------------- add message to queue ----- */
				
					nEnterPowerUpTest_Timer = 0;
					
					nApplMenuState = APPL_MENU_STATE_LOGO;
					DEBUG_PRINT_STATE(APPL_MENU_STATE_LOGO);
                    
				}
				
				break;
			
		}// end case APPL_MENU_STATE_POWER_UP_TEST
		
		
		

		
		//
		// 
		// display LOGO 
		//
		//
		
		case APPL_MENU_STATE_LOGO:
		{
			
		    
		
			Appl_Menu_SetMenuDisplayLogo();
		
			// trigger a display refresh
			//
			nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH_ENTER;
            
            DEBUG_PRINT_STATE(APPL_MENU_STATE_ACTION_REFRESH_ENTER);
		
			break;
		}
		
		
		
		
		//
		//
		// REFRESH states
		//
		//
		case APPL_MENU_STATE_ACTION_REFRESH_ENTER:
		{
			//
			// to do ... safe -> high power req ...
			//
			//
			/* Max7219_Set_Intensity(APPL_MENU_INTENSITY_NORMAL); ------------------- add message to queue */

		
			nApplMenuState = APPL_MENU_STATE_ACTION_REFRESH;
            
            DEBUG_PRINT_STATE(APPL_MENU_STATE_ACTION_REFRESH);
		
			break;
			
		}// end case
		
		
		
		case APPL_MENU_STATE_ACTION_REFRESH:
		{
			
			//
			// to do request SPI command for refresh ....
			//
			
			//
			// refresh indication all the menues ...
			//
			Appl_Menu_Refresh();
			
			
			//
			// if successfull requests >>>>
			//
			nApplMenuState = APPL_MENU_STATE_IDDLE_HIGH_POWER_ENTER;
            
            DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_HIGH_POWER_ENTER);
			
			
			//
			// todo ... else ... stay in this state and repeat request for spi 
			//
			
			break;
		}
		
		
		//
		//
		// IDDLE and LOW POWER modes
		//
		//
		
		
		
		//
		// - in this state the controller waits for the user interraction
		//
		// - if the user does not interract for the "APPLICATION_TIMER_L1_MAX_COUNT" than the display shall be 
		//   switched to a state of low power - low intensity display 
		//
		case APPL_MENU_STATE_IDDLE_HIGH_POWER_ENTER:
		{
			nEnterEnergySave_L1_Timer = APPLICATION_TIMER_L1_MAX_COUNT;
			
			// prepare for the iddle task ...
			nApplMenuState = APPL_MENU_STATE_IDDLE_HIGH_POWER;
			
            DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_HIGH_POWER);
			
			//
			// To Do ... high power display command
			//
			
			
			break;
		}
		
		
		
		//
		// - wait for any user itteraction
		//
		//
		case APPL_MENU_STATE_IDDLE_HIGH_POWER:
			{
				
				if(nEnterEnergySave_L1_Timer > 0)
				{
						
					nEnterEnergySave_L1_Timer --;
				}
				else
				{
					nEnterEnergySave_L1_Timer = 0;
					
					nApplMenuState = APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1_ENTER;
                    
                    DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1_ENTER);
					
				}
				
				
				// ToDo
				//
				// if any user itteraction indicated by a display ... state change ... than the counter is re-started
				//
				
				
				// ToDo
				// 
				// if any blinking command is required ... than the counter is re-started
				//
				
				
				// ToDo
				//
				//
				
				
				break;
			}
		// end case 
			
			
		
		case APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1_ENTER:
		{
			//
			// To Do ... dimmer the display L1
			//	
			/* Max7219_Set_Intensity(APPL_MENU_INTENSITY_L1); ----------------- add message to queue ---*/

			
			nApplMenuState = APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1;
            
            DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1);
            
			break;
		}
		
		
		
		
		case APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L1:
		{
			
				if(nEnterEnergySave_L2_Timer < APPLICATION_TIMER_L2_MAX_COUNT)
				{
						
					nEnterEnergySave_L2_Timer ++;
				}
				else
				{
					nEnterEnergySave_L2_Timer = 0;
					
					nApplMenuState = APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2_ENTER;
                    
                    DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2_ENTER);
					
				}
				
				break;
		}
		
		

		case APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2_ENTER:
		{
			
			//
			// To Do ... change energy state to save 2 ...
			//
			/* Max7219_Set_Intensity(APPL_MENU_INTENSITY_L2); ---------------- add message to queue ------*/


			nApplMenuState = APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2;
            
            DEBUG_PRINT_STATE(APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2);
			
			break;
		}
		
		

		
		case APPL_MENU_STATE_IDDLE_ENERGY_SAVE_L2:
		{
			
			// stay here undefinitely
            break;
		}
			
		
		
	}// end switch(nApplMenuState)
	
	
}// end function Appl_Menu_MainFunction



