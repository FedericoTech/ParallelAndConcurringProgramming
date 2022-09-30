/**
 * Two philosophers, thinking and eating sushi
 * This example is the opposite to the dead lock.
 * the threads are designed to detect any collision so that
 * if any they return the resource.
 * The problem happens when several threads keep colliding and yielding
 * the resource. they keep working without progressing the work.
 */
#include <thread>
#include <mutex>
#include <cstdio>
#include <functional>

int sushi_count = 50000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
	//repeat until sushi is gone
	while(sushi_count > 0) {
		//we look first mutex
		first_chopstick.lock();

		//if second mutex is locked...
		if(!second_chopstick.try_lock()){
			//we return back the firt mutex
			first_chopstick.unlock();


			std::this_thread::yield(); //it yields the execution to a thread
		//if the second mutex is now ours...
		} else {
			//we do our task
			if(sushi_count) {
				sushi_count--;
			}

			//we unlock the mutexes
			second_chopstick.unlock();
			first_chopstick.unlock();
		}
	}
}

int main()
{
	std::mutex chopstick_a, chopstick_b;

	//we have all these philosophers.
	std::array<std::thread, 40000> philosophers;

	//we create them
	for(size_t i = 0; i < philosophers.size(); i+=2)
	{
		philosophers[i] = std::thread(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));

		//this philosopher gets the mutexes in reverse order which would produce a mutual exclusion
		philosophers[i + 1] = std::thread(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));
	}

	//we wait for them all
	for(size_t i = 0; i < philosophers.size(); i++)
	{
		philosophers[i].join();
	}

	printf("The philosofers are done eating.\n");

	return 0;
}





