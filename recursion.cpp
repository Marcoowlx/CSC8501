#include <iostream>

using namespace std;

void func(int x) {
	cout << "Input a number:" << "\n";
	cin >> x;
	if (x >= 0) {
		cout << "You input a positive number!" << "\n";
		func(x);
	}
	else {
		cout << "You input a negative number, program ends!" << "\n";
	}
}

int main() {
	int x;
	x = 0;
	func(x);
	system("pause");
}