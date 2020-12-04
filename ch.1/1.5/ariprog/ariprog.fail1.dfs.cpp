/*
ID: karl liang
TASK: ariprog
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <list>

#define TOTAL 1000
#define SQUARE(x) ((x)*(x))
#define TO_INDEX(n) ((n)-1)

using namespace std;

typedef pair<int, int> ab_pair;

list<ab_pair> ab;
int array[25];

set<int> generate_pq(int m) {
	// generate p^2 + q^2 set
	set<int> pq;
	for (int p = 0; p <= m; p++)
		for (int q = 0; q <= m; q++)
			pq.insert(SQUARE(p) + SQUARE(q));

	return pq;
}

void check_seq(int n) {
	// select 5 elements to calculate if matched a+nb seq
	int a = array[0];
	int b = array[1] - a;
	cout << "a:" << a << ", "
		<< "b:" << b << '\n';

	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << '\n';

	for (int i = 2; i < n; i++)
		if (array[i] - array[i-1] != b)
			return;

	ab_pair pair(a, b);
	ab.push_back(pair);
	return;
}

void find_seq(int depth, int n, set<int> pq) {
	// if reach n, check array
	// check all seq are matched a + nb
	if (depth == n)
		return check_seq(n);

	if (pq.size() == 0)
		return;

	// get elements from pq
	set<int> subset;

	subset = pq;
	for (int val : pq) {
		array[depth] = val;
		subset.erase(val);
		find_seq(depth+1, n, subset);
		// no need to rest cause we don't want duplicated elements
	}
	return;
}

int main() {
	ifstream fin ("ariprog.in");
	int n, m;
	fin >> n >> m;

	set<int> pq;
	pq = generate_pq(m);
	for (int val : pq)
		cout << val << " ";
	cout << '\n';

	find_seq(0, n, pq);
	ab.sort([](const ab_pair &a, const ab_pair &b) {
		return a.first < b.first || a.second < b.second;
	});

	ofstream fout ("ariprog.out");
	int len;

	len = ab.size();
	if (len > TOTAL)
		len = TOTAL;
	for (int i = 0; i < len; i++) {
		fout << ab.begin()->first << " "
			<< ab.begin()->second << '\n';
		ab.pop_front();
	}

	if (len == 0)
		fout << "NONE" << '\n';

	return 0;
}
