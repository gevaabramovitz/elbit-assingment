//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

constexpr size_t ITERATIONS = 1000*1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

std::atomic<size_t> sum(0);
//size_t sum = 0;

void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		sum += (arg+i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		sum += (arg*i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}

//15026
int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
    std::thread t1(operation1, OP1_PARAM);
//	operation1(OP1_PARAM);
	operation2(OP2_PARAM);
    t1.join();
	auto end = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum <<  ", " <<(sum == EXPECTED_SUM ? "success" :
    "failure!")<< std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
    // I needed to use an atomic counter in order to avoid of unreliable increasing of the
    // counter that is, to change the increasing operation to be atomic operation.
    // I used ".join()" func in order to make sure that the entire operations (1, 2) has completed
}