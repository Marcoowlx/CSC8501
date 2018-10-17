#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

//读取数据的分割
vector<string> split(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

//string转int
void str2int(int &int_temp, const string &string_temp)
{
	stringstream stream(string_temp);
	stream >> int_temp;
}

int main() {

	//设置时间种子
	srand((unsigned)time(NULL));

	ofstream outfile;
	ifstream infile;
	outfile.open("test.txt");
	infile.open("test.txt");
	int ROOT = rand() % 10000;
	int *arr_CN = new int[4];
	int *arr_LN = new int[4];
	int *arr_HN = new int[4];

	
	//初始化结构体
	lock new_lock[100];

	//产生随机hash值
	arr_CN = random(arr_CN);
	arr_LN = random(arr_LN);
	arr_HN = random(arr_HN);

	//产生ROOT
	new_lock[0].ROOT = g_root(ROOT);

	//产生CN
	new_lock[0].CN = UHF(new_lock[0].ROOT, arr_CN);
	
	//产生LN
	new_lock[0].LN = LHF(new_lock[0].CN, arr_LN);

	//产生HN
	new_lock[0].HN = PHF(new_lock[0].LN, arr_HN);

	//输出ROOT和3个定值
	for (int i = 0; i < 100; i++) {
		int ROOT = rand() % 10000;
		new_lock[i].ROOT = g_root(ROOT);
		outfile << "NS" << i + 1 << endl;
		outfile << "ROOT ";
		outfile << new_lock[i].ROOT[0] << new_lock[i].ROOT[1] << new_lock[i].ROOT[2] << new_lock[i].ROOT[3] << endl;
		outfile << "UHF ";
		outfile << "[ " << arr_CN[0] << " ]" << "[ " << arr_CN[1] << " ]" << "[ " << arr_CN[2] << " ]" << "[ " << arr_CN[3] << " ]" << endl;
		outfile << "LHF ";
		outfile << "[ " << arr_LN[0] << " ]" << "[ " << arr_LN[1] << " ]" << "[ " << arr_LN[2] << " ]" << "[ " << arr_LN[3] << " ]" << endl;
		outfile << "PHF ";
		outfile << "[ " << arr_HN[0] << " ]" << "[ " << arr_HN[1] << " ]" << "[ " << arr_HN[2] << " ]" << "[ " << arr_HN[3] << " ]" << endl;
	}


	//整行读取文件
	string s[5];
	for (int i = 0; i < 5; i++) {
		getline(infile, s[i]);
		cout << s[i] << endl;
	}

	//读取ROOT
	vector<string> v = split(s[1], ",[] "); //可按多个字符来分隔;
	/*cout << v[1] << " ";
	cout << endl;*/
	
	//读取UHF
	vector<string> v1 = split(s[2], ",[] "); //可按多个字符来分隔;
	/*cout << v1[1] << " ";
	cout << v1[2] << " ";
	cout << v1[3] << " ";
	cout << v1[4] << " ";
	cout << endl;*/

	//读取LHF
	vector<string> v2 = split(s[3], ",[] "); //可按多个字符来分隔;
	/*cout << v2[1] << " ";
	cout << v2[2] << " ";
	cout << v2[3] << " ";
	cout << v2[4] << " ";
	cout << endl;*/

	//读取RHF
	vector<string> v3 = split(s[4], ",[] "); //可按多个字符来分隔;
	/*cout << v3[1] << " ";
	cout << v3[2] << " ";
	cout << v3[3] << " ";
	cout << v3[4] << " ";
	cout << endl;*/

	//string2int
	int UHF_test[4];
	for (int i = 0; i < 4; i++) {
		str2int(UHF_test[i], v1[i + 1]);
		cout << UHF_test[i];
	}
	cout << endl;

	int LHF_test[4];
	for (int i = 0; i < 4; i++) {
		str2int(LHF_test[i], v2[i + 1]);
		cout << LHF_test[i];
	}
	cout << endl;

	int PHF_test[4];
	for (int i = 0; i < 4; i++) {
		str2int(PHF_test[i], v3[i + 1]);
		cout << PHF_test[i];
	}
	cout << endl;

	//通过读取的文件生成Lock2
	new_lock[1].ROOT = new_lock[0].HN;
	new_lock[1].CN= UHF(new_lock[1].ROOT, UHF_test);
	new_lock[1].LN = LHF(new_lock[1].CN, LHF_test);
	new_lock[1].HN = UHF(new_lock[1].LN, PHF_test);
	
	//输出ROOT
	cout << "The ROOT is:" << endl;
	print(new_lock[0].ROOT);
	cout << endl;

	//输出CN
	cout << "The CN is:" << endl;
	print(new_lock[0].CN);
	cout << endl;

	//输出LN
	cout << "The LN is:" << endl;
	print(new_lock[0].LN);
	cout << endl;

	//输出HN
	cout << "The HN is:" << endl;
	print(new_lock[0].HN);
	cout << endl;
	
	//Lock2
	//输出ROOT
	cout << "The ROOT is:" << endl;
	print(new_lock[1].ROOT);
	cout << endl;

	//输出CN
	cout << "The CN is:" << endl;
	print(new_lock[1].CN);
	cout << endl;

	//输出LN
	cout << "The LN is:" << endl;
	print(new_lock[1].LN);
	cout << endl;

	//输出HN
	cout << "The HN is:" << endl;
	print(new_lock[1].HN);
	cout << endl;

	

	system("pause");

	outfile.close();
	return 0;

}