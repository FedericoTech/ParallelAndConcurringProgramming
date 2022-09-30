/**
 * Threads that waste CPU cycles
 * This example shows that the main and the two threads are three threads of the same process
 */

#include <thread>
#include <chrono>
#include <unistd.h> //POSIX Operating system API
#include <iostream>

//a simple function that wastes CPU cycles "forever"
void cpu_waster()
{
	// the function getpid comes from unistd.h
	std::cout << "CPU Waster Proccess ID: " << getpid() << std::endl;
	std::cout << "CPU Waster Thread ID: " << std::this_thread::get_id() << std::endl;
	while(true) continue;
}

int main()
{
	std::cout << "Main Proccess ID: " << getpid() << std::endl;
	std::cout << "Main Thread ID: " << std::this_thread::get_id() << std::endl;

	std::thread thread1(cpu_waster);
	std::thread thread2(cpu_waster);

	while(true){ //infinite loop to only send the main thread to sleep.
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	//This program can only be exited with Ctr + C

	return 0;
}

