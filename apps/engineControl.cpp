#include "engineControl.hpp"


engineControl::engineControl()
	: m_speed(0)
{}

uint8_t engineControl::move(argumentHandler& arg)
{
	switch(arg.getargv()[1][0])
	{
		case 'w':
		case 'W':
			return moveW();
		break;
		case 'a':
		case 'A':
			return moveA();
		break;
		case 's':
		case 'S':
			return moveS();
		break;
		case 'd':
		case 'D':
			return moveD();
		break;
		default:
			return 0;
		break;
	}
	std::cout << "I moved " << arg.getargv()[1][0] << " with " << arg.getargc() << "\n";
}

uint8_t engineControl::stop(argumentHandler& arg)
{
	switch(arg.getargv()[1][0])
	{
		case 'w':
		case 'W':
			return stopW();
		break;
		case 'a':
		case 'A':
			return stopA();
		break;
		case 's':
		case 'S':
			return stopS();
		break;
		case 'd':
		case 'D':
			return stopD();
		break;
		default:
			return 0;
		break;
	}
	std::cout << "I stopped " << arg.getargv()[1][0] << " with " << arg.getargc() << "\n";
}

uint8_t engineControl::moveW()
{
	std::cout << "MSpeed: " << std::to_string(m_speed) << "\n";
	if (m_speed < 11)
	{
		++m_speed;
		return 0b00100000 | m_speed;					//0b001YXXXX - X is speed and y is direction
	}
	return 0b00100000 | m_speed;		
}

uint8_t engineControl::moveA()
{
	return 0b01100000;								//0b011XXXXZ - X dont care Z is turning direction
}

uint8_t engineControl::moveS()
{
	std::cout << "MSpeed: " << std::to_string(m_speed) << "\n";
	if (m_speed < 11)
	{
		++m_speed;
		return 0b00110000 | m_speed;					//0b001YXXXX - X is speed and y is direction
	}
	return 0b00110000 | m_speed;
}

uint8_t engineControl::moveD()
{
	return 0b01100001;								//0b011XXXXZ - X dont care Z is turning direction
}

uint8_t engineControl::stopW()
{
	m_speed = 0;
	return 0b01000000;								//0b010xxxxx - Stop moving
}

uint8_t engineControl::stopA()
{
	return 0b10000000;								//0b100XXXXX - Stop turning
}

uint8_t engineControl::stopS()
{
	m_speed = 0;
	return 0b01000000;								//0b010xxxxx - Stop moving
}

uint8_t engineControl::stopD()
{
	return 0b10000000;								//0b100XXXXX - Stop turning
}
