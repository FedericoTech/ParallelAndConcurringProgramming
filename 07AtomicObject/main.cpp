/**
 * Two shoppers adding items to a shared notepad
 * Another way to avoid data races when we only want to protect
 * the access to a variable is with atomic types which is a
 * class that wraps a type and allows us to operate with it in a
 * thread-safe manner.
 */
#include <thread>
#include <atomic>
#include <cstdio>

//here we are using an atomic wrapper
std::atomic<unsigned int> garlic_count(0);

void shopper()
{
	//this shopper adds those garlics
	for(int i = 0; i < 10000000; i++){
		++garlic_count;
	}
}

int main() {
	std::thread shopper1(shopper);
	std::thread shopper2(shopper);
	shopper1.join();
	shopper2.join();

	//we can see that all the garlics of each are added
	printf("We should buy %u garlic.\n", garlic_count.load());
	return 0;
}
