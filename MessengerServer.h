#ifndef MESSANGER_SERVER
#define MESSANGER_SERVER

#include <string>
#include <map>
#include <vector>
#include <mutex>

#include "ServerSocket.h"

class ClientSocket;

typedef std::map<ServerSocket*, std::string> ClientsPool;

class MessengerServer
{
public:
	MessengerServer(int port = 30000);
	~MessengerServer();
protected:
    void ClientsListener(ServerSocket* serverSocket);
    void ClientsAccepter();
    
    std::mutex m_poolMutex;
	ServerSocket* m_thisSocket;
	ClientsPool m_clientsPool;
	//std::vector<std::pair<ClientSocket, ClientSocket>> m_clientsBindings;
};


#endif//MESSENGER_SERVER
