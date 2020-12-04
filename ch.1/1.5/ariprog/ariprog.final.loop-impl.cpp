/*
ID: karl liang
TASK: ariprog
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

#define TOTAL 1000
#define MAX_M 251 // 0 ~ 250 => 251 num
#define MAX_N 25
#define SQUARE(x) ((x)*(x))
#define TO_INDEX(n) ((n)-1)

using namespace std;

typedef pair<int, int> ab_pair;
typedef vector<int>::iterator v_it;

list<ab_pair> ab;
uint16_t table[SQUARE(MAX_M)+SQUARE(MAX_M)];
int table_size = sizeof(table) / sizeof(uint16_t);

vector<int>& generate_pq(int m) {
	// generate p^2 + q^2 set
	static vector<int> pq(SQUARE(m+1));
	int val, ind;
	for (int p = 0; p <= m; p++)
		for (int q = 0; q <= m; q++) {
			val = SQUARE(p) + SQUARE(q);
			ind = p+q*(m+1);
			pq[ind] = val;
		}

	v_it it;
	sort(pq.begin(), pq.end());
	it = unique(pq.begin(), pq.end());
	pq.resize(distance(pq.begin(), it));

	for (int i = 0; i < pq.size(); i++) {
		table[pq[i]] = i;
	}
	return pq;
}

int main() {
	ifstream fin ("ariprog.in");
	int n, m;
	fin >> n >> m;
	fin.close();

	vector<int> &pq = generate_pq(m);
	int *ppq = pq.data();
	// for (int val : pq)
	// 	cout << val << " ";
	// cout << '\n';

	int a, a1b, diff;
	int depth, need, index;
	for (int i = 0; i < pq.size(); i++) {
		a = ppq[i];
		// printf("a=%d\n", a);
		if (pq.size() - i < n)
			break;

		for (int j = i+1; j < pq.size(); j++) {
			a1b = ppq[j];
			diff = a1b - a;
			if (pq.size() - j < n - 1)
				break;

			// printf("a1b=%d, diff=%d\n", a1b, diff);
			depth = 2;
			index = j + 1;
			for (; depth < n; depth++) {
				if (pq.size() - index < n - depth) {
					// puts("no enough elements");
					break;
				}

				// go through the row
				need = a + depth * diff;

				if (need > table_size) {
					// puts("more than table size");
					break;
				}
				// printf("table[%d]=%d, ", need, table[need]);
				// printf("pq[%d]=%d\n", table[need], pq[table[need]]);
				if (ppq[table[need]] != need) {
					// puts("no");
					break;
				}

				// puts("find");
				index = table[need];
			}
			if (depth == n) {
				// puts("find");
				ab_pair pair(a, diff);
				ab.push_back(pair);
			}
		}
		// puts("done");
	}
	ab.sort([](const ab_pair &a, const ab_pair &b) {
		return a.first < b.first || a.second < b.second;
	});

	ofstream fout ("ariprog.out");

	if (ab.size() > TOTAL)
		ab.resize(TOTAL);
	for (ab_pair ans : ab) {
		fout << ans.first << " "
			<< ans.second << '\n';
	}
	if (ab.size() == 0)
		fout << "NONE" << '\n';
	fout.close();

	return 0;
}
