#include "msgQueue.hpp"
#include <mutex>

msgQueue::msgQueue(unsigned long maxSize) 
	: m_maxSize(maxSize)
{}

void msgQueue::send(unsigned long id, message* msg)

{
	std::unique_lock<std::mutex> lock(m_mutex);					//Class used to lock mutex within scope
	while(m_messageQueue.size() == m_maxSize)					//Sleep if queue is full
	{
		m_condVar.wait(lock);
	}
	m_messageQueue.push(queueItem(id, msg));	//Add queueItem to queue
	m_condVar.notify_one();										//Signal that queueItem was added to queue
}

message* msgQueue::receive(unsigned long& id)
{
   	std::unique_lock<std::mutex> lock(m_mutex);								//Class used to lock mutex within scope
	while(m_messageQueue.empty())								//Sleep if queue is empty
	{
		m_condVar.wait(lock);
	}
	queueItem tmpItem = m_messageQueue.front();					//Get queueItem
	m_messageQueue.pop();										//Remove bottom queueItem from queue
	id = tmpItem.m_id;											//Set id
	m_condVar.notify_one();										//Signal that queueItems was removed from queue
	return tmpItem.m_msg;										
}
