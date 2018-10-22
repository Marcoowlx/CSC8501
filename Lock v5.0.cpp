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

//定义类
class my_func {
public:
	my_func() {};
	~my_func() {};
	int* g_root(int a);
	int* hash_func(int* first, int * last);
	void print(int *print);
	int* UHF(int* first, int* last);
	int* LHF(int* first, int* last);
	int* PHF(int* first, int* last);
	int* random(int *a);
private:
};

//创建5把锁数组
lock new_lock[5];

//创建输出文件数组
lock new_file[500];

//拆分ROOT
int* my_func::g_root(int a) {
	int * root = new int[4];
	root[0] = a / 1000;
	root[1] = a % 1000 / 100;
	root[2] = a % 100 / 10;
	root[3] = a % 10;
	return root;
}

//hash function
int* my_func::hash_func(int* first, int * last) {
	int *new_arr = new int[4];
	for (int i = 0; i < 4; i++) {
		if (last[i] >= 0)
			new_arr[i] = (first[i] + last[i]) % 10;
		else
			new_arr[i] = (first[i] + last[i] + 10) % 10;
	}
	return new_arr;
}

//打印结构体
void my_func::print(int *print) {
	for (int i = 0; i < 4; i++) {
		cout << "[ " << print[i] << " ]";
	}
}

//通过ROOT得到CN
int* my_func::UHF(int* first, int* last) {
	int* new_CN = new int[4];
	new_CN = hash_func(first, last);
	return new_CN;

}

//通过CN得到LN
int* my_func::LHF(int* first, int* last) {
	int* new_LN = new int[4];
	new_LN = hash_func(first, last);
	return new_LN;
}

//通过LN得到HN
int* my_func::PHF(int* first, int* last) {
	int* new_HN = new int[4];
	new_HN = hash_func(first, last);
	return new_HN;
}

//产生随机数
int* my_func::random(int *a) {

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

//判断是否valid
bool w_valid(int i) {
	
	int sum=0;
	int LN_sum0=0;
	int LN_sum1=0;
	int LN_sum2=0;
	int LN_sum3=0;
	int LN_sum4=0;
	bool ret=true;
	
	//判断CN是否相等
	for (int j = 0; j < 5; j++) {
		cout << "CN = ";
		cout << new_file[j + 5 * i].CN[0];
		cout << new_file[j + 5 * i].CN[1];
		cout << new_file[j + 5 * i].CN[2];
		cout << new_file[j + 5 * i].CN[3]<<endl;
		cout << "i= " << i << endl;
		if (new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[1] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[3] ||
			new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[3] ||
			new_file[j + 5 * i].CN[2] == new_file[j + 5 * i].CN[3]) {
			cout << "CN equals!" << endl;
			ret = false;
			return ret;			
		}
	}

	//判断LN是否为偶数
	for (int j = 0; j < 5; j++){
		for (int z = 0; z < 4; z++) {
			sum = sum + new_file[j + 5 * i].LN[z];
		}
	}

	if (sum % 2 == 1) {
		ret = false;
		cout << "Even sum!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return ret;
	}

	
	/*//判断LN是否小于右边
	for (int z = 0; z < 4; z++) {
			LN_sum0 = LN_sum0 + new_file[5 * i].LN[z];
			LN_sum1 = LN_sum0 + new_file[1+5 * i].LN[z];
			LN_sum2 = LN_sum0 + new_file[2+5 * i].LN[z];
			LN_sum3 = LN_sum0 + new_file[3+5 * i].LN[z];
			LN_sum4 = LN_sum0 + new_file[4+5 * i].LN[z];
	}*/


	/*if (LN_sum0 >= LN_sum1 || LN_sum1 >= LN_sum2 || LN_sum2 >= LN_sum3 || LN_sum3 >= LN_sum4) {}
	{
		cout << " more than!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		ret = false;
		return ret;
	}*/
		
	return ret;
}

//洗牌算法
void get_rand_number(int array[], int length)
{

	//设置时间种子
	srand((unsigned)time(NULL));

	int index;
	int value;
	int median;

	if (NULL == array || 0 == length)
		return;

	for (index = 0; index < length; index++) {
		value = index + rand() % (length - index);

		median = array[index];
		array[index] = array[value];
		array[value] = median;
	}
}

//创建CN,LN,HN数组
int *arr_CN = new int[4];
int *arr_LN = new int[4];
int *arr_HN = new int[4];

//创建判断
bool useful = true;

int main() {

	//洗牌生成0-9999的数
	int arr_ROOT[10000];

	for (int i = 0; i < 10000; i++) {
		arr_ROOT[i] = i;
	}
	
	//打乱排序
	get_rand_number(arr_ROOT, 10000);
	
	

	//初始化class
	my_func func;

	//创建文件操作
	ofstream outkey_file, outm_file;
	ifstream inkey_file, inm_file;
	outkey_file.open("key_file.txt");
	inkey_file.open("key_file.txt");
	outm_file.open("multi_file.txt");
	inm_file.open("multi_file.txt");

	restart:
	//产生随机hash值
	arr_CN = func.random(arr_CN);
	arr_LN = func.random(arr_LN);
	arr_HN = func.random(arr_HN);

	int f=0 ;
	int ROOT;
	
	
	
		
		//输出key_file
	
		for (int i = 0; i < 100; i++) {
			if (f < 10000) {
				cout << f << endl;
					cout << "i= " << i << endl;
				//随机产生ROOT
				ROOT = arr_ROOT[f];
				//cout << "ROOT= "<<arr_ROOT[i]<<endl;

				//分割ROOT 并传入结构体ROOT
				new_file[5 * i].ROOT = func.g_root(ROOT);

				//产生第一个CN
				new_file[5 * i].CN = func.UHF(new_file[5 * i].ROOT, arr_CN);

				//产生第一个LN
				new_file[5 * i].LN = func.LHF(new_file[5 * i].CN, arr_LN);

				//产生第一个HN
				new_file[5 * i].HN = func.PHF(new_file[5 * i].LN, arr_HN);

				//循环产生后4把锁
				for (int u = 1; u < 5; u++) {

					new_file[u + 5 * i].ROOT = new_file[5 * i].ROOT;
					//产生CN
					new_file[u + 5 * i].CN = func.UHF(new_file[(u - 1) + 5 * i].HN, arr_CN);

					//产生LN
					new_file[u + 5 * i].LN = func.LHF(new_file[u + 5 * i].CN, arr_LN);

					//产生HN
					new_file[u + 5 * i].HN = func.PHF(new_file[u + 5 * i].LN, arr_HN);
				}

				//计数+1
				f++;

				//判断是否有效
				useful = w_valid(i);

				//根据是否有效做出操作
				//如果有效
				if (useful == true)
				{
					cout << "valid! f= " << f << endl;
					outkey_file << "NS" << i + 1 << endl;
					outkey_file << "ROOT ";
					outkey_file << new_file[5 * i].ROOT[0] << new_file[5 * i].ROOT[1] << new_file[5 * i].ROOT[2] << new_file[5 * i].ROOT[3] << endl;
					outkey_file << "UHF ";
					outkey_file << "[ " << arr_CN[0] << " ]" << "[ " << arr_CN[1] << " ]" << "[ " << arr_CN[2] << " ]" << "[ " << arr_CN[3] << " ]" << endl;
					outkey_file << "LHF ";
					outkey_file << "[ " << arr_LN[0] << " ]" << "[ " << arr_LN[1] << " ]" << "[ " << arr_LN[2] << " ]" << "[ " << arr_LN[3] << " ]" << endl;
					outkey_file << "PHF ";
					outkey_file << "[ " << arr_HN[0] << " ]" << "[ " << arr_HN[1] << " ]" << "[ " << arr_HN[2] << " ]" << "[ " << arr_HN[3] << " ]" << endl;

				}
				//如果无效
				else {
					cout << "unvalid! f= " << f << endl;
					i--;
				}
			}
			else {
				cout << "GG" << endl;
				system("pause");
				cout << "Input 1 to restart, 0 to quit" << endl;
				int r;
				cin >> r;
				if (r == 1) {
					cout << "restart!" << endl;
					system("pause");
					goto restart;
				}
				else {
					cout << "over!" << endl;
					system("pause");
					exit(0);
				}
			}
			
	}
	
	
		//整行读取文件
		string s[500];
		for (int i = 0; i < 500; i++) {
				getline(inkey_file, s[i]);
				cout << s[i] << endl;
			}

		//分割UHF LHF RHF
		vector<string> v1 = split(s[2], ",[] ");

		//String转为int型
		int UHF_read[4];
		for (int i = 0; i < 4; i++)
			str2int(UHF_read[i], v1[i + 1]);
		cout << endl;

		vector<string> v2 = split(s[3], ",[] "); ;

		//String转为int型
		int LHF_read[4];
		for (int i = 0; i < 4; i++)
			str2int(LHF_read[i], v2[i + 1]);
		cout << endl;


		vector<string> v3 = split(s[4], ",[] ");

		//String转为int型
		int PHF_read[4];
		for (int i = 0; i < 4; i++)
			str2int(PHF_read[i], v3[i + 1]);
		cout << endl;


		//分割ROOT v[0]为“ROOT”，v[1]为值
		vector<string> v;
		int ROOT_read;

		//读取key_file后的操作
		for (int i = 0; i < 100; i++) {

				//分割ROOT
				v = split(s[1 + 5 * i], " ");

				//读取ROOT值，变为int
				str2int(ROOT_read, v[1]);

				//产生第一个CN
				new_file[5 * i].CN = func.UHF(func.g_root(ROOT_read), UHF_read);

				//产生第一个LN
				new_file[5 * i].LN = func.LHF(new_file[5 * i].CN, LHF_read);

				//产生第一个HN
				new_file[5 * i].HN = func.PHF(new_file[5 * i].LN, PHF_read);

				//循环产生后4把锁
				for (int u = 1; u < 5; u++) {
					//产生CN
					new_file[u + 5 * i].CN = func.UHF(new_file[(u - 1) + 5 * i].HN, UHF_read);

					//产生LN
					new_file[u + 5 * i].LN = func.LHF(new_file[u + 5 * i].CN, LHF_read);

					//产生HN
					new_file[u + 5 * i].HN = func.PHF(new_file[u + 5 * i].LN, PHF_read);
				}



				//输出multi_safe_file
				outm_file << "NS" << i + 1 << " ";
				if (useful == true) {
					outm_file << "VALID" << endl;
				}
				else {
					outm_file << "NOT VALID" << endl;
				}

				for (int j = 0; j < 5; j++) {
					outm_file << "CN" << j << " ";
					for (int z = 0; z < 4; z++) {
						outm_file << new_file[j + 5 * i].CN[z];
					}
					outm_file << ",";

					outm_file << "LN" << j << " ";
					for (int z = 0; z < 4; z++) {
						outm_file << new_file[j + 5 * i].LN[z];
					}
					outm_file << ",";

					outm_file << "HN" << j << " ";
					for (int z = 0; z < 4; z++) {
						outm_file << new_file[j + 5 * i].HN[z];
					}

					outm_file << endl;
				}



			
		}
	
	

	outkey_file.close();
	inkey_file.close();
	outm_file.close();
	inm_file.close();
	system("pause");
	return 0;

}