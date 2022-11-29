#pragma once
#include "message.hpp"
#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>

class msgQueue
{
public:
	msgQueue ( unsigned long maxSize = 10);
	void send( unsigned long id, message* msg = nullptr);
	message* receive ( unsigned long& id);
private:
	//struct to hold id and message in the queue.
	struct queueItem
	{
		queueItem(unsigned long id, message* msg)
		{
			m_id = id;
			m_msg = msg;
		}
		unsigned long m_id;
		message* m_msg;
	};
    // Container with structs
    std::queue<queueItem> m_messageQueue;
	unsigned long m_maxSize;
	std::mutex m_mutex;
	std::condition_variable m_condVar;
};
