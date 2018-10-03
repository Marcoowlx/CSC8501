#include <iostream>

using namespace std;

bool func(int x) {
	if (x >= 0 ) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	int x;
mylabel:
	cout << "Input a number:" << "\n";
	cin >> x;
	bool b = func(x);
	if (b == true) {
		cout << "You input a positive number!" << "\n";
		goto mylabel;
	}
	else {
		cout << "You input a negative number, program ends!" << "\n";
		system("pause");
	}
}