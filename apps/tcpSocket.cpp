#include "tcpSocket.hpp"

#include <unistd.h>
#include <memory.h>




tcpSocket::tcpSocket(int portnum)
	: m_buffer(new char(m_bufferSize)), m_fd(0)
{
	m_fdListen = socket(AF_INET, SOCK_STREAM, 0);
	if (m_fdListen < 0)
		throw std::runtime_error("unable to open listen socket");

	sockaddr_in server_saddr = {};
	server_saddr.sin_family = AF_INET;
	server_saddr.sin_addr.s_addr = INADDR_ANY;
	server_saddr.sin_port = htons(portnum);
		int enable = 1;
	setsockopt(m_fdListen, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

	if (bind(m_fdListen, (struct sockaddr *)&server_saddr, sizeof(server_saddr)) < 0)
			throw std::runtime_error("failed to bind listen socket");
}

tcpSocket::~tcpSocket()
{
	delete[] m_buffer;
}

void tcpSocket::startConnection()
{

	listen(m_fdListen, 1);
	m_sockaddrInSize = sizeof(m_saddr);
	m_fd = accept(m_fdListen, (struct sockaddr *)&m_saddr, &m_sockaddrInSize);
	if (m_fd < 0)
	{
		throw std::runtime_error("accept socket failed");
	}
	// Get connection info
	LOG_DEBUG("Connection established on " << inet_ntoa(m_saddr.sin_addr) << ":" << std::to_string(m_saddr.sin_port) << std::endl);
	
}

void tcpSocket::closeConnection()
{
	close(m_fd);
	close(m_fdListen);
}

void tcpSocket::sendCommand(std::string str)
{
	write(m_fd, str.c_str(), str.length()+1);
}

std::string tcpSocket::getString()
{
	memset(m_buffer, 0, m_bufferSize - 1);
	if(!read(m_fd, m_buffer, m_bufferSize)) // If connection is borked listen for new.
		startConnection();
	return std::string(m_buffer);

}

