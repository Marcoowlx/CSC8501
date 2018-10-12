#include <iostream>
#include <vector>

using namespace std;
using std::vector;

// declare enemy class

using std::cout;

class Enemy {
public:
	static const int default_hps = 4;
	Enemy() :hit_points(default_hps) { score = new int(0); }
	Enemy(int hps) :hit_points(hps) { score = new int(0); }
	Enemy(const Enemy& src);
	Enemy& operator=(const Enemy& rhs);
	virtual ~Enemy() { delete score; }
	virtual int get_hit_points() const { return hit_points; }
	virtual int get_score() const { return *score; }
	virtual void set_hit_points(int new_hit_points) { hit_points = new_hit_points; }
	virtual	void set_score(int new_score) { *score = new_score; }
protected:
	int hit_points;
	int* score;
};

class ArmedEnemy : public Enemy {
public:
	static const int default_ammo = 8;
	ArmedEnemy() :Enemy(), ammo_level(default_ammo) {}
	ArmedEnemy(int hps, int ammo) :Enemy(hps), ammo_level(ammo) {}
	virtual ~ArmedEnemy() {}
	virtual void set_score(const int new_score);
	virtual void shoot();
protected:
	int ammo_level;
};

Enemy::Enemy(const Enemy& src) :
	hit_points(src.hit_points),
	score(new int(*src.score))
{
}

/**
* assignment operator for enemy
*/
Enemy& Enemy::operator=(const Enemy& rhs)
{
	if (this == &rhs) {
		return (*this);
	}
	//free old memory
	delete score;

	//copy new memory
	hit_points = rhs.hit_points;
	score = new int(*rhs.score);

	return *this;
}

/**
* set score method
*/
void ArmedEnemy::set_score(const int new_score) {
	*score = new_score;
	cout << "score is now " << *score << "\n";
}

/**
* shoot method
*/
void ArmedEnemy::shoot() {
	if (ammo_level > 0) {
		cout << "bang!\n";
		--ammo_level;
	}
	else {
		cout << "out of ammo\n";
	}
}


int main() {

	vector<ArmedEnemy>* v = new vector<ArmedEnemy>(3);

	ArmedEnemy a, b;
	v->push_back(a);
	v->push_back(b);

	cout << "size of armedenemies is:" << v->size() << endl;

	system("pause");
	

	return 0;
}