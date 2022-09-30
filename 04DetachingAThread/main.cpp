/**
 * Cook1 finishes cooking while Cook2 Cleans
 * This example demonstrates that we can have a thread, make it independent from the main thread
 * and will close when the main thread closes.
 */
#include <thread>
#include <chrono>
#include <cstdio>

void kitchen_cleaner()
{
	while(true){
		printf("Cook2 cleaned the kitchen.\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	//we start this thread that cleans the kitchen ever once in a while
	std::thread cook2(kitchen_cleaner);

	cook2.detach(); //we detach the thread from this main thread

	//cook1 is cooking and keeps us informed
	for(int i = 0; i < 3; i++){
		printf("Cook1 is cooking...\n");
		//we simulate that it takes a while in every round
		std::this_thread::sleep_for(std::chrono::milliseconds(600));
	}

	//cook 1 finished and at the end of the scope cook2 will also finish and the program ends
	printf("Cook1 is done!\n");

	return 0;
}

