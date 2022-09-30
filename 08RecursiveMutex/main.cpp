/**
 * Two shoppers adding garlic and potatoes to a shared notepad
 * This example demonstrates how we can perform a recursive mutex
 * so that, a thread doesn't lock itself it happens to call a function with a mutex
 * wich calls another function which tries to lock the same mutex.
 */
#include <thread>
#include <mutex>
#include <cstdio>

//we have to counts, garlics and potatoes
unsigned int garlic_count = 0;
unsigned int potato_count = 0;

std::recursive_mutex pencil;

//function that adds garlics
void add_garlic()
{
	pencil.lock(); //this block of code is protected
	garlic_count++;
	pencil.unlock();
}

//function that adds potatoes but also garlics
void add_potato()
{
	pencil.lock(); //this block of code is protected
	potato_count++;

	add_garlic(); //we have nested two lock calls on the same mutex

	pencil.unlock();
}

void shopper()
{
	//the shopper adds garligs and potatoes
	for(int i= 0; i < 10000; i++){
		add_garlic();
		add_potato();
	}
}

int main()
{
	std::thread shopper1(shopper);
	std::thread shopper2(shopper);
	shopper1.join();
	shopper2.join();
	printf("We should buy %u garlic.\n", garlic_count);
	printf("We should buy %u potatoes.\n", potato_count);

	return 0;
}
