#pragma once

#include <thread>

#include "UARTBoostDriver.h"
#include "msgQueue.hpp"
#include "message.hpp"

class microController
	{
	private:
		std::thread m_eventLoopThread;
		std::thread m_uartInputThread;
		UARTDriver* m_uart;
		msgQueue* m_msgQueue;
		msgQueue* m_clientMsgQueue;
		// void beerChangeHandler(message* msg);
		// void distanceChangeHandler(message* msg);
		void moveHandler(message* msg);
		void raceModeHandler(message* msg);
		void dispatcher(message* msg, unsigned long id);
		void eventLoop();
		void uartInput();
	public:
		// struct uartInputMsg : message
		// {
		// 	uartInputMsg(std::string str) 
		// 	{
		// 		m_input = str;
		// 	}
		// 	std::string m_input;
		// };

		struct moveMsg : message
		{
			moveMsg(uint8_t output)
			{
				m_output = output;
			}
			uint8_t m_output;
		};

		struct raceMode : message
		{
			raceMode(uint8_t output)
			{
				m_output = output;
			}
			uint8_t m_output;
		};

		enum 
		{
			ID_BEER_AMOUNT_CHANGE,
			ID_DISTANCE_CHANGE,
			ID_MOVE,
			ID_raceMode
		};
		microController(msgQueue* clientMsgQueue = nullptr);
		~microController();
		msgQueue* getMsgQueue() const;
		void setClientHandlerMsgQueue(msgQueue* clientMsgQueue);
		void join();
	};



