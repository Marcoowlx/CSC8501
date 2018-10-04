#include <iostream>

using namespace std;


void swapp(int &a,int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

}

void arr_swap(int a[]) {
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (a[x] > a[x + 1]) {
				swapp(a[x], a[x + 1]);
			}
		}
	}
}

void print(int a[]) {
	for (int x = 0; x < 10; x++) {
		cout << " [ " << a[x] << " ] " ;
	}
}

int nums[10] = { 7,4,5,8,2,6,9,1,3,10 };


void main() {
	int x ,y ;
	cout << "Input a number" << endl;
	cin >> x;

	cout << "Input another number" << endl;
	cin >> y;

	cout << "The first number = " << x << " before swap" << endl;
	cout << "The second number = " << y << " before swap" << endl;
	swapp(x, y);

	cout << "The first number = " << x << " after swap" << endl;
	cout << "The second number = " << y << " after swap" << endl;

	print(nums);
	arr_swap(nums);
	cout << endl;
	print(nums);
	

	system("pause");
}