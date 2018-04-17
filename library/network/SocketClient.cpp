/*
 * SocketClient.cpp  Created on: 2 Jul 2014
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

#include "SocketClient.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
using namespace std;

namespace exploringBB 
{


SocketClient::SocketClient(std::string serverName, int portNumber) 
{
	this->socketfd = -1;
	this->server = NULL;
	this->serverName = serverName;
	this->portNumber = portNumber;
	this->isConnected = false;
}


int SocketClient::connectToServer()
{

    /*
       socket() creates an endpoint for communication and returns a file
       descriptor that refers to that endpoint.

       The domain argument specifies a communication domain; this selects
       the protocol family which will be used for communication.  These
       families are defined in <sys/socket.h>.  The currently understood
       formats include:

       Name                Purpose                          Man page
       AF_UNIX, AF_LOCAL   Local communication              unix(7)
       AF_INET             IPv4 Internet protocols          ip(7)
       AF_INET6            IPv6 Internet protocols          ipv6(7)
       AF_IPX              IPX - Novell protocols
       AF_NETLINK          Kernel user interface device     netlink(7)
       AF_X25              ITU-T X.25 / ISO-8208 protocol   x25(7)
       AF_AX25             Amateur radio AX.25 protocol
       AF_ATMPVC           Access to raw ATM PVCs
       AF_APPLETALK        AppleTalk                        ddp(7)
       AF_PACKET           Low level packet interface       packet(7)
       AF_ALG              Interface to kernel crypto API

       The socket has the indicated type, which specifies the communication
       semantics.  Currently defined types are:

       SOCK_STREAM     Provides sequenced, reliable, two-way, connection-
                       based byte streams.  An out-of-band data transmission
                       mechanism may be supported.

       SOCK_DGRAM      Supports datagrams (connectionless, unreliable
                       messages of a fixed maximum length).

       SOCK_SEQPACKET  Provides a sequenced, reliable, two-way connection-
                       based data transmission path for datagrams of fixed
                       maximum length; a consumer is required to read an
                       entire packet with each input system call.

       SOCK_RAW        Provides raw network protocol access.

       SOCK_RDM        Provides a reliable datagram layer that does not
                       guarantee ordering.

       SOCK_PACKET     Obsolete and should not be used in new programs; see
                       packet(7).

       Some socket types may not be implemented by all protocol families.

       Since Linux 2.6.27, the type argument serves a second purpose: in
       addition to specifying a socket type, it may include the bitwise OR
       of any of the following values, to modify the behavior of socket():

       SOCK_NONBLOCK   Set the O_NONBLOCK file status flag on the new open
                       file description.  Using this flag saves extra calls
                       to fcntl(2) to achieve the same result.

       SOCK_CLOEXEC    Set the close-on-exec (FD_CLOEXEC) flag on the new
                       file descriptor.  See the description of the
                       O_CLOEXEC flag in open(2) for reasons why this may be
                       useful.
     */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socketfd < 0)
    {
    	perror("Socket Client: error opening socket.\n");
    	return 1;
    }
    
    
    /*
        !!! ABSOLETE !!!
    */
    server = gethostbyname(serverName.data());
    
    if (server == NULL) 
    {
        perror("Socket Client: error - no such host.\n");
        return 1;
    }
    
    // set all values to "0"
    bzero((char *) &serverAddress, sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    
    // byte copy ...
    bcopy((char *)server->h_addr,(char *)&serverAddress.sin_addr.s_addr, server->h_length);
    
    // converts the unsigned short integer hostshort from host byte order to network byte order.
    serverAddress.sin_port = htons(portNumber);



    /*
     * ====================== Connect =========================== 
     */

    /*  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    
        The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. 
        The addrlen argument specifies the size of addr. 
        The format of the address in addr is determined by the address space of the socket sockfd
     */
    if (connect(socketfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
    	perror("Socket Client: error connecting to the server.\n");
    	return 1;
    }
    
    this->isConnected = true;
    return 0;
}


int SocketClient::send(std::string message)
{

    /*
     * [ToDo] Here we should check if the client is connected to a server !!!
     *
     */


	const char *writeBuffer = message.data();

	int length = message.length();

    /*
    
        write - write to a file descriptor
        
        #include <unistd.h>

           ssize_t write(int fd, const void *buf, size_t count);
           
        write() writes up to count bytes from the buffer pointed buf to the
       file referred to by the file descriptor fd.

       The number of bytes written may be less than count if, for example,
       there is insufficient space on the underlying physical medium, or the
       RLIMIT_FSIZE resource limit is encountered (see setrlimit(2)), or the
       call was interrupted by a signal handler after having written less
       than count bytes.  (See also pipe(7).)
       
       On success, the number of bytes written is returned (zero indicates
       nothing was written).  It is not an error if this number is smaller
       than the number of bytes requested; this may happen for example
       because the disk device was filled.  
       
       On error, -1 is returned, and errno is set appropriately.   
    */

    int n = write(this->socketfd, writeBuffer, length);

    if (n < 0)
    {
       perror("Socket Client: error writing to socket");
       return 1;
    }
    
    return 0;
}


string SocketClient::receive(int size=1024)
{
    char readBuffer[size];
    
    bzero(readBuffer, size);
    
    
    /*
    
        read - read from a file descriptor
        
        #include <unistd.h>

            ssize_t read(int fd, void *buf, size_t count);
    
        read() attempts to read up to count bytes from file descriptor fd
       into the buffer starting at buf.

       On files that support seeking, the read operation commences at the
       file offset, and the file offset is incremented by the number of
       bytes read.  If the file offset is at or past the end of file, no
       bytes are read, and read() returns zero.

       If count is zero, read() may detect the errors described below.  In
       the absence of any errors, or if read() does not check for errors, a
       read() with a count of 0 returns zero and has no other effects.

       If count is greater than SSIZE_MAX, the result is unspecified.

    
        On success, the number of bytes read is returned (zero indicates end
       of file), and the file position is advanced by this number.  It is
       not an error if this number is smaller than the number of bytes
       requested; this may happen for example because fewer bytes are
       actually available right now (maybe because we were close to end-of-
       file, or because we are reading from a pipe, or from a terminal), or
       because read() was interrupted by a signal. 

       On error, -1 is returned, and errno is set appropriately.  In this
       case, it is left unspecified whether the file position (if any)
       changes.
    
     */
     
    
    int n = read(this->socketfd, readBuffer, sizeof(readBuffer));
    
    if (n < 0)
    {
       perror("Socket Client: error reading from socket");
    }
    
    return string(readBuffer);
}

/*
string SocketClient::receiveAll()
{
	//int recv_all(int sockfd, void *buf, size_t len, int flags)
    size_t toread = len;
    char  *bufptr = (char*) buf;
    while (toread > 0)
    {
        ssize_t rsz = recv(sockfd, bufptr, toread, 0);
        if (rsz <= 0)
            return rsz;  //Error or other end closed cnnection

        toread -= rsz;  // Read less next time
        bufptr += rsz;  // Next buffer position to read into
    }
    return len;
}
*/

int SocketClient::disconnectFromServer()
{
	this->isConnected = false;
	
	close(this->socketfd);
	
	return 0;
}

SocketClient::~SocketClient() 
{
	if (this->isConnected == true)
	{
		disconnectFromServer();
	}
}

} /* namespace exploringBB */
