#include <thread>


void test()
{
	long int x = 1;
	for (int i=1; i < 10000000000; i++)
	{
		x = x * i + x;
	}
}


int main()
{
	std::thread thread1(test);
	std::thread thread2(test);
	std::thread thread3(test);
	std::thread thread4(test);
	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	
	return 0;
}