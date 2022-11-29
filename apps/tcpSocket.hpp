#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdexcept>
#include <iostream>

#define LOG_DEBUG(text) std::cout << text << std::endl

class tcpSocket
{
private:
	char* m_buffer;
	const unsigned int m_bufferSize = 256;
	int m_portnum;
	int m_fd;
	int m_fdListen;
	sockaddr_in m_saddr;
	const sockaddr *m_saddrPtr;
	socklen_t m_sockaddrInSize;

public:
	tcpSocket(int portnum);
	~tcpSocket();
	void startConnection();
	void closeConnection();
	void sendCommand(std::string str);
	std::string getString();
};
