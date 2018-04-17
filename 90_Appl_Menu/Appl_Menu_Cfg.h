#ifndef __APPL_MENU_CFG_V2_H__
#define __APPL_MENU_CFG_V2_H__

#include "Appl_Menu.h"

#define APPL_MENU_DEPTH_LEVELS (3)

// defines the blinking transition on/off delays
//
#define APPL_MENU_MAX_BLINKING_DELAY (20)


// - defines how many menu entry exists
#define APPLICATION_MAIN_MENU_COUNTS (5)
#define APPLICATION_MAIN_MENU_COUNTS_TOTAL (7)




extern const T_MENU_ELEMENT MENU_DISPLAY_ELEMENTS[];
extern const T_SUB_MENU_STRING_LIST  SUB_MENU_STRING_LIST[];




// - used to indicate a delay during the Power on - in which case
// all the LED's are fully powered - for the user to check if any damaged
//
#define APPLICATION_TIMER_POWER_UP_TEST (0x0004)

#define APPLICATION_TIMER_L1_MAX_COUNT  (0x000F)
#define APPLICATION_TIMER_L2_MAX_COUNT  (0x000F)





//
// here must be defined all the external variables used by the MENU elements
//

#endif
