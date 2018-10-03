#include <iostream>

using namespace std;

void main() {
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int *a = &arr[0];
	for (int x = 10; x > 0; x--)
	{
		cout << "[" <<*a << "]" << " ";
		a++;
	}
	system("pause");
}