/**
 * Two philosophers, thinking and eating sushi
 * in this example we demonstrate how to fix the dinning philosophers.
 * These are threads that need to lock more than a mutex to operate.
 * The problem happens when the threads don't lock the mitexes al in the same order
 * therefore they enter a dead lock.
 */
#include <thread>
#include <mutex>
#include <cstdio>
#include <functional>

int sushi_count = 5000;

//this function accepts two mutexes.
void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
	//repeat until the sushi is gone.
	while(sushi_count > 0) {
		//it locks the first mutex received first
		first_chopstick.lock();
		//it locks the second mutex received next
		second_chopstick.lock();

		//it does it operation
		if(sushi_count) {
			sushi_count--;
		}

		//it unlocks the mutexes in reverse order
		second_chopstick.unlock();
		first_chopstick.unlock();
	}
}

int main()
{
	std::mutex chopstick_a, chopstick_b; //we have these two mutexes

	//the first philosopher receives the first mutex first, then the second
	std::thread philosopher1(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));

	//the second pholosopher receives the second mutex first, then the first
	//std::thread philosopher2(philosopher, std::ref(chopstick_b), std::ref(chopstick_a)); //this will deadlock as it gets the mutexes in inverted order

	//to solve the deadlock we need to provide the mitexes in the same order
	std::thread philosopher2(philosopher, std::ref(chopstick_a), std::ref(chopstick_b)); //there has to be the commitment to get the mutexes always in the same order.

	//we wait for the two to finish.
	philosopher1.join();
	philosopher2.join();


	printf("The philosofers are done eating.\n");

	return 0;
}

