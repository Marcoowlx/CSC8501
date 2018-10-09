#include <iostream>

using namespace std;

// declare enemy class

class Enemy {
public:
	Enemy(int hps);
	virtual ~Enemy();
	virtual int get_hit_points() const;
	virtual int get_score() const;
	virtual void set_hit_points(int new_hit_points);
	virtual	void set_score(int new_score);
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

int Enemy::get_hit_points() const {
	return hit_points;
}

int Enemy::get_score() const {
	return *score;
}

void Enemy::set_hit_points(const int new_hit_points) {
	hit_points = new_hit_points;
}

void Enemy::set_score(const int new_score) {
	*score = new_score;
}

// declare flying enemy class

class ArmedEnemy : public Enemy
{
public:
	ArmedEnemy(int hps, int ammo);
	virtual ~ArmedEnemy();
	virtual void set_score(const int new_score);
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

void ArmedEnemy::set_score(const int new_score) {
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
	void set_score(int sc);
	void set_a_ammo(int a_ammo);
	void shoot();
	int get_score();
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

void Boss::set_score(int sc) {
	*score = sc;
	cout << "Boss score is:" << *score << endl;
}

void Boss::shoot() {
	if (a_ammo_level > 0)
	{
		cout << "bang!\n";
		--a_ammo_level;
	}
	else
	{
		cout << "out of ammo\n";
	}
}

int Boss::get_score() {
	return *score;
}

void Boss::set_a_ammo(int a_ammo) {
	a_ammo_level = a_ammo;
}

int Boss::get_a_ammo() {
	return a_ammo_level;
}



void some_function(Enemy& enemy) {
	enemy.set_score(6);
}

int main(void) {

	Boss* b = new Boss(2, 5, 7);
	b->set_hit_points(3);
	cout << "hit points = " << b->get_hit_points() << "\n";

	b->shoot();

	some_function(*b);
	b->set_score(5);
	cout << "Boss ammo is:" << b->get_a_ammo() << endl;
	b->set_a_ammo(11);
	cout << "After change boss ammo is:" << b->get_a_ammo() << endl;
	system("pause");
	delete b;
	b = NULL;
	return 0;
}
