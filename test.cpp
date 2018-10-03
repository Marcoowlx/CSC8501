
#include <iostream>
#include <string>

	using namespace std;

	int add(int x, int y) {
		return x + y;
	}

	int min(int x, int y) {
		return x - y;
	}

	double divide(int x, double y){
		return x / y;
	}

	double multi(int x, double y) {
		return x*y;
	}

	int main() {
		cout << "What's your first name?" << "\n";
		string fs;
		cin >> fs;

		cout << "What's your last name?" << "\n";
		string ls;
		cin >> ls;

		cout << "Hello!" << ' ' << fs << ' ' << ls << "\n";

		cout << "Input a number" << "\n";
		int x;
		cin >> x;

		cout << "Input another number" << "\n";
		int y;
		cin >> y;

		int ia;
		ia = add(x, y);
		int im;
		im = min(x, y);

		cout << x << "+" << y << "=" << ia <<"\n";
		cout << x << "-" << y << "=" << im <<"\n";

		cout << "Input a interger number:" << "\n";
		int z;
		cin >> z;

		cout << "Input a double number:" << "\n";
		double d;
		cin >> d;

		double dd;
		dd = divide(z, d);
		double mu;
		mu = multi(z, d);

		cout << z << "/" << d << "=" << dd << "\n";
		cout << z << "*" << d << "=" << mu << "\n";

		cin >> x;
		return 0;
	}



@marco