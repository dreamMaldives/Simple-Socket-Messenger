
#include "MessengerServer.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <thread>



void ClientsListener(MessengerServer* messengerServer, ServerSocket* serverSocket)
{
	while ( true )
	{
		std::string message;
     		*(serverSocket) >> message;
		//Shared Lock
		for(ClientsPool::iterator it = messengerServer->m_clientsPool.begin(); 
			it != messengerServer->m_clientsPool.end(); 
			++it)
		{
		//	if(it->second != serverSocket)
		//	{
				*(it->second) << it->first << std::string(": ") << message;
		//	}
		}
		//Shared UnLock
	}
}

void ClientsAccepter(MessengerServer* messengerServer)
{
    // Create the socket
    messengerServer->m_thisSocket = new ServerSocket( 30000 );
        
	while ( true )
	{
	
	  try
	  {
	      ServerSocket* newSock = new ServerSocket;
	      messengerServer->m_thisSocket->accept ( *newSock );
	      std::cout << "Socket accepted\n";
	      std::string clientName;
	      std::string askName("Who are you?");
	      *newSock << askName;
	      *newSock >> clientName;
	      std::cout << "Name: "<< clientName << "\n";
	      
	  
//Lock mutex here;
	  messengerServer->m_clientsPool.insert( std::pair<std::string, ServerSocket*>(clientName, newSock));
//UnLock mutex here;
	
//Run thread to listen newSock
	  std::thread clientListener = std::thread(ClientsListener, messengerServer,  newSock);
	  clientListener.detach();
//Wait for next client
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
        std::thread acceptor(ClientsAccepter, this);
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
