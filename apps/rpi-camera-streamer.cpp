#include "client.hpp"
#include "microController.hpp"


int main()
{
	client myClient;
	microController myMicroController(myClient.getMsgQueue());
	myClient.setMicroControllerMsgQueue(myMicroController.getMsgQueue());
	while (true) 
		{};
	return 0;
}