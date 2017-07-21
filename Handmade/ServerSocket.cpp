#include <iostream>
#include "ServerSocket.h"

//------------------------------------------------------------------------------------------------------
//constructor that allocates a maximum of 3 client sockets
//------------------------------------------------------------------------------------------------------
ServerSocket::ServerSocket()
{

	m_socketSet = SDLNet_AllocSocketSet(3);

}
//------------------------------------------------------------------------------------------------------
//function that opens up a connection socket using resolved IP and port number 
//------------------------------------------------------------------------------------------------------
bool ServerSocket::Open()
{

	m_socket = SDLNet_TCP_Open(&m_IP);

	if (!m_socket)
	{
		std::cout << "Could not open socket connection." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that checks if a particular client socket has activity
//------------------------------------------------------------------------------------------------------
bool ServerSocket::Check(std::string mapIndex)
{

	//run a check on all sockets and if any of them have 
	//data check the individual socket using passed ID
	//either none of the sockets have data waiting OR some
	//sockets do have data ready, just not this particular socket
	
	if(SDLNet_CheckSockets(m_socketSet, 0) > 0 && SDLNet_SocketReady(m_clientSockets[mapIndex]))
	{
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that listens for an incoming client connection 
//------------------------------------------------------------------------------------------------------
bool ServerSocket::Listen(std::string mapIndex)
{

	TCPsocket tempSocket = nullptr;

	//if client has connected, server will establish a connection and save it
	tempSocket = SDLNet_TCP_Accept(m_socket);

	//once a client has connected add it to the socket map and socket set
	if (tempSocket)
	{
		m_clientSockets[mapIndex] = tempSocket;
		SDLNet_TCP_AddSocket(m_socketSet, tempSocket);
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends a passed message via the connection socket
//------------------------------------------------------------------------------------------------------
bool ServerSocket::SendMessage(std::string mapIndex, std::string& message)
{

	int length = message.length() + 1;

	if (SDLNet_TCP_Send(m_clientSockets[mapIndex], message.c_str(), length) < length)
	{
		std::cout << "Could not send message." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that receives a message via the connection socket and stores it in passed string
//------------------------------------------------------------------------------------------------------
bool ServerSocket::ReceiveMessage(std::string mapIndex, std::string& message)
{

	char tempMessage[2000];

	if (SDLNet_TCP_Recv(m_clientSockets[mapIndex], tempMessage, 2000) <= 0)
	{
		std::cout << "Could not receive message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down a particular client connection socket 
//------------------------------------------------------------------------------------------------------
void ServerSocket::Close(std::string mapIndex)
{

	SDLNet_TCP_DelSocket(m_socketSet, m_clientSockets[mapIndex]);
	SDLNet_TCP_Close(m_clientSockets[mapIndex]);

}
//------------------------------------------------------------------------------------------------------
//function that closes down the client and listening connection sockets 
//------------------------------------------------------------------------------------------------------
void ServerSocket::CloseAll()
{

	for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
	{
		SDLNet_TCP_DelSocket(m_socketSet, it->second);
		SDLNet_TCP_Close(it->second);
	}

	SDLNet_TCP_Close(m_socket);

}
//------------------------------------------------------------------------------------------------------
//destructor that de-allocates all client sockets
//------------------------------------------------------------------------------------------------------
ServerSocket::~ServerSocket()
{

	SDLNet_FreeSocketSet(m_socketSet);

}