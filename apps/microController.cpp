#include "microController.hpp"
#include "client.hpp"

#include <iomanip>


microController::microController(msgQueue* clientHandlerMsgQueue)
	: m_uart(new UARTDriver), m_msgQueue(new msgQueue), m_clientMsgQueue(clientHandlerMsgQueue)
{
	m_eventLoopThread = std::thread(&microController::eventLoop, this); //Event loop to handle events
	m_uartInputThread = std::thread(&microController::uartInput, this); //UART loop to listen for input
}

microController::~microController()
{
	delete m_msgQueue;
	delete m_uart;
}

msgQueue* microController::getMsgQueue() const
{
	return m_msgQueue;
}

void microController::setClientHandlerMsgQueue(msgQueue* clientMsgQueue)
{
	m_clientMsgQueue = clientMsgQueue;
}

void microController::join()
{
	m_uartInputThread.join();
	m_eventLoopThread.join();
}

void microController::eventLoop()
{
	for(;;)
	{
		unsigned long id;
		message* msg = m_msgQueue->receive(id);			//Blocking
		dispatcher(msg, id);
		delete msg;
	}
}


void microController::dispatcher(message* msg, unsigned long id)
{
	switch(id)
	{
		case ID_BEER_AMOUNT_CHANGE:
			beerChangeHandler(msg);
		break;
		case ID_DISTANCE_CHANGE:
			distanceChangeHandler(msg);
		break;
		case ID_MOVE:
			moveHandler(msg);
		break;
		case ID_raceMode:
			moveHandler(msg);
		break;
	}
}

// void microController::beerChangeHandler(message* msg)		//INPUT
// {
// 	m_clientMsgQueue->send(client::ID_BEER_UPDATE
// 	, new client::returnMsg(static_cast<uartInputMsg*>(msg)->m_input));		// new type of message
// }

// void microController::distanceChangeHandler(message* msg) 	//INPUT
// {
// 	m_clientMsgQueue->send(client::ID_DISTANCE_UPDATE
// 	, new client::returnMsg(static_cast<uartInputMsg*>(msg)->m_input));		// new type of message
// }

void microController::moveHandler(message* msg)				//OUTPUT
{
	m_uart->write_to_port(static_cast<microController::moveMsg*>(msg)->m_output);
}

void microController::raceModeHandler(message* msg)			//OUTPUT
{
	m_uart->write_to_port(static_cast<microController::raceMode*>(msg)->m_output);
}

void microController::uartInput() // Seperate Thread
{
	char input;
	for(;;)
	{
		input = m_uart->read_from_port();
		message* msg;
		unsigned long id;
		std::string str;
		if (input > 0b1111111)				//127 - Distance
		{
			str = "distance ";
			id = client::ID_DISTANCE_UPDATE;
		}
		else								// Amount of beer
		{
			str = "beer ";
			id = client::ID_BEER_UPDATE;
		}
		str.append(std::to_string(static_cast<int>(input & 0b1111111)));
		msg = new client::returnMsg(str);
		m_clientMsgQueue->send(id, msg);
	}
}