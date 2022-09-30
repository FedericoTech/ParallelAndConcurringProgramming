/**
 * Two shoppers adding items to a shared notepad
 * This example demonstrats that we can try to lock the mutex if
 * it isn't unlock but if we can't we can do something else instead of
 * waiting for it.
 */

#include <thread>
#include <mutex>
#include <chrono>
#include <cstdio>

unsigned int items_on_notepad = 0;

std::mutex pencil;

void shopper(const char* name)
{
	int items_to_add = 0;

	while(items_on_notepad <= 20){
		//first check whether there are items to add, if so, it evaluates the try lock
		if(items_to_add && pencil.try_lock()){ //add item(s) to shared items_on_notepad
			//now this block is locked

			items_on_notepad += items_to_add;
			printf("%s added %u items(s) to notepad.\n", name, items_to_add);
			items_to_add = 0;

			std::this_thread::sleep_for(std::chrono::milliseconds(300)); //time spent writing

			pencil.unlock(); //we unlock the block
		//if no items or the mutex is locked...
		} else { //look for other things to buy
			std::this_thread::sleep_for(std::chrono::milliseconds(300)); //time spent searching

			items_to_add++; //we accumulate items to add

			printf("%s found something else to buy.\n", name);
		}
	}
}

int main() {
	//we capture the current time
	std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();

	std::thread shopper1(shopper, "Shopper 1");
	std::thread shopper2(shopper, "Shopper 2");

	//we wait for the shoppers to finish.
	shopper1.join();
	shopper2.join();

	//in this case it's long
	long elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();

	//now we show how much time passed.
	printf("Elapsed Time: %.2f seconds\n", elapsed_time/1000.0);
}

