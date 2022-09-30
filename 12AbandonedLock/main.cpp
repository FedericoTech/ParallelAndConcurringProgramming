/**
 * two philosophers, thinking and eating sushi
 * In this example we are going to demonstrate how to
 * solve the issue of a thread exiting without unlocking a resource.
 * which would cause a deadlock in other threads waiting for the same resource.
 */

#include <thread>
#include <mutex>
#include <functional> // for the std::ref

int sushi_count = 5000;

void philosopher(std::mutex &chopsticks)
{
	//repeat until the sushi is gone
	while(sushi_count > 0) {
		std::scoped_lock lock(chopsticks);	// we lock the block with the scoped lock, C++ 17
		//make calculations
		if(sushi_count) {
			sushi_count--;
		}

		//simulating an issue that ends the process without unlocking the mutex;
		if(sushi_count == 10){
			printf("This philosopher has had enough!\n");
			break;
		}

		//chopsticks.unlock(); //not longer needed
	} //scope ends here
}

int main()
{
	std::mutex chopsticks;
	std::thread philosopher1(philosopher, std::ref(chopsticks));
	std::thread philosopher2(philosopher, std::ref(chopsticks));

	//we wait for the philosophers
	philosopher1.join();
	philosopher2.join();

	printf("The philosophers are done eating.\n");

	return 0;
}

