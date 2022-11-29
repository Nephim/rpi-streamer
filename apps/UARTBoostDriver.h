#ifndef UARTDRIVE_H
#define UARTDRIVE_H
using namespace std;
#include <iostream>


#pragma once

class UARTDriver
{
public:
    UARTDriver(std::string devicePort = "/dev/ttyS0");
    ~UARTDriver();
    int open_port(std::string devicePort);
    void write_to_port(char n);
    char read_from_port();
    void close_port();

  private:
    char n;
	std::string m_devicePort;
};

#endif