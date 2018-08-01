#include "Appl_Menu.h"
#include "Appl_Menu_Cfg.h"

#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>


struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) 
    {
        printf(" %d ", r);
        return r;
    } else 
    {
        printf(" %d ", (int)c);
        return c;
    }
}


int main(void)
{
    int key = 0;
    unsigned char nValue;

    //set_conio_terminal_mode();
    
   // Appl_Menu_Init();
    
    printf("\n\n --------------------------- Start Test ------------------------------\n\n");
    
    
    while(1)
    {
        printf("[]");
        scanf("%c", &nValue);
        
        switch(nValue)
        {
            case 'A':
            case 'a':
            {
                printf("\nLEFT: ");
                break;
            }
            
            case 'D':
            case 'd':
            {
                printf("\nRIGHT: ");
                break;
            }
            
            case 'Q':
            case 'q':
            {
                printf("\nQuit ");
                exit(0);
                break;
            }

                
        }
        
        
        //Appl_Menu_MainFunction();
        
        /*
         *  process keyboard triggers
         */ 
        
        //usleep(100000);

        
        //printf("\n\r call ... start ");
/*        
        
        if( kbhit() )
        {
            key = getch();
            // if the first value is esc
            if (key == 27) 
            { 
                key = getch(); // skip the [
                key = getch();
                
                switch(key) 
                {   // the real value
                    case 'A':
                    printf("\n UP ");
                    //Appl_Menu_ScrollUp();
                    // code for arrow up
                    break;
                    
                    case 'B':
                    printf("\n DOWN ");
                    //Appl_Menu_ScrollDown();
                    // code for arrow down
                    break;
                    
                    
                    case 'C':
                    printf("\n RIGHT ");
                    //Appl_Menu_ExitSubMenu();
                    // code for arrow right
                    break;
                    
                    case 'D':
                    printf("\n LEFT ");  
                    //Appl_Menu_EnterSubMenu();
                    // code for arrow left
                    break;
                }
            }else
            {
                
                exit(0);
            }
        }
*/
        //printf("\n\r call ... end \n\n\r ");
        
        
    }

}
