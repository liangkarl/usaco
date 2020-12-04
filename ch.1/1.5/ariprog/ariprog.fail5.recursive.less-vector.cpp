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
#define SQUARE(x) ((x)*(x))
#define TO_INDEX(n) ((n)-1)

using namespace std;

typedef pair<int, int> ab_pair;
typedef vector<int>::iterator v_it;

list<ab_pair> ab;
uint16_t table[SQUARE(250)+SQUARE(250)];
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

// void find_seq(int a, int diff, int depth, int n, v_it it, vector<int> &pq) {
void find_seq(int a, int diff, int depth, int n, int index, vector<int> &pq) {
	// printf("depth: %d, ", depth);

	// reach n depth
	if (depth == n) {
		// puts("find");
		ab_pair pair(a, diff);
		ab.push_back(pair);
		return;
	}

	// printf("beg=%d, ", pq[index]);
	// no enough elements for rest len
	// if (abs(distance(pq.end(), it)) < n - depth) {
	if (pq.size() - index < n - depth) {
		// puts("no enough elements");
		return;
	}

	// go through the row
	int need = a + depth * diff;

	if (need > table_size) {
		// puts("more than table size");
		return;
	}
	// printf("table[%d]=%d, ", need, table[need]);
	// printf("pq[%d]=%d\n", table[need], pq[table[need]]);
	int *ppq = pq.data();
	if (ppq[table[need]] != need) {
		// puts("no");
		return;
	}
	// map<int, int>::iterator key;
	// key = tabl.find(need);
	// if (key == tabl.end()) {
	// 	// puts("no");
	// 	return;
	// }

	// vector<int>::iterator dest;
	// dest = lower_bound(it, pq.end(), need);
	// if (*dest != need) {
	// 	// puts("no");
	// 	return;
	// }
	// printf("%d=%d (next)\n", need, pq[table[need]]);

	// keep bfs
	// find_seq(a, diff, depth + 1, n, dest++, pq);
	// find_seq(a, diff, depth + 1, n, key->second, pq);
	find_seq(a, diff, depth + 1, n, table[need], pq);
	return;
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
	for (int i = 0; i < pq.size(); i++) {
		a = ppq[i];
		// printf("a=%d\n", a);
		if (pq.size() - i < n)
			continue;
		for (int j = i+1; j < pq.size(); j++) {
			a1b = ppq[j];
			diff = a1b - a;
			if (diff <= 0 || pq.size() - j < n - 1)
				continue;
			// printf("a1b=%d, diff=%d\n", a1b, diff);
			// find_seq(a, a1b-a, 2, n, pq.begin() + (j+1), pq);
			find_seq(a, a1b-a, 2, n, j+1, pq);
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
