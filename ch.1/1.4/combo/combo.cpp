/*
ID: Karl Liang
TASK: combo
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

#define MIN_COMB 5

// |1|..2..3..4..5..|6|
#define MIN_NO_OVERLAP_DIST 5
// |1|..|46|..47..48..49..50
#define MAX_NO_OVERLAP_DIST(n) ((n)-5)

ofstream fout ("combo.out");
ifstream fin ("combo.in");

// FIXME: Should be more simple in mathmatical way.
void solution1(int farmers[], int master[], int n) {
	int overlap = 1, offset;
	for (int i = 0; i < 3; i++) {
		offset = abs(farmers[i] - master[i]);
		cout << offset << endl;
		if (offset >= MIN_NO_OVERLAP_DIST
				&& offset <= MAX_NO_OVERLAP_DIST(n)) { // no overlap
			cout << "no overlap" << endl;
			overlap = 0;
			break;
		} else {
			cout << "overlaped" << endl;
			if (n > MIN_COMB) {
				if (offset < MIN_NO_OVERLAP_DIST) // overlap
					overlap *= (MIN_COMB - offset);
				else if (offset > MAX_NO_OVERLAP_DIST(n))
					overlap *= (offset - MAX_NO_OVERLAP_DIST(n));
			} else {
				overlap = n * n * n;
			}

		}
	}
	if (n > MIN_COMB)
		fout << 5*5*5*2 - overlap << endl;
	else
		fout << n*n*n*2 - overlap << endl;

	fout.close();
}

#define OVERLAP_DIST 5
int get_overlap(int f, int m, int n) {
	int dist, max_n_dist;
	// n is within overlap distance, means would be overlap fully.
	max_n_dist = n > OVERLAP_DIST? OVERLAP_DIST : n;
	dist = abs(f-m);
	// no overlap
	if (dist > OVERLAP_DIST && (abs(dist - n) > OVERLAP_DIST))
		return 0;
	else if (max_n_dist < OVERLAP_DIST) // overlap fully
		return max_n_dist;
	else { // overlap partially
		if (dist > max_n_dist)
			dist = abs(n - dist);
		return max_n_dist - dist;
	}
}

void solution2(int farmers[], int master[], int n) {
	int combination;
	combination = n > MIN_COMB?
		MIN_COMB * MIN_COMB * MIN_COMB : n * n * n;

	int overlap;
	overlap = 1;
	for (int i = 0; i < 3; i++)
		overlap *= get_overlap(farmers[i], master[i], n);

	int ans;
	ans = combination * 2 - overlap;
	fout << ans << endl;
	fout.close();
}

int main() {
	int n;
	fin >> n;

	int farmers[3], master[3];
	for (int i = 0; i < 3; i++)
		fin >> farmers[i];

	for (int i = 0; i < 3; i++)
		fin >> master[i];

	fin.close();

	// solution1(farmers, master, n);
	solution2(farmers, master, n);
	return 0;
}
