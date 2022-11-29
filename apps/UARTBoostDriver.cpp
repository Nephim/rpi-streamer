#include "UARTBoostDriver.h"
#include <errno.h>   /* Error number definitions */
#include <fcntl.h>   /* File control definitions */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdlib.h>
#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

asio::io_context io;
asio::serial_port port(io);
//int fd; /* File descriptor for the port */

UARTDriver::UARTDriver(std::string devicePort)
	: m_devicePort(devicePort)
{ 
	open_port(devicePort);
}

UARTDriver::~UARTDriver()
{
}

int UARTDriver::open_port(std::string devicePort)
{
	port.open(devicePort); // Hvis i bruger en USB2Uart ting
    port.set_option(asio::serial_port_base::baud_rate(115200));

	return 1;
}

void UARTDriver::write_to_port(char n)
{
	int bytes_written = port.write_some(asio::buffer(&n, 1));
	printf("Bytes written: %d\n", bytes_written);
}

char UARTDriver::read_from_port() 
{ 
	char c;

	while(!(asio::read(port, asio::buffer(&c,1))))
	{}

	return c;
}

void UARTDriver::close_port() 
{ 
	port.close();
}