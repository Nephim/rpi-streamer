#include "argumentHandler.hpp"

#include<sstream>

void argumentHandler::allocateArg()
{
	if(m_argc == m_argSize)
	{
		m_argSize *= 2;								//double size
		char** tmpArgV = new char*[m_argSize];		// alocate tmp array
		for(int i = 0; i < m_argc; ++i)
		{
			*(tmpArgV + i) = *(m_argv + i); //moving the pointers to arguments over
		}
		delete[] m_argv;
		m_argv = tmpArgV;
	}
}
void argumentHandler::clearArgs()
{
	for(int i = 0; i < m_argc; ++i)
	{
		delete[] m_argv[i];
	}
	delete [] m_argv;
	m_argSize = 10;
	m_argc = 0;
	m_argv = new char*[m_argSize];
}

argumentHandler::argumentHandler(int argc, char* argv[], int argSize)
	: m_argc(argc), m_argv(argv), m_argSize(argSize)
{
	if(m_argv == nullptr)
	{
		m_argv = new char*[m_argSize];
	}
	
}

argumentHandler::~argumentHandler()
{
	for(int i = 0; i < m_argc; ++i)
	{
		delete[] m_argv[i];
	}
	delete [] m_argv;
}
	
void argumentHandler::addArgument(const std::string arg)
{
	allocateArg();
	m_argv[m_argc] = new char(arg.length()+1);
	strcpy(m_argv[m_argc], arg.c_str());
	++m_argc;
}

void argumentHandler::stringInput(const std::string str)
{
	clearArgs();
	char ch;
	std::string word;
	for(unsigned long i = 0; i <= str.length(); ++i)
	{
		ch = str[i];
		if (isspace(ch))
		{
			addArgument(word);
			word = "";
		}
		else
		{
		word += ch;
		}
	}
	addArgument(word);
}

int argumentHandler::getargc()
{
	return m_argc;
}
char** argumentHandler::getargv()
{
	return m_argv;
}
char* argumentHandler::getCommand()
{
	return m_argv[0]; // The command string
}

std::string argumentHandler::getString()
{
	std::string str;
	for(int i = 0; i < m_argc; ++i)
	{
		str.append(m_argv[i]);
	}
	return str;
}

void argumentHandler::print() const
{
	std::cout << "Arguments: " << m_argc << "\n";
	for(int i = 0; i < m_argc; ++i)
	{
		std::cout << *(m_argv+i) << " ";
	}
	std::cout << std::endl;
}