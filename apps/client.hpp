#pragma once

#include <thread>

#include "videoStream.hpp"
#include "engineControl.hpp"
#include "tcpSocket.hpp"
#include "msgQueue.hpp"
#include "microController.hpp"
#include "message.hpp"

class client
{
private:
	engineControl m_engine;
	std::thread m_tcpSocketThread;
	std::thread m_eventLoopThread;
	videoStream m_videoStream;
	msgQueue* m_msgQueue;
	msgQueue* m_microControllerMsgQueue;
	tcpSocket m_socket;
	void tcpSocketLoop();
	void eventLoop();
	void dispatcher(message* msg, unsigned long id);
	void beerChangeHandler(message* msg);
	void distanceChangeHandler(message* msg);
public:
	struct returnMsg : message
	{
		returnMsg(std::string str)
		{
			m_str = str;
		}
		std::string m_str;
	};
	enum
	{
		ID_BEER_UPDATE,
		ID_DISTANCE_UPDATE
	};
	client(msgQueue* microControllerMsgQueue = nullptr);
	msgQueue* getMsgQueue() const;
	void setMicroControllerMsgQueue(msgQueue* microControllerMsgQueue);
	
};