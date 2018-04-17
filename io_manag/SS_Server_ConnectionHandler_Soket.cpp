/*
 *  Extension of connection hadler
 * 
 * 
 */


#include "SS_Server_ConnectionHandler_Soket.h"
#include "./../library/network/SocketServer.h"


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace exploringBB 
{

    
/*
 * v0.1 Constantin Parascan
 *
 * This function is used to retrieve the public key from the server.
 */

int SS_Server_ConnectionHandler_Soket::getPublicKey( char* arrkey, int nSize )
{
    this->b_SessionIsUnlocked = false;

    // [ ToDo ]
    //
    // calculate the public key
    // calculate the private key
    //
    // store both keys
    //
    // return the public key
    //
    //

    return "0";
}


void SS_Server_ConnectionHandler_Soket::setAuthKey(string strMessage, int nStartMessage)
{
    //
    //
    //
    //
    //
} 


/*
 * v0.1 Constantin Parascan
 *
 * This is the main loop of the connection handler on the server.
 *
 * [ ToDo ]
 *     - limit number of connections ...
 *     - after a period of time of innactivity ... kill the connection handler
 */
void SS_Server_ConnectionHandler_Soket::threadLoop()
{
    #ifdef _DEBUG_TRACE_
    cout << "ConnectionHandler::threadLoop --- *** Created a Connection Handler threaded Function ***" << endl;
    #endif
    
    string rec = this->receive(1024);
    
    
    /*
    
    
     *
     *  !! GETTERS !!
     *
     
     if( rec == "getPublicKey" )
     {
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Received from the client [" << rec << "]" << endl;
       #endif
       
       stringstream ss;
       ss << this->getPublicKey();
       
       this->send(ss.str());
       
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Sent [" << ss.str() << "]" << endl;
     }
     
     
     
     
     *
     *  !! SETTERS !!
     *
     
     if( rec.find("setAuthKey") != string::npos )
     {

       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Received from the client [" << rec << "]" << endl;
       #endif
       
       stringstream ss;
       ss << this->setAuthKey( rec,  );
       
       this->send(ss.str());
       
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Sent [" << ss.str() << "]" << endl;     
     
     }
     
 
     if( rec.find("setCmdEncr") != string::npos )
     {

       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Received from the client [" << rec << "]" << endl;
       #endif
       
       stringstream ss;
       ss << this->setCmdEncr();
       
       this->send(ss.str());
       
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Sent [" << ss.str() << "]" << endl;     
     
     }

     
     */
    cout << "Server received: " << rec << endl;
    
    if (rec == "getTemperature")
    {
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Received from the client [" << rec << "]" << endl;
       #endif
       
       stringstream ss;
       ss << "Server message returned --->>" << rec << endl;/* this->getTemperature(this->readAnalog(0)); */
       
       this->send(ss.str());
       
       #ifdef _DEBUG_TRACE_
       cout << "ConnectionHandler::threadLoop --- Sent [" << ss.str() << "]" << endl;
       #endif
    }
    else 
    {
       #ifdef _DEBUG_TRACE_
       cout << "Received from the client [" << rec << "]" << endl;
       #endif
       
       this->send(string("Unknown Command"));
    }
    
    #ifdef _DEBUG_TRACE_
    cout << "*** End of the Temperature Connection Handler Function" << endl;
    #endif
    
    this->parent->notifyHandlerDeath(this);
}

    
    
}
