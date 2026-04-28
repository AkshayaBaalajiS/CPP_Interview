#include <iostream>
#include <memory>
using namespace std;

class A
{
	public :
		unique_ptr<int[]> up;
};

class B
{
	public :
		int a;
		B()
		{
			cout<<"@ B class constructor\n";
		}
		B(int a, float b)
		{
			cout<<"@ B class parameterized constructor\n";
		}
};

int main()
{
	cout<<"This is the program to prc the unique_ptr in cpp\n";
	A * ptr = new A();
	ptr->up = make_unique<int[]>(100);
	unique_ptr<A> up1 = make_unique<A>();
	unique_ptr<A*> up2 = make_unique<A*>();
	unique_ptr<A[]> up3 = make_unique<A[]>(10);  

	// the below cant be done cause for the array we need to mention the size and the cons should be called per individual element
	// and a default cons should be there 
	// unique_ptr<B[]> up4 = make_unique<B[]>(10, 100.0f);  
	// unique_ptr<B*> up5 = make_unique<B*>(10, 100.0f);  

	unique_ptr<B[]> up4 = make_unique<B[]>(10);  
	unique_ptr<B*> up5 = make_unique<B*>();
	
	B ** ptr23 = new B*[10]; // this is imple as below 
	// the below is not the RAI compliant 
	ptr23[0] = new B();
	ptr23[0]->a = 213;
	unique_ptr<B*[]> up6 = make_unique<B*[]>(10);
	up6[0] = new B();
	cout<<"up6[0].a = " << up6[0]->a<<endl;

	unique_ptr<unique_ptr<B*[]>> up7 = make_unique<unique_ptr<B*[]>>(make_unique<B*[]>(10)); 
	

}