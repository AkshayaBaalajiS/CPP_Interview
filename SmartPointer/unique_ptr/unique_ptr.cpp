#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Buffer
{
	public :
		int size;
		unique_ptr<int[]> up;

		Buffer(const Buffer&) = delete;
			
		Buffer(Buffer && ref)
		{
			size = ref.size;
			up = std::move(ref.up);
			ref.up = nullptr;
		}

		Buffer(int size) : size(size)
		{
			cout<<"@ Buffer class \n";
			up =  make_unique<int[]>(size);
		}

		// void set(unique_ptr<int[]> ref) // here unnecessary copy done 
		void set(unique_ptr<int[]> && ref) // in pass by reference no copy is taken 
		{
			up = std::move(ref);
		}

		unique_ptr<int[]> get()
		{
			return std::move(up);
		}
};

int main()
{
	cout<<"This is the code to understand the unique_ptr in cpp\n";
	
	unique_ptr<Buffer> up = make_unique<Buffer>(10);	

	// transfer ownership 
	unique_ptr<Buffer> up1;
	up1 = std::move(up);

	for(int i=0;i<up1->size;i++)
	{
		up1->up[i] = 12+i;
	}

	unique_ptr<int[]> up2 = up1->get();
	up1->set(std::move(up2));


	// STL + smart pointer 
	std::vector<unique_ptr<Buffer>> vect;
	vect.resize(10);
	vect[0] = make_unique<Buffer>(12);

	Buffer obj(12);
	// Buffer obj1 = obj;// use of deleted function this cant be done 
	Buffer obj1 = std::move(obj);// rather this can be done 

}