#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Buffer
{
	public :
		Buffer()
		{

		}
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
		~Buffer()
		{
			cout<<"@ Buffer class destructor \n";
		}
};

int main()
{
	cout<<"This is the code to understand the unique_ptr in cpp\n";
	
	std::vector<Buffer> vect;
	vect.resize(10);

}