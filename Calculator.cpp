#include <iostream>

using namespace std;

void add(double x, double y) {
	cout << x << "+" << y << "=" << x + y << "\n";
}

void min(double x, double y) {
	cout << x << "-" << y << "=" << x - y << "\n";
}

void divide(double x, double y) {
	cout << x << "/" << y << "=" << x / y << "\n";
}

void multi(double x, double y) {
	cout << x << "*" << y << "=" << x * y << "\n";
}


int main() {
	char c;
	c = 'y';
	do {
		cout << "Input a number:" << "\n";
		double x;
		cin >> x;
		cout << "Input another number:" << "\n";
		double y;
		cin >> y;

		cout << "choose an operator:" << "\n" << "1. +  2. -  3. /  4. *" << "\n";
		int o;
		cin >> o;
		switch (o) {
		case 1: add(x, y);
			break;
		case 2: min(x, y);
			break;
		case 3: divide(x, y);
			break;
		case 4: multi(x, y);
			break;
		default:
			cout << "You input the wrong number!" << "\n";
			break;
		}
		cout << "Input 'q' to quit / input 'y' to continue" << "\n";
		cin >> c;
		
	} while (c != 'q');

	cout << "Calculator end!" << "\n";

	system("pause");

	return 0;

}



@marco