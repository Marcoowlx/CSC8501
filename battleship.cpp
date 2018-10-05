#include <iostream>
#include <ctime>
using namespace std;




void main() {
	//setting time seed
	srand((unsigned)time(NULL));

	//create 2 maps
	bool f[5][5];
	bool g[5][5];
	int score=0;
	int k;

	//insert value into real map by random
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			k = rand() % 2;
			if (k == 1) {
				g[i][j] = true;
			}
			else {
				g[i][j] = false;
			}
		}
	}


	//create display map
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			f[i][j] = false;
		}
	}


print:
	//print display map
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << f[i][j];
		}
		cout << endl;
	}

input:
	//first coordinate
	cout << "Input a number for first coordinate(0-4,  5 to quit):" << endl;
	int x;
	cin >> x;
	if (x == 5) {
		goto quit;
	}
	//second coordinate
	cout << "Input a number for second coordinate(0-4):" << endl;
	int y;
	cin >> y;

	cout << "Your guess is " << "[ " << x << " ]" << "[ " << y << " ]" << endl;

	//compare with real map
	if (g[x][y] == true) {
		f[x][y] = true;
		cout << "Congratulations! You hit a ship!" << endl;
		score++;
		goto print;
	}
	else
	{
		cout << "Sorry! You didn't hit a ship!" << endl;
		goto print;
	}

quit:
	cout << "Game ending! Your score is:" << score << endl;
	system("pause");
}