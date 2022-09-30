/**
 * Two threads chop vegetables
 */
#include <thread>
#include <chrono>
#include <cstdio>

bool chopping = true;

void vegetable_chopper(const char* name){
	unsigned int vegetable_count = 0;

	//if it's still time to chop
	while(chopping){
		//the cook chops again
		++vegetable_count;
	} //once the cook finishes...
	printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main() {
	std::thread cook1(vegetable_chopper, "Cook 1");
	std::thread cook2(vegetable_chopper, "Cook 2");

	printf("Cook 1 and 2 are chopping vegetables...\n");

	//we set the main thread to sleep for a second so that we leave the two cooks chop
	std::this_thread::sleep_for(std::chrono::seconds(1));

	chopping = false; //we signal the time is up.

	//we wait for them to finish their last chop
	cook1.join();
	cook2.join();
	/**
	 * if we don't join the program finishes when the last thread finishes
	 * and if the last thread is not the main thread we get an error
	 * "terminate called without an active exception"
	 */

	//back to the main thread
	printf("Done\n");

	return 0;
}


