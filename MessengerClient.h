#ifndef MESSENGER_CLIENT
#define MESSENGER_CLIENT

#include <string>

#include "ClientSocket.h"

class ClientSocket;

class MessengerClient
{
public:
	MessengerClient(int port = 30000);
	~MessengerClient();
	ClientSocket* m_thisSocket;
protected:
};



#endif//MESSENGER_CLIENT
