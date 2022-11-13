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
public:
    argumentHandler(int argc = 0, char* argv[] = nullptr, int argSize = 10);
    void addArgument(const std::string arg);
    int getargc();
    char** getargv();
    void print() const;
};