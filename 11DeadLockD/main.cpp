/**
 * Two philosophers, thinging and eathing sushi
 * in this example we are going to demonstrate how to fix the dead lock
 * with the scoped_lock class from C++ 17
 * we need to compile this program en C++ 17 for it to function
 * This is due to that we might not guarantee that the two mutexes will be locked an unlocked
 * in the right order across the code.
 */
#include <thread>
#include <mutex>
#include <cstdio>
#include <functional> //this is for the std::ref

int sushi_count = 5000;

void philosopher(std::mutex &first_chopstick, std::mutex &second_chopstick)
{
	//we repeat until the sushi is gone
	while(sushi_count > 0) {
		//with the scoped_lock the two mutexes lock and unlock at the same time in thread safe manner
		std::scoped_lock(first_chopstick, second_chopstick); //C++ 17

		//we do the calculation.
		if(sushi_count) {
			sushi_count--;
		}
		/* we not longer need to manually unlock the mitexes. they will be unlocked by scoped_lock at the end of the scope.
		second_chopstick.unlock();
		first_chopstick.unlock();
		*/
	} //end of the scope
}

int main()
{
	std::mutex chopstick_a, chopstick_b; //we declare the two mutexes

	//we can now provide the mutexes in either order
	std::thread philosopher1(philosopher, std::ref(chopstick_a), std::ref(chopstick_b));
	std::thread philosopher2(philosopher, std::ref(chopstick_b), std::ref(chopstick_a));

	//we wait for the philosophers
	philosopher1.join();
	philosopher2.join();

	printf("The philosofers are done eating.\n");

	return 0;
}
