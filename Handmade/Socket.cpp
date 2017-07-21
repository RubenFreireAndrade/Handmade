#include <iostream>
#include "Socket.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Socket::Socket()
{

	m_socket = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that sets up the SDL networking sub-system and the server/client 
//------------------------------------------------------------------------------------------------------
bool Socket::Initialize(Uint16 port, const char* ipAddress)
{

	if (SDLNet_Init() == -1)
	{
		std::cout << "Networking sub-system did not initialize properly." << std::endl << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&m_IP, ipAddress, port) == -1)
	{
		std::cout << "Could not resolve IP address." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down the SDL networking sub-system
//------------------------------------------------------------------------------------------------------
void Socket::ShutDown()
{

	SDLNet_Quit();

}