#include "MessengerClient.h"

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <algorithm>

void Reciever(MessengerClient* messengerClient)
{
	while(true)
	{
		std::string message;
		*(messengerClient->m_thisSocket) >> message;
		
     	std::for_each(message.begin(), message.end(), [](char& it){
     	    if( (it) == '_')
     	        (it) =  ' ';
     	});
     	
		std::string systemCall = "notify-send ";
		systemCall.append(message);
		system(systemCall.c_str());
		//std::cout << message;
	}
}


void Sender(MessengerClient* messengerClient)
{
	while(true)
	{
		std::string message;
		std::cin >> message;
		
     	std::for_each(message.begin(), message.end(), [](char& it){
     	    if( (it) == ' ')
     	        (it) =  '_';
     	});
     	
		*(messengerClient->m_thisSocket) << message;
	}
}
MessengerClient::MessengerClient(int port)
      	: m_thisSocket( nullptr )
{
        m_thisSocket = new ClientSocket("localhost", 30000 );
        
     	std::thread recieverThread = std::thread(Reciever, this);
     	std::thread senderThread = std::thread(Sender, this);

	senderThread.join();
	recieverThread.join();
}

MessengerClient::~MessengerClient()
{
	delete m_thisSocket;//m_thisSocket.close();
}
