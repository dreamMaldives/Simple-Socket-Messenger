
#include "MessengerServer.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>



void MessengerServer::ClientsListener(ServerSocket* serverSocket)
{
	while ( true )
	{
		std::string message;
     		*(serverSocket) >> message;
     		     	
        std::lock_guard<std::mutex> locker(m_poolMutex);
        std::string senderName = this->m_clientsPool.at(serverSocket);
		for(ClientsPool::iterator it = this->m_clientsPool.begin(); 
			it != this->m_clientsPool.end(); 
			++it)
		{
			if(it->first != serverSocket)
			{
				*(it->first) << senderName << std::string(": ") << message;
			}
		}
	}
}

void MessengerServer::ClientsAccepter()
{
    // Create the socket
    this->m_thisSocket = new ServerSocket( 30000 );
        
	while ( true )
	{	
	  try
	  {
	      ServerSocket* newSock = new ServerSocket;
	      this->m_thisSocket->accept ( *newSock );
	      std::cout << "Socket accepted\n";
	      std::string clientName;
	      std::string askName("Who are you?");
	      *newSock << askName;
	      *newSock >> clientName;
	      std::cout << "Name: "<< clientName << "\n";
	      
	      
          m_poolMutex.lock();
	      this->m_clientsPool.insert( std::pair<ServerSocket*, std::string>(newSock, clientName));
          m_poolMutex.unlock();
	
    //Run thread to listen newSock
	      std::thread clientListener = std::thread( &MessengerServer::ClientsListener, this,  newSock);
	      clientListener.detach();
	  }
	  catch ( SocketException& e )
	  {	  
            std::cout << "Exception was caught:" << e.description() << "\nContinue.\n";
      }
	}
}


MessengerServer::MessengerServer(int port)
    : m_thisSocket(nullptr)
{

try
    {
        std::thread acceptor( &MessengerServer::ClientsAccepter, this);
	    acceptor.join();
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}

MessengerServer::~MessengerServer()
{
    delete m_thisSocket;
}
