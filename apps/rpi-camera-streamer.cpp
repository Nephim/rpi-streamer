#include "client.hpp"
#include "microController.hpp"

#include <chrono>


int main()
{
	client myClient;
	microController myMicroController(myClient.getMsgQueue());
	myClient.setMicroControllerMsgQueue(myMicroController.getMsgQueue());
	// for(;;)
	// {
	// 	std::this_thread::sleep_for(10s);
	// }
	myClient.join();
	myMicroController.join();
	return 0;
}
