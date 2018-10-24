#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

struct lock {
	int *ROOT = new int[4];
	int *CN = new int[4];
	int *LN = new int[4];
	int *n_LN = new int[4];
	int *HN = new int[4];
	struct lock* left;
	struct lock* right;
};

class my_func {
public:
	my_func() {};
	~my_func() {};
	int* g_root(int a);
	vector<string>  split(const string &s, const string &seperator);
	void str2int(int &int_temp, const string &string_temp);
	int* hash_func(int* first, int * last);
	int* UHF(int* first, int* last);
	int* LHF(int* first, int* last);
	int* PHF(int* first, int* last);
	void write_key_file();
	void write_multi_file();
	void read_file();
	void unlock();
	void only();
private:
	lock new_file[500];
	//创建UHF LHF数组
	int n_UHF[4];
	int n_LHF[4];
	int n_PHF[4];
	int *ROOT_read = new int[4];
	ofstream outkey_file;
	ofstream outm_file;
	ifstream inkey_file;
	ofstream true_key_file;
	ofstream true_multi_file;
	int count;
	int u_l[4];
};

//拆分ROOT
int* my_func::g_root(int a) {
	int * root = new int[4];
	root[0] = a / 1000;
	root[1] = a % 1000 / 100;
	root[2] = a % 100 / 10;
	root[3] = a % 10;
	return root;
}

//读取数据的分割
vector<string>  my_func::split(const string &s, const string &seperator) {
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
void my_func::str2int(int &int_temp, const string &string_temp)
{
	stringstream stream(string_temp);
	stream >> int_temp;
}

//hash转换
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

//判断是否有效
/*bool my_func::valid() {
	int ret=true;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 5; j++) {
			//判断LN
			for (int k = 0; k < 4; k++) {
				if (new_file[j + 5 * i].LN[k] == new_file[j + 5 * i].n_LN[k]){
					ret = true;
				}
				else {
					goto restart;
				}
			}
			//判断CN
			if (new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[1] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[2] == new_file[j + 5 * i].CN[3]) {
				goto restart;
			}
			else {
				ret = true;
			}
		}
	}
	return ret;
}*/
		
//write key_file
void my_func::write_key_file() {
	
	for (int i = 0; i < 100; i++) {
		outkey_file << "NS" << i + 1 << endl;
		outkey_file << "ROOT ";
		outkey_file << new_file[5 * i].ROOT[0] << new_file[5 * i].ROOT[1] << new_file[5 * i].ROOT[2] << new_file[5 * i].ROOT[3] << endl;
		outkey_file << "UHF ";
		outkey_file << "[ " << n_UHF[0] << " ]" << "[ " << n_UHF[1] << " ]" << "[ " << n_UHF[2] << " ]" << "[ " << n_UHF[3] << " ]" << endl;
		outkey_file << "LHF ";
		outkey_file << "[ " << n_LHF[0] << " ]" << "[ " << n_LHF[1] << " ]" << "[ " << n_LHF[2] << " ]" << "[ " << n_LHF[3] << " ]" << endl;
		outkey_file << "PHF ";
		outkey_file << "[ " << n_PHF[0] << " ]" << "[ " << n_PHF[1] << " ]" << "[ " << n_PHF[2] << " ]" << "[ " << n_PHF[3] << " ]" << endl;
	}
	
}

//write multi_file
void my_func::write_multi_file() {
	for (int i = 0; i < 100; i++) {

		//输出multi_safe_file
		outm_file << "NS" << i + 1 << " ";
		outm_file << "VALID" << endl;

		for (int j = 0; j < 5; j++) {
			outm_file << "CN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j + 5 * i].CN[z];
			}
			outm_file << ",";

			outm_file << "LN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j + 5 * i].n_LN[z];
			}
			outm_file << ",";

			outm_file << "HN" << j << " ";
			for (int z = 0; z < 4; z++) {
				outm_file << new_file[j + 5 * i].HN[z];
			}
			outm_file << endl;
		}
	}
}

//读取文件
void my_func::read_file() {
	ifstream inl_file;
	inl_file.open("locked_safe_file.txt");
	string s[700];
	for (int i = 0; i < 700; i++) {
		getline(inl_file, s[i]);
	}

	//分割第一个ROOT
	vector<string> vroot = split(s[1], " ");
	
	//分割第一个LN
	vector<string> vLN = split(s[2], ":  ");

	//分割第二个LN
	vector<string> VLN2 = split(s[3], ":  ");
	

	int ROOT;
	int LN1_read[4];
	int LN2_read[4];

	//获取4位ROOT
	str2int(ROOT, vroot[1]);
	ROOT_read = g_root(ROOT);

	//获取4位LN
	for (int i=0; i < 4; i++) {
		str2int(LN1_read[i], vLN[i+1]);
		str2int(LN2_read[i], VLN2[i+1]);
	}
	
	//计算出PHF
	for (int i = 0; i < 4; i++) {
		n_PHF[i] = ((LN2_read[i] + ROOT_read[i] - LN1_read[i] - LN1_read[i] )+ 40) %10;
	//	cout << PHF[i]<<" ";
	}
	
	//读入所有LN
	vector<string> e_LN;
	vector<string> e_ROOT;
	
	//将LN放入new_file
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 5; j++) {
			//分割LN
			e_LN = split(s[(j+2) + 7 * i], ":  ");
			//cout << "LN= ";
			for (int k = 0; k < 4; k++) {
				str2int(new_file[j + 5 * i].LN[k], e_LN[k+1]);
			//	cout  << new_file[j + 5 * i].LN[k];
			}
		//	cout << endl;
		}
		//将ROOT放入new_file
		e_ROOT = split(s[1+7*i], " ");
		int root;
		str2int(root, e_ROOT[1]);
		new_file[5 * i].ROOT = g_root(root);
	}
	
	//生成HN
	for (int i = 0; i < 500; i++) {
		new_file[i].HN = PHF(new_file[i].LN, n_PHF);
	//	cout << "HN= ";
		for (int j = 0; j < 4; j++) {
	//		cout << new_file[i].HN[j];
		}
	//	cout << endl;
	}
}

//解锁
void my_func::unlock() {
	
	count = 0;
	outkey_file.open("new_key_file.txt");
	outm_file.open("new_multi_file.txt");

	//计算UHF+LHF UHF+LHF=（LN-(I-1)HN）
	
	for (int i = 0; i < 4; i++) {
		u_l[i] = ((new_file[0].LN[i] - ROOT_read[i]) + 20) % 10;
	//	cout << u_l[i];
	}
	cout << endl;
	int cir = 0;
	int test[10000];
	for (int i = 0; i < 10000; i++)
		test[i] = i;
	int *split = new int[4];
	

restart:
//	cout << cir << endl;
	split = g_root(test[cir]);
	cir++;
	if (cir == 10000) {
		cout << "have try all solution!" << endl;
		only();
		system("pause");
		exit(0);
	}


	//随机4个数字给UHF
	n_UHF[0] = split[0];
	n_UHF[1] = split[1];
	n_UHF[2] = split[2];
	n_UHF[3] = split[3];
	//得出LHF
	n_LHF[0] = u_l[0] - n_UHF[0];
	n_LHF[1] = u_l[1] - n_UHF[1];
	n_LHF[2] = u_l[2] - n_UHF[2];
	n_LHF[3] = u_l[3] - n_UHF[3];

	

	bool open = true;


	//通过新的hash生成锁
	for (int i = 0; i < 100; i++) {
		//生成第一把锁
		new_file[5 * i].CN = UHF(new_file[5 * i].ROOT, n_UHF);
		new_file[5 * i].n_LN = LHF(new_file[5 * i].CN, n_LHF);
		//循环生成4把锁
		for (int j = 1; j < 5; j++) {
			new_file[j + 5 * i].CN = UHF(new_file[j + 5 * i - 1].HN, n_UHF);
			new_file[j + 5 * i].n_LN = LHF(new_file[j + 5 * i].CN, n_LHF);
		}
	}


	//判断是否VALID
	//100套锁
	for (int i = 0; i < 100; i++) {
		//每套5把锁
		for (int j = 0; j < 5; j++) {
			//判断LN
			for (int k = 0; k < 4; k++) {
						if (new_file[j + 5 * i].LN[k] == new_file[j + 5 * i].n_LN[k]) {
							open = true;
						}
						else {
							goto restart;
						}
					}
			//判断CN
			if (new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[1] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[2] == new_file[j + 5 * i].CN[3]) {
						goto restart;
					}
			else {
						open = true;
					}
		}
		if (open == false) {
			goto restart;
		}
		else {
			}
		}
		
		
		
		if (open == true) {
			cout << "The lock open!"  << endl;
			cout << "The UHF is:" << endl;
			for (int j = 0; j < 4; j++) {
				cout << n_UHF[j] << " ";
			}
			cout << endl;
			cout << "The LHF is:" << endl;
			for (int j = 0; j < 4; j++) {
				cout << n_LHF[j] << " ";
			}
			cout << endl;
			write_key_file();
			write_multi_file();
			
			cout << "count= " << count<<endl;
			count++;
		//	system("pause");
			goto restart;
		//	exit(0);
		}
		else {
			goto restart;
		}
	
		outkey_file.close();
		outm_file.close();
}

void my_func::only() {
	ifstream old_key_file;
	//打开新的文件
	inkey_file.open("new_key_file.txt");
	//打开原来的文件
	old_key_file.open("key_file.txt");
	//打开true key file
	true_key_file.open("true_key_file.txt");
	//打开tru multi file
	true_multi_file.open("true_multi_file.txt");
	
	int length;
	int read_UHF[4];
	int read_old[4];
	int UHF_equal[4];
	int LHF_equal[4];
	length= count * 500;
	string *s =new string[length];
	string old_key[500];

	//读取新生成的key_file
	for (int i = 0; i < length; i++) {
		getline(inkey_file, s[i]);
	}

	//读取原来的UHF
	for (int i = 0; i < 500; i++) {
		getline(old_key_file, old_key[i]);
	}


	vector<string> oldkey = split(old_key[2], "[] ");
	cout << "old key is:" << endl;
	for (int i = 0; i < 4; i++) {
		str2int(read_old[i], oldkey[i+1]);
		if (read_old[i] < 0)
			read_old[i] = read_old[i] + 10;
		cout << read_old[i];
	}

	
	//获取新的UHF
	for (int i = 0; i < count; i++) {
		//读取文件
		vector<string> vUHF = split(s[2 + 500 * i], "[] ");
		//转换为int型
		str2int(read_UHF[0], vUHF[1]);
		str2int(read_UHF[1], vUHF[2]);
		str2int(read_UHF[2], vUHF[3]);
		str2int(read_UHF[3], vUHF[4]);
		cout << "New key is:" << endl;
		for (int i = 0; i < 4; i++) {
			cout << read_UHF[i];
		}
		cout << endl;

		//与course1的UHF进行比较
		if (read_UHF[0] == read_old[0] && read_UHF[1] == read_old[1] && read_UHF[2] == read_old[2] && read_UHF[3] == read_old[3]) {
			cout << "equal!" << endl;
			UHF_equal[0] = read_UHF[0];
			UHF_equal[1] = read_UHF[1];
			UHF_equal[2] = read_UHF[2];
			UHF_equal[3] = read_UHF[3];

			LHF_equal[0] = u_l[0] - read_UHF[0];
			LHF_equal[1] = u_l[1] - read_UHF[1];
			LHF_equal[2] = u_l[2] - read_UHF[2];
			LHF_equal[3] = u_l[3] - read_UHF[3];
	
			for (int i = 0; i < 100; i++) {
				
		
				//输出true_key_file
				true_key_file << "NS" << i + 1 << endl;
				true_key_file << "ROOT ";
				true_key_file << new_file[5 * i].ROOT[0] << new_file[5 * i].ROOT[1] << new_file[5 * i].ROOT[2] << new_file[5 * i].ROOT[3] << endl;
				true_key_file << "UHF ";
				true_key_file << "[ " << UHF_equal[0] << " ]" << "[ " << UHF_equal[1] << " ]" << "[ " << UHF_equal[2] << " ]" << "[ " << UHF_equal[3] << " ]" << endl;
				true_key_file << "LHF ";
				true_key_file << "[ " << LHF_equal[0] << " ]" << "[ " << LHF_equal[1] << " ]" << "[ " << LHF_equal[2] << " ]" << "[ " << LHF_equal[3] << " ]" << endl;
				true_key_file << "PHF ";
				true_key_file << "[ " << n_PHF[0] << " ]" << "[ " << n_PHF[1] << " ]" << "[ " << n_PHF[2] << " ]" << "[ " << n_PHF[3] << " ]" << endl;

				//根据true_key重新生成CN
				for (int i = 0; i < 100; i++) {
					new_file[5 * i].CN = UHF(new_file[5 * i].ROOT, UHF_equal);
					for (int j = 1; j < 5; j++) {
						new_file[j + 5 * i].CN = UHF(new_file[j + 5 * i - 1].HN, UHF_equal);
					}
				}

				//输出true_multi_safe_file
				true_multi_file << "NS" << i + 1 << " ";
				true_multi_file << "VALID" << endl;
				
				for (int j = 0; j < 5; j++) {

					true_multi_file << "CN" << j << " ";
					for (int z = 0; z < 4; z++) {
						true_multi_file << new_file[j + 5 * i].CN[z];
					}
					true_multi_file << ",";

					true_multi_file << "LN" << j << " ";
					for (int z = 0; z < 4; z++) {
						true_multi_file << new_file[j + 5 * i].n_LN[z];
					}
					true_multi_file << ",";

					true_multi_file << "HN" << j << " ";
					for (int z = 0; z < 4; z++) {
						true_multi_file << new_file[j + 5 * i].HN[z];
					}
					true_multi_file << endl;
				}
			}

		/*	cout << "UL" << endl;;
			cout << u_l[0];
			cout << u_l[1];
			cout << u_l[2];
			cout << u_l[3];
			cout << endl;
			cout << "LHF" << endl;;
			cout << LHF_equal[0];
			cout << LHF_equal[1];
			cout << LHF_equal[2];
			cout << LHF_equal[3];
			cout << endl;*/
			system("pause");
			exit(0);
		}
		else
		{
			cout << "no equal" << endl;
		}
	}
}


int main() {

	//初始化class
	my_func func;
	func.read_file();
	func.unlock();
	system("pause");
	return 0;
}