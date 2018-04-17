/*
 *  Extension of connection hadler
 * 
 * 
 */

#ifndef SS_SERVER_CONNECTIONHANDLER_SOKET_H_
#define SS_SERVER_CONNECTIONHANDLER_SOKET_H_

namespace exploringBB 
{
 
class SocketServer;    
    
class SS_Server_ConnectionHandler_Soket :public ConnectionHandler
{
        
      
    SS_Server_ConnectionHandler_Soket(SocketServer *parent, sockaddr_in *client, int clientSocketfd)
    {
        ::ConnectionHandler(parent, client, clientSocketfd);
    }
        
    virtual ~SS_Server_ConnectionHandler_Soket();

        
        
        
        //int  start();
        //void wait();
        //void stop() { this->running = false; }

        
        
        

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
        float getTemperature(int adc_value);
        
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
    
}

#endif // SS_SERVER_CONNECTIONHANDLER_SOKET_H_