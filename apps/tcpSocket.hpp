#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdexcept>
#include <iostream>

//#include "output/output.hpp"

class tcpSocket
{
private:
	char* m_buffer;
	const int m_bufferSize = 256;
	int m_portnum;
	int m_fd;
	int m_fdListen;
	sockaddr_in m_saddr;
	const sockaddr *m_saddrPtr;
	socklen_t m_sockaddrInSize;

public:
	tcpSocket(int portnum = 9000);
	~tcpSocket();
	void sockListen();
	std::string getString();
};
