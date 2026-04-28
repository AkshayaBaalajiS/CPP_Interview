#include <iostream>
using namespace std;

int main()
{
	cout<<"This is the program to understand the Lambda \n";

	int a = 3;
	float b = 1234.234f;

	auto lambda = [] ()
	{
		cout<<"Lambda function \n";
	};	
	cout<<"--------------------------------------\n";
	cout<<"Capture class understand \n";

	auto lambda1 = [=] ()
	{
		cout<<"inside lambda " << " a = " << a <<endl;
		cout<< " b = " << b <<endl;
		// as the capture class = so value can be accessed but not altered 
		// a = 234;
		// b= 234.23423f;
	};
	lambda1();
	cout<<"--------------------------------------\n";

	auto lambda2 = [&] ()
	{
		cout<<"inside lambda " << " a = " << a <<endl;
		cout<< " b = " << b <<endl;
		 a = 564;	
		b= 234.23423f;
	};
	lambda2();
	cout<<"--------------------------------------\n";
	// capture by value 
	auto lambda3 = [a] ()
	{
		cout<<"inside lambda3 " << " a = " << a <<endl;
		 // a = 234;	// a is read only here 
	};
	lambda3();

	cout<<"--------------------------------------\n";
	// capture by value 
	auto lambda5 = [a] () mutable 
	{
		cout<<"inside lambda5 " << " a = " << a <<endl;
		 a = 6475;	
	};
	lambda5();
	cout<< " a = " << a <<endl;


	cout<<"--------------------------------------\n";
	// capture by reference  
	auto lambda4 = [&a] ()
	{
		cout<<"inside lambda3 " << " a = " << a <<endl;
		 a = 234; 
		 // b = 123;
	};
	lambda4();
	cout<<"--------------------------------------\n";
	auto lambda6 = [] (int & a)
	{
		cout<<"inside lambda3 " << " a = " << a <<endl;
		 a = 658; 
		 // b = 123;
	};
	lambda6(a);
	cout<<"a = " <<   a <<endl;

	{
		auto lambda7 = [] (int & a) 
		{
			cout<<"inside lambda3 " << " a = " << a <<endl;
			 a = 658; 
			 return a ;
			 // b = 123;
		};
		int result = lambda7(a);
		cout<<"a = " <<   a <<endl;
		cout<<"result = " <<   result <<endl;
	}

	{
		auto lambda7 = [] (int & a) -> float 
		{
			 dacout<<"inside lambda3 " << " a = " << a <<endl;
			 a = 658; 
			 return a * 0.24234 ;
			 // b = 123;
		};
		int result = lambda7(a);
		float result1 = lambda7(a);
		cout<<"a = " <<   a <<endl;
		cout<<"result = " <<   result <<endl;
		cout<<"result1 = " <<   result1 <<endl;
	}

	{
		// dangling reference prob 
		int * ptr = new int(123);
		auto lambda7 = [&] (int & a) -> float 
		{
			 dacout<<"inside lambda3 " << " a = " << a <<endl;
			 a = 658  +  *ptr; 

			 return a * 0.24234 ;
			 // b = 123;
		};

		delete ptr;
		int result = lambda7(a);
		float result1 = lambda7(a);
		cout<<"a = " <<   a <<endl;
		cout<<"result = " <<   result <<endl;
		cout<<"result1 = " <<   result1 <<endl;
	}

	

}