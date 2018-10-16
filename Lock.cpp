#include <iostream>
#include <ctime>

using namespace std;


//定义锁的结构体
struct lock {
	int *ROOT = new int[4];
	int *CN= new int[4];
	int *LN= new int[4];
	int *HN= new int[4];
	struct lock* left;
	struct lock* right;
};


//拆分ROOT
int* g_root(int a) {
	int * root = new int[4];
	root[0] = a / 1000;
	root[1] = a % 1000 / 100;
	root[2] = a % 100 / 10;
	root[3] = a % 10;
	return root;
}

//hash function
int* hash_func(int* first, int * last) {
	int *new_arr = new int[4];
	for (int i = 0; i < 4; i++) {
		if (last[i] >= 0)
			new_arr[i] = (first[i] + last[i]) % 10;
		else
			new_arr[i] = (first[i] + last[i] + 10) % 10;
	}
	return new_arr;
}

//print
void print(int *print) {
	for (int i = 0; i < 4; i++) {
		cout << "[ " << print[i] << " ]";
	}
}

//通过ROOT得到CN
int* UHF(int* first, int* last) {
	int* new_CN = new int[4];
	new_CN = hash_func(first, last);
	return new_CN;

}

//通过CN得到LN
int* LHF(int* first, int* last) {
	int* new_LN = new int[4];
	new_LN = hash_func(first, last);
	return new_LN;
}

//通过LN得到HN
int* PHF(int* first, int* last) {
	int* new_HN = new int[4];
	new_HN = hash_func(first, last);
	return new_HN;
}

//产生随机数
int* random(int *a) {
	for (int i = 0; i < 4; i++) {
		a[i] = (rand() % 19) - 9;
	}
	return a;
}


int main() {

	//设置时间种子
	srand((unsigned)time(NULL));

	int ROOT = rand() % 10000;
	int *arr_CN = new int[4];
	int *arr_LN = new int[4];
	int *arr_HN = new int[4];

	
	//初始化结构体
	struct lock* new_lock= new lock;

	//递归创建想法
	//new_lock->next->ROOT = new_lock->HN;

	//产生随机hash值
	arr_CN = random(arr_CN);
	arr_LN = random(arr_LN);
	arr_HN = random(arr_HN);

	print(arr_CN);
	cout << endl;
	print(arr_LN);
	cout << endl;
	print(arr_HN);
	cout << endl;
	//产生ROOT
	new_lock->ROOT = g_root(ROOT);

	//产生CN
	new_lock->CN = UHF(new_lock->ROOT, arr_CN);
	
	//产生LN
	new_lock->LN = LHF(new_lock->CN, arr_LN);

	//产生HN
	new_lock->HN = PHF(new_lock->LN, arr_HN);
	
	//输出ROOT
	cout << "The ROOT is:" << endl;
	print(new_lock->ROOT);
	cout << endl;

	//输出CN
	cout << "The CN is:" << endl;
	print(new_lock->CN);
	cout << endl;

	//输出LN
	cout << "The LN is:" << endl;
	print(new_lock->LN);
	cout << endl;

	//输出HN
	cout << "The HN is:" << endl;
	print(new_lock->HN);
	cout << endl;

	system("pause");
	return 0;

}