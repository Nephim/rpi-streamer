#include "client.hpp"

#include "microController.hpp"
#include "argumentHandler.hpp"

client::client(msgQueue* microControllerMsgQueue)
	: m_msgQueue(new msgQueue), m_microControllerMsgQueue(microControllerMsgQueue), m_socket(9000)
{
	m_eventLoopThread = std::thread(&client::eventLoop, this); //Event loop to handle events
	m_tcpSocketThread = std::thread(&client::tcpSocketLoop, this); //TCP socket loop to listen for input
}

msgQueue* client::getMsgQueue() const
{
	return m_msgQueue;
}

void client::setMicroControllerMsgQueue(msgQueue* microControllerMsgQueue)
{
	m_microControllerMsgQueue = microControllerMsgQueue;
}

void client::join()
{
	m_tcpSocketThread.join();
	m_eventLoopThread.join();
}

void client::tcpSocketLoop()
{
	m_socket.startConnection();
	argumentHandler arg;
	for(;;)
	{
		arg.stringInput(m_socket.getString());
		arg.print();
		if(std::string("rpi-streamer").compare(arg.getCommand()) == 0)
		{
			if (m_videoStream.isRunning() == true)
			{
				m_videoStream.stop();
			}
			m_videoStream.start(arg.getargc(), arg.getargv());
		} 
		else if (std::string("move").compare(arg.getCommand()) == 0)
		{
			if(m_microControllerMsgQueue == nullptr)
			{
				std::cout << "m_microControllerMsgQueue is a nullptr\n";
				return;
			}
			uint8_t moveCommand = m_engine.move(arg);
			std::cout << "Move Command " << std::to_string(moveCommand) << "\n";
			unsigned long id = microController::ID_MOVE;
			message* msg = new microController::moveMsg(m_engine.move(arg));
			m_microControllerMsgQueue->send(id, msg);
		}
		else if (std::string("stop").compare(arg.getCommand()) == 0)
		{
			if(m_microControllerMsgQueue == nullptr)
			{
				std::cout << "m_microControllerMsgQueue is a nullptr\n";
				return;
			}
			
			uint8_t stopCommand = m_engine.stop(arg);
			std::cout << "Stop Command " << std::to_string(stopCommand) << "\n";
			unsigned long id = microController::ID_MOVE;
			message* msg = new microController::moveMsg(stopCommand);
			m_microControllerMsgQueue->send(id, msg);
		}
		else if (std::string("rpi-streamer-stop").compare(arg.getCommand()) == 0)
		{
			m_videoStream.stop();
		}
		else
		{
			m_socket.sendCommand("Unknown command " + arg.getString() + "\n");
			std::cout << "Unknown command\n";
			arg.print();
		}
	}	
}

void client::eventLoop()
{
	for(;;)
	{
		unsigned long id;
		message* msg = m_msgQueue->receive(id);			//Blocking
		dispatcher(msg, id);
		delete msg;
	}
}

void client::dispatcher(message* msg, unsigned long id)
{
	switch(id)
	{
		case ID_BEER_UPDATE:
			beerChangeHandler(msg);
		break;
		case ID_DISTANCE_UPDATE:
			distanceChangeHandler(msg);
		break;
		default:
			return;
		break;
	}
}

void client::beerChangeHandler(message* msg)
{
	m_socket.sendCommand(static_cast<returnMsg*>(msg)->m_str);
}

void client::distanceChangeHandler(message* msg)
{
	m_socket.sendCommand(static_cast<returnMsg*>(msg)->m_str);
}