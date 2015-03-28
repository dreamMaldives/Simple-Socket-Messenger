#ifndef MESSANGER_SERVER
#define MESSANGER_SERVER

#include <string>
#include <map>
#include <vector>

#include "ServerSocket.h"

class ClientSocket;

typedef std::map<std::string, ServerSocket*> ClientsPool;

class MessengerServer
{
public:
	MessengerServer(int port = 30000);
	~MessengerServer();
	ServerSocket* m_thisSocket;
	ClientsPool m_clientsPool;
protected:
	//std::vector<std::pair<ClientSocket, ClientSocket>> m_clientsBindings;
};


#endif//MESSENGER_SERVER
