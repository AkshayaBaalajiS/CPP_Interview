#include <iostream>
#include <functional>
#include <memory>
using namespace std;

void function0()
{
	cout<<"void function0()\n";
}

int function1(int a, int b)
{
	cout<<"int function1(int a, int b)\n";
	return 0;
}

unique_ptr<int> function2(void * a)
{
	cout<<"unique_ptr<int> function2()\n";
	return make_unique<int>(123);
}

int main()
{
	cout<<"THis is the program to understand the function pointer \n";

	void (*functionPtr)() = function0;
	functionPtr();

	cout<<"---------------------\n"; 
	int  (*functionPtr1)(int, int) = function1;
	functionPtr1(12,12);
	cout<<"---------------------\n"; 

	unique_ptr<int> (*function2Ptr)(void *) = function2;
	function2Ptr(nullptr);

	std::function<unique_ptr<int>(void *)> function2Ptr1 = function2;
	function2Ptr1(nullptr);

	cout<<"---------------------\n"; 

	{
		auto lambda = [&] (int a, int b)
		{
			cout<<"Lambda function \n";
		};
		lambda(12,12);
	}

	{
		void (*functionPtr2)(int, int)  = [] (int a, int b)  
		{
			cout<<"Lambda function \n";
		};
		functionPtr2(12,12);
	}

	{
		std::function<void (int, int)> functionPtr2   = [=] (int a, int b)  
		{
			cout<<"Lambda function \n";
		};
		functionPtr2(12,12);
	}
	
	cout<<"---------------------\n"; 


	
}