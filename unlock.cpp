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

//读取数据的分割
vector<string>  split(const string &s, const string &seperator) {
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

//hash转换
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

//hash转换
int* hash_func(int* first, int  last) {
	int *new_arr = new int[4];
	for (int i = 0; i < 4; i++) {
		if (last >= 0)
			new_arr[i] = (first[i] + last) % 10;
		else
			new_arr[i] = (first[i] + last + 10) % 10;
	}
	return new_arr;
}

//洗牌随机产生hash值
void generate_HF(int array[], int length) {
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

bool valid(int i) {
	
		for (int k = 0; k < 4; k++) {
			/*cout << "Old LN ";
				for (int k = 0; k < 4; k++) {
					cout << new_file[ i ].LN[k];
				}
				cout << endl;
				cout << "New LN ";
				for (int k = 0; k < 4; k++) {
					cout <<new_file[i ].n_LN[k];
				}
				cout << endl;*/


				//判断第一把锁
			if (new_file[5 * i].LN[k] == new_file[5 * i].n_LN[k]) {
				cout << "1st LN equal, go to CN !!!!!!!!!!!!!!!!!!!????????????????????????????????" << endl;
				if (new_file[5 * i].CN[0] == new_file[5 * i].CN[1] || new_file[5 * i].CN[0] == new_file[5 * i].CN[2] || new_file[5 * i].CN[0] == new_file[5 * i].CN[3] ||
					new_file[5 * i].CN[1] == new_file[5 * i].CN[2] || new_file[5 * i].CN[1] == new_file[5 * i].CN[3] ||
					new_file[5 * i].CN[2] == new_file[5 * i].CN[3]) {
					cout << "1st CN equals???????????????????????!!!!!!!!!!!!!!!!!!!!! " << endl;
					return false;
				}
				else {
					//判断第二把锁
					if (new_file[1 + 5 * i].LN[k] == new_file[1 + 5 * i].n_LN[k]) {
						cout << "2nd LN equal, go to CN !!!!!!!!!!!!!!!!!!!????????????????????????????????" << endl;
						if (new_file[1 + 5 * i].CN[0] == new_file[1 + 5 * i].CN[1] || new_file[1 + 5 * i].CN[0] == new_file[1 + 5 * i].CN[2] || new_file[1 + 5 * i].CN[0] == new_file[1 + 5 * i].CN[3] ||
							new_file[1 + 5 * i].CN[1] == new_file[1 + 5 * i].CN[2] || new_file[1 + 5 * i].CN[1] == new_file[1 + 5 * i].CN[3] ||
							new_file[1 + 5 * i].CN[2] == new_file[1 + 5 * i].CN[3]) {
							cout << "2nd CN equals???????????????????????!!!!!!!!!!!!!!!!!!!!! " << endl;
							return false;
						}
						else {
							//判断第三把锁
							if (new_file[2 + 5 * i].LN[k] == new_file[2 + 5 * i].n_LN[k]) {
								cout << "3rd LN equal, go to CN !!!!!!!!!!!!!!!!!!!????????????????????????????????" << endl;
								if (new_file[2 + 5 * i].CN[0] == new_file[2 + 5 * i].CN[1] || new_file[2 + 5 * i].CN[0] == new_file[2 + 5 * i].CN[2] || new_file[2 + 5 * i].CN[0] == new_file[2 + 5 * i].CN[3] ||
									new_file[2 + 5 * i].CN[1] == new_file[2 + 5 * i].CN[2] || new_file[2 + 5 * i].CN[1] == new_file[2 + 5 * i].CN[3] ||
									new_file[2 + 5 * i].CN[2] == new_file[2 + 5 * i].CN[3]) {
									cout << "3rd CN equals???????????????????????!!!!!!!!!!!!!!!!!!!!!" << endl;
									return false;
								}
								else {
									//判断第四把锁
									if (new_file[3 + 5 * i].LN[k] == new_file[3 + 5 * i].n_LN[k]) {
										cout << "4th LN equal, go to CN !!!!!!!!!!!!!!!!!!!????????????????????????????????" << endl;
										if (new_file[3 + 5 * i].CN[0] == new_file[3 + 5 * i].CN[1] || new_file[3 + 5 * i].CN[0] == new_file[3 + 5 * i].CN[2] || new_file[3 + 5 * i].CN[0] == new_file[3 + 5 * i].CN[3] ||
											new_file[3 + 5 * i].CN[1] == new_file[3 + 5 * i].CN[2] || new_file[3 + 5 * i].CN[1] == new_file[3 + 5 * i].CN[3] ||
											new_file[3 + 5 * i].CN[2] == new_file[3 + 5 * i].CN[3]) {
											cout << "4th CN equals???????????????????????!!!!!!!!!!!!!!!!!!!!! " << endl;
											return false;
										}
										else {
											//判断第五把锁
											if (new_file[4 + 5 * i].LN[k] == new_file[4 + 5 * i].n_LN[k]) {
												cout << "5th LN equal, go to CN !!!!!!!!!!!!!!!!!!!????????????????????????????????" << endl;
												if (new_file[4 + 5 * i].CN[0] == new_file[4 + 5 * i].CN[1] || new_file[4 + 5 * i].CN[0] == new_file[4 + 5 * i].CN[2] || new_file[4 + 5 * i].CN[0] == new_file[4 + 5 * i].CN[3] ||
													new_file[4 + 5 * i].CN[1] == new_file[4 + 5 * i].CN[2] || new_file[4 + 5 * i].CN[1] == new_file[4 + 5 * i].CN[3] ||
													new_file[4 + 5 * i].CN[2] == new_file[4 + 5 * i].CN[3]) {
													cout << "4th CN equals???????????????????????!!!!!!!!!!!!!!!!!!!!! " << endl;
													return false;
												}
												else {
													cout << "VALID" << endl;
													return true;
												}

											}
											else {
												cout << "5th LN do not equal" << endl;
												return false;
											}
										}
									}
									else {
										cout << "4th LN do not equal!" << endl;
										return false;
									}
								}
							}
							else {
								cout << "3rd LN do not equal" << endl;
								return false;
							}
						}

					}
					else {
						cout << "2nd LN do not equal!" << endl;
						return false;
					}
				}
			}
			else {
				cout << "1st LN do not equal!" << endl;
				return false;
			}
		}

	
}
		

void read_file() {
	ifstream inl_file;
	inl_file.open("C:\\Users\\b8011457\\Project\\Lock\\Lock\\locked_safe_file.txt");
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
	int *ROOT_read=new int[4];
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
	int PHF[4];
	for (int i = 0; i < 4; i++) {
		PHF[i] = ((LN2_read[i] + ROOT_read[i] - LN1_read[i] - LN1_read[i] )+ 40) %10;
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
		new_file[i].HN = hash_func(new_file[i].LN, PHF);
	//	cout << "HN= ";
		for (int j = 0; j < 4; j++) {
	//		cout << new_file[i].HN[j];
		}
	//	cout << endl;
	}

	//计算UHF+LHF UHF+LHF=（LN-(I-1)HN）
	int u_l[4];
	for (int i = 0; i < 4; i++) {
		u_l[i] = (new_file[0].LN[i] - ROOT_read[i]+20) %10;
		//cout << u_l[i];
	}
	
	//生成数字库
	int base[19] = { -9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9 };

	//打乱数字库
	generate_HF(base, 19);

	//创建UHF LHF数组
	int UHF[4];
	int LHF[4];
	
	int flag = 0;
	//int UHF[4] = {-7,0,9,1};
	//int LHF[4] = {-8,-3,-3,-4};

	//generate_HF(UHF,10000);
/*	for (int i = 0; i < 10000; i++) {
		cout << "UHF= " << UHF[i] << endl;
	}*/
	//generate_HF(LHF,10000);


restart:

	//生成时间种子
	srand((unsigned)time(NULL));

	//随机产生四个数字
	int a1 = rand() % 20;
	int a2 = rand() % 20;
	int a3 = rand() % 20;
	int a4 = rand() % 20;
	int b1 = rand() % 20;
	int b2 = rand() % 20;
	int b3 = rand() % 20;
	int b4 = rand() % 20;

	//随机4个数字给UHF LHF
	UHF[0] = base[a1];
	UHF[1] = base[a2];
	UHF[2] = base[a3];
	UHF[3] = base[a4];

	LHF[0] = base[b1];
	LHF[1] = base[b2];
	LHF[2] = base[b3];
	LHF[3] = base[b4];
	
	bool open = true;


	//通过新的hash生成锁
	for (int i = 0; i < 100; i++) {
		//生成第一把锁
		new_file[5 * i].CN = hash_func(new_file[5 * i].ROOT, UHF);
		new_file[5 * i].n_LN = hash_func(new_file[5 * i].CN, LHF);
		//循环生成4把锁
		for (int j = 1; j < 5; j++) {
			new_file[j + 5 * i].CN = hash_func(new_file[j + 5 * i - 1].HN, UHF);
			new_file[j + 5 * i].n_LN = hash_func(new_file[j + 5 * i].CN, LHF);
		}

	/*	//打印新的LN
		for (int j = 0; j < 5; j++) {
			cout << "new LN=" << endl;
			for (int k = 0; k < 4; k++) {
				cout << new_file[j + 5 * i].n_LN[k];
			}
			cout << endl;
		}*/
	}


	if(flag<10000){
		for (int i = 0; i < 100; i++){
			cout << "Flag= " << flag << endl;
				open=valid(i);
				flag++;
				if (open == true){
					cout << "The lock open!" <<flag<< endl;
					cout << "The UHF is:"<<endl;
					for (int j = 0; j < 4; j++) {
						cout << UHF[j]<<" ";
					}
					cout << endl;
					cout << "The LHF is:"<<endl;
					for (int j = 0; j < 4; j++) {
						cout << LHF[j]<<" ";
					}
					cout << endl;
					system("pause");
					exit(0);
				}
				else {
					cout << "NOT VALID" << endl;
					cout << "New LN=" << endl;
					for (int z = 0; z < 5; z++) {
						for (int j = 0; j < 4; j++)
							cout << new_file[5 * i + z].n_LN[j];
						cout << endl;
					}
					goto restart;
				}
				
		}
	}
	else {
		cout << "GG" << endl;
		cout << "Input 1 to restart, 0 to quit" << endl;
		int h;
		cin >> h;
		if (h == 1) {
			cout << "restart!" << endl;
			system("pause");
			flag = 0;
			goto restart;
		}
		else {
			cout << "Over!" << endl;
			system("pause");
			exit(0);
		}
	}
}

int main() {
	read_file();

	cout << endl;
	system("pause");
	return 0;
}