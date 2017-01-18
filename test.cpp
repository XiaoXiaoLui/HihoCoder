#include <iostream>
#include <algorithm>

using namespace std;

bool operator < (const pair<int, int> &p1, const pair<int, int> &p2)
{
	cout << "Invoke 1" << endl;
	return true;
}

int main()
{
	pair<int, int> a, b;
	
	//a < b; // this line prints "Invoke 1"
	max(a, b); // prints nothing
	
	return 0;
}