/* A program for a threaded Temperature Server
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "../library/network/SocketServer.h"

#include "Soket_Server_Versions.h"

using namespace std;
using namespace exploringBB;


void Soket_Server_Display_Version(void);
void Soket_Server_Display_Help(void);


unsigned int nSoketServer_listeningPort = 0;

/*
 * v0.1
 * 
 * parameters supported
 * 
 * -v           - version
 * -h           - help
 * -p port_id   - listen on specific port for incomming connections
 * 
 */

int main(int argc, char *argv[])
{
    
    unsigned char nCurrentArgumentToProcess = 0;
    
    
    /* check input arguments */
    if(argc <= 1)
    {

        Soket_Server_Display_Version();
        Soket_Server_Display_Help();
        
        
        return 0;
        
    }
    else
    {
    
       /* 
        *  Process user request
        */
    
        nCurrentArgumentToProcess = 1;
        
        
       for ( nCurrentArgumentToProcess = 1; nCurrentArgumentToProcess < argc; nCurrentArgumentToProcess++ ) 
       {
            /* We will iterate over argv[] to get the parameters stored inside.
             * Note that we're starting on 1 because we don't need to know the 
             * path of the program, which is stored in argv[0] */
            
//            if (nCurrentArgumentToProcess < argc)
            {
                // Check that we haven't finished parsing already
                if ( strcmp(argv[ nCurrentArgumentToProcess ], "-h") == 0 ) 
                {
                    
                    Soket_Server_Display_Help();
                    
                    return 0;
                } 
                
                if ( strcmp(argv[ nCurrentArgumentToProcess ], "-v") == 0) 
                {
                    Soket_Server_Display_Version();
                    
                    return 0;
                } 
                
                if ( strcmp(argv[ nCurrentArgumentToProcess ], "-p") == 0) 
                {
                    if(( nCurrentArgumentToProcess + 1)  < argc)
                    {
                        nSoketServer_listeningPort = atoi(argv[nCurrentArgumentToProcess + 1]);
                        
                        cout << "Listening on port : " << nSoketServer_listeningPort << endl;
                    }
                } 
                
            }
        
            
        }
    }
    
    /* input parameter parsing ... ended */
    
    
    
    /* ToDo ... Server execution */
    
    cout << "Starting Server on port: " << nSoketServer_listeningPort << endl;
    
    SocketServer server( (int)nSoketServer_listeningPort );
    
    server.threadedListen();
    
    cout << "Server has exit. By" << endl;
    
/*
   cout << "Starting EBB Server Example" << endl;
   SocketServer server(5555);
   cout << "Listening for a connection..." << endl;
   server.threadedListen();
   cout << "End of EBB Server Example" << endl;
*/
}

void Soket_Server_Display_Version(void)
{
    cout << "Soket Server version " << SOKET_SERVER_MAIN_ENGINE_BASE_VER << "." << SOKET_SERVER_MAIN_ENGINE_PATCH_VER << endl;
}

void Soket_Server_Display_Help(void)
{
    cout << "Soket Server version " << SOKET_SERVER_MAIN_ENGINE_BASE_VER << "." << SOKET_SERVER_MAIN_ENGINE_PATCH_VER << endl;
    cout << "Usage: " << endl;
    cout << " -h --> display help and terminate execution" << endl;
    cout << " -v --> display version and terminate execution" << endl;
    cout << " -p [port_ID] --> listen to specific port ID" << endl;
}
