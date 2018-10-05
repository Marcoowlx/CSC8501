#include <iostream>

using namespace std;

void stack_print(char a[]) {
	for (int x = 0; x < 5; x++) {
		cout << a[x];
	}
}

void copy(char* x, char y[]) {
	for (int c = 0; c < 5; c++) {
		x[c] = y[c];
	}
}

void heap_print(char x[]) {
	for (int c = 0; c < 5; c++) {
		cout << x[c];
	}
}


void main() {
	//stack 栈
	char f[5] = {'M','a','r','c','o'};
	char l[5] = { 'W','a','n','g' };
	stack_print(f);
	cout << " ";
	stack_print(l);

	//heap 堆
	char* ff=new char[5];
	char* ll=new char[5];
	copy(ff, f);
	copy(ll, l);
	heap_print(ff);
	cout << " ";
	heap_print(ll);
	system("pause");
}