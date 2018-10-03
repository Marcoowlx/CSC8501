#include <iostream>

using namespace std;

void swaped(int c, int d) {
	int *a = &c;
	int *b = &d;
	cout << "The value of the 1st nmumber is " << c << "\n";
	cout << "The poiter value to the 1st nmumber is " << *a << "\n";

	cout << "The value of the 2nd nmumber is " << d << "\n";
	cout << "The poiter value to the 2nd nmumber is " << *b << "\n";
	int s = *a;
	*a = *b;
	*b = s;
	cout << "The value of the 1st nmumber is " << c << "\n";
	cout << "The poiter value to the 1st nmumber is " << *a << "\n";

	cout << "The value of the 2nd nmumber is " << d << "\n";
	cout << "The poiter value to the 2nd nmumber is " << *b << "\n";
}

void main() {
	int a, b;
	cout << "Input a number:" << "\n";
	cin >> a;
	cout << "Input another number:" << "\n";
	cin >> b;
	swaped(a, b);
	system("pause");
}