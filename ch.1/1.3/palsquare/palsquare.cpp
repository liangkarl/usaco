/*
ID: Karl Liang
TASK: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <list>

#define TO_INDEX(x) ((x)-1)
#define CONV_SYM(x) (char)((x>9)? 'A'+((x)-10) : '0'+(x))
#define MAX_NUM 300

using namespace std;

bool check_palindromic(const string digits) {
	// cout << digits << " is palindromic? " << endl;
	for (int i = 0; i < digits.length(); i++) {
		// cout << "i=" << i << ", " << digits[i]
			// << " <-> " << digits[TO_INDEX(digits.length())-i] << endl;
		if (digits[i] != digits[TO_INDEX(digits.length())-i])
			return false;
	}
	// cout << "yes" << endl;
	return true;
}

string convert_num(int num, int base) {
	string base_n_number;
	int digit;
	for (int divided = num; divided > 0; divided /= base) {
		digit = divided % base;
		// cout << "divided: " << digit << " -> " << CONV_SYM(digit) << endl;
		base_n_number.insert(base_n_number.begin(), CONV_SYM(digit));
	}
	// cout << base_n_number << endl;
	return base_n_number;
}

int main() {
    ofstream fout ("palsquare.out");
    ifstream fin ("palsquare.in");

	int base_B;
	fin >> base_B;

	string num_str;
	for (int num = 1; num <= MAX_NUM; num++) {
		// cout << "num: " << num << endl;
		num_str = convert_num(num * num, base_B);
		if (check_palindromic(num_str))
			fout << convert_num(num, base_B) << " " << num_str << endl;
	}
    return 0;
}
