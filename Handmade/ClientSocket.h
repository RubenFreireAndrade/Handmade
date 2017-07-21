/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : July 2017

  -----------------------------------------------------------------------------------------------

- This class derives from the Socket class and represents all functionality that has to do with
  a client connection. It will connect to an existing server (if there is one). It only allocates
  one socket in it's socket set.

- It is still a WIP!

*/

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>
#include "Socket.h"

class ClientSocket : public Socket
{

public:

	ClientSocket();
	~ClientSocket();

public:

	bool Open();
	bool Check();
	
	bool SendMessage(std::string& message);
	bool ReceiveMessage(std::string& message);

	void Close();

};

#endif