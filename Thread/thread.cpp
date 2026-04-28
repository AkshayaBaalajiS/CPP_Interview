#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m1;
mutex m2;

int global_data = 0 ;

condition_variable cv;
bool pred1 = false;




// thread function 
void function()
{
	for(int i=0;i<10;i++)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		
		{
			unique_lock<std::mutex> ul(m1);
			// ul.lock();
			/*
			👉 Why?
				unique_lock(m1) → already locks the mutex
				then you call ul.lock() again → ❌ double lock
			👉 This leads to:
				undefined behavior
				possible deadlock
				strange behavior
			*/
			global_data--;
			// ul.unlock();
			/*
				locks in constructor (by default)
				unlocks in destructor (RAII)
				no need for manual lock/unlock
			*/
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(223));
		auto end_time = std::chrono::high_resolution_clock::now();
		auto dura = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		cout<<"[DEBUG PRINT] function duration = " << dura.count() <<endl;
		
	}
}

void function1(void(*funcPtr1)())
{
	for(int i=0;i<10;i++)
	{
		// std::this_thread::sleep_for(std::chrono::milliseconds(112));
		auto start_time = std::chrono::high_resolution_clock::now();
		{	
			unique_lock<std::mutex> ul(m1, std::defer_lock);
			if(ul.try_lock())
			{
				// unique_lock<std::mutex> ul(m1);

				global_data++;
			}
			else
			{
				cout<<"[DEBUG PRINT] function1 lock not acquired \n";
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(123));
		auto end_time = std::chrono::high_resolution_clock::now();
		auto dura = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		cout<<"[DEBUG PRINT] function1 duration = " << dura.count() <<endl;
	
	}
}	

void funff()
{
	for(int i=0;i<10;i++)
	{	
		auto start_time = std::chrono::high_resolution_clock::now();
		unique_lock<std::mutex> ul(m2);
		cv.wait(ul, [](){return pred1;});
		pred1=false;
		auto end_time = std::chrono::high_resolution_clock::now();
		auto dura = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		cout<<"[DEBUG PRINT] funff duration = " << dura.count() <<endl;

	}
}			

int main()
{
	cout<<"This is the code to understand the Thread and prac the thread in cpp\n";
	auto lambdaFunc = [] ()
	{
		cout<<"@ Lambda function \n";
	};
	void (*funcPtr)()  = funff;
	thread t1(function);
	thread t2(function1, lambdaFunc);
	thread t3;
	thread t4(funff);
	
	for(int i=0;i<10;i++)
	{
		pred1 = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(93));
		cv.notify_one();
	}

	t1.join();
	t2.join();
	t4.join();
	if(t3.joinable())
	{
		cout<<"Thread can be joined \n";
	}
	else
	{
		cout<<"Thread cant be joined \n";
	}
	
}