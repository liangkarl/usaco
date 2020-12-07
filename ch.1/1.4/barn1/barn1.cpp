/*
ID: Karl Liang
TASK: barn1
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int compare(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int main() {
	ofstream fout ("barn1.out");
	ifstream fin ("barn1.in");

	int max_boards, stall_num, cow_in_stall;
	fin >> max_boards >> stall_num >> cow_in_stall;

	int cows[cow_in_stall];
	for (int i = 0; i < cow_in_stall; i++)
		fin >> cows[i];
	qsort(cows, cow_in_stall, sizeof(int), compare);

	int dist[cow_in_stall];
	int index;
	index = cows[0];
	for (int i = 1; i < cow_in_stall; i++) {
		dist[i-1] = cows[i] - index;
		index = cows[i];
		// cout << dist[i-1] << ", ";
	}
	dist[cow_in_stall-1] = stall_num + 1; // impssible value
	// cout << endl;
	qsort(dist, cow_in_stall, sizeof(int), compare);

	if (max_boards < cow_in_stall) {
		int diff, amount;
		diff = cow_in_stall - max_boards;
		amount = 0;
		for (int i = 0; i < diff; i++) {
			// printf("dist[%d]=%d\n", i, dist[i]);
			amount += (dist[i] - 1);
		}
		// cout << "cow_in_stall: " << cow_in_stall << ", "
		// 	<< "amount: " << amount << endl;
		fout << cow_in_stall + amount << endl;
	} else {
		fout << cow_in_stall << endl;
	}
	return 0;
}
