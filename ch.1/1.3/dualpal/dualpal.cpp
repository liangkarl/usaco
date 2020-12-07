/*
ID: Karl Liang
TASK: dualpal
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
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

	int n, s;
	fin >> n >> s;

	int at_least_two;
	string digits;

	at_least_two = 0;
	for (int num = 1, find = 0; find < n; num++) {
		for (int base = 2; base <= 10; base++) {
			digits = convert_num(s + num, base);
			if (check_palindromic(digits)) {
				at_least_two++;
				if (at_least_two == 2) {
					fout << s + num << endl;
					find++;
					break;
				}
			}
		}
		at_least_two = 0;
	}
    return 0;
}
