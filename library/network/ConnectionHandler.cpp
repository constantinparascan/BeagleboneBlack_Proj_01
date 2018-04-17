/*
 * ConnectionHandler.cpp  Created on: 18 Jul 2014
 * Copyright (c) 2014 Derek Molloy (www.derekmolloy.ie)
 * Made available for the book "Exploring BeagleBone" 
 * See: www.exploringbeaglebone.com
 * Licensed under the EUPL V.1.1
 *
 * This Software is provided to You under the terms of the European 
 * Union Public License (the "EUPL") version 1.1 as published by the 
 * European Union. Any use of this Software, other than as authorized 
 * under this License is strictly prohibited (to the extent such use 
 * is covered by a right of the copyright holder of this Software).
 * 
 * This Software is provided under the License on an "AS IS" basis and 
 * without warranties of any kind concerning the Software, including 
 * without limitation merchantability, fitness for a particular purpose, 
 * absence of defects or errors, accuracy, and non-infringement of 
 * intellectual property rights other than copyright. This disclaimer 
 * of warranty is an essential part of the License and a condition for 
 * the grant of any rights to this Software.
 * 
 * For more details, see http://www.derekmolloy.ie/
 */

#include "ConnectionHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SocketServer.h"

using namespace std;

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

namespace exploringBB 
{

ConnectionHandler::ConnectionHandler(SocketServer *parent, sockaddr_in *client, int clientSocketfd) 
{
   this->parent = parent;
   this->client = client;
   this->running = true;
   this->clientSocketfd = clientSocketfd;
   
   this->b_SessionIsUnlocked = false;
   
   //cout << "Created a Connection Handler" << endl;
}

ConnectionHandler::~ConnectionHandler() 
{
   delete this->client;
   cout << "Destroyed a Connection Handler" << endl;
}



int ConnectionHandler::start()
{
   cout << "Starting the Connection Handler thread" << endl;
   
   
   // pthread_create - create a new thread
   // used with:
   //        #include <pthread.h>
   //
   //
   //   >>> int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
   //                void *(*start_routine) (void *), void *arg);
   //
   //
   return (pthread_create(&(this->thread), NULL, threadHelper, this)==0);
}




void ConnectionHandler::wait()
{
	(void) pthread_join(this->thread, NULL);
}

int ConnectionHandler::send(std::string message)
{
	const char *writeBuffer = message.data();
	int length = message.length();
	
    int n = write(this->clientSocketfd, writeBuffer, length);
    
    if (n < 0)
    {
       perror("Connection Handler: error writing to server socket.");
       return 1;
    }
    return 0;
}

string ConnectionHandler::receive(int size=1024)
{
    char readBuffer[size];
    
    int n = read(this->clientSocketfd, readBuffer, sizeof(readBuffer));
    
    if (n < 0)
    {
       perror("Connection Handler: error reading from server socket.");
    }
    return string(readBuffer);
}

int ConnectionHandler::readAnalog(int number)
{ // returns the input as an int
   stringstream ss;
   ss << LDR_PATH << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

int ConnectionHandler::getTemperature(int adc_value)
{
	/*
   float cur_voltage = adc_value * (1.80f/4096.0       f);
   float diff_degreesC = (cur_voltage-0.75f)/0.01f;
   return (25.0f + diff_degreesC);
   */
	return 10;
}

/*
 * v0.1 Constantin Parascan
 *
 * This function is used to retrieve the public key from the server.
 */
/*
string ConnectionHandler::getPublicKey( void )
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
*/

/*
void ConnectionHandler::setAuthKey(string strMessage, int nStartMessage)
{
    //
    //
    //
    //
    //
}
*/


/*
 * v0.1 Constantin Parascan
 *
 * This is the main loop of the connection handler on the server.
 *
 * [ ToDo ]
 *     - limit number of connections ...
 *     - after a period of time of innactivity ... kill the connection handler
 */
void ConnectionHandler::threadLoop()
{
    #ifdef _DEBUG_TRACE_
    cout << "ConnectionHandler::threadLoop --- *** Created a Connection Handler threaded Function ***" << endl;
    #endif
    
    string rec = this->receive(1024);
    
    
    /*
    
    msgtype_1
    
        receive
        
            [key](nr)xxxxxx      <<< key number nr contents  (means use this key when talking to mine )
            [cha](nr)xxxxxxxx    <<< challenge request using key encryption "nr" -- responde using key "nr"
                                     to encrypted data xxxxxxxxx
    
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

} /* namespace exploringBB */
