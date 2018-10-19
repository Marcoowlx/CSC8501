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
	bool valid;
	struct lock* left;
	struct lock* right;
};


//创建5把锁数组
lock new_lock[5];

//创建输出文件数组
lock new_file[500];


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

//打印结构体
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

//判断是否VALID
void w_valid(int i) {
		if (new_file[i].CN[0] == new_file[i].CN[1]) {
		new_file[i].valid = false;
		}
		else if (new_file[i].CN[0] == new_file[i].CN[2])
		{
			new_file[i].valid = false;
		} 
		else if (new_file[i].CN[0] == new_file[i].CN[3]) {
			new_file[i].valid = false;
		}
		else if (new_file[i].CN[1] == new_file[i].CN[2]) {
			new_file[i].valid = false;
		}
		else if (new_file[i].CN[1] == new_file[i].CN[3]) {
			new_file[i].valid = false;
		} 
		else if(new_file[i].CN[2] == new_file[i].CN[3])
		{
			new_file[i].valid = false;
		}
		else
		{
			new_file[i].valid = true;
		}
	
}



int main() {

	//设置时间种子
	srand((unsigned)time(NULL));

	ofstream outkey_file,outm_file;
	ifstream inkey_file,inm_file;
	outkey_file.open("key_file.txt");
	inkey_file.open("key_file.txt");
	outm_file.open("multi_file.txt");
	inm_file.open("multi_file.txt");
	int ROOT; 
	int *arr_CN = new int[4];
	int *arr_LN = new int[4];
	int *arr_HN = new int[4];


	//产生随机hash值
	arr_CN = random(arr_CN);
	arr_LN = random(arr_LN);
	arr_HN = random(arr_HN);

/*	//产生ROOT
	new_lock[0].ROOT = g_root(ROOT);

	//产生CN
	new_lock[0].CN = UHF(new_lock[0].ROOT, arr_CN);
	
	//产生LN
	new_lock[0].LN = LHF(new_lock[0].CN, arr_LN);

	//产生HN
	new_lock[0].HN = PHF(new_lock[0].LN, arr_HN);


	//生成后4把锁
	for (int i = 1; i < 5; i++) {
		new_lock[i].ROOT = new_lock[i - 1].HN;
		new_lock[i].CN = UHF(new_lock[i].ROOT, arr_CN);
		new_lock[i].LN = LHF(new_lock[i].CN, arr_LN);
		new_lock[i].HN = UHF(new_lock[i].LN, arr_HN);
		new_lock[i].left = new_lock[i - 1].right;
		new_lock[i].right = new_lock[i + 1].left;
	}


	//输出5把锁
	for (int i = 0; i < 5; i++) {
		//输出ROOT
		cout << "The ROOT is:" << endl;
		print(new_lock[i].ROOT);
		cout << endl;

		//输出CN
		cout << "The CN is:" << endl;
		print(new_lock[i].CN);
		cout << endl;

		//输出LN
		cout << "The LN is:" << endl;
		print(new_lock[i].LN);
		cout << endl;

		//输出HN
		cout << "The HN is:" << endl;
		print(new_lock[i].HN);
		cout << endl;

	} */

	//输出key_file
	for (int i = 0; i < 100; i++) {

		ROOT= rand() % 10000;

	//	cout <<"i= "<< i << endl;
		
	//	cout << "ROOT= "<<ROOT << endl;
		

		//分割ROOT 并传入结构体ROOT
		new_file[5 * i].ROOT = g_root(ROOT);

	/*	for (int j = 0; j< 4; j++) {
			cout << "ROOT= "<< new_file[i].ROOT[j]<<"  ";
			cout << endl;
		}*/

		//产生第一个CN
		new_file[5 * i].CN = UHF(new_file[5 * i].ROOT, arr_CN);

		//产生第一个LN
		new_file[5 * i].LN = LHF(new_file[5 * i].CN, arr_LN);

		//产生第一个HN
		new_file[5 * i].HN = PHF(new_file[5 * i].LN, arr_HN);

		//循环产生后4把锁
		for (int u = 1; u < 5; u++) {

			new_file[u + 5 * i].ROOT = new_file[5 * i].ROOT;
			//产生CN
			new_file[u + 5 * i].CN = UHF(new_file[(u - 1) + 5 * i].HN, arr_CN);

			//产生LN
			new_file[u + 5 * i].LN = LHF(new_file[u + 5 * i].CN, arr_LN);

			//产生HN
			new_file[u + 5 * i].HN = PHF(new_file[u + 5 * i].LN, arr_HN);
		}

	/*	for (int j = 0; j< 4; j++) {
			cout << "CN= " << new_file[i].CN[j] << endl;
			cout << "CN= " << new_file[i + 1].CN[j] << endl;
			cout << "CN= " << new_file[i + 2].CN[j] << endl;
			cout << "CN= " << new_file[i + 3].CN[j] << endl;
			cout << "CN= " << new_file[i + 4].CN[j] << endl;
			cout << endl;
		}*/
	
		for (int z = 0; z < 5; z++) {
			w_valid(z+5*i);
			
		}
		if (new_file[5*i].valid == true && new_file[1+(5 * i)].valid == true && new_file[2+(5 * i)].valid == true && new_file[3+(5 * i)].valid == true&& new_file[4+(5 * i)].valid == true) {
				outkey_file << "NS" << i + 1 << endl;
				outkey_file << "ROOT ";
				outkey_file << new_file[5*i].ROOT[0] << new_file[5*i].ROOT[1] << new_file[5*i].ROOT[2] << new_file[5*i].ROOT[3] << endl;
				outkey_file << "UHF ";
				outkey_file << "[ " << arr_CN[0] << " ]" << "[ " << arr_CN[1] << " ]" << "[ " << arr_CN[2] << " ]" << "[ " << arr_CN[3] << " ]" << endl;
				outkey_file << "LHF ";
				outkey_file << "[ " << arr_LN[0] << " ]" << "[ " << arr_LN[1] << " ]" << "[ " << arr_LN[2] << " ]" << "[ " << arr_LN[3] << " ]" << endl;
				outkey_file << "PHF ";
				outkey_file << "[ " << arr_HN[0] << " ]" << "[ " << arr_HN[1] << " ]" << "[ " << arr_HN[2] << " ]" << "[ " << arr_HN[3] << " ]" << endl;
				cout << "VALID  "  << endl;
			}
		/*
			else {
				i--;
				cout << "NOT VALID " << endl;
			}
			*/
			else if(new_file[5 * i].valid == false || new_file[1 + (5 * i)].valid == false || new_file[2 + (5 * i)].valid == false || new_file[3 + (5 * i)].valid == false || new_file[4 + (5 * i)].valid == false){
				i--;
				cout << "NOT VALID " << endl;
			}
			else {
				i--;
				cout << "else run" << endl;
			}
	
		
	}


	//整行读取文件
	string s[500];
	for (int i = 0; i < 500; i++) {
		getline(inkey_file, s[i]);
		cout << s[i] << endl;
	}

	//分割UHF LHF RHF
	vector<string> v1 = split(s[2], ",[] "); //可按多个字符来分隔;

	//String转为int型
	int UHF_read[4];
	for (int i = 0; i < 4; i++) {
		str2int(UHF_read[i], v1[i + 1]);
//		cout << UHF_read[i];
	}
	cout << endl;
	
	vector<string> v2 = split(s[3], ",[] "); //可按多个字符来分隔;
	
	//String转为int型
	int LHF_read[4];
	for (int i = 0; i < 4; i++) {
		str2int(LHF_read[i], v2[i + 1]);
//		cout << LHF_read[i];
	}
	cout << endl;
	

	vector<string> v3 = split(s[4], ",[] "); //可按多个字符来分隔;

	 //String转为int型
	int PHF_read[4];
	for (int i = 0; i < 4; i++) {
		str2int(PHF_read[i], v3[i + 1]);
//		cout << PHF_read[i];
	}
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
		new_file[ 5 * i].CN = UHF(g_root(ROOT_read), UHF_read);

		//产生第一个LN
		new_file[5 * i].LN = LHF(new_file[ 5 * i].CN, LHF_read);

		//产生第一个HN
		new_file[5 * i].HN = PHF(new_file[ 5 * i].LN, PHF_read);

		//循环产生后4把锁
		for (int u = 1; u < 5; u++) {
			//产生CN
			new_file[u+5*i].CN = UHF(new_file[(u-1)+5*i].HN, UHF_read);

			//产生LN
			new_file[u+5*i].LN = LHF(new_file[u+5*i].CN, LHF_read);

			//产生HN
			new_file[u+5*i].HN = PHF(new_file[u+5*i].LN, PHF_read);
		}


	/*	//调用判断VALID函数
		for (int w = 0; w < 5; w++) {
			for (int k = 0; k < 4; k++) {
				cout << new_file[w+5*i].CN[k];
			}
			cout << " ";
			w_valid(w + 5 * i);
			cout << endl;
		}
		*/

	//输出multi_safe_file
		outm_file << "NS" << i + 1 << " ";
		if (new_file[5*i].valid == true && new_file[5*i+1].valid == true && new_file[5*i+2].valid == true && new_file[5*i+3].valid == true && new_file[5*i+4].valid == true  ) {
			outm_file << "VALID" << endl;
		}
		else{
			outm_file << "NOT VALID" << endl;
		}

		for (int j = 0; j < 5; j++) {
			outm_file << "CN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j+5*i].CN[z] ;
			}
			outm_file << ",";

			outm_file << "LN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j+5*i].LN[z];
			}
			outm_file << ",";

			outm_file << "HN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j+5*i].HN[z];
			}
			
			outm_file << endl;
		}

	}


	system("pause");

	outkey_file.close();
	inkey_file.close();
	outm_file.close();
	inm_file.close();
	return 0;

}