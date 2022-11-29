#pragma once

#include <iostream>

#include "argumentHandler.hpp"


class engineControl
{
private:
	uint8_t m_speed;
	uint8_t moveW();
	uint8_t moveA();
	uint8_t moveS();
	uint8_t moveD();
	uint8_t stopW();
	uint8_t stopA();
	uint8_t stopS();
	uint8_t stopD();

public:
	engineControl();
	uint8_t move(argumentHandler& arg);
	uint8_t stop(argumentHandler& arg);
};