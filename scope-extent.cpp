#include <iostream>

using namespace std;


namespace some_namespace {
	int some_function() {
		int x = 50;
		cout << "the value in x is " << x << "\n";
		cout << "the function called successfully in some_namespace" << "\n";
		return 0;
	}
}

namespace some_other_namespace {
	int some_function() {
		int x = 50;
		cout << "the value in x is " << x << "\n";
		cout << "the function called successfully in some_other_namespace" << "\n";
		return 0;
	}
}


using namespace some_namespace;
using namespace some_other_namespace;

int main() { 
	int x = 100;

	{
		int x = 200;
		cout << "the first value in x is " << x << "\n";
	}

	
	cout << "the second value in x is " << x << "\n";
	

	some_namespace::some_function();
	some_other_namespace::some_function();
	system("pause");

	return 0;
}