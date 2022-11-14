#include "tcpSocket.hpp"

//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>


tcpSocket::tcpSocket(int portnum)
	: m_portnum(portnum), m_buffer(new char(m_bufferSize))
{}

tcpSocket::~tcpSocket()
{
	delete[] m_buffer;
}

void tcpSocket::sockListen()
{
	m_fdListen = socket(AF_INET, SOCK_STREAM, 0);
	if (m_fdListen < 0)
		throw std::runtime_error("unable to open listen socket");

	sockaddr_in server_saddr = {};
	server_saddr.sin_family = AF_INET;
	server_saddr.sin_addr.s_addr = INADDR_ANY;
	server_saddr.sin_port = htons(m_portnum);
		int enable = 1;
	if (setsockopt(m_fdListen, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		throw std::runtime_error("failed to setsockopt listen socket");
		if (bind(m_fdListen, (struct sockaddr *)&server_saddr, sizeof(server_saddr)) < 0)
				throw std::runtime_error("failed to bind listen socket");
	listen(m_fdListen, 1);
	//LOG(2, "Waiting for client to connect...");
	m_sockaddrInSize = sizeof(m_saddr);
	m_fd = accept(m_fdListen, (struct sockaddr *)&m_saddr, &m_sockaddrInSize);
	if (m_fd < 0)
	{
		throw std::runtime_error("accept socket failed");
	}
		
		//LOG(2, "Client connection accepted");

	read(m_fd, m_buffer, m_bufferSize);
	//std::cout << m_buffer << "\n";
	close(m_fd);
	close(m_fdListen);
}

std::string tcpSocket::getString()
{
	return std::string(m_buffer);
}