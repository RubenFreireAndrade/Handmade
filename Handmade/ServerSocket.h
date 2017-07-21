/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2017

-----------------------------------------------------------------------------------------------

- This class derives from the Socket class and represents all functionality that has to do with
  a server connection. It will listen for incoming client connections and manage an array of 
  client socket connections, all monitored from within a socket set. A separate map of sockets
  is there to manually access specific client sockets

- It is still a WIP!

*/

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <map>
#include <string>
#include <SDL_net.h>
#include "Socket.h"

class ServerSocket : public Socket
{

public:

	ServerSocket();
	~ServerSocket();

public:

	bool Open();
	bool Check(std::string mapIndex);
	bool Listen(std::string mapIndex);
	
	bool SendMessage(std::string mapIndex, std::string& message);
	bool ReceiveMessage(std::string mapIndex, std::string& message);

	void Close(std::string mapIndex);
	void CloseAll();

private:

	std::map<std::string, TCPsocket> m_clientSockets;

};

#endif