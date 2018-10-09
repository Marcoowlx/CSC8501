#include <iostream>

using namespace std;

// declare enemy class

class Enemy {
public:
	Enemy(int hps);
	virtual ~Enemy();
	virtual int get_hit_points();
	virtual int get_score();
	virtual void set_hit_points(int new_hit_points);
	virtual	void set_score(int new_score)=0;
protected:
	int hit_points;
	int* score;
};

// define enemy class

Enemy::Enemy(int hps) :
	hit_points(hps) {
	score = new int(0);
}

Enemy::~Enemy() {
	delete score;
}

int Enemy::get_hit_points(){
	return hit_points;
}

void Enemy::set_hit_points(int new_hit_points) {
	hit_points = new_hit_points;
}

int Enemy::get_score(){
	return *score;
}

// declare flying enemy class

class ArmedEnemy : public Enemy
{
public:
	ArmedEnemy(int hps, int ammo);
	virtual ~ArmedEnemy();
	virtual void set_score( int new_score);
	virtual void shoot();
protected:
	int ammo_level;
};

// define flying enemy class

ArmedEnemy::ArmedEnemy(int hps, int ammo) :
	Enemy(hps),
	ammo_level(ammo) {
}

ArmedEnemy::~ArmedEnemy() {
}

void ArmedEnemy::set_score( int new_score) {
	*score = new_score;
	cout << "score is now " << *score << "\n";
}

void ArmedEnemy::shoot() {
	if (ammo_level > 0)
	{
		cout << "bang!\n";
		--ammo_level;
	}
	else
	{
		cout << "out of ammo\n";
	}
}


class Boss :public ArmedEnemy {
public:
	Boss(int hps, int ammo, int a_ammo);
	~Boss();
	void set_a_ammo(int a_ammo);
	int get_a_ammo();

private:
	int a_ammo_level;
};

Boss::Boss(int hps, int ammo, int a_ammo) :
	ArmedEnemy(hps, ammo),
	a_ammo_level(a_ammo) {

}

Boss::~Boss() {
}

void Boss::set_a_ammo(int a_ammo) {
	a_ammo_level = a_ammo;
}

int Boss::get_a_ammo() {
	return a_ammo_level;
}

void decre(Enemy* e) {
	e->set_hit_points(e->get_hit_points() - 1);
}

int main(void) {
	Enemy* arr[11];
	arr[0] = new ArmedEnemy(1,1);
	arr[1] = new ArmedEnemy(2, 2);
	arr[2] = new ArmedEnemy(3, 3);
	arr[3] = new ArmedEnemy(4, 4);
	arr[4] = new ArmedEnemy(5, 5);
	arr[5] = new ArmedEnemy(6, 6);
	arr[6] = new ArmedEnemy(7, 7);
	arr[7] = new ArmedEnemy(8, 8);
	arr[8] = new ArmedEnemy(9, 9);
	arr[9] = new ArmedEnemy(10, 10);
	arr[10] = new Boss(11, 11,7);

	for (int i = 0; i < 11; i++) {
		cout << "The hit pointer is:" << arr[i]->get_hit_points() << endl;
		decre(arr[i]);
		cout << "The new hit pointer is:" << arr[i]->get_hit_points() << endl;
	}

	Enemy** p[11];
	for (int j = 0; j < 11; j++) {
		p[j] = &arr[j];
		cout << p[j] << endl;
	}

	system("pause");
	delete *arr;
	delete **p;
	return 0;
}
