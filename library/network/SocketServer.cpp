/*
 * SocketServer.cpp  Created on: 13 Jul 2014
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

#include "SocketServer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
using namespace std;

namespace exploringBB {

SocketServer::SocketServer(int portNumber) 
{
	this->socketfd = -1;
	this->clientSocketfd = -1;
	this->portNumber = portNumber;
	this->clientConnected = false;
	this->connections = vector<ConnectionHandler *>();
}

int SocketServer::listen()
{
    /*  Try to open a soket ...
     */ 
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /*  If the soket has been successful opened ... continue ...
     */
    if (this->socketfd < 0)
    {
    	perror("Socket Server: error opening socket.\n");
    	return 1;
    }
    
    //bzero((char *) &serverAddress, sizeof(serverAddress));
    memset((char *) &serverAddress, 0, sizeof(serverAddress));
    
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    /*
     * uint16_t htons(uint16_t hostshort);
     * 
     * The htons() function converts the unsigned short integer hostshort
     * from host byte order to network byte order.
     * On the i386 the host byte order is Least Significant Byte first,
     *     whereas the network byte order, as used on the Internet, is Most
     *     Significant Byte first
     */
    serverAddress.sin_port = htons(this->portNumber);
    
    
    /* 
        bind - bind a name to a socket     
     
        #include <sys/types.h>        
        #include <sys/socket.h>

       int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     
     
        When a socket is created with socket(2), it exists in a name space
            (address family) but has no address assigned to it.  bind() assigns
            the address specified by addr to the socket referred to by the file
            descriptor sockfd.  addrlen specifies the size, in bytes, of the
            address structure pointed to by addr.  Traditionally, this operation
            is called “assigning a name to a socket”.
            
       It is normally necessary to assign a local address using bind()
       before a SOCK_STREAM socket may receive connections (see accept(2)).
       
       The actual structure passed for the addr argument will depend on the
       address family.  The sockaddr structure is defined as something like:

           struct sockaddr {
               sa_family_t sa_family;
               char        sa_data[14];
           }

       The only purpose of this structure is to cast the structure pointer
       passed in addr in order to avoid compiler warnings.  
       
       On success, zero is returned.  On error, -1 is returned, and errno is
       set appropriately.
        
     */
     
    if (bind(socketfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
    	perror("Socket Server: error on binding the socket.\n");
    	return 1;
    }
    
    ::listen(this->socketfd, 5);
    socklen_t clientLength = sizeof(this->clientAddress);
    
    this->clientSocketfd = accept(this->socketfd,
    		(struct sockaddr *) &this->clientAddress,
    		&clientLength);
    		
    		
    if (this->clientSocketfd < 0)
    {
    	perror("Socket Server: Failed to bind the client socket properly.\n");
    	return 1;
    }
    
    // return success ...
    return 0;
}

int SocketServer::threadedListen()
{

    
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (this->socketfd < 0)
    {
    	perror("Socket Server: error opening socket.\n");
    	return 1;
    }
    
    bzero((char *) &serverAddress, sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->portNumber);
    
    if (bind(socketfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
    	perror("Socket Server: error on binding the socket.\n");
    	return 1;
    }
    
    
    // listen - listen for connections on a socket
    // used with:
    //      #include <sys/socket.h>
    //      #include <sys/types.h>
    //
    //   >> int listen(int sockfd, int backlog);
    //
    //      - The sockfd argument is a file descriptor that refers to a socket 
    //              of type SOCK_STREAM or SOCK_SEQPACKET.
    //      - The backlog argument defines the maximum length to which the queue 
    //              of pending connections for sockfd may grow. If a connection 
    //              request arrives when the queue is full, the client may receive 
    //              an error with an indication of ECONNREFUSED or, if the 
    //              underlying protocol supports retransmission, the request may 
    //              be ignored so that a later reattempt at connection succeeds.
    //
    //      - On success, zero is returned. On error, -1 is returned, and errno is set appropriately.
    //
    ::listen(this->socketfd, 5);
    
    while(true)
    {
  	    struct sockaddr_in *temp = new (struct sockaddr_in)();
		socklen_t tempLength = sizeof(*temp);
		
		// accept - accept a new connection on a socket
		// used with:
		//      #include <sys/socket.h>
		//
		//  >>> int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
		//
		//  The accept() function shall extract the first connection on the queue 
		//      of pending connections, create a new socket with the same socket 
		//      type protocol and address family as the specified socket, and 
		//      allocate a new file descriptor for that socket.
		//
		//      - socket Specifies a socket that was created with socket(), 
		//          has been bound to an address with bind(), 
		//          and has issued a successful call to listen().
		//      - address Either a null pointer, or a pointer to a sockaddr structure 
		//          where the address of the connecting socket shall be returned.
		//      - address_len Points to a socklen_t structure which on input 
		//          specifies the length of the supplied sockaddr structure, 
		//          and on output specifies the length of the stored address.
		//
		//      - Upon successful completion, accept() shall return the 
		//          non-negative file descriptor of the accepted socket. 
		//          Otherwise, -1 shall be returned and errno set to indicate the error.
		//
		//
		//  +++ the call to accept() is a blocking call: 
		//      the function does not return until there is a client connecting to the server. 
		//      code execution for the thread which called the accept() function is halted, and does not take any processing power.
		//
        //      think of accept() as a call to join() or like a wait on a mutex/lock/semaphore.
		//
		//  +++  this function is difficult to cancel, so there exists non-blocking alternatives 
		//       which will allow the server to perform other actions while waiting for an incoming connection. 
		//       one such alternative is using select(). 
		//
		int tempSocketfd = accept(this->socketfd, (struct sockaddr *) temp, &tempLength);
		
		if (tempSocketfd < 0)
		{
			perror("Socket Server: Failed to bind the threaded client socket properly.\n");
			return 1;
		}
		else 
		{
			printf("Valid socket\n");
			
			ConnectionHandler *conn = new ConnectionHandler(this, temp, tempSocketfd);
			
			// The push_back() function insert elements into the end of the vector, 
			//      and is usually fastest.
			this->connections.push_back(conn);
			
			//
			// Creates the soket connection THREAD !
			//
			conn->start();
		}
    }
}

int SocketServer::send(std::string message)
{
	const char *writeBuffer = message.data();
	int length = message.length();
    int n = write(this->clientSocketfd, writeBuffer, length);
    if (n < 0)
    {
       perror("Socket Server: error writing to server socket.");
       return 1;
    }
    return 0;
}

string SocketServer::receive(int size=1024)
{
    char readBuffer[size];
    int n = read(this->clientSocketfd, readBuffer, sizeof(readBuffer));
    if (n < 0)
    {
       perror("Socket Server: error reading from server socket.");
    }
    return string(readBuffer);
}

/*
 *  Checks that connection handler is inside "connections" array ... and if so ... it erases the element from the array
 * 
 *  ... and also the connection given as parameter ... 
 * 
 */
void SocketServer::notifyHandlerDeath(ConnectionHandler *connection)
{
   std::vector<ConnectionHandler *>::iterator it;
   
   for(it = this->connections.begin(); it <= this->connections.end(); it++ )
   {
    
       /*
        * [ ToDo ] --- is this correct ? *it ??? and not it ???
        */
      if ( *it == connection)
      {
         this->connections.erase(it);
         
         printf("Server: Found and deleted the connection reference...");
      }
   }
   
   delete connection;
}

SocketServer::~SocketServer() 
{
	close(this->socketfd);
	close(this->clientSocketfd);
}

} /* namespace exploringBB */
