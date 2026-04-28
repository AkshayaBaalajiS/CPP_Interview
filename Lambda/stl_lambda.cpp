#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	cout<<"This is the code to understand the lambda \n";
	std::vector<int> v= {123,234,345,456,56,23,432,3443};

	for(auto i : v)
	{
		cout<<i << " " ;
	}
	cout<<endl;
	
	std::sort(v.begin(), v.end(), [](int & a, int & b){return a>b;});

	for(auto i : v)
	{
		cout<<i << " " ;
	}
	cout<<endl;
	
}
