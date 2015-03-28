# Makefile for the socket programming example
#

#simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
#simple_client_objects = ClientSocket.o Socket.o simple_client_main.o

messenger_server_objects = ServerSocket.o MessengerServer.o Socket.o messenger_server_main.o
messenger_client_objects = ClientSocket.o MessengerClient.o Socket.o messenger_client_main.o

CXXFLAGS += -std=c++11 -pthread

all : messenger_server messenger_client

messenger_server: $(messenger_server_objects)
	g++ $(messenger_server_objects) -o messenger_server -pthread


messenger_client: $(messenger_client_objects)
	g++ $(messenger_client_objects) -o messenger_client -pthread


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
MessangerServer: MessengerServer.cpp
MessangerClient: MessengerClient.cpp
messenger_server_main: messenger_server_main.cpp
messenger_client_main: messenger_client_main.cpp


clean:
	rm -f *.o messenger_server messenger_client
