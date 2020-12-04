/*
ID: karl liang
TASK: skidesign
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#define IS_ODD(x) ((x) & 0x1)
#define MAX_THRES 17

using namespace std;

typedef vector<int>::iterator IntIt;

template<typename T>
void print_loop(T &hills) {
	for (int hill : hills)
		cout << hill << " ";
	cout << '\n';
}

int main() {
	ifstream fin ("skidesign.in");
	int n;
	fin >> n;

	vector<int> hills(n);
	for (int i = 0; i < n; i++)
		fin >> hills[i];

	sort(hills.begin(), hills.end());
	print_loop(hills);

	int total, min, max, cost, lowest;
	lowest = INT32_MAX;
	// find the block [i, i+17]
	for (int low = hills.front(); low < hills.back(); low++) {
		min = low;
		max = low + MAX_THRES;
		total = 0;
		for (int val : hills) {
			if (val < min)
				cost = min - val;
			else if (val > max)
				cost = val - max;
			else
				cost = 0;
			total += cost * cost;
		}
		if (total < lowest)
			lowest = total;

		printf("min %d, max %d, total %d, cost %d, lowest %d\n",
				min, max, total, cost, lowest);
	}

	ofstream fout ("skidesign.out");
	fout << lowest << '\n';
	return 0;
}
