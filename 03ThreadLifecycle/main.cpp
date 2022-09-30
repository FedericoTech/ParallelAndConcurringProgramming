/**
 * Two threads cooking soup
 * This example demonstrates that we can check whether a thread is still active
 */

#include <thread>
#include <chrono>
#include <cstdio>

void cook2_to_chop_sausage(){
	printf("Cook2 started & waiting for sausage to thaw...\n");
	std::this_thread::sleep_for(std::chrono::seconds(3));
	printf("Cook2 is donde cutting sausage\n");
}

int main()
{
	printf("Cook1 requests Cook2's help.\n");
	std::thread cook2(cook2_to_chop_sausage);

	printf("  is Cook2 joinable? %s\n", cook2.joinable() ? "true" : "false");

	printf("Cook1 continues cooking soup.\n");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//meaning whether cook2 is still chopping
	printf("  is Cook2 joinable? %s\n", cook2.joinable() ? "true" : "false");

	printf("Cook1 patiently waits for Cook2 to finish and join...\n");
	//so cook1 waits for cook2
	cook2.join();

	//has cook2 finished?
	printf("  is Cook2 joinable? %s\n", cook2.joinable() ? "true" : "false");

	printf("Cook1 and Cook2 are both done!\n");

	return 0;
}

