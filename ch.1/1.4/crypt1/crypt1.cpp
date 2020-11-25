/*
ID: B9532025
TASK: crypt1
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <list>

using namespace std;

#define ONE_HUND 100
#define TEN 10
#define ONE_THOU 1000
#define TEN_THOU 10000

#define MXIER(x,y) ((x)*10+(y))
#define MXAND(x,y,z) ((x)*100+(y)*10+(z))

bool check_num_in_set(int *list, int len, int val) {
	int d;
	bool find;
	for (int num = val; num > 0; num /= 10) {
		d = num % 10;
		find = false;
		for (int i = 0; i < len; i++) {
			if (list[i] == d) {
				find = true;
				break;
			}
		}
		if (!find)
			return false;
	}
	return true;
}

int find_mxand_and_mxier(int *list, int len) {
	int mxier, mxand, quot;
	int top_num, sec_num;
	int amount;

	amount = 0;
	for (int up_hun = 0; up_hun < len; up_hun++) {
		for (int up_ten = 0; up_ten < len; up_ten++) {
			for (int up_num = 0; up_num < len; up_num++) {
				for (int down_ten = 0; down_ten < len; down_ten++) {
					for (int down_num = 0; down_num < len; down_num++) {
						mxand = MXAND(list[up_hun], list[up_ten], list[up_num]);
						mxier = MXIER(list[down_ten], list[down_num]);
						// cout << mxand << " x " << mxier << endl;
						if (mxand < ONE_HUND)
							goto jump_up_hun;

						if (mxier < TEN)
							break; // chane down_ten

						quot = mxand * mxier;
						// cout << " = " << quot << endl;
						if (quot > TEN_THOU || quot < ONE_THOU
								|| !check_num_in_set(list, len, quot))
							continue; // change down_num

						top_num = list[down_num] * mxand;
						// cout << "top: " << top_num << endl;
						if (top_num >= ONE_THOU
								|| !check_num_in_set(list, len, top_num))
							continue; // change down_num

						sec_num = list[down_ten] * mxand;
						// cout << "sec: " << sec_num << endl;
						if (sec_num >= ONE_THOU
								|| !check_num_in_set(list, len, sec_num))
							break; // change down_ten

						// cout << "  " << mxand << " : " << top_num << endl
							// << "x  " << mxier << " : " << sec_num << endl
							// << "---------" << endl
							// << "  " << quot << endl;
						amount++;
					}
				}
			}
		}
jump_up_hun:
		; // jump here when list[up_hun] == 0
	}
	return amount;
}

int main() {
	ofstream fout ("crypt1.out");
	ifstream fin ("crypt1.in");

	int n;
	fin >> n;

	int list[n];
	for (int i = 0; i < n; i++)
		fin >> list[i];

	fout << find_mxand_and_mxier(list, n) << endl;
	return 0;
}
