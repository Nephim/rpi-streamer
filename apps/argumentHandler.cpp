#include "argumentHandler.hpp"

argumentHandler::argumentHandler(int argc, char* argv[], int argSize)
	: m_argc(argc), m_argv(argv), m_argSize(argSize)
{
	m_argv = new char*[m_argSize];
}
	
void argumentHandler::addArgument(const std::string arg)
{
	allocateArg();
	*(m_argv + m_argc) = new char(arg.length()+1);
	strcpy(*(m_argv + m_argc), arg.c_str());
	++m_argc;
}
void argumentHandler::allocateArg()
{
	if(m_argc == m_argSize)
	{
		char** tmpArgV = new char*[m_argSize*2];
		for(int i = 0; i < m_argSize; ++i)
		{
			*(tmpArgV + i) = *(m_argv + i); //moving the pointers to arguments over
		}
	}
}
int argumentHandler::getargc()
{
	return m_argc;
}
char** argumentHandler::getargv()
{
	return m_argv;
}

void argumentHandler::print() const
{
	std::cout << "Arguments:\n";
	for(int i = 0; i < m_argc; ++i)
	{
		std::cout << *(m_argv+i) << " ";
	}
	std::cout << std::endl;
}