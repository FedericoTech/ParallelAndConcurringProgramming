/**
 * Two shoppers adding items to a shared notepad
 * This example demonstrates that we can protect some piece of code
 * from other's access when we need to have exclusive access so that we avoid
 * data races.
 */
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdio>
#include <sstream>

unsigned int garlic_count = 0;

std::mutex pencil; //this is the mechanism that enables the mutual exclusion

void shopper()
{
	std::stringstream ss;
	ss << std::this_thread::get_id(); //it returns a std::thread::id object

	for(int i = 0; i < 5; i++){
		printf("Shopper %s is thinking...\n", ss.str().c_str());

		//doing something that takes time
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		pencil.lock(); //we lock this piece of code
			++garlic_count;
		pencil.unlock(); //now we can unlock the code
	}
}

int main()
{
	std::thread shopper1(shopper);
	std::thread shopper2(shopper);
	shopper1.join();
	shopper2.join();

	//now we should see exaclty the sum of garlics added by the two shoppers

	printf("We should buy %u garlic.\n", garlic_count);
	return 0;
}
