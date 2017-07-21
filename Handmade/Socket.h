/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a socket that is used to establish connections. At the core it contains
  a socket, a socket set and IP struct. It is a base class, from which specific server or client
  socket classes need to be derived

- It is still a WIP!

*/

#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <SDL.h>
#include <SDL_net.h>

class Socket
{

public:

	Socket();

public:

	bool Initialize(Uint16 port, const char* ipAddress = NULL);
	void ShutDown();

protected:

	IPaddress m_IP;
	TCPsocket m_socket;
	SDLNet_SocketSet m_socketSet;

};

#endif 