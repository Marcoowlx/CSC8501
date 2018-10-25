#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

//create struct
struct lock {
	int *ROOT = new int[4];
	int *CN = new int[4];
	int *LN = new int[4];
	int *HN = new int[4];
	struct lock* left;
	struct lock* right;
};

//create class
class my_func {
public:
	my_func() {};
	~my_func() {};
	void get_length(int i);
	void set_length();
	vector<string> split(const string &s, const string &seperator);
	void str2int(int &int_temp, const string &string_temp);
	int* g_root(int a);
	int* hash_func(int* first, int * last);
	int* random(int *a);
	void generate_N();
	void get_rand_number(int array[], int length);
	void set_ROOT();
	int write_key_file();
	bool w_valid(int i);
	void read_key_file();
	void write_multi_file();
	void write_locked_safe_file();
	void loading();
private:
	//create new_file
	lock* new_file;
	//int 0-9999
	int arr_ROOT[10000];
	int ROOT;
	//create CN,LN,HN array
	int *arr_CN = new int[4];
	int *arr_LN = new int[4];
	int *arr_HN = new int[4];
	//create bool
	bool useful = true;
	int length ;
};

void my_func::get_length(int i) {
	length = i;
}

void my_func::set_length() {
	new_file = new lock[5*length];
}

//split string
//learn from https ://www.cnblogs.com/carsonzhu/p/5859552.html
vector<string> my_func::split(const string &s, const string &seperator) {
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

//string to int
void my_func::str2int(int &new_int, const string &new_string)
{
	//1. use stringstream
	/*stringstream stream(new_string);
	stream >> new_int;*/

	//2. use atoi
	new_int = atoi(new_string.c_str());
}

//split ROOT
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

//create random number
int* my_func::random(int *a) {
	for (int i = 0; i < 4; i++) {
		a[i] = (rand() % 19) - 9;
	}
	return a;
}

//create CN,LN,HN
void my_func::generate_N() {
	arr_CN = random(arr_CN);
	arr_LN = random(arr_LN);
	arr_HN = random(arr_HN);
}

//fisher
void my_func::get_rand_number(int array[], int length)
{
	//set time seed
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

//set ROOT
void my_func::set_ROOT() {
	for (int i = 0; i < 10000; i++) {
		arr_ROOT[i] = i;
	}

	//random
	get_rand_number(arr_ROOT, 10000);
}

//write key_file
int my_func::write_key_file() {

	ofstream outkey_file;
	outkey_file.open("key_file.txt");

	int f = 0;

	//write key_file
	for (int i = 0; i < length; i++) {
		if (f < 10000) {
			//create ROOT by random
			ROOT = arr_ROOT[f];

			//split ROOT into new_file
			new_file[5 * i].ROOT = g_root(ROOT);

			//create first CN
			new_file[5 * i].CN = hash_func(new_file[5 * i].ROOT, arr_CN);

			//create first LN
			new_file[5 * i].LN = hash_func(new_file[5 * i].CN, arr_LN);

			//create first HN
			new_file[5 * i].HN = hash_func(new_file[5 * i].LN, arr_HN);

			//create 4 locks
			for (int u = 1; u < 5; u++) {
				//pass ROOT
				new_file[u + 5 * i].ROOT = new_file[5 * i].ROOT;

				//create CN
				new_file[u + 5 * i].CN = hash_func(new_file[(u - 1) + 5 * i].HN, arr_CN);

				//create LN
				new_file[u + 5 * i].LN = hash_func(new_file[u + 5 * i].CN, arr_LN);

				//create HN
				new_file[u + 5 * i].HN = hash_func(new_file[u + 5 * i].LN, arr_HN);
			}

			//f+1
			f++;

			//whether is valid
			useful = w_valid(i);

	
			//if valid
			if (useful == true)
			{
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
			//if not valid
			else 
				i--;
		}
	}
	outkey_file.close();
	return f;
}

//whether_valid
bool my_func::w_valid(int i) {

	int sum = 0;
	int CN_sum0 = 0;
	int CN_sum1 = 0;
	int CN_sum2 = 0;
	int CN_sum3 = 0;
	int CN_sum4 = 0;
	bool ret = true;

	//whether CN equals
	for (int j = 0; j < 5; j++) {
		if (new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[1] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[3] ||
			new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[3] ||
			new_file[j + 5 * i].CN[2] == new_file[j + 5 * i].CN[3]) {
			ret = false;
			return ret;
		}
	}

	//whether cN is even
	for (int j = 0; j < 5; j++) {
		for (int z = 0; z < 4; z++) {
			sum = sum + new_file[j + 5 * i].CN[z];
		}
	}

	if (sum % 2 == 1) {
		ret = false;
		return ret;
	}


	//whether CN is less than right
	/*for (int z = 0; z < 4; z++) {
	CN_sum0 = CN_sum0 + new_file[5 * i].CN[z];
	CN_sum1 = CN_sum0 + new_file[1+5 * i].CN[z];
	CN_sum2 = CN_sum0 + new_file[2+5 * i].CN[z];
	CN_sum3 = CN_sum0 + new_file[3+5 * i].CN[z];
	CN_sum4 = CN_sum0 + new_file[4+5 * i].CN[z];
	}


	if (CN_sum0 >= CN_sum1 || CN_sum1 >= CN_sum2 || CN_sum2 >= CN_sum3 || CN_sum3 >= CN_sum4) 
	{
	cout << " more than!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	ret = false;
	return ret;
	}*/
	
	return ret;
}

//write key_file
void my_func::read_key_file() {
	ifstream inkey_file;
	inkey_file.open("key_file.txt");

	//read file by line
	string *s=new string[5*length];
	for (int i = 0; i < 5*length; i++) {
		getline(inkey_file, s[i]);
	}

	//split UHF LHF RHF
	vector<string> v1 = split(s[2], ",[] ");

	//UHF to int
	int UHF_read[4];
	for (int i = 0; i < 4; i++)
		str2int(UHF_read[i], v1[i + 1]);

	vector<string> v2 = split(s[3], ",[] "); ;

	//LHF to int
	int LHF_read[4];
	for (int i = 0; i < 4; i++)
		str2int(LHF_read[i], v2[i + 1]);

	vector<string> v3 = split(s[4], ",[] ");

	//PHF to int
	int PHF_read[4];
	for (int i = 0; i < 4; i++)
		str2int(PHF_read[i], v3[i + 1]);

	//split ROOT v[0] is “ROOT”，v[1] is value
	vector<string> v;
	int ROOT_read;

	//function after read key_file
	for (int i = 0; i < length; i++) {

		//split ROOT
		v = split(s[1 + 5 * i], " ");

		//ROOT to int
		str2int(ROOT_read, v[1]);

		//create first CN
		new_file[5 * i].CN = hash_func(g_root(ROOT_read), UHF_read);

		//create first LN
		new_file[5 * i].LN = hash_func(new_file[5 * i].CN, LHF_read);

		//create first HN
		new_file[5 * i].HN = hash_func(new_file[5 * i].LN, PHF_read);

		//create 4 locks
		for (int u = 1; u < 5; u++) {
			//create CN
			new_file[u + 5 * i].CN = hash_func(new_file[(u - 1) + 5 * i].HN, UHF_read);

			//create LN
			new_file[u + 5 * i].LN = hash_func(new_file[u + 5 * i].CN, LHF_read);

			//create HN
			new_file[u + 5 * i].HN = hash_func(new_file[u + 5 * i].LN, PHF_read);
		}
	}
	inkey_file.close();
}

//write multi_safe
void my_func::write_multi_file() {

	ofstream outm_file;
	outm_file.open("multi_file.txt");

	for (int i = 0; i < length; i++) {

		//write multi_safe_file
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
	outm_file.close();
}

//write locked_safe_file
void my_func::write_locked_safe_file() {
	ofstream outl_file;
	outl_file.open("locked_safe_file.txt");

	for (int i = 0; i<length; i++) {
		//write locked_key_file
		outl_file << "NS "<<i+1<<endl;
		outl_file << "ROOT ";
		for (int j = 0; j < 4; j++) {
			outl_file << new_file[5 * i].ROOT[j];
		}
		outl_file << endl;

		for (int j = 0; j < 5; j++) {
			outl_file << "LN" << j << ": ";
			for (int z = 0; z < 4; z++) {
				outl_file << new_file[j + 5 * i].LN[z] << " ";
			}
			outl_file << endl;
		}
	}
	outl_file.close();
	delete new_file;
}

void my_func::loading() {
	cout << "                                             ";
	cout << "..... ";
	Sleep(50);
	cout << "..... ";
	Sleep(50);
	cout << "..... ";
	Sleep(50);
	cout << "..... ";
	Sleep(50);
	cout << "..... ";
	Sleep(50);
	cout << "..... " << endl << endl;
	Sleep(50);
}

//main function
int main() {

	int x;
	int l;

	//class
	my_func func;
	cout << "                                         How much solutions you want?(Input a number)" << endl<<endl;
	cin >> l;
	func.get_length(l);
	func.set_length();

restart:
	//set ROOT
	func.set_ROOT();

	//create hash by random
	func.generate_N();

	//write key_file
	x = func.write_key_file();
	if (x == 10000) {
		func.loading();
		cout << "                                                     Generate failed!" << endl << endl;
		cout << "                                             Input '1' to restart, '0' to quit" << endl<<endl;
		int r;
		cin >> r;
		if (r == 1) {
			cout << "                                                   You choose restart!" << endl << endl;;
	//		system("pause");
			goto restart;
		}
		else {
			char r;
			cout << "                                                    The program is over!" << endl << endl;
			cout << "                                                    Press any key to exit" << endl << endl;
		//	system("pause");
			cin >> r;
			exit(0);
		}
	}
	else {
		char y;
		func.loading();
		cout << "                                                     Generate Succeed!" << endl<<endl;
		cout << "                                                   Press any key to exit" << endl << endl;
		cin >> y;
	}

	//read key_file
	func.read_key_file();

	//write multi_file
	func.write_multi_file();

	//write locked_safe_file
	func.write_locked_safe_file();

	//system("pause");
	return 0;

}