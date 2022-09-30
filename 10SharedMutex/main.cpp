/**
 * Several users reading a calendar, but only a few users updating it
 * In this example we demonstrate how we can lock a block only for "reading"
 * whereas it's blocked for "writing"
 */

#include <thread>
//#include <mutex>
#include <shared_mutex> //C++ 17
#include <chrono>
#include <cstdio>

char WEEKDAYS[7][10] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

int today = 0;
std::shared_mutex marker;

void calendar_reader(const int id)
{
	//lock_shared excludes lock until not lock_shared is left

	for(int i= 0; i < 7; i++){
		marker.lock_shared(); //locks for writing but not for reading
		printf("Reader-%d sees today is %s\n", id, WEEKDAYS[today]);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		marker.unlock_shared();
	}
}

void calendar_writer(const int id)
{
	//lock excludes lock_shared until it unlocks
	for(int i = 0; i < 7; i++) {
		marker.lock(); //it looks for writing and reading from other threads
		today = (today + 1) % 7;
		printf("Writer-%d updated date to %s\n", id, WEEKDAYS[today]);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		marker.unlock();
	}
}

int main()
{
	//create ten reather threads ... but only two writer threads
	std::array<std::thread, 10> readers;

	//we start all these reader threads
	for(unsigned int i = 0; i < readers.size(); i++) {
		readers[i] = std::thread(calendar_reader, i);
	}

	//we start all these writer threads
	std::array<std::thread, 2> writers;
	for(unsigned int i = 0; i < writers.size(); i++) {
		writers[i] = std::thread(calendar_writer, i);
	}

	//wait for the readers and writers to finish
	for(unsigned int i = 0; i < readers.size(); i++){
		readers[i].join();
	}

	for(unsigned int i = 0; i < writers.size(); i++){
		writers[i].join();
	}

	return 0;
}
