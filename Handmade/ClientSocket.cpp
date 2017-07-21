#include <iostream>
#include "ClientSocket.h"

//------------------------------------------------------------------------------------------------------
//constructor that allocates a 1 server/client connection socket
//------------------------------------------------------------------------------------------------------
ClientSocket::ClientSocket()
{

	m_socketSet = SDLNet_AllocSocketSet(1);

}
//------------------------------------------------------------------------------------------------------
//function that opens up a connection socket using resolved IP and port number 
//------------------------------------------------------------------------------------------------------
bool ClientSocket::Open()
{

	m_socket = SDLNet_TCP_Open(&m_IP);

	if (!m_socket)
	{
		std::cout << "Could not open socket connection." << std::endl << std::endl;
		return false;
	}

	//we add this client socket to the set to check for activity later
	SDLNet_TCP_AddSocket(m_socketSet, m_socket);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that checks if client socket has activity
//------------------------------------------------------------------------------------------------------
bool ClientSocket::Check()
{

	//first check socket set before checking client socket for data
	if (SDLNet_CheckSockets(m_socketSet, 0) > 0 && SDLNet_SocketReady(m_socket))
	{
		return true;
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that sends a passed message via the connection socket
//------------------------------------------------------------------------------------------------------
bool ClientSocket::SendMessage(std::string& message)
{

	int length = message.length() + 1;

	if (SDLNet_TCP_Send(m_socket, message.c_str(), length) < length)
	{
		std::cout << "Could not send message." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that receives a message via the connection socket and stores it in passed string
//------------------------------------------------------------------------------------------------------
bool ClientSocket::ReceiveMessage(std::string& message)
{

	char tempMessage[2000];

	if (SDLNet_TCP_Recv(m_socket, tempMessage, 2000) <= 0)
	{
		std::cout << "Could not receive message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down a connection socket 
//------------------------------------------------------------------------------------------------------
void ClientSocket::Close()
{

	SDLNet_TCP_DelSocket(m_socketSet, m_socket);
	SDLNet_TCP_Close(m_socket);

}
//------------------------------------------------------------------------------------------------------
//destructor that de-allocates socket
//------------------------------------------------------------------------------------------------------
ClientSocket::~ClientSocket()
{

	SDLNet_FreeSocketSet(m_socketSet);

}