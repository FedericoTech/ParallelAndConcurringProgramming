/**
 * Two shoppers adding items to a shared notepad
 * This example demonstrate an scenario of data race in which
 * two threads trample on each other
 */
#include <thread>
#include <cstdio>

unsigned int garlic_count = 0;

void shopper()
{
	for(int i = 0; i < 10000000; i++){
		++garlic_count;
	}
}

int main() {
	//each shopper adds the same number of garlics on the notepad
	std::thread shopper1(shopper);
	std::thread shopper2(shopper);
	shopper1.join();
	shopper2.join();

	//but because they trample on each other we'll see that the final number is far lower

	printf("We should buy %u garlic.\n", garlic_count);
	return 0;
}
