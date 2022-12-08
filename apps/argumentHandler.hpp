#pragma once
#include <string.h>
#include <iostream>

class argumentHandler
{
private:
	const unsigned int constARG_SIZE = 10;
	int m_argc;
	char** m_argv;
	int m_argSize;
	void allocateArg();
	void clearArgs();
public:
	argumentHandler(int argc = 0, char* argv[] = nullptr, int argSize = constARG_SIZE);
	~argumentHandler();
	void addArgument(const std::string arg);
	void stringInput(const std::string str);
	int getargc() const;
	char** getargv() const;
	char* getCommand() const;
	std::string getString();
	void print() const;
};