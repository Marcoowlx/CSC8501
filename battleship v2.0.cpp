#include <iostream>
#include <ctime>
using namespace std;

class BS {
public:
	BS(int hps);
	~BS();
	void set_location(int l,int w);
	void set_score();
	void set_hit_points(int hp);
	int get_score();
	int get_hit_points();
private:
	int hit_points;
	int score;
	int len, width;
};

BS::BS(int hps) :
	hit_points(hps) {
	 score = 0;
}

BS::~BS() {

}

void BS::set_score() {
	score ++;
}

void BS::set_hit_points(int hp) {
	hit_points = hp;
}

int BS::get_score() {
	return score;
}

int BS::get_hit_points() {
	return hit_points;
}

void BS::set_location(int l,int w) {
	len = l;
	width = w;
}



//创建玩家对象
BS player(0);

//创建敌船对象
BS s1(1);
BS s2(1);

//创建2张地图
bool f[5][5];
bool g[5][5];

void init_map() {
	//比较地图全部设置为false
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			g[i][j] = false;
		}
	}
	//将显示地图全部设置为false
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			f[i][j] = false;
		}
	}

}

void print_map() {
	//打印显示地图
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << f[i][j];
		}
		cout << endl;
	}

	//打印比较地图
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << g[i][j];
		}
		cout << endl;
	}
}

void quit_game() {
	//退出
	cout << "Game ending! Your score is:" << player.get_score() << endl;
	cout << "Game ending! Your hitpoints is:" << player.get_hit_points() << endl;
	system("pause");
}

void main() {

	//初始化地图
	init_map();


	//设置时间种子
	srand((unsigned)time(NULL));
	int k1,k2,k3,k4,k5, j1,j2,j3,j4,j5;
	k1 = rand() % 5;
	j1 = rand() % 5;
	k2 = rand() % 5;
	j2 = rand() % 5;

	//将随机生成船的位置设置为true
	s1.set_location(k1,j1);
	g[k1][j1] = true;
	s2.set_location(k2, j2);
	g[k2][j2] = true;





print:
	
	print_map();

input:
	//输入横坐标
	cout << "Input a number for first coordinate(0-4,  5 to quit):" << endl;
	int x;
	cin >> x;
	if (x == 5) {
		goto quit;
	}
	//输入纵坐标
	cout << "Input a number for second coordinate(0-4):" << endl;
	int y;
	cin >> y;

	cout << "Your guess is " << "[ " << x << " ]" << "[ " << y << " ]" << endl;

	//与比较地图比较
	if (g[x][y] == true) {
		f[x][y] = true;
		g[x][y] = false;
		cout << "Congratulations! You hit a ship!" << endl;
		player.set_score();
		goto print;
	}
	else
	{
		cout << "Sorry! You didn't hit a ship!" << endl;
		goto print;
	}

quit:
	quit_game();
}