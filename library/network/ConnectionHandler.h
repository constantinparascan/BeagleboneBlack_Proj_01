/*
 * ConnectionHandler.h  Created on: 18 Jul 2014
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

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<iostream>

namespace exploringBB 
{

class SocketServer;

class ConnectionHandler 
{
public:
   ConnectionHandler(SocketServer *parent, sockaddr_in *client, int clientSocketfd);
   virtual ~ConnectionHandler();

   int start();
   void wait();
   void stop() { this->running = false; }


   /* void setAuthKey(string strMessage, int nStartMessage);  */

   virtual int send(std::string message);
   virtual std::string receive(int size);

protected:
	virtual void threadLoop();

private:
   sockaddr_in *client;
   int 	       clientSocketfd;
   pthread_t   thread;
   SocketServer *parent;
   bool        running;

   int readAnalog(int number);
   int getTemperature(int adc_value);
   
   /* 
    * This function shall return a ssh public key
    */
   std::string getPublicKey( void );
   bool b_SessionIsUnlocked;
   

   static void * threadHelper(void * handler)
   {
   	  ((ConnectionHandler *)handler)->threadLoop();
   	  return NULL;
   }
};

} /* namespace exploringBB */

#endif /* CONNECTIONHANDLER_H_ */
