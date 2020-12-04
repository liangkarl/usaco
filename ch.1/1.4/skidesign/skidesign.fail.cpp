/*
ID: karl liang
TASK: skidesign
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>

#define IS_ODD(x) ((x) & 0x1)
#define MAX_THRES 17

using namespace std;

typedef list<int>::iterator IntIt;

void print_loop(list<int> &hills) {
	for (int hill : hills)
		cout << hill << " ";
	cout << '\n';
}

int main() {
	ifstream fin ("skidesign.in");
	int n;
	fin >> n;

	list<int> hills;
	int hill;
	for (int i = 0; i < n; i++) {
		fin >> hill;
		hills.push_back(hill);
	}
	hills.sort();
	print_loop(hills);

	int cost, total;
	int diff;
	bool all_even_diff = false;
	IntIt back, front;
	total = 0;
	diff = MAX_THRES + 1; // for enter
	// hills_list.remove(0);
	front = hills.begin();
	back = hills.end();
	back--;
	all_even_diff = false;
	while (diff > MAX_THRES) {
		// get higher hill with odd-diff and larger than MAX_THRES
		for (; front != hills.end(); front++) {
			diff = *back - *front;
			if (diff > MAX_THRES) {
				if (IS_ODD(diff))
					break;

				if (all_even_diff) {
					diff++;
					cout << "diff++\n";
					break;
				}
			}
		}

		printf("%d - %d => %d\n", *back, *front, diff);
		// no even diff found
		if (front == hills.end()) {
			all_even_diff = true;
			cout << "no even\n";
			goto update_var;
		}

		// calculate min cost;
		cost = (diff - MAX_THRES) / 2;
		total += cost * cost * 2;
		printf("diff(%d), cost(%d), total(%d)\n", diff, cost, total);

		// remove hills since change height only once
		hills.erase(back);
		hills.erase(front);

update_var:
		// update next iterator
		back = hills.end();
		back--;
		front = hills.begin();
		diff = *back - *front;
		print_loop(hills);
	}

	ofstream fout ("skidesign.out");
	fout << total << '\n';
	return 0;
}
