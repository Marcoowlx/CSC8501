#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <Windows.h>

using namespace std;
//create struct
struct lock {
	int *ROOT = new int[4];
	int *CN = new int[4];
	int *LN = new int[4];
	int *n_LN = new int[4];
	int *HN = new int[4];
	struct lock* left;
	struct lock* right;
};

//create class
class my_func {
public:
	my_func() {};
	~my_func() {};
	int count_line(char* filename);
	int* g_root(int a);
	vector<string>  split(const string &s, const string &seperator);
	void str2int(int &int_temp, const string &string_temp);
	int* hash_func(int* first, int * last);
	void read_file();
	void write_key_file();
	void write_multi_file();
	void unlock();
	void only();
	void loading();
private:
	lock new_file[10000];
	//create UHF LHF array
	int n_UHF[4];
	int n_LHF[4];
	int n_PHF[4];
	//create read ROOT array
	int *ROOT_read = new int[4];
	//write new_key_file
	ofstream outkey_file;
	//write new_multi_file
	ofstream outm_file;
	//read new_key_file
	ifstream inkey_file;
	//read loced_safe_file
	ifstream inl_file;
	//write true_key_file
	ofstream true_key_file;
	//write true_multi_file
	ofstream true_multi_file;
	//read key_file
	ifstream old_key_file;
	//count is the number of solution
	int count;
	//value of UHF+LHF
	int u_l[4];
	//lines of locked_safe_file
	
	//number of solution
	int sol;
	
	int txt_count;
};

//count line function
int my_func::count_line(char* filename) {
	ifstream Read;
	Read.open(filename);
	string tmp;
	int n = 0;
	while (getline(Read, tmp, '\n'))
		n++;
	Read.close();
	return n;
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

//split value
//learn from https://www.cnblogs.com/carsonzhu/p/5859552.html
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

//string to int
void my_func::str2int(int &new_int, const string &new_string)
{
	//1. use stringstream
	/*stringstream stream(new_string);
	stream >> new_int;*/

	//2. use atoi
	new_int = atoi(new_string.c_str());
}

//hash func
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

//read locked_safe_file
void my_func::read_file() {
	//open locked_safe_file
	inl_file.open("locked_safe_file.txt");
	txt_count=count_line("locked_safe_file.txt");

	string *s=new string[txt_count];

	for (int k = 0; k < txt_count; k++) {
		getline(inl_file, s[k]);
	}
	
	sol = txt_count / 7;

	loading();

	cout << "                                                 There is " << sol << " locks!" << endl << endl;

	//split first ROOT
	vector<string> vroot = split(s[1], " ");

	//split first LN
	vector<string> vLN = split(s[2], ":  ");

	//spliti second LN
	vector<string> VLN2 = split(s[3], ":  ");

	//first ROOT
	int ROOT;
	//first LN
	int LN1_read[4];
	//second LN
	int LN2_read[4];

	//ROOT to Int and split
	str2int(ROOT, vroot[1]);
	ROOT_read = g_root(ROOT);

	//gain 4 LN
	for (int i = 0; i < 4; i++) {
		str2int(LN1_read[i], vLN[i + 1]);
		str2int(LN2_read[i], VLN2[i + 1]);
	}

	//calculate PHF(2nd LN + ROOT - 2 * first LN)
	for (int i = 0; i < 4; i++) {
		n_PHF[i] = ((LN2_read[i] + ROOT_read[i] - LN1_read[i] - LN1_read[i]) + 40) % 10;
	}

	//read all LN
	vector<string> e_LN;
	vector<string> e_ROOT;

	//put LN into new_file
	for (int i = 0; i < sol; i++) {
		for (int j = 0; j < 5; j++) {
			//分割LN
			e_LN = split(s[(j + 2) + 7 * i], ":  ");
			for (int k = 0; k < 4; k++)
				//LN转换为int并存入new_file
				str2int(new_file[j + 5 * i].LN[k], e_LN[k + 1]);
		}
		//split ROOT
		e_ROOT = split(s[1 + 7 * i], " ");
		int root;
		//ROOT to int and put into new_file
		str2int(root, e_ROOT[1]);
		new_file[5 * i].ROOT = g_root(root);
	}

	//generate HN
	for (int i = 0; i < sol * 5; i++) {
		//generate HN by PHF and put into new_file
		new_file[i].HN = hash_func(new_file[i].LN, n_PHF);
	}
	inl_file.close();
}

//write key_file
void my_func::write_key_file() {
	for (int i = 0; i < sol; i++) {
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
	for (int i = 0; i < sol; i++) {
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

//unlock
void my_func::unlock() {
	//The number of right solution is 0 from beginning
	count = 0;

	//open file stream
	outkey_file.open("new_key_file.txt");
	outm_file.open("new_multi_file.txt");

	//calculate UHF+LHF UHF+LHF=(LN-(I-1)HN)
	for (int i = 0; i < 4; i++) 
		u_l[i] = ((new_file[0].LN[i] - ROOT_read[i]) + 20) % 10;

	//count try times
	int cir = 0;

	//gain value from 0000 to 9999
	int test[10000];
	for (int i = 0; i < 10000; i++)
		test[i] = i;


	int *split = new int[4];
	
restart:
	//int to array[4]
	split = g_root(test[cir]);

	//try times+1
	cir++;

	//End after try for 10000 times
	if (cir == 10000) {
		loading();
		char y;
		cout << "                                                Generate "<<count<<" solutions!" << endl<<endl;
		//call only() function
		only();
//		system("pause");
		cout << "                                                Press any key to exit" << endl<<endl;
		cin >> y;
		exit(0);
	}

	//random 4 number to UHF
	n_UHF[0] = split[0];
	n_UHF[1] = split[1];
	n_UHF[2] = split[2];
	n_UHF[3] = split[3];

	//get LHF by (UHF+LHF)-UHF
	n_LHF[0] = u_l[0] - n_UHF[0];
	n_LHF[1] = u_l[1] - n_UHF[1];
	n_LHF[2] = u_l[2] - n_UHF[2];
	n_LHF[3] = u_l[3] - n_UHF[3];

	//whether solution is right
	bool open = true;

	//create lock by new hash
	for (int i = 0; i < sol; i++) {
		//create first lock
		new_file[5 * i].CN = hash_func(new_file[5 * i].ROOT, n_UHF);
		new_file[5 * i].n_LN = hash_func(new_file[5 * i].CN, n_LHF);

		//create 4 locks
		for (int j = 1; j < 5; j++) {
			new_file[j + 5 * i].CN = hash_func(new_file[j + 5 * i - 1].HN, n_UHF);
			new_file[j + 5 * i].n_LN = hash_func(new_file[j + 5 * i].CN, n_LHF);
		}
	}

	//whether is VALID
	for (int i = 0; i < sol; i++) {
		//5 locks each
		for (int j = 0; j < 5; j++) 
		{
			//compare LN
			for (int k = 0; k < 4; k++) {
						//if LN equals
						if (new_file[j + 5 * i].LN[k] == new_file[j + 5 * i].n_LN[k])
							open = true;
						//if LN doesnt equal,restart
						else 
							goto restart;
			}
			//compare CN
			if (new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[1] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[0] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[2] || new_file[j + 5 * i].CN[1] == new_file[j + 5 * i].CN[3] ||
				new_file[j + 5 * i].CN[2] == new_file[j + 5 * i].CN[3]) 
				//if CN has repeat number，restart
				goto restart;
			else 
				//if CN doesnt repeat
				open = true;
		}
		//if not right,restart
		if (open == false) 
			goto restart;
	}
		
	//whether is VALID
	if (open == true) {
		//write right UHF and LHF
		write_key_file();
		write_multi_file();
		count++;
		goto restart;
	}
	else 
		goto restart;
	
	outkey_file.close();
	outm_file.close();
	delete split;
}

//generate true key
void my_func::only() {
	//open new_key_file
	inkey_file.open("new_key_file.txt");
	//open key_file
	old_key_file.open("key_file.txt");
	//open true key file
	true_key_file.open("true_key_file.txt");
	//open tru multi file
	true_multi_file.open("true_multi_file.txt");
	
	//length of new_key_file
	int length;
	//UHF read from new
	int read_UHF[4];
	//old UHF
	int read_old[4];
	//same UHF
	int UHF_equal[4];
	//same LHF
	int LHF_equal[4];
	//calculate the length
	length= count * 5* sol;

	//string of new_key_file
	string *s =new string[length];
	//string of key_file
	string *old_key=new string[sol*5];

	//read new_key_file
	for (int i = 0; i < length; i++) {
		getline(inkey_file, s[i]);
	}

	//read old UHF
	for (int i = 0; i < sol*5; i++) {
		getline(old_key_file, old_key[i]);
	}

	//split old UHF
	vector<string> oldkey = split(old_key[2], "[] ");
	for (int i = 0; i < 4; i++) {
		//String to Int
		str2int(read_old[i], oldkey[i+1]);
		//if less than 0
		if (read_old[i] < 0)
			read_old[i] = read_old[i] + 10;
	}

	//get new UHF
	for (int i = 0; i < count; i++) {
		//split new UHF
		vector<string> vUHF = split(s[2 + (5*sol * i)], "[] ");

		//String to int
		for (int j = 0; j < 4; j++) 
			str2int(read_UHF[j], vUHF[j + 1]);
	


		//compare with UHF in course1
		if (read_UHF[0] == read_old[0] && read_UHF[1] == read_old[1] && read_UHF[2] == read_old[2] && read_UHF[3] == read_old[3]) {
			for (int i = 0; i < 4; i++) {
				// give the value of read_UHF to UHF_equal
				UHF_equal[i] = read_UHF[i];
				// calculate the same LHF
				LHF_equal[i] = u_l[i] - read_UHF[i];
			}
			loading();
			//print true UHF
			cout << "                                                  The true UHF is: " << endl;
			cout << "                                                       ";
			for (int i = 0; i < 4; i++) 
				cout << UHF_equal[i]<<" ";
			cout << endl << endl;;

			//print true LHF
			cout << "                                                  The true LHF is: " << endl;
			cout << "                                                       ";
			for (int i = 0; i < 4; i++) 
				cout << LHF_equal[i]<<" ";
			cout << endl;
	
			for (int i = 0; i < sol; i++) {
				//write true_key_file
				true_key_file << "NS" << i + 1 << endl;
				true_key_file << "ROOT ";
				true_key_file << new_file[5 * i].ROOT[0] << new_file[5 * i].ROOT[1] << new_file[5 * i].ROOT[2] << new_file[5 * i].ROOT[3] << endl;
				true_key_file << "UHF ";
				true_key_file << "[ " << UHF_equal[0] << " ]" << "[ " << UHF_equal[1] << " ]" << "[ " << UHF_equal[2] << " ]" << "[ " << UHF_equal[3] << " ]" << endl;
				true_key_file << "LHF ";
				true_key_file << "[ " << LHF_equal[0] << " ]" << "[ " << LHF_equal[1] << " ]" << "[ " << LHF_equal[2] << " ]" << "[ " << LHF_equal[3] << " ]" << endl;
				true_key_file << "PHF ";
				true_key_file << "[ " << n_PHF[0] << " ]" << "[ " << n_PHF[1] << " ]" << "[ " << n_PHF[2] << " ]" << "[ " << n_PHF[3] << " ]" << endl;

				//generate CN by true_key
				for (int i = 0; i < sol; i++) {
					new_file[5 * i].CN = hash_func(new_file[5 * i].ROOT, UHF_equal);
					for (int j = 1; j < 5; j++) {
						new_file[j + 5 * i].CN = hash_func(new_file[j + 5 * i - 1].HN, UHF_equal);
					}
				}

				//write true_multi_safe_file
				true_multi_file << "NS" << i + 1 << " ";
				true_multi_file << "VALID" << endl;
				
				for (int j = 0; j < 5; j++) {
					true_multi_file << "CN" << j << " ";
					for (int z = 0; z < 4; z++) 
						true_multi_file << new_file[j + 5 * i].CN[z];
					true_multi_file << ",";

					true_multi_file << "LN" << j << " ";
					for (int z = 0; z < 4; z++) 
						true_multi_file << new_file[j + 5 * i].n_LN[z];
					true_multi_file << ",";

					true_multi_file << "HN" << j << " ";
					for (int z = 0; z < 4; z++) 
						true_multi_file << new_file[j + 5 * i].HN[z];
					true_multi_file << endl;
				}
			}
			cout << endl;
			cout << "                                                  Thanks for using!" << endl<<endl;
			inkey_file.close();
			old_key_file.close();
			true_key_file.close();
			true_multi_file.close();
		}
	}
}

void my_func::loading() {
	cout << "                                          ";
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

	//class
	my_func func;
	cout << "                                                       Welcome!" << endl << endl;
	//call read_file()
	func.read_file();
	//call unlock()
	func.unlock();

//	system("pause");
	return 0;
}