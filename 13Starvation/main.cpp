/**
 * two philosophers, thinking and eating sushi
 * In this example we show the issue of threads that don't have the chance
 * to execute as long as there are too many competitors
 * no resolved
 */

#include <thread>
#include <mutex>
#include <sstream>

int sushi_count = 5000;

void philosopher(std::mutex &chopsticks)
{
	int sushi_eaten = 0;

	while(sushi_count > 0) {
		std::scoped_lock lock(chopsticks); // C++17
		if(sushi_count) {
			sushi_count--;
			sushi_eaten++;
		}

		//simulating an issue that ends the proccess without unloking the mutex;
		if(sushi_count == 10){
			printf("This philosopher has had enough!\n");
			break;
		}

		//chopsticks.unlock(); //not longer needed
	} //scope ends here

	std::stringstream ss;
	ss << std::this_thread::get_id(); //it returns a std::thread::id object

	printf("Philosopher %s ate %d.\n", ss.str().c_str(), sushi_eaten);
}

int main()
{
	std::mutex chopsticks;

	//this time we have all these philosophers
	std::array<std::thread, 200> philosophers;

	for(size_t i = 0; i < philosophers.size(); i++){
		philosophers[i] = std::thread(philosopher, std::ref(chopsticks));
	}

	for(size_t i = 0; i < philosophers.size(); i++){
		philosophers[i].join();
	}

	printf("The philosophers are done eating.\n");

	//what we see is that most of the philosophers report they couldn't eat at all

	return 0;
}
