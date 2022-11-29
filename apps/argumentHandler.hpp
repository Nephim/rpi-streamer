#pragma once
#include <string.h>
#include <iostream>

class argumentHandler
{
private:
    int m_argc;
    char** m_argv;
   	int m_argSize;
    void allocateArg();
    void clearArgs();
public:
    argumentHandler(int argc = 0, char* argv[] = nullptr, int argSize = 10);
	~argumentHandler();
    void addArgument(const std::string arg);
	void stringInput(const std::string str);
    int getargc();
    char** getargv();
	char* getCommand();
	std::string getString();
    void print() const;
};