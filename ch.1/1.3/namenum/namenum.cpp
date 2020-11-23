/*
ID: B9532025
TASK: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <list>

using namespace std;

#define TO_KEYPAD_NUM(x) ((x)+2)
#define TO_INDEX(x) ((x)-'A')
#define DIC_LEN 4616

string name_to_num(const string name) {
	// static const char table[][3] = {
	// 	{'A','B','C'},
	// 	{'D','E','F'},
	// 	{'G','H','I'},
	// 	{'J','K','L'},
	// 	{'M','N','O'},
	// 	{'P','R','S'},
	// 	{'T','U','V'},
	// 	{'W','X','Y'},
	// };
	char table[26] = {0};
	table[TO_INDEX('A')] = table[TO_INDEX('B')] = table[TO_INDEX('C')] = 2;
	table[TO_INDEX('D')] = table[TO_INDEX('E')] = table[TO_INDEX('F')] = 3;
	table[TO_INDEX('G')] = table[TO_INDEX('H')] = table[TO_INDEX('I')] = 4;
	table[TO_INDEX('J')] = table[TO_INDEX('K')] = table[TO_INDEX('L')] = 5;
	table[TO_INDEX('M')] = table[TO_INDEX('N')] = table[TO_INDEX('O')] = 6;
	table[TO_INDEX('P')] = table[TO_INDEX('R')] = table[TO_INDEX('S')] = 7;
	table[TO_INDEX('T')] = table[TO_INDEX('U')] = table[TO_INDEX('V')] = 8;
	table[TO_INDEX('W')] = table[TO_INDEX('X')] = table[TO_INDEX('Y')] = 9;

	// int y_max, x_max;
	// x_max = sizeof(table[0]);
	// y_max = sizeof(table)/x_max;

	string digits;
	// bool is_found = false;
	for (int i = 0; i < name.length(); i++)
		digits.append(to_string(table[TO_INDEX(name[i])]));

	// cout << "find: " << name << " -> ";
	// for (int t = 0; t < name.length(); t++) {
		// for(int i = 0; i < y_max; i++) {
		// 	for (int j = 0; j < x_max; j++) {
		// 		if (table[i][j] == name[t]) {
		// 			digits.append(to_string(TO_KEYPAD_NUM(i)));
		// 			is_found = true;
		// 			goto out_loop;
		// 		}
		// 	}
		// }
		// out_loop:
		// if (!is_found) {
		// 	// cout << "no matched" << endl;
		// 	return "";
		// }
	// }

	// cout << digits << endl;
	return digits;
}

typedef map<string, list<string>> table;
typedef list<string> strlist;

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    // ifstream fdic ("namenumdict.txt");
    ifstream fdic ("dict.txt");

	string digits;
	fin >> digits;

	string dic[DIC_LEN];
	string dic_str;
	string dic_val;
	strlist *names;
	table &table = *new ::table();
	for (int i = 0; i < DIC_LEN; i++) {
		fdic >> dic_str;
		dic_val = name_to_num(dic_str);
		names = &table[dic_val];
		if (!dic_val.empty()) {
			names->push_back(dic_str);
			table[dic_val] = *names;
		}
	}

	string result;
	names = &table[digits];
	if (names->empty()) {
		fout << "NONE" << endl;
	} else {
		// cout << "digits: " << digits << endl;
		for (string str : *names)
			result.append(str).append("\n");
		fout << result;
	}
    return 0;
}
